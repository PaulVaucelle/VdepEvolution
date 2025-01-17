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
#include "TLatex.h"
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
 
 std::ifstream f1("./deltavfd_1.txt"); //TIB    
 std::ifstream f2("./deltavfd_2.txt");//TIB  
std::ifstream  f3("./deltavfd_3.txt");//TIB  
 std::ifstream f4("./deltavfd_4.txt");//TIB  
  std::ifstream f5("./deltavfd_11.txt");//TID
 std::ifstream f6("./deltavfd_12.txt");//TID
std::ifstream  f7("./deltavfd_13.txt");//TID
 std::ifstream f8("./deltavfd_14.txt");//TEC
 std::ifstream f9("./deltavfd_15.txt");//TEC
 std::ifstream f10("./deltavfd_16.txt");//TEC
 std::ifstream f11("./deltavfd_17.txt");//TEC
 std::ifstream f12("./deltavfd_18.txt");//TEC
std::ifstream  f13("./deltavfd_19.txt");//TEC
std::ifstream  f14("./deltavfd_20.txt");//TEC
 std::ifstream f15("./deltavfd_5.txt");//TOB
std::ifstream f16("./deltavfd_6.txt");//TOB
 std::ifstream f17("./deltavfd_7.txt");//TOB
 std::ifstream f18("./deltavfd_8.txt");//TOB
 std::ifstream f19("./deltavfd_9.txt");//TOB
std::ifstream  f20("./deltavfd_10.txt");//TOB
//ordered by sensor thickness

 
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
   pad2->SetBottomMargin(0.16);
   pad2->SetRightMargin(0.05);
   pad2->SetLeftMargin(0.15);
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

// For the axis labels:

  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.046, "XYZ");


  //--------------------------------------------------------------------------------//

  pad2->cd();
  pad2->SetFrameLineWidth(3);
     TMultiGraph *mg = new TMultiGraph();
    //  mg->SetTitle("V_{fd} Init. vs Final predicted value");
     auto gr5 = new TGraph(20);
     auto gr6 = new TGraph(20);

            gr5->SetLineColor(kRed);
       gr5->SetLineStyle(1);
       gr5->SetLineWidth(2);
       gr5->GetYaxis()->SetTitle("V_{fd}");//
       gr5->GetYaxis()->SetTitleColor(1);
      //  gr5->SetNdivisions(509,"XYZ");
       gr5->SetMinimum(1);
       gr5->SetMarkerStyle(21);
       gr5->SetMarkerSize(2);
       gr5->GetXaxis()->SetTitle(xtitle);
       gr5->SetMarkerColor(kRed);



       gr6->SetLineColor(kBlue);
       gr6->SetLineStyle(1);
       gr6->SetLineWidth(2);
       gr6->SetMarkerStyle(20);
       gr6->SetMarkerSize(2);
       gr6->SetMarkerColor(kBlue);
//    f1->cd();
/////////,"\n"
// std::string line;
double a, b;
while (f1 >> a >> b)
{
    // std::istringstream iss(line);
    
    gr5->SetPointX(0,0);
    gr5->SetPointY(0,a);
    gr6->SetPointX(0,0);
    gr6->SetPointY(0,b);

}
   
    //   f2->cd();
/////////
 
while (f2 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(1,1);
    gr5->SetPointY(1,a);
    gr6->SetPointX(1,1);
    gr6->SetPointY(1,b);

}

    //   f3->cd();
/////////
 
while (f3 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(2,2);
    gr5->SetPointY(2,a);
    gr6->SetPointX(2,2);
    gr6->SetPointY(2,b);


}

    //   f4->cd();
/////////
 
while (f4 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(3,3);
    gr5->SetPointY(3,a);
    gr6->SetPointX(3,3);
    gr6->SetPointY(3,b);


}

    //   f5->cd();
/////////
 
while (f5 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(4,4);
    gr5->SetPointY(4,a);
    gr6->SetPointX(4,4);
    gr6->SetPointY(4,b);


}

    //   f6->cd();
/////////
 
while (f6 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(5,5);
    gr5->SetPointY(5,a);
    gr6->SetPointX(5,5);
    gr6->SetPointY(5,b);


}

    //   f7->cd();
/////////
 
while (f7 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(6,6);
    gr5->SetPointY(6,a);
    gr6->SetPointX(6,6);
    gr6->SetPointY(6,b);


}

    //   f8->cd();
/////////
 
while (f8 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(7,7);
    gr5->SetPointY(7,a);
    gr6->SetPointX(7,7);
    gr6->SetPointY(7,b);


}

    //   f9->cd();
/////////
 
while (f9 >> a >> b)
{
    // // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(8,8);
    gr5->SetPointY(8,a);
    gr6->SetPointX(8,8);
    gr6->SetPointY(8,b);


}

    //   f10->cd();
/////////
 
while (f10 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(9,9);
    gr5->SetPointY(9,a);
    gr6->SetPointX(9,9);
    gr6->SetPointY(9,b);


}

    //   f11->cd();
/////////
 
while (f11 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(10,10);
    gr5->SetPointY(10,a);
    gr6->SetPointX(10,10);
    gr6->SetPointY(10,b);


}

    //   f12->cd();
/////////
 
while (f12 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(11,11);
    gr5->SetPointY(11,a);
    gr6->SetPointX(11,11);
    gr6->SetPointY(11,b);


}

    //   f13->cd();
/////////
 
while (f13 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(12,12);
    gr5->SetPointY(12,a);
    gr6->SetPointX(12,12);
    gr6->SetPointY(12,b);


}

    //   f14->cd();
/////////
 
while (f14 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(13,13);
    gr5->SetPointY(13,a);
    gr6->SetPointX(13,13);
    gr6->SetPointY(13,b);


}

    //   f15->cd();
