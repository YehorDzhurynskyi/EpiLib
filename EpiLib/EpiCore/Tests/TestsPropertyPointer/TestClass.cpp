EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClass.h"
#include "TestsPropertyPointer/TestClass.cxx"
EPI_GENREGION_END(include)

namespace
{

using namespace epi;

epiChar V0{};
epiWChar V1{};
epiBool V2{};
epiByte V3{};
epiFloat V4{};
epiDouble V5{};
epiSize_t V6{};
epiU8 V7{};
epiU16 V8{};
epiU32 V9{};
epiU64 V10{};
epiS8 V11{};
epiS16 V12{};
epiS32 V13{};
epiS64 V14{};
epiString V15(epiDEBUG_ONLY("Empty"));
epiWString V16(epiDEBUG_ONLY(L"Empty"));
epiArray<epiS32> V17{};
epiPtrArray<epiS32> V18{};
epiArray<epiString> V19{};
epiPtrArray<epiString> V20{};
epiVec2f V21{};
epiVec2d V22{};
epiVec2s V23{};
epiVec2u V24{};
epiVec3f V25{};
epiVec3d V26{};
epiVec3s V27{};
epiVec3u V28{};
epiVec4f V29{};
epiVec4d V30{};
epiVec4s V31{};
epiVec4u V32{};
epiMat2x2f V33{};
epiMat3x3f V34{};
epiMat4x4f V35{};
epiComplexf V36{};
epiComplexd V37{};
epiRect2f V38{};
epiRect2d V39{};
epiRect2s V40{};
epiRect2u V41{};
InplaceClass V42{};
InplaceClass* V43{};

epiChar R0{};
epiWChar R1{};
epiBool R2{};
epiByte R3{};
epiFloat R4{};
epiDouble R5{};
epiSize_t R6{};
epiU8 R7{};
epiU16 R8{};
epiU32 R9{};
epiU64 R10{};
epiS8 R11{};
epiS16 R12{};
epiS32 R13{};
epiS64 R14{};
epiString R15(epiDEBUG_ONLY("Empty"));
epiWString R16(epiDEBUG_ONLY(L"Empty"));
epiArray<epiS32> R17{};
epiPtrArray<epiS32> R18{};
epiArray<epiString> R19{};
epiPtrArray<epiString> R20{};
epiVec2f R21{};
epiVec2d R22{};
epiVec2s R23{};
epiVec2u R24{};
epiVec3f R25{};
epiVec3d R26{};
epiVec3s R27{};
epiVec3u R28{};
epiVec4f R29{};
epiVec4d R30{};
epiVec4s R31{};
epiVec4u R32{};
epiMat2x2f R33{};
epiMat3x3f R34{};
epiMat4x4f R35{};
epiComplexf R36{};
epiComplexd R37{};
epiRect2f R38{};
epiRect2d R39{};
epiRect2s R40{};
epiRect2u R41{};
InplaceClass R42{};
InplaceClass* R43{};

}

