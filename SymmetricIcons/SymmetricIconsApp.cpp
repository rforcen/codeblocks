/***************************************************************
 * Name:      SymmetricIconsApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-05-19
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SymmetricIconsApp.h"

//(*AppHeaders
#include "SymmetricIconsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SymmetricIconsApp);

bool SymmetricIconsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	SymmetricIconsFrame* Frame = new SymmetricIconsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
