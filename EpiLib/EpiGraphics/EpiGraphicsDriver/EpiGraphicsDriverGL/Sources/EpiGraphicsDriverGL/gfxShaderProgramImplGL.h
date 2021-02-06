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

    void UniformFloat(const epiChar* name, epiFloat value) override;
    void UniformVec2f(const epiChar* name, const epiVec2f& value) override;
    void UniformVec3f(const epiChar* name, const epiVec3f& value) override;
    void UniformVec4f(const epiChar* name, const epiVec4f& value) override;
    void UniformMat4x4f(const epiChar* name, const epiMat4x4f& value, epiBool transpose) override;

    void UniformS32(const epiChar* name, epiS32 value) override;
    void UniformVec2s(const epiChar* name, const epiVec2s& value) override;
    void UniformVec3s(const epiChar* name, const epiVec3s& value) override;
    void UniformVec4s(const epiChar* name, const epiVec4s& value) override;

    void UniformU32(const epiChar* name, epiU32 value) override;
    void UniformVec2u(const epiChar* name, const epiVec2u& value) override;
    void UniformVec3u(const epiChar* name, const epiVec3u& value) override;
    void UniformVec4u(const epiChar* name, const epiVec4u& value) override;

protected:
    epiU32 m_ID{0};
    const gfxShaderImplGL* m_ShaderVertex{nullptr};
    const gfxShaderImplGL* m_ShaderGeometry{nullptr};
    const gfxShaderImplGL* m_ShaderPixel{nullptr};
};


EPI_NAMESPACE_END()
