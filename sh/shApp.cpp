/***************************************************************
 * Name:      shApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-03-01
 * Copyright:  ()
 * License:
 **************************************************************/

#include "shApp.h"

//(*AppHeaders
#include "shMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(shApp);

bool shApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	shFrame* Frame = new shFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
