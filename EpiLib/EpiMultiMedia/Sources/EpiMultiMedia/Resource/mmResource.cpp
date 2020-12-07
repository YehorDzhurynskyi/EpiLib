EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmResource.h"
#include "EpiMultimedia/Resource/mmResource.cxx"
EPI_GENREGION_END(include)

EPI_NAMESPACE_BEGIN()

mmResourceStatus mmResource::GetStatus_Callback() const
{
    return m_Status;
}

void mmResource::SetStatus_Callback(mmResourceStatus value)
{
    m_Status = value;
}

EPI_NAMESPACE_END()
