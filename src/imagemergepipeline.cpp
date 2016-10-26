#include "imagemergepipeline.h"
#include "modmanager.h"
#include "profile.h"
#include "globalsettings.h"
#include "externalprogram.h"
#include "utils.h"
#include <QProcess>
#include <QTemporaryDir>
#include <QColor>

ImageMergePipeline::ImageMergePipeline(Modification *mod, const QString &id) : Pipeline(mod, id)
{
    m_defaultAlgorithm = new AlphaThresholdMergeAlgorithm();
}

ImageMergePipeline::~ImageMergePipeline()
{
    for(MergeAlgorithm * alg : m_mergeAlgorithms.values())
    {
        delete alg;
    }

    delete m_defaultAlgorithm;
}

ImageMergePipeline *ImageMergePipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    ImageMergePipeline * pip = new ImageMergePipeline(mod, id);

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
    }

    QJsonObject merge_json_map = json["merge-algorithm"].toObject();

    for(QString & key : merge_json_map.keys())
    {
        QJsonObject merge_json = merge_json_map[key].toObject();

        QString type = merge_json["algorithm"].toString();

        if(type == "alpha-threshold")
        {
            AlphaThresholdMergeAlgorithm * alg = new AlphaThresholdMergeAlgorithm();
            pip->m_mergeAlgorithms[key] = alg;
        }
        else if(type == "overwrite")
        {
            OverwriteMergeAlgorithm * alg =  new OverwriteMergeAlgorithm();
            pip->m_mergeAlgorithms[key] = alg;
        }
        else if(type == "mask")
        {
            MaskMergeAlgorithm * alg = new MaskMergeAlgorithm();
            pip->m_mergeAlgorithms[key] = alg;
        }
        else if(type == "tile")
        {
            TileMergeAlgorithm * alg = new TileMergeAlgorithm();
            alg->tilesx = merge_json["tilesx"].toInt();
            alg->tilesy = merge_json["tilesy"].toInt();
            pip->m_mergeAlgorithms[key] = alg;
        }
        else
        {
            pip->getLogger().log(Logger::Warning, "pipeline-merge-image", pip->id(), "load", "Unknown image merge type " + type);
        }
    }

    return pip;
}

QString ImageMergePipeline::pipelineType() const
{
    return "merge-image";
}

void ImageMergePipeline::install()
{
    getLogger().log(Logger::Info, "pipeline-merge-image", id(), "install", "Started installation");

    QTemporaryDir tmpdir;

    if(!tmpdir.isValid())
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge", "Could not create temporary directory!");
        return;
    }

    QDir(tmpdir.path()).mkpath(".");

    m_fgInstalledFiles.clear();
    QMap<QString, QString> destinationkeys;
    QMap<QString, QString> resolved_installables = resolveInstallables(m_installables, mod()->getModManager()->profile()->StardewValleyDir().absolutePath(), &destinationkeys);

    for(QString src : resolved_installables.keys())
    {
        QString dst = resolved_installables[src];

        if(!dst.endsWith(".xnb"))
        {
            getLogger().log(Logger::Error, "pipeline-merge-image", id(), "install", "Destination must be XNB file! But is " + dst);
            continue;
        }
        if(!src.endsWith(".png"))
        {
            getLogger().log(Logger::Error, "pipeline-merge-image", id(), "install", "Source must be PNG file! But is " + src);
            continue;
        }
        if(!QFileInfo(dst).exists())
        {
            getLogger().log(Logger::Error, "pipeline-merge-image", id(), "install", "Destination " + dst + " must exist!");
            continue;
        }

        QString inversed_dst = destinationkeys[dst];
        MergeAlgorithm * alg = m_mergeAlgorithms[inversed_dst];

        if(alg == nullptr)
        {
            alg = m_defaultAlgorithm;
        }

        if(merge(dst, src, tmpdir.path(), alg))
            m_fgInstalledFiles.insert(dst); // Mark as installed

    }

    getLogger().log(Logger::Info, "pipeline-merge-image", id(), "install", "Finished installation");
}

QMap<QString, ImageMergePipeline::MergeAlgorithm *> ImageMergePipeline::mergeAlgorithms() const
{
    return m_mergeAlgorithms;
}

bool ImageMergePipeline::merge(const QString &xnb_file, const QString &png_file, const QDir & tmpdir, MergeAlgorithm * alg)
{
    getLogger().log(Logger::Info, "pipeline", id(), "install", "Merging " + png_file + " into " + xnb_file);

    QString basename = QFileInfo(xnb_file).baseName();
    QString destinationfile = tmpdir.absoluteFilePath(basename + ".png");

    // First extract everything
    if(!extract(xnb_file, destinationfile))
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge", "Extraction failed! Skipping.");
        return false;
    }

    // Then merge
    alg->apply(getLogger(), destinationfile, QFileInfo(png_file).absolutePath() + "/" + basename);

    // Then pack it
    QString tmp_xnb = tmpdir.absoluteFilePath(basename + ".xnb");

    if(!pack(destinationfile, tmp_xnb))
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge", "Packing failed! Skipping.");
        return false;
    }
    QFile(xnb_file).remove();
    QFile::copy(tmp_xnb, xnb_file);

    return true;
}

