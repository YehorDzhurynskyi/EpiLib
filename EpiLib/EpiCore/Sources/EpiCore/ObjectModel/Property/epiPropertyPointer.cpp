#include "epiPropertyPointer.h"

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

epiPropertyPointer epiPropertyPointer::CreateFromProperty(Object& self, const MetaProperty* property)
{
    epiPropertyPointer ptr;
    ptr.m_Meta = property;
    ptr.m_Form = Form::Property;
    ptr.m_TypeID = ptr.m_Meta->GetTypeID();
    ptr.m_Self = &self;

    return ptr;
}

epiPropertyPointer epiPropertyPointer::CreateFromProperty(const Object& self, const MetaProperty* property)
{
    epiPropertyPointer ptr;
    ptr.m_Meta = property;
    ptr.m_Form = Form::PropertyConst;
    ptr.m_TypeID = ptr.m_Meta->GetTypeID();
    ptr.m_SelfConst = &self;

    return ptr;
}

epiPropertyPointer epiPropertyPointer::CreateFromArray(epiBaseArray& self, epiMetaTypeID nestedTypeId, epiU32 idx)
{
    epiPropertyPointer ptr;
    ptr.m_ValueAddr = self.GetData() + self.GetSizeOfItem() * idx;
    ptr.m_SizeOf = self.GetSizeOfItem();
    ptr.m_Form = Form::ArrayElem;
    ptr.m_TypeID = nestedTypeId;

    return ptr;
}

epiString epiPropertyPointer::GetValueString(epiS32 style) const
{
    switch (GetTypeID())
    {
    case epiMetaTypeID_epiBool:
    {
        if (style & epiPropertyPointerValueStringStyle_Boolean_ON_OFF)
        {
            return Get<epiBool>() ? "ON" : "OFF";
        }
        else if (style & epiPropertyPointerValueStringStyle_Boolean_True_False)
        {
            return Get<epiBool>() ? "True" : "False";
        }
        else if (style & epiPropertyPointerValueStringStyle_Boolean_Enabled_Disabled)
        {
            return Get<epiBool>() ? "Enabled" : "Disabled";
        }

        return std::to_string(Get<epiBool>());
    }
    case epiMetaTypeID_epiS32: return std::to_string(Get<epiS32>());
    case epiMetaTypeID_epiSize_t:
    {
        if (style & epiPropertyPointerValueStringStyle_Size_Repr_Bytes)
        {
            epiSize_t value = Get<epiSize_t>();
            if (value == 0)
            {
                return "0 B";
            }

            epiString str;
            str.reserve(64);

            const epiChar* kOrder[]
            {
                "B",
                "KB",
                "MB",
                "GB",
                "TB"
            };

            epiS32 order = 0;
            do
            {
                const epiSize_t rest = value % 1024;
                if (rest != 0)
                {
                    if (!str.empty())
                    {
                        str = ' ' + str;
                    }

                    str = std::to_string(rest) + ' ' + kOrder[order] + str;
                }

                value = (value - rest) / 1024;
            }
            while (value > 0 && (++order + 1) < epiArrLen(kOrder));

            return str;
        }

        return std::to_string(Get<epiSize_t>());
    }
    case epiMetaTypeID_epiString:
    {
        if (style & epiPropertyPointerValueStringStyle_String_Quoted)
        {
            return '`' + Get<epiString>() + '`';
        }

        return Get<epiString>();
    }
    default: epiAssert(!"Implement");
    }

    return "";
}

epiBool epiPropertyPointer::IsReadable() const
{
    return m_Form == Form::ArrayElem || m_Meta->m_Flags.ReadCallback || !m_Meta->m_Flags.WriteCallback || !m_Meta->m_Flags.WriteOnly;
}

epiBool epiPropertyPointer::IsWritable() const
{
    return m_Form != Form::PropertyConst && (m_Form == Form::ArrayElem || m_Meta->m_Flags.WriteCallback || !m_Meta->m_Flags.ReadCallback || !m_Meta->m_Flags.ReadOnly);
}

const epiChar* epiPropertyPointer::GetPropertyName() const
{
    return m_Meta->GetName();
}

epiMetaTypeID epiPropertyPointer::GetTypeID() const
{
    return m_TypeID;
}

epiMetaPropertyID epiPropertyPointer::GetPID() const
{
    return m_Meta->GetPID();
}

