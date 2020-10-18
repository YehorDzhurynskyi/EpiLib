#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiBlueprint/Node/bpNodeImageProvider.hxx"
EPI_GENREGION_END(include)

#include "EpiBlueprint/Node/bpNodeBase.h"

#include "EpiMultimedia/Image/Provider/mmImageProviderBase.h"

EPI_NAMESPACE_BEGIN()

class bpNodeImageProvider : public bpNodeBase
{
EPI_GENREGION_BEGIN(bpNodeImageProvider)

EPI_GENHIDDEN_bpNodeImageProvider()

public:
    constexpr static epiMetaTypeID TypeID{0x514ddded};

    enum bpNodeImageProvider_PIDs
    {
        PID_ImageProvider = 0x3994ec9e,
        PID_COUNT = 1
    };

protected:
    mmImageProviderBase* m_ImageProvider{nullptr};

EPI_GENREGION_END(bpNodeImageProvider)
};

EPI_NAMESPACE_END()
