/******************************************************************************
  MODULE:  COLORSCALE.FP
  PURPOSE: Color scaling and RGB-HSL conversion functions
******************************************************************************/

#include "ColorScale.h"

/******************************************************************************
  FUNCTION: ColorScaleRGB
  PURPOSE: 	Returns the RGB linear interpolated color between 2 colors
            If Ratio=0, you get Col1,
            If Ratio=1, you get Col2
  IN: Col1: low color in hex 0xRRGGBB format
      Col2: high color in hex 0xRRGGBB format
      Ratio: 0 for low color, 1 for high color, or in between
  EXAMPLE: Col1=0, Col2=0xFF00FF, Ratio=0.5 returns 0x800080
******************************************************************************/
_COLORREF ColorScaleRGB(	const _COLORREF Col1,
                        const _COLORREF Col2,
                        const float Ratio) {
    int R1=(Col1>>16)&0xFF, G1=(Col1>>8)&0xFF, B1=Col1&0xFF;
    int R2=(Col2>>16)&0xFF, G2=(Col2>>8)&0xFF, B2=Col2&0xFF;
    int Color;
    if (Ratio<=0) return Col1;	// Ratio parameter must be between 0 and 1
    else if (Ratio>=1) return Col2;
    Color=	(int)(R1+(R2-R1)*Ratio+0.5)<<16 |		// rounding
                                         (int)(G1+(G2-G1)*Ratio+0.5)<<8  |
                                         (int)(B1+(B2-B1)*Ratio+0.5);
    return Color;
}


/******************************************************************************
  FUNCTION: ColorScaleHSL
  PURPOSE: 	Returns the HSL linear interpolated color between 2 colors
            (more natural looking than RGB interpolation)
            For instance if the luminance is the same in Col1 and Col2,
                then the luminance of the result will be the same
            If Ratio=0, you get Col1,
            If Ratio=1, you get Col2
  IN: Col1: low color in hex 0xRRGGBB format
      Col2: high color in hex 0xRRGGBB format
      Ratio: 0 for low color, 1 for high color, or in between
  EXAMPLE: Col1=0, Col2=0xFF00FF, Ratio=0.5 returns 0x1F5F3F
******************************************************************************/
_COLORREF ColorScaleHSL(	const _COLORREF Col1,
                        const _COLORREF Col2,
                        const float Ratio) {
    static double H1, H2, S1, S2, L1, L2;
    static int rgb;

    if (Ratio<=0) return Col1;	// Ratio parameter must be between 0 and 1
    else if (Ratio>=1) return Col2;

    RGBtoHLS( Col1, H1, L1, S1);
    RGBtoHLS( Col2, H2, L2, S2);
    return rgb=HLStoRGB( H1+(H2-H1)*Ratio, L1+(L2-L1)*Ratio, S1+(S2-S1)*Ratio );
}


/******************************************************************************
  FUNCTION: ColorScaleRGB3
  PURPOSE: 	Returns the RGB linear interpolated color between 3 colors
  IN:      	Ratio1/2/3 is the weight assigned to color 1/2/3 (0 to 1)
  NOTE:		In general you want to pass Ratio1=1-Ratio2-Ratio3
            making sure that it stays between 0 and 1
******************************************************************************/
extern _COLORREF ColorScaleRGB3(const _COLORREF Col1, const _COLORREF Col2, const _COLORREF Col3,
                               float Ratio1, float Ratio2, float Ratio3) {
    int R1=(Col1>>16)&0xFF, G1=(Col1>>8)&0xFF, B1=Col1&0xFF;
    int R2=(Col2>>16)&0xFF, G2=(Col2>>8)&0xFF, B2=Col2&0xFF;
    int R3=(Col3>>16)&0xFF, G3=(Col3>>8)&0xFF, B3=Col3&0xFF;
    int Color;
    double SR;

    if (Ratio1<0) Ratio1=0; else if (Ratio1>1) Ratio1=1;
    if (Ratio2<0) Ratio2=0; else if (Ratio2>1) Ratio2=1;
    if (Ratio3<0) Ratio3=0; else if (Ratio3>1) Ratio3=1;
    if ((SR=Ratio1+Ratio2+Ratio3)==0) return Col1;
    Color=	(int)( (Ratio1*R1+Ratio2*R2+Ratio3*R3)/SR +0.5) <<16 |		// rounding
                                                              (int)( (Ratio1*G1+Ratio2*G2+Ratio3*G3)/SR +0.5)<<8  |
                                                              (int)( (Ratio1*B1+Ratio2*B2+Ratio3*B3)/SR +0.5);
    return Color;
}

