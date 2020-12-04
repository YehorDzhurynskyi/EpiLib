#pragma once

#include <wx/panel.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/dialog.h>
#include <wx/statbmp.h>

#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"
#include "EpiwxWidgets/epiWXPlot.h"

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
                                  const wxGLAttributes& glattrs,
                                  wxWindowID id,
                                  const wxString& title,
                                  const wxPoint& pos = wxDefaultPosition,
                                  const wxSize& size = wxDefaultSize,
                                  long style = wxDEFAULT_DIALOG_STYLE /* TODO: make it resizable `| wxRESIZE_BORDER`*/,
                                  const wxString& name = wxASCII_STR(wxDialogNameStr));

    void OnImageUpdated(wxCommandEvent& event);
    void OnImageUpdated();

protected:
    epi::mmVMImageBase& m_ImageVM;
    wxStaticBitmap* m_StaticBitmap{nullptr};
    epiWXPlot* m_PlotHistogramGrayscale{nullptr};
    epiWXPlot* m_PlotHistogramRGB{nullptr};
};

class epiWXImagePanel : public wxPanel
{
public:
    wxDECLARE_EVENT_TABLE();

    enum
    {
        ID_IMAGE_PANEL_RESET = wxID_HIGHEST + 1,
        ID_IMAGE_PANEL_FIT_TO_SCREEN,
        ID_IMAGE_PANEL_TO_GRAYSCALE_R,
        ID_IMAGE_PANEL_TO_GRAYSCALE_G,
        ID_IMAGE_PANEL_TO_GRAYSCALE_B,
        ID_IMAGE_PANEL_TO_GRAYSCALE_A,
        ID_IMAGE_PANEL_TO_GRAYSCALE_MIN,
        ID_IMAGE_PANEL_TO_GRAYSCALE_MAX,
        ID_IMAGE_PANEL_TO_GRAYSCALE_HUE,
        ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA,
        ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA601,
        ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA240,
        ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA709,
        ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA2020,
        ID_IMAGE_PANEL_TO_GRAYSCALE_BRIGHTNESS,
        ID_IMAGE_PANEL_TO_GRAYSCALE_LIGHTNESS,
        ID_IMAGE_PANEL_TO_GRAYSCALE_INTENSITY,
        ID_IMAGE_PANEL_TO_GRAYSCALE_CHROMA,
        ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONB,
        ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONL,
        ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONI,
        ID_IMAGE_PANEL_TO_NEGATIVE,
        ID_IMAGE_PANEL_THRESHOLD,
        ID_IMAGE_PANEL_GAMMA_CORRECTION,
        ID_IMAGE_PANEL_CONTRAST_ADJUSTMENT,
        ID_IMAGE_PANEL_HSB_ADJUSTMENT,
        ID_IMAGE_PANEL_HISTOGRAM_EQUALIZE,
        ID_IMAGE_PANEL_MEAN_FILTER,
        ID_IMAGE_PANEL_MEDIAN_FILTER,
        ID_IMAGE_PANEL_SHARPENING,
        ID_IMAGE_PANEL_GAUSSIAN_BLUR_FILTER,
        ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_FILTER,
        ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_VERTICAL_FILTER,
        ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_HORIZONTAL_FILTER,
        ID_IMAGE_PANEL_SPATIALLY_ADAPTIVE_NOISE_FILTER,
        ID_IMAGE_PANEL_HOMOMORPHIC_FILTER,
        ID_IMAGE_PANEL_CROP,
        ID_IMAGE_PANEL_DFT_MAGNITUDE,
        ID_IMAGE_PANEL_DFT_PHASE,
        ID_IMAGE_PANEL_NOISE_NORMAL,
        ID_IMAGE_PANEL_NOISE_SALT_AND_PEPPER,
        ID_IMAGE_PANEL_PRESET_EFFECT0,
        ID_IMAGE_PANEL_HIGHEST
    };

public:
    epiWXImagePanel(wxWindow* parent,
                    const wxGLAttributes& glattrs,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString& name = wxASCII_STR(wxPanelNameStr));

    void OnPaint(wxPaintEvent& event);
    void OnMouse(wxMouseEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    virtual void OnMenuEvent(wxCommandEvent& event);
    virtual void BuildContextMenu(wxMenu& contextMenu);

    void ImageReset();
    void ImageFitToScreen();
    void ImageScale(epiFloat factor = 1.0f);

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

private:
    wxGLAttributes m_GLAttrs;

    wxPoint m_ImagePosition{};
    wxPoint m_ImageCapturePosition{};
    wxPoint m_MouseCapturePosition{};
};
