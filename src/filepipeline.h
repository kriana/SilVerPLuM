#ifndef FILEPIPELINE_H
#define FILEPIPELINE_H

#include "pipeline.h"
#include <QJsonObject>


class FilePipeline : public Pipeline
{
public:    

    ~FilePipeline();

    static FilePipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    int prime();

private:

    FilePipeline(Modification * mod, const QString &id);
};

#endif // FILEPIPELINE_H
