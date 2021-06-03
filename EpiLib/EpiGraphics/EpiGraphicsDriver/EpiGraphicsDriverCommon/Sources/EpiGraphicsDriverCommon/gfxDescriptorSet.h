#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiGraphicsDriverCommon/gfxDescriptorSet.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"

#include "EpiGraphicsDriverCommon/gfxBuffer.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxDescriptorSetImpl;

} // namespace internalgfx

class gfxDescriptorBufferInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorBufferInfo)

EPI_GENHIDDEN_gfxDescriptorBufferInfo()

public:
    constexpr static epiMetaTypeID TypeID{0x5cc6bc21};

    enum gfxDescriptorBufferInfo_PIDs
    {
        PID_Buffer = 0x36f6f5c4,
        PID_Offset = 0x5ea6cfe6,
        PID_Range = 0x5246754d,
        PID_COUNT = 3
    };

protected:
    gfxBuffer m_Buffer{};
    epiSize_t m_Offset{0};
    epiSize_t m_Range{0};

EPI_GENREGION_END(gfxDescriptorBufferInfo)
};

class gfxDescriptorImageInfo : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorImageInfo)

EPI_GENHIDDEN_gfxDescriptorImageInfo()

public:
    constexpr static epiMetaTypeID TypeID{0xf26111f3};

    enum gfxDescriptorImageInfo_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDescriptorImageInfo)
};

class gfxDescriptorSet : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorSet)

EPI_GENHIDDEN_gfxDescriptorSet()

public:
    constexpr static epiMetaTypeID TypeID{0x974294fb};

    enum gfxDescriptorSet_PIDs
    {
        PID_COUNT = 0
    };

EPI_GENREGION_END(gfxDescriptorSet)

public:
    friend class internalgfx::gfxDescriptorSetImpl;

public:
    gfxDescriptorSet() = default;
    explicit gfxDescriptorSet(const std::shared_ptr<internalgfx::gfxDescriptorSetImpl>& impl);

protected:
    epiPimpl<internalgfx::gfxDescriptorSetImpl> m_Impl;
};

class gfxDescriptorSetWrite : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorSetWrite)

EPI_GENHIDDEN_gfxDescriptorSetWrite()

public:
    constexpr static epiMetaTypeID TypeID{0xfc720797};

    enum gfxDescriptorSetWrite_PIDs
    {
        PID_DstSet = 0x5e3cfe23,
        PID_DstBinding = 0x94687e11,
        PID_DstArrayElement = 0x6fb57ffa,
        PID_DescriptorCount = 0x2df3c685,
        PID_DescriptorType = 0xc183e584,
        PID_BufferInfos = 0xba739bf0,
        PID_ImageInfos = 0xcf49343c,
        PID_COUNT = 7
    };

protected:
    gfxDescriptorSet m_DstSet{};
    epiU32 m_DstBinding{0};
    epiU32 m_DstArrayElement{0};
    epiU32 m_DescriptorCount{0};
    gfxDescriptorType m_DescriptorType{};
    epiArray<gfxDescriptorBufferInfo> m_BufferInfos{};
    epiArray<gfxDescriptorImageInfo> m_ImageInfos{};

EPI_GENREGION_END(gfxDescriptorSetWrite)

public:
    epiBool IsValid() const;

    gfxDescriptorSetWrite& AddBufferInfo(const gfxDescriptorBufferInfo& bufferInfo);
    gfxDescriptorSetWrite& AddImageInfo(const gfxDescriptorImageInfo& imageInfo);
};

class gfxDescriptorSetCopy : public Object
{
EPI_GENREGION_BEGIN(gfxDescriptorSetCopy)

EPI_GENHIDDEN_gfxDescriptorSetCopy()

public:
    constexpr static epiMetaTypeID TypeID{0xead1be56};

    enum gfxDescriptorSetCopy_PIDs
    {
        PID_SrcSet = 0xb0418a96,
        PID_SrcBinding = 0x301fc8f1,
        PID_SrcArrayElement = 0xe4adae5b,
        PID_DstSet = 0x5e3cfe23,
        PID_DstBinding = 0x94687e11,
        PID_DstArrayElement = 0x6fb57ffa,
        PID_DescriptorCount = 0x2df3c685,
        PID_COUNT = 7
    };

protected:
    gfxDescriptorSet m_SrcSet{};
    epiU32 m_SrcBinding{0};
    epiU32 m_SrcArrayElement{0};
    gfxDescriptorSet m_DstSet{};
    epiU32 m_DstBinding{0};
    epiU32 m_DstArrayElement{0};
    epiU32 m_DescriptorCount{0};

EPI_GENREGION_END(gfxDescriptorSetCopy)
};

EPI_NAMESPACE_END()
