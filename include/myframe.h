//
// Created by Owen Carey on 6/4/23.
//

#ifndef WXWIDGETS_TEXT_EDITOR_MYFRAME_H
#define WXWIDGETS_TEXT_EDITOR_MYFRAME_H

#include <wx/wx.h>
#include <wx/file.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/choice.h>
#include <wx/dirctrl.h>
#include <wx/dir.h>
#include <wx/stc/stc.h>
#include <wx/filename.h>
#include <wx/process.h>  // for wxProcess
#include <wx/textctrl.h> // for wxTextCtrl
#include <wx/txtstrm.h>  // for wxTextInputStream

class MyFrame : public wxFrame {
public:
    MyFrame();
    wxGenericDirCtrl *dirCtrl;
    wxStyledTextCtrl *textCtrl;
    wxTextCtrl *consoleCtrl;
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnDirItemSelect(wxCommandEvent &event);
    void SetupCppLexer();
    void SetupPythonLexer();
    wxString GetFileExtension(const wxString& fileName);
    void RunCommand(const wxString &command);
    void OnConsoleEnter(wxCommandEvent &event);

private:
wxDECLARE_EVENT_TABLE();
};

#endif //WXWIDGETS_TEXT_EDITOR_MYFRAME_H