#if 0
// NOTE: runtime lookup
// uncomment if compile-time type deduction isn't enough

void* epiPropertyPointer::Get_Dynamic() const
{
    epiAssert(IsReadable());

    void* value = nullptr;

    if (m_Form == Form::ArrayElem)
    {
        value = m_ValueAddr;
    }
    else if (m_Form == Form::Property)
    {
        void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrRead;
        if (m_Meta->m_Flags.ReadCallback)
        {
            if (MetaType::IsCompound(m_Meta->m_TypeID))
            {
                GetCallback_Ref(Object);
            }
            else
            {
                switch (m_Meta->m_TypeID)
                {
                case epiMetaTypeID_epiChar: GetCallback(epiChar); break;
                case epiMetaTypeID_epiWChar: GetCallback(epiWChar); break;
                case epiMetaTypeID_epiBool: GetCallback(epiBool); break;
                case epiMetaTypeID_epiByte: GetCallback(epiByte); break;
                case epiMetaTypeID_epiFloat: GetCallback(epiFloat); break;
                case epiMetaTypeID_epiDouble: GetCallback(epiDouble); break;
                case epiMetaTypeID_epiSize_t: GetCallback(epiSize_t); break;
                case epiMetaTypeID_epiU8: GetCallback(epiU8); break;
                case epiMetaTypeID_epiU16: GetCallback(epiU16); break;
                case epiMetaTypeID_epiU32: GetCallback(epiU32); break;
                case epiMetaTypeID_epiU64: GetCallback(epiU64); break;
                case epiMetaTypeID_epiS8: GetCallback(epiS8); break;
                case epiMetaTypeID_epiS16: GetCallback(epiS16); break;
                case epiMetaTypeID_epiS32: GetCallback(epiS32); break;
                case epiMetaTypeID_epiS64: GetCallback(epiS64); break;
                case epiMetaTypeID_epiString: GetCallback_Ref(epiString); break;
                case epiMetaTypeID_epiWString: GetCallback_Ref(epiWString); break;
                case epiMetaTypeID_epiArray: GetCallback_Ref(epiBaseArray); break;
                case epiMetaTypeID_epiPtrArray: GetCallback_Ref(epiBaseArray); break;
                default: epiAssert(false, "Unexpected type id"); break;
                }
            }
        }
        else
        {
            if (MetaType::IsCompound(m_Meta->m_TypeID))
            {
                value = addr;
            }
            else
            {
                switch (m_Meta->m_TypeID)
                {
                case epiMetaTypeID_epiChar: value = (void*)*((epiChar*)addr); break;
                case epiMetaTypeID_epiWChar: value = (void*)*((epiWChar*)addr); break;
                case epiMetaTypeID_epiBool: value = (void*)*((epiBool*)addr); break;
                case epiMetaTypeID_epiByte: value = (void*)*((epiByte*)addr); break;
                case epiMetaTypeID_epiFloat: value = (void*)*((epiU32*)addr); break;
                case epiMetaTypeID_epiDouble: value = (void*)*((epiU64*)addr); break;
                case epiMetaTypeID_epiSize_t: value = (void*)*((epiSize_t*)addr); break;
                case epiMetaTypeID_epiU8: value = (void*)*((epiU8*)addr); break;
                case epiMetaTypeID_epiU16: value = (void*)*((epiU16*)addr); break;
                case epiMetaTypeID_epiU32: value = (void*)*((epiU32*)addr); break;
                case epiMetaTypeID_epiU64: value = (void*)*((epiU64*)addr); break;
                case epiMetaTypeID_epiS8: value = (void*)*((epiS8*)addr); break;
                case epiMetaTypeID_epiS16: value = (void*)*((epiS16*)addr); break;
                case epiMetaTypeID_epiS32: value = (void*)*((epiS32*)addr); break;
                case epiMetaTypeID_epiS64: value = (void*)*((epiS64*)addr); break;
                case epiMetaTypeID_epiString: value = addr; break;
                case epiMetaTypeID_epiWString: value = addr; break;
                case epiMetaTypeID_epiArray: value = addr; break;
                case epiMetaTypeID_epiPtrArray: value = addr; break;
                default: epiAssert(false, "Unexpected type id"); break;
                }
            }
        }
    }

    return value;
}

