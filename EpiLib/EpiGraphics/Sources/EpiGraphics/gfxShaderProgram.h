#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxShaderProgram.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

EPI_NAMESPACE_BEGIN()

enum class gfxShaderType
{
EPI_GENREGION_BEGIN(gfxShaderType)
    None = 0,
    Vertex = 1,
    Geometry = 2,
    Pixel = 3
EPI_GENREGION_END(gfxShaderType)
};

class gfxShader final : public Object
{
EPI_GENREGION_BEGIN(gfxShader)

EPI_GENHIDDEN_gfxShader()

public:
    constexpr static epiMetaTypeID TypeID{0x5e95f50e};

    enum gfxShader_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_ShaderID = 0xa24fee76,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;

protected:
    epiU32 m_ShaderID{0};

EPI_GENREGION_END(gfxShader)

public:
    gfxShader() = default;
    gfxShader(const gfxShader& rhs) = delete;
    gfxShader& operator=(const gfxShader& rhs) = delete;
    gfxShader(gfxShader&& rhs);
    gfxShader& operator=(gfxShader&& rhs);
    ~gfxShader();

public:
    void CreateFromSource(const epiChar* source, gfxShaderType type);
    void Destroy();

    gfxShaderType GetType() const { return m_Type; }

protected:
    gfxShaderType m_Type{gfxShaderType::None};
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
        PID_ProgramID = 0x2accaa4,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;

protected:
    epiU32 m_ProgramID{0};

EPI_GENREGION_END(gfxShaderProgram)

public:
    gfxShaderProgram();
    gfxShaderProgram(const gfxShaderProgram& rhs) = delete;
    gfxShaderProgram& operator=(const gfxShaderProgram& rhs) = delete;
    gfxShaderProgram(gfxShaderProgram&& rhs);
    gfxShaderProgram& operator=(gfxShaderProgram&& rhs);
    ~gfxShaderProgram();

public:
    void Create();
    void Destroy();

    void ShaderAttach(const gfxShader& shader);
    void ShaderDettach(gfxShaderType type);

    void Build();

    void Bind() override;
    void UnBind() override;

private:
    const gfxShader* m_ShaderVertex{nullptr};
    const gfxShader* m_ShaderGeometry{nullptr};
    const gfxShader* m_ShaderPixel{nullptr};
};

EPI_NAMESPACE_END()
