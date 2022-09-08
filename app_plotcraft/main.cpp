#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <wx/graphics.h>
#include <wx/sizer.h>
#include <wx/wx.h>

#include <cxxopts.hpp>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <utility>

#include "plotcraft/plotcraft.h"

int ParseCommandLine(int argc, const char** argv) {
  cxxopts::Options options("app_plotcraft", "One line description of \"app_plotcraft\"");

  options.positional_help("<filenames>");

  // clang-format off
  options.add_options()
    ("l,filelist", "Print out file list to be read") // a bool parameter
    ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage")
    ("input_files", "Input file(s) to concatenate",cxxopts::value<std::vector<std::string>>())
    ;
  // clang-format on

  // parse positional arguments into vector filenames
  options.parse_positional({"input_files"});

  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (const cxxopts::OptionParseException& x) {
    std::cerr << "app_plotcraft: " << x.what() << '\n';
    std::cerr << "usage: app_plotcraft [options] <filenames> ...\n";
    return EXIT_FAILURE;
  }

  // print out help if necessary
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return EXIT_SUCCESS;
  }

  // Enable logging
  switch (result.count("verbose")) {
    case 0:
      // no output
      break;
    case 1:
      std::cout << "verbose:1\n";
      break;
    case 2:
      std::cout << "verbose:2\n";
      break;
    default:
      std::cout << "verbose:?\n";
      break;
  }

  if (result.count("filelist")) {
    std::cout << "filelist command \n";
    const auto files = result["input_files"].as<std::vector<std::string>>();
    for (const auto& file : files) {
      std::cout << "- " << file << "\n";
    }
  }
  return EXIT_SUCCESS;
}

class DrawPrimitives : public plotcraft::presenter::IDrawPrimitives,
                       public plotcraft::gateway::IMeasure {
 public:
  DrawPrimitives(wxGraphicsContext& gc) : gc_(gc) {}

  void DrawText(std::string text, double x, double y, double angle) override {
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);

    // change coordinate system
    auto x_n = x;
    auto y_n = screen_height - y;

    spdlog::debug("DrawText(\"{}\", {}, {}, angle={})", text, x_n, y_n, angle);
    gc_.DrawText(text, x_n, y_n, angle);
  };

  void DrawLine(double x0, double y0, double x1, double y1) override {
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);
    gc_.StrokeLine(x0, screen_height - y0, x1, screen_height - y1);
  }

  const wxColour& GetColor(const std::string& color) {
    if (color == "black") {
      auto& ret = *wxBLACK;
      return ret;
    } else if (color == "white") {
      auto& ret = *wxWHITE;
      return ret;
    } else if (color == "red") {
      auto& ret = *wxRED;
      return ret;
    } else if (color == "green") {
      auto& ret = *wxGREEN;
      return ret;
    } else if (color == "blue") {
      auto& ret = *wxBLUE;
      return ret;
    }
    auto& ret = *wxBLACK;
    return ret;
  }

  void SetPen(std::string color, double width) override {
    spdlog::debug("SetPen(\"{}\", {})", color, width);
    auto& color_obj = GetColor(color);
    auto pen = gc_.CreatePen(wxGraphicsPenInfo(color_obj).Width(width));
    gc_.SetPen(pen);
  }

  void SetFont(std::string font_name, std::string color, double size) override {
    spdlog::debug("SetFont(\"{}\", \"{}\", {})", font_name, color, size);
    wxFontWeight font_weight = wxFontWeight::wxFONTWEIGHT_NORMAL;
    if (font_name == "bold") {
      font_weight = wxFontWeight::wxFONTWEIGHT_SEMIBOLD;
    }

    wxFont font(size, wxFONTFAMILY_SWISS, wxFONTSTYLE_MAX, font_weight);

    auto& color_obj = GetColor(color);
    auto gc_font = gc_.CreateFont(font, color_obj);
    gc_.SetFont(gc_font);
  }

  void SetBrush(std::string color) override {
    spdlog::debug("SetBrush(\"{}\")", color);
    if (color == "black") {
      auto& brush = *wxBLACK_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "white") {
      auto& brush = *wxWHITE_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "red") {
      auto& brush = *wxRED_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "green") {
      auto& brush = *wxGREEN_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "blue") {
      auto& brush = *wxBLUE_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    } else if (color == "transparent") {
      auto& brush = *wxTRANSPARENT_BRUSH;
      auto gc_brush = gc_.CreateBrush(brush);
      gc_.SetBrush(gc_brush);
    }
  }

  void DrawRect(double left, double bottom, double width, double height) override {
    // x (0,0)
    // |
    // |  x (left, bottom + height)
    // |  |
    // |  |
    // |  x (left, bottom)
    // |
    // x  (0, display_height)
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);

    // change coordinate system
    auto x = left;
    auto y = screen_height - (bottom + height);
    spdlog::debug("DrawRect({},{},{},{})", x, y, width, height);
    gc_.DrawRectangle(x, y, width, height);
  }

  void Clip(double left, double bottom, double width, double height) override {
    // x (0,0)
    // |
    // |  x (left, bottom + height)
    // |  |
    // |  |
    // |  x (left, bottom)
    // |
    // x  (0, display_height)
    double screen_height = 0.0f;
    double screen_width = 0.0f;
    gc_.GetSize(&screen_width, &screen_height);

    // change coordinate system
    auto x = left;
    auto y = screen_height - (bottom + height);
    spdlog::debug("Clip({},{},{},{})", x, y, width, height);
    gc_.Clip(x, y, width, height);
  }

  void ResetClip() override {
    spdlog::debug("ResetClip");
    gc_.ResetClip();
  }

  plotcraft::gateway::TextExtent GetTextExtent(const std::string& text,
                                               const std::string& font_name, double size) override {
    SetFont(font_name, "black", size);
    plotcraft::gateway::TextExtent text_extent;
    gc_.GetTextExtent(text, &text_extent.width, &text_extent.height, &text_extent.descent,
                      &text_extent.externalLeading);
    spdlog::debug("GetTextExtent(\"{}\",{},{},{},{})", text, text_extent.width, text_extent.height,
                  text_extent.descent, text_extent.externalLeading);
    return text_extent;
  }

 private:
  wxGraphicsContext& gc_;
};

