#ifndef TAUDIO_H
#define TAUDIO_H

#include <portaudio.h>


typedef int TbaseCallBack( const void *, void *,
                                unsigned long ,
                                const PaStreamCallbackTimeInfo* ,
                                PaStreamCallbackFlags ,
                                void *);

typedef void TsoundCallBack(void *userData, void*buffer, int nFrames);


typedef struct _DataCB { // container for userdata & callback
  void *data;
  TsoundCallBack *callBack;
} DataCB;


// base callback func
static int __baseCallBack( const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,   const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,   void *userData ) {

    DataCB *dc=(DataCB*)userData;
    dc->callBack(dc->data, outputBuffer, (int)framesPerBuffer); // cal user callback

    return paContinue;
}


class Audio
{
public:
    const int framesPerBuffer = 4096;

    PaStreamParameters outParams;
    PaStream *stream = nullptr;
    PaError err;

    struct {
        void *data;
        TsoundCallBack *cb;
    } dataCB;

    Audio()
    {}

    ~Audio()
    {
        if (stream != nullptr)
            Pa_CloseStream(stream);
        stream=nullptr;
    }

    static void init() {
        Pa_Initialize();
    }
    static void term() {
        Pa_Terminate();
    }

    void define(int nchan, int sampleRate, void*data, TsoundCallBack callBack)
    {
        dataCB.data=data;
        dataCB.cb=callBack;

        outParams.device = Pa_GetDefaultOutputDevice();
        outParams.channelCount = nchan;
        outParams.sampleFormat = paFloat32;
        outParams.suggestedLatency = Pa_GetDeviceInfo(outParams.device)->defaultLowOutputLatency;
        outParams.hostApiSpecificStreamInfo = NULL;

        err = Pa_OpenStream(&stream, nullptr,                                   // no input
                            &outParams, sampleRate, framesPerBuffer, paClipOff, // we won't output out of range samples so don't bother clipping them
                            __baseCallBack, &dataCB);

        err = Pa_StartStream(stream);
    }

    void start()
    {
        err = Pa_StartStream(stream);
    }
    bool stop()
    {
        bool isPly=isPlaying();
        err = Pa_StopStream(stream);
        return isPly;
    }

    bool isPlaying()
    {
        return (stream!=nullptr) ? Pa_IsStreamActive(stream) == 1 : false;
    }
};

#endif // TAUDIO_H
