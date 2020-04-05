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

EPI_GENREGION_BEGIN(include)
#include "A.h"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void DataClass::Serialization(json_t& json) const
{
    super::Serialization(json);

    epiSerialize(x, json);
    epiSerialize(y, json);
    epiSerialize(z, json);
    epiSerialize(w, json);
}

void DataClass::Deserialization(const json_t& json)
{
    super::Deserialization(json);

    epiDeserialize(x, json);
    epiDeserialize(y, json);
    epiDeserialize(z, json);
    epiDeserialize(w, json);
}

MetaClassData DataClass::EmitMetaClassData()
{
    MetaClassData data;

    epiMetaProperty(x, DataClass, epiFloat, 0);
    epiMetaProperty(y, DataClass, epiFloat, 0);
    epiMetaProperty(z, DataClass, epiFloat, 0);
    epiMetaProperty(w, DataClass, epiFloat, 0);

    return data;
}

MetaClassData DataClass::DataClass_MetaClassData = DataClass::EmitMetaClassData();

void AClass::Serialization(json_t& json) const
{
    super::Serialization(json);

    epiSerialize(Prty_1, json);
    epiSerialize(Prty_2, json);
    epiSerialize(Prty_3, json);
    epiSerialize(Prty_4, json);
    epiSerialize(Prty_5, json);
    epiSerialize(Prty_6, json);
    epiSerialize(Prty_7, json);
    epiSerialize(Virtual_1, json);
    epiSerialize(Virtual_2, json);
    epiSerialize(MyArray, json);
}

void AClass::Deserialization(const json_t& json)
{
    super::Deserialization(json);

    epiDeserialize(Prty_1, json);
    epiDeserialize(Prty_2, json);
    epiDeserialize(Prty_3, json);
    epiDeserialize(Prty_4, json);
    epiDeserialize(Prty_5, json);
    epiDeserialize(Prty_6, json);
    epiDeserialize(Prty_7, json);
    epiDeserialize(Virtual_1, json);
    epiDeserialize(Virtual_2, json);
    epiDeserialize(MyArray, json);
}

MetaClassData AClass::EmitMetaClassData()
{
    MetaClassData data;

    epiMetaProperty(Prty_1, AClass, epiS32, 0);
    epiMetaProperty(Prty_2, AClass, epiBool, 0);
    epiMetaProperty(Prty_3, AClass, DataClass, 0);
    epiMetaProperty(Prty_4, AClass, DataClass****, 0);
    epiMetaProperty(Prty_5, AClass, epiString, 0);
    epiMetaProperty(Prty_6, AClass, epiChar, 0);
    epiMetaProperty(Prty_7, AClass, epiChar, 0);
    epiMetaProperty(Virtual_1, AClass, epiFloat, 0);
    epiMetaProperty(Virtual_2, AClass, epiS32, 0);
    epiMetaProperty(MyArray, AClass, epiArray, epiFloat);

    return data;
}

MetaClassData AClass::AClass_MetaClassData = AClass::EmitMetaClassData();

void BClass::Serialization(json_t& json) const
{
    super::Serialization(json);

    epiSerialize(Prty_B, json);
}

void BClass::Deserialization(const json_t& json)
{
    super::Deserialization(json);

    epiDeserialize(Prty_B, json);
}

MetaClassData BClass::EmitMetaClassData()
{
    MetaClassData data;

    epiMetaProperty(Prty_B, BClass, epiFloat, 0);

    return data;
}

MetaClassData BClass::BClass_MetaClassData = BClass::EmitMetaClassData();

EPI_NAMESPACE_END()
