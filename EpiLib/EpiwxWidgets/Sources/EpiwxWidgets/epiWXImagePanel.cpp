#include "EpiwxWidgets/epiWXImagePanel.h"

#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"

#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageHSB.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageThreshold.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageGamma.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageSpatialDenoising.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageMedian.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageSharpening.h"

#include "EpiData/Series/dSeries2Dc.h"
#include "EpiData/Series/dSeries2Df.h"

#include "EpiDataVisualization/Plot/ViewModel/dvVMSeries1Df.h"

#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/menu.h>
#include <wx/numdlg.h>
#include <wx/msgdlg.h>
#include <wx/sizer.h>
#include <wx/button.h>

namespace
{

wxImage ToWXImage(epi::mmImage& image)
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

}

wxBEGIN_EVENT_TABLE(epiWXImageConfigurationDialog, wxDialog)
    EVT_COMMAND(wxID_ANY, OBJECT_CONFIGURATION_DIALOG_OBJECT_UPDATED, epiWXImageConfigurationDialog::OnImageUpdated)
wxEND_EVENT_TABLE()

epiWXImageConfigurationDialog::epiWXImageConfigurationDialog(epi::mmVMImageBase& vm,
                                                             wxWindow* parent,
                                                             const wxGLAttributes& glattrs,
                                                             wxWindowID id,
                                                             const wxString& title,
                                                             const wxPoint& pos,
                                                             const wxSize& size,
                                                             long style,
                                                             const wxString& name)
    : wxDialog(parent, id, title, pos, size, style, name)
    , m_ImageVM(vm)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);

    if (epi::mmImage* image = m_ImageVM.GetImageSrc())
    {
        if (wxBitmap bitmap = ToWXImage(*image); bitmap.IsOk())
        {
            m_StaticBitmap = new wxStaticBitmap(this, wxID_ANY, bitmap);
            contentSizer->Add(m_StaticBitmap, 0, wxALL, 10);
        }
    }

    contentSizer->Add(new epiWXObjectConfigurationPanel(m_ImageVM, this), wxSizerFlags().Expand());

#if 0 // TODO: uncomment (performance is not good enough to proceed histograms as well)
    wxBoxSizer* plotSizer = new wxBoxSizer(wxVERTICAL);
    m_PlotHistogramGrayscale = new epiWXPlot(this, glattrs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, wxGLCanvasName, wxNullPalette);
    m_PlotHistogramGrayscale->SetMinClientSize({500, 50});
    plotSizer->Add(m_PlotHistogramGrayscale, 1, wxALL | wxEXPAND, 10);

    m_PlotHistogramRGB = new epiWXPlot(this, glattrs, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, wxGLCanvasName, wxNullPalette);
    m_PlotHistogramRGB->SetMinClientSize({500, 50});
    plotSizer->Add(m_PlotHistogramRGB, 1, wxALL | wxEXPAND, 10);

    contentSizer->Add(plotSizer, wxSizerFlags().Expand());
#endif

    sizer->Add(contentSizer, wxSizerFlags().Expand());

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL, 10);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 10);

    sizer->Add(buttonSizer, wxSizerFlags().Right());

    SetSizerAndFit(sizer);

    OnImageUpdated();

    CenterOnParent();
}

void epiWXImageConfigurationDialog::OnImageUpdated(wxCommandEvent& event)
{
    OnImageUpdated();
}

