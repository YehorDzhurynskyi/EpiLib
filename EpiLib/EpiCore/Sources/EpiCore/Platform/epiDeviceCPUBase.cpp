EPI_GENREGION_BEGIN(include)
#include "EpiCore/Platform/epiDeviceCPUBase.h"
#include "EpiCore/Platform/epiDeviceCPUBase.cxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Property/epiPropertyPointer.h"

EPI_NAMESPACE_BEGIN()

epiSize_t epiDeviceCPUBase::GetNumberOfLogicalThreads_Callback() const
{
    return std::thread::hardware_concurrency();
}

epiString epiDeviceCPUBase::ToString() const
{
    epiString str;
    str.reserve(16);

    const MetaClass& meta = epiDeviceCPUBase::GetMetaClass();
    const MetaClassData& metaData = meta.GetClassData();
    for (const auto& prty : metaData)
    {
        const epiMetaPropertyID pid = prty.GetPID();
        if (const MetaProperty* prty = metaData.GetPropertyBy(pid))
        {
            str += epiString(prty->GetName()) + ":";
            epiPropertyPointer ptr = epiPropertyPointer::CreateFromProperty(*this, prty);
            str += ' ' + ptr.GetValueString(epiPropertyPointerValueStringStyle_Boolean_Enabled_Disabled |
                                            epiPropertyPointerValueStringStyle_String_Quoted);
            str += '\n';
        }
    }

    return str;
}

EPI_NAMESPACE_END()
