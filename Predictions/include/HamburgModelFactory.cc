#include "HamburgModelFactory.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraph.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
// #include "tdrstyle.C"
// #include "../CMS_lumi.C"
#include <fstream>
#include <sstream>
#include <vector>
#include "TLatex.h"
#include "TPaveText.h"
#include "TLine.h"


// set input tree reading
//------------------------

void HamburgModelFactory::setGlobalTree(std::string filename="GlobalTree.root"){

    fin = new TFile(filename.c_str());
    tree = (TTree*) fin->Get("globaltree");
    
    tree->SetBranchAddress("Partition",&partition);
    tree->SetBranchAddress("Struct",&struc);
    tree->SetBranchAddress("StructPos",&structpos);
    tree->SetBranchAddress("DETID",&detid);
    tree->SetBranchAddress("X",&x);
    tree->SetBranchAddress("Y",&y);
    tree->SetBranchAddress("Z",&z);
    tree->SetBranchAddress("L",&l);
    tree->SetBranchAddress("W1",&w1);
    tree->SetBranchAddress("D",&d);
    tree->SetBranchAddress("W2",&w2);
    
    tree->SetBranchAddress("PG",pg);
    tree->SetBranchAddress("CHANNEL",&channel);
    tree->SetBranchAddress("PGINDEX",&pgindex);
    tree->SetBranchAddress("NOMODULES",&nomod);
    
    //tree->SetBranchAddress("fluence",&fluence);
    //tree->SetBranchAddress("fluence_err",&fluenceerror);
    tree->SetBranchAddress("fluence_3500TeV",&fluence_3500TeV);
    tree->SetBranchAddress("fluence_3500TeV_err",&fluenceerror_3500TeV);
    tree->SetBranchAddress("fluence_7000TeV",&fluence_7000TeV);
    tree->SetBranchAddress("fluence_7000TeV_err",&fluenceerror_7000TeV);
    tree->SetBranchAddress("Temp",&temp);
    tree->SetBranchAddress("VDEP", &ini_vdep);
    tree->SetBranchAddress("DTDP",&dtdp);
    tree->SetBranchAddress("IniIleak", &ini_leak);
    
    nentries = tree->GetEntries();
    
    return;

}



// Read lumi/temperature scenario
//-------------------------------

void HamburgModelFactory::readLumiTempScenario(std::string filename="realistic_scenario_step1day_repl.txt"){

    Int_t nper=0;
    
    Int_t step, stepInYear;
    Float_t sqrtS, lumi;
    Float_t temperature, LVfraction, HVfraction;
    std::string def, var;
    
    std::ifstream lumifile;
    std::string line;
    lumifile.open(filename.c_str());
    if (lumifile.is_open()) {
        std::cout<<"Reading file : "<<filename<<std::endl;
        while ( getline (lumifile,line) )
        {
            std::istringstream iss(line);
            if (!(iss >> step >> stepInYear >> sqrtS >> lumi >> temperature >> LVfraction >> HVfraction)) {
                
                // Check if a variable is set
                std::istringstream iss2(line);
                if((iss2 >> def >> var >> step) && def=="#define"){
                    std::cout<<" Defining: "<<var<<" : "<<step<<std::endl;
                    std::cout<<" ----------------------- "<<std::endl;
                    if(var=="StepInDays") periodInDays=step;
                }
                else continue;
            }
            StepInYear.push_back(stepInYear);
            SqrtS.push_back(sqrtS);
            Lumi.push_back(lumi);
            
            Temp.push_back(temperature);
            if(lumi>0 or LVfraction>0.5) Active.push_back(1);
            else Active.push_back(0);
            nper++;
        }
        lumifile.close();
    }
    else std::cerr<<"File '"<<filename<<"' not available."<<std::endl;
    
    Nperiods=nper;
    std::cout<<" "<<Nperiods<<" periods found"<<std::endl;
    
    // initialize containers
    for(unsigned int i=0; i<Nperiods; i++){
        Feq.push_back(0);
        Temp_evol.push_back(0);
        I_leak.push_back(0);
        Na.push_back(0);
        NY.push_back(0);
        Nc.push_back(0);
        N.push_back(0);
        U.push_back(0);
    }
    
    return;
}



// Loop over time steps
//---------------------

