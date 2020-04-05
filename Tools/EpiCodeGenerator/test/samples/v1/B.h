#pragma once

EPI_GENREGION_BEGIN(include)
#include "B.hxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

class DClass : public BClass
{
EPI_GENREGION_BEGIN(DClass)
public:
    EPI_GENHIDDEN_DClass()

    constexpr static epiHash_t TypeID{0xcfa3285f};

    enum DClass_PIDs
    {
        PID_HIHI = 0x370f25b8,
        PID_IsA = 0x85c3346e,
        PID_IsB = 0x1cca65d4,
        PID_yArray = 0x3b00cb04,
        COUNT = 4
    };

protected:
    epiU32 m_HIHI{0};
    epiBool m_IsA{false};
    epiBool m_IsB{false};
    epiArray<AClass> m_yArray;

EPI_GENREGION_END(DClass)
};

EPI_NAMESPACE_END()
