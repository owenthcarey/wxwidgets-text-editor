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
//#include <wx/filepicker.h>

// The frame that contains the main part of the application.
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
    void OnBullet(wxCommandEvent &event);
    wxGenericDirCtrl *dirCtrl;
    void OnDirItemSelect(wxCommandEvent &event);
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
        ID_Bullet
    };

private:
wxDECLARE_EVENT_TABLE();
};

#endif //WXWIDGETS_TEXT_EDITOR_MYFRAME_H
