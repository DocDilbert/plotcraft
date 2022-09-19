#include "my_frame.h"

#include <wx/sizer.h>

const int ID_LISTBOX = 5;

MyFrame::MyFrame(const wxString& title, IExampleFactory& example_factory)
    : wxFrame((wxFrame*)NULL, -1, title, wxPoint(50, 50), wxSize(800, 600)),
      example_factory_(example_factory) {
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
  drawpane_ = new plotcraft::wxPlotCraftPanel((wxFrame*)this, active_example_->GetPlotcraftRef());
  sizer_->Add(drawpane_, 40, wxEXPAND);

  SetSizer(sizer_);
  SetAutoLayout(true);
}

void MyFrame::OnSelect(wxCommandEvent& event) {
  int sel = listbox_->GetSelection();
  if (sel != -1) {
    spdlog::debug("OnSelect {}", sel);

    active_example_ = example_factory_.Create(sel);
    auto* drawpane_new =
        new plotcraft::wxPlotCraftPanel((wxFrame*)this, active_example_->GetPlotcraftRef());

    sizer_->Replace(drawpane_, drawpane_new);
    drawpane_->Destroy();

    drawpane_ = drawpane_new;
    Layout();
  }
}

