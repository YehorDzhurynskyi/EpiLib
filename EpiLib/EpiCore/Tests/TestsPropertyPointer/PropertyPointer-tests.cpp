#include <gtest/gtest.h>

#include "EpiCore/ObjectModel/PropertyPointer.h"

#include "TestClassA.h"

#define ASSERT_PP(T, V) \
    if (pp.IsReadable()) \
        ASSERT_EQ(pp.Get<T>(), T{}); \
 \
    if (pp.IsWritable()) \
        pp.Set<T>(V); \
    else \
        break; \
 \
    if (pp.IsReadable()) \
        ASSERT_EQ(pp.Get<T>(), V); \
 \
    break; \

#define ASSERT_PP_COMPOUND_EX(T, V, IV) \
{ \
    T temp(IV); \
 \
    if (pp.IsReadable()) \
        ASSERT_EQ(pp.Get<T>(), temp); \
 \
    temp = V; \
    if (pp.IsWritable()) \
        pp.Set<T>(temp); \
    else \
        break; \
 \
    if (pp.IsReadable()) \
        ASSERT_EQ(pp.Get<T>(), temp); \
 \
    break; \
} \

#define ASSERT_PP_COMPOUND(T, V) ASSERT_PP_COMPOUND_EX(T, V, {})

#define ASSERT_PP_ARRAY(T, V) \
{ \
    if (!pp.IsReadable()) \
        break; \
 \
    T& temp = pp.Get<T>(); \
 \
    ASSERT_EQ(temp, T{}); \
 \
    temp = V; \
    ASSERT_EQ(pp.Get<T>(), V); \
 \
    if (!pp.IsWritable()) \
        break; \
 \
    pp.Set<T>(T{}); \
    ASSERT_EQ(pp.Get<T>(), T{}); \
 \
    break; \
} \

EPI_NAMESPACE_BEGIN()

