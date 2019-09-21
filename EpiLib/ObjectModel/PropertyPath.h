#pragma once

#include "MetaObject.h"

namespace epi
{

class PropertyPath final
{
protected:
    enum class PathNodeType
    {
        Plain,
        Index,
        Hash
    };

    struct PathNode
    {
        PathNode();

        union
        {
            epiS32 Index;
            epiHash_t Hash;
        };
        MetaPropertyID PropertyID;
        PathNodeType Type;
    };

public:
    epiBool Parse(const std::string& path);
    void Clear();

    epiByte* GetValue(const Object& object) const;

protected:
    std::vector<PathNode> m_Nodes;
};

}
