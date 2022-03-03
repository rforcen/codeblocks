/***************************************************************
 * Name:      mandelbrotApp.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2022-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef MANDELBROTAPP_H
#define MANDELBROTAPP_H

#include <wx/app.h>

class mandelbrotApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // MANDELBROTAPP_H
