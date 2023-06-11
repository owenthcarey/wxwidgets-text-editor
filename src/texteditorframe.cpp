//
// Created by Owen Carey on 6/4/23.
//

#include "../include/texteditorframe.h"

wxBEGIN_EVENT_TABLE(TextEditorFrame, wxFrame)
                EVT_MENU(wxID_OPEN, TextEditorFrame::OnOpen)
                EVT_MENU(wxID_SAVE, TextEditorFrame::OnSave)
                EVT_MENU(wxID_EXIT, TextEditorFrame::OnExit)
wxEND_EVENT_TABLE()

TextEditorFrame::TextEditorFrame() : wxFrame(NULL, wxID_ANY, "wxWidgets Text Editor",
                                             wxDefaultPosition, wxSize(800, 600)) {
    textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                              wxDefaultSize, wxTE_MULTILINE);
    dirCtrl = new wxGenericDirCtrl(this, wxID_ANY, wxGetHomeDir(),
                                   wxDefaultPosition, wxSize(200, 600),
                                   wxDIRCTRL_DEFAULT_STYLE | wxSUNKEN_BORDER);
    dirCtrl->Bind(wxEVT_DIRCTRL_SELECTIONCHANGED, &TextEditorFrame::OnDirItemSelect,
                  this);
    wxBoxSizer *boxSizer = new wxBoxSizer(wxHORIZONTAL);
    boxSizer->Add(dirCtrl, 0, wxEXPAND);
    boxSizer->Add(textCtrl, 1, wxEXPAND);
    SetSizer(boxSizer);
    wxMenu *menu = new wxMenu;
    menu->Append(wxID_OPEN, "&Open\tCtrl-O", "Open a file");
    menu->Append(wxID_SAVE, "&Save\tCtrl-S", "Save to a file");
    menu->AppendSeparator();
    menu->Append(wxID_EXIT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menu, "&File");
    SetMenuBar(menuBar);
}

void TextEditorFrame::OnOpen(wxCommandEvent &WXUNUSED(event)) {
    wxFileDialog openFileDialog(this, _("Open file"), "", "",
                                "Text files (*.txt)|*.txt",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    wxFile file;
    file.Open(openFileDialog.GetPath());
    wxString str;
    file.ReadAll(&str);
    textCtrl->SetValue(str);
}

void TextEditorFrame::OnSave(wxCommandEvent &WXUNUSED(event)) {
    wxFileDialog saveFileDialog(this, _("Save file"), "", "",
                                "Text files (*.txt)|*.txt",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    wxFile file;
    file.Create(saveFileDialog.GetPath(), true);
    file.Write(textCtrl->GetValue());
    file.Close();
}

void TextEditorFrame::OnExit(wxCommandEvent &WXUNUSED(event)) {
    Close(true);
}

void TextEditorFrame::OnDirItemSelect(wxCommandEvent &event) {
    wxString path = dirCtrl->GetPath();
    if (wxDir::Exists(path)) {
        return;
    }
    wxFile file;
    if (file.Open(path)) {
        wxString str;
        file.ReadAll(&str);
        textCtrl->SetValue(str);
    } else {
        wxLogMessage("Failed to open file: %s", path);
    }
}
