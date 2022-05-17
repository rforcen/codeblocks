// renderPoly.h
#pragma once

#include "wxGLRenderer.h"
#include "polygonizerWrap.h"

using std::vector;

class RenderPoly : public wxGLRenderer
{
public:
    RenderPoly(wxWindow *parent,
               wxWindowID id = wxID_ANY,
               const int *attribList = NULL,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxString& name = wxGLCanvasName,
               const wxPalette& palette = wxNullPalette) :
        wxGLRenderer(parent, id, attribList, pos, size, style, name, palette) {
        setZoom(-4);
        }

    ~RenderPoly()
    {
    }

    Polygonizer poly;

    void setFunc(int nfunc, float bounds, int resol)
    {
        poly.Create(bounds, resol, nfunc);

        Refresh();
    }

    void saveCTM() {
        poly.saveCTM("implsurf.ctm");
    }

    void drawScene()
    {
        sceneInit();

        glColor3f(0.5, 0.5, 0);
        for (auto t:poly.trigs)
        {
            glBegin(GL_TRIANGLES);
            Vertex vs[3]= {poly.vertexes[t.i1], poly.vertexes[t.i2], poly.vertexes[t.i3]};
            for (int i=0; i<3; i++)
            {
                glNormal3fv((GLfloat*)&vs[i].norm);
                glColor3fv((GLfloat*)&vs[i].color);
                glVertex3fv((GLfloat*)&vs[i].pos);
            }
            glEnd();
        }
    }

};
