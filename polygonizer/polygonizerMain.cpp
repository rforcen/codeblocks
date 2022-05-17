/***************************************************************
 * Name:      polygonizerMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-05-17
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "polygonizerMain.h"
#include <wx/msgdlg.h>
#include "engine/Timer.h"



//(*InternalHeaders(polygonizerFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)


//(*IdInit(polygonizerFrame)
const long polygonizerFrame::ID_SPINCTRL1 = wxNewId();
const long polygonizerFrame::ID_SPINCTRLDOUBLE1 = wxNewId();
const long polygonizerFrame::ID_BUTTON1 = wxNewId();
const long polygonizerFrame::ID_LISTBOX1 = wxNewId();
const long polygonizerFrame::ID_GLCANVAS1 = wxNewId();
const long polygonizerFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(polygonizerFrame,wxFrame)
    //(*EventTable(polygonizerFrame)
    //*)
END_EVENT_TABLE()

polygonizerFrame::polygonizerFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(polygonizerFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, id, _("Polygonizer"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(690,442));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    scResol = new wxSpinCtrl(this, ID_SPINCTRL1, _T("80"), wxDefaultPosition, wxSize(126,34), 0, 20, 300, 80, _T("ID_SPINCTRL1"));
    scResol->SetValue(_T("80"));
    BoxSizer3->Add(scResol, 1, wxALL|wxEXPAND, 5);
    scBounds = new wxSpinCtrlDouble(this, ID_SPINCTRLDOUBLE1, _T("2"), wxDefaultPosition, wxSize(128,34), 0, 0.5, 10, 0, 0.01, _T("ID_SPINCTRLDOUBLE1"));
    scBounds->SetValue(_T("2"));
    BoxSizer3->Add(scBounds, 1, wxALL|wxEXPAND, 5);
    btnSaveCTM = new wxButton(this, ID_BUTTON1, _("save CTM"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(btnSaveCTM, 1, wxALL|wxEXPAND, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxFIXED_MINSIZE, 5);
    ListBox1 = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(250,340), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer2->Add(ListBox1, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	GLCanvas1 = new RenderPoly(this, ID_GLCANVAS1, GLCanvasAttributes_1, wxDefaultPosition, wxSize(319,404), 0, _T("ID_GLCANVAS1"));
    #else
    	GLCanvas1 = new RenderPoly(this, ID_GLCANVAS1, wxDefaultPosition, wxSize(319,404), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    #endif // wxCHECK_VERSION
    BoxSizer1->Add(GLCanvas1, 2, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(BoxSizer1);
    Layout();

    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&polygonizerFrame::OnscResolChange);
    Connect(ID_SPINCTRLDOUBLE1,wxEVT_SPINCTRLDOUBLE,(wxObjectEventFunction)&polygonizerFrame::OnSpinCtrlDouble1Change);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&polygonizerFrame::OnbtnSaveCTMClick);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&polygonizerFrame::OnListBox1Select);
    //*)

    for (auto s : Polygonizer::getNames()) // fill list w/names
        ListBox1->Append(s);

    ListBox1->SetSelection(3);
    setFunc();
}

polygonizerFrame::~polygonizerFrame()
{
    //(*Destroy(polygonizerFrame)
    //*)
}

void polygonizerFrame::setFunc()
{
    Timer lap;
    GLCanvas1->setFunc(ListBox1->GetSelection(), scBounds->GetValue(), scResol->GetValue());
    StatusBar1->SetStatusText(wxString::Format("%ld trigs, %ld vertexes, lap:%ldms", GLCanvas1->poly.trigs.size(), GLCanvas1->poly.vertexes.size(), lap.lap()));
}

void polygonizerFrame::OnListBox1Select(wxCommandEvent& event)
{
    setFunc();
}

void polygonizerFrame::OnscResolChange(wxSpinEvent& event)
{
    setFunc();
}

void polygonizerFrame::OnSpinCtrlDouble1Change(wxSpinDoubleEvent& event)
{
    setFunc();
}

void polygonizerFrame::OnbtnSaveCTMClick(wxCommandEvent& event)
{
    GLCanvas1->saveCTM();
    StatusBar1->SetStatusText("polygon saved in implsurf.ctm");
}
