#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmJobResourceLoad.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/MT/JobSystem/epiIJob.h"

#include "EpiMultimedia/Resource/mmResource.h"

EPI_NAMESPACE_BEGIN()

class mmJobResourceLoad : public epiIJob
{
EPI_GENREGION_BEGIN(mmJobResourceLoad)

EPI_GENHIDDEN_mmJobResourceLoad()

public:
    constexpr static epiMetaTypeID TypeID{0xa4f59d9};

    enum mmJobResourceLoad_PIDs
    {
        PID_URL = 0x62d10724,
        PID_DeepLoad = 0x14e09a25,
        PID_Resource = 0x45e79640,
        PID_COUNT = 3
    };

protected:
    epiString m_URL{EPI_BUILD_DEBUG_ONLY("Empty")};
    epiBool m_DeepLoad{false};
    mmResource* m_Resource{nullptr};

EPI_GENREGION_END(mmJobResourceLoad)

public:
    mmJobResourceLoad(const epiChar* url, epiBool deepLoad);

    void Execute() override;

    epiString ToString() const override;
};

EPI_NAMESPACE_END()
