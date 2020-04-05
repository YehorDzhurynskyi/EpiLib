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

#define EPI_GENHIDDEN_DataClass() \
 \
using super = Object; \
 \
static MetaClassData EmitMetaClassData(); \
static MetaClassData DataClass_MetaClassData; \
 \
const MetaClass& GetMetaClass() const override \
{ \
    assert(g_ClassRegistry.find(DataClass::TypeID) != g_ClassRegistry.end()); \
    return *ClassRegistry_Type_Lookup(DataClass::TypeID); \
} \
 \
epiBool Is(epiHash_t rhs) const override \
{ \
    return rhs == DataClass::TypeID || super::Is(rhs); \
} \
 \
void Serialization(json_t& json) override; \
void Deserialization(const json_t& json) override;
\
inline epiFloat Getx() const { return m_x; } \
inline void Setx(epiFloat value) { m_x = value; } \
inline epiFloat Gety() const { return m_y; } \
inline void Sety(epiFloat value) { m_y = value; } \
inline epiFloat Getz() const { return m_z; } \
inline void Setz(epiFloat value) { m_z = value; } \
inline epiFloat Getw() const { return m_w; } \
inline void Setw(epiFloat value) { m_w = value; } \
\
enum DataClass_PIDXs \
{ \
    PIDX_x = 0, \
    PIDX_y = 1, \
    PIDX_z = 2, \
    PIDX_w = 3, \
    COUNT = 4 \
}; \

#define EPI_GENHIDDEN_AClass() \
 \
using super = Object; \
 \
static MetaClassData EmitMetaClassData(); \
static MetaClassData AClass_MetaClassData; \
 \
const MetaClass& GetMetaClass() const override \
{ \
    assert(g_ClassRegistry.find(AClass::TypeID) != g_ClassRegistry.end()); \
    return *ClassRegistry_Type_Lookup(AClass::TypeID); \
} \
 \
epiBool Is(epiHash_t rhs) const override \
{ \
    return rhs == AClass::TypeID || super::Is(rhs); \
} \
 \
void Serialization(json_t& json) override; \
void Deserialization(const json_t& json) override;
\
inline epiS32 GetPrty_1() const { return m_Prty_1; } \
inline void SetPrty_1(epiS32 value) { m_Prty_1 = value; } \
inline epiBool GetPrty_2() const { return m_Prty_2; } \
inline void SetPrty_2(epiBool value) { m_Prty_2 = value; } \
inline DataClass& GetPrty_3() { return m_Prty_3; } \
inline const DataClass& GetPrty_3() const { return m_Prty_3; } \
inline void SetPrty_3(const DataClass& value) { m_Prty_3 = value; } \
inline DataClass****& GetPrty_4() { return m_Prty_4; } \
inline const DataClass****& GetPrty_4() const { return m_Prty_4; } \
inline void SetPrty_4(const DataClass****& value) { m_Prty_4 = value; } \
inline epiString& GetPrty_5() { return m_Prty_5; } \
inline const epiString& GetPrty_5() const { return m_Prty_5; } \
inline void SetPrty_5(const epiString& value) { m_Prty_5 = value; } \
inline epiChar GetPrty_6() const { return m_Prty_6; } \
inline void SetPrty_6(epiChar value) { m_Prty_6 = value; } \
inline epiChar GetPrty_7() const { return m_Prty_7; } \
inline void SetPrty_7(epiChar value) { m_Prty_7 = value; } \
inline epiFloat GetVirtual_1() const { return m_Virtual_1; } \
inline void SetVirtual_1(epiFloat value) { m_Virtual_1 = value; } \
inline epiS32 GetVirtual_2() const { return m_Virtual_2; } \
inline void SetVirtual_2(epiS32 value) { m_Virtual_2 = value; } \
inline epiArray& GetMyArray() { return m_MyArray; } \
inline const epiArray& GetMyArray() const { return m_MyArray; } \
inline void SetMyArray(const epiArray& value) { m_MyArray = value; } \
\
enum AClass_PIDXs \
{ \
    PIDX_Prty_1 = 0, \
    PIDX_Prty_2 = 1, \
    PIDX_Prty_3 = 2, \
    PIDX_Prty_4 = 3, \
    PIDX_Prty_5 = 4, \
    PIDX_Prty_6 = 5, \
    PIDX_Prty_7 = 6, \
    PIDX_Virtual_1 = 7, \
    PIDX_Virtual_2 = 8, \
    PIDX_MyArray = 9, \
    COUNT = 10 \
}; \

#define EPI_GENHIDDEN_BClass() \
 \
using super = AClass; \
 \
static MetaClassData EmitMetaClassData(); \
static MetaClassData BClass_MetaClassData; \
 \
const MetaClass& GetMetaClass() const override \
{ \
    assert(g_ClassRegistry.find(BClass::TypeID) != g_ClassRegistry.end()); \
    return *ClassRegistry_Type_Lookup(BClass::TypeID); \
} \
 \
epiBool Is(epiHash_t rhs) const override \
{ \
    return rhs == BClass::TypeID || super::Is(rhs); \
} \
 \
void Serialization(json_t& json) override; \
void Deserialization(const json_t& json) override;
\
inline epiFloat GetPrty_B() const { return m_Prty_B; } \
inline void SetPrty_B(epiFloat value) { m_Prty_B = value; } \
\
enum BClass_PIDXs \
{ \
    PIDX_Prty_B = 0, \
    COUNT = 1 \
}; \
