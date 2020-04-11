#include "EpiCore/pch.h"
#include "PropertyPointer.h"

#include "Object.h"

namespace epi
{

#define SetCallback(_x) ((void (*)(Object*, _x))m_Meta.m_PtrWrite)(self, *((_x*)&value))
#define SetCallback_Ref(_x) ((void (*)(Object*, const _x&))m_Meta.m_PtrWrite)(self, (const _x&)value)

#define GetCallback(_x) { _x v = ((_x (*)(Object*))m_Meta.m_PtrRead)(self); value = (void*)*((epiSize_t*)&v); }
#define GetCallback_Ref(_x) { const _x& v = ((const _x& (*)(Object*))m_Meta.m_PtrRead)(self); value = (void*)&v; }

void* PropertyPointer::Get(Object* self)
{
    void* value = nullptr;

    if (m_Meta.m_Flags.HasCallbackRead)
    {
        switch (m_Meta.m_TypeID)
        {
        case MetaTypeID_epiChar: GetCallback(epiChar); break;
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
        default: epiAssert(false, "Unexpected type id"); break;
        }
    }
    else
    {
        void* addr = (epiByte*)self + (size_t)m_Meta.m_PtrRead;
        switch (m_Meta.m_TypeID)
        {
        case MetaTypeID_epiChar: value = (void*)*((epiChar*)addr); break;
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
        default: epiAssert(false, "Unexpected type id"); break;
        }
    }

    return value;
}

void PropertyPointer::Set(Object* self, void* value)
{
    if (m_Meta.m_Flags.HasCallbackWrite)
    {
        switch (m_Meta.m_TypeID)
        {
        case MetaTypeID_epiChar: SetCallback(epiChar); break;
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
        default: epiAssert(false, "Unexpected type id"); break;
        }
    }
    else
    {
        void* addr = (epiByte*)self + (size_t)m_Meta.m_PtrWrite;
        switch (m_Meta.m_TypeID)
        {
        case MetaTypeID_epiChar: *((epiChar*)addr) = *((epiChar*)&value); break;
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
        default: epiAssert(false, "Unexpected type id"); break;
        }
    }
}

}