void HamburgModelFactory::simulateSensorEvolution(int detid_){

    // clear and initialize containers
    for (Int_t i = 0; i< Nperiods; i++) {
        // fluence
        if(SqrtS[i]-0.9<0.01) Feq[i] = fluence_3500TeV * 5.3e13 * Lumi[i]; // https://cds.cern.ch/record/2800515/files/pos.ICRC2019.207.pdf
        if(SqrtS[i]==7) Feq[i] = fluence_3500TeV * 7.35e13 * Lumi[i];
        //if(SqrtS[i]==13) Feq[i] *= 8.0/7.35; // scaling factor between 7TeV and 13TeV pp cross section
        if(SqrtS[i]==8) Feq[i] = fluence_3500TeV * 7.47e13 * Lumi[i];
        if(SqrtS[i]==13 || SqrtS[i]-13.6<0.01) Feq[i] = fluence_7000TeV * 8.0e13 * Lumi[i];
        // temperature
        Temp_evol[i] = ZeroC + Temp[i];
        if(Active[i]) Temp_evol[i] += temp-4; // temp: from temperature mapping from Run1
        // initial i_leak
        I_leak[i]=ini_leak/1000*LeakCorrection(293.15, ZeroC+temp); // A
        // charge carriets concentration
        Na[i]=0;
        NY[i]=0;
        Nc[i]=0;
        intLumi.clear();
        intFeq.clear();
    }
    
    
    // sensor geometry
    Double_t volume = l*(w1+w2)/2*d*100*100*100;
    Double_t pitch = 120e-4;
    Int_t subdet = ((detid_ >> subdetoffset_) & subdetmask_);
    Int_t position;
    if(subdet==3) //TIB
    {
        position = ((detid_ >> layerstartbit_) & layermask_);
        (position < 3) ? (pitch=80e-4) : (pitch=120e-4);
    }
    if(subdet==4) pitch = 120e-4; // TID
    if(subdet==5) //TOB
    {
        position = ((detid_>> layerstartbit_) & layermask_);
        (position < 5) ? (pitch=183e-4) : (pitch=122e-4);
    }
    if(subdet==6){ //TEC
        position = ((detid_ >> tecringoffset_) & tecringmask_);
        (position < 4) ? (pitch = 120e-4) : (pitch = 163e-4);
    }

// #define tecringoffset_   5
// #define subdetoffset_   25
// #define layerstartbit_  14
// #define tecringmask_   0x7
// #define subdetmask_    0x7
// #define layermask_     0x7


//     ((detId>>25)&0x7) == 6 [Selecting the TEC] and ((detId>>14)&0xF) == 9
// [Selecting the wheel] and ((detId >> 5) & 7) == 5 [selecting the ring]
    
    // Ileak
    Double_t alpha1, alpha2, alpha3, delIleak;
    
    // Vdep
    TF1 * fff = new TF1("fff","-0.00111/(x*x)+0.0586/x+0.240-0.651*x+0.355*x*x");
    Double_t w2p = 0.25;
    Double_t Ufd_diode = ini_vdep / (1.+2.*pitch/(d*100)*fff->Eval(w2p));
    Double_t Neff0 = Ufd_diode * 2. * eps * eps0 / q_el / (d*d*10000); // initial Neff
    std::cout<<" Neff corr: "<<(1. + 2.*pitch/(d*100)*fff->Eval(w2p))<<std::endl;
    
    Double_t Na_temp, NY_temp;
    Double_t temperature;
    
    Int_t counter=1;
    Float_t total_Lumi=0;
    Float_t total_Feq=0;
    
    // Container for Ileak contributions from each previous time periods
    std::vector< std::vector<double> > A1;
    std::vector< std::vector<double> > A2;
    std::vector< std::vector<double> > A3;

    //----------------------
    int TempAlgo = 1; // 1 from Christian
    bool SelfHeating = true; // true in Christian's code
    //----------------------
    
    // Loop over periods for ILEAK
    for(Int_t i = 0; i<Nperiods; i++){
        
        // integrated lumi
        total_Lumi += Lumi[i];
        intLumi.push_back(total_Lumi);
        // integrated fluence
        total_Feq += Feq[i];
        intFeq.push_back(total_Feq);
        
        //std::cout<<i<<" Feq: "<<Feq[i]<<" temp: "<<Temp_evol[i]<<std::endl;

        alpha1 = a10;
        alpha2 = I_a2(Temp_evol[i]); // Term with no annealing, use temperature in the time period
        alpha3 = I_a3(1,periodInDays);

        // Annealing: consider a flash irradiation at beginning of the period
        // Update leakage current in current and future periods
        // Update consequent temperature increase
        
        if(TempAlgo==1) // Christian's algorithm
        {
            // Loop on current and next periods to compute contributions with annealing
            for(Int_t j=i; j<Nperiods; j++){ /// Start from i : compute leakage current for the end of the period i
                
                alpha1 *= I_a1(Temp_evol[j], 1, periodInDays); /// *= is equivalent to add the additionnal time period in the exponential. Takes into account the temperature in the current time period (can be different than the one at the time of the irradiation)
                
                //use lowest value from current and previous periods
                if(I_a2(Temp_evol[j])<alpha2) alpha2 = I_a2(Temp_evol[j]);  /// intercept (t=0) is temperature dependent ; can only decrease
                    
                alpha3 = I_a3(j-i+1, periodInDays);
                delIleak = (alpha1+alpha2+alpha3)*Feq[i]*volume*1000;
                
                //std::cout<<" "<<j<<" "<<alpha1<<" "<<alpha2<<" "<<alpha3<<std::endl;
                //std::cout<<" "<<j<<" "<<Feq[i]<<" "<<Temp_evol[j]<<" "<<delIleak<<std::endl;
                
                // if active: update the temperature for the increase due to the new leakage current increase (take only into account leakage current contributions already computed)
                if(SelfHeating && Active[j]){
                    temperature = Temp_evol[j];
                    int status = Ileak_Cavity(delIleak, temperature, dtdp, I_leak[j]);
                    if(!status) {
                        std::cout<<"Limit with temp: "<<temperature<<" for period "<<j<<" "<<Lumi[j]<<" "<<total_Lumi<<" "<<Feq[j]<<" "<<Temp_evol[j]<<std::endl;
                        I_leak[j] = -1;//-10
                        break;
                    }
                    Temp_evol[j] = temperature; // update of the temperature due to the level of I_leak
                }
                
                I_leak[j]+=delIleak; //in mA per module
                
            }
        }
        else // alternative algo. Take into account summed Ileak for computing increased temperature
        {
            // Container preparation
            A1.push_back( std::vector<double>(i+1, 0) );
            A2.push_back( std::vector<double>(i+1, 0) );
            A3.push_back( std::vector<double>(i+1, 0) );
            
            //  Current contribution:
            Double_t I_a2_i = I_a2(Temp_evol[i]);
            A1[i][0] = a10 * I_a1(Temp_evol[i], 1, periodInDays);
            A2[i][0] = I_a2_i;
            A3[i][0] = I_a3(1, periodInDays);
             
            // Loop on time previous periods to update their contribution with annealing (using current temperature)
            // in A[i][j]  j=0 is current one, j=1 is previous one, ...
            if(i>0)
            for(Int_t j=1; j<=i; j++){
                A1[i][j] = A1[i-1][j-1] * I_a1(Temp_evol[i], 1, periodInDays);
                A2[i][j] = A2[i-1][j-1];
                if(I_a2_i < A2[i][j]) A2[i][j] = I_a2_i;
                A3[i][j] = I_a3(j+1, periodInDays);
            }
            
            /*std::cout<<"A1 "<<std::endl;
            for(Int_t j=0; j<=i; j++){
                for(Int_t k=0; k<=j; k++) std::cout<<" "<<A1[j][k];
                std::cout<<std::endl;
            }*/

            // Sum contributions from previous periods
            alpha1=0;
            alpha2=0;
            alpha3=0;
            for(Int_t j=0; j<=i; j++){
                alpha1 += A1[i][j]*Feq[i-j]; // take into account fluence at that time
                alpha2 += A2[i][j]*Feq[i-j];
                alpha3 += A3[i][j]*Feq[i-j];
            }
            delIleak = (alpha1+alpha2+alpha3)*volume*1000;
            //std::cout<<" "<<i<<" "<<alpha1<<" "<<alpha2<<" "<<alpha3<<" "<<delIleak<<std::endl;

            // Update temperature
            if(SelfHeating && Active[i]){
                temperature = Temp_evol[i];
                int status = Ileak_Cavity(delIleak, temperature, dtdp, 0);
                if(!status) {
                    std::cout<<"Limit with temp: "<<temperature<<" for period "<<i<<" "<<Lumi[i]<<" "<<total_Lumi<<" "<<Feq[i]<<" "<<Temp_evol[i]<<std::endl;
                    I_leak[i] = -1;//-10
                    break;
                }
                
                // Update of the temperature due to the level of I_leak
                // Not taken into account for I_leak annealing here, but for Vdep below.
                Temp_evol[i] = temperature;
                
            }

            I_leak[i]+=delIleak; //in mA per module
        }
            
        //std::cout<<i<<" "<<I_leak[i]<<std::endl;
        //if(!Active[i]) I_leak[i]=0;
        if(!SqrtS[i]) I_leak[i]=0;
    } //end loop over periods ILEAK
    
        
    // Loop over periods for VDEP
    for(Int_t i = 0; i<Nperiods; i++){
            
        Nc[i] = -N_stable(Neff0, intFeq[i]);
        Na_temp = ga * Feq[i];
        NY_temp = 1;
        // annealing
        for(Int_t j=i; j<Nperiods; j++){
            Na_temp = N_short(1., Temp_evol[j], Na_temp, periodInDays);
            Na[j] += -Na_temp;
            NY_temp *= N_reverse2(1., Temp_evol[j], periodInDays);
            NY[j] += -gY * Feq[i] *(1.-NY_temp);
        }
        //std::cout<<i<<" "<<Neff0<<" "<<Nc[i]<<" "<<Na[i]<<" "<<NY[i]<<std::endl;
        //std::cout<<i<<" "<<Nc[i]<<" "<<Na[i]<<" "<<NY[i]<<std::endl;
        
        // filling Neff and full depletion voltage
        N[i] = Neff0 + Nc[i] + Na[i] + NY[i];
        U[i] = (1. + 2.*pitch/(d*100)*fff->Eval(w2p))*fabs(N[i])*(d*d*10000)*q_el/ (2. * eps * eps0);
        
    } //end loop over periods VDEP
    
    std::cout << " total Feq " << total_Feq << std::endl;
    
}


// Fill, draw and save plots
//---------------------------

