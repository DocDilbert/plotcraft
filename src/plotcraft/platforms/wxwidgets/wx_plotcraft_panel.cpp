#include "plotcraft/platforms/wxwidgets/wx_plotcraft_panel.h"

#include <spdlog/spdlog.h>

#include "plotcraft/platforms/wxwidgets/wx_draw_primitives.h"
#include "plotcraft/plotcraft.h"

namespace plotcraft {
namespace platform {
namespace wxwidgets {

BEGIN_EVENT_TABLE(wxPlotCraftPanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxPlotCraftPanel::mouseMoved)
 EVT_LEFT_DOWN(wxPlotCraftPanel::mouseDown)
 EVT_LEFT_UP(wxPlotCraftPanel::mouseReleased)
 EVT_RIGHT_DOWN(wxPlotCraftPanel::rightClick)
 EVT_LEAVE_WINDOW(wxPlotCraftPanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxPlotCraftPanel::keyPressed)
 EVT_KEY_UP(wxPlotCraftPanel::keyReleased)
 EVT_MOUSEWHEEL(wxPlotCraftPanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(wxPlotCraftPanel::paintEvent)

END_EVENT_TABLE()

struct wxPlotCraftPanel::wxPlotCraftImpl {};
// some useful events
/*
 void wxPlotCraftPanel::mouseMoved(wxMouseEvent& event) {}
 void wxPlotCraftPanel::mouseDown(wxMouseEvent& event) {}
 void wxPlotCraftPanel::mouseWheelMoved(wxMouseEvent& event) {}
 void wxPlotCraftPanel::mouseReleased(wxMouseEvent& event) {}
 Jvoid wxPlotCraftPanel::rightClick(wxMouseEvent& event) {}
 void wxPlotCraftPanel::mouseLeftWindow(wxMouseEvent& event) {}
 void wxPlotCraftPanel::keyPressed(wxKeyEvent& event) {}
 void wxPlotCraftPanel::keyReleased(wxKeyEvent& event) {}
 */

wxPlotCraftPanel::wxPlotCraftPanel(wxFrame* parent, plotcraft::PlotCraft& plot_craft)
    : wxPanel(parent),
      pimpl_(std::make_unique<wxPlotCraftPanel::wxPlotCraftImpl>()),
      plot_craft_(plot_craft) {}

wxPlotCraftPanel::~wxPlotCraftPanel() { spdlog::trace("wxPlotCraftPanel: Destructor called"); }

void wxPlotCraftPanel::paintEvent(wxPaintEvent& evt) {
  bool mem_dc = false;
  if (mem_dc) {
    paintEventMemoryDc();
  } else {
    paintEventDc();
  }
}

void wxPlotCraftPanel::paintEventMemoryDc() {
  wxPaintDC dc(this);

  auto content_scale_factor = GetContentScaleFactor();

  wxBitmap bitmap = wxBitmap();
  bitmap.CreateWithDIPSize(800, 572, content_scale_factor, wxBITMAP_SCREEN_DEPTH);

  LogBitmapOptions(bitmap);

  wxMemoryDC m_dc;
  m_dc.SelectObject(bitmap);
  wxGraphicsContext* gc = wxGraphicsContext::Create(m_dc);

  if (gc->SetAntialiasMode(wxAntialiasMode::wxANTIALIAS_DEFAULT)) {
    spdlog::info("Anti Aliasing enabled");
  }
  LogGraphicsContextOptions(*gc);

  wxDrawPrimitives dp(*gc);
  if (gc) {
    double width = 0.0f;
    double height = 0.0f;
    gc->GetSize(&width, &height);
    plot_craft_.Draw(dp, dp, 0, 0, width, height);
    delete gc;
  }

  m_dc.SelectObject(wxNullBitmap);
  dc.DrawBitmap(bitmap, 0, 0);
}

void wxPlotCraftPanel::paintEventDc() {
  wxPaintDC dc(this);

  // Create graphics context from it
  wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

  if (gc->SetAntialiasMode(wxAntialiasMode::wxANTIALIAS_DEFAULT)) {
    spdlog::debug("Anti Aliasing enabled");
  }
  LogGraphicsContextOptions(*gc);

  wxDrawPrimitives dp(*gc);
  if (gc) {
    double width = 0.0f;
    double height = 0.0f;
    gc->GetSize(&width, &height);
    plot_craft_.Draw(dp, dp, 0, 0, width, height);
    delete gc;
  }
}

void wxPlotCraftPanel::LogBitmapOptions(wxBitmap& bitmap) {
  auto size = bitmap.GetSize();
  auto scale_factor = bitmap.GetScaleFactor();
  spdlog::debug(
      "wxBitmap options: \n"
      "  SizeX={}, SizeY={}\n"
      "  ScaleFactor={}"
      "  HasAlpha={}",
      size.x, size.y, scale_factor, bitmap.HasAlpha());
}

void wxPlotCraftPanel::LogGraphicsContextOptions(wxGraphicsContext& gc) {
  auto aamode = gc.GetAntialiasMode();
  auto ipoqual = gc.GetInterpolationQuality();
  auto compmode = gc.GetCompositionMode();

  double dpix, dpiy;
  gc.GetDPI(&dpix, &dpiy);
  auto scale_factor = gc.FromDIP(1000);
  auto content_scale_factor = gc.GetContentScaleFactor();
  spdlog::debug(
      "wxGraphicsContext options:\n"
      "  AntialiasMode={}, InterpolationQuality={}, CompositionMode={}, \n"
      "  DpiX={}, DpiY={}, FromDpi(1000)={}, \n"
      "  ContentScaleFactor={}",
      aamode, ipoqual, compmode, dpix, dpiy, scale_factor, content_scale_factor);
}

}  // namespace wxwidgets
}  // namespace platform
}  // namespace plotcraft
