#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <wx/wx.h>

#include <cxxopts.hpp>
#include <iostream>
#include <memory>
#include <utility>

#include "example_factory.h"
#include "example_multiple1.h"
#include "example_single1.h"
#include "example_single2.h"
#include "my_frame.h"

typedef ExampleFactory<ExampleSingle1, ExampleSingle2, ExampleMultiple1> AllExampleFactory;

class MyApp : public wxApp {
  bool OnInit();

  int OnRun();
  int OnExit();

  bool DoParseCommandLine(int argc, const char** argv);

 private:
  bool saveall_ = {false};
  MyFrame* frame_;
  AllExampleFactory example_factory_;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  // Parse command line options with cxxopts
  // The wxwidgets command line options parser doesn't support some crucial options

  // the argv type has an overload so that it can be casted safely to (char**)
  char** cargv = (char**)argv;

  // ugly hack ... Assume that the values will not change in the future
  const char** ccargv = const_cast<const char**>(cargv);

  if (!DoParseCommandLine(argc, ccargv)) {
    return false;
  }

  spdlog::info("WxWidgets Version: {}.{}.{}.{}", wxMAJOR_VERSION, wxMINOR_VERSION, wxRELEASE_NUMBER,
               wxSUBRELEASE_NUMBER);

  wxInitAllImageHandlers();
  if (saveall_) {
    for (int i = 0; i < example_factory_.Count(); i++) {
      auto title = example_factory_.GetTitle(i);

      auto example = example_factory_.Create(i);
      auto& plotcraft = example->GetPlotcraftRef();
      plotcraft.SaveFig(title + ".png");
    }
    return false;
  } else {
    frame_ = new MyFrame(wxT("Hello wxDC"), example_factory_);
    frame_->Show();
  }
  return true;
}

int MyApp::OnRun() {
  spdlog::debug("OnRun");
  return wxApp::OnRun();
}

int MyApp::OnExit() {
  spdlog::debug("OnExit");
  return wxApp::OnExit();
}

bool MyApp::DoParseCommandLine(int argc, const char** argv) {
  cxxopts::Options options("app_plotcraft", "One line description of \"app_plotcraft\"");

  // clang-format off
  options.add_options()
    ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
    ("s,saveall", "Save all examples to png",  cxxopts::value<bool>()->default_value("false"))
    ("h,help", "Print usage")
    ;
  // clang-format on

  // parse positional arguments into vector filenames

  cxxopts::ParseResult result;
  try {
    result = options.parse(argc, argv);
  } catch (const cxxopts::OptionParseException& x) {
    std::cerr << "app_plotcraft: " << x.what() << '\n';
    std::cerr << "usage: app_plotcraft [options] <filenames> ...\n";
    return false;
  }

  // print out help if necessary
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return false;
  }
  saveall_ = result["saveall"].as<bool>();
  // Enable logging
  switch (result.count("verbose")) {
    case 0:
      spdlog::set_level(spdlog::level::off);
      break;
    case 1:
      spdlog::set_level(spdlog::level::info);
      break;
    case 2:
      spdlog::set_level(spdlog::level::debug);
      break;
    default:
      spdlog::set_level(spdlog::level::trace);
      break;
  }

  return true;
}
