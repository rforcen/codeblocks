// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.
#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/grid.h>
#include <vector>

using namespace std;

class wxGLImage: public wxGLCanvas {
  private:
    wxGLContext*	m_context=nullptr;

    bool textLoaded = false; // 1 texture
    GLuint textNum = 0;

    wxBitmap drawBmp;
    bool imDrawing=false;
    vector<uint32_t>image;
    GLdouble fH, fW;

    class RGB {
      public:
        uint8_t b,g,r;
        inline uint32_t toU32() {
            uint8_t vu8[4] = {b,g,r, 0xff};
            return *((uint32_t*)vu8);
        }
    };

  public:
    int w,h;

  public:
    wxGLImage(wxWindow *parent,
              wxWindowID id = wxID_ANY,
              const int *attribList = NULL,
              const wxPoint& pos = wxDefaultPosition,
              const wxSize& size = wxDefaultSize,
              long style = 0,
              const wxString& name = wxGLCanvasName
             ) : wxGLCanvas(parent, id, attribList, pos, size, style, name) {


        m_context = new wxGLContext(this);
        SetBackgroundStyle(wxBG_STYLE_CUSTOM); // To avoid flashing on MSW
    }

    ~wxGLImage() {
        if (textLoaded) glDeleteTextures(1, &textNum);
        if (m_context) delete m_context;
    }

    virtual void RenderGraph(wxMemoryDC&memDC)=0;


  protected:
    void SetTexture();
    void GenerateImage();

    void DrawGraph();

    wxSize getScaledSize(); // scale to hidpi
    void Render();

    void scalePoint(wxPoint &p);
    void OnPaint(wxPaintEvent& event);
    void OnResize(wxSizeEvent& evt);

    void setGeo();
    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    void panel(float l=1);
    void setTexture();
    void enableTextures();

  protected:
    DECLARE_EVENT_TABLE()
};
