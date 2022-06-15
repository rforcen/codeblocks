#pragma once

#include "dr_wav.h"
#include "fft.h"
#include <vector>
#include <string>
#include <algorithm>
#include "ColorIndex.h"

using namespace std;

class MusicFreq {
  public:
    static constexpr float MUSICAL_INC = 1.0594630943593,  // 2^(1/12)
                           LOG_MUSICAL_INC = 0.0577622650466,
                           baseC0 = 261.62556530061,  // 440 * MUSICAL_INC^(-9)
                           LOG_baseC0 = 5.5669143414923, LOG2 = 0.6931471805599;

    // Hz 2 octave
    static int Freq2Oct(float freq) {
        if (freq <= 0) return -999;
        return (int)floor((logf(freq) - LOG_baseC0) / LOG2);
    }
    // Hz 2 note
    static int Freq2Note(float freq) {
        if (freq <= 0) return 0;
        return (int)((log(freq) - LOG_baseC0) / LOG_MUSICAL_INC -
                     Freq2Oct(freq) * 12.);
    }
    static const char *Freq2NoteName(float freq) {
        return NoteName(Freq2Note(freq)).c_str();
    }
    static float NoteOct2Freq(int oct, int note=0) {
        return (baseC0 * powf(MUSICAL_INC, note + 12. * oct));
    }
    static vector<string> &NoteNames() {
        static vector<string>NoteList = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
        return NoteList;
    }
    static string& NoteName(int n) {
        return NoteNames()[n % 12];
    }
};

class RGB {
  public:
    RGB() {}
    RGB(uint32_t c):r(c>>16 & 0xff), g(c>>8 & 0xff), b(c & 0xff) {}
    uint8_t r=0,g=0,b=0;
};

class Wave {
  public:
    explicit Wave() {}

    Wave(const char* file) {
        pSampleData = drwav_open_file_and_read_pcm_frames_f32(file, &channels, &sampleRate, &totalPCMFrameCount, nullptr);
    }
    ~Wave() {
        drwav_free(pSampleData, nullptr);
    }

    bool ok() const {
        return pSampleData!=nullptr;
    }
    bool ok(size_t i) const {
        return pSampleData!=nullptr && i<totalPCMFrameCount;
    }

    bool load(const char* file) {
        pSampleData = drwav_open_file_and_read_pcm_frames_f32(file, &channels, &sampleRate, &totalPCMFrameCount, nullptr);

        DoFFT();
        calcMusicMatrix();
        calcFormants();

        return ok();
    }
    size_t GetNSamples() {
        return (size_t)totalPCMFrameCount;
    }
    uint GetSampleRate() {
        return sampleRate;
    }
    uint GetChannels() {
        return channels;
    }
    float GetMusicMatrix(int i) {
        return ((float*)musicMatrix)[i];
    }
    float operator[](size_t i) const {
        return ok(i) ? pSampleData[i] : 0;
    }
    float GetSample(size_t i) const {
        return pSampleData[i];
    }

    float GetOverSamp(size_t i) const {
        return pSampleData[i % totalPCMFrameCount];
    }
    float GetSecs() {
        return ok() ? (float)totalPCMFrameCount / channels / sampleRate: 0;
    }

    void calcMusicMatrix() {
        memset(musicMatrix, 0, sizeof(musicMatrix));
        float maxmm=-1e32;

        for (int i=0; i<(int)fft.size(); i++) {
            float freq=fft::Index2Freq(i, sampleRate, nFFT2);

            int oct=MusicFreq::Freq2Oct(freq);
            if (oct<=2 && oct >=-2) { // -2..+2 range
                int note =MusicFreq::Freq2Note(freq);
                float ratio = powf(2, oct);

                oct+=2; // in 0..4 range
                musicMatrix[oct][note]+=fft[i] / ratio;
                maxmm=max(maxmm, musicMatrix[oct][note]);
            }
        }

        // scale it
        if (maxmm) {
            float*mm=(float*)musicMatrix;
            for (int i=0; i<5*12; i++) mm[i]/=maxmm;
        }
        // sum oct/notes
        memset(mmSumNotes, 0, sizeof(mmSumNotes));
        memset(mmSumOct, 0, sizeof(mmSumOct));

        for (int o=0; o<5; o++) {
            for (int n=0; n<12; n++) {
                mmSumOct[o]+=musicMatrix[o][n];
                mmSumNotes[n]+=musicMatrix[o][n];
            }
        }
    }

    void calcFormants() { // based on music matrix

        formants.clear();
        for (int o=0; o<5; o++)
            for (int n=0; n<12; n++)
                formants.push_back({musicMatrix[o][n], MusicFreq::NoteOct2Freq(o,n)});
        sort(formants.begin(), formants.end(), [](Signal&a, Signal&b) {
            return b.amp < a.amp;
        });
    }

    void DoFFT() {
        nFFT=10; // log2(totalPCMFrameCount)+1; //
        nFFT2=pow(2, nFFT);


        fft = vector<float>(nFFT2+2);
        accFFT = fft;

        for (size_t off=0; off<totalPCMFrameCount; off+=nFFT2) {
            for (auto i=0; i<nFFT2; i++) fft[i]=pSampleData[(i+off) % totalPCMFrameCount];
            fft::fft(fft.data(), nFFT);
            fft[0]=0;

            for (int i=0; i<nFFT2; i++) accFFT[i]+=fft[i];
        }
        fft=accFFT;
        fft::AbsScale(fft.data(), fft.size(), 1);

        maxFreq=-1e32; // maxFreq calc
        int mf=0;
        for (int i=0; i<(int)fft.size(); i++) {
            if (fft[i]>maxFreq) {
                maxFreq=fft[i];
                mf=i;
            }
        }
        maxFreq=fft::Index2Freq(mf, sampleRate, nFFT2);
    }

    double calcTInc(int sampleRate) { // needs to be double!
        return 2.0 * M_PI / sampleRate;
    }

  public:
    unsigned int channels=0;
    unsigned int sampleRate=0;
    int nFFT=0, nFFT2=0;
    drwav_uint64 totalPCMFrameCount=0;

    float samplesPlayed=0; // play control
    bool playCompleted=false;
    float volFormants=0.3, binSepparation=1.5; //hz

    float *pSampleData=nullptr;
    float maxFreq;
    vector<float>fft, accFFT;

    const int nmm=5*12;
    float musicMatrix[5][12]; // 5 octaves, 12 notes
    float mmSumNotes[12], mmSumOct[5];
    class Signal {
      public:
        float amp, hz;
    };
    vector<Signal>formants;
};
