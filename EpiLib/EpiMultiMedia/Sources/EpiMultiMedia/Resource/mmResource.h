#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmResource.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiMultimedia/mmMediaBase.h"

EPI_NAMESPACE_BEGIN()

enum class mmResourceStatus : epiS32
{
EPI_GENREGION_BEGIN(mmResourceStatus)
    Empty = 0,
    Broken = 1,
    LoadedShallow = 2,
    LoadedDeep = 3
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
        PID_URL = 0x62d10724,
        PID_Status = 0x7cac602a,
        PID_Media = 0xabed8e08,
        PID_COUNT = 3
    };

protected:
    epiString m_URL{epiDEBUG_ONLY("Empty")};
    mmResourceStatus m_Status{mmResourceStatus::Empty};
    epiPtrArray<mmMediaBase> m_Media{};

EPI_GENREGION_END(mmResource)
};

EPI_NAMESPACE_END()
