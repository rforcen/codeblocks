/***************************************************************
 * Name:      StereogramMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2022-06-01
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "StereogramMain.h"
#include <wx/msgdlg.h>
#include <wx/dir.h>
#include <wx/mstream.h>

#include "stereogram.h"
#include "Timer.h"
#include "resources.h"

//(*IdInit(StereogramFrame)
const long StereogramFrame::ID_SPINCTRL1 = wxNewId();
const long StereogramFrame::ID_SPINCTRL2 = wxNewId();
const long StereogramFrame::ID_BUTTON1 = wxNewId();
const long StereogramFrame::ID_LISTCTRL2 = wxNewId();
const long StereogramFrame::ID_LISTCTRL1 = wxNewId();
const long StereogramFrame::ID_STATICBITMAP1 = wxNewId();
const long StereogramFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(StereogramFrame,wxFrame)
    //(*EventTable(StereogramFrame)
    //*)
END_EVENT_TABLE()

StereogramFrame::StereogramFrame(wxWindow* parent,wxWindowID id) {
    //(*Initialize(StereogramFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, id, _("Stereographs"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(646,451));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    scWidth = new wxSpinCtrl(this, ID_SPINCTRL1, _T("3840"), wxDefaultPosition, wxSize(104,32), 0, 1024, 8192, 3840, _T("ID_SPINCTRL1"));
    scWidth->SetValue(_T("3840"));
    scWidth->SetToolTip(_("image width"));
    BoxSizer2->Add(scWidth, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    scHeight = new wxSpinCtrl(this, ID_SPINCTRL2, _T("2160"), wxDefaultPosition, wxSize(104,32), 0, 1024, 8192, 2160, _T("ID_SPINCTRL2"));
    scHeight->SetValue(_T("2160"));
    scHeight->SetToolTip(_("image height"));
    BoxSizer2->Add(scHeight, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnSave = new wxButton(this, ID_BUTTON1, _("save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(btnSave, 0, wxALL|wxEXPAND, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 2);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    lcTextures = new wxListCtrl(this, ID_LISTCTRL2, wxDefaultPosition, wxSize(64,380), wxLC_LIST|wxLC_REPORT|wxLC_ICON|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_VRULES|wxBORDER_SIMPLE|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL2"));
    wxFont lcTexturesFont(31,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    lcTextures->SetFont(lcTexturesFont);
    BoxSizer3->Add(lcTextures, 0, wxALL|wxEXPAND, 5);
    lcMask = new wxListCtrl(this, ID_LISTCTRL1, wxDefaultPosition, wxSize(64,380), wxLC_LIST|wxLC_REPORT|wxLC_ICON|wxLC_NO_HEADER|wxLC_SINGLE_SEL|wxLC_VRULES|wxBORDER_SIMPLE|wxVSCROLL, wxDefaultValidator, _T("ID_LISTCTRL1"));
    wxFont lcMaskFont(31,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    lcMask->SetFont(lcMaskFont);
    BoxSizer3->Add(lcMask, 0, wxALL|wxEXPAND, 5);
    uiBmp = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxSize(355,380), wxBORDER_SIMPLE, _T("ID_STATICBITMAP1"));
    BoxSizer3->Add(uiBmp, 1, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    imgListTextures = new wxImageList(64, 64, 1);
    imgListMask = new wxImageList(64, 64, 1);
    SetSizer(BoxSizer1);
    Layout();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&StereogramFrame::OnbtnSaveClick);
    Connect(ID_LISTCTRL2,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&StereogramFrame::OnlcTexturesItemSelect);
    Connect(ID_LISTCTRL1,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&StereogramFrame::OnlcMaskItemSelect);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&StereogramFrame::OnPaint);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&StereogramFrame::OnResize);
    //*)

    // load resources from .o generated w/ mk_rsc.sh script
    const auto &loadResourcesImagesObj = [this](char*Resource[], deque<wxImage>&imgDeque, wxImageList*imgList, wxListCtrl*listCtrl) -> void {
        const auto width=64;

        for (int i=0; Resource[i]!=nullptr; i+=2) {
            wxMemoryInputStream mis(Resource[i+1], Resource[i] - Resource[i+1]); // size = end - start
            wxImage img = wxImage(mis);

            if (img.IsOk()) {
                imgDeque.push_front(img); // save original one
                img.Rescale(width, width);
                imgList->Add(img);
            }
        }

        listCtrl->SetImageList(imgList, wxIMAGE_LIST_NORMAL);

        wxListItem li; // column 0
        li.SetId(0);
        li.SetWidth(width);

        listCtrl->InsertColumn(0, li);

        for (int i=0; i<imgList->GetImageCount(); i++) {
            listCtrl->InsertItem(0, i);
            listCtrl->SetItemImage(li, i);
        }
    };

    // load a resource folders image list
    const auto &loadResourcesImages = [this](wxString folder, deque<wxImage>&imgDeque, wxImageList*imgList, wxListCtrl*listCtrl) -> void {
        const auto width=64;

        auto rscDir=wxGetCwd()+folder;
        wxDir dir(rscDir);
        wxString filename;
        for (auto cont = dir.GetFirst(&filename, "*.jpg"); cont ;  cont = dir.GetNext(&filename)) {
            wxImage img(rscDir + filename);
            imgDeque.push_front(img); // save original one

            img.Rescale(width, width);
            imgList->Add(img);
        }

        listCtrl->SetImageList(imgList, wxIMAGE_LIST_NORMAL);

        wxListItem li; // column 0
        li.SetId(0);
        li.SetWidth(width);

        listCtrl->InsertColumn(0, li);

        for (int i=0; i<imgList->GetImageCount(); i++) {
            listCtrl->InsertItem(0, i);
            listCtrl->SetItemImage(li, i);
        }
    };

    // load depthMap & texturePatterns from object files
    loadResourcesImagesObj(depthMapResources, maskImgs, imgListMask, lcMask);
    loadResourcesImagesObj(texturePatternsResource, textImgs, imgListTextures, lcTextures);

    lcTextures->SetItemState(0, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    lcMask->SetItemState(0, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
}

StereogramFrame::~StereogramFrame() {
    //(*Destroy(StereogramFrame)
    //*)
    delete imgListMask;
    delete imgListTextures;
}

wxImage StereogramFrame::generateStereoGram(int w, int h) {
    wxImage depthMap=maskImgs[maskIndex], texturePattern=textImgs[textIndex];

    float observationDistanceInches=14,
          eyeSeparationInches=2.5, maxDepthInches=12,
          minDepthInches=0;
    int horizontalPPI=72, verticalPPI=72;

    return StereoGram().generateTexturedSIRD(depthMap, texturePattern, w, h,
            observationDistanceInches, eyeSeparationInches, maxDepthInches,
            minDepthInches, horizontalPPI, verticalPPI );

}
void StereogramFrame::draw() {
    if (needsRepaint && maskIndex!=-1 && textIndex!=-1) {
        int w,h;
        uiBmp->GetSize(&w, &h);

        Timer t0;
        uiBmp->SetBitmap( generateStereoGram(w,h) );

        StatusBar1->SetStatusText(wxString::Format("lap:%ldms, size:%dx%d", t0.lap(), w,h));
        needsRepaint=false;
    }
}

void StereogramFrame::OnlcMaskItemSelect(wxListEvent& event) {
    maskIndex = event.GetIndex();
    needsRepaint=true;
    Refresh();
    event.Skip();
}

void StereogramFrame::OnlcTexturesItemSelect(wxListEvent& event) {
    textIndex = event.GetIndex();
    needsRepaint=true;
    Refresh();

    event.Skip();
}

void StereogramFrame::OnResize(wxSizeEvent& event) {
    needsRepaint=true;
    Refresh();

    event.Skip();
}

void StereogramFrame::OnPaint(wxPaintEvent& event) {
    draw();

    event.Skip();
}

void StereogramFrame::OnbtnSaveClick(wxCommandEvent& event) {
    if (maskIndex!=-1 && textIndex!=-1) {
        int w=scWidth->GetValue(), h=scHeight->GetValue();

        Timer t0;

        wxImage stgrm = generateStereoGram(w, h);

        auto lap = t0.lap();
        auto fileName = wxString::Format("Stereo%ld-%ld.png", textIndex, maskIndex);
        stgrm.SaveFile(fileName, wxBITMAP_TYPE_PNG);

        StatusBar1->SetStatusText(wxString::Format("file %s saved, lap:%ldms, size:%dx%d", fileName.c_str(), lap, w, h));
    }
}
