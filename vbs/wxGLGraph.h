#pragma once

#include "wxGLImage.h"
#include <functional>
#include "graphs.h"

using namespace std;


class wxGLGraph : public wxGLImage {

  private:
    Wave *wav=nullptr;
    GraphType grType=GRTYPE_SAMPLES;

  public:
    wxGLGraph(wxWindow *parent,
              wxWindowID id = wxID_ANY,
              const int *attribList = NULL,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0,
              const wxString& name = wxGLCanvasName
             ): wxGLImage(parent, id, attribList, pos, size, style, name) {}

    ~wxGLGraph() {}


    void SetWav(Wave*wav, GraphType grType=GRTYPE_SAMPLES) {
        this->wav=wav;
        this->grType=grType;
        Refresh();
    }

    void RenderGraph(wxMemoryDC&memDC) override {
        if(wav) {
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

        }
    }



};