void epiPropertyPointer::Set_Dynamic(void* value)
{
    epiAssert(IsWritable());

    if (m_Form == Form::ArrayElem)
    {
        memcpy_s(m_ValueAddr, m_SizeOf, &reinterpret_cast<Object&>(value), m_SizeOf);
    }
    else if (m_Form == Form::Property)
    {
        void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrWrite;
        if (m_Meta->m_Flags.WriteCallback)
        {
            switch (m_Meta->m_TypeID)
            {
            case epiMetaTypeID_epiChar: SetCallback(epiChar); break;
            case epiMetaTypeID_epiWChar: SetCallback(epiWChar); break;
            case epiMetaTypeID_epiBool: SetCallback(epiBool); break;
            case epiMetaTypeID_epiByte: SetCallback(epiByte); break;
            case epiMetaTypeID_epiFloat: SetCallback(epiFloat); break;
            case epiMetaTypeID_epiDouble: SetCallback(epiDouble); break;
            case epiMetaTypeID_epiSize_t: SetCallback(epiSize_t); break;
            case epiMetaTypeID_epiU8: SetCallback(epiU8); break;
            case epiMetaTypeID_epiU16: SetCallback(epiU16); break;
            case epiMetaTypeID_epiU32: SetCallback(epiU32); break;
            case epiMetaTypeID_epiU64: SetCallback(epiU64); break;
            case epiMetaTypeID_epiS8: SetCallback(epiS8); break;
            case epiMetaTypeID_epiS16: SetCallback(epiS16); break;
            case epiMetaTypeID_epiS32: SetCallback(epiS32); break;
            case epiMetaTypeID_epiS64: SetCallback(epiS64); break;
            case epiMetaTypeID_epiString: SetCallback_Ref(epiString); break;
            case epiMetaTypeID_epiWString: SetCallback_Ref(epiWString); break;
            case epiMetaTypeID_epiArray: SetCallback_Ref(epiBaseArray); break;
            case epiMetaTypeID_epiPtrArray: SetCallback_Ref(epiBaseArray); break;
            default: epiAssert(false, "Unexpected type id"); break;
            }
        }
        else
        {
            switch (m_Meta->m_TypeID)
            {
            case epiMetaTypeID_epiChar: *((epiChar*)addr) = *((epiChar*)&value); break;
            case epiMetaTypeID_epiWChar: *((epiWChar*)addr) = *((epiWChar*)&value); break;
            case epiMetaTypeID_epiBool: *((epiBool*)addr) = *((epiBool*)&value); break;
            case epiMetaTypeID_epiByte: *((epiByte*)addr) = *((epiByte*)&value); break;
            case epiMetaTypeID_epiFloat: *((epiFloat*)addr) = *((epiFloat*)&value); break;
            case epiMetaTypeID_epiDouble: *((epiDouble*)addr) = *((epiDouble*)&value); break;
            case epiMetaTypeID_epiSize_t: *((epiSize_t*)addr) = *((epiSize_t*)&value); break;
            case epiMetaTypeID_epiU8: *((epiU8*)addr) = *((epiU8*)&value); break;
            case epiMetaTypeID_epiU16: *((epiU16*)addr) = *((epiU16*)&value); break;
            case epiMetaTypeID_epiU32: *((epiU32*)addr) = *((epiU32*)&value); break;
            case epiMetaTypeID_epiU64: *((epiU64*)addr) = *((epiU64*)&value); break;
            case epiMetaTypeID_epiS8: *((epiS8*)addr) = *((epiS8*)&value); break;
            case epiMetaTypeID_epiS16: *((epiS16*)addr) = *((epiS16*)&value); break;
            case epiMetaTypeID_epiS32: *((epiS32*)addr) = *((epiS32*)&value); break;
            case epiMetaTypeID_epiS64: *((epiS64*)addr) = *((epiS64*)&value); break;
            case epiMetaTypeID_epiString: *((epiString*)addr) = *((const epiString*)value); break;
            case epiMetaTypeID_epiWString: *((epiWString*)addr) = *((const epiWString*)value); break;
            case epiMetaTypeID_epiArray: *((epiBaseArray*)addr) = *((const epiBaseArray*)value); break;
            case epiMetaTypeID_epiPtrArray: *((epiBaseArray*)addr) = *((const epiBaseArray*)value); break;
            default: epiAssert(false, "Unexpected type id"); break;
            }
        }
    }
}
#endif

EPI_NAMESPACE_END()
