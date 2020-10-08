#pragma once

#include <wx/panel.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/dialog.h>
#include <wx/statbmp.h>

#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"

#include "EpiMultimedia/Image/mmImage.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"

EPI_NAMESPACE_BEGIN()

class mmVMImageBase;

EPI_NAMESPACE_END()

class epiWXImageConfigurationDialog : public wxDialog
{
public:
    wxDECLARE_EVENT_TABLE();

public:
    epiWXImageConfigurationDialog(epi::mmVMImageBase& vm,
                                  wxWindow* parent,
                                  wxWindowID id,
                                  const wxString& title,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = wxDEFAULT_DIALOG_STYLE /* TODO: make it resizable `| wxRESIZE_BORDER`*/,
                                  const wxString& name = wxASCII_STR(wxDialogNameStr));

    void OnImageUpdated(wxCommandEvent& event);

protected:
    epi::mmVMImageBase& m_ImageVM;
    wxStaticBitmap* m_StaticBitmap{nullptr};
};

class epiWXImagePanel : public wxPanel
{
public:
    wxDECLARE_EVENT_TABLE();

    enum
    {
        ID_IMAGE_PANEL_RESET = wxID_HIGHEST + 1,
        ID_IMAGE_PANEL_FIT_TO_SCREEN,
        ID_IMAGE_PANEL_TO_GRAYSCALE,
        ID_IMAGE_PANEL_CONTRAST_ADJUSTMENT,
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
    void ImageContrast(epiS8 contrastR, epiS8 contrastG, epiS8 contrastB);
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

private:
    void OnMenu(wxCommandEvent& event);

protected:
    epi::mmImage m_ImageSrc;
    epi::mmImage m_ImageTgt;
    epiFloat m_ScaleFactor{1.0f};
};
