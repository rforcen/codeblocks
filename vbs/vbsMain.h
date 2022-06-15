/***************************************************************
 * Name:      vbsMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-06-08
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef VBSMAIN_H
#define VBSMAIN_H

//(*Headers(vbsFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dirdlg.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
//*)
#include <wx/persist/toplevel.h>

#include "common.h"
#include "WavGraph.h"
#include "Audio.h"


class vbsFrame: public wxFrame {
  public:

    vbsFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~vbsFrame();

  private:
    void drawMusicMatrix();
    void loadFiles(wxString path);
    void playWave();

    wxString path;
    Wave wave;
    Audio audio;

    //(*Handlers(vbsFrame)
    void OndpWavFilesDirChanged(wxFileDirPickerEvent& event);
    void OnlbWavFilesSelect(wxCommandEvent& event);
    void OngridFormantsCellLeftClick(wxGridEvent& event);
    void OnbtnPlayFormantsClick(wxCommandEvent& event);
    //*)

    //(*Identifiers(vbsFrame)
    static const long ID_DIRPICKERCTRL1;
    static const long ID_CHECKBOX1;
    static const long ID_LISTBOX1;
    static const long ID_STATICTEXT4;
    static const long ID_RADIAL;
    static const long ID_SPIRAL;
    static const long ID_NOTEBOOK1;
    static const long ID_STATICTEXT3;
    static const long ID_GRID1;
    static const long ID_MMGRAPH;
    static const long ID_STATICTEXT2;
    static const long ID_FFT;
    static const long ID_STATICTEXT6;
    static const long ID_LISTBOX2;
    static const long ID_STATICTEXT5;
    static const long ID_BUTTON1;
    static const long ID_SLIDER1;
    static const long ID_SLIDER2;
    static const long ID_GRID2;
    static const long ID_STATICTEXT1;
    static const long ID_SIGNAL;
    static const long ID_SPECTROGRAM;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(vbsFrame)
    WavGraph* fftGraph;
    WavGraph* mmGraph;
    WavGraph* radialGraph;
    WavGraph* spectrogramGraph;
    WavGraph* spiralGraph;
    WavGraph* wavGraph;
    wxButton* btnPlayFormants;
    wxCheckBox* cbAutoPlay;
    wxDirDialog* DirDialog1;
    wxDirPickerCtrl* dpWavFiles;
    wxGrid* gridFormants;
    wxGrid* musicMatrix;
    wxListBox* lbSignal;
    wxListBox* lbWavFiles;
    wxNotebook* Notebook1;
    wxSlider* slBinSepp;
    wxSlider* slVolume;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticText3;
    wxStaticText* StaticText4;
    wxStaticText* StaticText5;
    wxStaticText* stSignal;
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // VBSMAIN_H
