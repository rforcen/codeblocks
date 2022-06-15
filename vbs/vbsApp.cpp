/***************************************************************
 * Name:      vbsApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-06-08
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "vbsApp.h"

//(*AppHeaders
#include "vbsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(vbsApp);

bool vbsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	vbsFrame* Frame = new vbsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
