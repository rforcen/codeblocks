#pragma once

#include "wxGLImage.h"
#include <functional>
#include "Queens.h"

using namespace std;


class wxGLGraph : public wxGLImage {

  private:

    Queens*q=nullptr;

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

    void SetQueens(Queens*q) {
        this->q=q;
        Refresh();
    }

    void DrawBoard(wxMemoryDC&memDC) {
        memDC.SetBrush(*wxWHITE_BRUSH); // cls
        memDC.DrawRectangle(0,0,w,h);

        if (q) {
            int x0 = 0, y0 = 0;
            int nq = q->n;
            int sz, nw = w / nq, nh = h / nq;

            if (w > h) {
                sz = nh;
                x0 = (w - h) / 2;
                y0 = 0;
            } else {
                sz = nw;
                x0 = 0;
                y0 = (h - w) / 2;
            }
            int sz2=sz/2;

            bool ff = true;
            for (int i = 0; i < nq; i++) {
                for (int j = 0; j < nq; j++, ff=!ff) {
                    int xp = x0 + i * sz, yp = y0 + (nq - j - 1) * sz;

                    if (ff) {
                        memDC.SetBrush(wxBrush("#aaaaaa"));
                        memDC.DrawRectangle(xp, yp, sz, sz);
                    }

                    if (q->board[i] == j) {
                        memDC.SetBrush(*wxGREEN_BRUSH);
                        memDC.DrawCircle(xp+sz2, yp+sz2, sz2);
                        memDC.SetBrush(*wxRED_BRUSH);
                        memDC.DrawCircle(xp+sz2, yp+sz2, sz2/3);
                    }
                }
                if ((nq & 1) == 0)
                    ff = !ff;
            }

            memDC.SetBrush(*wxTRANSPARENT_BRUSH);
            memDC.SetPen(*wxBLACK_PEN);
            memDC.DrawRectangle(x0, y0, sz * nq - 1, sz * nq - 1);
        }
    }

    void RenderGraph(wxMemoryDC&memDC) override {
        DrawBoard(memDC);
    }
};

