#include <wx/wx.h>
#include <wx/file.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/colourdata.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/choice.h>

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
                EVT_TOOL(ID_Font, MyFrame::OnFont)
                EVT_TOOL(ID_Color, MyFrame::OnColor)
                EVT_TOOL(ID_BGColor, MyFrame::OnBGColor)
                EVT_TOOL(ID_Bold, MyFrame::OnBold)
                EVT_TOOL(ID_Italic, MyFrame::OnItalic)
                EVT_TOOL(ID_Underline, MyFrame::OnUnderline)
                EVT_TOOL(ID_LeftAlign, MyFrame::OnLeftAlign)
                EVT_TOOL(ID_RightAlign, MyFrame::OnRightAlign)
                EVT_TOOL(ID_CenterAlign, MyFrame::OnCenterAlign)
                EVT_TOOL(ID_Justify, MyFrame::OnJustify)
                EVT_CHOICE(ID_LineSpacing, MyFrame::OnLineSpacing)
                EVT_TOOL(ID_ParagraphSpacing, MyFrame::OnParagraphSpacing)
                EVT_TOOL(ID_Bullet, MyFrame::OnBullet)
                EVT_TOOL(ID_Number, MyFrame::OnNumber)
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

    // Create a 16x16 image filled with red pixels.
    wxImage image(16, 16, true);
    image.InitAlpha();
    unsigned char *data = image.GetData();
    unsigned char *alpha = image.GetAlpha();
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 16; ++x) {
            int index = (y * 16 + x) * 3;
            data[index] = 255;    // red channel
            data[index + 1] = 0;  // green channel
            data[index + 2] = 0;  // blue channel
            alpha[y * 16 + x] = 255;  // fully opaque
        }
    }
    wxBitmap bitmap(image);

    // Create a toolbar and add items.
    wxToolBar *toolbar = CreateToolBar();
    toolbar->AddTool(ID_Font, wxT("Font"), bitmap, wxT("Change font"));
    toolbar->AddTool(ID_Color, wxT("Color"), bitmap, wxT("Change color"));
    toolbar->AddTool(ID_BGColor, wxT("Background Color"), bitmap, wxT("Change background color"));
    toolbar->AddTool(ID_Bold, wxT("Bold"), bitmap, wxT("Bold text"));
    toolbar->AddTool(ID_Italic, wxT("Italic"), bitmap, wxT("Italicize text"));
    toolbar->AddTool(ID_Underline, wxT("Underline"), bitmap, wxT("Underline text"));
    toolbar->AddTool(ID_LeftAlign, wxT("Left Align"), bitmap, wxT("Left align text"));
    toolbar->AddTool(ID_RightAlign, wxT("Right Align"), bitmap, wxT("Right align text"));
    toolbar->AddTool(ID_CenterAlign, wxT("Center Align"), bitmap, wxT("Center align text"));
    toolbar->AddTool(ID_Justify, wxT("Justify"), bitmap, wxT("Justify text"));
//    toolbar->AddTool(ID_LineSpacing, wxT("Line Spacing"), bitmap, wxT("Change line spacing"));
    wxArrayString lineSpacingChoices;
    for (double i = 0.5; i <= 2.0; i += 0.1) {
        lineSpacingChoices.Add(wxString::Format("%.1f", i));
    }
    wxChoice* lineSpacingDropdown = new wxChoice(toolbar, ID_LineSpacing, wxDefaultPosition, wxDefaultSize, lineSpacingChoices);
    toolbar->AddControl(lineSpacingDropdown, wxT("Change line spacing"));
    toolbar->AddTool(ID_ParagraphSpacing, wxT("Paragraph Spacing"), bitmap, wxT("Change paragraph spacing"));
    toolbar->AddTool(ID_Bullet, wxT("Bullet"), bitmap, wxT("Add bullet"));
    toolbar->AddTool(ID_Number, wxT("Number"), bitmap, wxT("Add number"));
    toolbar->Realize();
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
    wxFontData data;
    data.SetInitialFont(textCtrl->GetFont());
    wxFontDialog dialog(this, data);
    if (dialog.ShowModal() == wxID_OK) {
        wxFontData retData = dialog.GetFontData();
        wxFont font = retData.GetChosenFont();
        wxTextAttr attr = textCtrl->GetDefaultStyle();
        attr.SetFont(font);
        textCtrl->SetDefaultStyle(attr);
    }
}

void MyFrame::OnColor(wxCommandEvent &event) {
    wxColourDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        wxColourData data = dialog.GetColourData();
        wxColour color = data.GetColour();
        wxTextAttr attr = textCtrl->GetDefaultStyle();
        attr.SetTextColour(color);
        textCtrl->SetDefaultStyle(attr);
    }
}

void MyFrame::OnBGColor(wxCommandEvent &event) {
    wxColourDialog dialog(this);
    if (dialog.ShowModal() == wxID_OK) {
        wxColourData data = dialog.GetColourData();
        wxColour color = data.GetColour();
        wxTextAttr attr = textCtrl->GetDefaultStyle();
        attr.SetBackgroundColour(color);
        textCtrl->SetDefaultStyle(attr);
    }
}

void MyFrame::OnBold(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    if(style.GetFontWeight() != wxFONTWEIGHT_BOLD) {
        style.SetFontWeight(wxFONTWEIGHT_BOLD);
    } else {
        style.SetFontWeight(wxFONTWEIGHT_NORMAL);
    }
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnItalic(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    if(style.GetFontStyle() != wxFONTSTYLE_ITALIC) {
        style.SetFontStyle(wxFONTSTYLE_ITALIC);
    } else {
        style.SetFontStyle(wxFONTSTYLE_NORMAL);
    }
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnUnderline(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    if(!style.GetFontUnderlined()) {
        style.SetFontUnderlined(true);
    } else {
        style.SetFontUnderlined(false);
    }
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnLeftAlign(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    style.SetAlignment(wxTEXT_ALIGNMENT_LEFT);
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnRightAlign(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    style.SetAlignment(wxTEXT_ALIGNMENT_RIGHT);
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnCenterAlign(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    style.SetAlignment(wxTEXT_ALIGNMENT_CENTER);
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnJustify(wxCommandEvent &event) {
    wxTextAttr style = textCtrl->GetDefaultStyle();
    style.SetAlignment(wxTEXT_ALIGNMENT_JUSTIFIED);
    textCtrl->SetDefaultStyle(style);
}

void MyFrame::OnLineSpacing(wxCommandEvent &event) {
    wxChoice* lineSpacingDropdown = (wxChoice*)FindWindow(ID_LineSpacing);
    wxString lineSpacingStr = lineSpacingDropdown->GetStringSelection();
    double lineSpacing = wxAtof(lineSpacingStr);
    wxLogMessage("Line spacing changed to: %f", lineSpacing);
}

void MyFrame::OnParagraphSpacing(wxCommandEvent &event) {
    wxLogMessage("OnParagraphSpacing event triggered");
}

void MyFrame::OnBullet(wxCommandEvent &event) {
    wxLogMessage("OnBullet event triggered");
}

void MyFrame::OnNumber(wxCommandEvent &event) {
    wxLogMessage("OnNumber event triggered");
}
