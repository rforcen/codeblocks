#pragma once

#define _COLORREF unsigned int	// 0 to 0xFFFFFF and 0xFFFFFFFF for transparencies

// TColor(BGR) 2 ColorRef(RGB)
#define TColor2ColorRef(c)  (_COLORREF)( (((c)&0xff0000)>>16) | (((c)&0x00ff00)) | (((c)&0x0000ff)<<16) )
//#define ColorRef2TColor(c)  (TColor  )( (((c)&0xff0000)>>16) | (((c)&0x00ff00)) | (((c)&0x0000ff)<<16) )

// Create a 0xRRGGBB from separate 8 bits colors - no error checking
#define MakeRGB(r,g,b) ( ((r)<<16) | ((g)<<8) | (b))
#define _getRED(c)   ((((c)&0xFF0000)>>16))
#define _getGREEN(c) ((((c)&0x00FF00)>>8))
#define _getBLUE(c)  ((((c)&0x0000FF)))

#define _getREDf(c)   (_getRED(c)/256.)
#define _getGREENf(c) (_getGREEN(c)/256.)
#define _getBLUEf(c)  (_getBLUE(c)/256.)
#define Max(x,y) (((x)>(y))?(x):(y))
#define Min(x,y) (((x)<(y))?(x):(y))

extern _COLORREF ColorScaleRGB( _COLORREF Col1,  _COLORREF Col2,  float Ratio);
extern _COLORREF ColorScaleHSL( _COLORREF Col1,  _COLORREF Col2,  float Ratio);
extern _COLORREF ColorScaleRGB3( _COLORREF Col1,  _COLORREF Col2,  _COLORREF Col3,
                                float Ratio1, float Ratio2, float Ratio3);
extern _COLORREF ColorScaleHSL3( _COLORREF Col1,  _COLORREF Col2,  _COLORREF Col3,
                                float Ratio1, float Ratio2, float Ratio3);

extern void       RGBtoHLS( _COLORREF rgb, double &H, double &L, double &S );
extern _COLORREF	HLStoRGB( double H,  double L,  double S );
