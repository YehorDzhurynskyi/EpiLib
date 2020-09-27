#pragma once

#include <wx/panel.h>
#include <wx/image.h>
#include <wx/bitmap.h>

#include "EpiMultimedia/mmImage.h"

class epiWXImagePanel : public wxPanel
{
public:
    wxDECLARE_EVENT_TABLE();

    enum
    {
        ID_IMAGE_PANEL_RESET = wxID_HIGHEST + 1,
        ID_IMAGE_PANEL_FIT_TO_SCREEN,
        ID_IMAGE_PANEL_TO_GRAYSCALE,
        ID_IMAGE_PANEL_CONTRAST,
        ID_IMAGE_PANEL_CONTRAST_STRETCH,
        ID_IMAGE_PANEL_CONTRAST_STRETCH_PER_CHANNEL,
        ID_IMAGE_PANEL_HISTOGRAM_EQUALIZE,
        ID_IMAGE_PANEL_HIGHEST
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
    virtual void OnMenuEvent(wxCommandEvent& event);
    virtual void BuildContextMenu(wxMenu& contextMenu);

    void ImageReset();
    void ImageFitToScreen();
    void ImageToGrayScale();
    void ImageScale(epiFloat factor = 1.0f);
    void ImageContrast(epiS8 contrast);
    void ImageContrastStretch(epiU8 lower, epiU8 upper);
    void ImageContrastStretch(epiU8 lowerR,
                              epiU8 upperR,
                              epiU8 lowerG,
                              epiU8 upperG,
                              epiU8 lowerB,
                              epiU8 upperB);
    void ImageHistogramEqualize();

    const epi::mmImage& GetImage() const;
    epi::mmImage& GetImage();
    void SetImage(const epi::mmImage& image);
    void SetImage(epi::mmImage&& image);

protected:
    void ImageRefresh();
    wxImage ToWXImage(epi::mmImage& image);

private:
    void OnMenu(wxCommandEvent& event);

protected:
    epi::mmImage m_ImageSrc;
    epi::mmImage m_ImageTgt;
    wxBitmap m_BitmapToDraw;
    epiFloat m_ScaleFactor{1.0f};
};
