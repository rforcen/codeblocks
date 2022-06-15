#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <functional>
#include <map>
#include "common.h"


typedef enum {GRTYPE_ERROR, GRTYPE_SAMPLES, GRTYPE_FFT, GRTYPE_RADIAL, GRTYPE_SPIRAL, GRTYPE_MUSICMATRIX, GRTYPE_SPECTROGRAM} GraphType;

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

            GetSize(&w, &h);

            wxBitmap bmp(w, h);
            wxMemoryDC memDC(bmp);
            memDC.SetPen(wxPen(*wxCYAN_PEN));

            const auto &simpleGraph = [&](int n, wxString title, std::function<float(int)> const &scaleY) {
                wxFont font(6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
                memDC.SetFont(font);
                memDC.SetTextForeground(*wxWHITE);

                memDC.DrawText(title, 5, 5);

                float x0=0, y0=scaleY(0), xinc=(float)w / n;

                for (auto i=0; i<n; i++) {
                    float x=xinc * i, y=scaleY(i);
                    memDC.DrawLine(x0,y0, x,y);
                    x0=x, y0=y;
                }
            };

            const auto &radialGraph = [&](int n, wxString title ) {
                wxFont font(8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
                memDC.SetFont(font);
                memDC.SetTextForeground(*wxWHITE);

                memDC.DrawText(title, 5, 5);

                int margin=25;
                int w0=w-margin, h0=h-margin, nvp=30;
                float x=0, y=0, off=margin, d=min(h0,w0), r=d/2, td=d-off, rm=max(w0,h0)/2, is=2.*M_PI/nvp,
                      x0=w0/2+x, 	 y0=h0/2+y, ss=4, bs=2*ss, ri=r-off, Max, Min;

                const auto &minmax = [&]() -> float {
                    Min=1e32, Max=-1e32;
                    for (int i=0; i<(int)wav->fft.size(); i++) {
                        Max=std::max(Max, wav->fft[i]);
                        Min=std::min(Min, wav->fft[i]);
                    }
                    return fabs(Max-Min);
                };

                const auto &drawFrame = [&]() {
                    wxFont font(6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
                    memDC.SetFont(font);

                    memDC.SetBrush(*wxTRANSPARENT_BRUSH);

                    memDC.DrawCircle(w0/2, h0/2, td/2); // 2 x concentric circles
                    td-=off;
                    memDC.DrawCircle(w0/2, h0/2, td/2);

                    for (int i=0; i<nvp; i++) {
                        float iis=sinf(i*is), iic=cosf(i*is),
                              xci= x0+ri*iis, yci= y0-ri*iic,
                              xco= x0+r *iis, yco= y0-r*iic;
                        memDC.SetPen(wxPen(*wxYELLOW_PEN));
                        memDC.DrawLine(xci,yci, xco,yco); // big tics

                        auto s=wxString::Format("%.0f", fft::Index2Freq(wav->nFFT2 * i / nvp, wav->sampleRate, wav->nFFT2));

                        memDC.SetTextForeground(*wxWHITE);
                        memDC.DrawText(s, xco,yco);

                        for (int j=1; j<10; j++) {
                            iis=i*is+j*is/10.;
                            xci=x0+ri*sinf(iis);
                            yci=y0-ri*cosf(iis);
                            float c=(j%2) ? ss : bs;

                            xco= x0+(ri+c)*sinf(iis);
                            yco= y0-(ri+c)*cosf(iis);
                            memDC.DrawLine(xci,yci, xco,yco); // small tics
                        }
                    }
                };


                const auto &drawRadial = [&] () {
                    vector<wxPoint>cont;
                    auto diff = minmax();

                    float r13=r/3., r23=2.*r/3.;
                    nvp=(int)wav->fft.size();
                    is=2.*M_PI/nvp;
                    r-=off;


                    for (int i=0; i<nvp; i++) {
                        float incr=r*(wav->fft[i]/Max), ri=r*(1-(wav->fft[i]/Max)),
                              s=sinf(i*is), c=cosf(i*is),
                              xci=x0 + r  * s,  yci=y0 - r  * c,
                              xri=x0 + ri * s,  yri=y0 - ri * c,
                              xri1, yri1, xt, yt;

                        incr=r*((wav->fft[i]-Min)/diff);
                        ri=r*(1-(wav->fft[i]-Min)/diff);

                        xt=xci, yt=yci;  // radial from circumference perimeter
                        memDC.SetPen(wxPen(*wxRED_PEN));

                        if (cont.size()==0) cont.push_back({(int)xt,(int)yt});

                        if (incr<=r13) {
                            memDC.DrawLine(xt, yt, xri, yri);
                            cont.push_back({xri,yri});
                        } else {
                            xri1=x0 + (r23) * s; // line 1/3 blue
                            yri1=y0 - (r23) * c;
                            memDC.DrawLine(xt, yt, (int)xri1, (int)yri1);
                            memDC.SetPen(wxPen(*wxYELLOW_PEN));

                            if (incr<=r23) {  //  line 2/3
                                xri1+=(1-(incr-r13)) * s;
                                yri1-=(1-(incr-r13)) * c;
                                memDC.DrawLine(xt, yt, (int)xri1, (int)yri1);
                                cont.push_back({(int)xri1,(int)yri1});
                            } else {                      // line > 2/3
                                xri1+= (1-r13) * s;
                                yri1-= (1-r13) * c;
                                memDC.DrawLine(xt, yt, (int)xri1, (int)yri1);
                                memDC.SetPen(wxPen(*wxCYAN_PEN));
                                xri1+=(1-(incr-r23)) * s;
                                yri1-=(1-(incr-r23)) * c;
                                memDC.DrawLine(xt, yt, xri1, yri1);
                                cont.push_back({xri1,yri1});
                            }
                        }
                    }
                    // frame values
                    memDC.SetPen(wxPen(*wxCYAN_PEN));
                    memDC.DrawLines(cont.size(), cont.data(), 0, 0);
                };

                drawFrame();
                drawRadial();
            };


            switch (grType) {
            case GRTYPE_SAMPLES:
                simpleGraph(wav->GetNSamples(),
                            wxString::Format("%d channels, %d sample rate, %ld samples, %.1f secs", wav->GetChannels(), wav->GetSampleRate(), wav->GetNSamples(), wav->GetSecs()),
                            [=](int i) -> float { return h *( (1 + wav->GetSample(i) * 0.9) / 2); });
                break;

            case GRTYPE_FFT:
                simpleGraph(wav->fft.size(),
                            wxString::Format("max freq. %.1fhz",wav->maxFreq),
                            [=](int i) -> float { return h * (1 - wav->fft[i] * 0.9);});
                break;

            case GRTYPE_RADIAL:
                radialGraph(wav->fft.size(), wxString::Format("max freq. %.1fhz",wav->maxFreq));
                break;

            case GRTYPE_SPIRAL: {

                memDC.SetBrush(*wxTRANSPARENT_BRUSH);
                memDC.SetPen(wxPen(*wxCYAN_PEN));

                float w2=w/2, h2=h/2, inc=0.2; //spirals
                int i;
                wxPoint centers[]= {wxPoint (w2, h2), wxPoint(w2, h2*(1-inc/2))}, startp, endp;
                vector<float>rad;

                const auto &addRad = [&](int cix) {
                    rad.push_back(fabs((startp-centers[cix]).y));
                };
                const auto &drawMidCirc0 = [&](int i) {
                    memDC.DrawArc(startp=wxPoint(w2, h2 * (2 - i*inc)), endp=wxPoint(w2, h2 * inc*i), centers[0]);
                    addRad(0);
                };
                const auto &drawMidCirc1 = [&](int i) {
                    memDC.DrawArc(startp=wxPoint(w2, h2 * inc*i), endp=wxPoint(w2, h2 * (2 - (i+1)*inc)), centers[1]);
                    addRad(1);
                };

                int Noct=4;
                for (i=1; i<=Noct; i++) {
                    drawMidCirc0(i);
                    drawMidCirc1(i);
                }
                //drawMidCirc0(i);

                // plot values
                float *v=wav->fft.data(); // (float*)wav->musicMatrix;
                int n=wav->fft.size(); // 60;
                vector<vector<wxPoint>> cont;
                int nn=n/(Noct*2); // Noct octaves

                memDC.SetBrush(*wxTRANSPARENT_BRUSH);
                memDC.SetPen(wxPen(*wxYELLOW_PEN));

                for (i=0; i<n; i++) {
                    int nOct=i/nn, np=i % nn;
                    wxPoint c = centers[nOct & 1];
                    float r=rad[nOct], sgn = (nOct & 1) ? -1:+1;
                    wxPoint p[2];

                    for (int j=0; j<2; j++) {
                        p[j].x = c.x + sgn * r * sin(M_PI * np / nn);
                        p[j].y = c.y + r * cos(M_PI * np / nn);
                        r -= 0.9 * h2 * inc * v[i];
                    }
                    memDC.DrawLine(p[0], p[1]);
                    if (cont.size()<=nOct)  cont.push_back(vector<wxPoint>());
                    cont[nOct].push_back(p[1]);
                }
                // frame values
                memDC.SetPen(wxPen(*wxRED_PEN));
                for (auto c:cont)
                    if(c.size()>1) memDC.DrawLines(c.size(), c.data(), 1, 1);
            }
            break;

            case GRTYPE_MUSICMATRIX: {

                wxFont font(7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
                memDC.SetFont(font);
                memDC.SetTextForeground(*wxWHITE);


                float xw=w/60.;

                for (int _oct=-2, ix=0; _oct<=+2; _oct++) {

                    memDC.SetPen(wxPen(*wxWHITE_PEN));
                    memDC.DrawLine(ix*xw, 0, ix*xw, h);

                    memDC.DrawText(wxString::Format("oct %d (%.0fhz)",_oct, MusicFreq::NoteOct2Freq(_oct)), 2+ix*xw, 0);

                    int oct=_oct+2, x0=0;

                    for (int note=0 ; note<12; note++, ix++) {

                        memDC.SetPen(wxPen(*wxCYAN_PEN));
                        memDC.SetBrush(*wxRED_BRUSH);

                        float y=(h*(1-wav->musicMatrix[oct][note]*0.9)), x=ix*xw;
                        memDC.DrawRectangle(x0, y, xw, h-y);
                        x0=x;
                    }
                }
            }
            break;

            case GRTYPE_SPECTROGRAM: {
                RGB imgCol[h][w];
                memset(imgCol, 0, sizeof(imgCol));

                int ns=wav->GetNSamples() / w, nFFT=log2f(ns), nFFT2=1<<nFFT;
                vector<float>fft(nFFT2);
                vector<vector<float>>ffts;
                float maxfft=-1e32;
                ColorIndex colIndex(64, 0x0000ff, 0xff0000);

                for (auto c=0; c<w; c++) {
                    for (int i=0; i<(int)fft.size(); i++) fft[i]=0;

                    for (int i=0; i<(int)fft.size(); i++) {
                        int ix=ns * c + i;
                        fft[i]=(ix < (int)wav->GetNSamples()) ? wav->GetSample(ix) : 0;
                    }
                    fft::fft(fft.data(), nFFT);
                    ffts.push_back(fft);

                    for (auto f:fft) maxfft=max(maxfft, f);
                }

                for (auto &fft:ffts) for (auto &f:fft) f/=maxfft;

                float inc=(float)nFFT2/h;
                for (auto c=0; c<w; c++) {
                    auto &fft=ffts[c];
                    for (int r=0; r<h; r++)
                        imgCol[r][c] = fft[r*inc]>0.1 ? RGB(colIndex.getColor(fft[r])) : 0;
                }

                wxImage img(w, h, (uint8_t*)imgCol, true);
                memDC.DrawBitmap(img, 0,0);
            }
            break;
            }

            wxPaintDC dc(this); // draw memDC into dc
            dc.Blit(0, 0, w, h, &memDC, 0, 0);
        }
    }

  private:
    Wave *wav=nullptr;
    GraphType grType=GRTYPE_SAMPLES;
    int w,h;
  protected:

    DECLARE_EVENT_TABLE();
};
