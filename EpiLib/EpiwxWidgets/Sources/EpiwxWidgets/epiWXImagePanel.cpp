#include "EpiwxWidgets/epiWXImagePanel.h"

#include <wx/dcclient.h>
#include <wx/menu.h>

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

    if (event.RightIsDown())
    {
        wxMenu contextMenu;
        contextMenu.Append(ID_IMAGE_RESET, wxT("&Reset"));
        contextMenu.Append(ID_IMAGE_FIT_TO_SCREEN, wxT("&Fit to screen"));

        PopupMenu(&contextMenu);
    }
}

void epiWXImagePanel::OnMenu(wxCommandEvent& event)
{
    switch (event.GetId())
    {
    case ID_IMAGE_RESET:
    {
        ImageReset();
    } break;
    case ID_IMAGE_FIT_TO_SCREEN:
    {
        ImageFitToScreen();
    } break;
    }
}

void epiWXImagePanel::ImageScale(epiFloat factor)
{
    // TODO: clamp `sizeScaled` instead of `m_ScaleFactor`
    m_ScaleFactor = std::clamp(factor, 0.0001f, 100.0f);
    const wxSize sizeScaled = m_Image.GetSize() * m_ScaleFactor;

    m_BitmapToDraw = m_Image.Scale(sizeScaled.x, sizeScaled.y, wxIMAGE_QUALITY_NEAREST);

    Refresh();
}

void epiWXImagePanel::ImageReset()
{
    ImageScale();
}

void epiWXImagePanel::ImageFitToScreen()
{
    wxSize sizeScaled;
    const epiFloat ar = m_Image.GetWidth() / static_cast<epiFloat>(m_Image.GetHeight());
    if (std::abs(m_Image.GetWidth() - GetClientSize().x) < std::abs(m_Image.GetHeight() - GetClientSize().y))
    {
        sizeScaled.x = GetClientSize().x;
        sizeScaled.y = sizeScaled.x / ar;
    }
    else
    {
        sizeScaled.y = GetClientSize().y;
        sizeScaled.x = sizeScaled.y * ar;
    }

    const epiFloat scaleFactor = sizeScaled.x / static_cast<epiFloat>(m_Image.GetSize().x);
    ImageScale(scaleFactor);
}

const wxImage& epiWXImagePanel::GetImage() const
{
    return m_Image;
}

wxImage& epiWXImagePanel::GetImage()
{
    return m_Image;
}

void epiWXImagePanel::SetImage(const wxImage& image)
{
    m_Image = image;
    ImageScale();
}

void epiWXImagePanel::SetImage(wxImage&& image)
{
    m_Image = std::move(image);
    ImageScale();
}
