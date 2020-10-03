#include "EpiCore/ObjectModel/epiPropertyGrouping.h"

EPI_NAMESPACE_BEGIN()

epiPropertyGrouping::GroupElement::GroupElement(epiMetaPropertyID prtyID)
    : m_PrtyID{prtyID}
{
}

epiMetaPropertyID epiPropertyGrouping::GroupElement::GetPrtyID() const
{
    return m_PrtyID;
}

epiPropertyGrouping::Group::Group(epiPropertyGrouping* grouping, const epiString& groupName)
    : m_Grouping{grouping}
    , m_GroupName{groupName}
{
}

epiPropertyGrouping::Group& epiPropertyGrouping::Group::AddElement(epiMetaPropertyID prtyID)
{
    epiAssert(m_ElementCount < kMaxGroupElementCount);

    m_Elements[m_ElementCount++] = std::move(GroupElement(prtyID));
    return *this;
}

epiBool epiPropertyGrouping::Group::GetIsReplicable() const
{
    return m_IsReplicable;
}

epiPropertyGrouping::Group& epiPropertyGrouping::Group::SetIsReplicable(epiBool isReplicable)
{
    m_IsReplicable = isReplicable;
    return *this;
}

epiBool epiPropertyGrouping::Group::GetIsExclusiveWith(const epiString& groupName) const
{
    return m_GroupsExclusive.end() != std::find(m_GroupsExclusive.begin(), std::next(m_GroupsExclusive.begin(), m_GroupExclusiveCount), groupName);
}

epiPropertyGrouping::Group& epiPropertyGrouping::Group::SetIsExclusiveWith(const epiString& groupName)
{
    epiAssert(m_GroupExclusiveCount < kMaxGroupCount);

    m_GroupsExclusive[m_GroupExclusiveCount++] = groupName;
    return *this;
}

epiPropertyGrouping& epiPropertyGrouping::Group::FinishGroup()
{
    epiAssert(m_Grouping != nullptr);

    return *m_Grouping;
}

const epiString& epiPropertyGrouping::Group::GetGroupName() const
{
    return m_GroupName;
}

epiPropertyGrouping::Group& epiPropertyGrouping::AddGroup(const epiString& groupName)
{
    epiAssert(m_GroupCount < kMaxGroupCount);
    epiAssert(std::next(m_Groups.begin(), m_GroupCount) == std::find_if(m_Groups.begin(),
                                                                        std::next(m_Groups.begin(), m_GroupCount),
                                                                        [groupName](const Group& group) { return group.GetGroupName() == groupName; }));

    return (m_Groups[m_GroupCount++] = std::move(Group(this, groupName)));
}

EPI_NAMESPACE_END()
