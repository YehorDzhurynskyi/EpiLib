#include "EpiwxWidgets/epiWXImagePanel.h"

#include "EpiwxWidgets/epiWXObjectConfigurationPanel.h"


#include "EpiMultimedia/Image/ViewModel/mmVMImageBase.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageContrast.h"
#include "EpiMultimedia/Image/ViewModel/mmVMImageHSB.h"

#include <wx/dcclient.h>
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

    sizer->Add(contentSizer, wxSizerFlags().Expand());

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, "OK"), 0, wxALL, 10);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 10);

    sizer->Add(buttonSizer, wxSizerFlags().Right());

    SetSizerAndFit(sizer);

    CenterOnParent();
}

void epiWXImageConfigurationDialog::OnImageUpdated(wxCommandEvent& event)
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
}

wxBEGIN_EVENT_TABLE(epiWXImagePanel, wxPanel)
    EVT_PAINT(epiWXImagePanel::OnPaint)
    EVT_MOUSE_EVENTS(epiWXImagePanel::OnMouse)
    EVT_MENU(wxID_ANY, epiWXImagePanel::OnMenu)
wxEND_EVENT_TABLE()

void epiWXImagePanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);

    if (wxBitmap bitmapToDraw = ToWXImage(m_ImageTgt).Scale(m_ImageTgt.GetWidth() * m_ScaleFactor, m_ImageTgt.GetHeight() * m_ScaleFactor, wxIMAGE_QUALITY_NEAREST);
        bitmapToDraw.IsOk())
    {
        const wxSize& sizeHalfClient = GetClientSize() / 2;
        const wxSize& sizeHalfImage = bitmapToDraw.GetSize() / 2;
        dc.DrawBitmap(bitmapToDraw, sizeHalfClient.x - sizeHalfImage.x, sizeHalfClient.y - sizeHalfImage.y, false);
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
    case ID_IMAGE_PANEL_CONTRAST_ADJUSTMENT:
    {
        epi::mmVMImageContrast vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, wxID_ANY, "Contrast Adjustment"); dialog.ShowModal() == wxID_OK)
        {
            m_ImageTgt = vm.GetImageTgt();
            Refresh();
        }
    } break;
    case ID_IMAGE_PANEL_HSB_ADJUSTMENT:
    {
        epi::mmVMImageHSB vm;
        vm.SetImageSrc(&m_ImageTgt);

        if (epiWXImageConfigurationDialog dialog(vm, this, wxID_ANY, "HSB Adjustment"); dialog.ShowModal() == wxID_OK)
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
    }
}

void epiWXImagePanel::BuildContextMenu(wxMenu& contextMenu)
{
    contextMenu.Append(ID_IMAGE_PANEL_FIT_TO_SCREEN, wxT("&Fit to screen"));
    contextMenu.AppendSeparator();
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
    contextMenu.AppendSeparator();
    contextMenu.Append(ID_IMAGE_PANEL_CONTRAST_ADJUSTMENT, wxT("&Contrast Adjustment"));
    contextMenu.Append(ID_IMAGE_PANEL_HSB_ADJUSTMENT, wxT("&HSB(HSV) Adjustment"));
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
