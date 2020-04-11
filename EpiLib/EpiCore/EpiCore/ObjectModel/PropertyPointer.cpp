#include "EpiCore/pch.h"
#if 0
#include "PropertyPointer.h"

using SetCallback_epiChar   = void (*)(epiChar);
using SetCallback_epiBool   = void (*)(epiBool);
using SetCallback_epiByte   = void (*)(epiByte);
using SetCallback_epiFloat  = void (*)(epiFloat);
using SetCallback_epiDouble = void (*)(epiDouble);
using SetCallback_epiSize_t = void (*)(epiSize_t);
using SetCallback_epiString = void (*)(epiString);
using SetCallback_epiU8     = void (*)(epiU8);
using SetCallback_epiU16    = void (*)(epiU16);
using SetCallback_epiU32    = void (*)(epiU32);
using SetCallback_epiU64    = void (*)(epiU64);
using SetCallback_epiS8     = void (*)(epiS8);
using SetCallback_epiS16    = void (*)(epiS16);
using SetCallback_epiS32    = void (*)(epiS32);
using SetCallback_epiS64    = void (*)(epiS64);

namespace epi
{

void* PropertyPointer::Get()
{

}

void PropertyPointer::Set(void* value)
{
    void* ptrWrite = nullptr;

    const MetaTypeID typeID = MetaTypeID_epiFloat;
    switch (typeID)
    {
    case MetaTypeID_epiChar: ((SetCallback_epiChar)ptrWrite)(reinterpret_cast<epiChar>(value)); break;
    case MetaTypeID_epiBool: ((SetCallback_epiBool)ptrWrite)(reinterpret_cast<epiBool>(value)); break;
    case MetaTypeID_epiByte: ((SetCallback_epiByte)ptrWrite)(reinterpret_cast<epiByte>(value)); break;
    case MetaTypeID_epiFloat: ((SetCallback_epiFloat)ptrWrite)(reinterpret_cast<epiFloat>(value)); break;
    case MetaTypeID_epiDouble: ((SetCallback_epiDouble)ptrWrite)(reinterpret_cast<epiDouble>(value)); break;
    case MetaTypeID_epiSize_t: ((SetCallback_epiSize_t)ptrWrite)(reinterpret_cast<epiSize_t>(value)); break;
    case MetaTypeID_epiU8: ((SetCallback_epiU8)ptrWrite)(reinterpret_cast<epiU8>(value)); break;
    case MetaTypeID_epiU16: ((SetCallback_epiU16)ptrWrite)(reinterpret_cast<epiU16>(value)); break;
    case MetaTypeID_epiU32: ((SetCallback_epiU32)ptrWrite)(reinterpret_cast<epiU32>(value)); break;
    case MetaTypeID_epiU64: ((SetCallback_epiU64)ptrWrite)(reinterpret_cast<epiU64>(value)); break;
    case MetaTypeID_epiS8: ((SetCallback_epiS8)ptrWrite)(reinterpret_cast<epiS8>(value)); break;
    case MetaTypeID_epiS16: ((SetCallback_epiS16)ptrWrite)(reinterpret_cast<epiS16>(value)); break;
    case MetaTypeID_epiS32: ((SetCallback_epiS32)ptrWrite)(reinterpret_cast<epiS32>(value)); break;
    case MetaTypeID_epiS64: ((SetCallback_epiS64)ptrWrite)(reinterpret_cast<epiS64>(value)); break;
    case MetaTypeID_epiString: ((SetCallback_epiString)ptrWrite)(reinterpret_cast<const epiString&>(value)); break;
    default: epiAssert(false, "Unexpected type id"); break;
    }
}

}
#endif
