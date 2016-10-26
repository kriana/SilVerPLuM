#ifndef IMAGEMERGEPIPELINE_H
#define IMAGEMERGEPIPELINE_H

#include "modification.h"
#include "launcherexecutable.h"
#include "platform.h"
#include <QProcessEnvironment>
#include "pipeline.h"

class ImageMergePipeline : public Pipeline
{
public:
    ~ImageMergePipeline();

    static ImageMergePipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual QString pipelineType() const;

    void install();

private:

    ImageMergePipeline(Modification * mod, const QString &id);

    bool merge(const QString & xnb_file, const QString & png_file, const QDir &tmpdir);

    bool extract(const QString & xnb_file, const QString & destination);

    bool pack(const QString & png_file, const QString & xnb_file);

    bool apply(const QString & imagefile, const QString & filterimagefile);
};

#endif // IMAGEMERGEPIPELINE_H
