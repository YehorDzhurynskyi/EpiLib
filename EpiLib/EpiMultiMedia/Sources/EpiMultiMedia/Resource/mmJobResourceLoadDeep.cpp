EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmJobResourceLoadDeep.h"
#include "EpiMultimedia/Resource/mmJobResourceLoadDeep.cxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Resource/mmResourceManager.h"

EPI_NAMESPACE_BEGIN()

mmJobResourceLoadDeep::mmJobResourceLoadDeep(mmResource& resource)
    : m_Resource{&resource}
{
}

void mmJobResourceLoadDeep::Execute()
{
    mmResourceManager::GetInstance().LoadResourceDeep(*GetResource());
}

EPI_NAMESPACE_END()
