#pragma once
#include <spdlog/spdlog.h>
#include <wx/dcgraph.h>
#include <wx/graphics.h>
#include <wx/panel.h>

#include <map>
#include <memory>

#include "plotcraft/platforms/wxwidgets/wx_draw_primitives.h"

class wxDrawContext {
 public:
  bool Prepare(int width, int height) {
    bitmap_ = std::make_unique<wxBitmap>(width, height, wxBITMAP_SCREEN_DEPTH);

    // LogBitmapOptions(bitmap);

    memory_dc_ = std::make_unique<wxMemoryDC>();
    memory_dc_->SelectObject(*bitmap_);
    gc_ = std::unique_ptr<wxGraphicsContext>(wxGraphicsContext::Create(*memory_dc_));

    if (gc_) {
      if (gc_->SetAntialiasMode(wxAntialiasMode::wxANTIALIAS_DEFAULT)) {
        spdlog::info("Anti Aliasing enabled");
      }
      dp_ = std::make_unique<wxDrawPrimitives>(*gc_);
      return true;
    }

    return false;
  }

  void Post(std::map<std::string, std::string> options) {
    auto it = options.find("filename");
    if (it == options.end()) {
      throw std::exception();
    }

    auto filename = it->second;
    memory_dc_->SelectObject(wxNullBitmap);
    bitmap_->SaveFile(filename, wxBitmapType::wxBITMAP_TYPE_PNG);
    dp_.reset();
    gc_.reset();
    bitmap_.reset();
    memory_dc_.reset();
  };

  plotcraft::presenter::IDrawPrimitives& GetDrawPrimitives() { return *dp_; }
  plotcraft::gateway::IMeasure& GetMeasure() { return *dp_; }

 private:
  std::unique_ptr<wxBitmap> bitmap_;
  std::unique_ptr<wxGraphicsContext> gc_;
  std::unique_ptr<wxDrawPrimitives> dp_;
  std::unique_ptr<wxMemoryDC> memory_dc_;
};
