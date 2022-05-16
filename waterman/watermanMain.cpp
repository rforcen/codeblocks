/***************************************************************
 * Name:      watermanMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-05-16
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "watermanMain.h"
#include "engine/Timer.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(watermanFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)



//(*IdInit(watermanFrame)
const long watermanFrame::ID_SLIDER1 = wxNewId();
const long watermanFrame::ID_BUTTON1 = wxNewId();
const long watermanFrame::ID_GLCANVAS1 = wxNewId();
const long watermanFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(watermanFrame,wxFrame)
    //(*EventTable(watermanFrame)
    //*)
END_EVENT_TABLE()

watermanFrame::watermanFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(watermanFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;

    Create(parent, id, _("waterman"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Slider1 = new wxSlider(this, ID_SLIDER1, 0, 5, 50000, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER1"));
    BoxSizer2->Add(Slider1, 1, wxALL|wxEXPAND, 5);
    btnRecolor = new wxButton(this, ID_BUTTON1, _("recolor"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(btnRecolor, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	GLCanvas1 = new wxGLCanvasWaterman(this, ID_GLCANVAS1, GLCanvasAttributes_1, wxDefaultPosition, wxSize(413,371), 0, _T("ID_GLCANVAS1"));
    #else
    	GLCanvas1 = new wxGLCanvasWaterman(this, ID_GLCANVAS1, wxDefaultPosition, wxSize(413,371), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    #endif // wxCHECK_VERSION
    BoxSizer1->Add(GLCanvas1, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&watermanFrame::OnSlider1CmdScrollChanged);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&watermanFrame::OnButton1Click);
    //*)

    wxScrollEvent e;
    Slider1->SetValue(rand() % 500);
    OnSlider1CmdScrollChanged(e);

}

watermanFrame::~watermanFrame()
{
    //(*Destroy(watermanFrame)
    //*)
}



void watermanFrame::OnButton1Click(wxCommandEvent& event)
{
    GLCanvas1->recolor();
}

void watermanFrame::OnSlider1CmdScrollChanged(wxScrollEvent& event)
{ Timer lap;

    GLCanvas1->setWaterman(Slider1->GetValue());

    StatusBar1->SetStatusText(wxString::Format("radius:%d, %ld faces, %ld vertices, lap:%ldms", Slider1->GetValue(), GLCanvas1->faces.size(), GLCanvas1->vertices.size(), lap.lap()));
}
