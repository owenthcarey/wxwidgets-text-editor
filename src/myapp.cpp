//
// Created by Owen Carey on 6/4/23.
//

#include "../include/myapp.h"
#include <wx/image.h>

bool MyApp::OnInit() {
    wxImage::AddHandler(new wxPNGHandler);
    MyFrame *frame = new MyFrame();
    frame->Show();
    return true;
}
