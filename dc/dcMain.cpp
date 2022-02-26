/***************************************************************
 * Name:      dcMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-02-26
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "dcMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(dcFrame)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(dcFrame)
const long dcFrame::ID_COMBOBOX1 = wxNewId();
const long dcFrame::ID_STATICBITMAP1 = wxNewId();
const long dcFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(dcFrame,wxFrame)
    //(*EventTable(dcFrame)
    //*)
END_EVENT_TABLE()

dcFrame::dcFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(dcFrame)
    Create(parent, id, _("Domain Coloring"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("id"));
    SetClientSize(wxSize(403,444));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    cbPreset = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    BoxSizer1->Add(cbPreset, 1, wxALL|wxEXPAND, 5);
    StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("/home/asd/Pictures/dc.png")).Rescale(wxSize(377,383).GetWidth(),wxSize(377,383).GetHeight())), wxDefaultPosition, wxSize(377,383), wxBORDER_DOUBLE, _T("ID_STATICBITMAP1"));
    BoxSizer1->Add(StaticBitmap1, 10, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_COMBOBOX1,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&dcFrame::OnchPresetSelect);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dcFrame::OncbPresetTextEnter);
    Connect(ID_COMBOBOX1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&dcFrame::OncbPresetTextEnter);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&dcFrame::OnResize);
    //*)

    // set presets
    for (auto p : presets) cbPreset->Append(wxString(p));
    preset = 0;
    cbPreset->SetSelection(preset);
    expr = DomainColoring::getPreset(preset);
}

dcFrame::~dcFrame()
{
    //(*Destroy(dcFrame)
    //*)
    if (img_buff!=nullptr) free(img_buff);
    delete dc;
}

void dcFrame::Draw() {

    GetSize(&w, &h);

    w-=12;
    h-=cbPreset->GetSize().GetHeight() + StatusBar1->GetSize().GetHeight()+40;

    StaticBitmap1->SetSize(w,h);

    if (size_t(w*h) != img_size || img_size==0) {
        img_size = w*h;
        if (img_buff!=nullptr) delete[]img_buff;
        img_buff = new uint32_t[img_size];
    }

    dc = new DomainColoring(img_buff, w, h, expr);

    if (!dc->getError()) {
        Timer t0;

        dc->genImageMT();

        auto lap=t0.lap();

        vector <uint8_t>rgb_buff;
        char*charBuff=(char*)img_buff;

        for (auto i=0; i<w*h*4; i++) // remove alpha, keep only rgb
            if (i % 4 != 3) rgb_buff.push_back(charBuff[i]);

        wxImage img;
        img.SetData((unsigned char*)rgb_buff.data(), w, h, true);
        wxBitmap bmp = wxBitmap(img, 32);

        StaticBitmap1->SetBitmap(bmp);
        StatusBar1->SetStatusText(wxString::Format("lap:%ldms, (%i, %i)", lap, w, h));
    }


}

void dcFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void dcFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void dcFrame::OnResize(wxSizeEvent& event)
{
    Draw();
}

void dcFrame::OnchPresetSelect(wxCommandEvent& event)
{
    preset = cbPreset->GetSelection();
    expr = DomainColoring::getPreset(preset);
    Draw();
}

void dcFrame::OncbPresetTextEnter(wxCommandEvent& event)
{
    expr = cbPreset->GetValue().ToStdString();
    Draw();
}
