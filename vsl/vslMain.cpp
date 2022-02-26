/***************************************************************
 * Name:      vslMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-02-21
 * Copyright:  ()
 * License:
 **************************************************************/

#include "vsl/VSL_compiler.h"
#include "Audio.h"
#define DR_WAV_IMPLEMENTATION
#include "dr/dr_wav.h"


#include "vslMain.h"
#include <wx/msgdlg.h>



//(*InternalHeaders(vslFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

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

//(*IdInit(vslFrame)
const long vslFrame::ID_SLIDER1 = wxNewId();
const long vslFrame::ID_CHECKBOX1 = wxNewId();
const long vslFrame::ID_STATICTEXT1 = wxNewId();
const long vslFrame::ID_CHOICE1 = wxNewId();
const long vslFrame::ID_LISTBOX1 = wxNewId();
const long vslFrame::ID_STATICLINE1 = wxNewId();
const long vslFrame::ID_VSLTEXT = wxNewId();
const long vslFrame::ID_STATUSBAR1 = wxNewId();
const long vslFrame::ID_TBPLAY = wxNewId();
const long vslFrame::ID_TB_OPEN = wxNewId();
const long vslFrame::ID_TB_SAVE = wxNewId();
const long vslFrame::ID_TBCLEAR = wxNewId();
const long vslFrame::ID_TB_RAND = wxNewId();
const long vslFrame::ID_TB_EXPORT = wxNewId();
const long vslFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(vslFrame,wxFrame)
    //(*EventTable(vslFrame)
    //*)
END_EVENT_TABLE()


