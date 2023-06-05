//
// Created by Owen Carey on 6/4/23.
//

#include "../include/myframe.h"

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_MENU(wxID_OPEN, MyFrame::OnOpen)
                EVT_MENU(wxID_SAVE, MyFrame::OnSave)
                EVT_MENU(wxID_EXIT, MyFrame::OnExit)
//                EVT_TOOL(ID_Font, MyFrame::OnFont)
//                EVT_TOOL(ID_Color, MyFrame::OnColor)
//                EVT_TOOL(ID_BGColor, MyFrame::OnBGColor)
//                EVT_TOOL(ID_Bold, MyFrame::OnBold)
//                EVT_TOOL(ID_Italic, MyFrame::OnItalic)
//                EVT_TOOL(ID_Underline, MyFrame::OnUnderline)
//                EVT_TOOL(ID_LeftAlign, MyFrame::OnLeftAlign)
//                EVT_TOOL(ID_RightAlign, MyFrame::OnRightAlign)
//                EVT_TOOL(ID_CenterAlign, MyFrame::OnCenterAlign)
//                EVT_TOOL(ID_Justify, MyFrame::OnJustify)
//                EVT_CHOICE(ID_LineSpacing, MyFrame::OnLineSpacing)
//                EVT_TOOL(ID_Bullet, MyFrame::OnBullet)
wxEND_EVENT_TABLE()

// The constructor for MyFrame.
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

    // Create a 16x16 image filled with red pixels.
//    wxImage image(16, 16, true);
//    image.InitAlpha();
//    unsigned char *data = image.GetData();
//    unsigned char *alpha = image.GetAlpha();
//    for (int y = 0; y < 16; ++y) {
//        for (int x = 0; x < 16; ++x) {
//            int index = (y * 16 + x) * 3;
//            data[index] = 255;    // red channel
//            data[index + 1] = 0;  // green channel
//            data[index + 2] = 0;  // blue channel
//            alpha[y * 16 + x] = 255;  // fully opaque
//        }
//    }
//    wxBitmap bitmap(image);

    // Load the icon bitmaps from files
//    wxBitmap boldBitmap("../assets/bold@2x.png", wxBITMAP_TYPE_PNG);
//    wxBitmap italicBitmap("../assets/italic@2x.png", wxBITMAP_TYPE_PNG);
//    wxBitmap listBulletBitmap("../assets/list.bullet@2x.png",
//                              wxBITMAP_TYPE_PNG);
//    wxBitmap textAlignLeftBitmap("../assets/text.alignleft@2x.png",
//                                 wxBITMAP_TYPE_PNG);
//    wxBitmap textAlignRightBitmap("../assets/text.alignright@2x.png",
//                                  wxBITMAP_TYPE_PNG);
//    wxBitmap textAlignCenterBitmap("../assets/text.aligncenter@2x.png",
//                                   wxBITMAP_TYPE_PNG);
//    wxBitmap textJustifyBitmap("../assets/text.justify@2x.png",
//                               wxBITMAP_TYPE_PNG);
//    wxBitmap underlineBitmap("../assets/underline@2x.png", wxBITMAP_TYPE_PNG);

    // Create a toolbar and add items.
//    wxToolBar *toolbar = CreateToolBar();
//    toolbar->AddTool(ID_Font, wxT("Font"), bitmap, wxT("Change font"));
//    toolbar->AddTool(ID_Color, wxT("Color"), bitmap, wxT("Change color"));
//    toolbar->AddTool(ID_BGColor, wxT("Background Color"), bitmap,
//                     wxT("Change background color"));
//    toolbar->AddTool(ID_Bold, wxT("Bold"), boldBitmap, wxT("Bold text"));
//    toolbar->AddTool(ID_Italic, wxT("Italic"), italicBitmap,
//                     wxT("Italicize text"));
//    toolbar->AddTool(ID_Underline, wxT("Underline"), underlineBitmap,
//                     wxT("Underline text"));
//    toolbar->AddTool(ID_LeftAlign, wxT("Left Align"), textAlignLeftBitmap,
//                     wxT("Left align text"));
//    toolbar->AddTool(ID_RightAlign, wxT("Right Align"), textAlignRightBitmap,
//                     wxT("Right align text"));
//    toolbar->AddTool(ID_CenterAlign, wxT("Center Align"), textAlignCenterBitmap,
//                     wxT("Center align text"));
//    toolbar->AddTool(ID_Justify, wxT("Justify"), textJustifyBitmap,
//                     wxT("Justify text"));
//    wxArrayString lineSpacingChoices;
//    for (double i = 0.5; i <= 2.0; i += 0.1) {
//        lineSpacingChoices.Add(wxString::Format("%.1f", i));
//    }
//    wxChoice *lineSpacingDropdown = new wxChoice(toolbar, ID_LineSpacing,
//                                                 wxDefaultPosition,
//                                                 wxDefaultSize,
//                                                 lineSpacingChoices);
//    toolbar->AddControl(lineSpacingDropdown, wxT("Change line spacing"));
//    toolbar->AddTool(ID_Bullet, wxT("Bullet"), listBulletBitmap,
//                     wxT("Add bullet"));
//    toolbar->Realize();

    dirCtrl = new wxGenericDirCtrl(this, wxID_ANY, wxGetHomeDir(),
                                   wxDefaultPosition, wxSize(200, 600),
                                   wxDIRCTRL_DEFAULT_STYLE | wxSUNKEN_BORDER);
    dirCtrl->Bind(wxEVT_DIRCTRL_SELECTIONCHANGED, &MyFrame::OnDirItemSelect,
                  this);
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(dirCtrl, 0, wxEXPAND);
    sizer->Add(textCtrl, 1, wxEXPAND);
    SetSizer(sizer);
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

