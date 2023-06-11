//
// Created by Owen Carey on 6/4/23.
//

#include "../include/texteditorapp.h"

bool TextEditorApp::OnInit() {
    TextEditorFrame *frame = new TextEditorFrame();
    frame->Show();
    return true;
}
