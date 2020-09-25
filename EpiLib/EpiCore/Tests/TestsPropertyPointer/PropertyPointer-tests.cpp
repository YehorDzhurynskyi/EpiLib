#include <gtest/gtest.h>

#include "EpiCore/ObjectModel/PropertyPointer.h"

#include "TestClass.h"

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
    T temp = IV; \
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

namespace
{

EPI_NAMESPACE_USING()

// TODO: add tests for array elements

void TraverseProperties(TestClassA& obj)
{
    obj.Reset();

    const auto* m = &obj.GetMetaClass();
    while (m)
    {
        for (const auto& p : m->GetClassData())
        {
            auto pp = PropertyPointer::CreateFromProperty(obj, &p);
            ASSERT_EQ(pp.GetTypeID(), p.GetTypeID());
            ASSERT_EQ(pp.IsReadable(), p.GetFlags().ReadCallback || !p.GetFlags().WriteCallback || !p.GetFlags().WriteOnly);
            ASSERT_EQ(pp.IsWritable(), p.GetFlags().WriteCallback || !p.GetFlags().ReadCallback || !p.GetFlags().ReadOnly);

            switch (p.GetTypeID())
            {
            case epiMetaTypeID_Ptr: if (pp.IsReadable()) ASSERT_EQ(pp.Get<Object*>(), nullptr); if (pp.IsWritable()) pp.Set<Object*>((Object*)0x00fff2); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<Object*>(), (Object*)0x00fff2); break;

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

            case epiMetaTypeID_epiString: ASSERT_PP_COMPOUND_EX(epiString, "Test text", epiString(epiDEBUG_ONLY("Empty")))
            case epiMetaTypeID_epiWString: ASSERT_PP_COMPOUND_EX(epiWString, L"Test Wtext", epiWString(epiDEBUG_ONLY(L"Empty")))

            case epiMetaTypeID_epiArray:
            switch (p.GetNestedTypeID())
            {
            case epiMetaTypeID_epiS32: ASSERT_PP_ARRAY(epiArray<epiS32>, epiArray<epiS32>({ -5, 1, 2, 3, 4, -3 }))
            case epiMetaTypeID_epiString: ASSERT_PP_ARRAY(epiArray<epiString>, epiArray<epiString>({ "Hello", " ", "World", "!", "" }))
            default: ASSERT_FALSE("Unhandled case");
            }
            break;

            case epiMetaTypeID_epiPtrArray:
            switch (p.GetNestedTypeID())
            {
            case epiMetaTypeID_epiS32: ASSERT_PP_ARRAY(epiPtrArray<epiS32>, epiPtrArray<epiS32>({ nullptr, (epiS32*)0xfa7f7af, (epiS32*)0x0000353f }))
            case epiMetaTypeID_epiString: ASSERT_PP_ARRAY(epiPtrArray<epiString>, epiPtrArray<epiString>({ nullptr, (epiString*)0xfa7f7af, (epiString*)0x0000353f }))
            default: ASSERT_FALSE("Unhandled case");
            }
            break;

            case epiMetaTypeID_epiVec2f: ASSERT_PP_COMPOUND(epiVec2f, epiVec2f({ 5.0f, -0.0052f }))
            case epiMetaTypeID_epiVec2d: ASSERT_PP_COMPOUND(epiVec2d, epiVec2d({ -35.0, 0.018 }))
            case epiMetaTypeID_epiVec2s: ASSERT_PP_COMPOUND(epiVec2s, epiVec2s({ -9123, 0 }))
            case epiMetaTypeID_epiVec2u: ASSERT_PP_COMPOUND(epiVec2u, epiVec2u({ 65653, 998 }))

            case epiMetaTypeID_epiVec3f: ASSERT_PP_COMPOUND(epiVec3f, epiVec3f({ 5.0f, -0.0052f, -18.02f }))
            case epiMetaTypeID_epiVec3d: ASSERT_PP_COMPOUND(epiVec3d, epiVec3d({ -35.0, 0.018, -0.074 }))
            case epiMetaTypeID_epiVec3s: ASSERT_PP_COMPOUND(epiVec3s, epiVec3s({ -9123, 0, 182842 }))
            case epiMetaTypeID_epiVec3u: ASSERT_PP_COMPOUND(epiVec3u, epiVec3u({ 65653, 998, 8232 }))

            case epiMetaTypeID_epiVec4f: ASSERT_PP_COMPOUND(epiVec4f, epiVec4f({ 5.0f, -0.0052f, -18.02f, 0.99f }))
            case epiMetaTypeID_epiVec4d: ASSERT_PP_COMPOUND(epiVec4d, epiVec4d({ -35.0, 0.018, -0.074, 0.421 }))
            case epiMetaTypeID_epiVec4s: ASSERT_PP_COMPOUND(epiVec4s, epiVec4s({ -9123, 0, 182842, -67 }))
            case epiMetaTypeID_epiVec4u: ASSERT_PP_COMPOUND(epiVec4u, epiVec4u({ 65653, 998, 8232, 74908 }))

            case epiMetaTypeID_epiMat2x2f: ASSERT_PP_COMPOUND(epiMat2x2f, epiMat2x2f({ 5.0f, -0.0052f,
                                                                                       0.50f, -102.0f }))

            case epiMetaTypeID_epiMat3x3f: ASSERT_PP_COMPOUND(epiMat3x3f, epiMat3x3f({ 5.0f, -0.0052f, 0.50f,
                                                                                       -98.006f, 0.0f, -0.0f,
                                                                                       80.4f, -6.02f, 0.9 }))

            case epiMetaTypeID_epiMat4x4f: ASSERT_PP_COMPOUND(epiMat4x4f, epiMat4x4f({ 5.0f, -0.0052f, 0.50, 70.0f,
                                                                                       -98.006f, 0.0f, -0.0, -23.25f,
                                                                                       80.4f, -6.02f, 0.9f, 0.0012f,
                                                                                       65.2f, 21.0f, 78.02f, -0.0014f }))

            case epiMetaTypeID_epiComplexf: ASSERT_PP_COMPOUND(epiComplexf, epiComplexf({ -5.0f, -2.0f }))
            case epiMetaTypeID_epiComplexd: ASSERT_PP_COMPOUND(epiComplexd, epiComplexd({ 0.0055, -0.78 }))

            case epiMetaTypeID_epiRect2f: ASSERT_PP_COMPOUND(epiRect2f, epiRect2f({ 5.0f, 3.0f, 0.05f, 9.0f }))
            case epiMetaTypeID_epiRect2d: ASSERT_PP_COMPOUND(epiRect2d, epiRect2d({ -5.0, -13.0, 10.05, 21.0 }))
            case epiMetaTypeID_epiRect2s: ASSERT_PP_COMPOUND(epiRect2s, epiRect2s({ -5, -2, 15, 71 }))
            case epiMetaTypeID_epiRect2u: ASSERT_PP_COMPOUND(epiRect2u, epiRect2u({ 807, 35, 1998, 421 }))

            case epiHashCompileTime(InplaceClass): ASSERT_PP_COMPOUND_EX(InplaceClass, InplaceClass(5, -127.0f, "Hi,!", { 0.05f, -192.0f, 25.0f, 0.005f }), InplaceClass({}))

            default: ASSERT_FALSE("Unhandled case");
            }
        }

        m = m->GetSuperTypeID() != epiMetaTypeID_None ? ClassRegistry_Type_Lookup(m->GetSuperTypeID()) : nullptr;
    }
}

}

EPI_NAMESPACE_BEGIN()

TEST(PropertyPointer, InheritedObject)
{
    TestClassA obj;

    TraverseProperties(obj);
}

TEST(PropertyPointer, InheritedSingleDepth)
{
    TestClassB obj;

    TraverseProperties(obj);
}

TEST(PropertyPointer, InheritedSingleDepthSingleInterface)
{
    TestClassC obj;

    TraverseProperties(obj);
}

TEST(PropertyPointer, InheritedDoubleDepth)
{
    TestClassBB obj;

    TraverseProperties(obj);
}

TEST(PropertyPointer, InheritedDoubleDepthDoubleInterface)
{
    TestClassCC obj;

    TraverseProperties(obj);
}

EPI_NAMESPACE_END()
