#pragma once

#include "EpiCore/ObjectModel/MetaObject.h"

EPI_NAMESPACE_BEGIN()

class epiPropertyGrouping
{
protected:
    static constexpr epiU32 kMaxGroupCount = 8;
    static constexpr epiU32 kMaxGroupElementCount = 16;

public:
    class GroupElement
    {
    public:
        GroupElement() = default;
        GroupElement(epiMetaPropertyID prtyID);
        GroupElement(const GroupElement& rhs) = default;
        GroupElement(GroupElement&& rhs) = default;
        GroupElement& operator=(const GroupElement& rhs) = default;
        GroupElement& operator=(GroupElement&& rhs) = default;
        ~GroupElement() = default;

        epiMetaPropertyID GetPrtyID() const;

    protected:
        epiMetaPropertyID m_PrtyID;
    };

    class Group
    {
    public:
        Group() = default;
        Group(epiPropertyGrouping* grouping, const epiString& groupName);
        Group(const Group& rhs) = default;
        Group(Group&& rhs) = default;
        Group& operator=(const Group& rhs) = default;
        Group& operator=(Group&& rhs) = default;
        ~Group() = default;

        Group& AddElement(epiMetaPropertyID prtyID);
        epiPropertyGrouping& FinishGroup();

        const epiString& GetGroupName() const;
        epiBool GetIsReplicable() const;
        Group& SetIsReplicable(epiBool isReplicable);
        epiBool GetIsExclusiveWith(const epiString& groupName) const;
        Group& SetIsExclusiveWith(const epiString& groupName);

    protected:
        epiPropertyGrouping* m_Grouping{ nullptr };

        epiString m_GroupName{};

        std::array<GroupElement, kMaxGroupElementCount> m_Elements;
        epiU32 m_ElementCount{0};

        std::array<epiString, kMaxGroupCount> m_GroupsExclusive;
        epiU32 m_GroupExclusiveCount{0};

        epiBool m_IsReplicable{false};

    public:
        auto begin() -> typename decltype(m_Elements)::iterator{ return m_Elements.begin(); }
        auto end() -> typename decltype(m_Elements)::iterator{ return std::next(m_Elements.begin(), m_ElementCount); }
        auto begin() const -> typename decltype(m_Elements)::const_iterator{ return m_Elements.cbegin(); }
        auto end() const -> typename decltype(m_Elements)::const_iterator{ return std::next(m_Elements.cbegin(), m_ElementCount); }
        auto cbegin() const -> typename decltype(m_Elements)::const_iterator{ return m_Elements.cbegin(); }
        auto cend() const -> typename decltype(m_Elements)::const_iterator{ return std::next(m_Elements.cbegin(), m_ElementCount); }
        auto rbegin() -> typename decltype(m_Elements)::reverse_iterator{ return m_Elements.rbegin(); }
        auto rend() -> typename decltype(m_Elements)::reverse_iterator{ return std::next(m_Elements.rbegin(), m_ElementCount); }
        auto crbegin() -> typename decltype(m_Elements)::const_reverse_iterator{ return m_Elements.crbegin(); }
        auto crend() -> typename decltype(m_Elements)::const_reverse_iterator{ return std::next(m_Elements.crbegin(), m_ElementCount); }
    };

public:
    Group& AddGroup(const epiString& groupName);

protected:
    std::array<Group, kMaxGroupCount> m_Groups;
    epiU32 m_GroupCount{0};

public:
    auto begin() -> typename decltype(m_Groups)::iterator { return m_Groups.begin(); }
    auto end() -> typename decltype(m_Groups)::iterator { return std::next(m_Groups.begin(), m_GroupCount); }
    auto begin() const -> typename decltype(m_Groups)::const_iterator { return m_Groups.cbegin(); }
    auto end() const -> typename decltype(m_Groups)::const_iterator { return std::next(m_Groups.cbegin(), m_GroupCount); }
    auto cbegin() const -> typename decltype(m_Groups)::const_iterator { return m_Groups.cbegin(); }
    auto cend() const -> typename decltype(m_Groups)::const_iterator { return std::next(m_Groups.cbegin(), m_GroupCount); }
    auto rbegin() -> typename decltype(m_Groups)::reverse_iterator { return m_Groups.rbegin(); }
    auto rend() -> typename decltype(m_Groups)::reverse_iterator { return std::next(m_Groups.rbegin(), m_GroupCount); }
    auto crbegin() -> typename decltype(m_Groups)::const_reverse_iterator { return m_Groups.crbegin(); }
    auto crend() -> typename decltype(m_Groups)::const_reverse_iterator { return std::next(m_Groups.crbegin(), m_GroupCount); }
};

EPI_NAMESPACE_END()
