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
 
TFile * f1 = new TFile("./VdepEvol_T_TIB_L3.root");    

 
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
   pad2->SetLeftMargin(0.10);
pad2->SetGrid(1,1);


gStyle->SetOptDate(0);
gStyle->SetPadBorderMode(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  gStyle->SetMarkerStyle(20);
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
  gStyle->SetTitleXOffset(0);
  gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(2);
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
    f1->ls();
    int nbin = 5844;
    TH1D * hVdep = new TH1D("","",nbin,0,nbin-1);
    hVdep = (TH1D*)f1->Get("T_3");
    hVdep->GetXaxis()->SetTimeDisplay(1);
    hVdep->GetXaxis()->SetTimeFormat("%m/%y%F2010-01-01 00:00:00");

    hVdep->SetTitle("");
    hVdep->GetXaxis()->SetTitleSize(0.06);
    hVdep->GetYaxis()->SetTitleSize(0.06);
    hVdep->GetXaxis()->SetLabelSize(0.0);
    hVdep->GetYaxis()->SetLabelSize(0.04);
        // hVdep->GetXaxis()->SetRangeUser(0.0);
    hVdep->GetYaxis()->SetRangeUser(-25,25);
    hVdep->GetXaxis()->SetTitleOffset(1.05);
    hVdep->SetLineColor(kBlack);
    hVdep->Draw();

// mg->SetMinimum(0.00001);
    
//   leg = new TLegend(0.8,0.72,0.90,0.88);
//   leg->SetBorderSize(0);
// //   leg->SetFillColor(0);
//   leg->SetFillStyle(0);
//   leg->SetTextFont(42);
//   leg->SetTextSize(0.04);
//   leg->SetHeader("V_{fd}");
  // leg->AddEntry(hVdep,"Init. V_{fd}","P");


  leg->Draw();
//########

           TLine *line = new TLine(415000000,-25,415000000,25);
      line->SetLineWidth(6);
   line->SetLineStyle(2);
   line->SetLineColor(kRed);
   line->Draw();

        TLatex *t = new TLatex(-0.15,26,"CMS");
        t->SetTextFont(61);
        t->SetTextAlign(11);
        float fac = pad2->GetTopMargin();
        t->SetTextSize(0.75*fac);
        t->Draw();
//########
        // TLatex *t2 = new TLatex();
        // t2->SetTextFont(52);
        // t2->SetTextAlign(11);
        // t2->SetTextSize(0.3*fac);
        // t2->DrawLatex(410000000,26,"Exp. Run 3 L_{int} = 300 fb^{-1}");
  //########

                TLatex *t3 = new TLatex(57500000,26,"Preliminary");
        t3->SetTextFont(52);
        t3->SetTextAlign(11);
        t3->SetTextSize(0.5*fac);
        t3->Draw();

  //########

                TLatex *t5 = new TLatex(-20000000,-29,"01/10    01/12    01/14    01/16    01/18    01/20    01/22    01/24    01/26");
        t5->SetTextFont(42);
        t5->SetTextAlign(1);
        t5->SetTextSize(0.6*fac);
        t5->Draw();

 c1->Update();
 c1->SaveAs("Temp_History.pdf");
}