void HamburgModelFactory::drawSaveSensorSimu(bool print_plots=false){
    
    // Could decide to average over periods
    
    Int_t maxTime = Nperiods;
    fout->cd();
    
    // Module temperature & Ileak
    TH1D * h_T = new TH1D("h_T","Module Temperature",maxTime,0.5, maxTime+0.5);
    TH1D * h_I_leak = new TH1D("I_leak","Leakage Current (not corrected)", maxTime,0.5, maxTime+0.5);
    TH1D * h_I_leak_corr = new TH1D("I_leak_corr","Leakage Current", maxTime,0., periodInDays*24.*60.*60.*maxTime);
    
    // Vdep related plots
    TH1D * h_Nc = new TH1D("Nc","Stable Damage",maxTime,0.5,maxTime+0.5);
    TH1D * h_Na = new TH1D("Na","Short Term Annealing",maxTime,0.5,maxTime+0.5);
    TH1D * h_NY = new TH1D("NY","Reverse Annealing",maxTime,0.5,maxTime+0.5);
    TH1D * h_N = new TH1D("N","Neff",maxTime,0.5,maxTime+0.5);
    TH1D * h_U = new TH1D("U","V_dep",maxTime,0.,periodInDays*24.*60.*60.*maxTime);
    
    TGraph * lumigr = new TGraph(maxTime);
    TGraph * feqgr = new TGraph(maxTime);
    TGraph * timegr = new TGraph();

    TGraph * Vdep_0v1 = new TGraph();
    std::ofstream ofs ("./deltavfd_"+std::to_string(detid)+".txt", std::ofstream::out);
    
    TGraph *DeltaVdep = new TGraph(maxTime);
    // std::ofstream StoreVinit ("./Vinit_"+std::to_string(detid)+".txt", std::ofstream::out);
    for(Int_t i = 0; i<Nperiods; i++){
        
        //if(i>200) std::cout << i+1 <<" "<<Temp_evol[i]<<" "<<I_leak[i]<<std::endl;
        h_T->SetBinContent(i+1, Temp_evol[i]);
        h_I_leak->SetBinContent(i+1, I_leak[i]);
        h_I_leak_corr->SetBinContent(i+1,I_leak[i]*LeakCorrection(Temp_evol[i], ZeroC+20));
        
        h_Nc->SetBinContent(i+1, Nc[i]);
        h_Na->SetBinContent(i+1, Na[i]);
        h_NY->SetBinContent(i+1, NY[i]);
        h_N->SetBinContent(i+1, N[i]);
        if (debug && (i%100 == 0)) std::cout << "     U " << U[i] << std::endl;
        h_U->SetBinContent(i+1, U[i]);
        
        DeltaVdep->SetPoint(i, intLumi[i], U[i]-U[0]);
        lumigr->SetPoint(i, intLumi[i], U[i]);
        feqgr->SetPoint(i, intFeq[i], U[i]);
        timegr->SetPoint(i, (i+1)*periodInDays-5736, U[i]);
        if(i==Nperiods-1) std::cout << " total Feq " << intFeq[i] << std::endl;

    }
    ofs << U[0] << " " << U[Nperiods-1]<<std::endl;
    //StoreVinit <<U[0]<<std::endl;
    Vdep_0v1->SetPoint(0,0,U[0]);
    Vdep_0v1->SetPoint(Nperiods-1,0,U[Nperiods-1]);
    
    //gStyle->SetTitleX(0.1f);
    //gStyle->SetTitleW(0.8f);
    gStyle->SetLineColor(kWhite);
    gStyle->SetOptStat(0);
    	    gStyle->SetPadTickX(1);//$$$$$$$  // To get tick marks on the opposite side of the frame
        gStyle->SetPadTickY(1);//$$$$$$$

          gStyle->SetTitleFont(42, "XYZ");
  gStyle->SetTitleSize(0.06, "XYZ");
  gStyle->SetTitleXOffset(0.7);
  gStyle->SetTitleYOffset(0.7);
  gStyle->SetLabelColor(1, "XYZ");
  gStyle->SetLabelFont(42, "XYZ");
  gStyle->SetLabelOffset(0.007, "XYZ");
  gStyle->SetLabelSize(0.035, "XYZ");
  gStyle->SetCanvasDefH(800); //Height of canvas
   gStyle->SetLineWidth(4);
//   gStyle->SetTitleSize(10,"X");
//    gStyle->SetTitleSize(10,"Y");
  gStyle->SetCanvasDefW(1350); //Width of canvas
    TCanvas * c1 = new TCanvas();
    TString title, name;
    if(print_plots) {

        /*        c1->cd();
         //	title.Form("#splitline{Temperature profile}{PG: %s, DETID: %i}", pg, detid);
         title.Form("Temperature (%s, DETID: %i)", pg, detid);
         h_T_years->SetTitle(title);
         h_T_years->GetXaxis()->SetTimeDisplay(1);
         h_T_years->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
         h_T_years->GetXaxis()->SetTitle("Time");
         h_T_years->GetYaxis()->SetTitle("Temperature (#circC)");
         h_T_years->GetYaxis()->SetTitleOffset(1.2);
         h_T_years->DrawCopy();
         name.Form("VdepEvol_T_mod_%s%i.png", pg, detid);
         c1->SaveAs(name);*/
        
        	if (detid<=4)
    		{

                        TCanvas * c2 = new TCanvas();
        c2->cd();

        title.Form("Module temperature (%s, DETID: %i)", "TIB_L" , detid);
        // h_T->SetTitle(title);
        h_T->SetLineColor(kBlack);
        h_T->GetXaxis()->SetTitle("Time (steps)");
        h_T->GetYaxis()->SetTitle("Temperature (#circK)");
        h_T->DrawCopy();
        name.Form("VdepEvol_T_%s%i.root", "TIB_L", detid);
        
        // c2->SaveAs(name);
	h_T->SetLabelOffset(0.007,"Y");
        h_T->SetName(Form("T_%i", detid));
        h_T->Write();
        h_T->SaveAs(name);
        
        TCanvas * c3 = new TCanvas();
        c3->cd();
	//setTDRStyle();
        title.Form("Corrected leakage current (%s, DETID: %i)", "TIB_L", detid);
        // h_I_leak_corr->SetTitle(title);
        h_I_leak_corr->SetLineColor(kBlack);
        h_I_leak_corr->GetXaxis()->SetTimeDisplay(1);
        h_I_leak_corr->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_I_leak_corr->GetXaxis()->SetTitle("Time");
        h_I_leak_corr->GetYaxis()->SetTitle("Leakage current [mA]");
        h_I_leak_corr->DrawCopy();
        name.Form("VdepEvol_Ileak_%s%i.png", "TIB_L", detid);
       
        //t->Draw();
        c3->SaveAs(name);
        h_I_leak_corr->SetName(Form("Ileak_%i", detid));
        h_I_leak_corr->Write();
        
        
        TCanvas * c4 = new TCanvas();
        c4->cd();
			title.Form("Full depletion voltage (%s%i)", "TIB_L", detid);


        h_U->SetLineColor(kBlack);
        h_U->SetLineWidth(4);
        h_U->GetXaxis()->SetTitle("Time");
        h_U->GetYaxis()->SetTitle("Full depletion voltage [ V ]");
        h_U->GetYaxis()->SetRangeUser(0,350);

    
        h_U->DrawCopy();

        name.Form("VdepEvol_Vdep_%s%i.root", "TIB_L", detid);

        
        //t->Draw();
        if (detid == 1){h_U->SaveAs("Vdep_L1.root");h_U->SaveAs("Vdep_L1.c");}
        
        h_U->SetName(Form("Vdep_%i", detid));
        h_U->Write();
                 TLine *line = new TLine(10,65,10,350);
        line->SetLineStyle(3);
        line->Draw();
        c4->SaveAs(name);


                TCanvas * c5 = new TCanvas();
        c5->cd();




        title.Form("Effective space charge (%s, DETID: %i)", "TIB_L", detid);
        // h_N->SetTitle(title);
        //	h_N->GetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        h_Nc->SetLineColor(kBlue);
        h_Nc->DrawCopy("SAME");
        h_Na->SetLineColor(kGreen);
        h_Na->DrawCopy("SAME");
        h_NY->SetLineColor(kRed);
        h_NY->DrawCopy("SAME");
        name.Form("VdepEvol_Ncontrib_%s%i.png", "TIB_L", detid);
               
        //t->Draw();
        c5->SaveAs(name);
        h_N->SetName(Form("N_%i", detid));
        h_N->Write();
        h_Nc->SetName(Form("Nc_%i", detid));
        h_Nc->Write();
        h_Na->SetName(Form("Na_%i", detid));
        h_Na->Write();
        h_NY->SetName(Form("NY_%i", detid));
        h_NY->Write();
        
        
        c5->cd();
        title.Form("Effective space charge contributions (%s, DETID: %i)", "TIB_L", detid);
        // h_N->SetTitle(title);
        //	h_N-dGetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time [steps]");
        h_N->GetYaxis()->SetTitle("Effective space charge [cm-3]");
        h_N->DrawCopy();
        name.Form("VdepEvol_Neff_%s%i.png", "TIB_L", detid);
              
        //t->Draw();
        c5->SaveAs(name);
            TCanvas * cgr = new TCanvas();
    cgr->cd();
    //setTDRStyle();
    

    title.Form("Vdep vs Lumi, %s%i", "TIB_L", detid);
    name.Form("VdepEvol_VdepvsLumi_%s%i.root", "TIB_L", detid);
    
    lumigr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage [ V ]");
    lumigr->GetHistogram()->GetXaxis()->SetTitle("Integrated luminosity [ fb^{ -1} ]");
        lumigr->GetHistogram()->GetYaxis()->SetRangeUser(0,350);
    lumigr->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // lumigr->SetTitle(title);
    lumigr->SetName(name);
    lumigr->SetLineColor(1);
    lumigr->SetLineWidth(4);
    lumigr->Draw("alp");
         
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    lumigr->SetName(Form("lumigr_%s%i", "TIB_L", detid));
    lumigr->SaveAs(Form("lumigr_%s%i.root", "TIB_L", detid));
    lumigr->Write();
    

    title.Form("DeltaVdep vs Lumi, %s%i", "TIB_L", detid);
    name.Form("VdepEvol_DeltaVdepvsLumi_%s%i.root", "TIB_L", detid);

    DeltaVdep->GetHistogram()->GetYaxis()->SetTitle("Delta Full depletion voltage [ V ]");
    DeltaVdep->GetHistogram()->GetXaxis()->SetTitle("Integrated luminosity [ fb^{ -1} ]");
    DeltaVdep->GetHistogram()->GetYaxis()->SetRangeUser(-350,250);
    DeltaVdep->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // DeltaVdep->SetTitle(title);
    DeltaVdep->SetName(name);
    DeltaVdep->SetLineColor(1);
    DeltaVdep->SetLineWidth(4);
    DeltaVdep->Draw("alp");
         
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    DeltaVdep->SetName(Form("DeltaVdep_%s%i", "TIB_L", detid));
    DeltaVdep->SaveAs(Form("DeltaVdep_%s%i.root", "TIB_L", detid));
    DeltaVdep->Write();

    title.Form("Vdep vs Fluence,%s%i", "TIB_L", detid);
    name.Form("VdepEvol_VdepvsFeq_%s%i.png", "TIB_L", detid);
    feqgr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage [ V ]");
    feqgr->GetHistogram()->GetXaxis()->SetTitle("Fluence [1MeV neq/cm^{-2}]");
    // feqgr->SetTitle(title);
    feqgr->SetName(name);
    feqgr->SetLineColor(1);
    feqgr->Draw("alp");
     
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    feqgr->SetName(Form("feqgr_%i", detid));
    feqgr->Write();
    
    title.Form("Vdep vs Time,%s%i.png", "TIB_L", detid);
    name.Form("VdepEvol_VdepvsTime_%s%i.png", "TIB_L", detid);
    timegr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage [ V ]");
    timegr->GetHistogram()->GetXaxis()->SetTitle("Time since end of Run3 [days]");
    timegr->GetHistogram()->SetAxisRange(-1000,1000);
    // timegr->SetTitle(title);
    timegr->SetName(name);
    timegr->SetLineColor(1);
    timegr->Draw("alp");
   
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    timegr->SetName(Form("timegr_%i", detid));

    timegr->Write();

    title.Form("Vdep vs Layer,%s%i.png", "TIB_L", detid);
    name.Form("VdepEvol_VdepvsLayer_%s%i.png", "TIB_L", detid);
    Vdep_0v1->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage [ V ]");
    Vdep_0v1->GetHistogram()->GetXaxis()->SetTitle("Time since end of Run3 [days]");
    Vdep_0v1->SetTitle(title);
    Vdep_0v1->SetName(name);
    Vdep_0v1->SetLineColor(1);
    Vdep_0v1->Draw("alp");
    cgr->SaveAs(name);
    Vdep_0v1->SetName(Form("timegr_%i", detid));
    Vdep_0v1->Write();
		}

	if (detid>4 && detid <=10)
    		{
			
			detid = detid-4;
                    TCanvas * c2 = new TCanvas();
        c2->cd();
	//setTDRStyle();
	//writeExtraText = true;       // if extra text
  	//extraText  = "CMS";  // default extra text is "Preliminary"
        title.Form("Module temperature (%s, DETID: %i)", "TOB_L" , detid);
        // h_T->SetTitle(title);
        h_T->SetLineColor(kBlack);
        h_T->GetXaxis()->SetTitle("Time (steps)");
        h_T->GetYaxis()->SetTitle("Temperature (#circK)");
        h_T->DrawCopy();
        name.Form("VdepEvol_T_%s%i.png", "TOB_L", detid);
                // TLatex *t = new TLatex(1,1000,"CMS");
        //t->Draw();
        c2->SaveAs(name);
	    h_T->SetLabelOffset(0.007,"Y");
        h_T->SetName(Form("T_%i", detid));
        h_T->Write();
        
        
        TCanvas * c3 = new TCanvas();
        c3->cd();
	//setTDRStyle();
        title.Form("Corrected leakage current (%s, DETID: %i)", "TOB_L", detid);
        // h_I_leak_corr->SetTitle(title);
        h_I_leak_corr->SetLineColor(kBlack);
        h_I_leak_corr->GetXaxis()->SetTimeDisplay(1);
        h_I_leak_corr->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_I_leak_corr->GetXaxis()->SetTitle("Time");
        h_I_leak_corr->GetYaxis()->SetTitle("Leakage current (mA)");
        h_I_leak_corr->DrawCopy();
        name.Form("VdepEvol_Ileak_%s%i.png", "TOB_L", detid);
                
        //t->Draw();
        c3->SaveAs(name);
        h_I_leak_corr->SetName(Form("Ileak_%i", detid));
        h_I_leak_corr->Write();
        
        
        TCanvas * c4 = new TCanvas();
        c4->cd();
			title.Form("Full depletion voltage (%s%i)", "TOB_L", detid); 



        // h_U->SetTitle(title);
        h_U->GetXaxis()->SetTimeDisplay(1);
	//h_U->GetXaxis()->SetTimeFormat("#splitline{%Y}{%d/%m}");
        h_U->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_U->SetLineColor(kBlack);
        h_U->GetXaxis()->SetTitle("Time");
        h_U->GetYaxis()->SetTitle("Full depletion voltage (V)");
        h_U->GetYaxis()->SetRangeUser(0,350);
        h_U->DrawCopy();
        name.Form("VdepEvol_Vdep_%s%i.png", "TOB_L", detid);
 
        //t->Draw();
        c4->SaveAs(name);
        h_U->SetName(Form("Vdep_%i", detid));
        h_U->Write();
                TCanvas * c5 = new TCanvas();
        c5->cd();
        title.Form("Effective space charge (%s, DETID: %i)", "TOB_L", detid);
        // h_N->SetTitle(title);
        //	h_N->GetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        h_Nc->SetLineColor(kBlue);
        h_Nc->DrawCopy("SAME");
        h_Na->SetLineColor(kGreen);
        h_Na->DrawCopy("SAME");
        h_NY->SetLineColor(kRed);
        h_NY->DrawCopy("SAME");
        name.Form("VdepEvol_Ncontrib_%s%i.png", "TOB_L", detid);

        //t->Draw();
        c5->SaveAs(name);
        h_N->SetName(Form("N_%i", detid));
        h_N->Write();
        h_Nc->SetName(Form("Nc_%i", detid));
        h_Nc->Write();
        h_Na->SetName(Form("Na_%i", detid));
        h_Na->Write();
        h_NY->SetName(Form("NY_%i", detid));
        h_NY->Write();
        
        
        c5->cd();
        title.Form("Effective space charge contributions (%s, DETID: %i)", "TOB_L", detid);
        // h_N->SetTitle(title);
        //	h_N-dGetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        name.Form("VdepEvol_Neff_%s%i.png", "TOB_L", detid);

        //t->Draw();
        c5->SaveAs(name);

            TCanvas * cgr = new TCanvas();
    cgr->cd();
    //setTDRStyle();
    

    title.Form("Vdep vs Lumi,%s%i", "TOB_L", detid);
    
    name.Form("VdepEvol_VdepvsLumi_%s%i.png", "TOB_L", detid);
    lumigr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    lumigr->GetHistogram()->GetXaxis()->SetTitle("Int. luminosity (fb^{-1})");
    lumigr->GetHistogram()->GetYaxis()->SetRangeUser(0,350);
    lumigr->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // lumigr->SetTitle(title);
    lumigr->SetName(name);
    lumigr->SetLineColor(1);
    lumigr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    //lumigr->SetName(Form("lumigr_%i", detid));
    lumigr->SetName(Form("lumigr_%s%i", "TOB_L", detid));
    lumigr->SaveAs(Form("lumigr_%s%i.root", "TOB_L", detid));
    lumigr->Write();
    
        title.Form("DeltaVdep vs Lumi, %s%i", "TOB_L", detid);
    name.Form("VdepEvol_DeltaVdepvsLumi_%s%i.root", "TOB_L", detid);

    DeltaVdep->GetHistogram()->GetYaxis()->SetTitle("Delta Full depletion voltage [ V ]");
    DeltaVdep->GetHistogram()->GetXaxis()->SetTitle("Integrated luminosity [ fb^{ -1} ]");
    DeltaVdep->GetHistogram()->GetYaxis()->SetRangeUser(-350,250);
    DeltaVdep->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // DeltaVdep->SetTitle(title);
    DeltaVdep->SetName(name);
    DeltaVdep->SetLineColor(1);
    DeltaVdep->SetLineWidth(4);
    DeltaVdep->Draw("alp");
         
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    DeltaVdep->SetName(Form("DeltaVdep_%s%i", "TOB_L", detid));
    DeltaVdep->SaveAs(Form("DeltaVdep_%s%i.root", "TOB_L", detid));
    DeltaVdep->Write();





    title.Form("Vdep vs Fluence, DETID: %s%i", "TOB_L", detid);
    name.Form("VdepEvol_VdepvsFeq_%s%i.png", "TOB_L", detid);
    feqgr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    feqgr->GetHistogram()->GetXaxis()->SetTitle("Fluence (1MeV neq/cm^{-2})");
    // feqgr->SetTitle(title);
    feqgr->SetName(name);
    feqgr->SetLineColor(1);
    feqgr->Draw("alp");
        
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    feqgr->SetName(Form("feqgr_%i", detid));
    feqgr->Write();
    
    title.Form("Vdep vs Time, %s%i", "TOB_L", detid);
    name.Form("VdepEvol_VdepvsTime_%s%i.png", "TOB_L", detid);
    timegr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    timegr->GetHistogram()->GetXaxis()->SetTitle("Time since end of Run3(days)");
    timegr->GetHistogram()->SetAxisRange(-1000,1000);
    // timegr->SetTitle(title);
    timegr->SetName(name);
    timegr->SetLineColor(1);
    timegr->Draw("alp");
     //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    timegr->SetName(Form("timegr_%i", detid));

    timegr->Write();
		}

    



	if (detid>10 && detid <=13)
    		{
			detid = detid-10;

            TCanvas * c2 = new TCanvas();
        c2->cd();
	//setTDRStyle();
	//writeExtraText = true;       // if extra text
  	//extraText  = "CMS";  // default extra text is "Preliminary"
        title.Form("Module temperature (%s, DETID: %i)", "TID_R" , detid);
        // h_T->SetTitle(title);
        h_T->SetLineColor(kBlack);
        h_T->GetXaxis()->SetTitle("Time (steps)");
        h_T->GetYaxis()->SetTitle("Temperature (#circK)");
        h_T->DrawCopy();
        name.Form("VdepEvol_T_%s%i.png", "TID_R", detid);
                // TLatex *t = new TLatex(1,1000,"CMS");
        //t->Draw();
        c2->SaveAs(name);
	h_T->SetLabelOffset(0.007,"Y");
        h_T->SetName(Form("T_%i", detid));
        h_T->Write();
        
        
        TCanvas * c3 = new TCanvas();
        c3->cd();
	//setTDRStyle();
        title.Form("Corrected leakage current (%s, DETID: %i)", "TID_R", detid);
        // h_I_leak_corr->SetTitle(title);
        h_I_leak_corr->SetLineColor(kBlack);
        h_I_leak_corr->GetXaxis()->SetTimeDisplay(1);
        h_I_leak_corr->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_I_leak_corr->GetXaxis()->SetTitle("Time");
        h_I_leak_corr->GetYaxis()->SetTitle("Leakage current (mA)");
        h_I_leak_corr->DrawCopy();
        name.Form("VdepEvol_Ileak_%s%i.png", "TOB_L", detid);
 
        //t->Draw();
        c3->SaveAs(name);
        h_I_leak_corr->SetName(Form("Ileak_%i", detid));
        h_I_leak_corr->Write();

                TCanvas * c4 = new TCanvas();
        c4->cd();
			title.Form("Full depletion voltage (%s%i)", "TID_R", detid);	




        // h_U->SetTitle(title);
        h_U->GetXaxis()->SetTimeDisplay(1);
	//h_U->GetXaxis()->SetTimeFormat("#splitline{%Y}{%d/%m}");
        h_U->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_U->SetLineColor(kBlack);
        h_U->GetXaxis()->SetTitle("Time");
        h_U->GetYaxis()->SetTitle("Full depletion voltage (V)");
        h_U->DrawCopy();
        name.Form("VdepEvol_Vdep_%s%i.png", "TID_R", detid);

        //t->Draw();
        c4->SaveAs(name);
        h_U->SetName(Form("Vdep_%i", detid));
        h_U->Write();
                TCanvas * c5 = new TCanvas();
        c5->cd();
        title.Form("Effective space charge (%s, DETID: %i)", "TID_R", detid);
        // h_N->SetTitle(title);
        //	h_N->GetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        h_Nc->SetLineColor(kBlue);
        h_Nc->DrawCopy("SAME");
        h_Na->SetLineColor(kGreen);
        h_Na->DrawCopy("SAME");
        h_NY->SetLineColor(kRed);
        h_NY->DrawCopy("SAME");
        name.Form("VdepEvol_Ncontrib_%s%i.png", "TID_R", detid);
               
        //t->Draw();
        c5->SaveAs(name);
        h_N->SetName(Form("N_%i", detid));
        h_N->Write();
        h_Nc->SetName(Form("Nc_%i", detid));
        h_Nc->Write();
        h_Na->SetName(Form("Na_%i", detid));
        h_Na->Write();
        h_NY->SetName(Form("NY_%i", detid));
        h_NY->Write();
        
        
        c5->cd();
        title.Form("Effective space charge contributions (%s, DETID: %i)", "TID_R", detid);
        // h_N->SetTitle(title);
        //	h_N-dGetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        name.Form("VdepEvol_Neff_%s%i.png", "TID_R", detid);

        //t->Draw();
        c5->SaveAs(name);

            TCanvas * cgr = new TCanvas();
    cgr->cd();
    //setTDRStyle();
    

    title.Form("Vdep vs Lumi, %s%i", "TID_R", detid);
    name.Form("VdepEvol_VdepvsLumi_%s%i.png", "TID_R", detid);
    lumigr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    lumigr->GetHistogram()->GetXaxis()->SetTitle("Int. luminosity (fb^{-1})");
    lumigr->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // lumigr->SetTitle(title);
    lumigr->SetName(name);
    lumigr->SetLineColor(1);
    lumigr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    lumigr->SetName(Form("lumigr_%i", detid));
    lumigr->SaveAs(Form("lumigr_%s%i.root", "TID_R", detid));
    lumigr->Write();
    
            title.Form("DeltaVdep vs Lumi, %s%i", "TID_R", detid);
    name.Form("VdepEvol_DeltaVdepvsLumi_%s%i.root", "TID_R", detid);

    DeltaVdep->GetHistogram()->GetYaxis()->SetTitle("Delta Full depletion voltage [ V ]");
    DeltaVdep->GetHistogram()->GetXaxis()->SetTitle("Integrated luminosity [ fb^{ -1} ]");
    DeltaVdep->GetHistogram()->GetYaxis()->SetRangeUser(-350,250);
    DeltaVdep->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // DeltaVdep->SetTitle(title);
    DeltaVdep->SetName(name);
    DeltaVdep->SetLineColor(1);
    DeltaVdep->SetLineWidth(4);
    DeltaVdep->Draw("alp");
         
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    DeltaVdep->SetName(Form("DeltaVdep_%s%i", "TID_R", detid));
    DeltaVdep->SaveAs(Form("DeltaVdep_%s%i.root", "TID_R", detid));
    DeltaVdep->Write();

    title.Form("Vdep vs Fluence, %s%i", "TID_R", detid);
    name.Form("VdepEvol_VdepvsFeq_%s%i.png", "TID_R", detid);
    feqgr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    feqgr->GetHistogram()->GetXaxis()->SetTitle("Fluence (1MeV neq/cm^{-2})");
    // feqgr->SetTitle(title);
    feqgr->SetName(name);
    feqgr->SetLineColor(1);
    feqgr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    feqgr->SetName(Form("feqgr_%i", detid));
    feqgr->Write();
    
    title.Form("Vdep vs Time, DETID: %s%i", "TID_R", detid);
    name.Form("VdepEvol_VdepvsTime_%s%i.png", "TID_R", detid);
    timegr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    timegr->GetHistogram()->GetXaxis()->SetTitle("Time since end of Run3(days)");
    timegr->GetHistogram()->SetAxisRange(-1000,1000);
    // timegr->SetTitle(title);
    timegr->SetName(name);
    timegr->SetLineColor(1);
    timegr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    timegr->SetName(Form("timegr_%i", detid));

    timegr->Write();
		}

	if (detid>13 && detid <=20)
    		{
			
			detid = detid-13;

            TCanvas * c2 = new TCanvas();
        c2->cd();
	//setTDRStyle();
	//writeExtraText = true;       // if extra text
  	//extraText  = "CMS";  // default extra text is "Preliminary"
        title.Form("Module temperature (%s, DETID: %i)", "TEC_R" , detid);
        // h_T->SetTitle(title);
        h_T->SetLineColor(kBlack);
        h_T->GetXaxis()->SetTitle("Time (steps)");
        h_T->GetYaxis()->SetTitle("Temperature (#circK)");
        h_T->DrawCopy();
        name.Form("VdepEvol_T_%s%i.png","TEC_R", detid);
                        // TLatex *t = new TLatex(1,1000,"CMS");
        //t->Draw();
        c2->SaveAs(name);

	h_T->SetLabelOffset(0.007,"Y");
        h_T->SetName(Form("T_%i", detid));
        h_T->Write();
        
        
        TCanvas * c3 = new TCanvas();
        c3->cd();
	//setTDRStyle();
        title.Form("Corrected leakage current (%s, DETID: %i)", "TEC_R", detid);
        // h_I_leak_corr->SetTitle(title);
        h_I_leak_corr->GetXaxis()->SetTimeDisplay(1);
        h_I_leak_corr->SetLineColor(kBlack);
        h_I_leak_corr->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_I_leak_corr->GetXaxis()->SetTitle("Time");
        h_I_leak_corr->GetYaxis()->SetTitle("Leakage current (mA)");
        h_I_leak_corr->DrawCopy();
        name.Form("VdepEvol_Ileak_%s%i.png", "TEC_R", detid);
                //t->Draw();
        c3->SaveAs(name);


        h_I_leak_corr->SetName(Form("Ileak_%i", detid));
        h_I_leak_corr->Write();

            TCanvas * c4 = new TCanvas();
        c4->cd();
			title.Form("Full depletion voltage (%s%i)", "TEC_R", detid);	

        // h_U->SetTitle(title);
        h_U->GetXaxis()->SetTimeDisplay(1);
	//h_U->GetXaxis()->SetTimeFormat("#splitline{%Y}{%d/%m}");
        h_U->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_U->SetLineColor(kBlack);
        h_U->GetXaxis()->SetTitle("Time");
        h_U->GetYaxis()->SetTitle("Full depletion voltage (V)");
        h_U->DrawCopy();
        name.Form("VdepEvol_Vdep_%s%i.png", "TEC_R", detid);
                //t->Draw();
        c4->SaveAs(name);


        h_U->SetName(Form("Vdep_%i", detid));
        h_U->Write();

                TCanvas * c5 = new TCanvas();
        c5->cd();
        title.Form("Effective space charge (%s, DETID: %i)","TEC_R", detid);
        // h_N->SetTitle(title);
        //	h_N->GetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        h_Nc->SetLineColor(kBlue);
        h_Nc->DrawCopy("SAME");
        h_Na->SetLineColor(kGreen);
        h_Na->DrawCopy("SAME");
        h_NY->SetLineColor(kRed);
        h_NY->DrawCopy("SAME");
        name.Form("VdepEvol_Ncontrib_%s%i.png", "TEC_R", detid);

        //t->Draw();
        c5->SaveAs(name);
        h_N->SetName(Form("N_%i", detid));
        h_N->Write();
        h_Nc->SetName(Form("Nc_%i", detid));
        h_Nc->Write();
        h_Na->SetName(Form("Na_%i", detid));
        h_Na->Write();
        h_NY->SetName(Form("NY_%i", detid));
        h_NY->Write();
        
        
        c5->cd();
        title.Form("Effective space charge contributions (%s, DETID: %i)", "TEC_R", detid);
        // h_N->SetTitle(title);
        //	h_N-dGetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        name.Form("VdepEvol_Neff_%s%i.png", "TEC_R", detid);

        //t->Draw();
        c5->SaveAs(name);


            TCanvas * cgr = new TCanvas();
    cgr->cd();
    //setTDRStyle();
    

    title.Form("Vdep vs Lumi,%s%i", "TEC_R", detid);
    name.Form("VdepEvol_VdepvsLumi_%s%i.png", "TEC_R", detid);
    lumigr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    lumigr->GetHistogram()->GetXaxis()->SetTitle("Int. luminosity (fb^{-1})");
    lumigr->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // lumigr->SetTitle(title);
    lumigr->SetName(name);
    lumigr->SetLineColor(1);
    lumigr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    lumigr->SetName(Form("lumigr_%i", detid));
    lumigr->SaveAs(Form("lumigr_%s%i.root", "TEC_R", detid));
    lumigr->Write();
    
            title.Form("DeltaVdep vs Lumi, %s%i", "TEC_R", detid);
    name.Form("VdepEvol_DeltaVdepvsLumi_%s%i.root", "TEC_R", detid);

    DeltaVdep->GetHistogram()->GetYaxis()->SetTitle("Delta Full depletion voltage [ V ]");
    DeltaVdep->GetHistogram()->GetXaxis()->SetTitle("Integrated luminosity [ fb^{ -1} ]");
    DeltaVdep->GetHistogram()->GetYaxis()->SetRangeUser(-350,250);
    DeltaVdep->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // DeltaVdep->SetTitle(title);
    DeltaVdep->SetName(name);
    DeltaVdep->SetLineColor(1);
    DeltaVdep->SetLineWidth(4);
    DeltaVdep->Draw("alp");
         
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    DeltaVdep->SetName(Form("DeltaVdep_%s%i", "TEC_R", detid));
    DeltaVdep->SaveAs(Form("DeltaVdep_%s%i.root", "TEC_R", detid));
    DeltaVdep->Write();

    title.Form("Vdep vs Fluence,%s%i", "TEC_R", detid);
    name.Form("VdepEvol_VdepvsFeq_%i.png", detid);
    feqgr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    feqgr->GetHistogram()->GetXaxis()->SetTitle("Fluence (1MeV neq/cm^{-2})");
    // feqgr->SetTitle(title);
    feqgr->SetName(name);
    feqgr->SetLineColor(1);
    feqgr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    feqgr->SetName(Form("feqgr_%i", detid));
    feqgr->Write();
    
    title.Form("Vdep vs Time, %s%i", "TEC_R", detid);
    name.Form("VdepEvol_VdepvsTime_%s%i.png", "TEC_R", detid);
    timegr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    timegr->GetHistogram()->GetXaxis()->SetTitle("Time since end of Run3(days)");
    timegr->GetHistogram()->SetAxisRange(-1000,1000);
    // timegr->SetTitle(title);
    timegr->SetName(name);
    timegr->SetLineColor(1);
    timegr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    timegr->SetName(Form("timegr_%i", detid));

    timegr->Write();
		}



	if (detid>470176166 && detid <=470444202)
    		{
			 
			// detid = detid-13;

            TCanvas * c2 = new TCanvas();
        c2->cd();
	//setTDRStyle();
	//writeExtraText = true;       // if extra text
  	//extraText  = "CMS";  // default extra text is "Preliminary"
        title.Form("Module temperature (%s, DETID: %i)", "TEC_R" , detid);
        // h_T->SetTitle(title);
        h_T->SetLineColor(kBlack);
        h_T->GetXaxis()->SetTitle("Time (steps)");
        h_T->GetYaxis()->SetTitle("Temperature (#circK)");
        h_T->DrawCopy();
        name.Form("VdepEvol_T_%s%i.png","TEC_R5_W9_", detid);
                        // TLatex *t = new TLatex(1,1000,"CMS");
        //t->Draw();
        c2->SaveAs(name);

	h_T->SetLabelOffset(0.007,"Y");
        h_T->SetName(Form("T_%i", detid));
        h_T->Write();
        
        
        TCanvas * c3 = new TCanvas();
        c3->cd();
	//setTDRStyle();
        title.Form("Corrected leakage current (%s, DETID: %i)", "TEC_R5_W9_", detid);
        // h_I_leak_corr->SetTitle(title);
        h_I_leak_corr->GetXaxis()->SetTimeDisplay(1);
        h_I_leak_corr->SetLineColor(kBlack);
        h_I_leak_corr->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_I_leak_corr->GetXaxis()->SetTitle("Time");
        h_I_leak_corr->GetYaxis()->SetTitle("Leakage current (mA)");
        h_I_leak_corr->DrawCopy();
        name.Form("VdepEvol_Ileak_%s%i.png", "TEC_R5_W9_", detid);
                //t->Draw();
        c3->SaveAs(name);


        h_I_leak_corr->SetName(Form("Ileak_%i", detid));
        h_I_leak_corr->Write();

            TCanvas * c4 = new TCanvas();
        c4->cd();
			title.Form("Full depletion voltage (%s%i)", "TEC_R5_W9_", detid);	

        // h_U->SetTitle(title);
        h_U->GetXaxis()->SetTimeDisplay(1);
	//h_U->GetXaxis()->SetTimeFormat("#splitline{%Y}{%d/%m}");
        h_U->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_U->SetLineColor(kBlack);
        h_U->GetXaxis()->SetTitle("Time");
        h_U->GetYaxis()->SetTitle("Full depletion voltage (V)");
        h_U->DrawCopy();
        name.Form("VdepEvol_Vdep_%s%i.png", "TEC_R5_W9_", detid);
                //t->Draw();
        c4->SaveAs(name);


        h_U->SetName(Form("Vdep_%i", detid));
        h_U->Write();

                TCanvas * c5 = new TCanvas();
        c5->cd();
        title.Form("Effective space charge (%s, DETID: %i)","TEC_R5_W9_", detid);
        // h_N->SetTitle(title);
        //	h_N->GetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        h_Nc->SetLineColor(kBlue);
        h_Nc->DrawCopy("SAME");
        h_Na->SetLineColor(kGreen);
        h_Na->DrawCopy("SAME");
        h_NY->SetLineColor(kRed);
        h_NY->DrawCopy("SAME");
        name.Form("VdepEvol_Ncontrib_%s%i.png", "TEC_R5_W9_", detid);

        //t->Draw();
        c5->SaveAs(name);
        h_N->SetName(Form("N_%i", detid));
        h_N->Write();
        h_Nc->SetName(Form("Nc_%i", detid));
        h_Nc->Write();
        h_Na->SetName(Form("Na_%i", detid));
        h_Na->Write();
        h_NY->SetName(Form("NY_%i", detid));
        h_NY->Write();
        
        
        c5->cd();
        title.Form("Effective space charge contributions (%s, DETID: %i)", "TEC_R5_W9_", detid);
        // h_N->SetTitle(title);
        //	h_N-dGetXaxis()->SetTimeDisplay(1);
        //	h_N->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
        h_N->GetXaxis()->SetTitle("Time (steps)");
        h_N->GetYaxis()->SetTitle("Effective space charge (cm-3)");
        h_N->DrawCopy();
        name.Form("VdepEvol_Neff_%s%i.png", "TEC_R5_W9_", detid);

        //t->Draw();
        c5->SaveAs(name);


            TCanvas * cgr = new TCanvas();
    cgr->cd();
    //setTDRStyle();
    

    title.Form("Vdep vs Lumi,%s%i", "TEC_R5_W9_", detid);
    name.Form("VdepEvol_VdepvsLumi_%s%i.png", "TEC_R5_W9_", detid);
    lumigr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    lumigr->GetHistogram()->GetXaxis()->SetTitle("Int. luminosity (fb^{-1})");
    lumigr->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // lumigr->SetTitle(title);
    lumigr->SetName(name);
    lumigr->SetLineColor(1);
    lumigr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    lumigr->SetName(Form("lumigr_%i", detid));
    lumigr->SaveAs(Form("lumigr_%s%i.root", "TEC_R5_W9_", detid));
    lumigr->Write();
    
        DeltaVdep->GetHistogram()->GetYaxis()->SetTitle("Delta Full depletion voltage [ V ]");
    DeltaVdep->GetHistogram()->GetXaxis()->SetTitle("Integrated luminosity [ fb^{ -1} ]");
    DeltaVdep->GetHistogram()->GetYaxis()->SetRangeUser(-350,200);
    DeltaVdep->GetHistogram()->GetXaxis()->SetRangeUser(0,600);
    // DeltaVdep->SetTitle(title);
    DeltaVdep->SetName(name);
    DeltaVdep->SetLineColor(1);
    DeltaVdep->SetLineWidth(4);
    DeltaVdep->Draw("alp");
         
        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    DeltaVdep->SetName(Form("DeltaVdep_%s%i", "TEC_R5_W9", detid));
    DeltaVdep->SaveAs(Form("DeltaVdep_%s%i.root", "TEC_R5_W9", detid));
    DeltaVdep->Write();


    title.Form("Vdep vs Fluence,%s%i", "TEC_R5_W9_", detid);
    name.Form("VdepEvol_VdepvsFeq_%i.png", detid);
    feqgr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    feqgr->GetHistogram()->GetXaxis()->SetTitle("Fluence (1MeV neq/cm^{-2})");
    // feqgr->SetTitle(title);
    feqgr->SetName(name);
    feqgr->SetLineColor(1);
    feqgr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    feqgr->SetName(Form("feqgr_%i", detid));
    feqgr->Write();
    
    title.Form("Vdep vs Time, %s%i", "TEC_R5_W9_", detid);
    name.Form("VdepEvol_VdepvsTime_%s%i.png", "TEC_R5_W9_", detid);
    timegr->GetHistogram()->GetYaxis()->SetTitle("Full depletion voltage (V)");
    timegr->GetHistogram()->GetXaxis()->SetTitle("Time since end of Run3(days)");
    timegr->GetHistogram()->SetAxisRange(-1000,1000);
    // timegr->SetTitle(title);
    timegr->SetName(name);
    timegr->SetLineColor(1);
    timegr->Draw("alp");

        //t->Draw();
    if(print_plots) cgr->SaveAs(name);
    timegr->SetName(Form("timegr_%i", detid));

    timegr->Write();
		}
	

    }
    
    
    ofs.close();
    //StoreVinit.close();
    h_T->Delete();
    h_I_leak->Delete();
    h_I_leak_corr->Delete();
    
    h_Nc->Delete();
    h_Na->Delete();
    h_NY->Delete();
    h_N->Delete();
    h_U->Delete();
}


