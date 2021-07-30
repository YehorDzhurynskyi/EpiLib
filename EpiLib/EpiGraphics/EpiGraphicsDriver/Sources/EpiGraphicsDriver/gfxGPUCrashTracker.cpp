//*********************************************************
//
// Copyright (c) 2019-2020, NVIDIA CORPORATION. All rights reserved.
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
#include "EpiGraphicsDriver/gfxGPUCrashTracker.h"
#include "EpiGraphicsDriver/gfxGPUCrashTracker.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxShaderModule.h"

#if EPI_NVIDIA_NSIGHT_AFTERMATH
#include <fstream>

EPI_NAMESPACE_BEGIN()

gfxGPUCrashTracker::gfxGPUCrashTracker()
{
    const GFSDK_Aftermath_Result result = GFSDK_Aftermath_EnableGpuCrashDumps(GFSDK_Aftermath_Version_API,
                                                                              GFSDK_Aftermath_GpuCrashDumpWatchedApiFlags_Vulkan,
                                                                              GFSDK_Aftermath_GpuCrashDumpFeatureFlags_DeferDebugInfoCallbacks,
                                                                              &gfxGPUCrashTracker::GpuCrashDumpCallback,
                                                                              &gfxGPUCrashTracker::ShaderDebugInfoCallback,
                                                                              &gfxGPUCrashTracker::CrashDumpDescriptionCallback,
                                                                              this);

    m_IsInitialized = GFSDK_Aftermath_SUCCEED(result);
}

gfxGPUCrashTracker::~gfxGPUCrashTracker()
{
    if (GetIsInitialized())
    {
        GFSDK_Aftermath_DisableGpuCrashDumps();
    }
}

void gfxGPUCrashTracker::GpuCrashDumpCallback(const void* pGpuCrashDump, const epiU32 gpuCrashDumpSize, void* pUserData)
{
    if (gfxGPUCrashTracker* tracker = reinterpret_cast<gfxGPUCrashTracker*>(pUserData))
    {
        tracker->GpuCrashDumpCallback_Internal(pGpuCrashDump, gpuCrashDumpSize);
    }
}

void gfxGPUCrashTracker::ShaderDebugInfoCallback(const void* pShaderDebugInfo, const epiU32 shaderDebugInfoSize, void* pUserData)
{
    if (gfxGPUCrashTracker* tracker = reinterpret_cast<gfxGPUCrashTracker*>(pUserData))
    {
        tracker->ShaderDebugInfoCallback_Internal(pShaderDebugInfo, shaderDebugInfoSize);
    }
}

void gfxGPUCrashTracker::CrashDumpDescriptionCallback(PFN_GFSDK_Aftermath_AddGpuCrashDumpDescription addDescription, void* pUserData)
{
    if (gfxGPUCrashTracker* tracker = reinterpret_cast<gfxGPUCrashTracker*>(pUserData))
    {
        tracker->CrashDumpDescriptionCallback_Internal(addDescription);
    }
}

void gfxGPUCrashTracker::ShaderDebugInfoLookupCallback(const GFSDK_Aftermath_ShaderDebugInfoIdentifier* pIdentifier, PFN_GFSDK_Aftermath_SetData setShaderDebugInfo, void* pUserData)
{
    if (gfxGPUCrashTracker* tracker = reinterpret_cast<gfxGPUCrashTracker*>(pUserData))
    {
        tracker->ShaderDebugInfoLookupCallback_Internal(pIdentifier, setShaderDebugInfo);
    }
}

void gfxGPUCrashTracker::ShaderLookupCallback(const GFSDK_Aftermath_ShaderHash* pShaderHash, PFN_GFSDK_Aftermath_SetData setShaderBinary, void* pUserData)
{
    if (gfxGPUCrashTracker* tracker = reinterpret_cast<gfxGPUCrashTracker*>(pUserData))
    {
        tracker->ShaderLookupCallback_Internal(pShaderHash, setShaderBinary);
    }
}

void gfxGPUCrashTracker::ShaderSourceDebugInfoLookupCallback(const GFSDK_Aftermath_ShaderDebugName* pShaderDebugName, PFN_GFSDK_Aftermath_SetData setShaderBinary, void* pUserData)
{
    if (gfxGPUCrashTracker* tracker = reinterpret_cast<gfxGPUCrashTracker*>(pUserData))
    {
        tracker->ShaderSourceDebugInfoLookupCallback_Internal(pShaderDebugName, setShaderBinary);
    }
}

