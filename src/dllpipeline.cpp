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
#include "externalprogram.h"

DllPipeline::DllPipeline(Modification *mod, const QString &id) : Pipeline(mod, id)
{
    // Default supported reffix extensions
    m_reffixExtensions << ".csproj" << ".sln" << ".vbproj" << ".targets";

    // Default reference mappings
    setReferenceMapping("MonoGame.Framework", "stardewvalley://MonoGame.Framework.dll");
    setReferenceMapping("StardewValley", "stardewvalley://StardewValley.exe");
    setReferenceMapping("Stardew Valley", "stardewvalley://StardewValley.exe"); // See fixCrazyness!
    setReferenceMapping("xTile", "stardewvalley://xTile.dll");
}

DllPipeline::~DllPipeline()
{

}

DllPipeline *DllPipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    DllPipeline * pip = new DllPipeline(mod, id);

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
    }

    pip->setEnableNugetRestore(json["nuget-restore"].toBool());
    pip->setSourceDirectory(json["sourcedir"].toString());

    QJsonObject reference_map = json["references"].toObject();

    for(QString ref : reference_map.keys())
    {
        pip->setReferenceMapping(ref, reference_map[ref].toString());
    }

    QJsonObject msbuild_args_map = json["build-parameters"].toObject();

    for(QString platform : msbuild_args_map.keys())
    {
        QStringList args;

        for(QJsonValue v : msbuild_args_map[platform].toArray())
        {
            args << v.toString();
        }

        pip->setBuildParameters(platform, args);
    }

    if(json.keys().contains("reffix-extensions"))
    {
        QStringList extensions;

        for(QJsonValue v : json["reffix-extensions"].toArray())
        {
            extensions << v.toString();
        }

        pip->setReffixExtensions(extensions);
    }

    return pip;
}

bool DllPipeline::prime(bool is_forced)
{
    int this_exit = 0;

    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime", "Start priming");

    if(enableNugetRestore())
    {
        downloadNugetIfNotExisting();

        int exit = runNuget();

        if(exit != 0)
        {
            this_exit = -1;
            getLogger().log(Logger::Warning, "pipeline-dll-compile", id(), "prime-nuget", "Nuget returned exit code " + QString::number(exit) + "!");
        }
        else
        {
            getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-nuget", "Nuget operation was successful");
        }
    }

    // First fix crazyness
    mod()->getModManager()->profile()->fixCrazyness();

    // Look for *.csproj files and fix the dependencies
    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "reffix", "Following extensions are supported: " + reffixExtensions().join(", "));
    QStringList projectfiles = utils::findAllFiles(pipelineSourceDir());
    for(QString file : projectfiles)
    {
        if(QFileInfo(file).isFile())
        {
            for(QString ext : m_reffixExtensions)
            {
                if(file.endsWith(ext))
                {
                    fixReferences(file);
                    break;
                }
            }
        }
    }

    {
        int exit = runMSBuild();

        if(exit != 0)
        {
            this_exit = -1;
            getLogger().log(Logger::Warning, "pipeline-dll-compile", id(), "prime-msbuild", "msbuild/xbuild returned exit code " + QString::number(exit) + "!");
        }
        else
        {
            getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-msbuild", "msbuild/xbuild was successful");
        }
    }

    // Restore the original *.csproj files
    {
        for(QString file : projectfiles)
        {
            if(QFileInfo(file).isFile())
            {
                for(QString ext : m_reffixExtensions)
                {
                    if(file.endsWith(ext))
                    {
                        QFile(file + ".reffix").remove();
                        QFile::copy(file, file + ".reffix");
                        QFile(file).remove();
                        QFile::copy(file + ".bak", file);
                        break;
                    }
                }
            }
        }
    }

    if(this_exit == 0)
    {
        getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime", "Priming was successful. Writing PRIME file.");
        writePrimeFile();
    }
    else
    {
        getLogger().log(Logger::Warning, "pipeline-dll-compile", id(), "prime", "Priming was NOT successful!");
        QFile(pipelineBaseDir().absoluteFilePath("PRIME")).remove(); // Remove PRIME
    }

    return this_exit == 0;
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

void DllPipeline::setBuildParameters(const QString &platform, const QStringList &args)
{
    m_buildArguments[platform] = args;
}

void DllPipeline::downloadNugetIfNotExisting()
{
    // Not working.

    /*if(!QFileInfo(GlobalSettings::instance()->getProgramNuget()).exists()
            || QFileInfo(GlobalSettings::instance()->getProgramNuget()).size() == 0)
    {
        mod()->getModManager()->profile()->getLogger().log(Logger::Info, "pipeline-dll-compile", "nuget-restore", "nuget-download", "Nuget doesn't exist. Downloading it now.");

        QNetworkAccessManager netman;
        QNetworkRequest netRequest(QUrl("https://dist.nuget.org/win-x86-commandline/latest/nuget.exe"));

        QNetworkReply * reply = netman.get(netRequest);

        QEventLoop loop;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();

        QDir dstdir = QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
        dstdir.mkpath(".");

        QFile dstfile(dstdir.absoluteFilePath("nuget.exe"));
        dstfile.remove();

        QByteArray data = reply->readAll();
         mod()->getModManager()->profile()->getLogger().log(Logger::Info, "pipeline-dll-compile", "nuget-restore", "nuget-download", "Downloaded " + QString::number(data.length()) + " bytes");

        if(dstfile.open(QFile::WriteOnly))
        {
            dstfile.write(data);
            dstfile.flush();
            dstfile.close();

            GlobalSettings::instance()->setProgramNuget(dstdir.absoluteFilePath("nuget.exe"));
        }

        reply->deleteLater();
    }*/
}

