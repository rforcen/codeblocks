/***************************************************************
 * Name:      queensMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-06-24
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef QUEENSMAIN_H
#define QUEENSMAIN_H

//(*Headers(queensFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/glcanvas.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/statusbr.h>
//*)

#include <wx/persist/toplevel.h>
#include <wx/timer.h>
#include "Timer.h"
#include "wxGLGraph.h"

class queensFrame: public wxFrame
{
    public:

        queensFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~queensFrame();

        Queens q=Queens(8);
        wxTimer timer;
        Timer t0;

    private:

        //(*Handlers(queensFrame)
        void OnnQueensChange(wxSpinEvent& event);
        void OnbtFirstClick(wxCommandEvent& event);
        void OnlbSolutionsSelect(wxCommandEvent& event);
        //*)

        //(*Identifiers(queensFrame)
        static const long ID_BUTTON1;
        static const long ID_SPINCTRL1;
        static const long ID_LISTBOX1;
        static const long ID_GLCANVAS1;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(queensFrame)
        wxButton* btFirst;
        wxGLGraph* board;
        wxListBox* lbSolutions;
        wxSpinCtrl* nQueens;
        wxStatusBar* StatusBar1;
        //*)

        void OnTimer(wxTimerEvent&);
        void transformations();

        DECLARE_EVENT_TABLE()
};

#endif // QUEENSMAIN_H
