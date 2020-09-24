#pragma once

#include <wx/panel.h>
#include <wx/image.h>
#include <wx/bitmap.h>

class epiWXImagePanel : public wxPanel
{
public:
    wxDECLARE_EVENT_TABLE();

    enum
    {
        ID_IMAGE_RESET = wxID_HIGHEST + 1,
        ID_IMAGE_FIT_TO_SCREEN
    };

public:
    epiWXImagePanel(wxWindow* parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString& name = wxASCII_STR(wxPanelNameStr))
        : wxPanel(parent, winid, pos, size, style, name)
    {
    }

    void OnPaint(wxPaintEvent& event);
    void OnMouse(wxMouseEvent& event);
    void OnMenu(wxCommandEvent& event);

    void ImageReset();
    void ImageFitToScreen();
    void ImageScale(epiFloat factor = 1.0f);

    const wxImage& GetImage() const;
    wxImage& GetImage();
    void SetImage(const wxImage& image);
    void SetImage(wxImage&& image);

protected:
    wxImage m_Image;
    wxBitmap m_BitmapToDraw;
    epiFloat m_ScaleFactor{1.0f};
};
