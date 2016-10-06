#include "dllpipeline.h"
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QtXml>
#include <QDirIterator>
#include <QDebug>
#include "globalsettings.h"
#include "platform.h"
#include "utils.h"
#include "modification.h"
#include "modmanager.h"
#include "pipeline.h"
#include "profile.h"
#include "globalsettings.h"

DllPipeline::DllPipeline(Modification *mod, const QString &id) : Pipeline(mod, id)
{
    // Default reference mappings
    setReferenceMapping("MonoGame.Framework", "stardewvalley://MonoGame.Framework.dll");
    setReferenceMapping("Stardew Valley", "stardewvalley://StardewValley.exe");
    setReferenceMapping("xTile", "stardewvalley://xTile.dll");
}

DllPipeline::~DllPipeline()
{

}

DllPipeline *DllPipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    DllPipeline * pip = new DllPipeline(mod, id);

    loadGenericFromJson(json, pip);

    pip->setEnableNugetRestore(json["nuget-restore"].toBool());

    QJsonObject reference_map = json["references"].toObject();

    for(QString ref : reference_map.keys())
    {
        pip->setReferenceMapping(ref, reference_map[ref].toString());
    }

    return pip;
}

void DllPipeline::prime()
{
    /*if(alreadyPrimed())
    {
        qInfo() << "Priming of dll-compile " << id() << " not needed.";
        return;
    }*/

    qInfo() << "Priming dll-compile pipeline " << id();

    if(enableNugetRestore())
        runNuget();

    // Look for *.csproj files and fix the dependencies
    for(QString file : utils::findAllFiles(pipelineBaseDir()))
    {
        if(QFileInfo(file).isFile() && file.endsWith(".csproj"))
        {
            fixReferences(file);
        }
    }

    writePrimeFile();
}

bool DllPipeline::enableNugetRestore() const
{
    return m_enableNugetRestore;
}

void DllPipeline::setEnableNugetRestore(bool enableNugetRestore)
{
    m_enableNugetRestore = enableNugetRestore;
}

QMap<QString, QString> DllPipeline::referenceMap() const
{
    return QMap<QString, QString>(m_referenceMap);
}

void DllPipeline::setReferenceMapping(const QString &reference, const QString &locationurl)
{
    m_referenceMap[reference] = locationurl;
}

bool DllPipeline::alreadyPrimed()
{
    QFile lockfile(pipelineBaseDir().absoluteFilePath("PRIME"));

    if (!lockfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&lockfile);
    return stream.readAll() == Platform::getPlatformString();
}

void DllPipeline::writePrimeFile()
{
    QFile lockfile(pipelineBaseDir().absoluteFilePath("PRIME"));

    qInfo() << "PRIME info file will be written into " << pipelineBaseDir().absoluteFilePath("PRIME");

    if (!lockfile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&lockfile);
    stream << Platform::getPlatformString();
}

void DllPipeline::runNuget()
{
    qInfo() << "Running nuget restore in " << pipelineBaseDir().absolutePath();

    QProcess process;
    process.setProgram(GlobalSettings::instance()->getProgramNuget());
    process.setArguments(QStringList() << "restore");
    process.setWorkingDirectory(pipelineBaseDir().absolutePath());

    process.start();
    process.waitForFinished(-1);
}

void DllPipeline::fixReferences(const QString &projectFile)
{
    qInfo() << "REF_FIX Fixing references in " << projectFile;

    QFile::copy(projectFile, projectFile + ".bak");

    QDomDocument doc;
    QFile file(projectFile);
    if (!file.open(QIODevice::ReadWrite) || !doc.setContent(&file))
    {
        qWarning() << "Unable to open or parse file!";
        return;
    }

    QDomNodeList reference_list = doc.elementsByTagName("Reference");

    for(int i = 0; i < reference_list.size(); ++i)
    {
        QDomNode nd = reference_list.at(i);

        if(nd.attributes().contains("Include"))
        {
            QString raw_include = nd.attributes().namedItem("Include").toAttr().value();
            qDebug() << "REF " <<raw_include;

            QString current_include;

            if(raw_include.contains(","))
            {
                current_include = raw_include.split(",")[0].trimmed();
            }
            else
            {
                current_include = raw_include;
            }

            // For XNA -> MonoGame override
            if(current_include.startsWith("Microsoft.Xna.Framework") && GlobalSettings::instance()->getDLLRedirectXNA())
            {
                qInfo() << "Redirecting " << raw_include << " to MonoGame";

                current_include = "MonoGame.Framework";
            }

            if(m_referenceMap.contains(current_include))
            {
                QString hint = mod()->getModManager()->resolveModUrl(m_referenceMap[current_include]);
                qInfo() << "Include " << raw_include << " detected as " << current_include << " will be hinted to " << hint;

                // Change the reference and add the hint path
                nd.attributes().namedItem("Include").toAttr().setValue(current_include);

                QDomElement hint_element = nd.firstChildElement("HintPath");

                if(hint_element.isNull())
                {
                    hint_element = doc.createElement("HintPath");
                    nd.appendChild(hint_element);

                    qDebug() << "Created a new HintPath element for this";
                }

                if(hint_element.hasChildNodes()) // Expect text node here or something is extremely wrong
                {
                    hint_element.firstChild().toText().setNodeValue(hint);
                }
                else
                {
                    QDomText text_element = doc.createTextNode(hint);
                    hint_element.appendChild(text_element);
                }

                qDebug() << "HI " << hint_element.nodeValue();
            }
        }
    }

    file.resize(0);
    QTextStream stream(&file);
    doc.save(stream, 4);

    qInfo() << "INFO Finished.";
}
