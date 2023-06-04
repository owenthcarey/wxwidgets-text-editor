#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    wxTextCtrl *textCtrl;
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "wxWidgets Text Editor")
{
    textCtrl = new wxTextCtrl(this, -1, "", wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE | wxTE_RICH2);
    textCtrl->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
}
