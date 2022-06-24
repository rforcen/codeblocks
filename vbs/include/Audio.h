#pragma once
#include <portaudio.h>
#include <functional>


//typedef void TsoundCallBack(void *userData, void*buffer, int nFrames);
class DataCB;
typedef std::function<void(DataCB *userData, void*buffer, int nFrames)> TsoundCallBack;

class DataCB { // container for userdata & callback
    public:
    void *data;
    TsoundCallBack callBack;
    PaStreamCallbackResult result;
};


class Audio {
  public:
    const int framesPerBuffer = 4096;

    PaStreamParameters outParams;
    PaStream *stream = nullptr;
    PaError err;

    DataCB dataCB;

    explicit Audio() {}

    ~Audio() {
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

    void define(int nchan, int sampleRate, void*data, TsoundCallBack callBack) {
        dataCB.data=data;
        dataCB.callBack=callBack;
        dataCB.result=paContinue;

        outParams.device = Pa_GetDefaultOutputDevice();
        outParams.channelCount = nchan;
        outParams.sampleFormat = paFloat32;
        outParams.suggestedLatency = Pa_GetDeviceInfo(outParams.device)->defaultLowOutputLatency;
        outParams.hostApiSpecificStreamInfo = NULL;

        err = Pa_OpenStream(&stream, nullptr,                                   // no input
                            &outParams, sampleRate, framesPerBuffer, paClipOff, // we won't output out of range samples so don't bother clipping them
                            // callback lambda
                            [](const void *inputBuffer, void *outputBuffer,
                               unsigned long framesPerBuffer,
                               const PaStreamCallbackTimeInfo* timeInfo,
                               const PaStreamCallbackFlags statusFlags,
        void *userData ) -> int {

            DataCB *dc=(DataCB*)userData;
            dc->callBack(dc, outputBuffer, (int)framesPerBuffer); // cal user callback

            return dc->result;
        }
        , &dataCB);

        err = Pa_StartStream(stream);
    }

    void start() {
        err = Pa_StartStream(stream);
    }
    bool stop() {
        bool isPly=isPlaying();
        err = Pa_StopStream(stream);
        return isPly;
    }

    bool isPlaying() {
        return (stream!=nullptr) ? Pa_IsStreamActive(stream) == 1 : false;
    }
};
