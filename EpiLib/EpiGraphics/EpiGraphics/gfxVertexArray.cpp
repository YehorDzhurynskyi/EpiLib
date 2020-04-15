#include "EpiGraphics/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxVertexArray.h"
#include "EpiGraphics/gfxVertexArray.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

void gfxVertexArray::Bind()
{
    glBindVertexArray(m_ID);
}

void gfxVertexArray::UnBind()
{
    glBindVertexArray(0);
}

EPI_NAMESPACE_END()