void epiWXImageConfigurationDialog::OnImageUpdated()
{
    if (m_StaticBitmap != nullptr)
    {
        if (epi::mmImage* image = m_ImageVM.GetImageSrc())
        {
            if (wxBitmap bitmap = ToWXImage(m_ImageVM.GetImageTgt()); bitmap.IsOk())
            {
                m_StaticBitmap->SetBitmap(bitmap);
                m_StaticBitmap->Refresh();
            }
        }
    }

    if (m_PlotHistogramRGB != nullptr && m_PlotHistogramGrayscale != nullptr)
    {
        epi::mmImage image = m_ImageVM.GetImageTgt();
        {
            epi::dvVMPlot& plotVM = m_PlotHistogramGrayscale->GetViewModel();
            plotVM.Clear();

            epi::dSeries1Df* series = new epi::dSeries1Df(); // TODO: resolve leak
            *series = image.ToGrayScaleLuma().Histogram(&epi::Color::GetLumau);

            const auto itMaxElement = std::max_element(series->begin(), series->end());
            epiRect2f rect;
            rect.Left = 0.0f;
            rect.Right = 256.0f;
            rect.Top = itMaxElement != series->end() ? *itMaxElement : 1.0f;
            rect.Bottom = 0.0f;
            plotVM.SetBBox(rect);
            plotVM.SetClipBox(rect);

            epi::dvVMSeries1Df& seriesVM = plotVM.Add<epi::dvVMSeries1Df>();
            seriesVM.SetSeries(series);
            seriesVM.SetRepr(epi::dvSeries1DfRepr::Bar);
            seriesVM.SetColor1(epi::Color::kDarkGray * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVM.SetColor2(epi::Color::kLightGray * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVM.SetZ(-0.99f);

            m_PlotHistogramGrayscale->Refresh();
        }
        {
            epi::dvVMPlot& plotVM = m_PlotHistogramRGB->GetViewModel();
            plotVM.Clear();

            epi::dSeries1Df* seriesR = new epi::dSeries1Df(); // TODO: resolve leak
            epi::dSeries1Df* seriesG = new epi::dSeries1Df(); // TODO: resolve leak
            epi::dSeries1Df* seriesB = new epi::dSeries1Df(); // TODO: resolve leak

            *seriesR = image.Histogram(&epi::Color::GetRu);
            *seriesG = image.Histogram(&epi::Color::GetGu);
            *seriesB = image.Histogram(&epi::Color::GetBu);

            const auto itMaxElementR = std::max_element(seriesR->begin(), seriesR->end());
            const auto itMaxElementG = std::max_element(seriesG->begin(), seriesG->end());
            const auto itMaxElementB = std::max_element(seriesB->begin(), seriesB->end());

            epiFloat maxElement = itMaxElementR != seriesR->end() ? *itMaxElementR : 0.0f;
            maxElement = std::max(maxElement, itMaxElementG != seriesG->end() ? *itMaxElementG : 0.0f);
            maxElement = std::max(maxElement, itMaxElementB != seriesB->end() ? *itMaxElementB : 0.0f);

            epiRect2f rect;
            rect.Left = 0.0f;
            rect.Right = 256.0f;
            rect.Top = std::max(maxElement, 1.0f);
            rect.Bottom = 0.0f;
            plotVM.SetBBox(rect);
            plotVM.SetClipBox(rect);

            epi::dvVMSeries1Df& seriesVMR = plotVM.Add<epi::dvVMSeries1Df>();
            seriesVMR.SetSeries(seriesR);
            seriesVMR.SetRepr(epi::dvSeries1DfRepr::Bar);
            seriesVMR.SetColor1(epi::Color::kDarkRed * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVMR.SetColor2(epi::Color::kLightRed * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVMR.SetZ(-99.0f);

            epi::dvVMSeries1Df& seriesVMG = plotVM.Add<epi::dvVMSeries1Df>();
            seriesVMG.SetSeries(seriesG);
            seriesVMG.SetRepr(epi::dvSeries1DfRepr::Bar);
            seriesVMG.SetColor1(epi::Color::kDarkGreen * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVMG.SetColor2(epi::Color::kLightGreen * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVMG.SetZ(-95.0f);

            epi::dvVMSeries1Df& seriesVMB = plotVM.Add<epi::dvVMSeries1Df>();
            seriesVMB.SetSeries(seriesB);
            seriesVMB.SetRepr(epi::dvSeries1DfRepr::Bar);
            seriesVMB.SetColor1(epi::Color::kDarkBlue * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVMB.SetColor2(epi::Color::kLightBlue * epi::Color(1.0f, 1.0f, 1.0f, 0.333333f));
            seriesVMB.SetZ(-90.0f);

            m_PlotHistogramRGB->Refresh();
        }
    }
}

wxBEGIN_EVENT_TABLE(epiWXImagePanel, wxPanel)
    EVT_PAINT(epiWXImagePanel::OnPaint)
    EVT_MOUSE_EVENTS(epiWXImagePanel::OnMouse)
    EVT_ERASE_BACKGROUND(epiWXImagePanel::OnEraseBackground)
    EVT_MENU(wxID_ANY, epiWXImagePanel::OnMenu)
wxEND_EVENT_TABLE()

epiWXImagePanel::epiWXImagePanel(wxWindow* parent,
                                 const wxGLAttributes& glattrs,
                                 wxWindowID winid,
                                 const wxPoint& pos,
                                 const wxSize& size,
                                 long style,
                                 const wxString& name)
    : wxPanel(parent, winid, pos, size, style, name)
    , m_GLAttrs{glattrs}
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void epiWXImagePanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    if (wxBitmap bitmapToDraw = ToWXImage(m_ImageTgt).Scale(m_ImageTgt.GetWidth() * m_ScaleFactor, m_ImageTgt.GetHeight() * m_ScaleFactor, wxIMAGE_QUALITY_NEAREST);
        bitmapToDraw.IsOk())
    {
        const wxSize& sizeHalfClient = GetClientSize() / 2;
        const wxSize& sizeHalfImage = bitmapToDraw.GetSize() / 2;
        dc.DrawBitmap(bitmapToDraw,
                      sizeHalfClient.x - sizeHalfImage.x + m_ImagePosition.x,
                      sizeHalfClient.y - sizeHalfImage.y + m_ImagePosition.y,
                      false);
    }
}

void epiWXImagePanel::OnMouse(wxMouseEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

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

    if (event.LeftDown())
    {
        m_MouseCapturePosition = event.GetPosition();
        m_ImageCapturePosition = m_ImagePosition;
    }
    else if (event.Dragging() && event.LeftIsDown())
    {
        m_ImagePosition = event.GetPosition() - m_MouseCapturePosition + m_ImageCapturePosition;
        Refresh();
    }
}

void epiWXImagePanel::OnEraseBackground(wxEraseEvent& event)
{
    // NOTE: should reduce flickering
}

void epiWXImagePanel::OnMenu(wxCommandEvent& event)
{
    if (!IsEnabled())
    {
        return;
    }

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
    case ID_IMAGE_PANEL_TO_GRAYSCALE_R:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleR();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_G:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleG();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_B:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleB();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_A:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleA();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_MIN:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleMin();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_MAX:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleMax();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_HUE:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleHue();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleLuma();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA601:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleLuma601();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA240:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleLuma240();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA709:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleLuma709();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA2020:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleLuma2020();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_BRIGHTNESS:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleBrightness();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_LIGHTNESS:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleLightness();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_INTENSITY:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleIntensity();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_CHROMA:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleChroma();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONB:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleSaturationB();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONL:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleSaturationL();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONI:
    {
        m_ImageTgt = m_ImageTgt.ToGrayScaleSaturationI();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_TO_NEGATIVE:
    {
        m_ImageTgt.Negative();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_THRESHOLD:
    {
        epi::mmVMImageThreshold vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "Thresholding"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_GAMMA_CORRECTION:
    {
        epi::mmVMImageGamma vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "Gamma Correction"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_CONTRAST_ADJUSTMENT:
    {
        epi::mmVMImageContrast vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "Contrast Adjustment"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_HSB_ADJUSTMENT:
    {
        epi::mmVMImageHSB vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "HSB Adjustment"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_HISTOGRAM_EQUALIZE:
    {
        m_ImageTgt.HistogramEqualize();
        Refresh();
    } break;
    case ID_IMAGE_PANEL_MEAN_FILTER:
    {
        const epi::dSeries2Df kernel = epi::dSeries2Df::Full(11 * 11, 11, 1.0f / (11 * 11));
        m_ImageTgt = m_ImageTgt.Convolve(kernel);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_MEDIAN_FILTER:
    {
        epi::mmVMImageMedian vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "Median Filter"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_SHARPENING:
    {
        epi::mmVMImageSharpening vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "Sharpening"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_GAUSSIAN_BLUR_FILTER:
    {
        const epi::dSeries2Df kernel = epi::dSeries2Df::Gaussian(11 * 11, 11, 4.0f);
        m_ImageTgt = m_ImageTgt.Convolve(kernel);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_FILTER:
    {
        epi::dSeries2Df kernel = epi::dSeries2Df::Full(3 * 3, 3, 0.0f);
        kernel.At(0, 1) = 1.0f;
        kernel.At(1, 0) = 1.0f;
        kernel.At(1, 1) = -4.0f;
        kernel.At(1, 2) = 1.0f;
        kernel.At(2, 1) = 1.0f;

        m_ImageTgt = m_ImageTgt.Convolve(kernel);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_VERTICAL_FILTER:
    {
        epi::dSeries2Df kernel = epi::dSeries2Df::Full(3 * 3, 3, 0.0f);
        kernel.At(0, 0) = -1.0f;
        kernel.At(0, 2) = +1.0f;
        kernel.At(1, 0) = -2.0f;
        kernel.At(1, 2) = +2.0f;
        kernel.At(2, 0) = -1.0f;
        kernel.At(2, 2) = +1.0f;

        m_ImageTgt = m_ImageTgt.Convolve(kernel);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_HORIZONTAL_FILTER:
    {
        epi::dSeries2Df kernel = epi::dSeries2Df::Full(3 * 3, 3, 0.0f);
        kernel.At(0, 0) = -1.0f;
        kernel.At(0, 1) = -2.0f;
        kernel.At(0, 2) = -1.0f;
        kernel.At(2, 0) = +1.0f;
        kernel.At(2, 1) = +2.0f;
        kernel.At(2, 2) = +1.0f;

        m_ImageTgt = m_ImageTgt.Convolve(kernel);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_SPATIALLY_ADAPTIVE_NOISE_FILTER:
    {
        epi::mmVMImageSpatialDenoising vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, m_GLAttrs, wxID_ANY, "Spatially Adaptive Noise Filter"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_CROP:
    {
        epiRect2u crop;
        crop.Left = 50;
        crop.Right = m_ImageTgt.GetWidth() - 50;
        crop.Bottom = 50;
        crop.Top = m_ImageTgt.GetHeight() - 50;

        m_ImageTgt = m_ImageTgt.Crop(crop);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_DFT_MAGNITUDE:
    {
        const epi::dSeries2Dc series = m_ImageTgt.ToSeries2Df().DFT_R2C();

        // TODO: open another image view
        epi::dSeries2Df seriesMagnitude = series.ToSeries2Df_Magnitude().DFT_RShift();
        seriesMagnitude.Transform([](epiFloat v)
        {
            return 10.0f * std::log10(v);
        });

        constexpr epiBool kClamp = false;
        m_ImageTgt = epi::mmImage::FromSeries2Df_ToGRAYSCALE(seriesMagnitude, kClamp);
        Refresh();
    } break;
    case ID_IMAGE_PANEL_DFT_PHASE:
    {
        const epi::dSeries2Dc series = m_ImageTgt.ToSeries2Df().DFT_R2C();

        // TODO: open another image view
        m_ImageTgt = epi::mmImage(series.ToSeries2Df_Phase());
        Refresh();
    } break;
    case ID_IMAGE_PANEL_PRESET_EFFECT0:
    {
        epi::mmImage r = m_ImageTgt.ToGrayScaleR();

        epi::mmImage intensity = m_ImageTgt.ToGrayScaleIntensity();
        intensity.Threshold(175, 175, 175);

        m_ImageTgt = m_ImageTgt.ToGrayScaleLuma();
        m_ImageTgt.ContrastStretch(0, 0, 0, 0, 0, 50);
        m_ImageTgt.Contrast(87, -92, 0);

        {
            epi::dSeries2Df kernelIdentity = epi::dSeries2Df::Full(3 * 3, 3, 0.0f);
            kernelIdentity.At(1, 1) = 1.0f;

            epi::dSeries2Df kernel = epi::dSeries2Df::Full(3 * 3, 3, 0.0f);
            kernel.At(0, 0) = -1.0f;
            kernel.At(0, 2) = +1.0f;
            kernel.At(1, 0) = -2.0f;
            kernel.At(1, 2) = +2.0f;
            kernel.At(2, 0) = -1.0f;
            kernel.At(2, 2) = +1.0f;

            m_ImageTgt = m_ImageTgt.Convolve(kernel, kernelIdentity, kernelIdentity);
        }

        {
            const epi::dSeries2Df kernel = epi::dSeries2Df::Full(5 * 5, 5, 1.0f / (5 * 5));
            m_ImageTgt = m_ImageTgt.Convolve(kernel);
            r.Convolve(kernel);
        }

        // TODO: consider intesity as an application mask
        m_ImageTgt.Overlap(intensity, epiVec2s{0, 0}, epi::Color(0.0f, 0.5f, 0.8f, 0.15f));
        m_ImageTgt.Overlap(r, epiVec2s{0, 0}, epi::Color(1.0f, 0.0f, 0.0f, 0.25f));
        m_ImageTgt.Overlap(r, epiVec2s{-15, -5}, epi::Color(1.0f, 0.0f, 0.0f, 0.1f));
        m_ImageTgt.Overlap(r, epiVec2s{-30, -10}, epi::Color(1.0f, 0.0f, 0.0f, 0.005f));

        Refresh();
    } break;
    }
}

void epiWXImagePanel::BuildContextMenu(wxMenu& contextMenu)
{
    contextMenu.Append(ID_IMAGE_PANEL_FIT_TO_SCREEN, wxT("&Fit to screen"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_R, wxT("&Convert to grayscale (R)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_G, wxT("&Convert to grayscale (G)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_B, wxT("&Convert to grayscale (B)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_A, wxT("&Convert to grayscale (A)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_MIN, wxT("&Convert to grayscale (Min)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_MAX, wxT("&Convert to grayscale (Max)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_HUE, wxT("&Convert to grayscale (Hue)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA, wxT("&Convert to grayscale (Luma)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA601, wxT("&Convert to grayscale (Luma601)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA240, wxT("&Convert to grayscale (Luma240)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA709, wxT("&Convert to grayscale (Luma709)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_LUMA2020, wxT("&Convert to grayscale (Luma2020)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_BRIGHTNESS, wxT("&Convert to grayscale (Brightness)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_LIGHTNESS, wxT("&Convert to grayscale (Lightness)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_INTENSITY, wxT("&Convert to grayscale (Intensity)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_CHROMA, wxT("&Convert to grayscale (Chroma)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONB, wxT("&Convert to grayscale (SaturationB)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONL, wxT("&Convert to grayscale (SaturationL)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_GRAYSCALE_SATURATIONI, wxT("&Convert to grayscale (SaturationI)"));
    contextMenu.Append(ID_IMAGE_PANEL_TO_NEGATIVE, wxT("&Convert to negative"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_THRESHOLD, wxT("&Thresholding"));
    contextMenu.Append(ID_IMAGE_PANEL_GAMMA_CORRECTION, wxT("&Gamma Correction"));
    contextMenu.Append(ID_IMAGE_PANEL_CONTRAST_ADJUSTMENT, wxT("&Contrast Adjustment"));
    contextMenu.Append(ID_IMAGE_PANEL_HSB_ADJUSTMENT, wxT("&HSB(HSV) Adjustment"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_HISTOGRAM_EQUALIZE, wxT("&Histogram equalize"));
    contextMenu.Append(ID_IMAGE_PANEL_MEAN_FILTER, wxT("&Mean Filter"));
    contextMenu.Append(ID_IMAGE_PANEL_MEDIAN_FILTER, wxT("&Median Filter"));
    contextMenu.Append(ID_IMAGE_PANEL_SHARPENING, wxT("&Sharpening"));
    contextMenu.Append(ID_IMAGE_PANEL_GAUSSIAN_BLUR_FILTER, wxT("&Gaussian Blur Filter"));
    contextMenu.Append(ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_FILTER, wxT("&Edge Detection Filter (Sobel)"));
    contextMenu.Append(ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_VERTICAL_FILTER, wxT("&Edge Detection Filter (Sobel Vertically)"));
    contextMenu.Append(ID_IMAGE_PANEL_EDGE_DETECTION_SOBEL_HORIZONTAL_FILTER, wxT("&Edge Detection Filter (Sobel Horizontally)"));
    contextMenu.Append(ID_IMAGE_PANEL_SPATIALLY_ADAPTIVE_NOISE_FILTER, wxT("&Spatially Adaptive Noise Filter"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_CROP, wxT("&Crop"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_DFT_MAGNITUDE, wxT("&DFT (Magnitude)"));
    contextMenu.Append(ID_IMAGE_PANEL_DFT_PHASE, wxT("&DFT (Phase)"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_PRESET_EFFECT0, wxT("&Effect Preset #0"));
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_RESET, wxT("&Reset"));
}

void epiWXImagePanel::ImageReset()
{
    m_ImageTgt = m_ImageSrc.Duplicate();
    ImageScale();
    m_ImagePosition = {};
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
    m_ImagePosition = {};
}

void epiWXImagePanel::ImageScale(epiFloat factor)
{
    // TODO: clamp `sizeScaled` instead of `m_ScaleFactor`
    m_ScaleFactor = std::clamp(factor, 0.0001f, 100.0f);

    Refresh();
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
