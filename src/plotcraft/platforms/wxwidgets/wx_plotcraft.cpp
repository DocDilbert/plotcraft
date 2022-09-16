#include "plotcraft/platforms/wxwidgets/wx_plotcraft.h"

#include <spdlog/spdlog.h>

#include "plotcraft/platforms/wxwidgets/wx_draw_primitives.h"
#include "plotcraft/plotcraft.h"

BEGIN_EVENT_TABLE(wxPlotcraft, wxPanel)
// some useful events
/*
 EVT_MOTION(wxPlotcraft::mouseMoved)
 EVT_LEFT_DOWN(wxPlotcraft::mouseDown)
 EVT_LEFT_UP(wxPlotcraft::mouseReleased)
 EVT_RIGHT_DOWN(wxPlotcraft::rightClick)
 EVT_LEAVE_WINDOW(wxPlotcraft::mouseLeftWindow)
 EVT_KEY_DOWN(wxPlotcraft::keyPressed)
 EVT_KEY_UP(wxPlotcraft::keyReleased)
 EVT_MOUSEWHEEL(wxPlotcraft::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(wxPlotcraft::paintEvent)

END_EVENT_TABLE()

struct wxPlotcraft::wxPlotCraftImpl {};
// some useful events
/*
 void wxPlotcraft::mouseMoved(wxMouseEvent& event) {}
 void wxPlotcraft::mouseDown(wxMouseEvent& event) {}
 void wxPlotcraft::mouseWheelMoved(wxMouseEvent& event) {}
 void wxPlotcraft::mouseReleased(wxMouseEvent& event) {}
 Jvoid wxPlotcraft::rightClick(wxMouseEvent& event) {}
 void wxPlotcraft::mouseLeftWindow(wxMouseEvent& event) {}
 void wxPlotcraft::keyPressed(wxKeyEvent& event) {}
 void wxPlotcraft::keyReleased(wxKeyEvent& event) {}
 */

wxPlotcraft::wxPlotcraft(wxFrame* parent, plotcraft::PlotCraft& plot_craft)
    : wxPanel(parent),
      pimpl_(std::make_unique<wxPlotcraft::wxPlotCraftImpl>()),
      plot_craft_(plot_craft) {}

wxPlotcraft::~wxPlotcraft() { spdlog::trace("wxPlotcraft: Destructor called"); }

void wxPlotcraft::paintEvent(wxPaintEvent& evt) {
  bool mem_dc = false;
  if (mem_dc) {
    paintEventMemoryDc();
  } else {
    paintEventDc();
  }
}

void wxPlotcraft::paintEventMemoryDc() {
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

void wxPlotcraft::paintEventDc() {
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

void wxPlotcraft::LogBitmapOptions(wxBitmap& bitmap) {
  auto size = bitmap.GetSize();
  auto scale_factor = bitmap.GetScaleFactor();
  spdlog::debug(
      "wxBitmap options: \n"
      "  SizeX={}, SizeY={}\n"
      "  ScaleFactor={}"
      "  HasAlpha={}",
      size.x, size.y, scale_factor, bitmap.HasAlpha());
}

void wxPlotcraft::LogGraphicsContextOptions(wxGraphicsContext& gc) {
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

