#include "filepipeline.h"

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

    pip->setName(json["name"].toString());
    pip->setDescription(json["description"].toString());
    pip->setPriority(json["priority"].toInt());
    pip->setDefault(json["default"].toBool());

    QJsonObject installables = json["installables"].toObject();

    for(QString src : installables.keys())
    {
        QString dst = installables[src].toString();

        pip->setInstallable(src, dst);
    }

    return pip;
}
