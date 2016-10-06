#include "filepipeline.h"
#include "platform.h"
#include <QJsonArray>

void FilePipeline::prime()
{
    // File mods don't have anything to prime
}

FilePipeline::FilePipeline(Modification *mod, const QString & id) : Pipeline(mod, id)
{

}

FilePipeline::~FilePipeline()
{

}

FilePipeline * FilePipeline::loadFromJson(Modification *mod, const QString &id, const QJsonObject &json)
{
    FilePipeline * pip = new FilePipeline(mod, id);

    loadGenericFromJson(json, pip);

    return pip;
}
