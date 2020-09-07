#include <gtest/gtest.h>

#include "EpiCore/ObjectModel/PropertyPointer.h"

#include "TestClassA.h"

#define ASSERT_PP(T, V) ASSERT_EQ(pp.Get<T>(), T{}); pp.Set<T>(V); ASSERT_EQ(pp.Get<T>(), V); break;
#define ASSERT_PP_COMPOUND_EX(T, V, IV) { T tIV); ASSERT_EQ(pp.Get<T>(), t); t = V; pp.Set<T>(t); ASSERT_EQ(pp.Get<T>(), t); break; }
#define ASSERT_PP_COMPOUND(T, V) ASSERT_PP_COMPOUND_EX(T, V, {})

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
            case epiMetaTypeID_epiChar: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiChar>(), '\0'); if (pp.IsWriteable()) pp.Set<epiChar>('H'); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiChar>(), 'H'); break;
            case epiMetaTypeID_epiWChar: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiWChar>(), L'\0'); if (pp.IsWriteable()) pp.Set<epiWChar>(L'H'); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiWChar>(), L'H'); break;

            case epiMetaTypeID_epiBool: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiBool>(), false); if (pp.IsWriteable()) pp.Set<epiBool>(true); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiBool>(), true); break;

            case epiMetaTypeID_epiByte: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiByte>(), 0); if (pp.IsWriteable()) pp.Set<epiByte>(12); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiByte>(), 12); break;

            case epiMetaTypeID_epiFloat: if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiFloat>(), 0.0f, epiFloatingEqTolerance()); if (pp.IsWriteable()) pp.Set<epiFloat>(-125.0f); else break; if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiFloat>(), -125.0f, epiFloatingEqTolerance()); break;
            case epiMetaTypeID_epiDouble: if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiDouble>(), 0.0, epiFloatingEqTolerance()); if (pp.IsWriteable()) pp.Set<epiDouble>(-0.035); else break; if (pp.IsReadable()) ASSERT_NEAR(pp.Get<epiDouble>(), -0.035, epiFloatingEqTolerance()); break;

            case epiMetaTypeID_epiSize_t: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiSize_t>(), 0); if (pp.IsWriteable()) pp.Set<epiSize_t>(550); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiSize_t>(), 550); break;

            case epiMetaTypeID_epiString: { epiString t(epiDEBUG_ONLY("Empty")); if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiString>(), t); t = "Test text"; if (pp.IsWriteable()) pp.Set<epiString>(t); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiString>(), t); break; }
            case epiMetaTypeID_epiWString: { epiWString t(epiDEBUG_ONLY(L"Empty")); if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiWString>(), t); t = L"Test Wtext"; if (pp.IsWriteable()) pp.Set<epiWString>(t); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiWString>(), t); break; }

            case epiMetaTypeID_epiU8: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU8>(), 0); if (pp.IsWriteable()) pp.Set<epiU8>(32); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU8>(), 32); break;
            case epiMetaTypeID_epiU16: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU16>(), 0); if (pp.IsWriteable()) pp.Set<epiU16>(158); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU16>(), 158); break;
            case epiMetaTypeID_epiU32: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU32>(), 0); if (pp.IsWriteable()) pp.Set<epiU32>(2444212); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU32>(), 2444212); break;
            case epiMetaTypeID_epiU64: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU64>(), 0); if (pp.IsWriteable()) pp.Set<epiU64>(298190129300); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiU64>(), 298190129300); break;
            case epiMetaTypeID_epiS8: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS8>(), 0); if (pp.IsWriteable()) pp.Set<epiS8>(-16); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS8>(), -16); break;
            case epiMetaTypeID_epiS16: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS16>(), 0); if (pp.IsWriteable()) pp.Set<epiS16>(-1241); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS16>(), -1241); break;
            case epiMetaTypeID_epiS32: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS32>(), 0); if (pp.IsWriteable()) pp.Set<epiS32>(89537); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS32>(), 89537); break;
            case epiMetaTypeID_epiS64: if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS64>(), 0); if (pp.IsWriteable()) pp.Set<epiS64>(213125125); else break; if (pp.IsReadable()) ASSERT_EQ(pp.Get<epiS64>(), 213125125); break;

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

    ASSERT_EQ(4, 2 + 2);
}

EPI_NAMESPACE_END()
