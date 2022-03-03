/***************************************************************
 * Name:      mandelbrotMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-02-27
 * Copyright:  ()
 * License:
 **************************************************************/

#include "mandelbrotMain.h"
#include <wx/msgdlg.h>
#include <wx/graphics.h>
#include <wx/dcclient.h>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

//(*InternalHeaders(mandelbrotFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f ) {
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

//(*IdInit(mandelbrotFrame)
const long mandelbrotFrame::ID_SPINCTRL1 = wxNewId();
const long mandelbrotFrame::ID_CHOICE1 = wxNewId();
const long mandelbrotFrame::ID_SPINCTRL2 = wxNewId();
const long mandelbrotFrame::ID_STATICTEXT1 = wxNewId();
const long mandelbrotFrame::ID_BUTTON1 = wxNewId();
const long mandelbrotFrame::ID_BUTTON2 = wxNewId();
const long mandelbrotFrame::ID_BUTTON3 = wxNewId();
const long mandelbrotFrame::ID_LISTBOX1 = wxNewId();
const long mandelbrotFrame::ID_PANEL1 = wxNewId();
const long mandelbrotFrame::ID_STATUSBAR1 = wxNewId();
const long mandelbrotFrame::ID_TOOLBARITEM1 = wxNewId();
const long mandelbrotFrame::ID_TOOLBARITEM2 = wxNewId();
const long mandelbrotFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(mandelbrotFrame,wxFrame)
    //(*EventTable(mandelbrotFrame)
    //*)
END_EVENT_TABLE()