void HamburgModelFactory::drawLumiTempScenario(){
    
    Int_t maxTime = Nperiods;
    fout->cd();
    
    // fluence/temperature history
    TH1D * h_Feq = new TH1D("h_Feq","Fluence",maxTime,0.5,periodInDays*24.*60.*60.*maxTime+0.5);
    TH1D * h_Feq_total = new TH1D("h_Feq_total","Total Fluence",maxTime,0.5,periodInDays*24.*60.*60.*maxTime+0.5);
    TH1D * h_DayLumi = new TH1D("h_DayLumi","Inst. Lumi per day",maxTime,0.5,periodInDays*24.*60.*60.*maxTime+0.5);
    TH1D * h_IntLumi = new TH1D("h_IntLumi","Integrated luminosity in fb^{-1}",maxTime,0.5,periodInDays*24.*60.*60.*maxTime+0.5);
    TH1D * h_T_base = new TH1D("h_T_base","Temperature set points", maxTime, 0.5, periodInDays*24*60*60*maxTime+0.5);
    
    	
    for(Int_t i = 0; i<Nperiods; i++){
        h_Feq->SetBinContent(i+1, Feq[i]);
        h_Feq_total->SetBinContent(i+1, intFeq[i]);
        h_DayLumi->SetBinContent(i+1, Lumi[i]);
        h_IntLumi->SetBinContent(i+1, intLumi[i]);
        h_T_base->SetBinContent(i+1, Temp[i]);
    }
    
    TString title;
    TCanvas * cF = new TCanvas();
    // gROOT->LoadMacro("tdrstyle.C");
    
    cF->cd();
    //setTDRStyle();
    //	  title.Form("Fluence vs time");
    //	  h_Feq_total->SetTitle(title);
    h_Feq_total->SetName("intFeq");
    h_Feq_total->GetXaxis()->SetTimeDisplay(1);
    h_Feq_total->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
    h_Feq_total->GetXaxis()->SetTitle("Time");
    h_Feq_total->GetYaxis()->SetTitle("Fluence (1MeV neq/cm^{-2})");
    h_Feq_total->DrawCopy();
    cF->SaveAs("VdepEvol_Feq_total.png");
    h_Feq_total->Write();
    
    TCanvas * cL = new TCanvas();
    cL->cd();
    // setTDRStyle();
    //	  title.Form("Fluence vs time");
    //	  h_Feq_total->SetTitle(title);
    h_IntLumi->SetName("intLumi");
    h_IntLumi->GetXaxis()->SetTimeDisplay(1);
    h_IntLumi->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
    h_IntLumi->GetXaxis()->SetTitle("Time");
    h_IntLumi->GetYaxis()->SetTitle("Integrated luminosity [ fb^{-1} ]");
    h_IntLumi->GetYaxis()->SetTitleOffset(1.2);
    h_IntLumi->DrawCopy();
    h_IntLumi->SaveAs("VdepEvol_IntLumi.root");
    cL->SaveAs("VdepEvol_IntLumi.png");
    h_IntLumi->Write();
    
    
    TCanvas * cT = new TCanvas();
    cT->cd();
    // setTDRStyle();
    title.Form("Temperature set points without corrections");
    h_T_base->SetTitle(title);
    h_T_base->SetName("Temp");
    h_T_base->GetXaxis()->SetTimeDisplay(1);
    h_T_base->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
    h_T_base->GetXaxis()->SetTitle("Time");
    h_T_base->GetYaxis()->SetTitle("Temperature [ #circC ]");
    h_T_base->DrawCopy();
    h_T_base->SaveAs("VdepEvol_T_base.root");
    cT->SaveAs("VdepEvol_T_base.png");
    h_T_base->Write();

}


