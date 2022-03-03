#include "wxGLCanvasSH.h"

BEGIN_EVENT_TABLE(wxGLCanvasSH, wxGLCanvas)
    EVT_PAINT(wxGLCanvasSH::Paintit)
    EVT_SIZE(wxGLCanvasSH::resized)
    EVT_MOTION(wxGLCanvasSH::mouseMoved)
    EVT_LEFT_DOWN(wxGLCanvasSH::mouseDown)
    EVT_LEFT_UP(wxGLCanvasSH::mouseReleased)
//    EVT_RIGHT_DOWN(wxGLCanvasSH::rightClick)
//    EVT_LEAVE_WINDOW(wxGLCanvasSH::mouseLeftWindow)
//    EVT_KEY_DOWN(wxGLCanvasSH::keyPressed)
//    EVT_KEY_UP(wxGLCanvasSH::keyReleased)
    EVT_MOUSEWHEEL(wxGLCanvasSH::mouseWheelMoved)
END_EVENT_TABLE()

void wxGLCanvasSH::resized(wxSizeEvent& evt) {
    Refresh();
}

void wxGLCanvasSH::Paintit(wxPaintEvent& WXUNUSED(event)) {
    wxGLCanvas::SetCurrent(*m_context);
    Render();
}

void wxGLCanvasSH::Render() {

    if(!IsShown()) return;

    if (sh==nullptr) {
        setGeo();
        sceneInit();
        sh=new SphericalHarmonics;
    }

    glClearColor(0.6,0.6,0.7, 0.6);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glLoadIdentity(); // Reset the model-view matrix

    glTranslatef(0, 0, zoom); // zoom

    glRotatef(-anglex, 0, 1, 0);
    glRotatef(angley, 1, 0, 0);

    sh->draw();

    glFlush();
    SwapBuffers();
}
