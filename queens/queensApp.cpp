/***************************************************************
 * Name:      queensApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-06-24
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "queensApp.h"

//(*AppHeaders
#include "queensMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(queensApp);

bool queensApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	queensFrame* Frame = new queensFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
