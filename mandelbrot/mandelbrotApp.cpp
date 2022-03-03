/***************************************************************
 * Name:      mandelbrotApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2022-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#include "mandelbrotApp.h"

//(*AppHeaders
#include "mandelbrotMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(mandelbrotApp);

bool mandelbrotApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	mandelbrotFrame* Frame = new mandelbrotFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
