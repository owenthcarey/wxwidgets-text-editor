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
    textCtrl = new wxStyledTextCtrl(this, wxID_ANY, wxDefaultPosition,
                                    wxDefaultSize,
                                    wxTE_MULTILINE);
    textCtrl->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                             wxFONTWEIGHT_NORMAL));
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_OPEN, "&Open\tCtrl-O", "Open a file");
    menuFile->Append(wxID_SAVE, "&Save\tCtrl-S", "Save to a file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);
    dirCtrl = new wxGenericDirCtrl(this, wxID_ANY, wxGetHomeDir(),
                                   wxDefaultPosition, wxSize(200, 600),
                                   wxDIRCTRL_DEFAULT_STYLE | wxSUNKEN_BORDER);
    dirCtrl->Bind(wxEVT_DIRCTRL_SELECTIONCHANGED, &MyFrame::OnDirItemSelect,
                  this);
    wxBoxSizer *h_sizer = new wxBoxSizer(wxHORIZONTAL);
    h_sizer->Add(dirCtrl, 0, wxEXPAND);
    h_sizer->Add(textCtrl, 1, wxEXPAND);
    consoleCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER);
    consoleCtrl->Bind(wxEVT_TEXT_ENTER, &MyFrame::OnConsoleEnter, this);
    wxBoxSizer *v_sizer = new wxBoxSizer(wxVERTICAL);
    v_sizer->Add(h_sizer, 1, wxEXPAND);
    v_sizer->Add(consoleCtrl, 0, wxEXPAND);
    SetSizer(v_sizer);
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
    wxString extension = GetFileExtension(path);
    if (extension == "cpp" || extension == "h") {
        SetupCppLexer();
    } else if (extension == "py") {
        SetupPythonLexer();
    }
}

void MyFrame::SetupCppLexer() {
    textCtrl->SetLexer(wxSTC_LEX_CPP);
    textCtrl->StyleSetFont(wxSTC_STYLE_DEFAULT,
                           wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                  wxFONTWEIGHT_NORMAL));
    textCtrl->StyleClearAll();
    textCtrl->StyleSetForeground(wxSTC_C_COMMENT, wxColour(150, 150, 150));
    textCtrl->StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(150, 150, 150));
    textCtrl->StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(150, 150, 150));
    textCtrl->StyleSetForeground(wxSTC_C_NUMBER, wxColour(0, 150, 0));
    textCtrl->StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 150));
    textCtrl->StyleSetForeground(wxSTC_C_STRING, wxColour(150, 0, 0));
    textCtrl->StyleSetForeground(wxSTC_C_CHARACTER, wxColour(150, 0, 0));
    textCtrl->StyleSetForeground(wxSTC_C_OPERATOR, wxColour(0, 0, 0));
}

void MyFrame::SetupPythonLexer() {
    textCtrl->SetLexer(wxSTC_LEX_PYTHON);
    textCtrl->StyleSetFont(wxSTC_STYLE_DEFAULT,
                           wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL,
                                  wxFONTWEIGHT_NORMAL));
    textCtrl->StyleClearAll();
    textCtrl->StyleSetForeground(wxSTC_P_COMMENTLINE, wxColour(150, 150, 150));
    textCtrl->StyleSetForeground(wxSTC_P_NUMBER, wxColour(0, 150, 0));
    textCtrl->StyleSetForeground(wxSTC_P_STRING, wxColour(150, 0, 0));
    textCtrl->StyleSetForeground(wxSTC_P_CHARACTER, wxColour(150, 0, 0));
    textCtrl->StyleSetForeground(wxSTC_P_WORD, wxColour(0, 0, 150));
    textCtrl->StyleSetForeground(wxSTC_P_TRIPLE, wxColour(150, 150, 0));
    textCtrl->StyleSetForeground(wxSTC_P_TRIPLEDOUBLE, wxColour(150, 150, 0));
    textCtrl->StyleSetForeground(wxSTC_P_CLASSNAME, wxColour(0, 0, 150));
    textCtrl->StyleSetForeground(wxSTC_P_DEFNAME, wxColour(0, 0, 150));
    textCtrl->StyleSetForeground(wxSTC_P_OPERATOR, wxColour(0, 0, 0));
    textCtrl->StyleSetForeground(wxSTC_P_IDENTIFIER, wxColour(0, 0, 0));
    textCtrl->StyleSetForeground(wxSTC_P_COMMENTBLOCK, wxColour(150, 150, 150));
    textCtrl->StyleSetForeground(wxSTC_P_STRINGEOL, wxColour(150, 0, 0));
}

wxString MyFrame::GetFileExtension(const wxString &fileName) {
    wxFileName fn(fileName);
    return fn.GetExt().Lower();
}

void MyFrame::RunCommand(const wxString &command) {
    // Create a new process that this application can interact with
    wxProcess *process = new wxProcess(this);
    // Redirect the output so we can capture it
    process->Redirect();
    // Execute the command
    long pid = wxExecute(command, wxEXEC_ASYNC, process);
    if (pid == 0) {
        // Command failed to start
        consoleCtrl->AppendText("Failed to run command: " + command + "\n");
        delete process;
    } else {
        // Read the output and append it to the consoleCtrl
        wxInputStream *stdoutStream = process->GetInputStream();
        wxTextInputStream *textStream = new wxTextInputStream(*stdoutStream);
        wxString line = textStream->ReadLine();
        while (!stdoutStream->Eof()) {
            consoleCtrl->AppendText(line + "\n");
            line = textStream->ReadLine();
        }
        // Clean up
        delete textStream;
        delete process;
    }
}

void MyFrame::OnConsoleEnter(wxCommandEvent& event) {
    wxString command = consoleCtrl->GetValue();
    consoleCtrl->Clear();
    RunCommand(command);
}
