#ifndef _FFTH
#define _FFTH
namespace fft {
#define PHI 0.618033988749895  // (-1+sqrt(5))/2
#define DeltaPhi 0.0001
#define DeltaRel 0.0001

typedef struct { int i, j, k; } TPHIRels;  // struct for PHI relations
typedef struct {
  int p;
  float v;
  float ph;
} Tpm;  // formants pos.
// m=2^n, vector should be n+2 large!!
void fft(float *y, int m);
void fft_inv(float *y, int m);
float *ModPhaseFFT(int n, float *x, float *mod, float *phase);
float ClosestPhiRel(float *HzFrm, int n);
void ProcessFFT(
    float *vfft, float *vx, int n,  // i/o vfft i/o vx in Hz
    float &max, float &HzMax,       // scaled values in power & Hz
    bool smooth, bool scalelog,       // smooth?, log scale?
    float scale, int samples,        // scale==0 don't scale
    float &coherence,                // calc coherence
    int &nform,                       // number of formants (must smooth!)
    float *HzFrm, float *PowFrm,    // vector containing formants
    float *phFrm);  // scaled vfft values and samples for Hz conversion.
void Formants(float *vfft, float *HzFrm, float *PwrFrm, int n, int &nform);
void Formants(float *vfft, float *HzFrm, float *PwrFrm, float *phFrm, int n,
              int &nform);
int GetPeaks(float *vfft, int nFFT, float *HzFrm, float *PwFrm, int &nform,
             float &fMax, float &fMin, float fc);

int CountRels(float *HzFrm, int nform, float Rel, float delta);
int CountPhiRels(float *HzFrm, int nform);
int CountOctRels(float *HzFrm, int nform);
int CountFourthRels(float *HzFrm, int nform);
int CountFifthRels(float *HzFrm, int nform);

int GetPHIRels(float *HzFrm, int nform, TPHIRels *PHIRels);
int GetRels(float *HzFrm, int nform, float *rels, float from, float to,
            float factor);
float AbsScale(float *vfft, int n);
float AbsScale(float *vfft, int n, float scale);
int Freq2Index(float freq, float samples, int nFFT);
float Index2Freq(int i, float samples, int nFFT);
int FreqRange(float *v, int n, float sump, int &_fMin, int &_fMax);

float v_MinMax(float &fMin, float &fMax, float *vHz, float *v, int n);
void v_Zero(float *v, int n);
float MirrorVector(float *v, float *vo, int n);
void SortTwo(float *y, float *x, int n);
void SortTwoAsc(float *y, float *x, int n);
void Sort(float *v, int n);
float Jitter(float *vfft, int n);
float weakNote(float *HzFrm, int nf);
float excessNote(float *musGrid, int n);
int _cmp_int(const void *p1, const void *p2);
int _cmp_dbl(const void *p1, const void *p2);
int _cmp_flt(const void *p1, const void *p2);
void MinMax(float *v, int n, float &Min, float &Max);
float db(float range, float val);
float db(float val);
float db100(float val);
}
#endif