// Save results in a tree
//------------------------

void HamburgModelFactory::saveSensorSimuInTree(std::string filename="SimuTree.root"){

    if(!foutTree) {
        foutTree = new TFile(filename.c_str() ,"recreate");
        simutree = new TTree("simutree", "");
        
        simutree->Branch("detid", &detid, "detid/I");
        simutree->Branch("period", &iper, "period/I");
        simutree->Branch("fluence", &flu_out, "fluence/F");
        simutree->Branch("lumi", &lumi_out, "lumi/F");
        simutree->Branch("T", &T_out, "T/F");
        simutree->Branch("Ileak", &Ileak_out, "Ileak/F");
        simutree->Branch("Vdep", &Vdep_out, "Vdep/F");
    }
    
    foutTree->cd();

    for(Int_t i = 0; i<Nperiods; i++){
        flu_out = intFeq[i];
        lumi_out = intLumi[i];
        T_out = Temp_evol[i];
        Ileak_out = I_leak[i]*LeakCorrection(Temp_evol[i], ZeroC+20);
        Vdep_out = U[i];
        iper = i+1;
        simutree->Fill();
    }
}



// Loop over modules
//------------------

void HamburgModelFactory::runSimuForAllModules(int option=1, bool saveTree=false){
    
    std::cout << "Starting module life simulation" << std::endl;
    std::cout << "Option " << option << std::endl;
    // float VDEPF[40]={0};
    //for (int idet = 0; idet< 1; idet++) {
    for (int idet = 0; idet< nentries; idet++) {

        tree->GetEntry(idet);
        if(option==0) std::cout << "Looping over all modules" << option << std::endl; // all modules
        if(option==1) // set of test modules
            if(detid!=369120278 && detid!=369120378 && detid != 369121381 && detid != 369121385) continue;
        if(option==2) // modules from small scans
        if (detid != 369121381 && detid != 369121382 && detid != 369121385 && detid != 369121386 && detid != 369121389 && detid != 369121390 && // TIB L1
            detid != 369125861 && detid != 369125862 && detid != 369125865 && detid != 369125866 && detid != 369125869 && detid != 369125870 && //TIB L1
            detid != 436232901 && detid != 436232902 && detid != 436232905 && detid != 436232906 && detid != 436232909 && detid != 436232910 && //TOB L1
            detid != 436232913 && detid != 436232914 && detid != 436232917 && detid != 436232918 && detid != 436232921 && detid != 436232922 && // TOB L1
            detid != 436281508 && detid != 436281512 && detid != 436281516 && detid != 436281520 && detid != 436281524 && detid != 436281528 && // TOB L4
            detid != 470148196 && detid != 470148200 && detid != 470148204 && detid != 470148228 && detid != 470148232 && detid != 470148236 && // TEC
            detid != 470148240 && detid != 470148292 && detid != 470148296 && detid != 470148300 && detid != 470148304 && // TEC
            detid != 470148261 && detid != 470148262 && detid != 470148265 && detid != 470148266 && detid != 470148324 && detid != 470148328 && detid != 470148332 && detid != 470148336 && detid != 470148340 // TEC
            // and (detid != 369121385) and (detid != 369138014) and (detid != 369158500 ) and (detid != 369175324) and (detid != 436229362)
            && detid!=369120278 && detid!=369120378
            ) continue;
        if(option==3) // 1% random modules
            if(idet%100!=0) continue;
        if(option==4) // random hot modules
            if(temp<20 || idet%10!=0) continue;


        if (option == 5)
            { 
                if ( detid != 470177449 && detid != 470177958 && detid != 470176941 && detid != 470177450 && detid != 470176942
                    && detid != 470440105 && detid != 470177961 && detid != 470177453 && detid != 470177962 && detid != 470177454 && detid != 470440109
                    && detid != 470177965 && detid != 470177966 && detid != 470442661 && detid != 470180517 && detid != 470442662 && detid != 470180518
                    && detid != 470443173 && detid != 470181029 && detid != 470442665 && detid != 470180521 && detid != 470181030 && detid != 470180522
                    && detid != 470443685 && detid != 470181541 && detid != 470443177 && detid != 470443686 && detid != 470181033 && detid != 470181542
                    && detid != 470443178 && detid != 470181034 && detid != 470444197 && detid != 470182053 && detid != 470181545 && detid != 470182054
                    && detid != 470443690 && detid != 470181546 && detid != 470182057 && detid != 470182058 && detid != 470440101 && detid != 470444198
                    && detid != 470440102 && detid != 470443174 && detid != 470443689 && detid != 470439593 && detid != 470439594 && detid != 470444201
                    && detid != 470439085 && detid != 470439086 && detid != 470439597 && detid != 470444202 && detid != 470440106 && detid != 470439598
                    && detid != 470442666 && detid != 470438574 && detid != 470438573 && detid != 470440110 && detid != 470176430 && detid != 470438309
                    && detid != 470176165 && detid != 470438310 && detid != 470176166 && detid != 470438821 && detid != 470176677 && detid != 470438313
                    && detid != 470438822 && detid != 470176169 && detid != 470176678 && detid != 470438314 && detid != 470176170 && detid != 470439333
                    && detid != 470177189 && detid != 470438825 && detid != 470439334 && detid != 470176681 && detid != 470177190 && detid != 470176173
                    && detid != 470438826 && detid != 470176682 && detid != 470439845 && detid != 470177701 && detid != 470439337 && detid != 470177193
                    && detid != 470177702 && detid != 470176685 && detid != 470177194 && detid != 470176686 && detid != 470177705 && detid != 470177197
                    && detid != 470177706 && detid != 470177198 && detid != 470177709 && detid != 470177710 && detid != 470180261 && detid != 470180262
                    && detid != 470442917 && detid != 470180773 && detid != 470442409 && detid != 470180265 && detid != 470180774 && detid != 470442410
                    && detid != 470180266 && detid != 470443429 && detid != 470181285 && detid != 470442921 && detid != 470443430 && detid != 470180777
                    && detid != 470181286 && detid != 470176938 && detid != 470442922 && detid != 470180778 && detid != 470443941 && detid != 470181797
                    && detid != 470443433 && detid != 470443942 && detid != 470181289 && detid != 470181798 && detid != 470181290 && detid != 470181801
                    && detid != 470181802 && detid != 470442405 && detid != 470439846 && detid != 470442406 && detid != 470442918 && detid != 470443945
                    && detid != 470439338 && detid != 470439849 && detid != 470443946 && detid != 470439341 && detid != 470438829 && detid != 470439850 && detid != 470439342 && detid != 470439853
                    && detid != 470439854 && detid != 470443434 && detid != 470438318 && detid != 470438317 && detid != 470438830 && detid != 470176174
                    && detid != 470438565 && detid != 470176421 && detid != 470438566 && detid != 470176422 && detid != 470439077 && detid != 470176933 && detid != 470438569 && detid != 470439078
                    && detid != 470176425 && detid != 470176934 && detid != 470438570 && detid != 470176426 && detid != 470439589 && detid != 470177445 && detid != 470439081 && detid != 470439590
                    && detid != 470176937 && detid != 470177446 && detid != 470176429 && detid != 470439082
                    && detid != 470177957 )
                    {continue;}

            }
        std::cout << " doing calculations for detid " << detid << std::endl;
        std::cout << "   fluence: " <<fluence_7000TeV<< " Ton: "<<temp<<" ini_leak: "<<ini_leak<<" ini_vdep: "<<ini_vdep<< std::endl;
        
        simulateSensorEvolution(detid);//VDEPF[idet] = 
        if(detid==369120278 || detid==369120378 || detid == 369121381 || detid == 369121385  || detid == 369125870) drawSaveSensorSimu(true);
        else if (detid == 470177449 || detid == 470177958 || detid == 470176941 || detid == 470177450 || detid == 470176942
            || detid == 470440105 || detid == 470177961 || detid == 470177453 || detid == 470177962 || detid == 470177454 || detid == 470440109
            || detid == 470177965 || detid == 470177966 || detid == 470442661 || detid == 470180517 || detid == 470442662 || detid == 470180518
            || detid == 470443173 || detid == 470181029 || detid == 470442665 || detid == 470180521 || detid == 470181030 || detid == 470180522
            || detid == 470443685 || detid == 470181541 || detid == 470443177 || detid == 470443686 || detid == 470181033 || detid == 470181542
            || detid == 470443178 || detid == 470181034 || detid == 470444197 || detid == 470182053 || detid == 470181545 || detid == 470182054
            || detid == 470443690 || detid == 470181546 || detid == 470182057 || detid == 470182058 || detid == 470440101 || detid == 470444198
            || detid == 470440102 || detid == 470443174 || detid == 470443689 || detid == 470439593 || detid == 470439594 || detid == 470444201
            || detid == 470439085 || detid == 470439086 || detid == 470439597 || detid == 470444202 || detid == 470440106 || detid == 470439598
            || detid == 470442666 || detid == 470438574 || detid == 470438573 || detid == 470440110 || detid == 470176430 || detid == 470438309
            || detid == 470176165 || detid == 470438310 || detid == 470176166 || detid == 470438821 || detid == 470176677 || detid == 470438313
            || detid == 470438822 || detid == 470176169 || detid == 470176678 || detid == 470438314 || detid == 470176170 || detid == 470439333
            || detid == 470177189 || detid == 470438825 || detid == 470439334 || detid == 470176681 || detid == 470177190 || detid == 470176173
            || detid == 470438826 || detid == 470176682 || detid == 470439845 || detid == 470177701 || detid == 470439337 || detid == 470177193
            || detid == 470177702 || detid == 470176685 || detid == 470177194 || detid == 470176686 || detid == 470177705 || detid == 470177197
            || detid == 470177706 || detid == 470177198 || detid == 470177709 || detid == 470177710 || detid == 470180261 || detid == 470180262
            || detid == 470442917 || detid == 470180773 || detid == 470442409 || detid == 470180265 || detid == 470180774 || detid == 470442410
            || detid == 470180266 || detid == 470443429 || detid == 470181285 || detid == 470442921 || detid == 470443430 || detid == 470180777
            || detid == 470181286 || detid == 470176938 || detid == 470442922 || detid == 470180778 || detid == 470443941 || detid == 470181797
            || detid == 470443433 || detid == 470443942 || detid == 470181289 || detid == 470181798 || detid == 470181290 || detid == 470181801
            || detid == 470181802 || detid == 470442405 || detid == 470439846 || detid == 470442406 || detid == 470442918 || detid == 470443945
            || detid == 470439338 || detid == 470439849 || detid == 470443946 || detid == 470439341 || detid == 470438829 || detid == 470439850 || detid == 470439342 || detid == 470439853
            || detid == 470439854 || detid == 470443434 || detid == 470438318 || detid == 470438317 || detid == 470438830 || detid == 470176174
            || detid == 470438565 || detid == 470176421 || detid == 470438566 || detid == 470176422 || detid == 470439077 || detid == 470176933 || detid == 470438569 || detid == 470439078
            || detid == 470176425 || detid == 470176934 || detid == 470438570 || detid == 470176426 || detid == 470439589 || detid == 470177445 || detid == 470439081 || detid == 470439590
            || detid == 470176937 || detid == 470177446 || detid == 470176429 || detid == 470439082 || detid == 470177957  )
                {
                    drawSaveSensorSimu(true); 
                }
        else drawSaveSensorSimu(false);


        
        if(saveTree) saveSensorSimuInTree();
        
    }
}


