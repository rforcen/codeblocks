#include "VSL_compiler.h"

#include <math.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <codecvt>
#include <vector>
#include <clocale>

using std::wcout, std::endl, std::vector;

// conversion
static wstring utf8_to_utf16(const std::string &utf8)
{
  vector<unsigned long> unicode;
  size_t i = 0;
  while (i < utf8.size())
  {
    unsigned long uni;
    size_t todo;
    bool error = false;
    unsigned char ch = utf8[i++];
    if (ch <= 0x7F)
    {
      uni = ch;
      todo = 0;
    }
    else if (ch <= 0xBF)
    {
      throw std::logic_error("not a UTF-8 string");
    }
    else if (ch <= 0xDF)
    {
      uni = ch & 0x1F;
      todo = 1;
    }
    else if (ch <= 0xEF)
    {
      uni = ch & 0x0F;
      todo = 2;
    }
    else if (ch <= 0xF7)
    {
      uni = ch & 0x07;
      todo = 3;
    }
    else
    {
      throw std::logic_error("not a UTF-8 string");
    }
    for (size_t j = 0; j < todo; ++j)
    {
      if (i == utf8.size())
        throw std::logic_error("not a UTF-8 string");
      unsigned char ch = utf8[i++];
      if (ch < 0x80 || ch > 0xBF)
        throw std::logic_error("not a UTF-8 string");
      uni <<= 6;
      uni += ch & 0x3F;
    }
    if (uni >= 0xD800 && uni <= 0xDFFF)
      throw std::logic_error("not a UTF-8 string");
    if (uni > 0x10FFFF)
      throw std::logic_error("not a UTF-8 string");
    unicode.push_back(uni);
  }

  wstring utf16;
  for (size_t i = 0; i < unicode.size(); ++i)
  {
    unsigned long uni = unicode[i];
    if (uni <= 0xFFFF)
    {
      utf16 += (wchar_t)uni;
    }
    else
    {
      uni -= 0x10000;
      utf16 += (wchar_t)((uni >> 10) + 0xD800);
      utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
    }
  }
  return utf16;
}

static void set_locales()
{
  std::setlocale(LC_ALL, "en_US.UTF-8"); // set locales to en_US
  std::setlocale(LC_NUMERIC, "en_US.UTF-8");
  std::setlocale(LC_TIME, "en_US.UTF-8");
}

extern "C"
{
  VSL_compiler *VSLNew()
  {
    set_locales();

    return new VSL_compiler;
  }
  VSL_compiler *VSLNewFromFile(char *fileName)
  {
    std::wifstream t(fileName);
    t.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    std::wstringstream buff;
    buff << t.rdbuf();
    VSL_compiler *vsl = VSLNew();

    vsl->compile(buff.str()); // compile

    return vsl;
  }
  bool VSLCompile(VSL_compiler *vsl, char *src)
  {
    // wstring source(src, src + strlen(src));
    string str(src);
    wstring source = utf8_to_utf16(str);

    vsl->compile(source); // compile
    return vsl->is_ok();
  }
  bool VSLCompileFile(VSL_compiler *vsl, char *fileName)
  {
    std::wifstream t(fileName);
    t.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    std::wstringstream buff;
    buff << t.rdbuf();

    return vsl->compile(buff.str()); // compile
  }
  void VSLFree(VSL_compiler *vsl)
  {
    delete vsl;
  }
  bool VSLIsOk(VSL_compiler *vsl)
  {
    return vsl->is_ok();
  }
  // getters
  int VSLGetNumChannels(VSL_compiler *vsl)
  {
    return vsl->get_n_channels();
  }
  int VSLGetSampleRate(VSL_compiler *vsl)
  {
    return vsl->get_sample_rate();
  }
  double VSLGetSeconds(VSL_compiler *vsl)
  {
    return vsl->get_seconds();
  }
  double VSLGetVolume(VSL_compiler *vsl)
  {
    return vsl->get_volume();
  }
  bool VSLIsFloatingPoint(VSL_compiler *vsl)
  {
    return vsl->get_floating_point();
  }

  double VSLExec(VSL_compiler *vsl, double x, int channel)
  {
    return vsl->execute(x, channel);
  }

  void VSLGenBuffer(VSL_compiler *vsl, float *buffer, int sampleCount, int nSamples)
  {
    double tinc = 2 * M_PI / vsl->get_sample_rate(), t = sampleCount * tinc;

    for (auto i = 0; i < nSamples; i++, t += tinc)
      for (auto chan = 0; chan < vsl->get_n_channels(); chan++)
        *buffer++ = vsl->get_volume() * vsl->execute(t, chan);
  }

  // test string passing
  void testString(char *s)
  {
    string str(s);
    wstring source = utf8_to_utf16(str);
    // printf("from testString:\n%s\n", s);
    // wstring source(s, s + strlen(s));
    wcout << "from testString:" << source << endl;
  }
  void testWString(int16_t *s) // wchar_t : 4 bytes
  {
    wcout << L"from testWString:";
    for (auto i = 0; s[i]; i++)
      wcout << s[i] << ' ';
  }
}

#ifdef __TEST
int main()
{
  string vsl_file = "/home/asd/Documents/qt/VSL/samples/3 voice rythm.vsl";

  std::wifstream t(vsl_file);
  t.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

  std::wstringstream buff;
  buff << t.rdbuf();
  wcout << buff.str() << endl;

  VSL_compiler vsl;

  bool ok = vsl.compile(buff.str()); // compile
  wcout << L"** compiler result:" << ok << L" ** " << endl;

  // evaluate
  wcout << L"evaluating..." << endl;
  for (auto i = 0; i < 10000000; i++)
  {
    double t, y;
    t = 2 * M_PI * i / 44100;
    y = vsl.execute(t, 0);
  }

  wcout << L"done" << endl;
  return 1;
}
#endif