QString DllPipeline::sourceDirectory() const
{
    return m_sourceDirectory;
}

void DllPipeline::setSourceDirectory(const QString &sourceDirectory)
{
    m_sourceDirectory = sourceDirectory;
}

QDir DllPipeline::pipelineSourceDir()
{
    return pipelineBaseDir().absolutePath() + "/" + sourceDirectory();
}

QProcessEnvironment DllPipeline::processEnvironment()
{
    QProcessEnvironment env = Pipeline::processEnvironment();

    // Tell that building is done using Silverplum
    env.insert("MOD_BUILDER", "Silverplum");

    return env;
}

QString DllPipeline::pipelineType() const
{
    return "compile-dll";
}

QStringList DllPipeline::reffixExtensions() const
{
    return m_reffixExtensions;
}

void DllPipeline::setReffixExtensions(const QStringList &reffixExtensions)
{
    m_reffixExtensions = reffixExtensions;
}

bool DllPipeline::alreadyPrimed()
{
    if(!GlobalSettings::instance()->getEnablePrimeCache())
        return false;
    
    QFile lockfile(pipelineBaseDir().absoluteFilePath("PRIME"));
    
    if (!lockfile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&lockfile);
    return stream.readAll() == Platform::getPlatformString() + "_" + (mod()->getModManager()->profile()->StardewValleyTechnologyString());
}

