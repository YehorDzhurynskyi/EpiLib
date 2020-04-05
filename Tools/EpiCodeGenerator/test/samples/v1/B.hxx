/*                                                      */
/*  ______       _                                      */
/* |  ____|     (_)                                     */
/* | |__   _ __  _                                      */
/* |  __| | '_ \| |   THIS FILE IS AUTO-GENERATED       */
/* | |____| |_) | |   manual changes won't be saved     */
/* |______| .__/|_|                                     */
/*        | |                                           */
/*        |_|                                           */
/*                                                      */

#define EPI_GENHIDDEN_DClass() \
 \
using super = BClass; \
 \
static MetaClassData EmitMetaClassData(); \
static MetaClassData DClass_MetaClassData; \
 \
const MetaClass& GetMetaClass() const override \
{ \
    assert(g_ClassRegistry.find(DClass::TypeID) != g_ClassRegistry.end()); \
    return *ClassRegistry_Type_Lookup(DClass::TypeID); \
} \
 \
epiBool Is(epiHash_t rhs) const override \
{ \
    return rhs == DClass::TypeID || super::Is(rhs); \
} \
 \
void Serialization(json_t& json) override; \
void Deserialization(const json_t& json) override;
\
inline epiU32 GetHIHI() const { return m_HIHI; } \
inline void SetHIHI(epiU32 value) { m_HIHI = value; } \
inline epiBool GetIsA() const { return m_IsA; } \
inline void SetIsA(epiBool value) { m_IsA = value; } \
inline epiBool GetIsB() const { return m_IsB; } \
inline void SetIsB(epiBool value) { m_IsB = value; } \
inline epiArray& GetyArray() { return m_yArray; } \
inline const epiArray& GetyArray() const { return m_yArray; } \
inline void SetyArray(const epiArray& value) { m_yArray = value; } \
\
enum DClass_PIDXs \
{ \
    PIDX_HIHI = 0, \
    PIDX_IsA = 1, \
    PIDX_IsB = 2, \
    PIDX_yArray = 3, \
    COUNT = 4 \
}; \
