//
// Created by Owen Carey on 6/4/23.
//

#ifndef WXWIDGETS_TEXT_EDITOR_TEXTEDITORAPP_H
#define WXWIDGETS_TEXT_EDITOR_TEXTEDITORAPP_H

#include "texteditorframe.h"

#include <wx/wx.h>

class TextEditorApp : public wxApp {
public:
    bool OnInit() override;
};

#endif //WXWIDGETS_TEXT_EDITOR_TEXTEDITORAPP_H