void DllPipeline::writePrimeFile()
{
    if(!GlobalSettings::instance()->getEnablePrimeCache())
        return;

    QFile lockfile(pipelineBaseDir().absoluteFilePath("PRIME"));

    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime", "PRIME info file will be written into " + pipelineBaseDir().absoluteFilePath("PRIME"));

    if (!lockfile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream stream(&lockfile);
    stream << Platform::getPlatformString() << "_" << (mod()->getModManager()->profile()->StardewValleyTechnologyString());
}

int DllPipeline::runNuget()
{
    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-nuget", "Running nuget restore in " + pipelineBaseDir().absolutePath());

    QProcess process;    
    //utils::wrapMonoExecutable(&process, GlobalSettings::instance()->getProgramNuget(), QStringList() << "restore");

    ExternalProgram nuget_program = GlobalSettings::instance()->getExternalProgram("nuget");

    if(nuget_program.isEmpty())
    {
        getLogger().log(Logger::Error, "pipeline-dll-compile", id(), "prime-nuget", "Nuget program is empty!");
        return -1;
    }

    ExternalProgram::tryToInfuse(&process, nuget_program.executablePath(), QStringList() << "restore");
    process.setWorkingDirectory(pipelineSourceDir().absolutePath());
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(utils::joinEnvironments(processEnvironment(), nuget_program.environment()));

    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-nuget", "Running " + process.program() + " " + process.arguments().join(" ") + " in " + process.workingDirectory());
    process.start();
    process.waitForStarted(-1);
    if(process.state() != QProcess::Running)
    {
        getLogger().log(Logger::Error, "pipeline-dll-compile", id(), "prime-nuget", "Failed to start process!");
        return -1;
    }
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-nuget-nuget", output);

    return process.exitCode();
}

int DllPipeline::runMSBuild()
{
    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-msbuild", "Running msbuild/xbuild in " + pipelineSourceDir().absolutePath());

    QStringList args = m_buildArguments[Platform::getPlatformString()];

    //getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-msbuild", "Running " + GlobalSettings::instance()->getProgramMSBuild() + " " + args.join(" "));

    QProcess process;

    ExternalProgram msbuild_program = GlobalSettings::instance()->getExternalProgram("msbuild");

    if(msbuild_program.isEmpty())
    {
        getLogger().log(Logger::Error, "pipeline-dll-compile", id(), "prime-msbuild", "MSBuild/XBuild program is empty!");
        return -1;
    }

    ExternalProgram::tryToInfuse(&process, msbuild_program.executablePath(), args);

    //utils::wrapMonoExecutable(&process, GlobalSettings::instance()->getProgramMSBuild(), args);
    process.setWorkingDirectory(pipelineSourceDir().absolutePath());
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.setProcessEnvironment(utils::joinEnvironments(processEnvironment(), msbuild_program.environment()));

    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-msbuild", "Running " + process.program() + " " + process.arguments().join(" ") + " in " + process.workingDirectory());
    process.start();
    process.waitForStarted(-1);
    if(process.state() != QProcess::Running)
    {
        getLogger().log(Logger::Error, "pipeline-dll-compile", id(), "prime-msbuild", "Failed to start process!");
        return -1;
    }
    process.waitForFinished(-1);

    QString output(process.readAllStandardOutput());
    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-msbuild-msbuild", output);


    return process.exitCode();
}

void DllPipeline::fixReferences(const QString &projectFile)
{
    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-reffix", "Fixing references in " + projectFile);

    QFile(projectFile + ".bak").remove();
    QFile::copy(projectFile, projectFile + ".bak");

    QDomDocument doc;
    QFile file(projectFile);
    if (!file.open(QIODevice::ReadWrite) || !doc.setContent(&file))
    {
        getLogger().log(Logger::Error, "pipeline-dll-compile", id(), "prime-reffix", "Cannot read or parse project file!");
        return;
    }

    // At first, MonoGame to XNA
    // Needs to be separated as it otherwise may skip references
    QDomNodeList reference_list = doc.elementsByTagName("Reference");

    if(GlobalSettings::instance()->getDLLRedirectXNA())
    {
        if(mod()->getModManager()->profile()->StardewValleyTechnology() == Platform::GameTechnologyXNA)
        {
    for(int i = 0; i < reference_list.size(); ++i)
    {
        QDomNode nd = reference_list.at(i);

        if(nd.attributes().contains("Include"))
        {
            QString raw_include = nd.attributes().namedItem("Include").toAttr().value();
            getLogger().log(Logger::Debug, "pipeline-dll-compile", id(), "prime-reffix", "Visiting " + raw_include);

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

                    // We cannot apply translation procedure here. The entry will be deleted and XNA will be added

                    if(current_include.startsWith("MonoGame.Framework"))
                    {
                        getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-reffix", "Detected MonoGame in XNA mode");

                        QDomNode reflist = nd.parentNode();
                        reflist.removeChild(nd);

                        getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-reffix", "Now adding XNA dependencies");

                        addReferenceNode(doc, reflist,
                                         "Microsoft.Xna.Framework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86",
                                         "",
                                         false,
                                         true);
                        addReferenceNode(doc, reflist,
                                         "Microsoft.Xna.Framework.Game, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86",
                                         "",
                                         false,
                                         true);
                        addReferenceNode(doc, reflist,
                                         "Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86",
                                         "",
                                         false,
                                         true);
                        addReferenceNode(doc, reflist,
                                         "Microsoft.Xna.Framework.Xact, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86",
                                         "",
                                         false,
                                         true);
                    }
                }
            }
        }
    }

    // Then fix hint-paths and do XNA -> MonoGame

    reference_list = doc.elementsByTagName("Reference");

    for(int i = 0; i < reference_list.size(); ++i)
    {
        QDomNode nd = reference_list.at(i);

        if(nd.attributes().contains("Include"))
        {
            QString raw_include = nd.attributes().namedItem("Include").toAttr().value();
            getLogger().log(Logger::Debug, "pipeline-dll-compile", id(), "prime-reffix", "Visiting " + raw_include);

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
            if(GlobalSettings::instance()->getDLLRedirectXNA())
            {
                if(mod()->getModManager()->profile()->StardewValleyTechnology() == Platform::GameTechnologyMonoGame)
                {
                    // Translate XNA to MonoGame by issuing a re-map

                    if(current_include.startsWith("Microsoft.Xna.Framework"))
                    {
                        getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-reffix", "Redirecting " + raw_include + " to MonoGame");

                        current_include = "MonoGame.Framework";
                    }
                }
            }

            if(m_referenceMap.contains(current_include))
            {
                QString hint = mod()->getModManager()->resolveModUrl(m_referenceMap[current_include]);
                getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-reffix", "Include " + raw_include + " was detected as " + current_include + " and will be hinted to " + hint);


                // Change the reference and add the hint path
                nd.attributes().namedItem("Include").toAttr().setValue(current_include);

                QDomElement hint_element = nd.firstChildElement("HintPath");

                if(hint_element.isNull())
                {
                    hint_element = doc.createElement("HintPath");
                    nd.appendChild(hint_element);
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

            }
        }
    }

    file.resize(0);
    QTextStream stream(&file);
    doc.save(stream, 4);

    getLogger().log(Logger::Info, "pipeline-dll-compile", id(), "prime-reffix", "Finished");
}

void DllPipeline::addReferenceNode(QDomDocument & doc, QDomNode &parent, const QString &reference, const QString &hintpath, bool isprivate, bool specificversion)
{
    QDomElement ref_element = doc.createElement("Reference");
    ref_element.setAttribute("Include", reference);

    if(!hintpath.isEmpty())
    {
        QDomElement hintpath_element = doc.createElement("HintPath");
        hintpath_element.appendChild(doc.createTextNode(hintpath));

        ref_element.appendChild(hintpath_element);
    }

    QDomElement private_element = doc.createElement("Private");
    private_element.appendChild(doc.createTextNode(isprivate ? "True" : "False"));
    ref_element.appendChild(private_element);

    QDomElement sversion_element = doc.createElement("SpecificVersion");
    sversion_element.appendChild(doc.createTextNode(specificversion ? "True" : "False"));
    ref_element.appendChild(sversion_element);

    parent.appendChild(ref_element);
}
