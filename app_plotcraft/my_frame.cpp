#include "my_frame.h"

const int ID_LISTBOX = 5;

MyFrame::MyFrame(const wxString& title, const std::vector<std::shared_ptr<IExample>> examples)
    : wxFrame((wxFrame*)NULL, -1, title, wxPoint(50, 50), wxSize(800, 600)), examples_(examples) {
  int i = 0;
  for (auto& it : examples_) {
    it->Execute();

#ifdef _1_
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

#endif
    i++;
  }

  drawpane_ = new DrawPane((wxFrame*)this);
  drawpane_->SelectPlotCraftInstance(&examples_[0]->GetPlotcraftRef());
  listbox_ = new wxListBox((wxFrame*)this, ID_LISTBOX, wxDefaultPosition, wxDefaultSize);

  Connect(wxEVT_LISTBOX, wxCommandEventHandler(MyFrame::OnSelect));

  i = 0;
  for (auto& it : examples_) {
    listbox_->Append(it->GetTitle());
  }
  listbox_->Select(0);

  listbox_->SetMaxSize(wxSize(200, wxDefaultCoord));
  wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(listbox_, 10, wxEXPAND);
  sizer->Add(drawpane_, 40, wxEXPAND);

  SetSizer(sizer);
  SetAutoLayout(true);
}

void MyFrame::OnSelect(wxCommandEvent& event) {
  int sel = listbox_->GetSelection();
  if (sel != -1) {
    spdlog::info("OnSelect {}", sel);

    drawpane_->SelectPlotCraftInstance(&examples_[sel]->GetPlotcraftRef());
  }
  drawpane_->Refresh();
}

