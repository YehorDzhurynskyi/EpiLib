#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmJobResourceLoadDeep.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/MT/JobSystem/epiIJob.h"

#include "EpiMultimedia/Resource/mmResource.h"

EPI_NAMESPACE_BEGIN()

class mmJobResourceLoadDeep : public epiIJob
{
EPI_GENREGION_BEGIN(mmJobResourceLoadDeep)

EPI_GENHIDDEN_mmJobResourceLoadDeep()

public:
    constexpr static epiMetaTypeID TypeID{0x9ca4ae9b};

    enum mmJobResourceLoadDeep_PIDs
    {
        PID_Resource = 0x45e79640,
        PID_COUNT = 1
    };

protected:
    mmResource* m_Resource{nullptr};

EPI_GENREGION_END(mmJobResourceLoadDeep)

public:
    mmJobResourceLoadDeep(mmResource& resource);

    void Execute() override;
};

EPI_NAMESPACE_END()
