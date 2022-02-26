/***************************************************************
 * Name:      dcMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-02-26
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DCMAIN_H
#define DCMAIN_H

//(*Headers(dcFrame)
#include <wx/combobox.h>
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/statbmp.h>
#include <wx/statusbr.h>
//*)

#include "dc/DomainColoring.h"
#include "dc/Timer.h"

class dcFrame: public wxFrame
{
    public:

        dcFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~dcFrame();

    private:

        DomainColoring *dc=nullptr;
        uint32_t*img_buff=nullptr;
        size_t img_size=0;
        int w,h;
        int preset=0;
        string expr;

        void Draw();

        //(*Handlers(dcFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnchPresetSelect(wxCommandEvent& event);
        void OncbPresetTextEnter(wxCommandEvent& event);
        //*)

        //(*Identifiers(dcFrame)
        static const long ID_COMBOBOX1;
        static const long ID_STATICBITMAP1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(dcFrame)
        wxBoxSizer* BoxSizer1;
        wxComboBox* cbPreset;
        wxStaticBitmap* StaticBitmap1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DCMAIN_H
