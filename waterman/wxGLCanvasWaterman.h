// NOTE: To run, it is recommended not to be in Compiz or Beryl, they have shown some instability.

#include <wx/wx.h>
#include <wx/glcanvas.h>


#ifdef __WXMAC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef WIN32
#include <unistd.h> // FIXME: ¿This work/necessary in Windows?
//Not necessary, but if it was, it needs to be replaced by process.h AND io.h
#endif

#include "engine/Waterman.h"

class wxGLCanvasWaterman: public wxGLCanvas
{


    wxGLContext*	m_context=nullptr;

    float anglex=0, angley=0, zoom=-3.5;
    int lastx=0, lasty=0;

    bool moving = false;

    WatermanPoly waterman;
    QuickHull3D hull;
public:
    vector<double>vertices;
    vector<vector<int>> faces;
    vector<Point3d>colors;

public:
    wxGLCanvasWaterman(wxWindow *parent,
                       wxWindowID id = wxID_ANY,
                       const int *attribList = NULL,
                       const wxPoint& pos = wxDefaultPosition,
                       const wxSize& size = wxDefaultSize,
                       long style = 0,
                       const wxString& name = wxGLCanvasName,
                       const wxPalette& palette = wxNullPalette) : wxGLCanvas(parent, id, attribList, pos, size, style, name, palette)
    {
        m_context = new wxGLContext(this);
    }

    ~wxGLCanvasWaterman()
    {
        if (m_context) delete m_context;
    }

    void Render();
    void drawPoly();
    void drawLines();

    void savePLY() {    }
    void saveCTM() {    }


    void Paintit(wxPaintEvent& event);
    void resized(wxSizeEvent& evt);

    void setWaterman(double radius)
    {
        QuickHull3D hull(waterman.genHull(radius));

        faces=hull.getFaces();
        vertices=hull.getScaledVertex();

        recolor();
    }

    void recolor()
    {
        colors=vector<Point3d>(100);
        for (auto &face : faces)
            colors[face.size()]=Point3d((double)rand()/RAND_MAX, (double)rand()/RAND_MAX, (double)rand()/RAND_MAX);
        Refresh();
    }

    void setGeo()
    {
        auto sc=GetContentScaleFactor();

        int w=GetSize().x, h=GetSize().y;

        glViewport(0,0, w*sc, h*sc);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        perspectiveGL(45, (float)w / h, 0.1, 100);
        glMatrixMode(GL_MODELVIEW);
    }

    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
    {
        GLdouble fH = tan(fovY / 360. * M_PI) * zNear, fW = fH * aspect;
        glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    }

    void sceneInit()    // works nice for golden solid colors (requires normals)
    {
        float lmodel_ambient[] = {0, 0, 0, 0};
        float lmodel_twoside[] = {GL_FALSE};
        float light0_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
        float light0_diffuse[] = {1.0f, 1.0f, 1.0f, 0.0f};
        float light0_position[] = {1, 0.5, 1, 0};
        float light1_position[] = {-1, 0.5, -1, 0};
        float light0_specular[] = {1, 1, 1, 0};
        float bevel_mat_ambient[] = {0, 0, 0, 1};
        float bevel_mat_shininess[] = {40};
        float bevel_mat_specular[] = {1, 1, 1, 0};
        float bevel_mat_diffuse[] = {1, 0, 0, 0};

//  glClearColor(float(color.redF()), float(color.greenF()), float(color.blueF()),               1);

        glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
        glEnable(GL_LIGHT0);

        glLightfv(GL_LIGHT1, GL_AMBIENT, light0_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light0_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
        glEnable(GL_LIGHT1);

        glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
        glEnable(GL_LIGHTING);

        glMaterialfv(GL_FRONT, GL_AMBIENT, bevel_mat_ambient);
        glMaterialfv(GL_FRONT, GL_SHININESS, bevel_mat_shininess);
        glMaterialfv(GL_FRONT, GL_SPECULAR, bevel_mat_specular);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, bevel_mat_diffuse);

        glEnable(GL_COLOR_MATERIAL);
        glShadeModel(GL_SMOOTH);

        glEnable(GL_LINE_SMOOTH);

        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glClearDepth(1.0); // Set background depth to farthest
        glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
        glDepthFunc(GL_LEQUAL); // Set the type of depth-test
        glShadeModel(GL_SMOOTH); // Enable smooth shading
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //  Nice perspective corrections
    }

    // events
    void mouseMoved(wxMouseEvent& event)
    {
        if (moving)
        {
            int x,y;
            event.GetPosition(&x, &y);

            anglex += (x-lastx) / 2.;
            angley += (y-lasty) / 2.;

            lastx=x;
            lasty=y;

            Refresh();
        }
    }
    void mouseDown(wxMouseEvent& event)
    {
        moving=true;
    }
    void mouseWheelMoved(wxMouseEvent& event)
    {
        zoom+=event.GetWheelRotation() / 1200.;
        Refresh();
    }
    void mouseReleased(wxMouseEvent& event)
    {
        moving=false;
    }
    void rightClick(wxMouseEvent& event) {}
    void mouseLeftWindow(wxMouseEvent& event) {}
    void keyPressed(wxKeyEvent& event) {}
    void keyReleased(wxKeyEvent& event) {}

protected:
    DECLARE_EVENT_TABLE()
};
