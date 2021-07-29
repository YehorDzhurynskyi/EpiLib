#pragma once

EPI_GENREGION_BEGIN(include)
#include "EpiDrawer/Text/drwTextManager.hxx"
EPI_GENREGION_END(include)

#include "EpiCore/ObjectModel/Object.h"
#include "EpiDrawer/Text/drwTextFace.h"

#include <ft2build.h>
#include FT_FREETYPE_H

EPI_NAMESPACE_BEGIN()

class drwTextManager final : public Object
{
EPI_GENREGION_BEGIN(drwTextManager)

EPI_GENHIDDEN_drwTextManager()

public:
    constexpr static epiMetaTypeID TypeID{0xfa8d842f};

    enum drwTextManager_PIDs
    {
        PID_DefaultFace = 0x40b63159,
        PID_COUNT = 1
    };

protected:
    drwTextFace m_DefaultFace{};

EPI_GENREGION_END(drwTextManager)

public:
    drwTextManager();
    drwTextManager(const drwTextManager& rhs) = delete;
    drwTextManager& operator=(const drwTextManager& rhs) = delete;
    drwTextManager(drwTextManager&& rhs) = delete;
    drwTextManager& operator=(drwTextManager&& rhs) = delete;
    ~drwTextManager();

public:
    void CreateFace(drwTextFace& target, const epiChar* ttf) const;

    void Embolden();

protected:
    FT_Library m_FTLibrary;

};

EPI_NAMESPACE_END()
