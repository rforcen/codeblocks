/***************************************************************
 * Name:      StereogramApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-06-01
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "StereogramApp.h"

//(*AppHeaders
#include "StereogramMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(StereogramApp);

bool StereogramApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	StereogramFrame* Frame = new StereogramFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
