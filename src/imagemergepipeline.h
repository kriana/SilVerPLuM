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
     * @brief
     */
    struct MergeAlgorithm
    {
        virtual ~MergeAlgorithm()
        {

        }

        virtual bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase) = 0;
    };

    /**
     * @brief Overwrites if alpha value is not 0.
     */
    struct AlphaThresholdMergeAlgorithm : public MergeAlgorithm
    {
        ~AlphaThresholdMergeAlgorithm()
        {
        }

        bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase) override;
    };

    /**
     * @brief Overwrites image with filter image
     */
    struct OverwriteMergeAlgorithm : public MergeAlgorithm
    {
        ~OverwriteMergeAlgorithm()
        {

        }

        bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase) override;
    };

    /**
     * @brief Does per-channel linear interpolation between destination and filter image based on mask image
     */
    struct MaskMergeAlgorithm : public MergeAlgorithm
    {
        ~MaskMergeAlgorithm()
        {

        }

        bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase) override;
    };

    /**
     * @brief Replaces a tile completely if filter image writes into it.
     */
    struct TileMergeAlgorithm : public MergeAlgorithm
    {
        int tilesx = 0;

        int tilesy = 0;

        ~TileMergeAlgorithm()
        {

        }

        bool apply(Logger &log, const QString & destinationfile, const QString & sourcefilebase) override;
    };

    ~ImageMergePipeline();

    static ImageMergePipeline *loadFromJson(Modification * mod, const QString & id, const QJsonObject & json);

    /**
     * @brief The type of this pipeline
     * @return
     */
    virtual QString pipelineType() const;

    void install();

    QMap<QString, MergeAlgorithm *> mergeAlgorithms() const;

private:

    QMap<QString, MergeAlgorithm *> m_mergeAlgorithms;

    MergeAlgorithm * m_defaultAlgorithm;

    ImageMergePipeline(Modification * mod, const QString &id);

    bool merge(const QString & xnb_file, const QString & png_file, const QDir &tmpdir, MergeAlgorithm *alg);

    bool extract(const QString & xnb_file, const QString & destination);

    bool pack(const QString & png_file, const QString & xnb_file);
};

#endif // IMAGEMERGEPIPELINE_H