class BasicDrawPane : public wxPanel {
 public:
  BasicDrawPane(wxFrame* parent, plotcraft::PlotCraft& plot_craft);

  void paintEvent(wxPaintEvent& evt);
  void paintNow();

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
  plotcraft::PlotCraft& plot_craft_;
};

class MyApp : public wxApp {
  bool OnInit();

  wxFrame* frame;
  BasicDrawPane* drawPane;

 public:
  plotcraft::PlotCraft plot_craft_;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  frame = new wxFrame((wxFrame*)NULL, -1, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

  plot_craft_.Figure();

  std::vector<double> m_x;
  std::vector<double> m_y_1;
  std::vector<double> m_y_2;

  const int steps = 50;
  for (auto i = 0; i < steps; i++) {
    double x = static_cast<double>(i) / static_cast<double>(steps - 1) * M_PI * -10.0;
    double sin_arg = 2.0 * M_PI / (static_cast<double>(steps - 1)) * static_cast<double>(i);
    double y1 = 1.1 * sin(2.0 * sin_arg) - 2.0;
    double y2 = 0.9 * sin(sin_arg + M_PI * 0.25) - 2.0;
    m_x.push_back(x);
    m_y_1.push_back(y1);
    m_y_2.push_back(y2);
  }

  plot_craft_.Plot(m_x, m_y_1,
                   {{"label", "My Measurement 1"}, {"color", "blue"}, {"markerstyle", "+"}});
  plot_craft_.Plot(m_x, m_y_2,
                   {{"label", "My Measurement 2"}, {"color", "red"}, {"markerstyle", ""}});

  // plot_craft_.Xlim(-40, 0.0);
  // plot_craft_.Ylim(-1.3, 1.25);
  plot_craft_.YLabel("Voltage (V)");
  // plot_craft_.YLabel("XXX");
  plot_craft_.XLabel("Time(s)");
  plot_craft_.Title("My Title");
  drawPane = new BasicDrawPane((wxFrame*)frame, plot_craft_);
  sizer->Add(drawPane, 1, wxEXPAND);

  frame->SetSizer(sizer);
  frame->SetAutoLayout(true);

  frame->Show();
  return true;
}

BEGIN_EVENT_TABLE(BasicDrawPane, wxPanel)
// some useful events
/*
 EVT_MOTION(BasicDrawPane::mouseMoved)
 EVT_LEFT_DOWN(BasicDrawPane::mouseDown)
 EVT_LEFT_UP(BasicDrawPane::mouseReleased)
 EVT_RIGHT_DOWN(BasicDrawPane::rightClick)
 EVT_LEAVE_WINDOW(BasicDrawPane::mouseLeftWindow)
 EVT_KEY_DOWN(BasicDrawPane::keyPressed)
 EVT_KEY_UP(BasicDrawPane::keyReleased)
 EVT_MOUSEWHEEL(BasicDrawPane::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(BasicDrawPane::paintEvent)

END_EVENT_TABLE()

// some useful events
/*
 void BasicDrawPane::mouseMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseDown(wxMouseEvent& event) {}
 void BasicDrawPane::mouseWheelMoved(wxMouseEvent& event) {}
 void BasicDrawPane::mouseReleased(wxMouseEvent& event) {}
 void BasicDrawPane::rightClick(wxMouseEvent& event) {}
 void BasicDrawPane::mouseLeftWindow(wxMouseEvent& event) {}
 void BasicDrawPane::keyPressed(wxKeyEvent& event) {}
 void BasicDrawPane::keyReleased(wxKeyEvent& event) {}
 */

BasicDrawPane::BasicDrawPane(wxFrame* parent, plotcraft::PlotCraft& plot_craft)
    : wxPanel(parent), plot_craft_(plot_craft) {}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void BasicDrawPane::paintEvent(wxPaintEvent& evt) {
  wxPaintDC dc(this);

  // Create graphics context from it
  wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
  if (gc->SetAntialiasMode(wxAntialiasMode::wxANTIALIAS_DEFAULT)) {
    spdlog::info("Anti Aliasing enabled");
  }
  DrawPrimitives dp(*gc);
  if (gc) {
    auto size = dc.GetSize();
    plot_craft_.Draw(dp, dp, 0, 0, size.GetWidth(), size.GetHeight());
    delete gc;
  }
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void BasicDrawPane::paintNow() {
  wxClientDC dc(this);

  wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
  DrawPrimitives dp(*gc);

  if (gc) {
    auto size = dc.GetSize();
    plot_craft_.Draw(dp, dp, 0, 0, size.GetWidth(), size.GetHeight());
    delete gc;
  }
}

