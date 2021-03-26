#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxVertexArray.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxVertexArrayImpl;

} // namespace internalgfx

class gfxVertexArray : public Object
{
EPI_GENREGION_BEGIN(gfxVertexArray)

EPI_GENHIDDEN_gfxVertexArray()

public:
    constexpr static epiMetaTypeID TypeID{0x7d61d88d};

    enum gfxVertexArray_PIDs
    {
        PID_IsCreated = 0x560b66db,
        PID_COUNT = 1
    };

protected:
    epiBool GetIsCreated_Callback() const;

EPI_GENREGION_END(gfxVertexArray)

public:
    gfxVertexArray() = default;
    explicit gfxVertexArray(internalgfx::gfxVertexArrayImpl* impl);
    gfxVertexArray(const gfxVertexArray& rhs) = delete;
    gfxVertexArray& operator=(const gfxVertexArray& rhs) = delete;
    gfxVertexArray(gfxVertexArray&& rhs);
    gfxVertexArray& operator=(gfxVertexArray&& rhs);
    ~gfxVertexArray();

protected:
    internalgfx::gfxVertexArrayImpl* m_Impl{nullptr};
};

EPI_NAMESPACE_END()
