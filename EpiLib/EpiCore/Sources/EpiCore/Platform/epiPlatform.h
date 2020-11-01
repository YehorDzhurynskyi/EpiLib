#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiPlatform.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/Platform/epiDeviceCPUBase.h"
#include "EpiCore/Platform/epiDeviceDisplay.h"

EPI_NAMESPACE_BEGIN()

class epiPlatform : public Object
{
EPI_GENREGION_BEGIN(epiPlatform)

EPI_GENHIDDEN_epiPlatform()

public:
    constexpr static epiMetaTypeID TypeID{0xe98b5405};

    enum epiPlatform_PIDs
    {
        PID_DeviceCPU = 0x5c3392e3,
        PID_DeviceDisplay = 0x5a319652,
        PID_COUNT = 2
    };

protected:
    epiDeviceCPUBase* m_DeviceCPU{nullptr};
    epiDeviceDisplay m_DeviceDisplay{};

EPI_GENREGION_END(epiPlatform)

protected:
    epiPlatform();

public:
    static epiPlatform& GetInstance()
    {
        static epiPlatform instance;
        return instance;
    }
};

EPI_NAMESPACE_END()
