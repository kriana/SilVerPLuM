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

    /**
     * @brief Default merge algorithm. Overwrites if alpha value is not 0.
     */
    struct MergeAlgorithm
    {
        virtual bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase);
    };

    /**
     * @brief Overwrites image with filter image
     */
    struct OverwriteAlgorithm : public MergeAlgorithm
    {
        virtual bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase);
    };

    /**
     * @brief Does per-channel linear interpolation between destination and filter image based on mask image
     */
    struct MaskMergeAlgorithm : public MergeAlgorithm
    {
        virtual bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase);
    };

    /**
     * @brief Replaces a tile completely if filter image writes into it.
     */
    struct TileMergeAlgorithm : public MergeAlgorithm
    {
        int tilesx = 0;

        int tilesy = 0;

        virtual bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase);
    };

    ~ImageMergePipeline();

    static ImageMergePipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual QString pipelineType() const;

    void install();

    QMap<QString, MergeAlgorithm> mergeAlgorithms() const;

    void setMergeAlgorithms(const QMap<QString, MergeAlgorithm> &mergeAlgorithms);

private:

    QMap<QString, MergeAlgorithm> m_mergeAlgorithms;

    ImageMergePipeline(Modification * mod, const QString &id);

    bool merge(const QString & xnb_file, const QString & png_file, const QDir &tmpdir, MergeAlgorithm alg);

    bool extract(const QString & xnb_file, const QString & destination);

    bool pack(const QString & png_file, const QString & xnb_file);
};

#endif // IMAGEMERGEPIPELINE_H
