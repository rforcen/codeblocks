// mandel
// g++ -O3 mandel.cpp -o mandel -pthread
// using magick: `Magick++-config --cxxflags --cppflags`

#pragma once

#include "Thread.h"
#include "Timer.h"
#include "spline.h"

#include <complex>
#include <string>
#include <mpreal.h>

using std::complex, std::string, mpfr::mpreal;

typedef uint32_t u32;
typedef complex<double> Complex64;

enum MandelEngine { f32, f64, f128, f256, f512, f1024, f2048, f4096 };

//typedef double real;

template <class real>
class Mandelbrot {
    typedef complex<real> ComplexReal;

  private:
    static const int NPALLETE=256;
    const u32 fire_pallete[NPALLETE] = {
        0, 0, 4, 12, 16, 24, 32, 36, 44, 48, 56, 64, 68, 76, 80, 88, 96, 100, 108,
        116, 120, 128, 132, 140, 148, 152, 160, 164, 172, 180, 184, 192, 200, 1224,
        3272, 4300, 6348, 7376, 9424, 10448, 12500, 14548, 15576, 17624,
        18648, 20700, 21724, 23776, 25824, 26848, 28900, 29924, 31976, 33000,
        35048, 36076, 38124, 40176, 41200, 43248, 44276, 46324, 47352, 49400,
        51452, 313596, 837884, 1363196, 1887484, 2412796, 2937084, 3461372, 3986684,
        4510972, 5036284, 5560572, 6084860, 6610172, 7134460, 7659772, 8184060,
        8708348, 9233660, 9757948, 10283260, 10807548, 11331836, 11857148, 12381436,
        12906748, 13431036, 13955324, 14480636, 15004924, 15530236, 16054524, 16579836,
        16317692, 16055548, 15793404, 15269116, 15006972, 14744828, 14220540, 13958396,
        13696252, 13171964, 12909820, 12647676, 12123388, 11861244, 11599100, 11074812,
        10812668, 10550524, 10288380, 9764092, 9501948, 9239804, 8715516, 8453372,
        8191228, 7666940, 7404796, 7142652, 6618364, 6356220, 6094076, 5569788,
        5307644, 5045500, 4783356, 4259068, 3996924, 3734780, 3210492, 2948348,
        2686204, 2161916, 1899772, 1637628, 1113340, 851196, 589052, 64764,
        63740, 62716, 61692, 59644, 58620, 57596, 55548, 54524, 53500, 51452,
        50428, 49404, 47356, 46332, 45308, 43260, 42236, 41212, 40188, 38140,
        37116, 36092, 34044, 33020, 31996, 29948, 28924, 27900, 25852, 24828,
        23804, 21756, 20732, 19708, 18684, 16636, 15612, 14588, 12540, 11516,
        10492, 8444, 7420, 6396, 4348, 3324, 2300, 252, 248, 244, 240, 236, 232,
        228, 224, 220, 216, 212, 208, 204, 200, 196, 192, 188, 184, 180, 176, 172,
        168, 164, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112,
        108, 104, 100, 96, 92, 88, 84, 80, 76, 72, 68, 64, 60, 56, 52, 48, 44, 40,
        36, 32, 28, 24, 20, 16, 12, 8, 0, 0
    };

  public:
    int w = 0, h = 0, iters = 200;
    u32 *image = nullptr;
    ComplexReal center = ComplexReal(0.5, 0.0), range = ComplexReal(-2.0, 2.0), cr;
    real rir, scale;
    u32 *pallete = nullptr;


  private:
    inline ComplexReal do_scale(real iw, real jh) {
        return cr + rir * ComplexReal(iw, jh);
    }

  public:
    Mandelbrot() {}
    Mandelbrot(ComplexReal center, ComplexReal range, int iters) {
        this->center = center;
        this->range=range;
        this->iters=iters;
    }

