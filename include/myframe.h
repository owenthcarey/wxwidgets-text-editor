//
// Created by Owen Carey on 6/4/23.
//

#ifndef WXWIDGETS_TEXT_EDITOR_MYFRAME_H
#define WXWIDGETS_TEXT_EDITOR_MYFRAME_H

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/dirctrl.h>
#include <wx/dir.h>

class MyFrame : public wxFrame {
public:
    MyFrame();
    wxGenericDirCtrl *dirCtrl;
    wxTextCtrl *textCtrl;
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnDirItemSelect(wxCommandEvent &event);

private:
wxDECLARE_EVENT_TABLE();
};

#endif //WXWIDGETS_TEXT_EDITOR_MYFRAME_H
