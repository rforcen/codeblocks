#pragma once

#include <wx/wx.h>
#include <wx/sizer.h>

#include "../mandel/mandel.h"
#include "../mandel/Timer.h"

class wxImagePanel : public wxPanel {
  public:

    int iters = 200;
    wxPoint pstart, pend;
    bool isDragging=false, refresh=true;
    wxBitmap mandelBmp;
    u32 *image;
    wxPoint zp;
    int w,h;
    wxString msg;
    MandelEngine engine=f64;

    wxStatusBar*sb=nullptr;

    complex<double> _ccenter=complex<double>(0.5, 0.0), _crange=complex<double>(-2.0, 2.0);
    complex<double> ccenter=_ccenter, crange=_crange;

    wxBitmap genImage(int w, int h, uint32_t*img_buff) {
        vector <uint8_t>rgb_buff;
        char*charBuff=(char*)img_buff;

        for (auto i=0; i<w*h*4; i++) // remove alpha, keep only rgb
            if (i % 4 != 3) rgb_buff.push_back(charBuff[i]);

        wxImage img;
        img.SetData((unsigned char*)rgb_buff.data(), w, h, true);
        return wxBitmap(img, 32);
    }


  public:
    wxImagePanel( 	wxWindow *  	parent,
                    wxWindowID  	id = wxID_ANY,
                    const wxPoint &  	pos = wxDefaultPosition,
                    const wxSize &  	size = wxDefaultSize,
                    long  	style = wxTAB_TRAVERSAL,
                    const wxString &  	name = wxPanelNameStr
                ) : wxPanel(parent, id, pos, size, style, name) {}


    void setDefault() {
        ccenter=_ccenter;
        crange=_crange;
        iters=200;

        paintNow();
    }

    void setStatusBar(wxStatusBar*sb) {
        this->sb=sb;
    }

    void incIters(int by) {
        iters+=by;

        paintNow();
    }

    void setIters(int iters) {
        this->iters=iters;
        paintNow();
    }

    void Add(wxListBox*lb) {
        auto ms=new Mandelbrot<double>(ccenter, crange, iters);
        lb->Append(ms->toString(), (void*)ms);
    }
    void Del(wxListBox*lb) {
        auto sel = lb->GetSelection();
        if (sel!=-1) {
            delete (Mandelbrot<double>*)lb->GetClientData(sel);
            lb->Delete(sel);
        }
    }

    void Get(wxListBox*lb) {
        auto ms=(Mandelbrot<double>*)lb->GetClientData(lb->GetSelection());
        ms->restore(ccenter, crange, iters);
        paintNow();
    }

    void setEngine(MandelEngine engine) {
        this->engine = engine;
        paintNow();
    }

    void generateFractal(int w, int h);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    // some useful events

    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
    void resize(wxSizeEvent& event) {
        refresh=true;
        paintNow();

        event.Skip();
    }


    DECLARE_EVENT_TABLE()
};
