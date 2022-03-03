/***************************************************************
 * Name:      shMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-03-01
 * Copyright:  ()
 * License:
 **************************************************************/

#include "shMain.h"
#include <wx/msgdlg.h>
#include "SphericalHarmonics.h"

//(*InternalHeaders(shFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f ) {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(shFrame)
const long shFrame::ID_CHOICE1 = wxNewId();
const long shFrame::ID_BUTTON1 = wxNewId();
const long shFrame::ID_SPINCTRL1 = wxNewId();
const long shFrame::ID_SPINCTRL2 = wxNewId();
const long shFrame::ID_LISTBOX1 = wxNewId();
const long shFrame::ID_GLCANVAS1 = wxNewId();
const long shFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(shFrame,wxFrame)
    //(*EventTable(shFrame)
    //*)
END_EVENT_TABLE()

shFrame::shFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(shFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, id, _("Spherical Harmonics"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    chFileType = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    chFileType->SetSelection( chFileType->Append(_("ctm")) );
    chFileType->Append(_("ply"));
    chFileType->SetToolTip(_("save file format"));
    BoxSizer3->Add(chFileType, 0, wxALL|wxEXPAND, 5);
    btSave = new wxButton(this, ID_BUTTON1, _("save"), wxDefaultPosition, wxSize(36,30), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(btSave, 0, wxALL|wxEXPAND, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    scColorMap = new wxSpinCtrl(this, ID_SPINCTRL1, _T("7"), wxDefaultPosition, wxSize(110,30), 0, 0, 27, 7, _T("ID_SPINCTRL1"));
    scColorMap->SetValue(_T("7"));
    scColorMap->SetToolTip(_("color map"));
    BoxSizer2->Add(scColorMap, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    scResol = new wxSpinCtrl(this, ID_SPINCTRL2, _T("128"), wxDefaultPosition, wxSize(110,30), 0, 64, 4096, 128, _T("ID_SPINCTRL2"));
    scResol->SetValue(_T("128"));
    scResol->SetToolTip(_("resolution"));
    BoxSizer2->Add(scResol, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lbCodes = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(107,387), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    lbCodes->SetToolTip(_("SH preset codes"));
    BoxSizer2->Add(lbCodes, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	GLCanvasSH = new wxGLCanvasSH(this, ID_GLCANVAS1, GLCanvasAttributes_1, wxDefaultPosition, wxSize(435,477), 0, _T("ID_GLCANVAS1"));
    #else
    	GLCanvasSH = new wxGLCanvasSH(this, ID_GLCANVAS1, wxDefaultPosition, wxSize(435,477), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    #endif // wxCHECK_VERSION
    BoxSizer1->Add(GLCanvasSH, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&shFrame::OnbtSaveClick);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&shFrame::OnscColorMapChange);
    Connect(ID_SPINCTRL2,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&shFrame::OnscResolChange);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&shFrame::OnlbCodesSelect);
    //*)

    SphericalHarmonics sh;
    for (int i=0; i<sh.getNCodes(); i++)
        lbCodes->Append(sh.getCode(i));
}

shFrame::~shFrame() {
    //(*Destroy(shFrame)
    //*)
}


void shFrame::OnlbCodesSelect(wxCommandEvent& event) {
    GLCanvasSH->setCode(event.GetSelection());
}

void shFrame::OnscColorMapChange(wxSpinEvent& event) {
    GLCanvasSH->setColorMap(event.GetValue());
}

void shFrame::OnscResolChange(wxSpinEvent& event) {
    GLCanvasSH->setResol(event.GetValue());
}

void shFrame::OnbtSaveClick(wxCommandEvent& event)
{
    wxString sels = chFileType->GetString(chFileType->GetSelection());

    if (sels=="ctm")  GLCanvasSH->saveCTM();
    else if (sels=="ply")  GLCanvasSH->savePLY();
    StatusBar1->SetStatusText("file saved:" + GLCanvasSH->getFileName(sels.ToStdString()));
}
