#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexArray.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxVertexArray::gfxVertexArray()
{
    Create();
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

gfxVertexArray::~gfxVertexArray()
{
    Destroy();
}

void gfxVertexArray::Create()
{
    glGenVertexArrays(1, &m_ID);
}

void gfxVertexArray::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex array");

    if (GetIsCreated())
    {
        glDeleteVertexArrays(1, &m_ID);
        m_ID = 0;
    }
}

epiBool gfxVertexArray::GetIsCreated_Callback() const
{
    return m_ID != 0;
}

void gfxVertexArray::Bind()
{
    epiExpect(GetIsCreated(), "A vertex array expected to be created");
    glBindVertexArray(m_ID);
}

void gfxVertexArray::UnBind()
{
    epiExpect(GetIsCreated(), "A vertex array expected to be created");
    glBindVertexArray(0);
}

EPI_NAMESPACE_END()
