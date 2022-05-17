#include "wxGLRenderer.h"

BEGIN_EVENT_TABLE(wxGLRenderer, wxGLCanvas)
    EVT_PAINT(wxGLRenderer::Paintit)
    EVT_SIZE(wxGLRenderer::resized)
    EVT_MOTION(wxGLRenderer::mouseMoved)
    EVT_LEFT_DOWN(wxGLRenderer::mouseDown)
    EVT_LEFT_UP(wxGLRenderer::mouseReleased)
//    EVT_RIGHT_DOWN(wxGLCanvasPoly::rightClick)
//    EVT_LEAVE_WINDOW(wxGLCanvasPoly::mouseLeftWindow)
//    EVT_KEY_DOWN(wxGLCanvasPoly::keyPressed)
//    EVT_KEY_UP(wxGLCanvasPoly::keyReleased)
    EVT_MOUSEWHEEL(wxGLRenderer::mouseWheelMoved)
END_EVENT_TABLE()

void wxGLRenderer::resized(wxSizeEvent& evt)
{
    Refresh();
}

void wxGLRenderer::Paintit(wxPaintEvent& WXUNUSED(event))
{
    wxGLCanvas::SetCurrent(*m_context);
    Render();
}


void wxGLRenderer::Render()
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

    drawScene();

    glFlush();
    SwapBuffers();
}
