EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClassA.h"
#include "TestsPropertyPointer/TestClassA.cxx"
EPI_GENREGION_END(include)

namespace
{
epiChar V0;
epiWChar V1;
epiBool V2;
epiByte V3;
epiFloat V4;
epiDouble V5;
epiSize_t V6;
epiU8 V7;
epiU16 V8;
epiU32 V9;
epiU64 V10;
epiS8 V11;
epiS16 V12;
epiS32 V13;
epiS64 V14;
epiString V15;
epiWString V16;
}

#define EmitGetter(t, name, n) \
t TestClassA::GetAPrty##name##n##_Callback() const \
{ \
    static_assert(std::is_same_v<decltype(V##n), std::decay_t<t>>); \
    return V##n; \
} \

#define EmitSetter(t, name, n) \
void TestClassA::SetAPrty##name##n##_Callback(t value) \
{ \
    static_assert(std::is_same_v<decltype(V##n), std::decay_t<t>>); \
    V##n = value; \
} \

#define EmitGetterSetter(t, name, n) \
    EmitGetter(t, name, n) \
    EmitSetter(t, name, n) \

EPI_NAMESPACE_BEGIN()

EmitGetterSetter(epiChar, Virtual, 0)
EmitGetterSetter(epiWChar, Virtual, 1)
EmitGetterSetter(epiBool, Virtual, 2)
EmitGetterSetter(epiByte, Virtual, 3)
EmitGetterSetter(epiFloat, Virtual, 4)
EmitGetterSetter(epiDouble, Virtual, 5)
EmitGetterSetter(epiSize_t, Virtual, 6)
EmitGetterSetter(epiU8, Virtual, 7)
EmitGetterSetter(epiU16, Virtual, 8)
EmitGetterSetter(epiU32, Virtual, 9)
EmitGetterSetter(epiU64, Virtual, 10)
EmitGetterSetter(epiS8, Virtual, 11)
EmitGetterSetter(epiS16, Virtual, 12)
EmitGetterSetter(epiS32, Virtual, 13)
EmitGetterSetter(epiS64, Virtual, 14)
EmitGetterSetter(const epiString&, Virtual, 15)
EmitGetterSetter(const epiWString&, Virtual, 16)
EmitGetter(epiChar, ReadCallback, 0)
EmitGetter(epiWChar, ReadCallback, 1)
EmitGetter(epiBool, ReadCallback, 2)
EmitGetter(epiByte, ReadCallback, 3)
EmitGetter(epiFloat, ReadCallback, 4)
EmitGetter(epiDouble, ReadCallback, 5)
EmitGetter(epiSize_t, ReadCallback, 6)
EmitGetter(epiU8, ReadCallback, 7)
EmitGetter(epiU16, ReadCallback, 8)
EmitGetter(epiU32, ReadCallback, 9)
EmitGetter(epiU64, ReadCallback, 10)
EmitGetter(epiS8, ReadCallback, 11)
EmitGetter(epiS16, ReadCallback, 12)
EmitGetter(epiS32, ReadCallback, 13)
EmitGetter(epiS64, ReadCallback, 14)
EmitGetter(const epiString&, ReadCallback, 15)
EmitGetter(const epiWString&, ReadCallback, 16)
EmitSetter(epiChar, WriteCallback, 0)
EmitSetter(epiWChar, WriteCallback, 1)
EmitSetter(epiBool, WriteCallback, 2)
EmitSetter(epiByte, WriteCallback, 3)
EmitSetter(epiFloat, WriteCallback, 4)
EmitSetter(epiDouble, WriteCallback, 5)
EmitSetter(epiSize_t, WriteCallback, 6)
EmitSetter(epiU8, WriteCallback, 7)
EmitSetter(epiU16, WriteCallback, 8)
EmitSetter(epiU32, WriteCallback, 9)
EmitSetter(epiU64, WriteCallback, 10)
EmitSetter(epiS8, WriteCallback, 11)
EmitSetter(epiS16, WriteCallback, 12)
EmitSetter(epiS32, WriteCallback, 13)
EmitSetter(epiS64, WriteCallback, 14)
EmitSetter(const epiString&, WriteCallback, 15)
EmitSetter(const epiWString&, WriteCallback, 16)

EPI_NAMESPACE_END()
