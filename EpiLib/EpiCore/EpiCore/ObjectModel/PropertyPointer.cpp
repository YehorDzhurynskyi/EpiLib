#include "EpiCore/pch.h"
#include "PropertyPointer.h"

#include "Object.h"

namespace epi
{

#define SetCallback(_x) ((void (*)(Object*, _x))m_Meta->m_PtrWrite)(m_Self, *((_x*)&value))
#define SetCallback_Ref(_x) ((void (*)(Object*, const _x&))m_Meta->m_PtrWrite)(m_Self, (const _x&)value)

#define GetCallback(_x) { _x v = ((_x (*)(Object*))m_Meta->m_PtrRead)(m_Self); value = (void*)*((epiSize_t*)&v); }
#define GetCallback_Ref(_x) { const _x& v = ((const _x& (*)(Object*))m_Meta->m_PtrRead)(m_Self); value = (void*)&v; }

PropertyPointer PropertyPointer::CreateFromProperty(Object& self, const MetaProperty* property)
{
    PropertyPointer ptr;
    ptr.m_Meta = property;
    ptr.m_Form = Form::Property;
    ptr.m_TypeID = ptr.m_Meta->GetTypeID();
    ptr.m_Self = &self;

    return ptr;
}

PropertyPointer PropertyPointer::CreateFromArray(epiBaseArray& self, MetaTypeID nestedTypeId, epiU32 idx)
{
    PropertyPointer ptr;
    ptr.m_ValueAddr = self.GetData() + self.GetSizeOfItem() * idx;
    ptr.m_SizeOf = self.GetSizeOfItem();
    ptr.m_Form = Form::ArrayElem;
    ptr.m_TypeID = nestedTypeId;

    return ptr;
}

void* PropertyPointer::Get()
{
    void* value = nullptr;

    if (m_Form == Form::ArrayElem)
    {
        value = m_ValueAddr;
    }
    else if (m_Form == Form::Property)
    {
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
                case MetaTypeID_epiChar: GetCallback(epiChar); break;
                case MetaTypeID_epiWChar: GetCallback(epiWChar); break;
                case MetaTypeID_epiBool: GetCallback(epiBool); break;
                case MetaTypeID_epiByte: GetCallback(epiByte); break;
                case MetaTypeID_epiFloat: GetCallback(epiFloat); break;
                case MetaTypeID_epiDouble: GetCallback(epiDouble); break;
                case MetaTypeID_epiSize_t: GetCallback(epiSize_t); break;
                case MetaTypeID_epiU8: GetCallback(epiU8); break;
                case MetaTypeID_epiU16: GetCallback(epiU16); break;
                case MetaTypeID_epiU32: GetCallback(epiU32); break;
                case MetaTypeID_epiU64: GetCallback(epiU64); break;
                case MetaTypeID_epiS8: GetCallback(epiS8); break;
                case MetaTypeID_epiS16: GetCallback(epiS16); break;
                case MetaTypeID_epiS32: GetCallback(epiS32); break;
                case MetaTypeID_epiS64: GetCallback(epiS64); break;
                case MetaTypeID_epiString: GetCallback_Ref(epiString); break;
                case MetaTypeID_epiWString: GetCallback_Ref(epiWString); break;
                case MetaTypeID_epiArray: GetCallback_Ref(epiBaseArray); break;
                case MetaTypeID_epiPtrArray: GetCallback_Ref(epiBaseArray); break;
                default: epiAssert(false, "Unexpected type id"); break;
                }
            }
        }
        else
        {
            void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrRead;
            if (MetaType::IsCompound(m_Meta->m_TypeID))
            {
                value = addr;
            }
            else
            {
                switch (m_Meta->m_TypeID)
                {
                case MetaTypeID_epiChar: value = (void*)*((epiChar*)addr); break;
                case MetaTypeID_epiWChar: value = (void*)*((epiWChar*)addr); break;
                case MetaTypeID_epiBool: value = (void*)*((epiBool*)addr); break;
                case MetaTypeID_epiByte: value = (void*)*((epiByte*)addr); break;
                case MetaTypeID_epiFloat: value = (void*)*((epiU32*)addr); break;
                case MetaTypeID_epiDouble: value = (void*)*((epiU64*)addr); break;
                case MetaTypeID_epiSize_t: value = (void*)*((epiSize_t*)addr); break;
                case MetaTypeID_epiU8: value = (void*)*((epiU8*)addr); break;
                case MetaTypeID_epiU16: value = (void*)*((epiU16*)addr); break;
                case MetaTypeID_epiU32: value = (void*)*((epiU32*)addr); break;
                case MetaTypeID_epiU64: value = (void*)*((epiU64*)addr); break;
                case MetaTypeID_epiS8: value = (void*)*((epiS8*)addr); break;
                case MetaTypeID_epiS16: value = (void*)*((epiS16*)addr); break;
                case MetaTypeID_epiS32: value = (void*)*((epiS32*)addr); break;
                case MetaTypeID_epiS64: value = (void*)*((epiS64*)addr); break;
                case MetaTypeID_epiString: value = addr; break;
                case MetaTypeID_epiWString: value = addr; break;
                case MetaTypeID_epiArray: value = addr; break;
                case MetaTypeID_epiPtrArray: value = addr; break;
                default: epiAssert(false, "Unexpected type id"); break;
                }
            }
        }
    }

    return value;
}