//void MyFrame::OnFont(wxCommandEvent &event) {
//    wxFontData data;
//    data.SetInitialFont(textCtrl->GetFont());
//    wxFontDialog dialog(this, data);
//    if (dialog.ShowModal() == wxID_OK) {
//        wxFont font = dialog.GetFontData().GetChosenFont();
//        wxTextAttr style = textCtrl->GetDefaultStyle();
//        style.SetFont(font);
//        textCtrl->SetDefaultStyle(style);
//    }
//}
//
//void MyFrame::OnColor(wxCommandEvent &event) {
//    wxColourDialog dialog(this);
//    if (dialog.ShowModal() == wxID_OK) {
//        wxColour color = dialog.GetColourData().GetColour();
//        wxTextAttr style = textCtrl->GetDefaultStyle();
//        style.SetTextColour(color);
//        textCtrl->SetDefaultStyle(style);
//    }
//}
//
//void MyFrame::OnBGColor(wxCommandEvent &event) {
//    wxColourDialog dialog(this);
//    if (dialog.ShowModal() == wxID_OK) {
//        wxColour color = dialog.GetColourData().GetColour();
//        wxTextAttr style = textCtrl->GetDefaultStyle();
//        style.SetBackgroundColour(color);
//        textCtrl->SetDefaultStyle(style);
//    }
//}
//
//void MyFrame::OnBold(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    if (style.GetFontWeight() != wxFONTWEIGHT_BOLD) {
//        style.SetFontWeight(wxFONTWEIGHT_BOLD);
//    } else {
//        style.SetFontWeight(wxFONTWEIGHT_NORMAL);
//    }
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnItalic(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    if (style.GetFontStyle() != wxFONTSTYLE_ITALIC) {
//        style.SetFontStyle(wxFONTSTYLE_ITALIC);
//    } else {
//        style.SetFontStyle(wxFONTSTYLE_NORMAL);
//    }
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnUnderline(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    if (!style.GetFontUnderlined()) {
//        style.SetFontUnderlined(true);
//    } else {
//        style.SetFontUnderlined(false);
//    }
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnLeftAlign(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    style.SetAlignment(wxTEXT_ALIGNMENT_LEFT);
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnRightAlign(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    style.SetAlignment(wxTEXT_ALIGNMENT_RIGHT);
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnCenterAlign(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    style.SetAlignment(wxTEXT_ALIGNMENT_CENTER);
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnJustify(wxCommandEvent &event) {
//    wxTextAttr style = textCtrl->GetDefaultStyle();
//    style.SetAlignment(wxTEXT_ALIGNMENT_JUSTIFIED);
//    textCtrl->SetDefaultStyle(style);
//}
//
//void MyFrame::OnLineSpacing(wxCommandEvent &event) {
//    wxChoice *lineSpacingDropdown = (wxChoice *) FindWindow(ID_LineSpacing);
//    wxString lineSpacingStr = lineSpacingDropdown->GetStringSelection();
//    double lineSpacing = wxAtof(lineSpacingStr);
//    wxLogMessage("Line spacing changed to: %f", lineSpacing);
//}
//
//void MyFrame::OnBullet(wxCommandEvent &event) {
//    wxLogMessage("OnBullet event triggered");
//}

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
