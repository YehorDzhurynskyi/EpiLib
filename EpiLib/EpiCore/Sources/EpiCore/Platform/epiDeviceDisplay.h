#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiDeviceDisplay.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

enum class DPIAwareness : epiS32
{
EPI_GENREGION_BEGIN(DPIAwareness)
    UnAware = 0,
    SystemAware = 1,
    PerMonitorAware = 2
EPI_GENREGION_END(DPIAwareness)
};

class epiDeviceDisplay : public Object
{
EPI_GENREGION_BEGIN(epiDeviceDisplay)

EPI_GENHIDDEN_epiDeviceDisplay()

public:
    constexpr static epiMetaTypeID TypeID{0xde3161d1};

    enum epiDeviceDisplay_PIDs
    {
        PID_DPI = 0x3d69586e,
        PID_DPIAwareness = 0x5fdfa48d,
        PID_COUNT = 2
    };

protected:
    epiVec2u GetDPI_Callback() const;
    void SetDPIAwareness_Callback(DPIAwareness value);

protected:
    DPIAwareness m_DPIAwareness{};

EPI_GENREGION_END(epiDeviceDisplay)
};

EPI_NAMESPACE_END()
