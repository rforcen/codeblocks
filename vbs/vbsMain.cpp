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
const long vbsFrame::ID_CHECKBOX1 = wxNewId();
const long vbsFrame::ID_LISTBOX1 = wxNewId();
const long vbsFrame::ID_STATICTEXT4 = wxNewId();
const long vbsFrame::ID_RADIAL = wxNewId();
const long vbsFrame::ID_SPIRAL = wxNewId();
const long vbsFrame::ID_NOTEBOOK1 = wxNewId();
const long vbsFrame::ID_STATICTEXT3 = wxNewId();
const long vbsFrame::ID_GRID1 = wxNewId();
const long vbsFrame::ID_MMGRAPH = wxNewId();
const long vbsFrame::ID_STATICTEXT2 = wxNewId();
const long vbsFrame::ID_FFT = wxNewId();
const long vbsFrame::ID_STATICTEXT6 = wxNewId();
const long vbsFrame::ID_LISTBOX2 = wxNewId();
const long vbsFrame::ID_STATICTEXT5 = wxNewId();
const long vbsFrame::ID_BUTTON1 = wxNewId();
const long vbsFrame::ID_SLIDER1 = wxNewId();
const long vbsFrame::ID_SLIDER2 = wxNewId();
const long vbsFrame::ID_GRID2 = wxNewId();
const long vbsFrame::ID_STATICTEXT1 = wxNewId();
const long vbsFrame::ID_SIGNAL = wxNewId();
const long vbsFrame::ID_SPECTROGRAM = wxNewId();
const long vbsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(vbsFrame,wxFrame)
    //(*EventTable(vbsFrame)
    //*)
END_EVENT_TABLE()

