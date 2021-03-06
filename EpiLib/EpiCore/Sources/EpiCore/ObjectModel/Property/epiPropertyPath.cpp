#include "EpiCore/ObjectModel/Property/epiPropertyPath.h"

#include "EpiCore/ObjectModel/Object.h"
#include "EpiCore/ObjectModel/Handle.h"

#include <charconv>

EPI_NAMESPACE_BEGIN()

epiPropertyPath::PathNode::PathNode()
    : PropertyID(-1)
    , Type(PathNodeType::Plain)
{}

epiBool epiPropertyPath::Parse(const std::string& path)
{
    const epiSize_t classNamePos = path.find(':');
    if (classNamePos == std::string::npos) goto invalid_input;

    const MetaClass* meta = ClassRegistry_Name_Lookup(&path[0], classNamePos);
    if (meta == nullptr) goto invalid_input;

    PathNode node;
    epiS32 hashBeginIndex = classNamePos + 2;
    for (epiS32 i = hashBeginIndex; i < path.size() + 1; ++i)
    {
        const epiChar ch = path[i];
        switch (ch)
        {
        case '\0':
        case ':':
        {
            epiS32 hashEndIndex = hashBeginIndex;
            while (isalnum(path[hashEndIndex]) || path[hashEndIndex] == '_') ++hashEndIndex;

            std::string propertyName(&path[hashBeginIndex], hashEndIndex - hashBeginIndex);
            const epiMetaPropertyID pid = epiHash(propertyName.c_str());
            node.PropertyID = pid;
            m_Nodes.push_back(node);
            node = PathNode();

            const MetaProperty* metaProperty = meta->GetPropertyBy(pid);
            if (metaProperty == nullptr) goto invalid_input;

            if (MetaType::IsMultiDimensional(metaProperty->GetTypeID()))
            {
                assert(metaProperty->HasNested());
                epiMetaTypeID elemTypeID = metaProperty->GetNestedTypeID();

                if (MetaType::IsCompound(elemTypeID))
                {
                    meta = ClassRegistry_Type_Lookup(elemTypeID);
                }
            }

            if (path[i] == ':')
            {
                if (path[++i] != ':') goto invalid_input;
                hashBeginIndex = ++i;
            }

            break;
        }
        case '[':
        {
            const epiS32 indexBeginIndex = ++i;
            if (path[indexBeginIndex] == '\'')
            {
                while (path[++i] != '\'')
                {
                    if (!isdigit(path[i]) && !isalnum(path[i])) goto invalid_input;
                }

                const epiS32 len = i - indexBeginIndex - 1;
                if (len <= 0 || path[++i] != ']') goto invalid_input;

                node.Type = PathNodeType::Hash;
                node.Hash = epiHashEx(&path[indexBeginIndex + 1], len);
            }
            else
            {
                do { if (!isdigit(path[i])) goto invalid_input; } while (path[++i] != ']');

                node.Type = PathNodeType::Index;
                auto[p, ec] = std::from_chars(&path[indexBeginIndex], &path[i], node.Index);
                if (ec != std::errc()) goto invalid_input;
            }

            break;
        }
        default:
        {
            if (!isalnum(ch) && ch != '_') goto invalid_input;
            break;
        }
        }
    }

    return true;

invalid_input:
    Clear();
    return false;
}

void epiPropertyPath::Clear()
{
    m_Nodes.clear();
}

epiByte* epiPropertyPath::GetValue(const Object& object) const
{
    const Object* current = &object;
    epiByte* value = nullptr;

    epiU32 index = 0;
    for (const auto& node : m_Nodes)
    {
        const MetaProperty* property = current->GetMetaClass().GetPropertyBy_FromCurrent(node.PropertyID);
        if (property == nullptr)
        {
            return nullptr;
        }
        // TODO: repair
        value = nullptr; // property->GetValue(*current);

        // TODO: refactor
        if (node.Type != PathNodeType::Plain)
        {
            if (node.Type == PathNodeType::Index)
            {
#if 0
                value = MetaType::GetElementByIndex(value, *property, node.Index);
            }
            else if (node.Type == PathNodeType::Hash)
            {
                value = MetaType::GetElementByHash(value, *property, node.Hash);
#endif
            }

            if (value == nullptr)
            {
                return nullptr;
            }

            //if (MetaType::IsHandle(property->GetTypeID()))
            //{
            //    value = ((BaseHandle*)value)->GetValue();
            //}

            if (value == nullptr)
            {
                return nullptr;
            }

            if (++index < m_Nodes.size())
            {
                current = (const Object*)value;
            }
        }
    }

    return value;
}

void epiPropertyPath::AddPathNode(epiMetaPropertyID pid)
{
    PathNode node;
    node.PropertyID = pid;
    node.Type = PathNodeType::Plain;

    m_Nodes.push_back(std::move(node));
}

void epiPropertyPath::AddPathNodeIndexed(epiMetaPropertyID pid, epiS32 index)
{
    PathNode node;
    node.PropertyID = pid;
    node.Type = PathNodeType::Index;
    node.Index = index;

    m_Nodes.push_back(std::move(node));
}

void epiPropertyPath::Reverse()
{
    std::reverse(m_Nodes.begin(), m_Nodes.end());
}

EPI_NAMESPACE_END()