    Mandelbrot(int w, int h, int iters, Complex64 center, Complex64 range)
        : w(w), h(h), iters(iters), image(new u32[w * h]), center(center), range(range),
          cr(ComplexReal(range.real(), range.real())), rir((range.imag() - range.real())), scale(0.8 * w / h) {
        if (iters>NPALLETE) {
            vector<double>x,y;
            for (int i=0; i<NPALLETE; i++) {
                x.push_back(i);
                y.push_back(fire_pallete[i]);
            }
            tk::spline spl(x,y);

            pallete=new u32[iters];
            for (int i=0; i<iters; i++)
                pallete[i]=spl(i*NPALLETE / iters);
        } else {
            this->iters=NPALLETE;
            pallete=new u32[NPALLETE];
            memcpy(pallete, fire_pallete, sizeof(fire_pallete));
        }
    }

    ~Mandelbrot() {
        if (image != nullptr) delete[] image;
        if (pallete != nullptr) delete[]pallete;
    }

    void setPrecision(int digits) {
        mpreal::set_default_prec(mpfr::digits2bits(digits));
    }

    int size_bytes() {
        return w * h * sizeof(*image);
    }
    int image_size() {
        return w * h;
    }

    inline u32 gen_pixel(int index) {
        const ComplexReal c0 = scale * do_scale(real(index % w) / w, real(index / w) / h) - center;
        ComplexReal z = c0;

        int ix = iters;
        for (int it = 0; it < iters; it++) {
            z = z * z + c0;
            if (norm(z) > real(4)) {
                ix = it;
                break;
            }
        }
        return 0xff000000 | ((ix == iters) ? 0 : pallete[ ix << 2 ]);
    }

    // single thread
    void maneldebrot_st() {
        for (auto index = 0; index < image_size(); index++)
            image[index] = gen_pixel(index);
    }

    // multithread version
    u32* maneldebrot_mt() {
        Thread(image_size()).run([this](int index) {
            image[index] = gen_pixel(index);
        });
        return image;
    }

    template<typename ... Args>
    string string_format( const string& format, Args ... args ) {
        int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        if( size_s <= 0 ) {
            throw std::runtime_error( "Error during formatting." );
        }
        auto size = static_cast<size_t>( size_s );
        auto buf = std::make_unique<char[]>( size );
        std::snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }

    string toString() {
        return string_format("(%.2f,%.2f),(%.2f,%.2f),%d", center.real(), center.imag(), range.real(), range.imag(), iters);
    }

    void restore(complex<double>&center, complex<double>&range, int &iters) {
        center=this->center;
        range=this->range;
        iters=this->iters;
    }
};


//class MandelStat {
//  public:
//    ComplexReal center, range;
//    int iters;
//
//    template<typename ... Args>
//    string string_format( const string& format, Args ... args ) {
//        int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
//        if( size_s <= 0 ) {
//            throw std::runtime_error( "Error during formatting." );
//        }
//        auto size = static_cast<size_t>( size_s );
//        auto buf = std::make_unique<char[]>( size );
//        std::snprintf( buf.get(), size, format.c_str(), args ... );
//        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
//    }
//
//    MandelStat(ComplexReal center, ComplexReal range, int iters):center(center), range(range), iters(iters) {}
//    MandelStat() {}
//
//    void restore(ComplexReal &center, ComplexReal &range, int &iters) {
//        center=this->center;
//        range=this->range;
//        iters=this->iters;
//    }
//
//    string toString() {
//        return string_format("(%.2f,%.2f),(%.2f,%.2f),%d", center.real(), center.imag(), range.real(), range.imag(), iters);
//    }
//
//};
#ifdef __TEST
void test_mandel() {
    const int n = 1024 * 4, iters = 200;
    auto mandel = Mandelbrot(n, n, iters, ComplexReal(0.5f, 0.0f), ComplexReal(-2.0f, 2.0f));

    printf("mandelbrot %dx%d=%d, iters:%d, on %d cpus...\n", n, n, n * n, iters, Thread::nCpus());

    auto t0 = Timer();

    mandel.maneldebrot_mt();
    printf("mt: %ldms, writing mandel.png\n", t0.lap());

    mandel.writepng("mandel.png");

    t0.start();
    mandel.maneldebrot_st();
    printf("st: %ldms\n", t0.lap());
}

#endif
