#include "wxGLCanvasSymmIcon.h"
#include <vector>
using std::vector;

BEGIN_EVENT_TABLE(wxGLCanvasSymmIcon, wxGLCanvas)
    EVT_PAINT(wxGLCanvasSymmIcon::Paintit)
    EVT_SIZE(wxGLCanvasSymmIcon::resized)
END_EVENT_TABLE()


wxSize wxGLCanvasSymmIcon::getScaledSize() { // scale to hidpi
    GetSize(&w,&h);

    double sf = GetContentScaleFactor();
    w=(double)w * sf;
    h=(double)h * sf;
    return wxSize(w,h);
}

void wxGLCanvasSymmIcon::setBitmap(vector<u32>&image) {
    if (textLoaded) glDeleteTextures(1, &textNum);

    glGenTextures(1, &textNum); // generate 1 texture in text_id
    glBindTexture(GL_TEXTURE_2D, textNum);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Texture blends with object background

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLint)w, (GLint)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    textLoaded=true;

    Refresh();
}

void wxGLCanvasSymmIcon::resized(wxSizeEvent& evt) {
    Refresh();

    evt.Skip();
}

void wxGLCanvasSymmIcon::Paintit(wxPaintEvent&event) {
    wxGLCanvasSymmIcon::SetCurrent(*m_context);

    Render();
    event.Skip();
}

void wxGLCanvasSymmIcon::Render() {

    if(!IsShown() || !textLoaded) return;

    setGeo();
    enableTextures();

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glLoadIdentity(); // Reset the model-view matrix

    glTranslatef(0, 0, -2.2); // zoom

    // draw
    glColor3f(1,1,1);

    panel();

    glFlush();
    SwapBuffers();
}

void wxGLCanvasSymmIcon::setGeo() {
    getScaledSize();

    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(45, (float)w / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void wxGLCanvasSymmIcon::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    GLdouble fH = tan(fovY / 360. * M_PI) * zNear, fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void wxGLCanvasSymmIcon::panel(float l) {

    float lx=l, ly=l;

    if (w>h) lx = l * (float)w/h;
    else ly = l * (float)h/w;

    glBegin(GL_QUADS);

    glTexCoord2d(0,0);
    glVertex2d(-lx, -ly);
    glTexCoord2d(0,1);
    glVertex2d(-lx, ly);
    glTexCoord2d(1,1);
    glVertex2d(lx, ly);
    glTexCoord2d(1,0);
    glVertex2d(lx, -ly);

    glEnd();
}

void wxGLCanvasSymmIcon::setTexture() {
    glBindTexture(GL_TEXTURE_2D, textNum);
}
void wxGLCanvasSymmIcon::enableTextures() {
    glEnable(GL_TEXTURE_2D);
}
