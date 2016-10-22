#include "repositorypipeline.h"
#include "pipeline.h"
#include "platform.h"
#include "launcherexecutable.h"
#include "utils.h"

RepositoryPipeline::RepositoryPipeline(Modification *mod, const QString &id) : Pipeline(mod, id)
{

}

RepositoryPipeline::~RepositoryPipeline()
{

}

RepositoryPipeline *RepositoryPipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    RepositoryPipeline * pip = new RepositoryPipeline(mod, id);

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
    }

    QStringList repos;

    for(QJsonValue val : json["repositories"].toArray())
    {
        repos << val.toString();
    }

    pip->setRepositories(repos);

    return pip;
}

QStringList RepositoryPipeline::repositories()
{
    return m_Repositories;
}

void RepositoryPipeline::setRepositories(const QStringList &Repositories)
{
    m_Repositories = Repositories;
}

QStringList RepositoryPipeline::installedFiles()
{
    return QStringList();
}

void RepositoryPipeline::install()
{

}

void RepositoryPipeline::uninstall()
{

}

Pipeline::PipelineType RepositoryPipeline::pipelineMainType() const
{
    return PipelineType::RepositoryPipeline;
}

bool RepositoryPipeline::alreadyPrimed()
{
    return true;
}

int RepositoryPipeline::prime(bool is_forced)
{
    return 0;
}
