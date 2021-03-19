EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxVertexArray.h"
#include "EpiGraphicsDriverCommon/gfxVertexArray.cxx"
EPI_GENREGION_END(include)

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

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

void gfxVertexArray::Create()
{
    epiExpect(!GetIsCreated(), "Create method should be called on destroyed vertex array");

    m_Impl->Create();
}

void gfxVertexArray::Destroy()
{
    epiExpect(GetIsCreated(), "Destroy method should be called on already created vertex array");

    m_Impl->Destroy();
}

epiBool gfxVertexArray::GetIsCreated_Callback() const
{
    return m_Impl->GetIsCreated();
}

epiU32 gfxVertexArray::GetID_Callback() const
{
    return m_Impl->GetID();
}

void gfxVertexArray::Bind()
{
    epiExpect(GetIsCreated(), "A vertex array expected to be created");

    super::Bind();

    m_Impl->Bind();
}

void gfxVertexArray::UnBind()
{
    epiExpect(GetIsCreated(), "A vertex array expected to be created");

    super::UnBind();

    m_Impl->UnBind();
}

EPI_NAMESPACE_END()
