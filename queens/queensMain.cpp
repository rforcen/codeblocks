/***************************************************************
 * Name:      queensMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-06-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "queensMain.h"
#include <wx/clipbrd.h>

//(*IdInit(queensFrame)
const long queensFrame::ID_BUTTON1 = wxNewId();
const long queensFrame::ID_SPINCTRL1 = wxNewId();
const long queensFrame::ID_LISTBOX1 = wxNewId();
const long queensFrame::ID_GLCANVAS1 = wxNewId();
const long queensFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(queensFrame,wxFrame)
    //(*EventTable(queensFrame)
    //*)
END_EVENT_TABLE()

queensFrame::queensFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(queensFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, id, _("queens"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(458,465));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    btFirst = new wxButton(this, ID_BUTTON1, _("solve"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(btFirst, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    nQueens = new wxSpinCtrl(this, ID_SPINCTRL1, _T("12"), wxDefaultPosition, wxSize(131,33), 0, 5, 100, 12, _T("ID_SPINCTRL1"));
    nQueens->SetValue(_T("12"));
    BoxSizer2->Add(nQueens, 0, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    lbSolutions = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(126,422), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer3->Add(lbSolutions, 0, wxALL|wxEXPAND, 5);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	board = new wxGLGraph(this, ID_GLCANVAS1, GLCanvasAttributes_1, wxDefaultPosition, wxSize(459,422), 0, _T("ID_GLCANVAS1"));
    #else
    	board = new wxGLGraph(this, ID_GLCANVAS1, wxDefaultPosition, wxSize(459,422), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    #endif // wxCHECK_VERSION
    BoxSizer3->Add(board, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(BoxSizer1);
    Layout();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&queensFrame::OnbtFirstClick);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&queensFrame::OnnQueensChange);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&queensFrame::OnlbSolutionsSelect);
    //*)

    timer.Bind(wxEVT_TIMER, &queensFrame::OnTimer, this);

    q=Queens(nQueens->GetValue());
    board->SetQueens(&q);

    wxPersistenceManager::Get().RegisterAndRestore(this);
}

queensFrame::~queensFrame() {
    //(*Destroy(queensFrame)
    //*)
    timer.Stop();
    q.stop();

     wxPersistenceManager::Get().Save(this);
}

void queensFrame::OnnQueensChange(wxSpinEvent& event) {
    q=Queens(nQueens->GetValue());
    board->SetQueens(&q);
    lbSolutions->Clear();
}

void queensFrame::OnbtFirstClick(wxCommandEvent& event) {
    lbSolutions->Clear();
    timer.Stop();

    if (!q.isRunning()) {

        thread([&]() {
            t0.start();

            q.findFirst();

            CallAfter([this]() {
                auto lap=t0.lap();

                timer.Stop();

                auto ce = q.countEvals.str();


                q.board=q.solutions[0];
                board->SetQueens(&q);

                transformations();
                StatusBar1->SetStatusText(wxString::Format("lap:%ldms, evals:%s, solutions found:%ld", lap, ce.c_str(), q.solutions.size()));

            });
        }).detach();

        timer.Start(100);

    } else {
        q.stop();
    }
}

void queensFrame::OnTimer(wxTimerEvent&) {
    StatusBar1->SetStatusText(wxString::Format("seaching first solution, lap:%.1f\"",t0.lap()/1000.));
}

void queensFrame::transformations() {
    q.transformations();

    lbSolutions->Clear();
    string str;
    for (auto &s:q.solutions) {
        auto ss=s.toString();
        lbSolutions->Append(ss);
        str += ss + "\n";
    }

    // copy solutions to clipboard
    if (wxTheClipboard->Open()) {
        wxTheClipboard->SetData( new wxTextDataObject(str) );
        wxTheClipboard->Close();
    }
}

void queensFrame::OnlbSolutionsSelect(wxCommandEvent& event) {
    int ns=event.GetInt();
    q.loadSolution(ns);
    board->SetQueens(&q);
}