vslFrame::vslFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(vslFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _("vsl player"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(820,400));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    slVolume = new wxSlider(this, ID_SLIDER1, 10, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS, wxDefaultValidator, _T("ID_SLIDER1"));
    slVolume->SetTickFreq(5);
    slVolume->SetPageSize(2);
    slVolume->SetToolTip(_("master volume"));
    slVolume->SetHelpText(_("master volume"));
    BoxSizer2->Add(slVolume, 3, wxALL|wxALIGN_CENTER_VERTICAL, 10);
    cbAutoPlay = new wxCheckBox(this, ID_CHECKBOX1, _("autoplay"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    cbAutoPlay->SetValue(true);
    BoxSizer2->Add(cbAutoPlay, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Symbols"), wxDefaultPosition, wxSize(81,16), wxALIGN_RIGHT, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    chSymbols = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    BoxSizer2->Add(chSymbols, 0, wxALL, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    lbPreset = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, wxBORDER_RAISED, wxDefaultValidator, _T("ID_LISTBOX1"));
    lbPreset->SetForegroundColour(wxColour(141,67,36));
    wxFont lbPresetFont(9,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Monospace"),wxFONTENCODING_DEFAULT);
    lbPreset->SetFont(lbPresetFont);
    BoxSizer3->Add(lbPreset, 1, wxALL|wxEXPAND, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_VERTICAL|wxBORDER_SIMPLE, _T("ID_STATICLINE1"));
    BoxSizer3->Add(StaticLine1, 0, wxALL|wxEXPAND, 5);
    TextVSL = new wxTextCtrl(this, ID_VSLTEXT, wxEmptyString, wxDefaultPosition, wxSize(699,418), wxTE_MULTILINE, wxDefaultValidator, _T("ID_VSLTEXT"));
    TextVSL->SetFocus();
    TextVSL->SetForegroundColour(wxColour(12,0,255));
    wxFont TextVSLFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("FreeMono"),wxFONTENCODING_DEFAULT);
    TextVSL->SetFont(TextVSLFont);
    BoxSizer3->Add(TextVSL, 7, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer3, 10, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -10 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_VERTICAL|wxBORDER_DOUBLE|wxBORDER_SUNKEN, _T("ID_TOOLBAR1"));
    TBPlay = ToolBar1->AddTool(ID_TBPLAY, _("play"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("play VSL"), _("play VSL"));
    TBOpen = ToolBar1->AddTool(ID_TB_OPEN, _("open"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("open VSL file"), _("open VSL file"));
    TB_Save = ToolBar1->AddTool(ID_TB_SAVE, _("save"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("save VSL to file"), _("save current VSL file"));
    ToolBar1->AddSeparator();
    TB_new = ToolBar1->AddTool(ID_TBCLEAR, _("new"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("new vsl"));
    ToolBar1->AddSeparator();
    TB_Rand = ToolBar1->AddTool(ID_TB_RAND, _("random"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("random wave"), _("random wave"));
    TB_Export = ToolBar1->AddTool(ID_TB_EXPORT, _("export_wav"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, _("export to WAV file"), _("export to WAV"));
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    fdOpen = new wxFileDialog(this, _("open VSL"), wxEmptyString, wxEmptyString, _("*.vsl"), wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    fdSave = new wxFileDialog(this, _("Write VSL"), wxEmptyString, wxEmptyString, _("*.vsl"), wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    fdExport = new wxFileDialog(this, _("export to wav"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    SetSizer(BoxSizer1);
    Layout();

    Connect(ID_SLIDER1,wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&vslFrame::OnslVolumeCmdScrollChanged);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&vslFrame::OnchSymbolsSelect);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&vslFrame::OnlbPresetSelect);
    Connect(ID_TBPLAY,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&vslFrame::OntbPlayClicked);
    Connect(ID_TB_OPEN,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&vslFrame::OnTBOpenClicked);
    Connect(ID_TB_SAVE,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&vslFrame::OnTB_SaveClicked);
    Connect(ID_TBCLEAR,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&vslFrame::OnTB_newClicked);
    Connect(ID_TB_RAND,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&vslFrame::OnTB_RandClicked);
    Connect(ID_TB_EXPORT,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&vslFrame::OnTB_ExportClicked);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&vslFrame::OnKeyDown);
    //*)

    Bind(wxEVT_CHAR_HOOK, &vslFrame::OnKeyDown, this); // frame listens keystrokes


    auto s=LR"(// default
const seconds=9, f0=440, f1=Ø·f0, f14=f1/4, s3=[3], s2=[2], k0=0.6, k1=0.2;
let ts3=τ+s3;

~f0  ∿(f0/ts3 + {k0,f1}  ∿(f1/ts3 + {k1, f14}  { f14/(τ+s2)}));
)";

    TextVSL->SetValue(wxString(s));
    dirty=true;

    Audio::init();

    vsl = new VSL_compiler;
    audio = new Audio;

    LoadResources();

    // load cbSymbols with vsl->
    vsl->compile(L"");
    for (auto st : vsl->getSymbols()) chSymbols->Append(wxString(st.first));

    srand(time(NULL)); // randomize

    lbPreset->SetSelection(rand() % lbPreset->GetCount(), true);
}

void vslFrame::SetToolBarBitmap(char *astart, char*aend, int id) {
    wxMemoryInputStream mis(astart, (size_t)(aend-astart));
    auto bmp = wxBitmap(mis, wxBITMAP_TYPE_PNG);
    ToolBar1->SetToolNormalBitmap(id, bmp);
}

void vslFrame::LoadResources() {
    // object size (end-start)
    #define BINSIZE(s) (size_t)(&s##_end - &s##_start)

    // set app icon
    wxMemoryInputStream mis(&_binary_voicesync_logo_ico_start, BINSIZE(_binary_voicesync_logo_ico));
    wxBitmap bmpApp(mis, wxBITMAP_TYPE_ICO);
    wxIcon icon;
    icon.CopyFromBitmap(bmpApp);
    SetIcon(icon);

    // set play/pause bitmaps
    wxMemoryInputStream misPlay(&_binary_play_png_start, BINSIZE(_binary_play_png));
    bmpPlay = wxBitmap(misPlay, wxBITMAP_TYPE_PNG);
    ToolBar1->SetToolNormalBitmap(ID_TBPLAY, bmpPlay);

    wxMemoryInputStream misPause(&_binary_pause_png_start, BINSIZE(_binary_pause_png));
    bmpPause = wxBitmap(misPause, wxBITMAP_TYPE_PNG);

    SetToolBarBitmap(&_binary_transformation_png_start, &_binary_transformation_png_end, ID_TB_EXPORT); // export
    SetToolBarBitmap(&_binary_clear_png_start, &_binary_clear_png_end, ID_TBCLEAR); // new
    SetToolBarBitmap(&_binary_rand_png_start, &_binary_rand_png_end, ID_TB_RAND); // rand

    // fill presets lb
    for (auto ps:preset_names) lbPreset->Append(ps);
}

vslFrame::~vslFrame()
{
    //(*Destroy(vslFrame)
    //*)
    Audio::term();

    delete audio;
    delete vsl;
}


// call back
void soundCallBack(void *userData, void*buffer, int nFrames) {
    VSL_compiler *vsl=(VSL_compiler *)userData;
    vsl->generateBuffer(nFrames, (float*)buffer);
}
////////////


void vslFrame::OntbPlayClicked(wxCommandEvent& event){   PlayVSL();}
void vslFrame::OnTBOpenClicked(wxCommandEvent& event){   LoadVSL();}
void vslFrame::OnTB_SaveClicked(wxCommandEvent& event){  SaveVSL();}

void vslFrame::OnTB_ExportClicked(wxCommandEvent& event)
{
    if (vsl->compile(TextVSL->GetValue().ToStdWstring()))
        ExportVSLWav();
}

void vslFrame::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode()) {
        case WXK_ESCAPE : Close(); break;

        case WXK_F5: PlayVSL(); break;
        case WXK_F2: SaveVSL(); break;
        case WXK_F3: LoadVSL(); break;
        case WXK_F4: ExportVSLWav(); break;

        default: event.Skip(); break;
    }
}

void vslFrame::stop() {
    audio->stop();
    ToolBar1->SetToolNormalBitmap(ID_TBPLAY, bmpPlay);
}

void vslFrame::PlayVSL() {
    auto isPlaying = audio->stop(); // don't compile if playing
    ToolBar1->SetToolNormalBitmap(ID_TBPLAY, isPlaying ? bmpPlay:bmpPause); // change tb icon

    bool ok = vsl->compile(TextVSL->GetValue().ToStdWstring());

    StatusBar1->SetStatusText(wxString::Format(wxT("%s, #chan:%i, rate:%i, vol:%.2f, secs:%.2f, bits:%d %s"),
        ok ? "ok" : vsl->error_msg(), vsl->get_n_channels(), vsl->get_sample_rate(), vsl->get_volume(), vsl->get_seconds(),
                    vsl->get_bits_sample(), vsl->get_floating_point()?"fp":"int"));

    vsl->set_volume((double)slVolume->GetValue() / slVolume->GetMax());
    if (ok && !isPlaying) {
        audio->define(vsl->get_n_channels(), vsl->get_sample_rate(), vsl, soundCallBack);
        audio->start();
    }
    dirty=false;
}

void vslFrame::SaveVSL() {
    stop();

    if (fdSave->ShowModal()==wxID_OK) {
       wxTextFile ft;
       if (ft.Create(fdSave->GetPath())) {
           ft.AddLine(TextVSL->GetValue());
           ft.Write();
           ft.Close();
       }
    }
}

void vslFrame::LoadVSL() {
    stop();

    fdOpen->SetDirectory(vslFolder);
    if (fdOpen->ShowModal()==wxID_OK) {
        vslFolder=fdOpen->GetDirectory();
        wxTextFile ft;
        if (ft.Open(fdOpen->GetPath())) {
            wxString s;

            for (s=ft.GetFirstLine()+"\r"; !ft.Eof(); s+=ft.GetNextLine()+"\r");

            TextVSL->SetValue(s);
            if (cbAutoPlay->IsChecked()) PlayVSL();
        }
    }
}

void vslFrame::OnTextVSLText(wxCommandEvent& event)
{
    dirty=true;
}

void vslFrame::ExportVSLWav() {
    stop();

    if (fdExport->ShowModal()==wxID_OK) {
        auto sfile = fdExport->GetPath().ToStdString(); // 2 step conversion

        drwav wav;
        drwav_data_format format=drwav_data_format{
            .container = drwav_container_riff, .format = DR_WAVE_FORMAT_IEEE_FLOAT,
            .channels = (drwav_uint32) vsl->get_n_channels(), .sampleRate = (drwav_uint32)vsl->get_sample_rate(), .bitsPerSample = 32};

        if (drwav_init_file_write(&wav, sfile.c_str(), &format, NULL)) {
            vector<float>vb = vsl->genSamples();
            drwav_uint64 framesWritten = drwav_write_pcm_frames(&wav, vb.size(), vb.data());
            StatusBar1->SetStatusText(framesWritten==vb.size() ? "export ok":"export failure");
        } else {
            StatusBar1->SetStatusText("bad format");
        }
    }
}


void vslFrame::OnchSymbolsSelect(wxCommandEvent& event)
{
    // insert in text selected symbol
    TextVSL->WriteText(chSymbols->GetString(chSymbols->GetSelection()));
}

void vslFrame::OnlbPresetSelect(wxCommandEvent& event) // set preset
{
    stop();

    auto sel=lbPreset->GetSelection() * 2;
    string s;

    for (auto ch=preset_address[sel+1]; ch<preset_address[sel]; ch++) s+=*ch;
    TextVSL->SetValue(wxString::FromUTF8(s.c_str()));
    if (cbAutoPlay->IsChecked()) PlayVSL();
}

void vslFrame::OnslVolumeCmdScrollChanged(wxScrollEvent& event)
{
    vsl->set_volume((double)slVolume->GetValue() / slVolume->GetMax());
}


void vslFrame::OnTB_newClicked(wxCommandEvent& event)
{
    stop();
    if (wxMessageBox("clear vsl?", "vsl", wxYES_NO)==wxYES)
        TextVSL->Clear();
}

void vslFrame::OnTB_RandClicked(wxCommandEvent& event)
{
    stop();

    wxString s;
    for (auto i=0, n=(rand() % 50)+5; i<n; i++)
        s+=wxString::Format("wave(%4.2f,%5.1f, %.2f)%c%c",
            1.0 * rand()/RAND_MAX, 800.0 * rand()/RAND_MAX, 1.0 * rand()/RAND_MAX, i<n-1 ?'+':';', i&1 ? '\r':' ');
    TextVSL->SetValue(s);
    if (cbAutoPlay->IsChecked()) PlayVSL();
}
