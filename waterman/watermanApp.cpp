/***************************************************************
 * Name:      watermanApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-05-16
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "watermanApp.h"

//(*AppHeaders
#include "watermanMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(watermanApp);

bool watermanApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	watermanFrame* Frame = new watermanFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
