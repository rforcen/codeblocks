#ifndef FREQMESH_H
#define FREQMESH_H

#include <math.h>
#include <string>
#include <vector>
#include <stdarg.h> // For va_start, etc.
#include <memory>   // For std::unique_ptr
#include <cstring>

using std::lower_bound;
using std::vector, std::string;

std::string string_format(const std::string fmt_str, ...)
{
  int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
  std::unique_ptr<char[]> formatted;
  va_list ap;
  while (1)
  {
    formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
    strcpy(&formatted[0], fmt_str.c_str());
    va_start(ap, fmt_str);
    final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
    va_end(ap);
    if (final_n < 0 || final_n >= n)
      n += abs(final_n - n + 1);
    else
      break;
  }
  return std::string(formatted.get());
}

class MusicalFreq
{
private:
  inline static double pow2int(double f, int n)
  { // f·2^n
    return n < 0 ? f / (1 << -n) : f * (1 << n);
  }

public:
  static constexpr double baseC0 = 261.62556530061,
                          log2_baseC0 = 8.031359713524722,
                          musical_inc = 1.0594630943593;

  static double freq_in_oct(double f, int oct)
  {
    return pow2int(f, int(log2_baseC0 + oct - log2(f)));
  }
};

class FreqMesh : public MusicalFreq
{
public:
  vector<double> amp, hz;
  uint n = 0;

private:
  static const uint nwaves = 150;
  double base = 3510., slope = 1.4;
  uint islope = 2800;

  bool _is_init = false;

public:
  bool is_init() { return _is_init; }

  void set_param(double base = 3510, double slope = 1.4, uint islope = 2800,
                 uint n = nwaves)
  {
    this->base = base;
    this->slope = slope;
    this->islope = islope;
    this->n = n;

    gen_wave(n);
  }

  // line equation y=ax+b with a real b part 3510. and a composed by real 1.4
  // and INT(i x 2800 / n)
  inline double star_freqs(uint i)
  {
    return base + slope * uint(i * islope / n);
  }
  inline double line_form(uint i)
  {
    return base + i * slope;
  } // interesting: i*2+3500

  inline int get_octave(double d)
  {
    static double octRange[] = {0.43, 0.77, 1};
    static const int n_octs = sizeof(octRange) / sizeof(*octRange);

    return int(lower_bound(octRange, octRange + n_octs, d) - octRange) -
           (n_octs - 2);
  }

  void gen_wave(uint n = nwaves)
  {
    this->n = n;

    amp.resize(n);
    hz.resize(n);

    for (uint i = 0; i < n; i++)
    {
      amp[i] = sin(0.1 + i * 2 * M_PI / n);
      hz[i] = freq_in_oct(star_freqs(i), get_octave(double(i) / n));
    }
    _is_init = true;
  }

  double gen_sample(double t)
  {
    double samp = 0;
    for (uint i = 0; i < n; i++)
      samp += amp[i] * sin(t * hz[i]);
    return samp;
  }

  string gen_str_wave(uint n = nwaves)
  {
    gen_wave(n);

    string str;
    for (uint i = 0; i < n; i++)
      str.append(string_format("{%f, %f}%s", amp[i], hz[i], (i == n - 1 ? ";\n\n" : "+")));

    return str;
  }

  string gen_clip_wave(uint n = nwaves)
  {
    gen_wave(n);

    string str;
    for (uint i = 0; i < n; i++)
      str.append(string_format("%f\t%f\n", amp[i], hz[i]));

    return str;
  }
};

#endif // FREQMESH_H
