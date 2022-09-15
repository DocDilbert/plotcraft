#pragma once

#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>

#include <memory>
#include <vector>

#include "i_example_factory.h"
#include "plotcraft/plotcraft.h"

class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString& title, IExampleFactory& example_factory);

 private:
  void OnSelect(wxCommandEvent& event);

  wxPlotcraft* drawpane_;
  wxListBox* listbox_;
  wxBoxSizer* sizer_;
  wxPanel* content_panel_;

  IExampleFactory& example_factory_;
  std::shared_ptr<IExample> active_example_;
};
