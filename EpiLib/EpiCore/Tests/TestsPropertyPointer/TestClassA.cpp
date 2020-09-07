EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClassA.h"
#include "TestsPropertyPointer/TestClassA.cxx"
EPI_GENREGION_END(include)

namespace
{

using namespace epi;

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
epiString V15(epiDEBUG_ONLY("Empty"));
epiWString V16(epiDEBUG_ONLY(L"Empty"));
epiArray<epiS32> V17;
epiPtrArray<epiS32> V18;

epiChar R0;
epiWChar R1;
epiBool R2;
epiByte R3;
epiFloat R4;
epiDouble R5;
epiSize_t R6;
epiU8 R7;
epiU16 R8;
epiU32 R9;
epiU64 R10;
epiS8 R11;
epiS16 R12;
epiS32 R13;
epiS64 R14;
epiString R15(epiDEBUG_ONLY("Empty"));
epiWString R16(epiDEBUG_ONLY(L"Empty"));
epiArray<epiS32> R17;
epiPtrArray<epiS32> R18;

}

#define EmitGetter(t, name, p, n) \
t TestClassA::GetAPrty##name##n##_Callback() const \
{ \
    static_assert(std::is_same_v<decltype(p##n), std::decay_t<t>>); \
    return p##n; \
} \

#define EmitSetter(t, name, p, n) \
void TestClassA::SetAPrty##name##n##_Callback(t value) \
{ \
    static_assert(std::is_same_v<decltype(p##n), std::decay_t<t>>); \
    p##n = value; \
} \

#define EmitGetterSetter(t, name, p, n) \
    EmitGetter(t, name, p, n) \
    EmitSetter(t, name, p, n) \

EPI_NAMESPACE_BEGIN()

EmitGetterSetter(epiChar, Virtual, V, 0)
EmitGetterSetter(epiWChar, Virtual, V, 1)
EmitGetterSetter(epiBool, Virtual, V, 2)
EmitGetterSetter(epiByte, Virtual, V, 3)
EmitGetterSetter(epiFloat, Virtual, V, 4)
EmitGetterSetter(epiDouble, Virtual, V, 5)
EmitGetterSetter(epiSize_t, Virtual, V, 6)
EmitGetterSetter(epiU8, Virtual, V, 7)
EmitGetterSetter(epiU16, Virtual, V, 8)
EmitGetterSetter(epiU32, Virtual, V, 9)
EmitGetterSetter(epiU64, Virtual, V, 10)
EmitGetterSetter(epiS8, Virtual, V, 11)
EmitGetterSetter(epiS16, Virtual, V, 12)
EmitGetterSetter(epiS32, Virtual, V, 13)
EmitGetterSetter(epiS64, Virtual, V, 14)
EmitGetterSetter(const epiString&, Virtual, V, 15)
EmitGetterSetter(const epiWString&, Virtual, V, 16)
EmitGetterSetter(const epiArray<epiS32>&, Virtual, V, 17)
EmitGetterSetter(const epiPtrArray<epiS32>&, Virtual, V, 18)

EmitGetter(epiChar, ReadCallback, R, 0)
EmitGetter(epiWChar, ReadCallback, R, 1)
EmitGetter(epiBool, ReadCallback, R, 2)
EmitGetter(epiByte, ReadCallback, R, 3)
EmitGetter(epiFloat, ReadCallback, R, 4)
EmitGetter(epiDouble, ReadCallback, R, 5)
EmitGetter(epiSize_t, ReadCallback, R, 6)
EmitGetter(epiU8, ReadCallback, R, 7)
EmitGetter(epiU16, ReadCallback, R, 8)
EmitGetter(epiU32, ReadCallback, R, 9)
EmitGetter(epiU64, ReadCallback, R, 10)
EmitGetter(epiS8, ReadCallback, R, 11)
EmitGetter(epiS16, ReadCallback, R, 12)
EmitGetter(epiS32, ReadCallback, R, 13)
EmitGetter(epiS64, ReadCallback, R, 14)
EmitGetter(const epiString&, ReadCallback, R, 15)
EmitGetter(const epiWString&, ReadCallback, R, 16)
EmitGetter(const epiArray<epiS32>&, ReadCallback, R, 17)
EmitGetter(const epiPtrArray<epiS32>&, ReadCallback, R, 18)

EmitSetter(epiChar, WriteCallback, V, 0)
EmitSetter(epiWChar, WriteCallback, V, 1)
EmitSetter(epiBool, WriteCallback, V, 2)
EmitSetter(epiByte, WriteCallback, V, 3)
EmitSetter(epiFloat, WriteCallback, V, 4)
EmitSetter(epiDouble, WriteCallback, V, 5)
EmitSetter(epiSize_t, WriteCallback, V, 6)
EmitSetter(epiU8, WriteCallback, V, 7)
EmitSetter(epiU16, WriteCallback, V, 8)
EmitSetter(epiU32, WriteCallback, V, 9)
EmitSetter(epiU64, WriteCallback, V, 10)
EmitSetter(epiS8, WriteCallback, V, 11)
EmitSetter(epiS16, WriteCallback, V, 12)
EmitSetter(epiS32, WriteCallback, V, 13)
EmitSetter(epiS64, WriteCallback, V, 14)
EmitSetter(const epiString&, WriteCallback, V, 15)
EmitSetter(const epiWString&, WriteCallback, V, 16)
EmitSetter(const epiArray<epiS32>&, WriteCallback, V, 17)
EmitSetter(const epiPtrArray<epiS32>&, WriteCallback, V, 18)

EPI_NAMESPACE_END()
