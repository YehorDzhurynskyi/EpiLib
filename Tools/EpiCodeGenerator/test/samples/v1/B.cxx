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
#include "B.h"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void DClass::Serialization(json_t& json) const
{
    super::Serialization(json);

    epiSerialize(HIHI, json);
    epiSerialize(IsA, json);
    epiSerialize(IsB, json);
    epiSerialize(yArray, json);
}

void DClass::Deserialization(const json_t& json)
{
    super::Deserialization(json);

    epiDeserialize(HIHI, json);
    epiDeserialize(IsA, json);
    epiDeserialize(IsB, json);
    epiDeserialize(yArray, json);
}

MetaClassData DClass::EmitMetaClassData()
{
    MetaClassData data;

    epiMetaProperty(HIHI, DClass, epiU32, 0);
    epiMetaProperty(IsA, DClass, epiBool, 0);
    epiMetaProperty(IsB, DClass, epiBool, 0);
    epiMetaProperty(yArray, DClass, epiArray, AClass);

    return data;
}

MetaClassData DClass::DClass_MetaClassData = DClass::EmitMetaClassData();

EPI_NAMESPACE_END()
