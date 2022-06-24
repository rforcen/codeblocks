#include <wx/rawbmp.h>
#include "wxGLImage.h"
#include <vector>
#include <functional>

/* key points:

    1- use RGBA textures NOT RGB ones generated in a vector<uint32_t>
    2- calculate size of canvas using  GetContentScaleFactor()
    3- draw in a wxBimap associated wxMemoryDC and convert the bitmap to a rotated/mirror image -> rgba
    4- glTranslatef to fH = tan(fovY / 360. * M_PI) * zNear;

*/

using namespace std;

BEGIN_EVENT_TABLE(wxGLImage, wxGLCanvas)
    EVT_PAINT(wxGLImage::OnPaint)
    EVT_SIZE(wxGLImage::OnResize)
END_EVENT_TABLE()


wxSize wxGLImage::getScaledSize() { // scale to hidpi
    GetSize(&w,&h);

    double sf = GetContentScaleFactor();
    w=(double)w * sf;
    h=(double)h * sf;
    return wxSize(w,h);
}

void wxGLImage::GenerateImage() { // convert rgb -> rgba
    wxImage drawImg = drawBmp.ConvertToImage().Rotate180().Mirror();

    RGB *data=(RGB*)drawImg.GetData();
    image.resize(w*h);

    for (int i=0; i<w*h; i++)
        image[i]=data[i].toU32();
}

void wxGLImage::SetTexture() {

    if (textLoaded) glDeleteTextures(1, &textNum);

    glGenTextures(1, &textNum); // generate 1 texture in text_id
    glBindTexture(GL_TEXTURE_2D, textNum);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  // Texture blends with object background

    GenerateImage(); // don't use GL_RGB, hangs on resize

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLint)w, (GLint)h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    textLoaded=true;
}

void wxGLImage::DrawGraph() {
    getScaledSize(); // calc proper w,h

    drawBmp=wxBitmap(w, h);
    wxMemoryDC memDC(drawBmp); // draw on 'drawBmp'

    RenderGraph(memDC);

    SetTexture(); // generate a GL texture from bitmap converted to rgba
}


void wxGLImage::OnResize(wxSizeEvent& evt) {
    Refresh();

    evt.Skip();
}

void wxGLImage::OnPaint(wxPaintEvent&event) {
    SetCurrent(*m_context);

    DrawGraph();

    Render();
}

void wxGLImage::Render() {

    if(!IsShown() || !textLoaded) return;

    setGeo();
    enableTextures();

    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers

    glLoadIdentity(); // Reset the model-view matrix

    glTranslatef(0, 0, -1/fH); // zoom to 1/fW

    // draw
    glColor3f(1,1,1);

    panel();

    glFlush();
    SwapBuffers();
}

void wxGLImage::setGeo() {

    glViewport(0,0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(45, 1, 1, 10); // aspect is 1 as we want a flat 2d surface
    glMatrixMode(GL_MODELVIEW);
}

void wxGLImage::perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar) {
    fH = tan(fovY / 360. * M_PI) * zNear;
    fW = fH * aspect;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void wxGLImage::panel(float l) {

    float lx=l, ly=l;

//    if (w>h) lx = l * (float)w/h;
//    else ly = l * (float)h/w;

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

void wxGLImage::setTexture() {
    glBindTexture(GL_TEXTURE_2D, textNum);
}
void wxGLImage::enableTextures() {
    glEnable(GL_TEXTURE_2D);
}
