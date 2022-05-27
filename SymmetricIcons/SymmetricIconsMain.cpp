/***************************************************************
 * Name:      SymmetricIconsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"

#include <wx/msgdlg.h>
#include <wx/evtloop.h>
#include <stdio.h>
#include <thread>

#include "SymmetricIconsMain.h"

using std::thread;

//(*IdInit(SymmetricIconsFrame)
const long SymmetricIconsFrame::ID_SPINCTRL1 = wxNewId();
const long SymmetricIconsFrame::ID_BUTTON1 = wxNewId();
const long SymmetricIconsFrame::ID_BUTTON2 = wxNewId();
const long SymmetricIconsFrame::ID_GRID1 = wxNewId();
const long SymmetricIconsFrame::ID_GLCANVAS1 = wxNewId();
const long SymmetricIconsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SymmetricIconsFrame,wxFrame)
    //(*EventTable(SymmetricIconsFrame)
    EVT_GRID_RANGE_SELECT(SymmetricIconsFrame::selectGrid)
    //*)
END_EVENT_TABLE()

SymmetricIconsFrame::SymmetricIconsFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(SymmetricIconsFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;

    Create(parent, wxID_ANY, _("Symmetric Icon"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    nIters = new wxSpinCtrl(this, ID_SPINCTRL1, _T("2000"), wxDefaultPosition, wxSize(104,33), 0, 1, 10000, 2000, _T("ID_SPINCTRL1"));
    nIters->SetValue(_T("2000"));
    nIters->SetToolTip(_("# iters in 1e5"));
    nIters->SetHelpText(_("# iters in 1e5"));
    BoxSizer2->Add(nIters, 0, wxALL|wxEXPAND, 2);
    saveImage = new wxButton(this, ID_BUTTON1, _("save"), wxDefaultPosition, wxSize(79,33), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(saveImage, 0, wxALL|wxEXPAND, 2);
    btnStop = new wxButton(this, ID_BUTTON2, _("stop"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(btnStop, 0, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 3);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    gridPreset = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxSize(641,287), 0, _T("ID_GRID1"));
    gridPreset->CreateGrid(0,7);
    wxFont gridPresetFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    gridPreset->SetFont(gridPresetFont);
    gridPreset->EnableEditing(true);
    gridPreset->EnableGridLines(true);
    wxFont GridLabelFont_1(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    gridPreset->SetLabelFont(GridLabelFont_1);
    gridPreset->SetColLabelValue(0, _("lambda"));
    gridPreset->SetColLabelValue(1, _("alpha"));
    gridPreset->SetColLabelValue(2, _("beta"));
    gridPreset->SetColLabelValue(3, _("gamma"));
    gridPreset->SetColLabelValue(4, _("omega"));
    gridPreset->SetColLabelValue(5, _("symbol"));
    gridPreset->SetColLabelValue(6, _("scale"));
    gridPreset->SetDefaultCellFont( gridPreset->GetFont() );
    gridPreset->SetDefaultCellTextColour( gridPreset->GetForegroundColour() );
    BoxSizer3->Add(gridPreset, 0, wxALL|wxEXPAND, 2);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	siGLCanvas = new wxGLCanvasSymmIcon(this, ID_GLCANVAS1, GLCanvasAttributes_1, wxDefaultPosition, wxSize(354,336), 0, _T("ID_GLCANVAS1"));
    #else
    	siGLCanvas = new wxGLCanvasSymmIcon(this, ID_GLCANVAS1, wxDefaultPosition, wxSize(354,336), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_1);
    #endif // wxCHECK_VERSION
    BoxSizer4->Add(siGLCanvas, 1, wxALL|wxEXPAND, 2);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 2);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&SymmetricIconsFrame::OnnItersChange);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SymmetricIconsFrame::OnsaveImageClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SymmetricIconsFrame::OnbtnStopClick);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SymmetricIconsFrame::OnClose);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&SymmetricIconsFrame::OnPaint);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&SymmetricIconsFrame::OnResize);
    //*)

    fillPreset();

    srand(time(0));
}

SymmetricIconsFrame::~SymmetricIconsFrame() {
    //(*Destroy(SymmetricIconsFrame)
    //*)
}

void SymmetricIconsFrame::selectGrid(wxGridRangeSelectEvent&event) {
    StopWorking();

    RePaintAsync();
    event.Skip();
}

void SymmetricIconsFrame::fillPreset() {
    double lambda, alpha, beta, gamma, omega;
    int sym;
    double scale;

    for (auto row=0; row<symmIcon.getnPreset(); row++) {
        symmIcon.getPreset(row, lambda, alpha, beta, gamma, omega, sym, scale);
        auto s=wxString::Format("%.2f,%.2f,%.2f,%.2f,%.2f,%d,%.2f", lambda, alpha, beta, gamma, omega, sym, scale);

        gridPreset->AppendRows(1);
        double preset[7]= {lambda, alpha, beta, gamma, omega, (double)sym, scale};
        for (auto i=0; i<7; i++)
            gridPreset->SetCellValue(row, i, wxString::Format("%.3f", preset[i]));
    }
}



void SymmetricIconsFrame::RePaintAsync(bool refresh) {
    const long itersDiv=100000;

    if (working) return;

    auto sr=gridPreset->GetSelectedRows();
    if (refresh && sr.size()>0) {
        wxSize sz = siGLCanvas->getScaledSize();
        symmIcon.setSize(sz.x, sz.y);

        int selIcon=sr[0];
        symmIcon.setPreset(selIcon);

        long iters=nIters->GetValue()*itersDiv;
        working=true;

        thread([this, iters, selIcon, sz]() {
            Timer t0;
            for (long i=0; i<iters && working; i++) { // generate
                if (symmIcon.generateSymmIcon(itersDiv)) { // generate enough iters before updating
                    auto lap=t0.lap();
                    CallAfter([this, i, sz, lap]() { // update icon after thread completition
                        StatusBar1->SetStatusText(wxString::Format("iters:%ld, size(%d, %d), lap:%ldms", (i+1)/itersDiv, sz.x, sz.y, lap));
                        siGLCanvas->setBitmap(symmIcon.screen);
                    });
                    wxYieldIfNeeded();
                }
            }
            working=!working; // ack
            needsRefresh=false;

            if (!working) {
                auto lap=t0.lap();
                CallAfter([this, iters, sz, lap]() { // update icon after thread completition
                    StatusBar1->SetStatusText(wxString::Format("iters:%ld, size(%d, %d), lap:%ldms", iters/100000, sz.x, sz.y, lap));
                });
            }
        }).detach();

        StatusBar1->SetStatusText(wxString::Format("generating icon %d, please wait", selIcon+1));
    }
}

void SymmetricIconsFrame::OnResize(wxSizeEvent& event) {
    StopWorking();
    needsRefresh=true;
    event.Skip();
}

void SymmetricIconsFrame::OnnItersChange(wxSpinEvent& event) {
    RePaintAsync();
    event.Skip();
}

void SymmetricIconsFrame::OnsaveImageClick(wxCommandEvent& event) {
    StopWorking();

    wxSize sz = siGLCanvas->getScaledSize();
    wxBitmap bmp=genImage(sz.x, sz.y, symmIcon.screen);
    bmp.SaveFile("symmIcon.png", wxBITMAP_TYPE_PNG);


    StatusBar1->SetStatusText("saved on file symmIcon.png");
}

void SymmetricIconsFrame::OnPaint(wxPaintEvent& event) {
    RePaintAsync(needsRefresh);
    event.Skip();
}

void SymmetricIconsFrame::StopWorking() {
    if (working) {
        working=false; // stop
        while (!working); // wait ack
        wxYieldIfNeeded();
        working=false;
    }
}

void SymmetricIconsFrame::OnClose(wxCloseEvent& event) {
    StopWorking();
    event.Skip();
}

void SymmetricIconsFrame::OnbtnStopClick(wxCommandEvent& event) {
    StopWorking();
}
