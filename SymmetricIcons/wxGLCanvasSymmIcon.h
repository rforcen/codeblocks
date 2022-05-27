// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.


#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/grid.h>
#include <vector>

typedef uint32_t u32;
using std::vector;

class wxGLCanvasSymmIcon: public wxGLCanvas {
  private:
    wxGLContext*	m_context=nullptr;

    bool textLoaded = false; // 1 texture
    GLuint textNum = 0;
    int w,h;

  public:
      // GLCanvas1 = new wxGLCanvas(this, ID_GLCANVAS1, GLCanvasAttributes_1, wxDefaultPosition, wxSize(330,281), 0, _T("ID_GLCANVAS1"));
    wxGLCanvasSymmIcon(wxWindow *parent,
                       wxWindowID id = wxID_ANY,
                       const int *attribList = NULL,
                       const wxPoint& pos = wxDefaultPosition,
                       const wxSize& size = wxDefaultSize,
                       long style = 0,
                       const wxString& name = wxGLCanvasName
                       ) : wxGLCanvas(parent, id, attribList, pos, size, style, name) {


        m_context = new wxGLContext(this);
        //SetBackgroundStyle(wxBG_STYLE_CUSTOM); // To avoid flashing on MSW
    }

    ~wxGLCanvasSymmIcon() {
        if (textLoaded) glDeleteTextures(1, &textNum);
        if (m_context) delete m_context;
    }

    wxSize getScaledSize(); // scale to hidpi
    void setBitmap(vector<u32>&image);

  protected:
    void Render();

    void scalePoint(wxPoint &p);
    void Paintit(wxPaintEvent& event);
    void resized(wxSizeEvent& evt);

    void setGeo();
    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    void panel(float l=1);
    void setTexture();
    void enableTextures();

  protected:
    DECLARE_EVENT_TABLE()
};
