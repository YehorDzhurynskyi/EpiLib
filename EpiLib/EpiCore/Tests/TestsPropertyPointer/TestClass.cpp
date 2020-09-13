EPI_GENREGION_BEGIN(include)
#include "TestsPropertyPointer/TestClass.h"
#include "TestsPropertyPointer/TestClass.cxx"
EPI_GENREGION_END(include)

#define EmitGlobals(p) \
    thread_local epiChar p##0{}; \
    thread_local epiWChar p##1{}; \
    thread_local epiBool p##2{}; \
    thread_local epiByte p##3{}; \
    thread_local epiFloat p##4{}; \
    thread_local epiDouble p##5{}; \
    thread_local epiSize_t p##6{}; \
    thread_local epiU8 p##7{}; \
    thread_local epiU16 p##8{}; \
    thread_local epiU32 p##9{}; \
    thread_local epiU64 p##10{}; \
    thread_local epiS8 p##11{}; \
    thread_local epiS16 p##12{}; \
    thread_local epiS32 p##13{}; \
    thread_local epiS64 p##14{}; \
    thread_local epiString p##15{epiDEBUG_ONLY("Empty")}; \
    thread_local epiWString p##16{epiDEBUG_ONLY(L"Empty")}; \
    thread_local epiArray<epiS32> p##17{}; \
    thread_local epiPtrArray<epiS32> p##18{}; \
    thread_local epiArray<epiString> p##19{}; \
    thread_local epiPtrArray<epiString> p##20{}; \
    thread_local epiVec2f p##21{}; \
    thread_local epiVec2d p##22{}; \
    thread_local epiVec2s p##23{}; \
    thread_local epiVec2u p##24{}; \
    thread_local epiVec3f p##25{}; \
    thread_local epiVec3d p##26{}; \
    thread_local epiVec3s p##27{}; \
    thread_local epiVec3u p##28{}; \
    thread_local epiVec4f p##29{}; \
    thread_local epiVec4d p##30{}; \
    thread_local epiVec4s p##31{}; \
    thread_local epiVec4u p##32{}; \
    thread_local epiMat2x2f p##33{}; \
    thread_local epiMat3x3f p##34{}; \
    thread_local epiMat4x4f p##35{}; \
    thread_local epiComplexf p##36{}; \
    thread_local epiComplexd p##37{}; \
    thread_local epiRect2f p##38{}; \
    thread_local epiRect2d p##39{}; \
    thread_local epiRect2s p##40{}; \
    thread_local epiRect2u p##41{}; \
    thread_local InplaceClass p##42{}; \
    thread_local InplaceClass* p##43{}; \


#define EmitReset(p) \
    p##0 = {}; \
    p##1 = {}; \
    p##2 = {}; \
    p##3 = {}; \
    p##4 = {}; \
    p##5 = {}; \
    p##6 = {}; \
    p##7 = {}; \
    p##8 = {}; \
    p##9 = {}; \
    p##10 = {}; \
    p##11 = {}; \
    p##12 = {}; \
    p##13 = {}; \
    p##14 = {}; \
    p##15 = {epiDEBUG_ONLY("Empty")}; \
    p##16 = {epiDEBUG_ONLY(L"Empty")}; \
    p##17 = {}; \
    p##18 = {}; \
    p##19 = {}; \
    p##20 = {}; \
    p##21 = {}; \
    p##22 = {}; \
    p##23 = {}; \
    p##24 = {}; \
    p##25 = {}; \
    p##26 = {}; \
    p##27 = {}; \
    p##28 = {}; \
    p##29 = {}; \
    p##30 = {}; \
    p##31 = {}; \
    p##32 = {}; \
    p##33 = {}; \
    p##34 = {}; \
    p##35 = {}; \
    p##36 = {}; \
    p##37 = {}; \
    p##38 = {}; \
    p##39 = {}; \
    p##40 = {}; \
    p##41 = {}; \
    p##42 = {}; \
    p##43 = {}; \

namespace
{

EPI_NAMESPACE_USING()

EmitGlobals(AV)
EmitGlobals(AR)
EmitGlobals(BV)
EmitGlobals(BR)
EmitGlobals(CV)
EmitGlobals(CR)
EmitGlobals(BBV)
EmitGlobals(BBR)
EmitGlobals(CCV)
EmitGlobals(CCR)

}

