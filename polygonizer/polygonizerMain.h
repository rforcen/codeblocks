/***************************************************************
 * Name:      polygonizerMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-05-17
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef POLYGONIZERMAIN_H
#define POLYGONIZERMAIN_H

//(*Headers(polygonizerFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/statusbr.h>
//*)

#include "renderPoly.h"

class polygonizerFrame: public wxFrame
{
    public:

        polygonizerFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~polygonizerFrame();

    private:

        void setFunc();


        //(*Handlers(polygonizerFrame)
        void OnListBox1Select(wxCommandEvent& event);
        void OnscResolChange(wxSpinEvent& event);
        void OnSpinCtrlDouble1Change(wxSpinDoubleEvent& event);
        void OnbtnSaveCTMClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(polygonizerFrame)
        static const long ID_SPINCTRL1;
        static const long ID_SPINCTRLDOUBLE1;
        static const long ID_BUTTON1;
        static const long ID_LISTBOX1;
        static const long ID_GLCANVAS1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(polygonizerFrame)
        RenderPoly* GLCanvas1;
        wxButton* btnSaveCTM;
        wxListBox* ListBox1;
        wxSpinCtrl* scResol;
        wxSpinCtrlDouble* scBounds;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // POLYGONIZERMAIN_H
