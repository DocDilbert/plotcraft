#include "draw_pane.h"

BEGIN_EVENT_TABLE(DrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(DrawPane::mouseMoved)
 EVT_LEFT_DOWN(DrawPane::mouseDown)
 EVT_LEFT_UP(DrawPane::mouseReleased)
 EVT_RIGHT_DOWN(DrawPane::rightClick)
 EVT_LEAVE_WINDOW(DrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(DrawPane::keyPressed)
 EVT_KEY_UP(DrawPane::keyReleased)
 EVT_MOUSEWHEEL(DrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(DrawPane::paintEvent)

END_EVENT_TABLE()

// some useful events
/*
 void DrawPane::mouseMoved(wxMouseEvent& event) {}
 void DrawPane::mouseDown(wxMouseEvent& event) {}
 void DrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void DrawPane::mouseReleased(wxMouseEvent& event) {}
 Jvoid DrawPane::rightClick(wxMouseEvent& event) {}
 void DrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void DrawPane::keyPressed(wxKeyEvent& event) {}
 void DrawPane::keyReleased(wxKeyEvent& event) {}
 */

DrawPane::DrawPane(wxFrame* parent) : wxPanel(parent), plot_craft_(nullptr) {}

void DrawPane::SelectPlotCraftInstance(plotcraft::PlotCraft* plot_craft) {
  this->plot_craft_ = plot_craft;
}

void DrawPane::paintEvent(wxPaintEvent& evt) {
  bool mem_dc = false;
  if (mem_dc) {
    paintEventMemoryDc();
  } else {
    paintEventDc();
  }
}

void DrawPane::paintEventMemoryDc() {
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

  DrawPrimitives dp(*gc);
  if (gc) {
    double width = 0.0f;
    double height = 0.0f;
    gc->GetSize(&width, &height);
    plot_craft_->Draw(dp, dp, 0, 0, width, height);
    delete gc;
  }

  m_dc.SelectObject(wxNullBitmap);
  dc.DrawBitmap(bitmap, 0, 0);
  bitmap.SaveFile("test.png", wxBitmapType::wxBITMAP_TYPE_PNG);
}

void DrawPane::paintEventDc() {
  wxPaintDC dc(this);

  // Create graphics context from it
  wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

  if (gc->SetAntialiasMode(wxAntialiasMode::wxANTIALIAS_DEFAULT)) {
    spdlog::debug("Anti Aliasing enabled");
  }
  LogGraphicsContextOptions(*gc);

  DrawPrimitives dp(*gc);
  if (gc) {
    double width = 0.0f;
    double height = 0.0f;
    gc->GetSize(&width, &height);
    plot_craft_->Draw(dp, dp, 0, 0, width, height);
    delete gc;
  }
}

void DrawPane::LogBitmapOptions(wxBitmap& bitmap) {
  auto size = bitmap.GetSize();
  auto scale_factor = bitmap.GetScaleFactor();
  spdlog::debug(
      "wxBitmap options: \n"
      "  SizeX={}, SizeY={}\n"
      "  ScaleFactor={}"
      "  HasAlpha={}",
      size.x, size.y, scale_factor, bitmap.HasAlpha());
}

void DrawPane::LogGraphicsContextOptions(wxGraphicsContext& gc) {
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

