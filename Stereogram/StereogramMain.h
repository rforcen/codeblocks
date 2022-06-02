/***************************************************************
 * Name:      StereogramMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-06-01
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef STEREOGRAMMAIN_H
#define STEREOGRAMMAIN_H

//(*Headers(StereogramFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/imaglist.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/statbmp.h>
#include <wx/statusbr.h>
//*)

#include <deque>
using namespace std;


class StereogramFrame: public wxFrame
{
    public:

        StereogramFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~StereogramFrame();

    private:
        long maskIndex=-1, textIndex=-1;
        void draw();
        wxImage generateStereoGram(int w, int h);
        deque<wxImage> textImgs, maskImgs;
        bool needsRepaint=false;

        //(*Handlers(StereogramFrame)
        void OnlcMaskItemSelect(wxListEvent& event);
        void OnlcTexturesItemSelect(wxListEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnbtnSaveClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(StereogramFrame)
        static const long ID_SPINCTRL1;
        static const long ID_SPINCTRL2;
        static const long ID_BUTTON1;
        static const long ID_LISTCTRL2;
        static const long ID_LISTCTRL1;
        static const long ID_STATICBITMAP1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(StereogramFrame)
        wxButton* btnSave;
        wxImageList* imgListMask;
        wxImageList* imgListTextures;
        wxListCtrl* lcMask;
        wxListCtrl* lcTextures;
        wxSpinCtrl* scHeight;
        wxSpinCtrl* scWidth;
        wxStaticBitmap* uiBmp;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // STEREOGRAMMAIN_H