vbsFrame::vbsFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(vbsFrame)
    wxBoxSizer* BoxSizer10;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer13;
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
    cbAutoPlay = new wxCheckBox(this, ID_CHECKBOX1, _("autoplay"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    cbAutoPlay->SetValue(false);
    BoxSizer2->Add(cbAutoPlay, 0, wxALL|wxEXPAND, 5);
    lbWavFiles = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(180,291), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer2->Add(lbWavFiles, 1, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 2);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer7 = new wxBoxSizer(wxVERTICAL);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("radial spectrum"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT4"));
    StaticText4->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText4->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    BoxSizer7->Add(StaticText4, 0, wxALL|wxEXPAND, 0);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    radialGraph = new WavGraph(Notebook1, ID_RADIAL, wxPoint(2,251), wxSize(426,507), wxTAB_TRAVERSAL, _T("ID_RADIAL"));
    spiralGraph = new WavGraph(Notebook1, ID_SPIRAL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SPIRAL"));
    Notebook1->AddPage(radialGraph, _("radial"), false);
    Notebook1->AddPage(spiralGraph, _("spiral"), false);
    BoxSizer7->Add(Notebook1, 1, wxALL|wxEXPAND, 2);
    BoxSizer4->Add(BoxSizer7, 1, wxALL|wxEXPAND, 2);
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
    mmGraph = new WavGraph(this, ID_MMGRAPH, wxDefaultPosition, wxSize(608,62), wxTAB_TRAVERSAL, _T("ID_MMGRAPH"));
    BoxSizer6->Add(mmGraph, 0, wxALL|wxEXPAND, 2);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("spectrum"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_STATICTEXT2"));
    StaticText2->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText2->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    BoxSizer6->Add(StaticText2, 0, wxALL|wxEXPAND, 0);
    BoxSizer8 = new wxBoxSizer(wxVERTICAL);
    BoxSizer9 = new wxBoxSizer(wxVERTICAL);
    fftGraph = new WavGraph(this, ID_FFT, wxDefaultPosition, wxSize(600,148), wxTAB_TRAVERSAL, _T("ID_FFT"));
    fftGraph->SetToolTip(_("fft"));
    BoxSizer9->Add(fftGraph, 1, wxALL|wxEXPAND, 2);
    BoxSizer8->Add(BoxSizer9, 1, wxALL|wxEXPAND, 2);
    BoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer11 = new wxBoxSizer(wxVERTICAL);
    StaticText5 = new wxStaticText(this, ID_STATICTEXT6, _("signal params"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_RAISED, _T("ID_STATICTEXT6"));
    StaticText5->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText5->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    BoxSizer11->Add(StaticText5, 0, wxALL|wxEXPAND, 0);
    lbSignal = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
    lbSignal->SetBackgroundColour(wxColour(192,220,192));
    BoxSizer11->Add(lbSignal, 1, wxALL|wxEXPAND, 0);
    BoxSizer10->Add(BoxSizer11, 1, wxALL|wxEXPAND, 2);
    BoxSizer12 = new wxBoxSizer(wxVERTICAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT5, _("formants"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_RAISED, _T("ID_STATICTEXT5"));
    StaticText1->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    StaticText1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    BoxSizer12->Add(StaticText1, 0, wxALL|wxEXPAND, 0);
    btnPlayFormants = new wxButton(this, ID_BUTTON1, _("play"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer12->Add(btnPlayFormants, 1, wxALL|wxEXPAND, 0);
    BoxSizer13 = new wxBoxSizer(wxHORIZONTAL);
    slVolume = new wxSlider(this, ID_SLIDER1, 30, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER1"));
    wxFont slVolumeFont(9,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    slVolume->SetFont(slVolumeFont);
    slVolume->SetToolTip(_("formants vol."));
    BoxSizer13->Add(slVolume, 1, wxALL|wxEXPAND, 0);
    slBinSepp = new wxSlider(this, ID_SLIDER2, 15, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_VERTICAL|wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER2"));
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
    BoxSizer13->Add(gridFormants, 0, wxALL|wxEXPAND, 0);
    BoxSizer12->Add(BoxSizer13, 0, wxALL|wxEXPAND, 0);
    BoxSizer10->Add(BoxSizer12, 0, wxALL|wxEXPAND, 2);
    BoxSizer8->Add(BoxSizer10, 1, wxALL|wxEXPAND, 2);
    BoxSizer6->Add(BoxSizer8, 1, wxALL|wxEXPAND, 2);
    BoxSizer4->Add(BoxSizer6, 1, wxALL|wxEXPAND, 2);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxEXPAND, 2);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    stSignal = new wxStaticText(this, ID_STATICTEXT1, _("signal"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE|wxBORDER_RAISED, _T("ID_STATICTEXT1"));
    stSignal->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
    stSignal->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUHILIGHT));
    BoxSizer5->Add(stSignal, 0, wxALL|wxEXPAND, 0);
    wavGraph = new WavGraph(this, ID_SIGNAL, wxDefaultPosition, wxSize(1228,57), wxTAB_TRAVERSAL, _T("ID_SIGNAL"));
    wavGraph->SetToolTip(_("signal"));
    BoxSizer5->Add(wavGraph, 1, wxALL|wxEXPAND, 2);
    spectrogramGraph = new WavGraph(this, ID_SPECTROGRAM, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SPECTROGRAM"));
    BoxSizer5->Add(spectrogramGraph, 1, wxEXPAND, 0);
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
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&vbsFrame::OnlbWavFilesSelect);
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

            if (m==1) {
                setAttr(oct, note, wxRED, wxWHITE);
            } else {
                setAttr(oct, note, &bg, wxBLUE);
            }
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

void vbsFrame::playWave() {
    audio.stop();

    if(cbAutoPlay->IsChecked()) {
        wave.samplesPlayed=0;
        wave.playCompleted=false;

        audio.define(wave.GetChannels(), wave.GetSampleRate(), &wave,
        [](void *dataCB, void*buffer, int nFrames) {
            DataCB *dc=(DataCB*)dataCB;
            Wave*wave=(Wave*)dc->data;
            float*buff=(float*)buffer;

            for (int i=0, si=wave->samplesPlayed; i<nFrames && si<wave->GetNSamples(); i++, si++)
                buff[i]=wave->GetSample(si);

            wave->samplesPlayed+=nFrames;

            if (wave->samplesPlayed >= wave->GetNSamples()) {
                wave->samplesPlayed=0;
                wave->playCompleted=true;
                dc->result=paComplete;
            }
        });
        audio.start();
    }
}

void vbsFrame::OnlbWavFilesSelect(wxCommandEvent& event) { // select wav
    lbSignal->Clear();

    auto fullName = wxFileName(path, event.GetString()).GetFullPath();
    if (wave.load(fullName.c_str())) {
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
        wavGraph->SetWav(&wave, GRTYPE_SAMPLES);
        fftGraph->SetWav(&wave, GRTYPE_FFT);
        radialGraph->SetWav(&wave, GRTYPE_RADIAL);
        spiralGraph->SetWav(&wave, GRTYPE_SPIRAL);
        mmGraph->SetWav(&wave, GRTYPE_MUSICMATRIX);
        spectrogramGraph->SetWav(&wave, GRTYPE_SPECTROGRAM);

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
        wave.volFormants = slVolume->GetValue() / 100.;
        wave.binSepparation = slBinSepp->GetValue() / 10.;

        if (wave.formants.size()!=0) {
            audio.define(2, 44100, &wave, // stereo 44100hz
            [](void *dataCB, void*buffer, int nFrames) {

                DataCB *dc=(DataCB*)dataCB;
                Wave*wave=(Wave*)dc->data;
                float*buff=(float*)buffer;

                double tinc = wave->calcTInc(44100), t = wave->samplesPlayed * tinc; // must double !

                for (int i=0; i<nFrames*2; i+=2, t+=tinc) {
                    float sL=0, sR=0;
                    int cf=5; // only need 5 formants
                    for(auto &frm : wave->formants) {
                        sL+=frm.amp * sinf(frm.hz * t);
                        sR+=frm.amp * sinf(wave->binSepparation * t) * sinf((wave->binSepparation + frm.hz) * t);
                        if (--cf == 0) break;
                    }
                    buff[i+0] = wave->volFormants * (sL / 5);
                    buff[i+1] = wave->volFormants * (sR / 5);
                }
                wave->samplesPlayed+=nFrames;
            });

            audio.start();
        }
    }
}
