//---------------------------------------------------------------------------
void TGraph::Spiral(int nt) {
    GetRect();
    double  r0=(__min(w,h))/(nt*2.+1),
            x0=w/2+x+r0/4., y0=h/2+y+r0/2.;
#define sector(X,Y,R)  cnv->Arc( (X)-(R), (Y)-(R), (X)+(R), (Y)+(R),  (X), (Y)+(R), (X), (Y)-(R))
#define sectorI(X,Y,R) cnv->Arc( (X)-(R), (Y)-(R), (X)+(R), (Y)+(R),  (X), (Y)-(R), (X), (Y)+(R))

    radius=r0;
    Cls(clBlack);
    cnv->Pen->Color=clAqua;

    double mf=1;
    for (int t=0; t<(nt<<1); t++, mf+=0.5) {
        if (t&1) sectorI(x0,y0-r0/2,r0*mf);
        else     sector (x0,y0,     r0*mf);
    }
}

//
// in 'i' turn draw *v values of size 'n'
//
void TGraph::SpiralVal(int ix, double *v, int nvp) {

    GetRect();
    double r0=radius,
           x0=w/2+x+r0/4., y0=h/2+y+r0/2.;

    cnv->Pen->Color=clBlue;
    if (!scaled)	Dif=MinMax(v,nvp);
    if (Max==0) return; // all values 0 or negative.
    Max*=1.2;
    double mf=ix, is=2.*M_PI/nvp, r=r0;

    POINT *cont=new POINT[nvp]; // contourn points
    int ic=0;
#define AddCont(xv,yv) { cont[ic].x=(xv); cont[ic].y=(yv); ic++; }


    for (int i=0; i<nvp; i++) {
        if (i==nvp/2) {
            y0-=r0/2;
            mf+=0.5;
        }

        double ri=(v[i]/Max),
               s=sin((i+1)*is), c=cos((i+1)*is),
               xci=x0 + mf*r * s,  yci=y0 - mf*r * c,
               xri=x0 + (mf-ri)*r * s,  yri=y0 - (mf-ri)*r * c;
        // lines
        cnv->MoveTo(xci,yci);  // radial from circumference perimeter
        cnv->LineTo(xri,yri);
        //
        AddCont(xri,yri);
    }

    // frame values
    cnv->Pen->Color=clYellow;
    cnv->MoveTo(cont[0].x,cont[0].y);
    for (int i=1; i<nvp; i++) cnv->LineTo(cont[i].x,cont[i].y);
    //cnv->LineTo(cont[0].x,cont[0].y);

    delete[]cont;
}

// 12 notes in a radial grid, to be called after spiral val.
void TGraph::RadialNotes(void) {
    double r0=radius, r=__min(w,h)/2.-r0, x0=w/2+x+r0/4., y0=h/2+y+r0/2.;
    double frC=NoteOct2Freq(0,0);
    cnv->Pen->Color=clRed;
    cnv->Font->Color=clWhite;  // font color
    for (int i=0; i<12; i++) {
        double is=2.*M_PI * (NoteOct2Freq(i,0)-frC) / frC,
               s=sin(is), c=cos(is),
               xc=x0 + r  * s,  yc=y0 - r  * c;
        cnv->MoveTo(x0,y0);
        cnv->LineTo(xc,yc);
        cnv->TextOut(xc,yc, NoteString(i));
        if (i==6) y0-=r0/2.;
    }
}

