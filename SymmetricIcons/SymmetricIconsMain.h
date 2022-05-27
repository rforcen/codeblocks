/***************************************************************
 * Name:      SymmetricIconsMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SYMMETRICICONSMAIN_H
#define SYMMETRICICONSMAIN_H

//(*Headers(SymmetricIconsFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/statusbr.h>
//*)

#include "engine/SymmIcon.h"
#include "engine/Timer.h"
#include "wxGLCanvasSymmIcon.h"
#include <atomic>

using std::atomic_bool;

class SymmetricIconsFrame: public wxFrame {
  public:

    SymmetricIconsFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~SymmetricIconsFrame();

  private:

    SymmetricIcon symmIcon;
    vector<uint32_t>image;

    bool needsRefresh=true;
    atomic_bool working=false;

    void fillPreset();
    void RePaintAsync(bool refresh=true);
    void selectGrid(wxGridRangeSelectEvent&e);
    void StopWorking();

    wxBitmap genImage(int w, int h, vector<uint32_t>&img_buff) {
        uint8_t *rgb_buff=(uint8_t *)malloc(w*h*3);
        char*charBuff=(char*)img_buff.data();

        for (auto i=0, ix=0; i<w*h*4; i++) // remove alpha, keep only rgb
            if (i % 4 != 3) rgb_buff[ix++]=charBuff[i];

        wxImage img;
        img.SetData((unsigned char*)rgb_buff, w, h, false);
        return wxBitmap(img, 24);
    }

    //(*Handlers(SymmetricIconsFrame)
    void OnResize(wxSizeEvent& event);
    void OnnItersChange(wxSpinEvent& event);
    void OnpresetsSelect(wxCommandEvent& event);
    void OnsaveImageClick(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnbtnStopClick(wxCommandEvent& event);
    //*)

    //(*Identifiers(SymmetricIconsFrame)
    static const long ID_SPINCTRL1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long ID_GRID1;
    static const long ID_GLCANVAS1;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(SymmetricIconsFrame)
    wxButton* btnStop;
    wxButton* saveImage;
    wxGLCanvasSymmIcon* siGLCanvas;
    wxGrid* gridPreset;
    wxSpinCtrl* nIters;
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // SYMMETRICICONSMAIN_H
