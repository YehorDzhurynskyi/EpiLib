#pragma once

#include "EpiCore/ObjectModel/MetaObject.h"

EPI_NAMESPACE_BEGIN()

class epiPropertyPath final
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
        epiMetaPropertyID PropertyID;
        PathNodeType Type;
    };

public:
    epiBool Parse(const std::string& path);

    void AddPathNode(epiMetaPropertyID pid);
    void AddPathNodeIndexed(epiMetaPropertyID pid, epiS32 index);

    void Reverse();
    void Clear();

    epiByte* GetValue(const Object& object) const;

protected:
    std::vector<PathNode> m_Nodes;
};

EPI_NAMESPACE_END()