// Use average temperature and Vini per layer
// for getting one representative curve per layer
//------------------------------------------------

void HamburgModelFactory::runSimuForAvgModules(bool drawNeff=false){//float[40] 
    
    std::cout << nentries <<" entries" << std::endl;
    // float VDEPF[40]={0};
    // pseudo detids from 1 to 10 for barrel layers
    for (int idet = 0; idet< nentries; idet++) {
        
        tree->GetEntry(idet);
        std::cout << " doing calculations for detid " << detid << std::endl;
        std::cout << "   fluence: " <<fluence_7000TeV<< " Ton: "<<temp<<" ini_leak: "<<ini_leak<<" ini_vdep: "<<ini_vdep<< std::endl;

        simulateSensorEvolution(detid);//VDEPF[idet] = 
        drawSaveSensorSimu(drawNeff);
        
    }
    // return VDEPF;
}


//Plot demanded by the SND experiment => Final Vdep value vs Time
// void HamburgModelFactory::drawVdepFinalvsTime(int layer, float[10][40] vdep_detid)
//     {

//         TH2D * h_Vdepf = new TH2D("h_Vdepf","Final Vdep vs Time",1000,0,1000,800,0,800);    
//         for(Int_t i = 0; i<10; i++)
//             {
//                 h_Vdepf->SetBinContent(100*(i+1), vdep_detid[i][layer]);
//             }
    
//         TCanvas * cF = new TCanvas();
//         cF->cd();
//     //	  title.Form("Fluence vs time");
//     //	  h_Feq_total->SetTitle(title);
//         h_Vdepf->SetName("intFeq");
//         h_Vdepf->GetXaxis()->SetTimeDisplay(1);
//         h_Vdepf->GetXaxis()->SetTimeFormat("%d\/%m\/%y%F2010-01-01 00:00:00");
//         h_Vdepf->GetXaxis()->SetTitle("Time (days)");
//         h_Vdepf->GetYaxis()->SetTitle("Vdep (V)");
//         h_Vdepf->DrawCopy();
//         cF->SaveAs("VdepFinal_Time.png");
//         h_Vdepf->Write();
//     }


