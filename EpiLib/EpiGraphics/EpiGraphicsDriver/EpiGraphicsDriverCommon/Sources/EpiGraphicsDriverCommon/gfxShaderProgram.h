#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxShaderProgram.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

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
        PID_Type = 0x2cecf817,
        PID_COUNT = 2
    };

protected:
    epiBool GetIsCreated_Callback() const;
    gfxShaderType GetType_Callback() const;

EPI_GENREGION_END(gfxShader)

public:
    friend class gfxShaderProgram;

public:
    gfxShader() = default;
    explicit gfxShader(internalgfx::gfxShaderImpl* impl);
    gfxShader(const gfxShader& rhs) = delete;
    gfxShader& operator=(const gfxShader& rhs) = delete;
    gfxShader(gfxShader&& rhs);
    gfxShader& operator=(gfxShader&& rhs);
    ~gfxShader();

public:
    epiBool InitFromSource(const epiChar* source, gfxShaderType type, const epiChar* entryPoint = "main");

protected:
    internalgfx::gfxShaderImpl* m_Impl{nullptr};
};

class gfxShaderProgramCreateInfo : public Object
{
EPI_GENREGION_BEGIN(gfxShaderProgramCreateInfo)

EPI_GENHIDDEN_gfxShaderProgramCreateInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x2e1f76a0};

    enum gfxShaderProgramCreateInfo_PIDs
    {
        PID_IsEmpty = 0xae6d7566,
        PID_Vertex = 0xee5d7c03,
        PID_Geometry = 0x6c246cfd,
        PID_Fragment = 0x32db77ba,
        PID_COUNT = 4
    };

protected:
    epiBool GetIsEmpty_Callback() const;

protected:
    gfxShader* m_Vertex{nullptr};
    gfxShader* m_Geometry{nullptr};
    gfxShader* m_Fragment{nullptr};

EPI_GENREGION_END(gfxShaderProgramCreateInfo)
};

class gfxShaderProgram final : public Object
{
EPI_GENREGION_BEGIN(gfxShaderProgram)

EPI_GENHIDDEN_gfxShaderProgram()

public:
    constexpr static epiMetaTypeID TypeID{0x7a046d1e};

    enum gfxShaderProgram_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_COUNT = 1
    };

protected:
    epiBool GetIsCreated_Callback() const;

EPI_GENREGION_END(gfxShaderProgram)

public:
    friend class gfxDevice;

public:
    gfxShaderProgram() = default;
    explicit gfxShaderProgram(internalgfx::gfxShaderProgramImpl* impl);
    gfxShaderProgram(const gfxShaderProgram& rhs) = delete;
    gfxShaderProgram& operator=(const gfxShaderProgram& rhs) = delete;
    gfxShaderProgram(gfxShaderProgram&& rhs);
    gfxShaderProgram& operator=(gfxShaderProgram&& rhs);
    ~gfxShaderProgram();

protected:
    internalgfx::gfxShaderProgramImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
