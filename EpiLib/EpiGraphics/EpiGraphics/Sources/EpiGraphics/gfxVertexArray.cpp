EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexArray.cxx"
EPI_GENREGION_END(include)

#include <glad/glad.h>

EPI_NAMESPACE_BEGIN()

gfxVertexArray::gfxVertexArray()
{
    Create();
}

gfxVertexArray::~gfxVertexArray()
{
    if (GetIsCreated())
    {
        Destroy();
    }
}

gfxVertexArray::gfxVertexArray(gfxVertexArray&& rhs)
{
    m_ID = rhs.m_ID;
    rhs.m_ID = 0;
}

gfxVertexArray& gfxVertexArray::operator=(gfxVertexArray&& rhs)
{
    m_ID = rhs.m_ID;
    rhs.m_ID = 0;

    return *this;
}

void gfxVertexArray::Create()
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed vertex array");

    glGenVertexArrays(1, &m_ID);
}

void gfxVertexArray::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex array");

    glDeleteVertexArrays(1, &m_ID);
    m_ID = 0;
}

epiBool gfxVertexArray::GetIsCreated_Callback() const
{
    return m_ID != 0;
}

void gfxVertexArray::Bind()
{
    epiExpect(GetIsCreated(), "A vertex array expected to be created");

    super::Bind();
    glBindVertexArray(m_ID);
}

void gfxVertexArray::UnBind()
{
    epiExpect(GetIsCreated(), "A vertex array expected to be created");

    super::UnBind();
    glBindVertexArray(0);
}

EPI_NAMESPACE_END()
