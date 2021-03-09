#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxShaderProgram.hxx"
EPI_GENREGION_END(include)

#include "EpiGraphics/gfxBindable.h"

#include "EpiGraphicsDriverCommon/gfxEnum.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxShaderImpl;
class gfxShaderProgramImpl;

} // namespace internalgfx

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
    gfxShader(gfxShader&& rhs);
    gfxShader& operator=(gfxShader&& rhs);
    ~gfxShader();

public:
    void CreateFromSource(const epiChar* source, gfxShaderType type);
    void Destroy();

protected:
    internalgfx::gfxShaderImpl* m_Impl{nullptr};
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

    void Texture(const epiChar* name, epiU32 value);

    template<typename T>
    void Uniform(const epiChar* name, const T& value);

    void UniformFloat(const epiChar* name, epiFloat value);
    void UniformVec2f(const epiChar* name, const epiVec2f& value);
    void UniformVec3f(const epiChar* name, const epiVec3f& value);
    void UniformVec4f(const epiChar* name, const epiVec4f& value);
    void UniformMat4x4f(const epiChar* name, const epiMat4x4f& value, epiBool transpose = false);

    void UniformS32(const epiChar* name, epiS32 value);
    void UniformVec2s(const epiChar* name, const epiVec2s& value);
    void UniformVec3s(const epiChar* name, const epiVec3s& value);
    void UniformVec4s(const epiChar* name, const epiVec4s& value);

    void UniformU32(const epiChar* name, epiU32 value);
    void UniformVec2u(const epiChar* name, const epiVec2u& value);
    void UniformVec3u(const epiChar* name, const epiVec3u& value);
    void UniformVec4u(const epiChar* name, const epiVec4u& value);

protected:
    internalgfx::gfxShaderProgramImpl* m_Impl{nullptr};
};

template<typename T>
void gfxShaderProgram::Uniform(const epiChar* name, const T& value)
{
    using T_ = std::decay_t<T>;

    if constexpr (std::is_same_v<epiFloat, T_>)
    {
        UniformFloat(name, value);
    }
    else if constexpr (std::is_same_v<epiVec2f, T_>)
    {
        UniformVec2f(name, value);
    }
    else if constexpr (std::is_same_v<epiVec3f, T_>)
    {
        UniformVec3f(name, value);
    }
    else if constexpr (std::is_same_v<epiVec4f, T_>)
    {
        UniformVec4f(name, value);
    }
    else if constexpr (std::is_same_v<epiMat4x4f, T_>)
    {
        UniformMat4x4f(name, value);
    }
    else if constexpr (std::is_same_v<epiS32, T_>)
    {
        UniformS32(name, value);
    }
    else if constexpr (std::is_same_v<epiVec2s, T_>)
    {
        UniformVec2s(name, value);
    }
    else if constexpr (std::is_same_v<epiVec3s, T_>)
    {
        UniformVec3s(name, value);
    }
    else if constexpr (std::is_same_v<epiVec4s, T_>)
    {
        UniformVec4s(name, value);
    }
    else if constexpr (std::is_same_v<epiU32, T_>)
    {
        UniformU32(name, value);
    }
    else if constexpr (std::is_same_v<epiVec2u, T_>)
    {
        UniformVec2u(name, value);
    }
    else if constexpr (std::is_same_v<epiVec3u, T_>)
    {
        UniformVec3u(name, value);
    }
    else if constexpr (std::is_same_v<epiVec4u, T_>)
    {
        UniformVec4u(name, value);
    }
    else
    {
        static_assert(false);
    }
}

EPI_NAMESPACE_END()
