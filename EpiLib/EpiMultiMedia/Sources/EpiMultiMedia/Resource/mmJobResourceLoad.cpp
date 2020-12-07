EPI_GENREGION_BEGIN(include)
#include "EpiMultimedia/Resource/mmJobResourceLoad.h"
#include "EpiMultimedia/Resource/mmJobResourceLoad.cxx"
EPI_GENREGION_END(include)

#include "EpiMultimedia/Resource/mmResourceManager.h"

EPI_NAMESPACE_BEGIN()

mmJobResourceLoad::mmJobResourceLoad(const epiChar* url, epiBool deepLoad)
    : m_URL{url}
    , m_DeepLoad{deepLoad}
{
}

void mmJobResourceLoad::Execute()
{
    SetResource(mmResourceManager::GetInstance().LoadResource(GetURL().c_str(), GetDeepLoad()));
}

epiString mmJobResourceLoad::ToString() const
{
    return "mmJobResourceLoad{URL=" + GetURL() + "}";
}

EPI_NAMESPACE_END()
