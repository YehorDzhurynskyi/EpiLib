EPI_GENREGION_BEGIN(include)
#include "EpiGraphics/gfxContext.h"
#include "EpiGraphics/gfxContext.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

gfxContext::gfxContext()
{
    // TODO: move it to proper place
    m_Camera.SetPosition({ 0.0f, 0.0f, 1.0f });
    m_Camera.SetLookAtPosition({ 0.0f, 0.0f, 0.0f });
    m_Camera.SetUpDirection({ 0.0f, 1.0f, 0.0f });
    m_Camera.SetPlaneNear(0.1f);
    m_Camera.SetPlaneFar(1000.0f);

    epi::gfxCameraOrtho* ortho = epi::As<epi::gfxCameraOrtho, epi::gfxCamera>(&m_Camera);

    epiRect2f rect;
    rect.Left = -1.0f;
    rect.Top = 1.0f;
    rect.Right = 1.0f;
    rect.Bottom = -1.0f;

    ortho->SetFrameDimension(rect);
}

EPI_NAMESPACE_END()
