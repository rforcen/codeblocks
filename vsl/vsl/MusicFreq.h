#pragma once

#include <string>
#include <vector>

using Color = uint32_t;
using std::string, std::vector;

class MusicFreq
{
  static constexpr double MUSICAL_INC = 1.0594630943593, // 2^(1/12)
      LOG_MUSICAL_INC = 0.0577622650466,
                          baseC0 = 261.62556530061, // 440 * MUSICAL_INC^(-9)
      LOG_baseC0 = 5.5669143414923, LOG2 = 0.6931471805599;

public:
  static Color Freq2Color(double freq);
  static double FreqInOctave(double f, int oct);
  static double FreqInOctaves(double f, int oct0, int oct1);
  static string NoteString(int i);
  static string NoteString(double freq);
  static double NoteOct2Freq(int note, int oct);
  static int Freq2NoteOct(double freq, int &note, int &oct, string &NoteOct,
                          double &err);
  static int Freq2NoteOct(double freq, int &note, int &oct, string &NoteOct);
  static string Freq2NoteOct(double freq);
  static int Freq2Oct(double freq);
  static int Freq2Note(double freq);
  static double ErrInNote(double freq);
  static bool FreqInOctRange(double freq, int octDown, int octUp);
  static double Freq2Element(double freq);
  static string Freq2StrNote(double freq);
  static void Frm2OctaveRange(double *HzFrm, int nform, int oct = 0);
  static double NoteFit(double hz);
  static vector<string> note_str()
  {
    return {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
  }
  static string NoteStr2ColorName(string note);
  static string Freq2ColorName(double freq);
};
