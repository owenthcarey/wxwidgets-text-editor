#include <wx/wx.h>
#include <wx/file.h>
#include <wx/richtext/richtextctrl.h>

class MyApp : public wxApp {
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame {
public:
    MyFrame();
    wxRichTextCtrl *textCtrl;
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnFont(wxCommandEvent &event);
    void OnColor(wxCommandEvent &event);
    void OnBGColor(wxCommandEvent &event);
    void OnBold(wxCommandEvent &event);
    void OnItalic(wxCommandEvent &event);
    void OnUnderline(wxCommandEvent &event);
    void OnLeftAlign(wxCommandEvent &event);
    void OnRightAlign(wxCommandEvent &event);
    void OnCenterAlign(wxCommandEvent &event);
    void OnJustify(wxCommandEvent &event);
    void OnLineSpacing(wxCommandEvent &event);
    void OnParagraphSpacing(wxCommandEvent &event);
    void OnBullet(wxCommandEvent &event);
    void OnNumber(wxCommandEvent &event);
    // Define IDs for custom events
    enum {
        ID_Font = 101,
        ID_Color,
        ID_BGColor,
        ID_Bold,
        ID_Italic,
        ID_Underline,
        ID_LeftAlign,
        ID_RightAlign,
        ID_CenterAlign,
        ID_Justify,
        ID_LineSpacing,
        ID_ParagraphSpacing,
        ID_Bullet,
        ID_Number
    };

private:
wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
                EVT_MENU(wxID_SAVE, MyFrame::OnSave)
                EVT_MENU(wxID_EXIT, MyFrame::OnExit)
                EVT_MENU(ID_Font, MyFrame::OnFont)
                EVT_MENU(ID_Color, MyFrame::OnColor)
                EVT_MENU(ID_BGColor, MyFrame::OnBGColor)
                EVT_MENU(ID_Bold, MyFrame::OnBold)
                EVT_MENU(ID_Italic, MyFrame::OnItalic)
                EVT_MENU(ID_Underline, MyFrame::OnUnderline)
                EVT_MENU(ID_LeftAlign, MyFrame::OnLeftAlign)
                EVT_MENU(ID_RightAlign, MyFrame::OnRightAlign)
                EVT_MENU(ID_CenterAlign, MyFrame::OnCenterAlign)
                EVT_MENU(ID_Justify, MyFrame::OnJustify)
                EVT_MENU(ID_LineSpacing, MyFrame::OnLineSpacing)
                EVT_MENU(ID_ParagraphSpacing, MyFrame::OnParagraphSpacing)
                EVT_MENU(ID_Bullet, MyFrame::OnBullet)
                EVT_MENU(ID_Number, MyFrame::OnNumber)
wxEND_EVENT_TABLE()

// This defines the equivalent of main() for the current platform.
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame();
    frame->Show();
    return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "wxWidgets Text Editor",
                             wxDefaultPosition, wxSize(800, 600)) {
//    textCtrl = new wxTextCtrl(this, -1, "", wxDefaultPosition, wxDefaultSize,
//                              wxTE_MULTILINE | wxTE_RICH2);
    textCtrl = new wxRichTextCtrl(this, -1, "", wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE | wxTE_RICH2);
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

    wxMenu *menuFormat = new wxMenu;
    menuFormat->Append(ID_Font, "&Font");
    menuFormat->Append(ID_Color, "&Color");
    menuFormat->Append(ID_BGColor, "&Background Color");
    menuFormat->Append(ID_Bold, "&Bold");
    menuFormat->Append(ID_Italic, "&Italic");
    menuFormat->Append(ID_Underline, "&Underline");
    menuFormat->Append(ID_LeftAlign, "&Left Align");
    menuFormat->Append(ID_RightAlign, "&Right Align");
    menuFormat->Append(ID_CenterAlign, "&Center Align");
    menuFormat->Append(ID_Justify, "&Justify");
    menuFormat->Append(ID_LineSpacing, "&Line Spacing");
    menuFormat->Append(ID_ParagraphSpacing, "&Paragraph Spacing");
    menuFormat->Append(ID_Bullet, "&Bullet");
    menuFormat->Append(ID_Number, "&Number");
    menuBar->Append(menuFormat, "&Format");
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

void MyFrame::OnFont(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnColor(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnBGColor(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnBold(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnItalic(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnUnderline(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnLeftAlign(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnRightAlign(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnCenterAlign(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnJustify(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnLineSpacing(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnParagraphSpacing(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnBullet(wxCommandEvent &event) {
    // TODO
}

void MyFrame::OnNumber(wxCommandEvent &event) {
    // TODO
}
