#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxShaderProgram.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxShader final : public Object
{
EPI_GENREGION_BEGIN(gfxShader)

EPI_GENHIDDEN_gfxShader()

public:
    constexpr static epiMetaTypeID TypeID{0x5e95f50e};

    enum gfxShader_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_Type = 0x2cecf817,
        PID_COUNT = 3
    };

protected:
    epiBool GetIsCreated_Callback() const;
    epiU32 GetID_Callback() const;
    gfxShaderType GetType_Callback() const;

EPI_GENREGION_END(gfxShader)

public:
    friend class gfxShaderProgram;

public:
    gfxShader() = default;
    gfxShader(const gfxShader& rhs) = delete;
    gfxShader& operator=(const gfxShader& rhs) = delete;
    gfxShader(gfxShader&& rhs) = default;
    gfxShader& operator=(gfxShader&& rhs) = default;
    ~gfxShader();

public:
    void CreateFromSource(const epiChar* source, gfxShaderType type);
    void Destroy();

protected:
    std::unique_ptr<gfxShaderImpl> m_Impl;
};

class gfxShaderProgram final : public gfxBindable
{
EPI_GENREGION_BEGIN(gfxShaderProgram)

EPI_GENHIDDEN_gfxShaderProgram()

public:
    constexpr static epiMetaTypeID TypeID{0x7a046d1e};

    enum gfxShaderProgram_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ID = 0x11d3633a,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;
    epiU32 GetID_Callback() const;

EPI_GENREGION_END(gfxShaderProgram)

public:
    gfxShaderProgram();
    gfxShaderProgram(const gfxShaderProgram& rhs) = delete;
    gfxShaderProgram& operator=(const gfxShaderProgram& rhs) = delete;
    gfxShaderProgram(gfxShaderProgram&& rhs) = default;
    gfxShaderProgram& operator=(gfxShaderProgram&& rhs) = default;
    ~gfxShaderProgram();

public:
    void Create();
    void Destroy();

    void ShaderAttach(const gfxShader& shader);
    void ShaderDettach(gfxShaderType type);

    void Build();

    void Bind() override;
    void UnBind() override;

protected:
    std::unique_ptr<gfxShaderProgramImpl> m_Impl;
};

EPI_NAMESPACE_END()
