#pragma once

#include "common.h"

class Graphs {
  public:
    wxMemoryDC*memDC;
    int w,h, w0, h0;

    explicit Graphs(wxMemoryDC*memDC, int w, int h) : memDC(memDC), w(w), h(h), w0(w/2), h0(h/2) {}

    // font aux
    wxFont createFont(int sz) {
        return wxFont(sz, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    }
    wxFont smallerFont() {
        return createFont(8);
    }
    wxFont smallFont() {
        return createFont(12);
    }
    wxFont normalFont() {
        return createFont(15);
    }

    // line graph
    void lineGraph(int n, wxString title, std::function<float(int)> const &scaleY) {

        memDC->SetFont(smallFont());
        memDC->SetTextForeground(*wxWHITE);

        memDC->DrawText(title, 5, 5);

        if (w*5 > n) { // small plot
            float x0=0, y0=scaleY(0), xinc=(float)w / n;

            for (auto i=0; i<n; i++) {
                float x=xinc * i, y=scaleY(i);
                memDC->DrawLine(x0,y0, x,y);
                x0=x, y0=y;
            }
        } else { // large graph plot min,max of section n/w
            float min=h, max=-h;
            int nw = n / w;

            for (int i=0, x=0; i<n; i++) {
                if (i>0 && i % nw == 0) {
                    memDC->DrawLine(x, min, x, max);
                    if (i<n-1)
                        memDC->DrawLine(x, scaleY(i), x+1, scaleY(i+1));

                    min=h;
                    max=-h;
                    x++;
                }
                auto y=scaleY(i);
                min=std::min(min, y);
                max=std::max(max, y);
            }
        }
    }


    void radialGraph (Wave*wav, wxString title) {

        memDC->SetFont(smallFont());
        memDC->SetTextForeground(*wxWHITE);

        memDC->DrawText(title, 5, 5);

        int margin=25;
        int w0=w-margin, h0=h-margin, nvp=30;
        float x=0, y=0, off=margin, d=min(h0,w0), r=d/2, td=d-off, is=2.*M_PI/nvp,
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
            memDC->SetFont(smallFont());

            memDC->SetBrush(*wxTRANSPARENT_BRUSH);

            memDC->DrawCircle(w0/2, h0/2, td/2); // 2 x concentric circles
            td-=off;
            memDC->DrawCircle(w0/2, h0/2, td/2);

            for (int i=0; i<nvp; i++) {
                float iis=sinf(i*is), iic=cosf(i*is),
                      xci= x0+ri*iis, yci= y0-ri*iic,
                      xco= x0+r *iis, yco= y0-r*iic;
                memDC->SetPen(wxPen(*wxYELLOW_PEN));
                memDC->DrawLine(xci,yci, xco,yco); // big tics

                auto s=wxString::Format("%.0f", fft::Index2Freq(wav->nFFT2 * i / nvp, wav->sampleRate, wav->nFFT2));

                memDC->SetTextForeground(*wxWHITE);
                memDC->DrawText(s, xco,yco);

                for (int j=1; j<10; j++) {
                    iis=i*is+j*is/10.;
                    xci=x0+ri*sinf(iis);
                    yci=y0-ri*cosf(iis);
                    float c=(j%2) ? ss : bs;

                    xco= x0+(ri+c)*sinf(iis);
                    yco= y0-(ri+c)*cosf(iis);
                    memDC->DrawLine(xci,yci, xco,yco); // small tics
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
                memDC->SetPen(wxPen(*wxRED_PEN));

                if (cont.size()==0) cont.push_back({(int)xt,(int)yt});

                if (incr<=r13) {
                    memDC->DrawLine(xt, yt, xri, yri);
                    cont.push_back({(int)xri,(int)yri});
                } else {
                    xri1=x0 + (r23) * s; // line 1/3 blue
                    yri1=y0 - (r23) * c;
                    memDC->DrawLine(xt, yt, (int)xri1, (int)yri1);
                    memDC->SetPen(wxPen(*wxYELLOW_PEN));

                    if (incr<=r23) {  //  line 2/3
                        xri1+=(1-(incr-r13)) * s;
                        yri1-=(1-(incr-r13)) * c;
                        memDC->DrawLine(xt, yt, (int)xri1, (int)yri1);
                        cont.push_back({(int)xri1,(int)yri1});
                    } else {                      // line > 2/3
                        xri1+= (1-r13) * s;
                        yri1-= (1-r13) * c;
                        memDC->DrawLine(xt, yt, (int)xri1, (int)yri1);
                        memDC->SetPen(wxPen(*wxCYAN_PEN));
                        xri1+=(1-(incr-r23)) * s;
                        yri1-=(1-(incr-r23)) * c;
                        memDC->DrawLine(xt, yt, xri1, yri1);
                        cont.push_back({(int)xri1, (int)yri1});
                    }
                }
            }
            // frame wav->fft
            memDC->SetPen(wxPen(*wxCYAN_PEN));
            memDC->DrawLines(cont.size(), cont.data(), 0, 0);
        };

        drawFrame();
        drawRadial();
    }

    void spiralGraph(Wave*wav) {

        memDC->SetBrush(*wxTRANSPARENT_BRUSH);
        memDC->SetPen(wxPen(*wxCYAN_PEN));

        float inc=0.2; //spirals
        int i;
        wxPoint centers[]= {wxPoint (w0, h0), wxPoint(w0, h0*(1-inc/2))}, startp, endp;
        vector<float>rad;

        const auto &addRad = [&](int cix) {
            rad.push_back(fabs((startp-centers[cix]).y));
        };
        const auto &drawMidCirc0 = [&](int i) {
            memDC->DrawArc(startp=wxPoint(w0, h0 * (2 - i*inc)), endp=wxPoint(w0, h0 * inc*i), centers[0]);
            addRad(0);
        };
        const auto &drawMidCirc1 = [&](int i) {
            memDC->DrawArc(startp=wxPoint(w0, h0 * inc * i), endp=wxPoint(w0, h0 * (2 - (i+1) * inc)), centers[1]);
            addRad(1);
        };

        int Noct=4;
        for (i=1; i<=Noct; i++) {
            drawMidCirc0(i);
            drawMidCirc1(i);
        }

        // plot values
        float *v=wav->fft.data();
        int n=wav->fft.size();
        vector<vector<wxPoint>> cont;
        int nn=n/(Noct*2); // Noct octaves

        // lines

        memDC->SetFont(smallerFont());
        memDC->SetTextForeground(*wxWHITE);

        // notes lines
        memDC->SetPen(wxPen(*wxBLUE_PEN));
        wxPoint c(w0, h0);
        wxCoord Rad=std::min(w0, h0)-20;

        for (int n=0; n<12; n++) {
            float alpha = -4*M_PI * MusicFreq::baseC0 / MusicFreq::NoteOct2Freq(0,n);
            wxPoint t(w0+Rad*sinf(alpha), h0+Rad*cosf(alpha));
            memDC->DrawLine(c, t);
            memDC->DrawText(MusicFreq::NoteName(n), t);
        }

        memDC->SetBrush(*wxTRANSPARENT_BRUSH);
        memDC->SetPen(wxPen(*wxYELLOW_PEN));
        for (i=0; i<n; i++) {
            int nOct=i/nn, np=i % nn;
            wxPoint c = centers[nOct & 1];
            float r=rad[nOct], sgn = (nOct & 1) ? -1:+1;
            wxPoint p[2];

            for (int j=0; j<2; j++) {
                p[j].x = c.x + sgn * r * sin(M_PI * np / nn);
                p[j].y = c.y + r * cos(M_PI * np / nn);
                r -= 0.9 * h0 * inc * v[i];
            }
            memDC->DrawLine(p[0], p[1]);
            if ((int)cont.size()<=nOct)  cont.push_back(vector<wxPoint>());
            cont[nOct].push_back(p[1]);
        }
        // frame values
        memDC->SetPen(wxPen(*wxYELLOW_PEN));
        for (auto c:cont)
            if(c.size()>1) memDC->DrawLines(c.size(), c.data(), 1, 1);
    }

    void musicMatrixGraph(Wave*wav) {


        memDC->SetFont(smallFont());
        memDC->SetTextForeground(*wxWHITE);


        float xw=w/60.;

        for (int _oct=-2, ix=0; _oct<=+2; _oct++) {

            memDC->SetPen(wxPen(*wxWHITE_PEN));
            memDC->DrawLine(ix*xw, 0, ix*xw, h);

            memDC->DrawText(wxString::Format("oct %d (%.0fhz)",_oct, MusicFreq::NoteOct2Freq(_oct)), 2+ix*xw, 0);

            int oct=_oct+2, x0=0;

            for (int note=0 ; note<12; note++, ix++) {

                memDC->SetPen(wxPen(*wxCYAN_PEN));
                memDC->SetBrush(*wxRED_BRUSH);

                float y=(h*(1-wav->musicMatrix[oct][note]*0.9)), x=ix*xw;
                memDC->DrawRectangle(x0, y, xw, h-y);
                x0=x;
            }
        }
    }

    void spectrogramGraph(Wave*wav) {
        RGB imgCol[h][w];
        memset(imgCol, 0, sizeof(imgCol));

        int ns=wav->GetNSamples() / w, nFFT=log2f(ns), nFFT2=1<<nFFT;
        vector<float>fft(nFFT2+2);
        vector<vector<float>>ffts;
        float maxfft=-1e32;
        ColorIndex colIndex(64, 0x0000ff, 0xff0000);

        for (auto c=0; c<w; c++) {
            for (int i=0; i<nFFT2; i++) fft[i]=0;

            for (int i=0; i<nFFT2; i++) {
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
        memDC->DrawBitmap(img, 0,0);
    }

    void concentricGraph(Wave*wav) {

        wxPoint center(w0, h0);
        wxCoord Rad=std::min(w0, h0)-20, rad=Rad;
        int inc=rad/5;
        memDC->SetBrush(*wxTRANSPARENT_BRUSH);

        memDC->SetFont(smallFont());
        memDC->SetTextForeground(*wxWHITE);

        vector<vector<wxPoint>>cont;
        for (int o=0, oct=2; o<5; o++, rad-=inc, oct--) {

            memDC->DrawText(wxString::Format("oct %d (%.0fhz)", oct, MusicFreq::NoteOct2Freq(oct)), w0+10, h0+rad);
            memDC->DrawCircle(center, rad);

            int from=wav->Freq2Index( MusicFreq::NoteOct2Freq(oct, 0) ), to=wav->Freq2Index( MusicFreq::NoteOct2Freq(oct+1, 0) ), n=to-from;
            float aInc=2*M_PI/n;

            cont.push_back(vector<wxPoint>());
            wxPoint frst;
            for (int i=from; i<to; i++) {
                wxPoint f(w0 + rad * sinf(aInc * i), h0 + rad * cosf(aInc *i)),
                        t(w0 + (rad - inc * wav->fft[i]) * sinf(aInc * i), h0 + (rad - inc * wav->fft[i]) * cosf(aInc *i));
                memDC->DrawLine(f, t);
                if(i==from) frst=t;
                cont[o].push_back(t);
            }
            cont[o].push_back(frst);
        }

        memDC->SetPen(wxPen(*wxYELLOW_PEN)); // contourn
        for (auto c:cont)
            if(c.size()>1) memDC->DrawLines(c.size(), c.data(), 1, 1);

        // notes lines
        memDC->SetPen(wxPen(*wxBLUE_PEN));
        wxPoint c(w0, h0);

        for (int n=0; n<12; n++) {
            float alpha = -4*M_PI * MusicFreq::baseC0 / MusicFreq::NoteOct2Freq(0,n);
            wxPoint t(w0+Rad*sinf(alpha), h0+Rad*cosf(alpha));
            memDC->DrawLine(c, t);
            memDC->DrawText(MusicFreq::NoteName(n), t);
        }
    }


};