#define EmitGetter(t, name, p, n, b) \
t TestClass##b::Get##b##Prty##name##n##_Callback() const \
{ \
    static_assert(std::is_same_v<std::decay_t<decltype(p##n)>, std::decay_t<t>>); \
    return p##n; \
} \

#define EmitSetter(t, name, p, n, b) \
void TestClass##b::Set##b##Prty##name##n##_Callback(t value) \
{ \
    static_assert(std::is_same_v<std::decay_t<decltype(p##n)>, std::decay_t<t>>); \
    p##n = value; \
} \

#define EmitGetterSetter(t, name, p, n, b) \
    EmitGetter(t, name, p, n, b) \
    EmitSetter(t, name, p, n, b) \

#define EmitCallbacks(b) \
EmitGetterSetter(epiChar, Virtual, b##V, 0, b) \
EmitGetterSetter(epiWChar, Virtual, b##V, 1, b) \
EmitGetterSetter(epiBool, Virtual, b##V, 2, b) \
EmitGetterSetter(epiByte, Virtual, b##V, 3, b) \
EmitGetterSetter(epiFloat, Virtual, b##V, 4, b) \
EmitGetterSetter(epiDouble, Virtual, b##V, 5, b) \
EmitGetterSetter(epiSize_t, Virtual, b##V, 6, b) \
EmitGetterSetter(epiU8, Virtual, b##V, 7, b) \
EmitGetterSetter(epiU16, Virtual, b##V, 8, b) \
EmitGetterSetter(epiU32, Virtual, b##V, 9, b) \
EmitGetterSetter(epiU64, Virtual, b##V, 10, b) \
EmitGetterSetter(epiS8, Virtual, b##V, 11, b) \
EmitGetterSetter(epiS16, Virtual, b##V, 12, b) \
EmitGetterSetter(epiS32, Virtual, b##V, 13, b) \
EmitGetterSetter(epiS64, Virtual, b##V, 14, b) \
EmitGetterSetter(const epiString&, Virtual, b##V, 15, b) \
EmitGetterSetter(const epiWString&, Virtual, b##V, 16, b) \
EmitGetterSetter(const epiArray<epiS32>&, Virtual, b##V, 17, b) \
EmitGetterSetter(const epiPtrArray<epiS32>&, Virtual, b##V, 18, b) \
EmitGetterSetter(const epiArray<epiString>&, Virtual, b##V, 19, b) \
EmitGetterSetter(const epiPtrArray<epiString>&, Virtual, b##V, 20, b) \
EmitGetterSetter(const epiVec2f&, Virtual, b##V, 21, b) \
EmitGetterSetter(const epiVec2d&, Virtual, b##V, 22, b) \
EmitGetterSetter(const epiVec2s&, Virtual, b##V, 23, b) \
EmitGetterSetter(const epiVec2u&, Virtual, b##V, 24, b) \
EmitGetterSetter(const epiVec3f&, Virtual, b##V, 25, b) \
EmitGetterSetter(const epiVec3d&, Virtual, b##V, 26, b) \
EmitGetterSetter(const epiVec3s&, Virtual, b##V, 27, b) \
EmitGetterSetter(const epiVec3u&, Virtual, b##V, 28, b) \
EmitGetterSetter(const epiVec4f&, Virtual, b##V, 29, b) \
EmitGetterSetter(const epiVec4d&, Virtual, b##V, 30, b) \
EmitGetterSetter(const epiVec4s&, Virtual, b##V, 31, b) \
EmitGetterSetter(const epiVec4u&, Virtual, b##V, 32, b) \
EmitGetterSetter(const epiMat2x2f&, Virtual, b##V, 33, b) \
EmitGetterSetter(const epiMat3x3f&, Virtual, b##V, 34, b) \
EmitGetterSetter(const epiMat4x4f&, Virtual, b##V, 35, b) \
EmitGetterSetter(const epiComplexf&, Virtual, b##V, 36, b) \
EmitGetterSetter(const epiComplexd&, Virtual, b##V, 37, b) \
EmitGetterSetter(const epiRect2f&, Virtual, b##V, 38, b) \
EmitGetterSetter(const epiRect2d&, Virtual, b##V, 39, b) \
EmitGetterSetter(const epiRect2s&, Virtual, b##V, 40, b) \
EmitGetterSetter(const epiRect2u&, Virtual, b##V, 41, b) \
EmitGetterSetter(const InplaceClass&, Virtual, b##V, 42, b) \
 \
const InplaceClass* TestClass##b::Get##b##PrtyVirtual43_Callback() const \
{ \
    return b##V43; \
} \
 \
EmitSetter(InplaceClass*, Virtual, b##V, 43, b) \
 \
EmitGetter(epiChar, ReadCallback, b##R, 0, b) \
EmitGetter(epiWChar, ReadCallback, b##R, 1, b) \
EmitGetter(epiBool, ReadCallback, b##R, 2, b) \
EmitGetter(epiByte, ReadCallback, b##R, 3, b) \
EmitGetter(epiFloat, ReadCallback, b##R, 4, b) \
EmitGetter(epiDouble, ReadCallback, b##R, 5, b) \
EmitGetter(epiSize_t, ReadCallback, b##R, 6, b) \
EmitGetter(epiU8, ReadCallback, b##R, 7, b) \
EmitGetter(epiU16, ReadCallback, b##R, 8, b) \
EmitGetter(epiU32, ReadCallback, b##R, 9, b) \
EmitGetter(epiU64, ReadCallback, b##R, 10, b) \
EmitGetter(epiS8, ReadCallback, b##R, 11, b) \
EmitGetter(epiS16, ReadCallback, b##R, 12, b) \
EmitGetter(epiS32, ReadCallback, b##R, 13, b) \
EmitGetter(epiS64, ReadCallback, b##R, 14, b) \
EmitGetter(const epiString&, ReadCallback, b##R, 15, b) \
EmitGetter(const epiWString&, ReadCallback, b##R, 16, b) \
EmitGetter(const epiArray<epiS32>&, ReadCallback, b##R, 17, b) \
EmitGetter(const epiPtrArray<epiS32>&, ReadCallback, b##R, 18, b) \
EmitGetter(const epiArray<epiString>&, ReadCallback, b##R, 19, b) \
EmitGetter(const epiPtrArray<epiString>&, ReadCallback, b##R, 20, b) \
EmitGetter(const epiVec2f&, ReadCallback, b##R, 21, b) \
EmitGetter(const epiVec2d&, ReadCallback, b##R, 22, b) \
EmitGetter(const epiVec2s&, ReadCallback, b##R, 23, b) \
EmitGetter(const epiVec2u&, ReadCallback, b##R, 24, b) \
EmitGetter(const epiVec3f&, ReadCallback, b##R, 25, b) \
EmitGetter(const epiVec3d&, ReadCallback, b##R, 26, b) \
EmitGetter(const epiVec3s&, ReadCallback, b##R, 27, b) \
EmitGetter(const epiVec3u&, ReadCallback, b##R, 28, b) \
EmitGetter(const epiVec4f&, ReadCallback, b##R, 29, b) \
EmitGetter(const epiVec4d&, ReadCallback, b##R, 30, b) \
EmitGetter(const epiVec4s&, ReadCallback, b##R, 31, b) \
EmitGetter(const epiVec4u&, ReadCallback, b##R, 32, b) \
EmitGetter(const epiMat2x2f&, ReadCallback, b##R, 33, b) \
EmitGetter(const epiMat3x3f&, ReadCallback, b##R, 34, b) \
EmitGetter(const epiMat4x4f&, ReadCallback, b##R, 35, b) \
EmitGetter(const epiComplexf&, ReadCallback, b##R, 36, b) \
EmitGetter(const epiComplexd&, ReadCallback, b##R, 37, b) \
EmitGetter(const epiRect2f&, ReadCallback, b##R, 38, b) \
EmitGetter(const epiRect2d&, ReadCallback, b##R, 39, b) \
EmitGetter(const epiRect2s&, ReadCallback, b##R, 40, b) \
EmitGetter(const epiRect2u&, ReadCallback, b##R, 41, b) \
EmitGetter(const InplaceClass&, ReadCallback, b##R, 42, b) \
 \
const InplaceClass* TestClass##b::Get##b##PrtyReadCallback43_Callback() const \
{ \
    return b##R43; \
} \
 \
EmitSetter(epiChar, WriteCallback, b##V, 0, b) \
EmitSetter(epiWChar, WriteCallback, b##V, 1, b) \
EmitSetter(epiBool, WriteCallback, b##V, 2, b) \
EmitSetter(epiByte, WriteCallback, b##V, 3, b) \
EmitSetter(epiFloat, WriteCallback, b##V, 4, b) \
EmitSetter(epiDouble, WriteCallback, b##V, 5, b) \
EmitSetter(epiSize_t, WriteCallback, b##V, 6, b) \
EmitSetter(epiU8, WriteCallback, b##V, 7, b) \
EmitSetter(epiU16, WriteCallback, b##V, 8, b) \
EmitSetter(epiU32, WriteCallback, b##V, 9, b) \
EmitSetter(epiU64, WriteCallback, b##V, 10, b) \
EmitSetter(epiS8, WriteCallback, b##V, 11, b) \
EmitSetter(epiS16, WriteCallback, b##V, 12, b) \
EmitSetter(epiS32, WriteCallback, b##V, 13, b) \
EmitSetter(epiS64, WriteCallback, b##V, 14, b) \
EmitSetter(const epiString&, WriteCallback, b##V, 15, b) \
EmitSetter(const epiWString&, WriteCallback, b##V, 16, b) \
EmitSetter(const epiArray<epiS32>&, WriteCallback, b##V, 17, b) \
EmitSetter(const epiPtrArray<epiS32>&, WriteCallback, b##V, 18, b) \
EmitSetter(const epiArray<epiString>&, WriteCallback, b##V, 19, b) \
EmitSetter(const epiPtrArray<epiString>&, WriteCallback, b##V, 20, b) \
EmitSetter(const epiVec2f&, WriteCallback, b##V, 21, b) \
EmitSetter(const epiVec2d&, WriteCallback, b##V, 22, b) \
EmitSetter(const epiVec2s&, WriteCallback, b##V, 23, b) \
EmitSetter(const epiVec2u&, WriteCallback, b##V, 24, b) \
EmitSetter(const epiVec3f&, WriteCallback, b##V, 25, b) \
EmitSetter(const epiVec3d&, WriteCallback, b##V, 26, b) \
EmitSetter(const epiVec3s&, WriteCallback, b##V, 27, b) \
EmitSetter(const epiVec3u&, WriteCallback, b##V, 28, b) \
EmitSetter(const epiVec4f&, WriteCallback, b##V, 29, b) \
EmitSetter(const epiVec4d&, WriteCallback, b##V, 30, b) \
EmitSetter(const epiVec4s&, WriteCallback, b##V, 31, b) \
EmitSetter(const epiVec4u&, WriteCallback, b##V, 32, b) \
EmitSetter(const epiMat2x2f&, WriteCallback, b##V, 33, b) \
EmitSetter(const epiMat3x3f&, WriteCallback, b##V, 34, b) \
EmitSetter(const epiMat4x4f&, WriteCallback, b##V, 35, b) \
EmitSetter(const epiComplexf&, WriteCallback, b##V, 36, b) \
EmitSetter(const epiComplexd&, WriteCallback, b##V, 37, b) \
EmitSetter(const epiRect2f&, WriteCallback, b##V, 38, b) \
EmitSetter(const epiRect2d&, WriteCallback, b##V, 39, b) \
EmitSetter(const epiRect2s&, WriteCallback, b##V, 40, b) \
EmitSetter(const epiRect2u&, WriteCallback, b##V, 41, b) \
EmitSetter(const InplaceClass&, WriteCallback, b##V, 42, b) \
EmitSetter(InplaceClass*, WriteCallback, b##V, 43, b) \

EPI_NAMESPACE_BEGIN()

EmitCallbacks(A)
EmitCallbacks(B)
EmitCallbacks(C)
EmitCallbacks(BB)
EmitCallbacks(CC)

void TestClassA::Reset()
{
    EmitReset(AV)
    EmitReset(AR)
}

void TestClassB::Reset()
{
    super::Reset();

    EmitReset(BV)
    EmitReset(BR)
}

void TestClassC::Reset()
{
    super::Reset();

    EmitReset(CV)
    EmitReset(CR)
}

void TestClassBB::Reset()
{
    super::Reset();

    EmitReset(BBV)
    EmitReset(BBR)
}

void TestClassCC::Reset()
{
    super::Reset();

    EmitReset(CCV)
    EmitReset(CCR)
}

EPI_NAMESPACE_END()
