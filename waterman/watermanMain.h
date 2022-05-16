/***************************************************************
 * Name:      watermanMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-05-16
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef WATERMANMAIN_H
#define WATERMANMAIN_H

#include "wxGLCanvasWaterman.h"

//(*Headers(watermanFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
//*)



class watermanFrame: public wxFrame
{
public:

    watermanFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~watermanFrame();

private:

    //(*Handlers(watermanFrame)
    void OnButton1Click(wxCommandEvent& event);
    void OnSlider1CmdScrollChanged(wxScrollEvent& event);
    //*)

    //(*Identifiers(watermanFrame)
    static const long ID_SLIDER1;
    static const long ID_BUTTON1;
    static const long ID_GLCANVAS1;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(watermanFrame)
    wxButton* btnRecolor;
    wxGLCanvasWaterman* GLCanvas1;
    wxSlider* Slider1;
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // WATERMANMAIN_H
