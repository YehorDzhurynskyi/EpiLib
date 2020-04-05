#pragma once

EPI_GENREGION_BEGIN(include)
#include "A.hxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

class DataClass : public Object
{
EPI_GENREGION_BEGIN(DataClass)
public:
    EPI_GENHIDDEN_DataClass()

    constexpr static epiHash_t TypeID{0x48110fc1};

    enum DataClass_PIDs
    {
        PID_x = 0x8cdc1683,
        PID_y = 0xfbdb2615,
        PID_z = 0x62d277af,
        PID_w = 0x1c630b12,
        COUNT = 4
    };

protected:
    epiFloat m_x{0.0f};
    epiFloat m_y{0.0f};
    epiFloat m_z{0.0f};
    epiFloat m_w{0.0f};

EPI_GENREGION_END(DataClass)
};

class AClass : public Object
{
EPI_GENREGION_BEGIN(AClass)
public:
    EPI_GENHIDDEN_AClass()

    constexpr static epiHash_t TypeID{0x9f6eb9ec};

    enum AClass_PIDs
    {
        PID_Prty_1 = 0xedde3f4e,
        PID_Prty_2 = 0x74d76ef4,
        PID_Prty_3 = 0x3d05e62,
        PID_Prty_4 = 0x9db4cbc1,
        PID_Prty_5 = 0xeab3fb57,
        PID_Prty_6 = 0x73baaaed,
        PID_Prty_7 = 0x4bd9a7b,
        PID_Virtual_1 = 0x5c39952b,
        PID_Virtual_2 = 0xc530c491,
        PID_MyArray = 0x3272a160,
        COUNT = 10
    };

protected:
    epiS32 m_Prty_1{0};
    epiBool m_Prty_2{false};
    DataClass m_Prty_3;
    DataClass**** m_Prty_4{nullptr};
    epiString m_Prty_5{"some another text"};
    epiChar m_Prty_6{'@'};
    epiChar m_Prty_7{'\''};
    epiFloat m_Virtual_1{142.0};
    epiS32 m_Virtual_2{-991};
    epiArray<epiFloat> m_MyArray;

EPI_GENREGION_END(AClass)
};

class BClass : public AClass
{
EPI_GENREGION_BEGIN(BClass)
public:
    EPI_GENHIDDEN_BClass()

    constexpr static epiHash_t TypeID{0x19facb42};

    enum BClass_PIDs
    {
        PID_Prty_B = 0x24d21fc8,
        COUNT = 1
    };

protected:
    epiFloat m_Prty_B{-2424.0};

EPI_GENREGION_END(BClass)
};

EPI_NAMESPACE_END()
