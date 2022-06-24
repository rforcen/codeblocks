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
#include <wx/choice.h>
#include <wx/dirdlg.h>
#include <wx/filepicker.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/grid.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/tglbtn.h>
//*)
#include <wx/persist/toplevel.h>

#include "common.h"
#include "WavGraph.h"
#include "wxGLGraph.h"
#include "Audio.h"

class vbsFrame: public wxFrame {
  public:

    vbsFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~vbsFrame();

  private:
    void drawMusicMatrix();
    void loadFiles(wxString path);
    void playWave(), playSignal();

    wxString path;
    Wave wave;
    Audio audio;

    //(*Handlers(vbsFrame)
    void OndpWavFilesDirChanged(wxFileDirPickerEvent& event);
    void OnlbWavFilesSelect(wxCommandEvent& event);
    void OngridFormantsCellLeftClick(wxGridEvent& event);
    void OnbtnPlayFormantsClick(wxCommandEvent& event);
    void OntbPlayToggle(wxCommandEvent& event);
    void OnchGraphTypeSelect(wxCommandEvent& event);
    //*)

    //(*Identifiers(vbsFrame)
    static const long ID_DIRPICKERCTRL1;
    static const long ID_TOGGLEBUTTON1;
    static const long ID_CHECKBOX1;
    static const long ID_LISTBOX1;
    static const long ID_STATICTEXT6;
    static const long ID_LISTBOX2;
    static const long ID_STATICTEXT4;
    static const long ID_CHOICE2;
    static const long ID_CHOICE1;
    static const long ID_GLCANVAS3;
    static const long ID_STATICTEXT3;
    static const long ID_GRID1;
    static const long ID_GLCANVAS4;
    static const long ID_STATICTEXT2;
    static const long ID_FFT_GRAPH0;
    static const long ID_FFT_GRAPH1;
    static const long ID_FFT_GRAPH2;
    static const long ID_STATICTEXT5;
    static const long ID_BUTTON1;
    static const long ID_SLIDER1;
    static const long ID_SLIDER2;
    static const long ID_GRID2;
    static const long ID_STATICTEXT1;
    static const long ID_GLCANVAS1;
    static const long ID_GLCANVAS2;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(vbsFrame)
    wxButton* btnPlayFormants;
    wxCheckBox* cbAutoPlay;
    wxChoice* chGraphType;
    wxChoice* fftValues;
    wxDirDialog* DirDialog1;
    wxDirPickerCtrl* dpWavFiles;
    wxGLGraph* fftGraph0;
    wxGLGraph* fftGraph1;
    wxGLGraph* fftGraph2;
    wxGLGraph* graphGL;
    wxGLGraph* mmGraph;
    wxGLGraph* spectrogramGraphGL;
    wxGLGraph* wavGraphGL;
    wxGrid* gridFormants;
    wxGrid* musicMatrix;
    wxListBox* lbSignal;
    wxListBox* lbWavFiles;
    wxSlider* slBinSepp;
    wxSlider* slVolume;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticText3;
    wxStaticText* StaticText4;
    wxStaticText* StaticText5;
    wxStaticText* stSignal;
    wxStatusBar* StatusBar1;
    wxToggleButton* tbPlay;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // VBSMAIN_H
