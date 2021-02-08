#include "EpiGraphicsDriverGL/gfxVertexArrayImplGL.h"

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

gfxVertexArrayImplGL::gfxVertexArrayImplGL(gfxVertexArrayImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    rhs.m_ID = 0;
}

gfxVertexArrayImplGL& gfxVertexArrayImplGL::operator=(gfxVertexArrayImplGL&& rhs)
{
    m_ID = rhs.m_ID;
    rhs.m_ID = 0;

    return *this;
}

void gfxVertexArrayImplGL::Create()
{
    glGenVertexArrays(1, &m_ID);
}

void gfxVertexArrayImplGL::Destroy()
{
    glDeleteVertexArrays(1, &m_ID);
    m_ID = 0;
}

epiBool gfxVertexArrayImplGL::GetIsCreated() const
{
    return m_ID != 0;
}

epiU32 gfxVertexArrayImplGL::GetID() const
{
    return m_ID;
}

void gfxVertexArrayImplGL::Bind()
{
    glBindVertexArray(m_ID);
}

void gfxVertexArrayImplGL::UnBind()
{
    glBindVertexArray(0);
}

} // namespace internalgfx

EPI_NAMESPACE_END()
