#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmResource.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum class mmMIMEType
{
EPI_GENREGION_BEGIN(mmMIMEType)
    UNKNOWN = 0,
    AUDIO_MPEG = 1
EPI_GENREGION_END(mmMIMEType)
};

enum class mmResourceStatus
{
EPI_GENREGION_BEGIN(mmResourceStatus)
    Broken = 0,
    LoadedPartially = 1,
    LoadedFully = 2
EPI_GENREGION_END(mmResourceStatus)
};

class mmResource : public Object
{
EPI_GENREGION_BEGIN(mmResource)

EPI_GENHIDDEN_mmResource()

public:
    constexpr static epiMetaTypeID TypeID{0x4a7ac86c};

    enum mmResource_PIDs
    {
        PID_URI = 0x12bbf3ab,
        PID_MIME = 0x74106de4,
        PID_Status = 0x7cac602a,
        PID_COUNT = 3
    };

protected:
    epiString m_URI{epiDEBUG_ONLY("Empty")};
    mmMIMEType m_MIME{mmMIMEType::UNKNOWN};
    mmResourceStatus m_Status{mmResourceStatus::Broken};

EPI_GENREGION_END(mmResource)
};

EPI_NAMESPACE_END()
