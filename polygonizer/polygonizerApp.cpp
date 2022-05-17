/***************************************************************
 * Name:      polygonizerApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-05-17
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "polygonizerApp.h"

//(*AppHeaders
#include "polygonizerMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(polygonizerApp);

bool polygonizerApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	polygonizerFrame* Frame = new polygonizerFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
