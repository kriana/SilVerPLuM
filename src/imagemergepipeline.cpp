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

}

ImageMergePipeline::~ImageMergePipeline()
{

}

ImageMergePipeline *ImageMergePipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    ImageMergePipeline * pip = new ImageMergePipeline(mod, id);

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
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
    QMap<QString, QString> resolved_installables = resolveInstallables(m_installables, mod()->getModManager()->profile()->StardewValleyDir().absolutePath());

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

        if(merge(dst, src, tmpdir.path()))
            m_fgInstalledFiles.insert(dst); // Mark as installed

    }
}

bool ImageMergePipeline::merge(const QString &xnb_file, const QString &png_file, const QDir & tmpdir)
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
    apply(destinationfile, png_file);

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

bool ImageMergePipeline::apply(const QString &imagefile, const QString &filterimagefile)
{
    getLogger().log(Logger::Info, "pipeline", id(), "install", "Applying filter in " + filterimagefile);


    QImage img;
    QImage filter;

    img.load(imagefile);
    filter.load(filterimagefile);

    if(img.isNull())
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-merge", "Image " + imagefile + " not loadable!");
        return false;
    }
    if(filter.isNull())
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-merge", "Image " + filterimagefile + " not loadable!");
        return false;
    }

    if(img.width() != filter.width() || img.height() != filter.height())
    {
        getLogger().log(Logger::Error, "pipeline-merge-image", id(), "merge-merge", "Images have different sizes! Refusing to apply filtering!");
        return false;
    }

    // If no mask is available, just overwrite
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

    QFile(imagefile).remove();
    return img.save(imagefile);
}
