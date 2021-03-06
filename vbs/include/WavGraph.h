#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/panel.h>

#include <functional>
#include <map>

#include "common.h"
#include "graphs.h"


class WavGraph : public wxPanel {
  public:
    WavGraph(wxWindow *parent,
             wxWindowID id = wxID_ANY,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style=wxTB_DEFAULT_STYLE,
             const wxString& name = "");
    virtual ~WavGraph();

    void SetWav(Wave*wav, GraphType grType=GRTYPE_SAMPLES) {
        this->wav=wav;
        this->grType=grType;
        Refresh();
    }

  protected:

    void OnPaint(wxPaintEvent&) {
        if(wav) {
            int w,h;

            GetSize(&w, &h);

            wxBitmap bmp(w, h);
            wxMemoryDC memDC(bmp);

            memDC.SetPen(wxPen(*wxCYAN_PEN));
            Graphs grs(&memDC, w,h);

            switch (grType) {
            case GRTYPE_ERROR:
                break;

            case GRTYPE_SAMPLES:
                grs.lineGraph(wav->GetNSamples(),
                              wxString::Format("%d channels, %d sample rate, %ld samples, %.1f secs", wav->GetChannels(), wav->GetSampleRate(), wav->GetNSamples(), wav->GetSecs()),
                              [=](int i) -> float { return h *( (1 + wav->GetSample(i) * 0.9) / 2); });
                break;

            case GRTYPE_FFT: {
                auto name = GetName();
                if (name=="ID_FFT_GRAPH0")
                    grs.lineGraph(wav->fft.size()/3,
                                  wxString::Format("max freq. %.1fhz",wav->maxFreq),
                                  [=](int i) -> float { return h * (1 - wav->fft[i] * 0.9);});
                else if (name=="ID_FFT_GRAPH1")
                    grs.lineGraph(wav->fft.size()/3,
                                  "", [=](int i) -> float { return h * (1 - wav->fft[i+wav->fft.size()/3] * 0.9);});
                else if (name=="ID_FFT_GRAPH2")
                    grs.lineGraph(wav->fft.size()/3,
                                  "", [=](int i) -> float { return h * (1 - wav->fft[i+2*wav->fft.size()/3] * 0.9);});

            }
            break;

            case GRTYPE_RADIAL:
                grs.radialGraph(wav, wxString::Format("max freq. %.1fhz",wav->maxFreq));
                break;

            case GRTYPE_SPIRAL:
                grs.spiralGraph(wav);
                break;

            case GRTYPE_MUSICMATRIX:
                grs.musicMatrixGraph(wav);
                break;

            case GRTYPE_SPECTROGRAM:
                grs.spectrogramGraph(wav);
                break;

            case GRTYPE_CONCENTRIC:
                grs.concentricGraph(wav);
                break;
            }

            wxPaintDC dc(this); // draw memDC into dc
            dc.Blit(0, 0, w, h, &memDC, 0, 0);
        }
    }

  private:
    Wave *wav=nullptr;
    GraphType grType=GRTYPE_SAMPLES;


  protected:

    DECLARE_EVENT_TABLE();
};
