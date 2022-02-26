/***************************************************************
 * Name:      vslApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-02-21
 * Copyright:  ()
 * License:
 **************************************************************/

#include "vslApp.h"

//(*AppHeaders
#include "vslMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(vslApp);

bool vslApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	vslFrame* Frame = new vslFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
