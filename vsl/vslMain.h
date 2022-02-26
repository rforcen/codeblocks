/***************************************************************
 * Name:      vslMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2022-02-21
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef VSLMAIN_H
#define VSLMAIN_H



//(*Headers(vslFrame)
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/toolbar.h>
//*)

#include <wx/textfile.h>
#include <wx/mstream.h>
#include <vector>
#include <cstdlib>

using std::vector;

// resources.o created w/ ld -r -b binary -o resources.o *.png
// nm resources.o creates, don't use _size as relocatable efi will change its value, use ptr diff(end - start)
// images
extern char _binary_clear_png_end,_binary_clear_png_start,_binary_pause_png_end,_binary_pause_png_start,_binary_play_png_end,_binary_play_png_start,_binary_rand_png_end,
_binary_rand_png_start,_binary_transformation_png_end,_binary_transformation_png_start,_binary_voicesync_logo_ico_end,_binary_voicesync_logo_ico_start;
// presets
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
extern char _binary_3_voice_rythm_01_vsl_end,_binary_3_voice_rythm_01_vsl_start,_binary_3_voice_rythm_vsl_end,_binary_3_voice_rythm_vsl_start,    _binary_alien_march_vsl_end,_binary_alien_march_vsl_start,_binary_am___fm_01_vsl_end,_binary_am___fm_01_vsl_start,_binary_am___fm_vsl_end,_binary_am___fm_vsl_start,    _binary_aus_flower_01_vsl_end,_binary_aus_flower_01_vsl_start,_binary_aus_flower_02_vsl_end,_binary_aus_flower_02_vsl_start,_binary_aus_flower_exp_vsl_end,    _binary_aus_flower_exp_vsl_start,_binary_a_vsl_end,_binary_a_vsl_start,_binary_bal_phi_vsl_end,_binary_bal_phi_vsl_start,_binary_bell_org_vsl_end,    _binary_bell_org_vsl_start,_binary_bell_vsl_end,_binary_bell_vsl_start,_binary_bolw_bal_phi_vsl_end,_binary_bolw_bal_phi_vsl_start,_binary_bowl_01_vsl_end,    _binary_bowl_01_vsl_start,_binary_bowl_mix_vsl_end,_binary_bowl_mix_vsl_start,_binary_bowl_vsl_end,_binary_bowl_vsl_start,_binary_brain_crack_vsl_end,    _binary_brain_crack_vsl_start,_binary_cadence_vsl_end,_binary_cadence_vsl_start,_binary_cry_vsl_end,_binary_cry_vsl_start,_binary_default_02_vsl_end,    _binary_default_02_vsl_start,_binary_default_let_vsl_end,_binary_default_let_vsl_start,_binary_default_vsl_end,_binary_default_vsl_start,_binary_exp01_vsl_end,    _binary_exp01_vsl_start,_binary__flwr01_vsl_end,_binary__flwr01_vsl_start,_binary_foo_vsl_end,_binary_foo_vsl_start,_binary_freq_inc_01_vsl_end,_binary_freq_inc_01_vsl_start,    _binary_freq_inc_vsl_end,_binary_freq_inc_vsl_start,_binary_freqmesh01_vsl_end,_binary_freqmesh01_vsl_start,_binary_freq_ramp_01_vsl_end,_binary_freq_ramp_01_vsl_start,    _binary_freq_ramp_vsl_end,_binary_freq_ramp_vsl_start,_binary_func01_vsl_end,_binary_func01_vsl_start,_binary_func02_vsl_end,_binary_func02_vsl_start,_binary_func_alg01_vsl_end,    _binary_func_alg01_vsl_start,_binary_mantra_vsl_end,_binary_mantra_vsl_start,_binary_mediterraneum_vsl_end,_binary_mediterraneum_vsl_start,_binary_merc01_vsl_end,_binary_merc01_vsl_start,    _binary_notes_vsl_end,_binary_notes_vsl_start,_binary_pacman_vsl_end,_binary_pacman_vsl_start,_binary_planet_vsl_end,_binary_planet_vsl_start,_binary_prog01_vsl_end,_binary_prog01_vsl_start,    _binary_r3_vsl_end,_binary_r3_vsl_start,_binary_rand_sheet01_vsl_end,_binary_rand_sheet01_vsl_start,_binary_relax01_vsl_end,_binary_relax01_vsl_start,_binary_rithm01_vsl_end,_binary_rithm01_vsl_start,    _binary_rithm02_vsl_end,_binary_rithm02_vsl_start,_binary_rithm03_vsl_end,_binary_rithm03_vsl_start,_binary_rithm04_vsl_end,_binary_rithm04_vsl_start,_binary_rnd01_vsl_end,_binary_rnd01_vsl_start,    _binary_rnd02_vsl_end,_binary_rnd02_vsl_start,_binary_rpn01_vsl_end,_binary_rpn01_vsl_start,_binary_rpn02_vsl_end,_binary_rpn02_vsl_start,_binary_rpn_compressor_tilde_vsl_end,    _binary_rpn_compressor_tilde_vsl_start,_binary_rpn_compressor_vsl_end,_binary_rpn_compressor_vsl_start,_binary_rpn_seq_comp_tilde_vsl_end,_binary_rpn_seq_comp_tilde_vsl_start,    _binary_star01_vsl_end,_binary_star01_vsl_start,_binary_star02_vsl_end,_binary_star02_vsl_start,_binary_star03_vsl_end,_binary_star03_vsl_start,_binary_star04_vsl_end,_binary_star04_vsl_start,    _binary_star_fformula_vsl_end,_binary_star_fformula_vsl_start,_binary_star_formula01_vsl_end,_binary_star_formula01_vsl_start,_binary_star_formula_vsl_end,_binary_star_formula_vsl_start,    _binary_star_from_spreadsheet_vsl_end,_binary_star_from_spreadsheet_vsl_start,_binary_star_sound01_vsl_end,_binary_star_sound01_vsl_start,_binary_star_sound02_vsl_end,_binary_star_sound02_vsl_start,    _binary_str01_vsl_end,_binary_str01_vsl_start,_binary_waka_waka_vsl_end,_binary_waka_waka_vsl_start,_binary_white_noise_vsl_end,_binary_white_noise_vsl_start;
#pragma GCC diagnostic pop

class vslFrame: public wxFrame
{
public:

    vslFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~vslFrame();

private:

    class Audio*audio;
    class VSL_compiler*vsl;

    bool dirty=false;
    wxString vslFolder;

    wxBitmap bmpPlay, bmpPause;
    vector<wxString> preset_names={"3_voice_rythm_01","3_voice_rythm","alien_march","am___fm_01","am___fm","aus_flower_01","aus_flower_02","aus_flower_exp","a","bal_phi","bell_org","bell","bolw_bal_phi","bowl_01","bowl_mix","bowl","brain_crack","cadence","cry","default_02","default_let","default","exp01","_flwr01","foo","freq_inc_01","freq_inc","freqmesh01","freq_ramp_01","freq_ramp","func01","func02","func_alg01","mantra","mediterraneum","merc01","notes","pacman","planet","prog01","r3","rand_sheet01","relax01","rithm01","rithm02","rithm03","rithm04","rnd01","rnd02","rpn01","rpn02","rpn_compressor_tilde","rpn_compressor","rpn_seq_comp_tilde","star01","star02","star03","star04","star_fformula","star_formula01","star_formula","star_from_spreadsheet","star_sound01","star_sound02","str01","waka_waka","white_noise"};
    vector<char*>preset_address={&_binary_3_voice_rythm_01_vsl_end,&_binary_3_voice_rythm_01_vsl_start,&_binary_3_voice_rythm_vsl_end,&_binary_3_voice_rythm_vsl_start, &_binary_alien_march_vsl_end,&_binary_alien_march_vsl_start,&_binary_am___fm_01_vsl_end,&_binary_am___fm_01_vsl_start,&_binary_am___fm_vsl_end,&_binary_am___fm_vsl_start, &_binary_aus_flower_01_vsl_end,&_binary_aus_flower_01_vsl_start,&_binary_aus_flower_02_vsl_end,&_binary_aus_flower_02_vsl_start,&_binary_aus_flower_exp_vsl_end, &_binary_aus_flower_exp_vsl_start,&_binary_a_vsl_end,&_binary_a_vsl_start,&_binary_bal_phi_vsl_end,&_binary_bal_phi_vsl_start,&_binary_bell_org_vsl_end, &_binary_bell_org_vsl_start,&_binary_bell_vsl_end,&_binary_bell_vsl_start,&_binary_bolw_bal_phi_vsl_end,&_binary_bolw_bal_phi_vsl_start,&_binary_bowl_01_vsl_end, &_binary_bowl_01_vsl_start,&_binary_bowl_mix_vsl_end,&_binary_bowl_mix_vsl_start,&_binary_bowl_vsl_end,&_binary_bowl_vsl_start,&_binary_brain_crack_vsl_end, &_binary_brain_crack_vsl_start,&_binary_cadence_vsl_end,&_binary_cadence_vsl_start,&_binary_cry_vsl_end,&_binary_cry_vsl_start,&_binary_default_02_vsl_end, &_binary_default_02_vsl_start,&_binary_default_let_vsl_end,&_binary_default_let_vsl_start,&_binary_default_vsl_end,&_binary_default_vsl_start,&_binary_exp01_vsl_end, &_binary_exp01_vsl_start,&_binary__flwr01_vsl_end,&_binary__flwr01_vsl_start,&_binary_foo_vsl_end,&_binary_foo_vsl_start,&_binary_freq_inc_01_vsl_end,&_binary_freq_inc_01_vsl_start, &_binary_freq_inc_vsl_end,&_binary_freq_inc_vsl_start,&_binary_freqmesh01_vsl_end,&_binary_freqmesh01_vsl_start,&_binary_freq_ramp_01_vsl_end,&_binary_freq_ramp_01_vsl_start, &_binary_freq_ramp_vsl_end,&_binary_freq_ramp_vsl_start,&_binary_func01_vsl_end,&_binary_func01_vsl_start,&_binary_func02_vsl_end,&_binary_func02_vsl_start,&_binary_func_alg01_vsl_end, &_binary_func_alg01_vsl_start,&_binary_mantra_vsl_end,&_binary_mantra_vsl_start,&_binary_mediterraneum_vsl_end,&_binary_mediterraneum_vsl_start,&_binary_merc01_vsl_end,&_binary_merc01_vsl_start, &_binary_notes_vsl_end,&_binary_notes_vsl_start,&_binary_pacman_vsl_end,&_binary_pacman_vsl_start,&_binary_planet_vsl_end,&_binary_planet_vsl_start,&_binary_prog01_vsl_end,&_binary_prog01_vsl_start, &_binary_r3_vsl_end,&_binary_r3_vsl_start,&_binary_rand_sheet01_vsl_end,&_binary_rand_sheet01_vsl_start,&_binary_relax01_vsl_end,&_binary_relax01_vsl_start,&_binary_rithm01_vsl_end,&_binary_rithm01_vsl_start, &_binary_rithm02_vsl_end,&_binary_rithm02_vsl_start,&_binary_rithm03_vsl_end,&_binary_rithm03_vsl_start,&_binary_rithm04_vsl_end,&_binary_rithm04_vsl_start,&_binary_rnd01_vsl_end,&_binary_rnd01_vsl_start, &_binary_rnd02_vsl_end,&_binary_rnd02_vsl_start,&_binary_rpn01_vsl_end,&_binary_rpn01_vsl_start,&_binary_rpn02_vsl_end,&_binary_rpn02_vsl_start,&_binary_rpn_compressor_tilde_vsl_end, &_binary_rpn_compressor_tilde_vsl_start,&_binary_rpn_compressor_vsl_end,&_binary_rpn_compressor_vsl_start,&_binary_rpn_seq_comp_tilde_vsl_end,&_binary_rpn_seq_comp_tilde_vsl_start, &_binary_star01_vsl_end,&_binary_star01_vsl_start,&_binary_star02_vsl_end,&_binary_star02_vsl_start,&_binary_star03_vsl_end,&_binary_star03_vsl_start,&_binary_star04_vsl_end,&_binary_star04_vsl_start, &_binary_star_fformula_vsl_end,&_binary_star_fformula_vsl_start,&_binary_star_formula01_vsl_end,&_binary_star_formula01_vsl_start,&_binary_star_formula_vsl_end,&_binary_star_formula_vsl_start, &_binary_star_from_spreadsheet_vsl_end,&_binary_star_from_spreadsheet_vsl_start,&_binary_star_sound01_vsl_end,&_binary_star_sound01_vsl_start,&_binary_star_sound02_vsl_end,&_binary_star_sound02_vsl_start, &_binary_str01_vsl_end,&_binary_str01_vsl_start,&_binary_waka_waka_vsl_end,&_binary_waka_waka_vsl_start,&_binary_white_noise_vsl_end,&_binary_white_noise_vsl_start};

    void PlayVSL();
    void SaveVSL();
    void LoadVSL();
    void ExportVSLWav();

    void SetToolBarBitmap(char *astart, char *aend, int id);
    void LoadResources();

    void stop();


    //(*Handlers(vslFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnBitmapButton1Click(wxCommandEvent& event);
    void OntbPlayClicked(wxCommandEvent& event);
    void OnTBOpenClicked(wxCommandEvent& event);
    void OnTB_SaveClicked(wxCommandEvent& event);
    void OnTB_ExportClicked(wxCommandEvent& event);
    void OnKeyDown(wxKeyEvent& event);
    void OnTextVSLText(wxCommandEvent& event);
    void OnchSymbolsSelect(wxCommandEvent& event);
    void OnlbPresetSelect(wxCommandEvent& event);
    void OnslVolumeCmdScrollChanged(wxScrollEvent& event);
    void OnTB_newClicked(wxCommandEvent& event);
    void OnTB_RandClicked(wxCommandEvent& event);
    //*)

    //(*Identifiers(vslFrame)
    static const long ID_SLIDER1;
    static const long ID_CHECKBOX1;
    static const long ID_STATICTEXT1;
    static const long ID_CHOICE1;
    static const long ID_LISTBOX1;
    static const long ID_STATICLINE1;
    static const long ID_VSLTEXT;
    static const long ID_STATUSBAR1;
    static const long ID_TBPLAY;
    static const long ID_TB_OPEN;
    static const long ID_TB_SAVE;
    static const long ID_TBCLEAR;
    static const long ID_TB_RAND;
    static const long ID_TB_EXPORT;
    static const long ID_TOOLBAR1;
    //*)

    //(*Declarations(vslFrame)
    wxCheckBox* cbAutoPlay;
    wxChoice* chSymbols;
    wxFileDialog* fdExport;
    wxFileDialog* fdOpen;
    wxFileDialog* fdSave;
    wxListBox* lbPreset;
    wxSlider* slVolume;
    wxStaticLine* StaticLine1;
    wxStaticText* StaticText1;
    wxStatusBar* StatusBar1;
    wxTextCtrl* TextVSL;
    wxToolBar* ToolBar1;
    wxToolBarToolBase* TBOpen;
    wxToolBarToolBase* TBPlay;
    wxToolBarToolBase* TB_Export;
    wxToolBarToolBase* TB_Rand;
    wxToolBarToolBase* TB_Save;
    wxToolBarToolBase* TB_new;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // VSLMAIN_H
