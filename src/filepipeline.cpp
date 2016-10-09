#include "filepipeline.h"
#include "platform.h"
#include <QJsonArray>

int FilePipeline::prime(bool force)
{
    // File mods don't have anything to prime

    return 0;
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

    if(!loadGenericFromJson(json, pip))
    {
        delete pip;
        return nullptr;
    }

    return pip;
}
