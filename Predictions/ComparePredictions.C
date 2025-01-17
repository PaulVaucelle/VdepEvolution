#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TLegend.h>

void plot() {
    TString file1 = "Oldlumigr_TIB_L1.root";
    TString file2 = "lumigr_TIB_L1.root";
   
    TString graph1_name = "lumigr_TIB_L1";
    TString graph2_name = "lumigr_TIB_L1";
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
    graph1->SetLineColor(kRed);
    graph1->SetLineWidth(2);
    graph1->SetMarkerColor(kRed);
    graph1->SetMarkerStyle(20);
    graph1->SetMarkerStyle(1);
    graph1->SetMarkerSize(1);

    graph2->SetLineColor(kBlue);
    graph2->SetLineWidth(2);
    graph2->SetMarkerColor(kBlue);
    graph2->SetMarkerStyle(1);
    graph2->SetMarkerSize(1);

    // Dessiner les graphiques sur le même canvas
    graph1->Draw("ALP");  // Axe, ligne, points
    graph2->Draw("LP SAME");

    // Ajouter une légende
    TLegend* legend = new TLegend(0.5, 0.7, 0.7, 0.9);
    legend->AddEntry(graph1, "Old TIBL1", "lp");
    legend->AddEntry(graph2, "New TIBL1", "lp");
    legend->Draw();

    // Afficher le canvas
    canvas->Update();
    canvas->SaveAs("ComaprePredi.png");

    // Fermeture des fichiers ROOT
    f1->Close();
    f2->Close();
}
