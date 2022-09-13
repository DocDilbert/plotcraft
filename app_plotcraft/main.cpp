#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <wx/wx.h>

#include <cxxopts.hpp>
#include <iostream>
#include <memory>
#include <utility>

#include "example1.h"
#include "example2.h"
#include "i_example.h"
#include "my_frame.h"

class MyApp : public wxApp {
  bool OnInit();

  int OnRun();
  int OnExit();

  bool DoParseCommandLine(int argc, const char** argv);
  MyFrame* frame;
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

  std::vector<std::shared_ptr<IExample>> examples;
  examples.push_back(std::make_shared<Example1>());
  examples.push_back(std::make_shared<Example2>());

  frame = new MyFrame(wxT("Hello wxDC"), examples);

  frame->Show();
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
