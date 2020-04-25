#include "EpiUI/pch.h"

EPI_GENREGION_BEGIN(include)
#include "EpiUI/uiPage.h"
#include "EpiUI/uiPage.cxx"
EPI_GENREGION_END(include)

#include "EpiUI/uiContext.h"

EPI_NAMESPACE_BEGIN()

epiVec2f uiPage::GetMouseLocalUICoord_Internal() const
{
    // TODO: implement
    return m_UIContext->GetMouseUICoord();
}

EPI_NAMESPACE_END()