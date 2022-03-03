/***************************************************************
 * Name:      mandelbrotMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef MANDELBROTMAIN_H
#define MANDELBROTMAIN_H

//(*Headers(mandelbrotFrame)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/imaglist.h>
#include <wx/listbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/toolbar.h>
//*)

#include "mandel/mandel.h"
#include "wxImagePanel.h"

class mandelbrotFrame: public wxFrame
{
public:

    mandelbrotFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~mandelbrotFrame();

private:

    //(*Handlers(mandelbrotFrame)
    void OnKeyDown(wxKeyEvent& event);
    void OntbResetClicked(wxCommandEvent& event);
    void OnscItersChange(wxSpinEvent& event);
    void OnbtAddBkClick(wxCommandEvent& event);
    void OnlbBookMarksSelect(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnbtDelBkClick(wxCommandEvent& event);
    void OnbtClearBkClick(wxCommandEvent& event);
    void OnchEngineSelect(wxCommandEvent& event);
    void OntbExportClicked(wxCommandEvent& event);
    //*)

    //(*Identifiers(mandelbrotFrame)
    static const long ID_SPINCTRL1;
    static const long ID_CHOICE1;
    static const long ID_SPINCTRL2;
    static const long ID_STATICTEXT1;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long ID_BUTTON3;
    static const long ID_LISTBOX1;
    static const long ID_PANEL1;
    static const long ID_STATUSBAR1;
    static const long ID_TOOLBARITEM1;
    static const long ID_TOOLBARITEM2;
    static const long ID_TOOLBAR1;
    //*)

    //(*Declarations(mandelbrotFrame)
    wxButton* btAddBk;
    wxButton* btClearBk;
    wxButton* btDelBk;
    wxChoice* chEngine;
    wxFileDialog* fdExport;
    wxImageList* ImageList1;
    wxImagePanel* ImagePanel;
    wxListBox* lbBookMarks;
    wxSpinCtrl* scIters;
    wxSpinCtrl* scResolution;
    wxStaticText* StaticText1;
    wxStatusBar* StatusBar1;
    wxToolBar* ToolBar1;
    wxToolBarToolBase* tbExport;
    wxToolBarToolBase* tbReset;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // MANDELBROTMAIN_H
