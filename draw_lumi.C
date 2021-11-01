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
  gStyle->SetPadTickY(1);
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadLeftMargin(0.1); 
  gStyle->SetPadBottomMargin(0.1);

  TCanvas *cc = new TCanvas("cc","cc",1200,600);
  cc->Range(0,0,1,1);

  float r = 0.35;

  TH2D hax("hax",";date (day/month/year);#splitline{LHC luminosity  }{(10^{33} cm^{-2} s^{-1})  }",10,t1, t2,6,0.,0.02);
  hax.GetXaxis()->SetTimeDisplay(1);
  hax.GetXaxis()->SetTimeFormat("%d/%m/%y");
  hax.GetXaxis()->SetNdivisions(-205);
  hax.GetYaxis()->SetNdivisions(-205);
  hax.GetYaxis()->SetLabelSize(0.02*(1-r)/r);
  hax.GetXaxis()->SetLabelSize(0.02*(1-r)/r);
  hax.GetXaxis()->SetTitleSize(0.02*(1-r)/r);
  hax.GetYaxis()->SetTitleSize(0.02*(1-r)/r);
  hax.GetYaxis()->SetTitleOffset(1.25);
  hax.GetXaxis()->SetTitleOffset(1.25);
  hax.GetXaxis()->SetLabelOffset(0.03);
  hax.Draw("AXIS");

  TFile fdel("del.root","RECREATE");
  TTree * lumi1=new TTree("lumi","");
  lumi1->ReadFile(LumInFile,"run/I:fill/I:time/I:nls/I:ncms/I:delivere/D:lumi/D");
  lumi1->SetMarkerStyle(7);
  lumi1->SetMarkerColor(38);
  lumi1->Draw("lumi:time",Form("time>%d && time<%d",t1, t2 ),"same");

  cc->cd();

  cc->SaveAs("/eos/user/i/ivovtin/LM_ECAL/RUN3/lumi_draw.eps");
  cc->SaveAs("/eos/user/i/ivovtin/LM_ECAL/RUN3/lumi_draw.png");
}