void gfxGPUCrashTracker::GpuCrashDumpCallback_Internal(const void* pGpuCrashDump, const epiU32 gpuCrashDumpSize)
{
    // TODO: handle leaks: decoder couldn't be destroyed in case intermediate function fail
    std::lock_guard<std::mutex> lk(m_Mutex);

    GFSDK_Aftermath_GpuCrashDump_Decoder decoder = {};
    {
        const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_CreateDecoder(GFSDK_Aftermath_Version_API,
                                                                                         pGpuCrashDump,
                                                                                         gpuCrashDumpSize,
                                                                                         &decoder);
        if (!GFSDK_Aftermath_SUCCEED(result))
        {
            epiLogError("Failed to call 'GFSDK_Aftermath_GpuCrashDump_CreateDecoder'!");
            return;
        }
    }

    GFSDK_Aftermath_GpuCrashDump_BaseInfo baseInfo = {};
    {
        const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_GetBaseInfo(decoder, &baseInfo);
        if (!GFSDK_Aftermath_SUCCEED(result))
        {
            epiLogError("Failed to call 'GFSDK_Aftermath_GpuCrashDump_GetBaseInfo'!");
            return;
        }
    }

    epiU32 applicationNameLength = 0;
    {
        const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_GetDescriptionSize(decoder,
                                                                                              GFSDK_Aftermath_GpuCrashDumpDescriptionKey_ApplicationName,
                                                                                              &applicationNameLength);
        if (!GFSDK_Aftermath_SUCCEED(result))
        {
            epiLogError("Failed to call 'GFSDK_Aftermath_GpuCrashDump_GetDescriptionSize'!");
            return;
        }
    }

    std::string crashDumpFileName;
    {
        std::vector<epiChar> applicationName(applicationNameLength, '\0');
        const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_GetDescription(decoder,
                                                                                          GFSDK_Aftermath_GpuCrashDumpDescriptionKey_ApplicationName,
                                                                                          epiU32(applicationName.size()),
                                                                                          applicationName.data());

        // Create a unique file name for writing the crash dump data to a file.
        // Note: due to an Nsight Aftermath bug (will be fixed in an upcoming
        // driver release) we may see redundant crash dumps. As a workaround,
        // attach a unique count to each generated file name.
        static epiS32 count = 0;
        const std::string baseFileName =
            std::string(applicationName.data())
            + "-"
            + std::to_string(baseInfo.pid)
            + "-"
            + std::to_string(++count);

        crashDumpFileName = baseFileName + ".nv-gpudmp";
        std::ofstream dumpFile(crashDumpFileName, std::ios::out | std::ios::binary);
        if (dumpFile)
        {
            dumpFile.write((const epiChar*)pGpuCrashDump, gpuCrashDumpSize);
            dumpFile.close();
        }
    }

    {
        epiU32 jsonSize = 0;
        {
            const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_GenerateJSON(decoder,
                                                                                            GFSDK_Aftermath_GpuCrashDumpDecoderFlags_ALL_INFO,
                                                                                            GFSDK_Aftermath_GpuCrashDumpFormatterFlags_NONE,
                                                                                            &gfxGPUCrashTracker::ShaderDebugInfoLookupCallback,
                                                                                            &gfxGPUCrashTracker::ShaderLookupCallback,
                                                                                            nullptr, // TODO: provide callback
                                                                                            &gfxGPUCrashTracker::ShaderSourceDebugInfoLookupCallback,
                                                                                            this,
                                                                                            &jsonSize);
            if (!GFSDK_Aftermath_SUCCEED(result))
            {
                epiLogError("Failed to call 'GFSDK_Aftermath_GpuCrashDump_GenerateJSON'!");
                return;
            }
        }

        std::vector<epiChar> json(jsonSize);
        {
            const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_GetJSON(decoder,
                                                                                       epiU32(json.size()),
                                                                                       json.data());
            if (!GFSDK_Aftermath_SUCCEED(result))
            {
                epiLogError("Failed to call 'GFSDK_Aftermath_GpuCrashDump_GetJSON'!");
                return;
            }
        }

        const std::string jsonFileName = crashDumpFileName + ".json";
        std::ofstream jsonFile(jsonFileName, std::ios::out | std::ios::binary);
        if (jsonFile)
        {
            jsonFile.write(json.data(), json.size());
            jsonFile.close();
        }

        const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GpuCrashDump_DestroyDecoder(decoder);
        if (!GFSDK_Aftermath_SUCCEED(result))
        {
            epiLogError("Failed to call 'GFSDK_Aftermath_GpuCrashDump_DestroyDecoder'!");
            return;
        }
    }
}

void gfxGPUCrashTracker::ShaderDebugInfoCallback_Internal(const void* pShaderDebugInfo, const epiU32 shaderDebugInfoSize)
{
    std::lock_guard<std::mutex> lk(m_Mutex);

    GFSDK_Aftermath_ShaderDebugInfoIdentifier identifier = {};
    const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GetShaderDebugInfoIdentifier(GFSDK_Aftermath_Version_API,
                                                                                       pShaderDebugInfo,
                                                                                       shaderDebugInfoSize,
                                                                                       &identifier);
    if (!GFSDK_Aftermath_SUCCEED(result))
    {
        epiLogError("Failed to call 'GFSDK_Aftermath_GetShaderDebugInfoIdentifier'!");
        return;
    }

    epiArray<epiU8> data((epiU8*)pShaderDebugInfo, (epiU8*)pShaderDebugInfo + shaderDebugInfoSize);
    m_ShaderDebugInfo[identifier].swap(data);

    // Create a unique file name.
    const std::string filePath = "shader-" + std::to_string(identifier.id[0]) + "-" + std::to_string(identifier.id[0]) + ".nvdbg";

    std::ofstream f(filePath, std::ios::out | std::ios::binary);
    if (f)
    {
        f.write((const epiChar*)pShaderDebugInfo, shaderDebugInfoSize);
    }
}

