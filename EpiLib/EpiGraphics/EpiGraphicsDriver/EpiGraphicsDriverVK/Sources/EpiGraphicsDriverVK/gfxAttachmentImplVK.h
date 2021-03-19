#pragma once

#include "EpiGraphicsDriverCommon/gfxDriverInternal.h"

EPI_NAMESPACE_BEGIN()

namespace internalgfx
{

class gfxAttachmentImplVK : public gfxAttachmentImpl
{
public:
    gfxAttachmentImplVK() = default;
    gfxAttachmentImplVK(const gfxAttachmentImplVK& rhs) = delete;
    gfxAttachmentImplVK& operator=(const gfxAttachmentImplVK& rhs) = delete;
    gfxAttachmentImplVK(gfxAttachmentImplVK&& rhs) = default;
    gfxAttachmentImplVK& operator=(gfxAttachmentImplVK&& rhs) = default;
    ~gfxAttachmentImplVK() override;
};

} // namespace internalgfx

EPI_NAMESPACE_END()