/////////
 
while (f15 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(14,14);
    gr5->SetPointY(14,a);
    gr6->SetPointX(14,14);
    gr6->SetPointY(14,b);


}

    //   f16->cd();
/////////
 
while (f16 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(15,15);
    gr5->SetPointY(15,a);
    gr6->SetPointX(15,15);
    gr6->SetPointY(15,b);


}

    //   f17->cd();
/////////
 
while (f17 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(16,16);
    gr5->SetPointY(16,a);
    gr6->SetPointX(16,16);
    gr6->SetPointY(16,b);


}

    //   f18->cd();
/////////
 
while (f18 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(17,17);
    gr5->SetPointY(17,a);
    gr6->SetPointX(17,17);
    gr6->SetPointY(17,b);


}

    //   f19->cd();
/////////
 
while (f19 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(18,18);
    gr5->SetPointY(18,a);
    gr6->SetPointX(18,18);
    gr6->SetPointY(18,b);


}

    //   f20->cd();
/////////
 
while (f20 >> a >> b)
{
    // std::istringstream iss(line);
    // double a, b;
    // if (!(iss >> a >> b)) { break; } // error
    gr5->SetPointX(19,19);
    gr5->SetPointY(19,a);
    gr6->SetPointX(19,19);
    gr6->SetPointY(19,b);


}


///////////////////////////////////////
mg->Add(gr5);
mg->Add(gr6);




mg->Draw("AP");

   TLine *line = new TLine(0.5,50,0.5,350);
//    line->SetLineStyle(3);
// //    line->SetLineWidth(2);
//    line->Draw();
//    line = new TLine(1.5,63,1.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//    line = new TLine(2.5,63,2.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
      line = new TLine(3.5,50,3.5,350);
      line->SetLineWidth(2);
   line->SetLineStyle(2);
   line->Draw();
//       line = new TLine(4.5,63,4.5,343);
      
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(5.5,63,5.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(6.5,63,6.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(7.5,63,7.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(8.5,63,8.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
      line = new TLine(6.5,50,6.5,350);
      line->SetLineWidth(2);
   line->SetLineStyle(2);
   line->Draw();
//       line = new TLine(10.5,63,10.5,343);
         
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(11.5,63,11.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
      line = new TLine(13.5,50,13.5,350);
      line->SetLineWidth(2);
   line->SetLineStyle(2);
   line->Draw();
//       line = new TLine(13.5,63,13.5,343);
         
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(14.5,63,14.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(15.5,63,15.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(16.5,63,16.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(17.5,63,17.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(18.5,63,18.5,343);
//    line->SetLineStyle(3);
//    line->Draw();
//       line = new TLine(19,63,19,343);
//    line->SetLineStyle(3);
//    line->Draw();
// mg->SetMinimum(0.00001);

      mg->GetXaxis()->SetBinLabel(5,"TIB L1");
      mg->GetXaxis()->SetBinLabel(10,"TIB L2");
      mg->GetXaxis()->SetBinLabel(15,"TIB L3");
      mg->GetXaxis()->SetBinLabel(19,"TIB L4");
      mg->GetXaxis()->SetBinLabel(24,"TID R1");
      mg->GetXaxis()->SetBinLabel(29,"TID R2");
      mg->GetXaxis()->SetBinLabel(34,"TID R3");
      mg->GetXaxis()->SetBinLabel(38,"TEC R1");
      mg->GetXaxis()->SetBinLabel(43,"TEC R2");
      mg->GetXaxis()->SetBinLabel(48,"TEC R3");
      mg->GetXaxis()->SetBinLabel(53,"TEC R4");
      mg->GetXaxis()->SetBinLabel(58,"TEC R5");
      mg->GetXaxis()->SetBinLabel(62,"TEC R6");
      mg->GetXaxis()->SetBinLabel(67,"TEC R7");
      mg->GetXaxis()->SetBinLabel(72,"TOB L1");
      mg->GetXaxis()->SetBinLabel(77,"TOB L2");
      mg->GetXaxis()->SetBinLabel(82,"TOB L3");
      mg->GetXaxis()->SetBinLabel(86,"TOB L4");
      mg->GetXaxis()->SetBinLabel(91,"TOB L5");
      mg->GetXaxis()->SetBinLabel(96,"TOB L6");
      mg->GetXaxis()->SetLabelSize(0.05);
      mg->GetYaxis()->SetTitle("Full depletion voltage [ V ]");//
      mg->GetYaxis()->SetRangeUser(50,350);//
    
  leg = new TLegend(0.60,0.80,0.925,0.90);
//   leg->SetBorderSize(0);
//   leg->SetFillColor(0);
//   leg->SetFillStyle(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
//   leg->SetHeader("V_{fd}");
  leg->AddEntry(gr5,"Initial measured value","P");
  leg->AddEntry(gr6,"Final predicted value","P");

  leg->Draw();
//########
        TLatex *t = new TLatex(-1.,355,"CMS");
        t->SetTextFont(61);
        t->SetTextAlign(11);
        float fac = pad2->GetTopMargin();
        t->SetTextSize(0.75*fac);
        t->Draw();
 //########
        TLatex *t3 = new TLatex(1.25,355,"Simulation");
        t3->SetTextFont(52);
        t3->SetTextAlign(11);
        t3->SetTextSize(0.5*fac);
        t3->Draw();
// //########
//         TLatex *t2 = new TLatex();
//         t2->SetTextFont(52);
//         t2->SetTextAlign(11);
//         t2->SetTextSize(0.4*fac);
//         t2->DrawLatex(13.4,360,"Expected Run 3 L_{int} = 260 fb^{-1}");
 c1->Update();
 c1->SaveAs("deltaVfd_perlayer.pdf");
}
