//
// Created by Owen Carey on 6/4/23.
//

#include "../include/myframe.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
                EVT_MENU(wxID_SAVE, MyFrame::OnSave)
                EVT_MENU(wxID_EXIT, MyFrame::OnExit)
wxEND_EVENT_TABLE()

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "wxWidgets Text Editor",
                             wxDefaultPosition, wxSize(800, 600)) {
    textCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition,
                              wxDefaultSize, wxTE_MULTILINE);
    dirCtrl = new wxGenericDirCtrl(this, wxID_ANY, wxGetHomeDir(),
                                   wxDefaultPosition, wxSize(200, 600),
                                   wxDIRCTRL_DEFAULT_STYLE | wxSUNKEN_BORDER);
    dirCtrl->Bind(wxEVT_DIRCTRL_SELECTIONCHANGED, &MyFrame::OnDirItemSelect,
                  this);
    wxBoxSizer *h_sizer = new wxBoxSizer(wxHORIZONTAL);
    h_sizer->Add(dirCtrl, 0, wxEXPAND);
    h_sizer->Add(textCtrl, 1, wxEXPAND);
    SetSizer(h_sizer);
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open\tCtrl-O", "Open a file");
    menuFile->Append(wxID_SAVE, "&Save\tCtrl-S", "Save to a file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);
}

void MyFrame::OnOpen(wxCommandEvent &WXUNUSED(event)) {
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

void MyFrame::OnSave(wxCommandEvent &WXUNUSED(event)) {
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

void MyFrame::OnExit(wxCommandEvent &WXUNUSED(event)) {
    Close(true);
}

void MyFrame::OnDirItemSelect(wxCommandEvent &event) {
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
