#include "wxGLCanvasWaterman.h"

BEGIN_EVENT_TABLE(wxGLCanvasWaterman, wxGLCanvas)
    EVT_PAINT(wxGLCanvasWaterman::Paintit)
    EVT_SIZE(wxGLCanvasWaterman::resized)
    EVT_MOTION(wxGLCanvasWaterman::mouseMoved)
    EVT_LEFT_DOWN(wxGLCanvasWaterman::mouseDown)
    EVT_LEFT_UP(wxGLCanvasWaterman::mouseReleased)
//    EVT_RIGHT_DOWN(wxGLCanvasPoly::rightClick)
//    EVT_LEAVE_WINDOW(wxGLCanvasPoly::mouseLeftWindow)
//    EVT_KEY_DOWN(wxGLCanvasPoly::keyPressed)
//    EVT_KEY_UP(wxGLCanvasPoly::keyReleased)
    EVT_MOUSEWHEEL(wxGLCanvasWaterman::mouseWheelMoved)
END_EVENT_TABLE()

void wxGLCanvasWaterman::resized(wxSizeEvent& evt)
{
    Refresh();
}

void wxGLCanvasWaterman::Paintit(wxPaintEvent& WXUNUSED(event))
{
    wxGLCanvas::SetCurrent(*m_context);
    Render();
}

void wxGLCanvasWaterman::drawLines()
{
    for (auto &face : faces)
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1,1,1);

        for (auto ix : face)
            glVertex3dv((GLdouble *)&vertices[size_t(ix*3)]);
        glEnd();
    }
}

void wxGLCanvasWaterman::drawPoly()
{
    for (auto &face : faces)
    {
        glBegin(GL_POLYGON);

        glColor3dv((GLdouble *)(&colors[face.size()]));

        for (auto ix : face)
            glVertex3dv((GLdouble *)(&vertices[size_t(ix*3)]));

        glEnd();

    }

}

void wxGLCanvasWaterman::Render()
{

    if(!IsShown()) return;


    {
        setGeo();
    }

    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black and opaque
    glClearDepth(1.0); // Set background depth to farthest
    glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL); // Set the type of depth-test
    glShadeModel(GL_SMOOTH); // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClearColor(0,0,0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity(); // Reset the model-view matrix

    glTranslatef(0, 0, zoom); // zoom

    glRotatef(-anglex, 0, 1, 0);
    glRotatef(angley, 1, 0, 0);

    // draw waterman
    {
        drawPoly();
        drawLines();
    }


    glFlush();
    SwapBuffers();
}