mandelbrotFrame::mandelbrotFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(mandelbrotFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, id, _("mandelbrot"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(442,412));
    SetMinSize(wxSize(-1,-1));
    SetMaxSize(wxSize(-1,-1));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNSHADOW));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    scIters = new wxSpinCtrl(this, ID_SPINCTRL1, _T("256"), wxDefaultPosition, wxSize(101,30), 0, 100, 9000, 256, _T("ID_SPINCTRL1"));
    scIters->SetValue(_T("256"));
    scIters->SetToolTip(_("# iterations"));
    BoxSizer2->Add(scIters, 0, wxEXPAND, 0);
    chEngine = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    chEngine->Append(_("f32 - float"));
    chEngine->SetSelection( chEngine->Append(_("f64 - double")) );
    chEngine->Append(_("f128 - long double"));
    chEngine->Append(_("f256 - mpfr"));
    chEngine->Append(_("f512 - mpfr"));
    chEngine->Append(_("f1024 - mpfr"));
    chEngine->Append(_("f2048 - mpfr"));
    chEngine->Append(_("f4096 - mpfr"));
    chEngine->SetToolTip(_("precision"));
    BoxSizer2->Add(chEngine, 0, wxALL|wxEXPAND, 0);
    scResolution = new wxSpinCtrl(this, ID_SPINCTRL2, _T("1024"), wxDefaultPosition, wxDefaultSize, 0, 256, 8192, 1024, _T("ID_SPINCTRL2"));
    scResolution->SetValue(_T("1024"));
    scResolution->SetToolTip(_("export resolution"));
    BoxSizer2->Add(scResolution, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("bookmarks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    btAddBk = new wxButton(this, ID_BUTTON1, _("+"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(btAddBk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    btDelBk = new wxButton(this, ID_BUTTON2, _("-"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(btDelBk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    btClearBk = new wxButton(this, ID_BUTTON3, _("clear"), wxDefaultPosition, wxSize(60,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer3->Add(btClearBk, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    lbBookMarks = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer2->Add(lbBookMarks, 3, wxEXPAND, 0);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 0);
    ImagePanel = new wxImagePanel(this, ID_PANEL1, wxDefaultPosition, wxSize(563,477), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    ImagePanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    BoxSizer1->Add(ImagePanel, 1, wxALL|wxEXPAND, 0);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL, _T("ID_TOOLBAR1"));
    tbReset = ToolBar1->AddTool(ID_TOOLBARITEM1, _("reset"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    tbExport = ToolBar1->AddTool(ID_TOOLBARITEM2, _("export"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_GO_FORWARD")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    ImageList1 = new wxImageList(16, 16, 1);
    fdExport = new wxFileDialog(this, _("export file"), wxEmptyString, wxEmptyString, _("*.png"), wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&mandelbrotFrame::OnscItersChange);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&mandelbrotFrame::OnchEngineSelect);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&mandelbrotFrame::OnbtAddBkClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&mandelbrotFrame::OnbtDelBkClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&mandelbrotFrame::OnbtClearBkClick);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&mandelbrotFrame::OnlbBookMarksSelect);
    Connect(ID_TOOLBARITEM1,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&mandelbrotFrame::OntbResetClicked);
    Connect(ID_TOOLBARITEM2,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&mandelbrotFrame::OntbExportClicked);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&mandelbrotFrame::OnClose);
    //*)

    Bind(wxEVT_CHAR_HOOK, &mandelbrotFrame::OnKeyDown, this); // frame listens keystrokes
    ImagePanel->setStatusBar(StatusBar1);

    // read .bmk file & load

    wxFileName f(wxStandardPaths::Get().GetExecutablePath());
    wxString bkmPath(f.GetPath() + "/mandel.bkm");

    if (wxFile::Access(bkmPath, wxFile::read)) {
        wxFile fh(bkmPath);
        if (fh.IsOpened()) {
            while (!fh.Eof()) {
                auto ms=new Mandelbrot<double>;
                if (fh.Read(ms, sizeof(*ms)) == sizeof(*ms))
                    lbBookMarks->Append(ms->toString(), ms);
            }
        }
    }
}

mandelbrotFrame::~mandelbrotFrame() {
    //(*Destroy(mandelbrotFrame)
    //*)
}

void mandelbrotFrame::OnKeyDown(wxKeyEvent& event) {
    switch (event.GetKeyCode()) {
    case WXK_ESCAPE :
        Close();
        break;
    case WXK_SPACE :
        ImagePanel->setDefault();
        break;
    case WXK_NUMPAD_ADD:
        ImagePanel->Add(lbBookMarks);
        break;
    case WXK_NUMPAD_SUBTRACT:
        ImagePanel->Del(lbBookMarks);
        break;

    case WXK_PAGEDOWN:
        ImagePanel->incIters(-50);
        scIters->SetValue(ImagePanel->iters);
        break;

    case WXK_PAGEUP:
        ImagePanel->incIters(+50);
        scIters->SetValue(ImagePanel->iters);
        break;

    default:
        event.Skip();
        break;
    }
}

void mandelbrotFrame::OntbResetClicked(wxCommandEvent& event) {
    ImagePanel->setDefault();
}

void mandelbrotFrame::OnscItersChange(wxSpinEvent& event) {
    ImagePanel->setIters(event.GetValue());
}

void mandelbrotFrame::OnbtAddBkClick(wxCommandEvent& event) {
    ImagePanel->Add(lbBookMarks);
}

void mandelbrotFrame::OnlbBookMarksSelect(wxCommandEvent& event) {
    ImagePanel->Get(lbBookMarks);
}

void mandelbrotFrame::OnClose(wxCloseEvent& event) {

    wxFileName f(wxStandardPaths::Get().GetExecutablePath());
    wxString appPath(f.GetPath());
    wxFile fh(appPath + "/mandel.bkm", wxFile::write);

    if (fh.IsOpened()) {
        for (size_t i=0; i<lbBookMarks->GetCount(); i++) {
            auto ms=(Mandelbrot<double>*)lbBookMarks->GetClientData(i);
            fh.Write(ms, sizeof(*ms));
            delete ms;
        }
        fh.Close();
    }
    event.Skip();
}

void mandelbrotFrame::OnbtDelBkClick(wxCommandEvent& event) {
    ImagePanel->Del(lbBookMarks);
}

void mandelbrotFrame::OnbtClearBkClick(wxCommandEvent& event) {
    for (size_t i=0; i<lbBookMarks->GetCount(); i++)
        delete (Mandelbrot<double>*)lbBookMarks->GetClientData(i);

    lbBookMarks->Clear();
}

void mandelbrotFrame::OnchEngineSelect(wxCommandEvent& event)
{
    ImagePanel->setEngine((MandelEngine)event.GetSelection());
}

void mandelbrotFrame::OntbExportClicked(wxCommandEvent& event)
{
    if (fdExport->ShowModal()==wxID_OK) {
        ImagePanel->generateFractal(scResolution->GetValue(), scResolution->GetValue());
        ImagePanel->mandelBmp.SaveFile(fdExport->GetPath(), wxBITMAP_TYPE_PNG);
    }
}
