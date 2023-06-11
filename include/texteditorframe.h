//
// Created by Owen Carey on 6/4/23.
//

#ifndef WXWIDGETS_TEXT_EDITOR_TEXTEDITORFRAME_H
#define WXWIDGETS_TEXT_EDITOR_TEXTEDITORFRAME_H

#include <wx/dir.h>
#include <wx/dirctrl.h>
#include <wx/file.h>
#include <wx/wx.h>

class TextEditorFrame : public wxFrame {
public:
    TextEditorFrame();

private:
    wxGenericDirCtrl *dirCtrl;
    wxTextCtrl *textCtrl;
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnDirItemSelect(wxCommandEvent &event);
    wxDECLARE_EVENT_TABLE();
};

#endif //WXWIDGETS_TEXT_EDITOR_TEXTEDITORFRAME_H
