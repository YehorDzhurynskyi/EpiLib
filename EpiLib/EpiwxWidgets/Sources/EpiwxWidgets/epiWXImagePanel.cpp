#include "EpiwxWidgets/epiWXImagePanel.h"

#include <wx/dcclient.h>
#include <wx/menu.h>
#include <wx/numdlg.h>
#include <wx/msgdlg.h>

wxBEGIN_EVENT_TABLE(epiWXImagePanel, wxPanel)
    EVT_PAINT(epiWXImagePanel::OnPaint)
    EVT_MOUSE_EVENTS(epiWXImagePanel::OnMouse)
    EVT_MENU(wxID_ANY, epiWXImagePanel::OnMenu)
wxEND_EVENT_TABLE()

void epiWXImagePanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    if (m_BitmapToDraw.IsOk())
    {
        const wxSize& sizeHalfClient = GetClientSize() / 2;
        const wxSize& sizeHalfImage = m_BitmapToDraw.GetSize() / 2;
        dc.DrawBitmap(m_BitmapToDraw, sizeHalfClient.x - sizeHalfImage.x, sizeHalfClient.y - sizeHalfImage.y, false);
    }
}

void epiWXImagePanel::OnMouse(wxMouseEvent& event)
{
    // TODO: make scrolling FPS independent

    if (const epiFloat dZoom = event.GetWheelRotation() / 120.0f; dZoom != 0.0f)
    {
        ImageScale(m_ScaleFactor + dZoom * 0.05f);
    }

    if (event.RightDown())
    {
        wxMenu contextMenu;
        BuildContextMenu(contextMenu);

        PopupMenu(&contextMenu);
    }
}

void epiWXImagePanel::OnMenu(wxCommandEvent& event)
{
    OnMenuEvent(event);
}

void epiWXImagePanel::OnMenuEvent(wxCommandEvent& event)
{
    switch (event.GetId())
    {
    case ID_IMAGE_PANEL_RESET:
    {
        ImageReset();
    } break;
    case ID_IMAGE_PANEL_FIT_TO_SCREEN:
    {
        ImageFitToScreen();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE:
    {
        ImageToGrayScale();
    } break;
    case ID_IMAGE_PANEL_CONTRAST:
    {
        const epiS8 contrast = static_cast<epiS8>(wxGetNumberFromUser(fmt::format("Set contrast value in range [{}..{}]", std::numeric_limits<epiS8>::min(), std::numeric_limits<epiS8>::max()),
                                                  "Contrast:",
                                                  "Contrast",
                                                  0,
                                                  std::numeric_limits<epiS8>::min(),
                                                  std::numeric_limits<epiS8>::max(),
                                                  this));
        ImageContrast(contrast);
    } break;
    case ID_IMAGE_PANEL_CONTRAST_STRETCH:
    {
        const epiU8 contrastLower = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast lower value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                      "Contrast:",
                                                      "Contrast",
                                                      0,
                                                      std::numeric_limits<epiU8>::min(),
                                                      std::numeric_limits<epiU8>::max(),
                                                      this));

        const epiU8 contrastUpper = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast upper value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                       "Contrast:",
                                                       "Contrast",
                                                       0,
                                                       std::numeric_limits<epiU8>::min(),
                                                       std::numeric_limits<epiU8>::max(),
                                                       this));

        if (contrastLower >= contrastUpper)
        {
            wxMessageBox("Are you sure you want to quit the program?",
                         "Error",
                         wxOK | wxICON_ERROR,
                         this);
            break;
        }

        ImageContrastStretch(contrastLower, contrastUpper);
    } break;
    case ID_IMAGE_PANEL_CONTRAST_STRETCH_PER_CHANNEL:
    {
        const epiU8 contrastLowerR = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast red lower value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                       "Contrast:",
                                                       "Contrast",
                                                       0,
                                                       std::numeric_limits<epiU8>::min(),
                                                       std::numeric_limits<epiU8>::max(),
                                                       this));

        const epiU8 contrastUpperR = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast red upper value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                       "Contrast:",
                                                       "Contrast",
                                                       0,
                                                       std::numeric_limits<epiU8>::min(),
                                                       std::numeric_limits<epiU8>::max(),
                                                       this));

        if (contrastLowerR >= contrastUpperR)
        {
            wxMessageBox(fmt::format("Lower bound=`{}` should be strictly less than the upper bound=`{}`", contrastLowerR, contrastUpperR),
                         "Error",
                         wxOK | wxICON_ERROR,
                         this);
            break;
        }

        const epiU8 contrastLowerG = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast green lower value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                        "Contrast:",
                                                        "Contrast",
                                                        0,
                                                        std::numeric_limits<epiU8>::min(),
                                                        std::numeric_limits<epiU8>::max(),
                                                        this));

        const epiU8 contrastUpperG = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast green upper value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                        "Contrast:",
                                                        "Contrast",
                                                        0,
                                                        std::numeric_limits<epiU8>::min(),
                                                        std::numeric_limits<epiU8>::max(),
                                                        this));

        if (contrastLowerG >= contrastUpperG)
        {
            wxMessageBox(fmt::format("Lower bound=`{}` should be strictly less than the upper bound=`{}`", contrastLowerG, contrastUpperG),
                         "Error",
                         wxOK | wxICON_ERROR,
                         this);
            break;
        }

        const epiU8 contrastLowerB = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast blue lower value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                        "Contrast:",
                                                        "Contrast",
                                                        0,
                                                        std::numeric_limits<epiU8>::min(),
                                                        std::numeric_limits<epiU8>::max(),
                                                        this));

        const epiU8 contrastUpperB = static_cast<epiU8>(wxGetNumberFromUser(fmt::format("Set contrast blue upper value in range [{}..{}]", std::numeric_limits<epiU8>::min(), std::numeric_limits<epiU8>::max()),
                                                        "Contrast:",
                                                        "Contrast",
                                                        0,
                                                        std::numeric_limits<epiU8>::min(),
                                                        std::numeric_limits<epiU8>::max(),
                                                        this));

        if (contrastLowerB >= contrastUpperB)
        {
            wxMessageBox(fmt::format("Lower bound=`{}` should be strictly less than the upper bound=`{}`", contrastLowerB, contrastUpperB),
                         "Error",
                         wxOK | wxICON_ERROR,
                         this);
            break;
        }

        ImageContrastStretch(contrastLowerR, contrastUpperR, contrastLowerG, contrastUpperG, contrastLowerB, contrastUpperB);
    } break;
    case ID_IMAGE_PANEL_HISTOGRAM_EQUALIZE:
    {
        ImageHistogramEqualize();
    } break;
    }
}