#define EmitGetter(t, name, p, n) \
t TestClassA::GetAPrty##name##n##_Callback() const \
{ \
    static_assert(std::is_same_v<std::decay_t<decltype(p##n)>, std::decay_t<t>>); \
    return p##n; \
} \

#define EmitSetter(t, name, p, n) \
void TestClassA::SetAPrty##name##n##_Callback(t value) \
{ \
    static_assert(std::is_same_v<std::decay_t<decltype(p##n)>, std::decay_t<t>>); \
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
EmitGetterSetter(const epiArray<epiString>&, Virtual, V, 19)
EmitGetterSetter(const epiPtrArray<epiString>&, Virtual, V, 20)
EmitGetterSetter(const epiVec2f&, Virtual, V, 21)
EmitGetterSetter(const epiVec2d&, Virtual, V, 22)
EmitGetterSetter(const epiVec2s&, Virtual, V, 23)
EmitGetterSetter(const epiVec2u&, Virtual, V, 24)
EmitGetterSetter(const epiVec3f&, Virtual, V, 25)
EmitGetterSetter(const epiVec3d&, Virtual, V, 26)
EmitGetterSetter(const epiVec3s&, Virtual, V, 27)
EmitGetterSetter(const epiVec3u&, Virtual, V, 28)
EmitGetterSetter(const epiVec4f&, Virtual, V, 29)
EmitGetterSetter(const epiVec4d&, Virtual, V, 30)
EmitGetterSetter(const epiVec4s&, Virtual, V, 31)
EmitGetterSetter(const epiVec4u&, Virtual, V, 32)
EmitGetterSetter(const epiMat2x2f&, Virtual, V, 33)
EmitGetterSetter(const epiMat3x3f&, Virtual, V, 34)
EmitGetterSetter(const epiMat4x4f&, Virtual, V, 35)
EmitGetterSetter(const epiComplexf&, Virtual, V, 36)
EmitGetterSetter(const epiComplexd&, Virtual, V, 37)
EmitGetterSetter(const epiRect2f&, Virtual, V, 38)
EmitGetterSetter(const epiRect2d&, Virtual, V, 39)
EmitGetterSetter(const epiRect2s&, Virtual, V, 40)
EmitGetterSetter(const epiRect2u&, Virtual, V, 41)
EmitGetterSetter(const InplaceClass&, Virtual, V, 42)

const InplaceClass* TestClassA::GetAPrtyVirtual43_Callback() const
{
    return V43;
}

EmitSetter(InplaceClass*, Virtual, V, 43)

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
EmitGetter(const epiArray<epiString>&, ReadCallback, R, 19)
EmitGetter(const epiPtrArray<epiString>&, ReadCallback, R, 20)
EmitGetter(const epiVec2f&, ReadCallback, R, 21)
EmitGetter(const epiVec2d&, ReadCallback, R, 22)
EmitGetter(const epiVec2s&, ReadCallback, R, 23)
EmitGetter(const epiVec2u&, ReadCallback, R, 24)
EmitGetter(const epiVec3f&, ReadCallback, R, 25)
EmitGetter(const epiVec3d&, ReadCallback, R, 26)
EmitGetter(const epiVec3s&, ReadCallback, R, 27)
EmitGetter(const epiVec3u&, ReadCallback, R, 28)
EmitGetter(const epiVec4f&, ReadCallback, R, 29)
EmitGetter(const epiVec4d&, ReadCallback, R, 30)
EmitGetter(const epiVec4s&, ReadCallback, R, 31)
EmitGetter(const epiVec4u&, ReadCallback, R, 32)
EmitGetter(const epiMat2x2f&, ReadCallback, R, 33)
EmitGetter(const epiMat3x3f&, ReadCallback, R, 34)
EmitGetter(const epiMat4x4f&, ReadCallback, R, 35)
EmitGetter(const epiComplexf&, ReadCallback, R, 36)
EmitGetter(const epiComplexd&, ReadCallback, R, 37)
EmitGetter(const epiRect2f&, ReadCallback, R, 38)
EmitGetter(const epiRect2d&, ReadCallback, R, 39)
EmitGetter(const epiRect2s&, ReadCallback, R, 40)
EmitGetter(const epiRect2u&, ReadCallback, R, 41)
EmitGetter(const InplaceClass&, ReadCallback, R, 42)

const InplaceClass* TestClassA::GetAPrtyReadCallback43_Callback() const
{
    return R43;
}

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
EmitSetter(const epiArray<epiString>&, WriteCallback, V, 19)
EmitSetter(const epiPtrArray<epiString>&, WriteCallback, V, 20)
EmitSetter(const epiVec2f&, WriteCallback, V, 21)
EmitSetter(const epiVec2d&, WriteCallback, V, 22)
EmitSetter(const epiVec2s&, WriteCallback, V, 23)
EmitSetter(const epiVec2u&, WriteCallback, V, 24)
EmitSetter(const epiVec3f&, WriteCallback, V, 25)
EmitSetter(const epiVec3d&, WriteCallback, V, 26)
EmitSetter(const epiVec3s&, WriteCallback, V, 27)
EmitSetter(const epiVec3u&, WriteCallback, V, 28)
EmitSetter(const epiVec4f&, WriteCallback, V, 29)
EmitSetter(const epiVec4d&, WriteCallback, V, 30)
EmitSetter(const epiVec4s&, WriteCallback, V, 31)
EmitSetter(const epiVec4u&, WriteCallback, V, 32)
EmitSetter(const epiMat2x2f&, WriteCallback, V, 33)
EmitSetter(const epiMat3x3f&, WriteCallback, V, 34)
EmitSetter(const epiMat4x4f&, WriteCallback, V, 35)
EmitSetter(const epiComplexf&, WriteCallback, V, 36)
EmitSetter(const epiComplexd&, WriteCallback, V, 37)
EmitSetter(const epiRect2f&, WriteCallback, V, 38)
EmitSetter(const epiRect2d&, WriteCallback, V, 39)
EmitSetter(const epiRect2s&, WriteCallback, V, 40)
EmitSetter(const epiRect2u&, WriteCallback, V, 41)
EmitSetter(const InplaceClass&, WriteCallback, V, 42)
EmitSetter(InplaceClass*, WriteCallback, V, 43)

EPI_NAMESPACE_END()