/******************************************************************************
  FUNCTION: ColorScaleHSL3
  PURPOSE: 	Returns the HSL linear interpolated color between 3 colors
  IN:      	Ratio1/2/3 is the weight assigned to color 1/2/3 (0 to 1)
  NOTE:		In general you want to pass Ratio1=1-Ratio2-Ratio3
            making sure that it stays between 0 and 1
******************************************************************************/
extern _COLORREF ColorScaleHSL3(const _COLORREF Col1, const _COLORREF Col2, const _COLORREF Col3,
                               float Ratio1, float Ratio2, float Ratio3) {
    static double H1, H2, H3, S1, S2, S3, L1, L2, L3, SR;
    static int rgb;

    if (Ratio1<0) Ratio1=0; else if (Ratio1>1) Ratio1=1;
    if (Ratio2<0) Ratio2=0; else if (Ratio2>1) Ratio2=1;
    if (Ratio3<0) Ratio3=0; else if (Ratio3>1) Ratio3=1;
    if ((SR=Ratio1+Ratio2+Ratio3)==0) return Col1;

    RGBtoHLS( Col1, H1, L1, S1);
    RGBtoHLS( Col2, H2, L2, S2);
    RGBtoHLS( Col3, H3, L3, S3);
    return rgb=HLStoRGB( (Ratio1*H1+Ratio2*H2+Ratio3*H3)/SR,
                         (Ratio1*L1+Ratio2*L2+Ratio3*L3)/SR,
                         (Ratio1*S1+Ratio2*S2+Ratio3*S3)/SR);
}


/******************************************************************************
  Q: How do I convert between the HSL (Hue, Saturation, and Luminosity) and RBG color models ?
  A: The conversion algorithms presented here come from the book
     Fundamentals of Interactive Computer Graphics by Foley and van Dam.
     In the example code, HSL values are represented as floating point number in the range 0 to 1.
     RGB tridrants use the Windows convention of 0 to 255 of each element.
******************************************************************************/

/******************************************************************************
  FUNCTION: RGBtoHLS
  PURPOSE: 	Convert from RGB to HLS
  IN: RGB color (0xRRGGBB)
  OUT: Hue, Saturation, Luminance from 0 to 1
******************************************************************************/
#define MIN3(a,b,c) ((a)<=(b) ? (a)<=(c)?(a):(c) : (b)<=(c)?(b):(c) )
#define MAX3(a,b,c) ((a)>=(b) ? (a)>=(c)?(a):(c) : (b)>=(c)?(b):(c) )

void RGBtoHLS(	const _COLORREF rgb,
                double &H, double &L, double &S ) {
    double delta;
    double r = (double)((rgb>>16)&0xFF)/255;
    double g = (double)((rgb>> 8)&0xFF)/255;
    double b = (double)((rgb    )&0xFF)/255;
    double cmax = MAX3(r,g,b);
    double cmin = MIN3(r,g,b);
    L=(cmax+cmin)/2.0;
    if(cmax==cmin) S = H = 0; // it's really undefined
    else {
        if(L < 0.5)	S = (cmax-cmin)/(cmax+cmin);
        else			S = (cmax-cmin)/(2.0-cmax-cmin);
        delta = cmax - cmin;
        if (r==cmax) H = (g-b)/delta;
        else
            if(g==cmax) H = 2.0 +(b-r)/delta;
            else        H = 4.0+(r-g)/delta;
        H /= 6.0;
        if (H < 0.0) H += 1;
    }
}

//*****************************************************************************
static double HueToRGB(const double m1, const double m2, double h ) {
    if (h<0) h+=1.0;
    if (h>1) h-=1.0;
    if (6.0*h < 1  ) return (m1+(m2-m1)*h*6.0);
    if (2.0*h < 1  ) return m2;
    if (3.0*h < 2.0) return (m1+(m2-m1)*((2.0/3.0)-h)*6.0);
    return m1;
}


/******************************************************************************
  FUNCTION: HLStoRGB
  PURPOSE: 	Convert from HSL to RGB
  IN: 		Hue, Saturation, Luminance from 0 to 1
  RETURN: 	RGB color (0xRRGGBB)
******************************************************************************/
typedef unsigned char  BYTE;        // 8-bit unsigned entity

_COLORREF HLStoRGB(const double H, const double L, const double S ) {
    double r,g,b;
    double m1, m2;

    if (S==0) r=g=b=L;
    else {
        if (L <=0.5) m2 = L*(1.0+S);
        else         m2 = L+S-L*S;
        m1 = 2.0*L-m2;
        r = HueToRGB(m1,m2,H+1.0/3.0);
        g = HueToRGB(m1,m2,H);
        b = HueToRGB(m1,m2,H-1.0/3.0);
    }
    return MakeRGB((BYTE)(r*255),(BYTE)(g*255),(BYTE)(b*255));
}