void gfxGPUCrashTracker::CrashDumpDescriptionCallback_Internal(PFN_GFSDK_Aftermath_AddGpuCrashDumpDescription addDescription)
{
#if 0
    // Add some basic description about the crash. This is called after the GPU crash happens, but before
    // the actual GPU crash dump callback. The provided data is included in the crash dump and can be
    // retrieved using GFSDK_Aftermath_GpuCrashDump_GetDescription().
    //
    // For example:
    // addDescription(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_ApplicationName, "VkHelloNsightAftermath");
    // addDescription(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_ApplicationVersion, "v1.0");
    // addDescription(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_UserDefined, "This is a GPU crash dump example.");
    // addDescription(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_UserDefined + 1, "Engine State: Rendering.");
    // addDescription(GFSDK_Aftermath_GpuCrashDumpDescriptionKey_UserDefined + 2, "More user-defined information...");
#endif
}

void gfxGPUCrashTracker::ShaderDebugInfoLookupCallback_Internal(const GFSDK_Aftermath_ShaderDebugInfoIdentifier* pIdentifier, PFN_GFSDK_Aftermath_SetData setShaderDebugInfo)
{
    if (pIdentifier == nullptr)
    {
        return;
    }

    auto debugInfoIt = m_ShaderDebugInfo.find(*pIdentifier);
    if (debugInfoIt == m_ShaderDebugInfo.end())
    {
        return;
    }

    setShaderDebugInfo(debugInfoIt->second.data(), epiU32(debugInfoIt->second.Size()));
}

void gfxGPUCrashTracker::ShaderLookupCallback_Internal(const GFSDK_Aftermath_ShaderHash* pShaderHash, PFN_GFSDK_Aftermath_SetData setShaderBinary)
{
    if (pShaderHash == nullptr)
    {
        return;
    }

    const auto shaderIt = m_ShaderBinaries.find(*pShaderHash);
    if (shaderIt == m_ShaderBinaries.end())
    {
        return;
    }

    epiArray<epiU8>& shaderBinary = shaderIt->second;
    setShaderBinary(shaderBinary.data(), epiU32(shaderBinary.Size()));
}

void gfxGPUCrashTracker::ShaderSourceDebugInfoLookupCallback_Internal(const GFSDK_Aftermath_ShaderDebugName* pShaderDebugName, PFN_GFSDK_Aftermath_SetData setShaderBinary)
{
    if (pShaderDebugName == nullptr)
    {
        return;
    }

    const auto shaderIt = m_ShaderBinariesWithDebugInfo.find(*pShaderDebugName);
    if (shaderIt == m_ShaderBinariesWithDebugInfo.end())
    {
        return;
    }

    epiArray<epiU8>& shaderBinary = shaderIt->second;
    setShaderBinary(shaderBinary.data(), epiU32(shaderBinary.Size()));
}

epiBool gfxGPUCrashTracker::RegisterShader(const gfxShaderModule& shaderModule)
{
    if (!shaderModule.HasImpl())
    {
        epiLogWarn("Failed to register a Shader! The provided Shader has no implementation!");
        return false;
    }

    if (const gfxShaderModuleFrontend frontend = shaderModule.GetFrontend(); frontend != gfxShaderModuleFrontend::SPIRV)
    {
        epiLogWarn("Failed to register a Shader! Shader's frontend should be SPIRV, but `{}` provided!", frontend); // TODO: str repr
        return false;
    }

    epiArray<epiU8> code = shaderModule.GetCode();
    const GFSDK_Aftermath_SpirvCode spirvCode{code.data(), epiU32(code.Size())};

    GFSDK_Aftermath_ShaderHash shaderHash;
    const GFSDK_Aftermath_Result result = GFSDK_Aftermath_GetShaderHashSpirv(GFSDK_Aftermath_Version_API,
                                                                             &spirvCode,
                                                                             &shaderHash);

    if (!GFSDK_Aftermath_SUCCEED(result))
    {
        epiLogError("Failed to call 'GFSDK_Aftermath_GetShaderHashSpirv'!");
        return false;
    }

    m_ShaderBinaries[shaderHash].swap(code);
}

void gfxGPUCrashTracker::Reset()
{
    m_ShaderDebugInfo.clear();
    m_ShaderBinaries.clear();
    m_ShaderBinariesWithDebugInfo.clear();
}
#else
gfxGPUCrashTracker::~gfxGPUCrashTracker() = default;
epiBool gfxGPUCrashTracker::Init() { return false; }
epiBool gfxGPUCrashTracker::RegisterShader(const gfxShader& shader) { return false; }
#endif // EPI_NSIGHT_AFTERMATH

EPI_NAMESPACE_END()
