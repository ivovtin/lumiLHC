#include "TFile.h"
#include "TDirectoryFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TF1.h"
#include "TNtuple.h"
#include "TString.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"

#include <iostream>

//void draw_lumi(Int_t t1=1633063232, Int_t t2=1635741632, TString LumInFile="lum.csv")
void draw_lumi(Int_t t1=0, Int_t t2=0, TString LumInFile="lum0.csv")
{
  gStyle->SetTimeOffset(0);
  gStyle->SetOptStat(0);

  TCanvas *cc = new TCanvas("cc","cc",1200,900);
  cc->Range(0,0,1,1);

  float r = 0.35;
  float epsilon = 0.02;

  TPad PadLum("Pad1", "Pad1", 0., 0., 1., r*(1-epsilon) );
  PadLum.cd();
  gPad->SetTicky();
  gPad->SetGridx();
  gPad->SetGridy();

  PadLum.SetTopMargin(0);
  PadLum.SetBottomMargin(0.2);
  PadLum.Draw();
  PadLum.cd();

  TH2D hax("hax",";date (day/month/year);#splitline{LHC luminosity  }{(10^{33} cm^{-2} s^{-1})  }",10,t1, t2,6,0.,0.02);
  hax.GetXaxis()->SetTimeDisplay(1);
  hax.GetXaxis()->SetTimeFormat("%d/%m/%y");
  hax.GetXaxis()->SetNdivisions(-205);
  hax.GetYaxis()->SetNdivisions(-205);
  hax.GetYaxis()->SetLabelSize(0.04*(1-r)/r);
  hax.GetXaxis()->SetLabelSize(0.04*(1-r)/r);
  hax.GetXaxis()->SetTitleSize(0.04*(1-r)/r);
  hax.GetYaxis()->SetTitleSize(0.04*(1-r)/r);
  hax.GetYaxis()->SetTitleOffset(0.5);
  hax.GetXaxis()->SetTitleOffset(1.3);
  hax.GetXaxis()->SetLabelOffset(0.03);
  hax.Draw("AXIS");

  TFile fdel("del.root","RECREATE");
  TTree * lumi1=new TTree("lumi","");
  lumi1->ReadFile(LumInFile,"run/I:fill/I:time/I:nls/I:ncms/I:delivere/D:lumi/D");
  lumi1->SetMarkerStyle(7);
  lumi1->SetMarkerColor(38);
  lumi1->Draw("lumi:time",Form("time>%d && time<%d",t1, t2 ),"same");

  PadLum.Update();
  PadLum.Modified();
  cc->cd();

  PadLum.SaveAs("/eos/user/i/ivovtin/LM_ECAL/RUN3/lumi_draw.eps");
  //PadLum.SaveAs("/eos/user/i/ivovtin/LM_ECAL/RUN3/lumi_draw.png");
}