bool ImageMergePipeline::extract(const QString &xnb_file, const QString &destination)
{
    getLogger().log(Logger::Info, "pipeline", id(), "install", "Extracting " + xnb_file + " to " + destination);

    QProcess process;

    ExternalProgram xnb_to_png_program = GlobalSettings::instance()->getExternalProgram("xnb-to-png");

    if(xnb_to_png_program.isEmpty())
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-extract", "xnb-to-png program is empty!");
        return false;
    }

    QStringList args;
    args << xnb_file;
    args << destination;

    ExternalProgram::tryToInfuse(&process, xnb_to_png_program.executablePath(), args);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(utils::joinEnvironments(processEnvironment(), xnb_to_png_program.environment()));

    process.start();
    process.waitForStarted(-1);
    if(process.state() != QProcess::Running)
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-extract", "Failed to start process!");
        return false;
    }
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    getLogger().log(Logger::Info, "pipeline-merge-image", id(), "merge-extract", output);  

    return true;
}

bool ImageMergePipeline::pack(const QString &png_file, const QString &xnb_file)
{
    getLogger().log(Logger::Info, "pipeline", id(), "install", "Packing " + png_file + " into " + xnb_file);

    QProcess process;

    ExternalProgram png_to_xnb_program = GlobalSettings::instance()->getExternalProgram("png-to-xnb");

    if(png_to_xnb_program.isEmpty())
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-pack", "png-to-xnb program is empty!");
        return false;
    }

    QStringList args;
    args << png_file;
    args << xnb_file;

    ExternalProgram::tryToInfuse(&process, png_to_xnb_program.executablePath(), args);
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(utils::joinEnvironments(processEnvironment(), png_to_xnb_program.environment()));

    process.start();
    process.waitForStarted(-1);
    if(process.state() != QProcess::Running)
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-pack", "Failed to start process!");
        return false;
    }
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    getLogger().log(Logger::Info, "pipeline-merge-image", id(), "merge-pack", output);

    return true;
}

bool ImageMergePipeline::AlphaThresholdMergeAlgorithm::apply(Logger &log, const QString &destinationfile, const QString &sourcefilebase)
{
    log.log(Logger::Info, "pipeline", "filter-alpha-threshold", "install", "Applying alpha treshold filter in " + destinationfile);

    QImage img;
    QImage filter;

    img.load(destinationfile);
    filter.load(sourcefilebase + ".png");

    if(img.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-alpha-threshold", "merge-merge", "Image " + destinationfile + " not loadable!");
        return false;
    }
    if(filter.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-alpha-threshold", "merge-merge", "Image " + sourcefilebase + " not loadable!");
        return false;
    }
    if(filter.width() != img.width() || filter.height() != img.height())
    {
        log.log(Logger::Error, "pipeline-tile", "filter-alpha-threshold", "merge-merge", "Images don't have the same size!");
        return false;
    }

    for(int y = 0; y < img.height(); ++y)
    {
        for(int x = 0; x < img.width(); ++x)
        {
            const QColor there = filter.pixelColor(x,y);

            if(there.alpha() > 0)
                img.setPixelColor(x,y,there);
        }
    }

    QFile(destinationfile).remove();
    return img.save(destinationfile);
}


bool ImageMergePipeline::OverwriteMergeAlgorithm::apply(Logger &log, const QString &destinationfile, const QString &sourcefilebase)
{
    log.log(Logger::Info, "pipeline", "filter-overwrite", "install", "Applying overwrite filter in " + destinationfile);

    QImage img;
    QImage filter;

    img.load(destinationfile);
    filter.load(sourcefilebase + ".png");

    if(img.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-overwrite", "merge-merge", "Image " + destinationfile + " not loadable!");
        return false;
    }
    if(filter.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-overwrite", "merge-merge", "Image " + sourcefilebase + " not loadable!");
        return false;
    }
    if(filter.width() != img.width() || filter.height() != img.height())
    {
        log.log(Logger::Error, "pipeline-tile", "filter-overwrite", "merge-merge", "Images don't have the same size!");
        return false;
    }

    for(int y = 0; y < img.height(); ++y)
    {
        for(int x = 0; x < img.width(); ++x)
        {
            const QColor there = filter.pixelColor(x,y);

            img.setPixelColor(x,y,there);
        }
    }

    QFile(destinationfile).remove();
    return img.save(destinationfile);
}

