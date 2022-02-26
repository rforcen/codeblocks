/***************************************************************
 * Name:      dcApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-02-26
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "dcApp.h"

//(*AppHeaders
#include "dcMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(dcApp);

bool dcApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	dcFrame* Frame = new dcFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
