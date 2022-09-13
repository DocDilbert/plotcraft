#pragma once

#include <wx/frame.h>

#include <memory>
#include <vector>

#include "draw_pane.h"
#include "i_example.h"

class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString& title, const std::vector<std::shared_ptr<IExample>> examples);

 private:
  void OnSelect(wxCommandEvent& event);

  DrawPane* drawpane_;
  wxListBox* listbox_;

  const std::vector<std::shared_ptr<IExample>> examples_;
};