bool ImageMergePipeline::MaskMergeAlgorithm::apply(Logger &log, const QString &destinationfile, const QString &sourcefilebase)
{
    log.log(Logger::Info, "pipeline", "filter-mask", "install", "Applying mask filter in " + destinationfile);

    QImage img;
    QImage filter;
    QImage mask;

    img.load(destinationfile);
    filter.load(sourcefilebase + ".png");
    mask.load(sourcefilebase + ".mask.png");

    if(img.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-mask", "merge-merge", "Image " + destinationfile + " not loadable!");
        return false;
    }
    if(filter.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-mask", "merge-merge", "Image " + sourcefilebase + " not loadable!");
        return false;
    }
    if(mask.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-mask", "merge-merge", "Image " + sourcefilebase + " not loadable!");
        return false;
    }
    if(filter.width() != img.width() || filter.height() != img.height() || mask.height() != img.height() || mask.width() != img.width())
    {
        log.log(Logger::Error, "pipeline-tile", "filter-alpha-threshold", "merge-merge", "Images don't have the same size!");
        return false;
    }

    for(int y = 0; y < img.height(); ++y)
    {
        for(int x = 0; x < img.width(); ++x)
        {
            const QColor there = filter.pixelColor(x,y);
            const QColor here = img.pixelColor(x,y);
            const QColor mod = mask.pixelColor(x,y);
            const double vr = mod.red() / 255.0;
            const double vg = mod.green() / 255.0;
            const double vb = mod.blue() / 255.0;
            const double va = mod.alpha() / 255.0;

            img.setPixelColor(x,y,QColor((int)(there.red() * vr + here.red() * (1.0 - vr)),
                                         (int)(there.green() * vg + here.green() * (1.0 - vg)),
                                         (int)(there.blue() * vb + here.blue() * (1.0 - vb)),
                                         (int)(there.alpha() * va + here.alpha() * (1.0 - va))));
        }
    }

    QFile(destinationfile).remove();
    return img.save(destinationfile);
}

bool ImageMergePipeline::TileMergeAlgorithm::apply(Logger &log, const QString &destinationfile, const QString &sourcefilebase)
{
    log.log(Logger::Info, "pipeline", "filter-tile", "install", "Applying tile filter in " + destinationfile);

    QImage img;
    QImage filter;

    img.load(destinationfile);
    filter.load(sourcefilebase + ".png");

    if(img.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-tile", "merge-merge", "Image " + destinationfile + " not loadable!");
        return false;
    }
    if(filter.isNull())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-tile", "merge-merge", "Image " + sourcefilebase + " not loadable!");
        return false;
    }
    if(filter.width() != img.width() || filter.height() != img.height())
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-tile", "merge-merge", "Images don't have the same size!");
        return false;
    }
    if(tilesx <= 0 || tilesy <= 0)
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-tile", "merge-merge", "Invalid tile count!");
        return false;
    }
    if( filter.width() % tilesx != 0 || filter.height() % tilesy != 0)
    {
        log.log(Logger::Error, "pipeline-merge-image", "filter-tile", "merge-merge", "Image width and height need to be divdeable by tile count!");
        return false;
    }

    // Clear tiles
    int tw = img.width() / tilesx;
    int th = img.height() / tilesy;

    for(int tx = 0; tx < tilesx; ++tx)
    {
        for(int ty = 0; ty < tilesy; ++ty)
        {
            // Determine if tile will be overwritten
            bool overwrite = false;
            for(int y = ty * th; !overwrite && y < (ty + 1) * th; ++y)
            {
                for(int x = tx * tw; !overwrite && x < (tx + 1) * tw; ++x)
                {
                    const QColor there = filter.pixelColor(x,y);

                    if(there.alpha() > 0)
                    {
                        overwrite = true;
                    }
                }
            }

            // Overwrite
            if(overwrite)
            {
                log.log(Logger::Error, "pipeline-merge-image", "filter-tile", "merge-merge", QString("Tile detected @ %1 %2").arg(tx).arg(ty));

                for(int y = ty * th; y < (ty + 1) * th; ++y)
                {
                    for(int x = tx * tw; x < (tx + 1) * tw; ++x)
                    {
                        img.setPixelColor(x,y,QColor(0,0,0,0));
                    }
                }
            }
        }
    }

    // Alpha overwrite
    for(int y = 0; y < img.height(); ++y)
    {
        for(int x = 0; x < img.width(); ++x)
        {
            const QColor there = filter.pixelColor(x,y);

            if(there.alpha() > 0)
            {
                img.setPixelColor(x,y,there);
            }
        }
    }

    QFile(destinationfile).remove();
    return img.save(destinationfile);
}