TEST(PropertyPointer, Base)
{
    TestClassA a;

    const auto* m = &a.GetMetaClass();
    while (m)
    {
        for (const auto& p : m->GetClassData())
        {
            auto pp = PropertyPointer::CreateFromProperty(a, &p);
            ASSERT_EQ(pp.GetTypeID(), p.GetTypeID());

            switch (p.GetTypeID())
            {
            case epiMetaTypeID_epiChar: ASSERT_PP(epiChar, 'K')
            case epiMetaTypeID_epiWChar: ASSERT_PP(epiWChar, L'H')

            case epiMetaTypeID_epiBool: ASSERT_PP(epiBool, true)

            case epiMetaTypeID_epiByte: ASSERT_PP(epiByte, 12)

            case epiMetaTypeID_epiFloat: if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiFloat>(), 0.0f, epiFloatingEqTolerance()); if (pp.IsWritable()) pp.Set<epiFloat>(-125.0f); else break; if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiFloat>(), -125.0f, epiFloatingEqTolerance()); break;
            case epiMetaTypeID_epiDouble: if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiDouble>(), 0.0, epiFloatingEqTolerance()); if (pp.IsWritable()) pp.Set<epiDouble>(-0.035); else break; if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiDouble>(), -0.035, epiFloatingEqTolerance()); break;

            case epiMetaTypeID_epiSize_t: ASSERT_PP(epiSize_t, 550)

            case epiMetaTypeID_epiU8: ASSERT_PP(epiU8, 32)
            case epiMetaTypeID_epiU16: ASSERT_PP(epiU16, 158)
            case epiMetaTypeID_epiU32: ASSERT_PP(epiU32, 2444212)
            case epiMetaTypeID_epiU64: ASSERT_PP(epiU64, 298190129300)
            case epiMetaTypeID_epiS8: ASSERT_PP(epiS8, -16)
            case epiMetaTypeID_epiS16: ASSERT_PP(epiS16, -1241)
            case epiMetaTypeID_epiS32: ASSERT_PP(epiS32, 89537)
            case epiMetaTypeID_epiS64: ASSERT_PP(epiS64, 213125125)

            case epiMetaTypeID_epiString: ASSERT_PP_COMPOUND_EX(epiString, "Test text", epiDEBUG_ONLY("Empty"))
            case epiMetaTypeID_epiWString: ASSERT_PP_COMPOUND_EX(epiWString, L"Test Wtext", epiDEBUG_ONLY(L"Empty"))

            case epiMetaTypeID_epiArray: ASSERT_PP_ARRAY(epiArray<epiS32>, epiArray<epiS32>({ -5, 1, 2, 3, 4, -3 }))
            case epiMetaTypeID_epiPtrArray: ASSERT_PP_ARRAY(epiPtrArray<epiS32>, epiPtrArray<epiS32>({ nullptr, (epiS32*)0xfa7f7af, (epiS32*)0x0000353f }))

            // TODO: handle
            // case epiMetaTypeID_epiArray: ASSERT_EQ(pp.Get<epiArray<epiS32>>(), epiArray<epiS32>{}); pp.Set<epiArray<epiS32>>({ 4, 3, -122, 5 }); ASSERT_EQ(pp.Get<epiArray<epiS32>>(), epiArray<epiS32>({ 4, 3, -122, 5 })); break;
            // case epiMetaTypeID_epiPtrArray: ASSERT_EQ(pp.Get<epiChar>(), '0'); pp.Set<epiChar>('H'); ASSERT_EQ(pp.Get<epiChar>(), 'H'); break;

            // case epiMetaTypeID_epiVec2f: ASSERT_EQ(pp.Get<epiVec2f>(), epiVec2f(0.0f, 0.0f)); pp.Set<epiVec2f>(epiVec2f(21.0f, -0.05f)); ASSERT_EQ(pp.Get<epiVec2f>(), epiVec2f(21.0f, -0.05f)); break;
            // case epiMetaTypeID_epiVec2d: ASSERT_EQ(pp.Get<epiVec2d>(), epiVec2d(0.0, 0.0)); pp.Set<epiVec2d>(epiVec2d(0.0210, -12.05)); ASSERT_EQ(pp.Get<epiVec2d>(), epiVec2d(0.0210, -12.05)); break;
            // case epiMetaTypeID_epiVec2s: ASSERT_EQ(pp.Get<epiVec2s>(), epiVec2s(0, 0)); pp.Set<epiVec2s>(epiVec2s(-3, 12)); ASSERT_EQ(pp.Get<epiVec2s>(), epiVec2s(-3, 12)); break;
            // case epiMetaTypeID_epiVec2u: ASSERT_EQ(pp.Get<epiVec2u>(), epiVec2u(0, 0)); pp.Set<epiVec2u>(epiVec2u(0, 17)); ASSERT_EQ(pp.Get<epiVec2u>(), epiVec2u(0, 17)); break;

            // case epiMetaTypeID_epiVec3f: ASSERT_EQ(pp.Get<epiVec3f>(), '0'); pp.Set<epiVec3f>('H'); ASSERT_EQ(pp.Get<epiVec3f>(), 'H'); break;
            // case epiMetaTypeID_epiVec3d: ASSERT_EQ(pp.Get<epiVec3d>(), '0'); pp.Set<epiVec3d>('H'); ASSERT_EQ(pp.Get<epiVec3d>(), 'H'); break;
            // case epiMetaTypeID_epiVec3s: ASSERT_EQ(pp.Get<epiVec3s>(), '0'); pp.Set<epiVec3s>('H'); ASSERT_EQ(pp.Get<epiVec3s>(), 'H'); break;
            // case epiMetaTypeID_epiVec3u: ASSERT_EQ(pp.Get<epiVec3u>(), '0'); pp.Set<epiVec3u>('H'); ASSERT_EQ(pp.Get<epiVec3u>(), 'H'); break;

            // case epiMetaTypeID_epiVec4f: ASSERT_EQ(pp.Get<epiVec4f>(), '0'); pp.Set<epiVec4f>('H'); ASSERT_EQ(pp.Get<epiVec4f>(), 'H'); break;
            // case epiMetaTypeID_epiVec4d: ASSERT_EQ(pp.Get<epiVec4d>(), '0'); pp.Set<epiVec4d>('H'); ASSERT_EQ(pp.Get<epiVec4d>(), 'H'); break;
            // case epiMetaTypeID_epiVec4s: ASSERT_EQ(pp.Get<epiVec4s>(), '0'); pp.Set<epiVec4s>('H'); ASSERT_EQ(pp.Get<epiVec4s>(), 'H'); break;
            // case epiMetaTypeID_epiVec4u: ASSERT_EQ(pp.Get<epiVec4u>(), '0'); pp.Set<epiVec4u>('H'); ASSERT_EQ(pp.Get<epiVec4u>(), 'H'); break;

            // case epiMetaTypeID_epiMat2x2f: ASSERT_EQ(pp.Get<epiMat2x2f>(), '0'); pp.Set<epiMat2x2f>('H'); ASSERT_EQ(pp.Get<epiMat2x2f>(), 'H'); break;
            // case epiMetaTypeID_epiMat3x3f: ASSERT_EQ(pp.Get<epiMat3x3f>(), '0'); pp.Set<epiMat3x3f>('H'); ASSERT_EQ(pp.Get<epiMat3x3f>(), 'H'); break;
            // case epiMetaTypeID_epiMat4x4f: ASSERT_EQ(pp.Get<epiMat4x4f>(), '0'); pp.Set<epiMat4x4f>('H'); ASSERT_EQ(pp.Get<epiMat4x4f>(), 'H'); break;
            default: ASSERT_FALSE("Unhandled case");
            }
        }

        m = m->GetSuperTypeID() != epiMetaTypeID_None ? ClassRegistry_Type_Lookup(m->GetSuperTypeID()) : nullptr;
    }
}

EPI_NAMESPACE_END()
