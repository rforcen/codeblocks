#include "wxImagePanel.h"

BEGIN_EVENT_TABLE(wxImagePanel, wxPanel)
// some useful events

    EVT_MOTION(wxImagePanel::mouseMoved)
    EVT_LEFT_DOWN(wxImagePanel::mouseDown)
    EVT_LEFT_UP(wxImagePanel::mouseReleased)
    EVT_RIGHT_DOWN(wxImagePanel::rightClick)
    EVT_LEAVE_WINDOW(wxImagePanel::mouseLeftWindow)
    EVT_KEY_DOWN(wxImagePanel::keyPressed)
    EVT_KEY_UP(wxImagePanel::keyReleased)
    EVT_MOUSEWHEEL(wxImagePanel::mouseWheelMoved)
    EVT_SIZE(wxImagePanel::resize)


// catch paint events
    EVT_PAINT(wxImagePanel::paintEvent)

END_EVENT_TABLE()


// some useful events

void wxImagePanel::mouseMoved(wxMouseEvent& event) {
    pend=event.GetPosition();
    Refresh();
}
void wxImagePanel::mouseDown(wxMouseEvent& event) {
    pstart=event.GetPosition();
    isDragging=true;
}
void wxImagePanel::mouseWheelMoved(wxMouseEvent& event) {
    int wd=event.GetWheelRotation(); // GetWheelDelta();
    double scale=wd < 0 ? 1.1 : 0.9;
    double ratio = (crange.imag() - crange.real()) / 10;
    wxPoint p = event.GetPosition();

    // re center fractal
    ccenter = complex<double>(
                  ccenter.real() + ratio * (w / 2 - p.x) / w,
                  ccenter.imag() + ratio * (h / 2 - p.y) / h);

    crange = complex<double>(crange.real() * scale, crange.imag() * scale);


    paintNow();
}

void wxImagePanel::mouseReleased(wxMouseEvent& event) {
    pend=event.GetPosition();
    isDragging=false;

    if (pstart==pend) {
        const int c=50;
        pstart-=wxPoint(c,c);
        pend+=wxPoint(c,c);
    }
    auto rx = fabs(pstart.x - pend.x) / w,
         ry = fabs(pstart.y - pend.y) / h;
    auto ratio = abs(crange);

    wxPoint cp = pstart + (pend - pstart) / 2; // pstart..pend center point

    // re center fractal
    ccenter = complex<double>(
                  ccenter.real() + ratio * (w / 2 - cp.x) / w,
                  ccenter.imag() + ratio * (h / 2 - cp.y) / h);

    crange = complex<double>(crange.real() * rx, crange.imag() * ry);
    paintNow();
}
void wxImagePanel::rightClick(wxMouseEvent& event) {}
void wxImagePanel::mouseLeftWindow(wxMouseEvent& event) {}
void wxImagePanel::keyPressed(wxKeyEvent& event) {}
void wxImagePanel::keyReleased(wxKeyEvent& event) {}

void wxImagePanel::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

void wxImagePanel::paintNow() {
    wxClientDC dc(this);

    refresh=true;
    render(dc);
}

void wxImagePanel::generateFractal(int w, int h) {
    switch (engine) {
    case f32: {
        Mandelbrot<float> mandel(w, h, iters, ccenter, crange);
        mandelBmp=genImage(w, h, mandel.maneldebrot_mt());
    }
    break;
    case f64: {
        Mandelbrot<double> mandel(w, h, iters, ccenter, crange);
        mandelBmp=genImage(w, h, mandel.maneldebrot_mt());
    }
    break;
    case f128: {
        Mandelbrot<long double> mandel(w, h, iters, ccenter, crange);
        mandelBmp=genImage(w, h, mandel.maneldebrot_mt());
    }
    break;

    default: { // 256..4096
        Mandelbrot<mpreal> mandel(w, h, iters, ccenter, crange);
        mandel.setPrecision( 1 << (8 + engine - f256) );
        mandelBmp=genImage(w, h, mandel.maneldebrot_mt());
    }

    break;
    }
}

void wxImagePanel::render(wxDC&  dc) {
    if (refresh) {

        GetSize(&w, &h);

        Timer t0;

        generateFractal(w,h);

        msg=wxString::Format("lap:%ldms, iters:%d, size:(%d,%d)", t0.lap(), iters, w, h);
        refresh=false;
    }

    dc.DrawBitmap(mandelBmp, zp);

    if (isDragging) {

        dc.SetPen(*wxWHITE_PEN);
        dc.SetBrush(*wxTRANSPARENT_BRUSH);

        dc.DrawRectangle(pstart.x, pstart.y, pend.x-pstart.x, pend.y-pstart.y);
    }

    if (!msg.IsEmpty()) {
        if (sb) sb->SetStatusText(msg);
        else {
            dc.SetBrush(*wxGREEN_BRUSH);
            dc.SetTextBackground(*wxGREEN);
            dc.SetTextForeground(*wxWHITE);
            dc.DrawText(msg, 2, 2);
        }
    }
}

