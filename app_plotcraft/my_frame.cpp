#include "my_frame.h"

#include <wx/sizer.h>

const int ID_LISTBOX = 5;

MyFrame::MyFrame(const wxString& title, IExampleFactory& example_factory)
    : wxFrame((wxFrame*)NULL, -1, title, wxPoint(50, 50), wxSize(800, 600)),
      example_factory_(example_factory) {
#ifdef _1_
  for (auto& it : examples_) {
    it->Execute();

    // content scale factor
    auto content_scale_factor = 2;

    wxBitmap bitmap = wxBitmap();
    bitmap.CreateWithDIPSize(800, 572, content_scale_factor, wxBITMAP_SCREEN_DEPTH);

    wxMemoryDC m_dc;
    m_dc.SelectObject(bitmap);
    wxGraphicsContext* gc = wxGraphicsContext::Create(m_dc);

    if (gc->SetAntialiasMode(wxAntialiasMode::wxANTIALIAS_DEFAULT)) {
      spdlog::info("Anti Aliasing enabled");
    }

    DrawPrimitives dp(*gc);
    if (gc) {
      double width = 0.0f;
      double height = 0.0f;
      gc->GetSize(&width, &height);
      auto& plot_craft = it->GetPlotcraftRef();
      plot_craft.Draw(dp, dp, 0, 0, width, height);
      delete gc;
    }

    m_dc.SelectObject(wxNullBitmap);
    std::string filename = "example" + std::to_string(i) + ".png";
    bitmap.SaveFile(filename, wxBitmapType::wxBITMAP_TYPE_PNG);

    i++;
  }

#endif
  listbox_ = new wxListBox((wxFrame*)this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

  Connect(wxEVT_LISTBOX, wxCommandEventHandler(MyFrame::OnSelect));

  for (int i = 0; i < example_factory_.Count(); i++) {
    auto title = example_factory_.GetTitle(i);
    listbox_->Append(title);
  }
  listbox_->Select(0);

  listbox_->SetMaxSize(wxSize(200, wxDefaultCoord));
  sizer_ = new wxBoxSizer(wxHORIZONTAL);
  sizer_->Add(listbox_, 10, wxEXPAND);

  active_example_ = example_factory_.Create(0);
  drawpane_ = new wxPlotcraft((wxFrame*)this, active_example_->GetPlotcraftRef());
  sizer_->Add(drawpane_, 40, wxEXPAND);

  SetSizer(sizer_);
  SetAutoLayout(true);
}

void MyFrame::OnSelect(wxCommandEvent& event) {
  int sel = listbox_->GetSelection();
  if (sel != -1) {
    spdlog::debug("OnSelect {}", sel);

    active_example_ = example_factory_.Create(sel);
    auto* drawpane_new = new wxPlotcraft((wxFrame*)this, active_example_->GetPlotcraftRef());

    sizer_->Replace(drawpane_, drawpane_new);
    drawpane_->Destroy();

    drawpane_ = drawpane_new;
    Layout();
  }
}

