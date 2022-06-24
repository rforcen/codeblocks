/***************************************************************
 * Name:      vbsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-06-08
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>

#include "vbsMain.h"


//(*IdInit(vbsFrame)
const long vbsFrame::ID_DIRPICKERCTRL1 = wxNewId();
const long vbsFrame::ID_TOGGLEBUTTON1 = wxNewId();
const long vbsFrame::ID_CHECKBOX1 = wxNewId();
const long vbsFrame::ID_LISTBOX1 = wxNewId();
const long vbsFrame::ID_STATICTEXT6 = wxNewId();
const long vbsFrame::ID_LISTBOX2 = wxNewId();
const long vbsFrame::ID_STATICTEXT4 = wxNewId();
const long vbsFrame::ID_CHOICE2 = wxNewId();
const long vbsFrame::ID_CHOICE1 = wxNewId();
const long vbsFrame::ID_GLCANVAS3 = wxNewId();
const long vbsFrame::ID_STATICTEXT3 = wxNewId();
const long vbsFrame::ID_GRID1 = wxNewId();
const long vbsFrame::ID_GLCANVAS4 = wxNewId();
const long vbsFrame::ID_STATICTEXT2 = wxNewId();
const long vbsFrame::ID_FFT_GRAPH0 = wxNewId();
const long vbsFrame::ID_FFT_GRAPH1 = wxNewId();
const long vbsFrame::ID_FFT_GRAPH2 = wxNewId();
const long vbsFrame::ID_STATICTEXT5 = wxNewId();
const long vbsFrame::ID_BUTTON1 = wxNewId();
const long vbsFrame::ID_SLIDER1 = wxNewId();
const long vbsFrame::ID_SLIDER2 = wxNewId();
const long vbsFrame::ID_GRID2 = wxNewId();
const long vbsFrame::ID_STATICTEXT1 = wxNewId();
const long vbsFrame::ID_GLCANVAS1 = wxNewId();
const long vbsFrame::ID_GLCANVAS2 = wxNewId();
const long vbsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(vbsFrame,wxFrame)
    //(*EventTable(vbsFrame)
    //*)
END_EVENT_TABLE()

vbsFrame::vbsFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(vbsFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer9;

    Create(parent, wxID_ANY, _("VBS"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(419,430));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    dpWavFiles = new wxDirPickerCtrl(this, ID_DIRPICKERCTRL1, wxEmptyString, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRP_DIR_MUST_EXIST, wxDefaultValidator, _T("ID_DIRPICKERCTRL1"));
    dpWavFiles->SetBackgroundColour(wxColour(192,220,192));
    BoxSizer2->Add(dpWavFiles, 0, wxALL|wxEXPAND, 2);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    tbPlay = new wxToggleButton(this, ID_TOGGLEBUTTON1, _("play"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
    BoxSizer14->Add(tbPlay, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer14, 0, wxALL|wxEXPAND, 5);
    cbAutoPlay = new wxCheckBox(this, ID_CHECKBOX1, _("autoplay"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    cbAutoPlay->SetValue(false);
    BoxSizer2->Add(cbAutoPlay, 0, wxALL|wxEXPAND, 5);
    lbWavFiles = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(180,291), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer2->Add(lbWavFiles, 2, wxALL|wxEXPAND, 2);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("signal params"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_RAISED, _T("ID_STATICTEXT6"));
    StaticText5->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText5->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    BoxSizer2->Add(StaticText5, 0, wxALL|wxEXPAND, 0);
    lbSignal = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
    lbSignal->SetBackgroundColour(wxColour(192,220,192));
    BoxSizer2->Add(lbSignal, 1, wxALL|wxEXPAND, 0);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 2);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("radial spectrum"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT4"));
    StaticText4->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    BoxSizer7->Add(StaticText4, 0, wxALL|wxEXPAND, 2);
    BoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    chGraphType = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    chGraphType->Append(_("radial"));
    chGraphType->Append(_("spiral"));
    chGraphType->SetSelection( chGraphType->Append(_("concentric")) );
    BoxSizer15->Add(chGraphType, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    fftValues = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    fftValues->Append(_("256"));
    fftValues->Append(_("512"));
    fftValues->Append(_("1024"));
    fftValues->Append(_("2048"));
    fftValues->Append(_("4096"));
    fftValues->SetSelection( fftValues->Append(_("8192")) );
    fftValues->Append(_("16384"));
    fftValues->Append(_("32768"));
    fftValues->Append(_("65536"));
    BoxSizer15->Add(fftValues, 1, wxALL|wxEXPAND, 5);
    BoxSizer7->Add(BoxSizer15, 0, wxALL|wxEXPAND, 2);
    int GLCanvasAttributes_1[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	graphGL = new wxGLGraph(this, ID_GLCANVAS3, GLCanvasAttributes_1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS3"));
    #else
    	graphGL = new wxGLGraph(this, ID_GLCANVAS3, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS3"), GLCanvasAttributes_1);
    #endif // wxCHECK_VERSION
    BoxSizer7->Add(graphGL, 1, wxALL|wxEXPAND, 0);
    BoxSizer4->Add(BoxSizer7, 1, wxALL|wxEXPAND, 0);
    BoxSizer6 = new wxBoxSizer(wxVERTICAL);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("music matrix"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT3"));
    StaticText3->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText3->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    BoxSizer6->Add(StaticText3, 0, wxALL|wxEXPAND, 0);
    musicMatrix = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
    musicMatrix->CreateGrid(6,13);
    musicMatrix->SetBackgroundColour(wxColour(192,220,192));
    wxFont musicMatrixFont(11,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Monospace"),wxFONTENCODING_DEFAULT);
    musicMatrix->SetFont(musicMatrixFont);
    musicMatrix->EnableEditing(false);
    musicMatrix->EnableGridLines(true);
    musicMatrix->SetRowLabelSize(40);
    musicMatrix->SetDefaultColSize(35, true);
    musicMatrix->SetLabelTextColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    musicMatrix->SetColLabelValue(0, _("A"));
    musicMatrix->SetColLabelValue(1, _("A#"));
    musicMatrix->SetColLabelValue(2, _("B"));
    musicMatrix->SetColLabelValue(3, _("C"));
    musicMatrix->SetColLabelValue(4, _("C#"));
    musicMatrix->SetColLabelValue(5, _("D"));
    musicMatrix->SetColLabelValue(6, _("D#"));
    musicMatrix->SetColLabelValue(7, _("E"));
    musicMatrix->SetColLabelValue(8, _("F"));
    musicMatrix->SetColLabelValue(9, _("F#"));
    musicMatrix->SetColLabelValue(10, _("G"));
    musicMatrix->SetColLabelValue(11, _("G#"));
    musicMatrix->SetColLabelValue(12, _("Sum"));
    musicMatrix->SetRowLabelValue(0, _("-2"));
    musicMatrix->SetRowLabelValue(1, _("-1"));
    musicMatrix->SetRowLabelValue(2, _(" 0"));
    musicMatrix->SetRowLabelValue(3, _("+1"));
    musicMatrix->SetRowLabelValue(4, _("+2"));
    musicMatrix->SetRowLabelValue(5, _("sum"));
    musicMatrix->SetDefaultCellFont( musicMatrix->GetFont() );
    musicMatrix->SetDefaultCellTextColour( musicMatrix->GetForegroundColour() );
    BoxSizer6->Add(musicMatrix, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    int GLCanvasAttributes_2[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	mmGraph = new wxGLGraph(this, ID_GLCANVAS4, GLCanvasAttributes_2, wxDefaultPosition, wxSize(612,73), 0, _T("ID_GLCANVAS4"));
    #else
    	mmGraph = new wxGLGraph(this, ID_GLCANVAS4, wxDefaultPosition, wxSize(612,73), 0, _T("ID_GLCANVAS4"), GLCanvasAttributes_2);
    #endif // wxCHECK_VERSION
    BoxSizer6->Add(mmGraph, 0, wxALL|wxEXPAND, 0);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("spectrum"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
    StaticText2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    BoxSizer6->Add(StaticText2, 0, wxALL|wxEXPAND, 0);
    BoxSizer8 = new wxBoxSizer(wxVERTICAL);
    BoxSizer9 = new wxBoxSizer(wxVERTICAL);
    int GLCanvasAttributes_3[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	fftGraph0 = new wxGLGraph(this, ID_FFT_GRAPH0, GLCanvasAttributes_3, wxDefaultPosition, wxDefaultSize, 0, _T("ID_FFT_GRAPH0"));
    #else
    	fftGraph0 = new wxGLGraph(this, ID_FFT_GRAPH0, wxDefaultPosition, wxDefaultSize, 0, _T("ID_FFT_GRAPH0"), GLCanvasAttributes_3);
    #endif // wxCHECK_VERSION
    BoxSizer9->Add(fftGraph0, 1, wxALL|wxEXPAND, 0);
    int GLCanvasAttributes_4[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	fftGraph1 = new wxGLGraph(this, ID_FFT_GRAPH1, GLCanvasAttributes_4, wxDefaultPosition, wxDefaultSize, 0, _T("ID_FFT_GRAPH1"));
    #else
    	fftGraph1 = new wxGLGraph(this, ID_FFT_GRAPH1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_FFT_GRAPH1"), GLCanvasAttributes_4);
    #endif // wxCHECK_VERSION
    BoxSizer9->Add(fftGraph1, 1, wxALL|wxEXPAND, 0);
    int GLCanvasAttributes_5[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	fftGraph2 = new wxGLGraph(this, ID_FFT_GRAPH2, GLCanvasAttributes_5, wxDefaultPosition, wxDefaultSize, 0, _T("ID_FFT_GRAPH2"));
    #else
    	fftGraph2 = new wxGLGraph(this, ID_FFT_GRAPH2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_FFT_GRAPH2"), GLCanvasAttributes_5);
    #endif // wxCHECK_VERSION
    BoxSizer9->Add(fftGraph2, 1, wxALL|wxEXPAND, 0);
    BoxSizer8->Add(BoxSizer9, 1, wxALL|wxEXPAND, 0);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer12 = new wxBoxSizer(wxVERTICAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT5, _("formants"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_RAISED, _T("ID_STATICTEXT5"));
    StaticText1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    BoxSizer12->Add(StaticText1, 0, wxALL|wxEXPAND, 0);
    btnPlayFormants = new wxButton(this, ID_BUTTON1, _("play"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer12->Add(btnPlayFormants, 0, wxALL|wxEXPAND, 0);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    slVolume = new wxSlider(this, ID_SLIDER1, 30, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER1"));
    wxFont slVolumeFont(9,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    slVolume->SetFont(slVolumeFont);
    slVolume->SetToolTip(_("formants vol."));
    BoxSizer13->Add(slVolume, 0, wxALL|wxEXPAND, 0);
    slBinSepp = new wxSlider(this, ID_SLIDER2, 15, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_VERTICAL|wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER2"));
    wxFont slBinSeppFont(9,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    slBinSepp->SetFont(slBinSeppFont);
    slBinSepp->SetToolTip(_("binaural sepparation"));
    BoxSizer13->Add(slBinSepp, 0, wxALL|wxEXPAND, 0);
    gridFormants = new wxGrid(this, ID_GRID2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID2"));
    gridFormants->CreateGrid(5,2);
    wxFont gridFormantsFont(8,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    gridFormants->SetFont(gridFormantsFont);
    gridFormants->EnableEditing(false);
    gridFormants->EnableGridLines(true);
    gridFormants->SetColLabelValue(0, _("db"));
    gridFormants->SetColLabelValue(1, _("hz"));
    gridFormants->SetDefaultCellFont( gridFormants->GetFont() );
    gridFormants->SetDefaultCellTextColour( gridFormants->GetForegroundColour() );
    BoxSizer13->Add(gridFormants, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer12->Add(BoxSizer13, 0, wxALL|wxEXPAND, 0);
    BoxSizer10->Add(BoxSizer12, 1, wxALL|wxEXPAND, 2);
    BoxSizer8->Add(BoxSizer10, 1, wxALL|wxEXPAND, 2);
    BoxSizer6->Add(BoxSizer8, 1, wxALL|wxEXPAND, 0);
    BoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND, 2);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND, 2);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    stSignal = new wxStaticText(this, ID_STATICTEXT1, _("signal"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_RAISED, _T("ID_STATICTEXT1"));
    stSignal->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    stSignal->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    BoxSizer5->Add(stSignal, 0, wxALL|wxEXPAND, 0);
    int GLCanvasAttributes_6[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	wavGraphGL = new wxGLGraph(this, ID_GLCANVAS1, GLCanvasAttributes_6, wxDefaultPosition, wxSize(1232,60), 0, _T("ID_GLCANVAS1"));
    #else
    	wavGraphGL = new wxGLGraph(this, ID_GLCANVAS1, wxDefaultPosition, wxSize(1232,60), 0, _T("ID_GLCANVAS1"), GLCanvasAttributes_6);
    #endif // wxCHECK_VERSION
    BoxSizer5->Add(wavGraphGL, 1, wxALL|wxEXPAND, 0);
    int GLCanvasAttributes_7[] = {
    	WX_GL_RGBA,
    	WX_GL_DOUBLEBUFFER,
    	WX_GL_DEPTH_SIZE,      16,
    	WX_GL_STENCIL_SIZE,    0,
    	0, 0 };
    #if wxCHECK_VERSION(3,0,0)
    	spectrogramGraphGL = new wxGLGraph(this, ID_GLCANVAS2, GLCanvasAttributes_7, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS2"));
    #else
    	spectrogramGraphGL = new wxGLGraph(this, ID_GLCANVAS2, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GLCANVAS2"), GLCanvasAttributes_7);
    #endif // wxCHECK_VERSION
    BoxSizer5->Add(spectrogramGraphGL, 1, wxALL|wxEXPAND, 0);
    BoxSizer3->Add(BoxSizer5, 0, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 2);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    DirDialog1 = new wxDirDialog(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_DIRPICKERCTRL1,wxEVT_COMMAND_DIRPICKER_CHANGED,(wxObjectEventFunction)&vbsFrame::OndpWavFilesDirChanged);
    Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&vbsFrame::OntbPlayToggle);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&vbsFrame::OnlbWavFilesSelect);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&vbsFrame::OnchGraphTypeSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&vbsFrame::OnbtnPlayFormantsClick);
    Connect(ID_GRID2,wxEVT_GRID_CELL_LEFT_CLICK,(wxObjectEventFunction)&vbsFrame::OngridFormantsCellLeftClick);
    //*)

    gridFormants->SetRowLabelSize(0);

    loadFiles("/run/media/asd/1tb/Backup/Code/_voicesync/wav"); // just for debugging!!

    SetName("vbs");
    wxPersistenceManager::Get().RegisterAndRestore(this);

    audio.init();
}

vbsFrame::~vbsFrame() {
    wxPersistenceManager::Get().Save(this);

    //(*Destroy(vbsFrame)
    //*)

    audio.stop();
    audio.term();
}

//
void vbsFrame::drawMusicMatrix() {// fill music matrix
    musicMatrix->SetDefaultCellAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);
    auto mm=wave.musicMatrix;

    musicMatrix->ClearGrid();

    const auto &setAttr = [&](int row, int col, const wxColor*bk, const wxColor*fg) {
        musicMatrix->SetCellBackgroundColour(row, col, *bk);
        musicMatrix->SetCellTextColour(*fg, row, col);
    };

    musicMatrix->SetLabelBackgroundColour(wxColor(192, 188, 8));
    const wxColor bg = wxColor(192, 220, 192);

    for (int o=-2; o<=+2; o++) { // oct -2..+2
        auto oct=o+2;

        setAttr(oct, 12, &bg, wxRED);
        musicMatrix->SetCellValue(wxString::Format("%.0f", 100.0 * wave.mmSumOct[oct]), oct, 12); // sumOct

        for (auto note=0; note<12; note++) {
            auto m= mm[oct][note];
            if (m > 0.1) musicMatrix->SetCellValue(wxString::Format("%.0f", 100.0 * m), oct, note);

            setAttr(oct, note, (m==1)?wxRED:&bg, (m==1)?wxWHITE:wxBLUE);
        }
    }
    for (int n=0; n<12; n++) {
        setAttr(5, n, &bg, wxRED);
        musicMatrix->SetCellValue(wxString::Format("%.0f", 100.0 * wave.mmSumNotes[n]), 5, n);
    }
    setAttr(5, 12, &bg, wxRED);
    musicMatrix->SetCellValue("·", 5,12);
}
//

void vbsFrame::OndpWavFilesDirChanged(wxFileDirPickerEvent& event) {
    loadFiles(event.GetPath());
}


void vbsFrame::loadFiles(wxString path) {
    this->path=path;

    wxDir dir(path);
    if (dir.IsOpened()) {
        lbWavFiles->Clear();
        wxString filename="";
        for(auto cont=dir.GetFirst(&filename, "*.wav"); cont; cont=dir.GetNext(&filename))
            lbWavFiles->Append(filename);
    }
}

void vbsFrame::playSignal() {
    wave.samplesPlayed=0;
    wave.playCompleted=false;

    audio.define(wave.GetChannels(), wave.GetSampleRate(), &wave,
    [](DataCB *dc, void*buffer, int nFrames) {

        Wave*wave=(Wave*)dc->data;
        wave->fillBuffer((float*)buffer, nFrames);

        dc->result = (wave->playCompleted) ? paComplete : paContinue;
    });
    audio.start();
}

void vbsFrame::playWave() {
    audio.stop();

    if(cbAutoPlay->IsChecked() && wave.isLoaded)
        playSignal();
}

void vbsFrame::OnlbWavFilesSelect(wxCommandEvent& event) { // select wav
    lbSignal->Clear();

    auto fullName = wxFileName(path, event.GetString()).GetFullPath();
    if (wave.load(fullName.c_str(), wxAtoi(fftValues->GetStringSelection()))) {
        SetTitle("VBS [" + fullName + "]");

        playWave();

        // signal params
        lbSignal->Append(wxString::Format("channels: %d", wave.GetChannels()));
        lbSignal->Append(wxString::Format("sample rate: %d", wave.GetSampleRate()));
        lbSignal->Append(wxString::Format("secs: %.1f", wave.GetSecs()));
        lbSignal->Append(wxString::Format("# samples: %ld", wave.GetNSamples()));
        lbSignal->Append(wxString::Format("max Freq.: %.1fhz oct:%d, note:%s", wave.maxFreq, MusicFreq::Freq2Oct(wave.maxFreq), MusicFreq::Freq2NoteName(wave.maxFreq)));

        // formants
        for (int i=0; i<5; i++) {
            gridFormants->SetCellValue(i, 0, wxString::Format("%0.1f", fft::db100(wave.formants[i].amp)));
            gridFormants->SetCellValue(i, 1, wxString::Format("%0.1f", wave.formants[i].hz));
        }

        // graphs
        wavGraphGL->SetWav(&wave, GRTYPE_SAMPLES);

        fftGraph0->SetWav(&wave, GRTYPE_FFT);
        fftGraph1->SetWav(&wave, GRTYPE_FFT);
        fftGraph2->SetWav(&wave, GRTYPE_FFT);

        graphGL->SetWav(&wave, (GraphType)((int)GRTYPE_RADIAL + (int)chGraphType->GetSelection()));

        mmGraph->SetWav(&wave, GRTYPE_MUSICMATRIX);
        spectrogramGraphGL->SetWav(&wave, GRTYPE_SPECTROGRAM);

        drawMusicMatrix();


        StatusBar1->SetStatusText(wxString::Format("%d channels, %d sample rate, %ld samples, %.1f secs", wave.GetChannels(), wave.GetSampleRate(), wave.GetNSamples(), wave.GetSecs()));
    }

}

void vbsFrame::OngridFormantsCellLeftClick(wxGridEvent& event) {}

void vbsFrame::OnbtnPlayFormantsClick(wxCommandEvent& event) {
    if (audio.isPlaying()) audio.stop();
    else {
        wave.samplesPlayed=0;
        wave.playCompleted=false;
        float volFormants = slVolume->GetValue() / 100.;
        float binSepparation = slBinSepp->GetValue() / 10.;

        if (wave.formants.size()!=0) {
            audio.define(2, 44100, &wave, // stereo 44100hz
            [=](DataCB *dc, void*buffer, int nFrames) {

                Wave*wave=(Wave*)dc->data;
                float*buff=(float*)buffer;

                double tinc = wave->calcTInc(44100), t = wave->samplesPlayed * tinc; // must be double !

                for (int i=0; i<nFrames*2; i+=2, t+=tinc) {
                    float sL=0, sR=0;
                    int cf=5; // only need 5 formants
                    for(auto &frm : wave->formants) {
                        sL+=frm.amp * sinf(frm.hz * t);
                        sR+=frm.amp * sinf(binSepparation * t) * sinf((binSepparation + frm.hz) * t);
                        if (--cf == 0) break;
                    }
                    buff[i+0] = volFormants * (sL / 5);
                    buff[i+1] = volFormants * (sR / 5);
                }
                wave->samplesPlayed+=nFrames;
            });

            audio.start();
        }
    }
}

void vbsFrame::OntbPlayToggle(wxCommandEvent& event) {
    playSignal();
}

void vbsFrame::OnchGraphTypeSelect(wxCommandEvent& event) {
    graphGL->SetWav(&wave, (GraphType)((int)GRTYPE_RADIAL + (int)chGraphType->GetSelection()));
}
