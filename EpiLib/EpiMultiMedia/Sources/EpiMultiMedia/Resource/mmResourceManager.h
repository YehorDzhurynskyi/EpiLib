#pragma once

#include "EpiMultimedia/Resource/mmResource.h"

EPI_NAMESPACE_BEGIN()

class mmResourceManager
{
public:
    static mmResourceManager& GetInstance()
    {
        static mmResourceManager instance;
        return instance;
    }

protected:
    mmResourceManager() = default;

public:
    mmResource* LoadResource(const epiChar* url, bool deepLoad = false);

    void LoadResourceShallow(mmResource& resource);
    void LoadResourceDeep(mmResource& resource);

protected:
    // TODO: replace with a more advanced method
    std::map<epiString, std::unique_ptr<mmResource>> m_Resources;
};

EPI_NAMESPACE_END()
