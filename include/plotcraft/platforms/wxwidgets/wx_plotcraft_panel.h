#pragma once

#include <spdlog/spdlog.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/panel.h>

#include <memory>

namespace plotcraft {
class PlotCraft;
}

class wxPlotCraftPanel : public wxPanel {
 public:
  wxPlotCraftPanel(wxFrame* parent, plotcraft::PlotCraft& plot_craft);
  virtual ~wxPlotCraftPanel();

  void paintEvent(wxPaintEvent& evt);
  void paintEventMemoryDc();
  void paintEventDc();

  // some useful events
  /*
   void mouseMoved(wxMouseEvent& event);
   void mouseDown(wxMouseEvent& event);
   void mouseWheelMoved(wxMouseEvent& event);
   void mouseReleased(wxMouseEvent& event);
   void rightClick(wxMouseEvent& event);
   void mouseLeftWindow(wxMouseEvent& event);
   void keyPressed(wxKeyEvent& event);
   void keyReleased(wxKeyEvent& event);
   */

  DECLARE_EVENT_TABLE()

 private:
  void LogBitmapOptions(wxBitmap& bitmap);
  void LogGraphicsContextOptions(wxGraphicsContext& gc);

  struct wxPlotCraftImpl;
  std::unique_ptr<wxPlotCraftImpl> pimpl_;
  plotcraft::PlotCraft& plot_craft_;
};

