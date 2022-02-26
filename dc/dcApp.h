/***************************************************************
 * Name:      dcApp.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2022-02-26
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef DCAPP_H
#define DCAPP_H

#include <wx/app.h>

class dcApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // DCAPP_H
