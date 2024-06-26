// Tell emacs that this is a C++ source
//  -*- C++ -*-.
#ifndef SMDHISTGEN_H
#define SMDHISTGEN_H

#include <fun4all/SubsysReco.h>

#include <string>
#include <vector>

class PHCompositeNode;
class TFile;
class TTree;
class TH1;
class TH2;
class TGraphErrors;
class Packet;
class CaloWaveformFitting;

class SmdHistGen : public SubsysReco
{
 public:

  SmdHistGen(const std::string &name = "SmdHistGen", const char* outname = "SmdHists.root");

  ~SmdHistGen() override;

  /** Called during initialization.
      Typically this is where you can book histograms, and e.g.
      register them to Fun4AllServer (so they can be output to file
      using Fun4AllServer::dumpHistos() method).
   */
  int Init(PHCompositeNode *topNode) override;

  /** Called for first event when run number is known.
      Typically this is where you may want to fetch data from
      database, because you know the run number. A place
      to book histograms which have to know the run number.
   */
  int InitRun(PHCompositeNode *topNode) override;

  /** Called for each event.
      This is where you do the real work.
   */
  int process_event(PHCompositeNode *topNode) override;

  /// Clean up internals after each event.
  int ResetEvent(PHCompositeNode *topNode) override;

  /// Called at the end of each run.
  int EndRun(const int runnumber) override;

  /// Called at the end of all processing.
  int End(PHCompositeNode *topNode) override;

  /// Reset
  int Reset(PHCompositeNode * /*topNode*/) override;

  void Print(const std::string &what = "ALL") const override;

 private:
  const char* outfilename;
  TFile *outfile;
  int evtctr = 0;

  std::vector<float> anaWaveformFast(Packet *p, const int channel);
  void CompSmdAdc();
  void CompSmdPos();
  void CompSumSmd();
  void CompZdcAdc();
  void CountLRUD();
  void CompAsym();
  CaloWaveformFitting *WaveformProcessingFast = nullptr;

  double PI = 3.14159;
  // packet id numbers
  const int packet_GL1 = 14001;
  const int packet_blue = 14902;
  const int packet_yellow = 14903;
  const int packet_smd = 12001;
  // smd
  // north smd
  TH1 *smd_hor_north = nullptr;
  TH1 *smd_ver_north = nullptr;
  TH1 *smd_sum_hor_north = nullptr;
  TH1 *smd_sum_ver_north = nullptr;
  // south smd 
  TH1 *smd_hor_south = nullptr;
  TH1 *smd_ver_south = nullptr;
  TH1 *smd_sum_hor_south = nullptr;
  TH1 *smd_sum_ver_south = nullptr;
  // smd hit 2D positions
  TH2 *smd_xy_north = nullptr;
  TH2 *smd_xy_south = nullptr;
  // asymmetries
  TGraphErrors *asymLR_north = nullptr;
  TGraphErrors *asymUD_north = nullptr;
  TGraphErrors *asym_north = nullptr;
  TGraphErrors *asymLR_south = nullptr;
  TGraphErrors *asymUD_south = nullptr;
  TGraphErrors *asym_south = nullptr;

  int spinPatternBlue[120] = {0};
  int spinPatternYellow[120] = {0};
  int bunchNum = 0;
  int Nleft_north = 0;
  int Nright_north = 0;
  int Nup_north = 0;
  int Ndown_north = 0;
  int Nleft_south = 0;
  int Nright_south = 0;
  int Nup_south = 0;
  int Ndown_south = 0;
  float asym_LR_north = 0.0;
  float asym_UD_north = 0.0;
  float asym_LR_south = 0.0;
  float asym_UD_south = 0.0;
  float asym_LR_north_err = 0.0;
  float asym_UD_north_err = 0.0;
  float asym_LR_south_err = 0.0;
  float asym_UD_south_err = 0.0;

  float smd_adc[32] = {0.0f};
  float zdc_adc[16] = {0.0f};
  float smd_sum[4] = {0.0f}; 
  float smd_pos[4] = {0.0f};

  float gain[32] = {0.0f};
  float smd_south_rgain[16] = {0.0f};
  float smd_north_rgain[16] = {0.0f};
  float overflow0[40] = {0.0f};
  float overflow1[40] = {0.0f};

};

#endif // SMDHISTGEN_H
