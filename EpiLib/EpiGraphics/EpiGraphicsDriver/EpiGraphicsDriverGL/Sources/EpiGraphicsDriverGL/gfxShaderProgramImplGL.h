#pragma once

#include "EpiGraphicsDriverAPI/EpiGraphicsDriverAPI.h"

EPI_NAMESPACE_BEGIN()

class gfxShaderImplGL : public gfxShaderImpl
{
public:
    gfxShaderImplGL() = default;
    gfxShaderImplGL(const gfxShaderImplGL& rhs) = delete;
    gfxShaderImplGL& operator=(const gfxShaderImplGL& rhs) = delete;
    gfxShaderImplGL(gfxShaderImplGL&& rhs);
    gfxShaderImplGL& operator=(gfxShaderImplGL&& rhs);
    ~gfxShaderImplGL() override = default;

    void CreateFromSource(const epiChar* source, gfxShaderType type) override;
    void Destroy() override;

    epiBool GetIsCreated() const override;
    epiU32 GetID() const override;
    gfxShaderType GetType() const override;

protected:
    epiU32 m_ID{0};
    gfxShaderType m_Type{gfxShaderType::None};
};

class gfxShaderProgramImplGL : public gfxShaderProgramImpl
{
public:
    gfxShaderProgramImplGL() = default;
    gfxShaderProgramImplGL(const gfxShaderProgramImplGL& rhs) = delete;
    gfxShaderProgramImplGL& operator=(const gfxShaderProgramImplGL& rhs) = delete;
    gfxShaderProgramImplGL(gfxShaderProgramImplGL&& rhs);
    gfxShaderProgramImplGL& operator=(gfxShaderProgramImplGL&& rhs);
    ~gfxShaderProgramImplGL() override = default;

    void Create() override;
    void Destroy() override;

    epiBool GetIsCreated() const override;
    epiU32 GetID() const override;

    void ShaderAttach(const gfxShaderImpl& shader) override;
    void ShaderDettach(gfxShaderType type) override;

    void Build() override;

    void Bind() override;
    void UnBind() override;

protected:
    epiU32 m_ID{0};
    const gfxShaderImplGL* m_ShaderVertex{nullptr};
    const gfxShaderImplGL* m_ShaderGeometry{nullptr};
    const gfxShaderImplGL* m_ShaderPixel{nullptr};
};


EPI_NAMESPACE_END()