void PropertyPointer::Set(void* value)
{
    if (m_Form == Form::ArrayElem)
    {
        memcpy_s(m_ValueAddr, m_SizeOf, &reinterpret_cast<Object&>(value), m_SizeOf);
    }
    else if (m_Form == Form::Property)
    {
        if (m_Meta->m_Flags.WriteCallback)
        {
            switch (m_Meta->m_TypeID)
            {
            case MetaTypeID_epiChar: SetCallback(epiChar); break;
            case MetaTypeID_epiWChar: SetCallback(epiWChar); break;
            case MetaTypeID_epiBool: SetCallback(epiBool); break;
            case MetaTypeID_epiByte: SetCallback(epiByte); break;
            case MetaTypeID_epiFloat: SetCallback(epiFloat); break;
            case MetaTypeID_epiDouble: SetCallback(epiDouble); break;
            case MetaTypeID_epiSize_t: SetCallback(epiSize_t); break;
            case MetaTypeID_epiU8: SetCallback(epiU8); break;
            case MetaTypeID_epiU16: SetCallback(epiU16); break;
            case MetaTypeID_epiU32: SetCallback(epiU32); break;
            case MetaTypeID_epiU64: SetCallback(epiU64); break;
            case MetaTypeID_epiS8: SetCallback(epiS8); break;
            case MetaTypeID_epiS16: SetCallback(epiS16); break;
            case MetaTypeID_epiS32: SetCallback(epiS32); break;
            case MetaTypeID_epiS64: SetCallback(epiS64); break;
            case MetaTypeID_epiString: SetCallback_Ref(epiString); break;
            case MetaTypeID_epiWString: SetCallback_Ref(epiWString); break;
            case MetaTypeID_epiArray: SetCallback_Ref(epiBaseArray); break;
            case MetaTypeID_epiPtrArray: SetCallback_Ref(epiBaseArray); break;
            default: epiAssert(false, "Unexpected type id"); break;
            }
        }
        else
        {
            void* addr = (epiByte*)m_Self + (size_t)m_Meta->m_PtrWrite;
            switch (m_Meta->m_TypeID)
            {
            case MetaTypeID_epiChar: *((epiChar*)addr) = *((epiChar*)&value); break;
            case MetaTypeID_epiWChar: *((epiWChar*)addr) = *((epiWChar*)&value); break;
            case MetaTypeID_epiBool: *((epiBool*)addr) = *((epiBool*)&value); break;
            case MetaTypeID_epiByte: *((epiByte*)addr) = *((epiByte*)&value); break;
            case MetaTypeID_epiFloat: *((epiFloat*)addr) = *((epiFloat*)&value); break;
            case MetaTypeID_epiDouble: *((epiDouble*)addr) = *((epiDouble*)&value); break;
            case MetaTypeID_epiSize_t: *((epiSize_t*)addr) = *((epiSize_t*)&value); break;
            case MetaTypeID_epiU8: *((epiU8*)addr) = *((epiU8*)&value); break;
            case MetaTypeID_epiU16: *((epiU16*)addr) = *((epiU16*)&value); break;
            case MetaTypeID_epiU32: *((epiU32*)addr) = *((epiU32*)&value); break;
            case MetaTypeID_epiU64: *((epiU64*)addr) = *((epiU64*)&value); break;
            case MetaTypeID_epiS8: *((epiS8*)addr) = *((epiS8*)&value); break;
            case MetaTypeID_epiS16: *((epiS16*)addr) = *((epiS16*)&value); break;
            case MetaTypeID_epiS32: *((epiS32*)addr) = *((epiS32*)&value); break;
            case MetaTypeID_epiS64: *((epiS64*)addr) = *((epiS64*)&value); break;
            case MetaTypeID_epiString: *((epiString*)addr) = (const epiString&)value; break;
            case MetaTypeID_epiWString: *((epiWString*)addr) = (const epiWString&)value; break;
            case MetaTypeID_epiArray: *((epiBaseArray*)addr) = (const epiBaseArray&)value; break;
            case MetaTypeID_epiPtrArray: *((epiBaseArray*)addr) = (const epiBaseArray&)value; break;
            default: epiAssert(false, "Unexpected type id"); break;
            }
        }
    }
}

}
