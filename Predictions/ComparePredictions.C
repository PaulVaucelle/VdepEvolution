#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>

void plot(TString LAYER, TString Ring) {
    TString layer = LAYER;
    TString file1 = "Oldlumigr_"+layer+".root";
    TString file2 = "lumigr_"+layer+".root";
   
    // TString graph1_name = "lumigr_"+layer;
    // TString graph2_name = "lumigr_"+layer;
       
    TString graph1_name = "lumigr_"+Ring;
    TString graph2_name = "lumigr_"+Ring;
    // Ouvrir les fichiers ROOT
    TFile* f1 = TFile::Open(file1);
    TFile* f2 = TFile::Open(file2);

    if (!f1 || f1->IsZombie() || !f2 || f2->IsZombie()) {
        std::cerr << "Error opening one of the files." << std::endl;
        return;
    }

    // Récupérer les TGraph
    TGraph* graph1 = dynamic_cast<TGraph*>(f1->Get(graph1_name));
    TGraph* graph2 = dynamic_cast<TGraph*>(f2->Get(graph2_name));

    if (!graph1 || !graph2) {
        std::cerr << "Error retrieving one of the TGraphs." << std::endl;
        f1->Close();
        f2->Close();
        return;
    }

    // Créer un canvas
    TCanvas* canvas = new TCanvas("canvas", "Overlay of Two TGraphs", 800, 600);

    // Configurer les styles pour les graphiques
    graph2->SetTitle("");
        graph2->SetLineColor(kBlue);
    graph2->SetLineWidth(2);
    graph2->SetMarkerColor(kBlue);
    graph2->SetMarkerStyle(1);
    graph2->SetMarkerSize(1);

    graph1->SetLineColor(kRed);
    graph1->SetLineWidth(2);
    graph1->SetMarkerColor(kRed);
    // graph1->SetMarkerStyle(20);
    graph1->SetMarkerStyle(1);
    graph1->SetMarkerSize(1);



    // Dessiner les graphiques sur le même canvas
    graph2->Draw("ALP");
    graph1->Draw("LP SAME");  // Axe, ligne, points

    graph2->GetXaxis()->SetRangeUser(0,600);
    graph2->GetYaxis()->SetRangeUser(0,350);
    // graph1->GetXaxis()->SetRangeUser(0,600);
    // graph1->GetYaxis()->SetRangeUser(0,350);

    // Ajouter une légende
    TLegend* legend = new TLegend(0.5, 0.7, 0.7, 0.9);
    legend->AddEntry(graph1, "Old "+layer, "lp");
    legend->AddEntry(graph2, "New "+layer, "lp");
    legend->Draw();

    // Afficher le canvas
    canvas->Update();
    canvas->SaveAs("ComaprePredi"+layer+".pdf");

    // Fermeture des fichiers ROOT
    f1->Close();
    f2->Close();
}
