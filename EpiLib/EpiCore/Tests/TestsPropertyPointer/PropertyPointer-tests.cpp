#include <gtest/gtest.h>

#include "EpiCore/ObjectModel/PropertyPointer.h"

#include "TestClassA.h"

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
            case MetaTypeID_epiChar: ASSERT_EQ(pp.Get<epiChar>(), '0'); pp.Set<epiChar>('H'); ASSERT_EQ(pp.Get<epiChar>(), 'H'); break;
            case MetaTypeID_epiWChar: ASSERT_EQ(pp.Get<epiWChar>(), L'0'); pp.Set<epiWChar>(L'H'); ASSERT_EQ(pp.Get<epiWChar>(), L'H'); break;

            case MetaTypeID_epiBool: ASSERT_EQ(pp.Get<epiBool>(), false); pp.Set<epiBool>(true); ASSERT_EQ(pp.Get<epiBool>(), true); break;

            case MetaTypeID_epiByte: ASSERT_EQ(pp.Get<epiByte>(), 0); pp.Set<epiByte>(12); ASSERT_EQ(pp.Get<epiByte>(), 12); break;

            case MetaTypeID_epiFloat: ASSERT_NEAR(pp.Get<epiFloat>(), 0.0f, epiFloatingEqTolerance()); pp.Set<epiFloat>(-125.0f); ASSERT_NEAR(pp.Get<epiFloat>(), -125.0f, epiFloatingEqTolerance()); break;
            case MetaTypeID_epiDouble: ASSERT_NEAR(pp.Get<epiDouble>(), 0.0, epiFloatingEqTolerance()); pp.Set<epiDouble>(-0.035); ASSERT_NEAR(pp.Get<epiDouble>(), -0.035, epiFloatingEqTolerance()); break;

            case MetaTypeID_epiSize_t: ASSERT_EQ(pp.Get<epiSize_t>(), 0); pp.Set<epiSize_t>(550); ASSERT_EQ(pp.Get<epiSize_t>(), 550); break;

            // TODO: handle
            // case MetaTypeID_epiString: ASSERT_EQ(pp.Get<epiString&>(), epiDEBUG_ONLY("Empty")); pp.Set<epiString&>("Test text"); ASSERT_EQ(pp.Get<epiString&>(), "Test text"); break;
            // case MetaTypeID_epiWString: ASSERT_EQ(pp.Get<epiWString&>(), epiDEBUG_ONLY(L"Empty")); pp.Set<epiWString&>(L"Test Wtext"); ASSERT_EQ(pp.Get<epiWString&>(), L"Test Wtext"); break;

            case MetaTypeID_epiU8: ASSERT_EQ(pp.Get<epiU8>(), 0); pp.Set<epiU8>(32); ASSERT_EQ(pp.Get<epiU8>(), 32); break;
            case MetaTypeID_epiU16: ASSERT_EQ(pp.Get<epiU16>(), 0); pp.Set<epiU16>(158); ASSERT_EQ(pp.Get<epiU16>(), 158); break;
            case MetaTypeID_epiU32: ASSERT_EQ(pp.Get<epiU32>(), 0); pp.Set<epiU32>(2444212); ASSERT_EQ(pp.Get<epiU32>(), 2444212); break;
            case MetaTypeID_epiU64: ASSERT_EQ(pp.Get<epiU64>(), 0); pp.Set<epiU64>(298190129300); ASSERT_EQ(pp.Get<epiU64>(), 298190129300); break;
            case MetaTypeID_epiS8: ASSERT_EQ(pp.Get<epiS8>(), 0); pp.Set<epiS8>(-16); ASSERT_EQ(pp.Get<epiS8>(), -16); break;
            case MetaTypeID_epiS16: ASSERT_EQ(pp.Get<epiS16>(), 0); pp.Set<epiS16>(-1241); ASSERT_EQ(pp.Get<epiS16>(), -1241); break;
            case MetaTypeID_epiS32: ASSERT_EQ(pp.Get<epiS32>(), 0); pp.Set<epiS32>(89537); ASSERT_EQ(pp.Get<epiS32>(), 89537); break;
            case MetaTypeID_epiS64: ASSERT_EQ(pp.Get<epiS64>(), 0); pp.Set<epiS64>(213125125); ASSERT_EQ(pp.Get<epiS64>(), 213125125); break;

            // TODO: handle
            // case MetaTypeID_epiArray: ASSERT_EQ(pp.Get<epiArray<epiS32>>(), epiArray<epiS32>{}); pp.Set<epiArray<epiS32>>({ 4, 3, -122, 5 }); ASSERT_EQ(pp.Get<epiArray<epiS32>>(), epiArray<epiS32>({ 4, 3, -122, 5 })); break;
            // case MetaTypeID_epiPtrArray: ASSERT_EQ(pp.Get<epiChar>(), '0'); pp.Set<epiChar>('H'); ASSERT_EQ(pp.Get<epiChar>(), 'H'); break;

            // case MetaTypeID_epiVec2f: ASSERT_EQ(pp.Get<epiVec2f>(), epiVec2f(0.0f, 0.0f)); pp.Set<epiVec2f>(epiVec2f(21.0f, -0.05f)); ASSERT_EQ(pp.Get<epiVec2f>(), epiVec2f(21.0f, -0.05f)); break;
            // case MetaTypeID_epiVec2d: ASSERT_EQ(pp.Get<epiVec2d>(), epiVec2d(0.0, 0.0)); pp.Set<epiVec2d>(epiVec2d(0.0210, -12.05)); ASSERT_EQ(pp.Get<epiVec2d>(), epiVec2d(0.0210, -12.05)); break;
            // case MetaTypeID_epiVec2s: ASSERT_EQ(pp.Get<epiVec2s>(), epiVec2s(0, 0)); pp.Set<epiVec2s>(epiVec2s(-3, 12)); ASSERT_EQ(pp.Get<epiVec2s>(), epiVec2s(-3, 12)); break;
            // case MetaTypeID_epiVec2u: ASSERT_EQ(pp.Get<epiVec2u>(), epiVec2u(0, 0)); pp.Set<epiVec2u>(epiVec2u(0, 17)); ASSERT_EQ(pp.Get<epiVec2u>(), epiVec2u(0, 17)); break;

            // case MetaTypeID_epiVec3f: ASSERT_EQ(pp.Get<epiVec3f>(), '0'); pp.Set<epiVec3f>('H'); ASSERT_EQ(pp.Get<epiVec3f>(), 'H'); break;
            // case MetaTypeID_epiVec3d: ASSERT_EQ(pp.Get<epiVec3d>(), '0'); pp.Set<epiVec3d>('H'); ASSERT_EQ(pp.Get<epiVec3d>(), 'H'); break;
            // case MetaTypeID_epiVec3s: ASSERT_EQ(pp.Get<epiVec3s>(), '0'); pp.Set<epiVec3s>('H'); ASSERT_EQ(pp.Get<epiVec3s>(), 'H'); break;
            // case MetaTypeID_epiVec3u: ASSERT_EQ(pp.Get<epiVec3u>(), '0'); pp.Set<epiVec3u>('H'); ASSERT_EQ(pp.Get<epiVec3u>(), 'H'); break;

            // case MetaTypeID_epiVec4f: ASSERT_EQ(pp.Get<epiVec4f>(), '0'); pp.Set<epiVec4f>('H'); ASSERT_EQ(pp.Get<epiVec4f>(), 'H'); break;
            // case MetaTypeID_epiVec4d: ASSERT_EQ(pp.Get<epiVec4d>(), '0'); pp.Set<epiVec4d>('H'); ASSERT_EQ(pp.Get<epiVec4d>(), 'H'); break;
            // case MetaTypeID_epiVec4s: ASSERT_EQ(pp.Get<epiVec4s>(), '0'); pp.Set<epiVec4s>('H'); ASSERT_EQ(pp.Get<epiVec4s>(), 'H'); break;
            // case MetaTypeID_epiVec4u: ASSERT_EQ(pp.Get<epiVec4u>(), '0'); pp.Set<epiVec4u>('H'); ASSERT_EQ(pp.Get<epiVec4u>(), 'H'); break;

            // case MetaTypeID_epiMat2x2f: ASSERT_EQ(pp.Get<epiMat2x2f>(), '0'); pp.Set<epiMat2x2f>('H'); ASSERT_EQ(pp.Get<epiMat2x2f>(), 'H'); break;
            // case MetaTypeID_epiMat3x3f: ASSERT_EQ(pp.Get<epiMat3x3f>(), '0'); pp.Set<epiMat3x3f>('H'); ASSERT_EQ(pp.Get<epiMat3x3f>(), 'H'); break;
            // case MetaTypeID_epiMat4x4f: ASSERT_EQ(pp.Get<epiMat4x4f>(), '0'); pp.Set<epiMat4x4f>('H'); ASSERT_EQ(pp.Get<epiMat4x4f>(), 'H'); break;
            default: ASSERT_FALSE("Unhandled case");
            }
        }

        m = m->GetSuperTypeID() != MetaTypeID_None ? ClassRegistry_Type_Lookup(m->GetSuperTypeID()) : nullptr;
    }

    ASSERT_EQ(4, 2 + 2);
}

EPI_NAMESPACE_END()