void epiWXImagePanel::BuildContextMenu(wxMenu& contextMenu)
{
    contextMenu.Append(ID_IMAGE_PANEL_FIT_TO_SCREEN, wxT("&Fit to screen"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE, wxT("&Convert to grayscale"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_CONTRAST, wxT("&Contrast"));
    contextMenu.Append(ID_IMAGE_PANEL_CONTRAST_STRETCH, wxT("&Contrast stretch"));
    contextMenu.Append(ID_IMAGE_PANEL_CONTRAST_STRETCH_PER_CHANNEL, wxT("&Contrast stretch (per channel)"));
    contextMenu.Append(ID_IMAGE_PANEL_HISTOGRAM_EQUALIZE, wxT("&Histogram equalize"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_RESET, wxT("&Reset"));
}

void epiWXImagePanel::ImageReset()
{
    m_ImageTgt = m_ImageSrc.Duplicate();
    ImageScale();
}

void epiWXImagePanel::ImageFitToScreen()
{
    wxSize sizeScaled;
    const epiFloat ar = m_ImageTgt.GetWidth() / static_cast<epiFloat>(m_ImageTgt.GetHeight());
    if (std::abs(static_cast<epiS32>(m_ImageTgt.GetWidth()) - GetClientSize().x) <
        std::abs(static_cast<epiS32>(m_ImageTgt.GetHeight()) - GetClientSize().y))
    {
        sizeScaled.x = GetClientSize().x;
        sizeScaled.y = sizeScaled.x / ar;
    }
    else
    {
        sizeScaled.y = GetClientSize().y;
        sizeScaled.x = sizeScaled.y * ar;
    }

    const epiFloat scaleFactor = sizeScaled.x / static_cast<epiFloat>(m_ImageTgt.GetWidth());
    ImageScale(scaleFactor);
}

void epiWXImagePanel::ImageToGrayScale()
{
    m_ImageTgt = m_ImageTgt.ToGrayScale();

    ImageRefresh();
}

void epiWXImagePanel::ImageScale(epiFloat factor)
{
    // TODO: clamp `sizeScaled` instead of `m_ScaleFactor`
    m_ScaleFactor = std::clamp(factor, 0.0001f, 100.0f);

    ImageRefresh();
}

void epiWXImagePanel::ImageContrast(epiS8 contrast)
{
    m_ImageTgt.Contrast(contrast);

    ImageRefresh();
}

void epiWXImagePanel::ImageContrastStretch(epiU8 lower, epiU8 upper)
{
    m_ImageTgt.ContrastStretch(lower, upper);

    ImageRefresh();
}

void epiWXImagePanel::ImageContrastStretch(epiU8 lowerR,
                                           epiU8 upperR,
                                           epiU8 lowerG,
                                           epiU8 upperG,
                                           epiU8 lowerB,
                                           epiU8 upperB)
{
    m_ImageTgt.ContrastStretch(lowerR, upperR, lowerG, upperG, lowerB, upperB);

    ImageRefresh();
}

void epiWXImagePanel::ImageHistogramEqualize()
{
    m_ImageTgt.HistogramEqualize();

    ImageRefresh();
}

void epiWXImagePanel::ImageRefresh()
{
    m_BitmapToDraw = ToWXImage(m_ImageTgt).Scale(m_ImageTgt.GetWidth() * m_ScaleFactor, m_ImageTgt.GetHeight() * m_ScaleFactor, wxIMAGE_QUALITY_NEAREST);
    Refresh();
}

wxImage epiWXImagePanel::ToWXImage(epi::mmImage& image)
{
    switch (image.GetPixelFormat())
    {
    case epi::mmImagePixelFormat::R8G8B8:
    {
        return wxImage(image.GetWidth(), image.GetHeight(), image.GetData().data(), true);
    } break;
    case epi::mmImagePixelFormat::GRAYSCALE:
    {
        uint8_t* buff = new uint8_t[image.GetWidth() * image.GetHeight() * 3];
        for (int32_t i = 0; i < image.GetWidth() * image.GetHeight(); ++i)
        {
            buff[i * 3 + 0] = image.GetData()[i];
            buff[i * 3 + 1] = image.GetData()[i];
            buff[i * 3 + 2] = image.GetData()[i];
        }
        return wxImage(image.GetWidth(), image.GetHeight(), buff, true);
    } break;
    }
}

const epi::mmImage& epiWXImagePanel::GetImage() const
{
    return m_ImageTgt;
}

epi::mmImage& epiWXImagePanel::GetImage()
{
    return m_ImageTgt;
}

void epiWXImagePanel::SetImage(const epi::mmImage& image)
{
    m_ImageSrc = image;
    ImageReset();
}

void epiWXImagePanel::SetImage(epi::mmImage&& image)
{
    m_ImageSrc = std::move(image);
    ImageReset();
}
