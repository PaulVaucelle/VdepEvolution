#include <iostream>
#include <TROOT.h>
#include "TVectorD.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TEfficiency.h" 
#include "TMath.h" 
#include "TMultiGraph.h"
#include "TLine.h"
#include "TMathText.h"

#include <iostream>
#include <time.h>
#include <sstream>
#include <fstream>
void plot()//std::vector<string> SampleList or string plot
{

    // if (SampleList.size()==0)
    //     {
    //         std::cout<<"Please, select samples to analyse and make sure they are all up to date"
    //     }
//  TFile *f1, *f2, *f3, *f4, *f5, *f6, *f7, *f8, *f9, *f10, *f11, *f12, *f13, *f14, *f15, *f16, *f17, *f18, *f19, *f20;
 
 TFile * f1 = new TFile("./lumigr_TIB_L1.root");     

 
int stati=0;
bool fit= 0;
bool logy=0;

 TLegend* leg;

// NNormalized or NXSNormalized
 TString xtitle = "Value"; 
 TString ytitle = "efficiency"; 
 int color13 = kRed+2;
int color14 = kGreen-5;
int color15 = kYellow-3;
int color16 = kYellow-7;

int color17 = kRed+4;
int color18 = kViolet;
int color19 = kViolet-5;
// *****************************************************************************

// TCanvas *c1 = new TCanvas("c1", "plots",200,0,900,500);
TCanvas *c1 = new TCanvas("c1", "plots",200,0,1500,1000);
c1->SetFillColor(10);
c1->SetFillStyle(4000);
c1->SetBorderSize(2);


TPad* pad2 = new TPad("pad2","This is pad2",0.05,0.05,0.98,0.98,21);
pad2->SetFillColor(0);
pad2->SetBorderMode(0);
pad2->SetFrameFillColor(10);
pad2->Draw();
pad2->SetLogy(0);
   pad2->SetTopMargin(0.08);
   pad2->SetBottomMargin(0.15);
   pad2->SetRightMargin(0.05);
   pad2->SetLeftMargin(0.15);
// pad2->SetGrid(1,1);


gStyle->SetOptDate(0);
gStyle->SetPadBorderMode(0);
  // gStyle->SetGridStyle(3);
  // gStyle->SetGridWidth(1);
  // gStyle->SetMarkerStyle(20);
gStyle->SetStatColor(0);
gStyle->SetTitleFont(62);
gStyle->SetTitleColor(1);
gStyle->SetTitleTextColor(1);
gStyle->SetTitleFillColor(10);
gStyle->SetTitleFontSize(0.04);
gStyle->SetTitleW(0.4);
gStyle->SetTitleH(0.09);
// gStyle->SetTitleX(0); // Set the position of the title box
// gStyle->SetTitleY(0.985); // Set the position of the title box
// gStyle->SetTitleStyle(Style_t style = 1001);
// gStyle->SetTitleBorderSize(2);
gStyle->SetOptStat(stati);
gStyle->SetPadTickX(1); gStyle->SetPadTickY(1);
// gStyle->SetPadGridX(true); gStyle->SetPadGridY(true);

// For the axis titles:

  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);

  gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(2);
  gStyle->SetTitleXOffset(0);
  gStyle->SetTitleYOffset(0);


  gStyle->SetTitleColor(1, "XYZ");
  gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.08, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);

// For the axis labels:

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.05, "XYZ");


  //--------------------------------------------------------------------------------//

  pad2->cd();
  pad2->SetFrameLineWidth(3);
    // f1->cd();
    // f1->ls();
    const int nbin = 5844;
    TGraph * hVdep = new TGraph(nbin);
    hVdep = (TGraph*)f1->Get("lumigr_TIB_L1");
    // hVdep->GetXaxis()->SetTimeDisplay(1);
    // hVdep->GetXaxis()->SetTimeFormat("%d/%m/%y%F2010-01-01 00:00:00");

    hVdep->SetTitle("");
    hVdep->GetXaxis()->SetTitleSize(0.06);
    hVdep->GetYaxis()->SetTitleSize(0.06);
    hVdep->GetXaxis()->SetLabelSize(0.04);
    hVdep->GetYaxis()->SetLabelSize(0.04);
    hVdep->GetHistogram()->GetXaxis()->SetTitleOffset(1.01);
    hVdep->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    hVdep->SetLineColor(kBlack);
    hVdep->Draw();

// mg->SetMinimum(0.00001);


//    leg = new TLegend(0.17,0.81,0.50,0.89);
// //   leg->SetBorderSize(0);
// // //   leg->SetFillColor(0);
// //   leg->SetFillStyle(0);
//    leg->SetTextFont(42);
//   leg->SetTextSize(0.04);
//   leg->SetHeader("Expected Run 3 L_{int} = 260 fb^{-1}");
//   // leg->AddEntry(hVdep,"Init. V_{fd}","P");
//   leg->Draw();
//########

           TLine *line = new TLine(397,0,397,350);
      line->SetLineWidth(6);
   line->SetLineStyle(2);
   line->SetLineColor(kRed);
   line->Draw();

        TLatex *t = new TLatex(-0.15,355,"CMS");
        t->SetTextFont(61);
        t->SetTextAlign(11);
        float fac = pad2->GetTopMargin();
        t->SetTextSize(0.75*fac);
        t->Draw();
// ########
       TLatex *t2 = new TLatex();
       t2->SetTextFont(52);
       t2->SetTextAlign(11);
       t2->SetTextSize(0.5*fac);
       t2->DrawLatex(18,310,"Expected L_{int}^{2025+2026} = 150 fb^{-1}");
  // ########

        TLatex *t3 = new TLatex(70,355,"Simulation");
        t3->SetTextFont(52);
        t3->SetTextAlign(11);
        t3->SetTextSize(0.5*fac);
        t3->Draw();
  //########

                TLatex *t4 = new TLatex(373,355,"Tracker Inner Barrel Layer 1");
        t4->SetTextFont(42);
        t4->SetTextAlign(11);
        t4->SetTextSize(0.5*fac);
        t4->Draw();

        TLatex *t6 = new TLatex();
        t6->SetTextFont(52);
        // t2->SetTextAlign(11);
        t6->SetTextAngle(90);
        t6->SetTextSize(0.4*fac);
        t6->SetTextColor(kRed);
        t6->DrawLatex(420,120,"Predictions");

 c1->Update();
 c1->SaveAs("VdepIntLumi_v2.pdf");
}
