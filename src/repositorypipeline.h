#ifndef REPOSITORYPIPELINE_H
#define REPOSITORYPIPELINE_H

#include "modification.h"
#include <QProcessEnvironment>
#include "pipeline.h"


class RepositoryPipeline : public Pipeline
{
public:
    ~RepositoryPipeline();

    static RepositoryPipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    QStringList Repositories() const;

    void setRepositories(const QStringList &Repositories);

    void install();

    void uninstall();

protected:

    int prime(bool is_forced);

    bool alreadyPrimed();

private:

    QStringList m_Repositories;

    RepositoryPipeline(Modification * mod, const QString &id);
};

#endif // REPOSITORYPIPELINE_H
