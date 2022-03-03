/***************************************************************
 * Name:      shMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-03-01
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SHMAIN_H
#define SHMAIN_H

//(*Headers(shFrame)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/statusbr.h>
//*)

#include "wxGLCanvasSH.h"

class shFrame: public wxFrame
{
    public:

        shFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~shFrame();

    private:

        //(*Handlers(shFrame)
        void OnlbCodesSelect(wxCommandEvent& event);
        void OnscColorMapChange(wxSpinEvent& event);
        void OnscResolChange(wxSpinEvent& event);
        void OnbtSaveClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(shFrame)
        static const long ID_CHOICE1;
        static const long ID_BUTTON1;
        static const long ID_SPINCTRL1;
        static const long ID_SPINCTRL2;
        static const long ID_LISTBOX1;
        static const long ID_GLCANVAS1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(shFrame)
        wxButton* btSave;
        wxChoice* chFileType;
        wxGLCanvasSH* GLCanvasSH;
        wxListBox* lbCodes;
        wxSpinCtrl* scColorMap;
        wxSpinCtrl* scResol;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SHMAIN_H
