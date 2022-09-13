#pragma once

#include <spdlog/spdlog.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/sizer.h>
#include <wx/wx.h>

#include "draw_primitives.h"
#include "plotcraft/plotcraft.h"

class DrawPane : public wxPanel {
 public:
  DrawPane(wxFrame* parent);

  void SelectPlotCraftInstance(plotcraft::PlotCraft* plot_craft);

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

  plotcraft::PlotCraft* plot_craft_;
};

