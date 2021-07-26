#pragma once

//*********************************************************
//
// Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
//
//  Permission is hereby granted, free of charge, to any person obtaining a
//  copy of this software and associated documentation files (the "Software"),
//  to deal in the Software without restriction, including without limitation
//  the rights to use, copy, modify, merge, publish, distribute, sublicense,
//  and/or sell copies of the Software, and to permit persons to whom the
//  Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//  DEALINGS IN THE SOFTWARE.
//
//*********************************************************

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/Debug/gfxGPUCrashTracker.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#if EPI_NVIDIA_NSIGHT_AFTERMATH
#define VULKAN_H_ 1
#include <GFSDK_Aftermath.h>
#include <GFSDK_Aftermath_GpuCrashDump.h>
#include <GFSDK_Aftermath_GpuCrashDumpDecoding.h>

inline epiBool operator<(const GFSDK_Aftermath_ShaderDebugInfoIdentifier& lhs, const GFSDK_Aftermath_ShaderDebugInfoIdentifier& rhs)
{
    if (lhs.id[0] == rhs.id[0])
    {
        return lhs.id[1] < rhs.id[1];
    }

    return lhs.id[0] < rhs.id[0];
}

inline epiBool operator<(const GFSDK_Aftermath_ShaderHash& lhs, const GFSDK_Aftermath_ShaderHash& rhs)
{
    return lhs.hash < rhs.hash;
}

inline epiBool operator<(const GFSDK_Aftermath_ShaderInstructionsHash& lhs, const GFSDK_Aftermath_ShaderInstructionsHash& rhs)
{
    return lhs.hash < rhs.hash;
}

inline epiBool operator<(const GFSDK_Aftermath_ShaderDebugName& lhs, const GFSDK_Aftermath_ShaderDebugName& rhs)
{
    return strncmp(lhs.name, rhs.name, sizeof(lhs.name)) < 0;
}
#endif // EPI_NVIDIA_NSIGHT_AFTERMATH

EPI_NAMESPACE_BEGIN()

class gfxShaderModule;
class gfxGPUCrashTracker final : public Object
{
EPI_GENREGION_BEGIN(gfxGPUCrashTracker)

EPI_GENHIDDEN_gfxGPUCrashTracker()

public:
    constexpr static epiMetaTypeID TypeID{0x900a939e};

    enum gfxGPUCrashTracker_PIDs
    {
        PID_IsInitialized = 0x101015d0,
        PID_COUNT = 1
    };

protected:
    epiBool m_IsInitialized{false};

EPI_GENREGION_END(gfxGPUCrashTracker)

public:
    gfxGPUCrashTracker();
    gfxGPUCrashTracker(const gfxGPUCrashTracker& rhs) = delete;
    gfxGPUCrashTracker& operator=(const gfxGPUCrashTracker& rhs) = delete;
    gfxGPUCrashTracker(gfxGPUCrashTracker&& rhs) = delete;
    gfxGPUCrashTracker& operator=(gfxGPUCrashTracker&& rhs) = delete;
    ~gfxGPUCrashTracker();

    epiBool RegisterShader(const gfxShaderModule& shaderModule);

    void Reset();

#if EPI_NVIDIA_NSIGHT_AFTERMATH
protected:
    static void GpuCrashDumpCallback(const void* pGpuCrashDump, const epiU32 gpuCrashDumpSize, void* pUserData);
    static void ShaderDebugInfoCallback(const void* pShaderDebugInfo, const epiU32 shaderDebugInfoSize, void* pUserData);
    static void CrashDumpDescriptionCallback(PFN_GFSDK_Aftermath_AddGpuCrashDumpDescription addDescription, void* pUserData);
    static void ShaderDebugInfoLookupCallback(const GFSDK_Aftermath_ShaderDebugInfoIdentifier* pIdentifier, PFN_GFSDK_Aftermath_SetData setShaderDebugInfo, void* pUserData);
    static void ShaderLookupCallback(const GFSDK_Aftermath_ShaderHash* pShaderHash, PFN_GFSDK_Aftermath_SetData setShaderBinary, void* pUserData);
    static void ShaderSourceDebugInfoLookupCallback(const GFSDK_Aftermath_ShaderDebugName* pShaderDebugName, PFN_GFSDK_Aftermath_SetData setShaderBinary, void* pUserData);

    void GpuCrashDumpCallback_Internal(const void* pGpuCrashDump, const epiU32 gpuCrashDumpSize);
    void ShaderDebugInfoCallback_Internal(const void* pShaderDebugInfo, const epiU32 shaderDebugInfoSize);
    void CrashDumpDescriptionCallback_Internal(PFN_GFSDK_Aftermath_AddGpuCrashDumpDescription addDescription);
    void ShaderDebugInfoLookupCallback_Internal(const GFSDK_Aftermath_ShaderDebugInfoIdentifier* pIdentifier, PFN_GFSDK_Aftermath_SetData setShaderDebugInfo);
    void ShaderLookupCallback_Internal(const GFSDK_Aftermath_ShaderHash* pShaderHash, PFN_GFSDK_Aftermath_SetData setShaderBinary);
    void ShaderSourceDebugInfoLookupCallback_Internal(const GFSDK_Aftermath_ShaderDebugName* pShaderDebugName, PFN_GFSDK_Aftermath_SetData setShaderBinary);

protected:
    std::mutex m_Mutex;
    std::map<GFSDK_Aftermath_ShaderDebugInfoIdentifier, epiArray<epiU8>> m_ShaderDebugInfo;
    std::map<GFSDK_Aftermath_ShaderHash, epiArray<epiU8>> m_ShaderBinaries;
    std::map<GFSDK_Aftermath_ShaderDebugName, epiArray<epiU8>> m_ShaderBinariesWithDebugInfo;
#endif // EPI_NVIDIA_NSIGHT_AFTERMATH
};

EPI_NAMESPACE_END()
