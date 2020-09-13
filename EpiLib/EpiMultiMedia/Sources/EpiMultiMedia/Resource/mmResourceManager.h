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
    std::unique_ptr<mmResource> LoadResource(const epiChar* url);
};

EPI_NAMESPACE_END()
