#include <TGraph.h>
#include <TCanvas.h>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

void computeGraphsStats() {
    // On suppose que tous les TGraph ont le même nombre de points
    const int nGraphs = 160; // Nombre de TGraph
    std::vector<TGraph*> graphs; // Contiendra les TGraph

    TString  DETIDS[nGraphs] = {
        "470177449" , "470177958" , "470176941" , "470177450" , "470176942" ,
        "470440105" ,"470177961" ,"470177453" ,"470177962" ,"470177454" ,"470440109" ,
        "470177965" ,"470177966" ,"470442661" ,"470180517" ,"470442662" ,"470180518" ,
        "470443173" ,"470181029" ,"470442665" ,"470180521" ,"470181030" ,"470180522" ,
        "470443685" ,"470181541" ,"470443177" ,"470443686" ,"470181033" ,"470181542" ,
        "470443178" ,"470181034" ,"470444197" ,"470182053" ,"470181545" ,"470182054" ,
        "470443690" ,"470181546" ,"470182057" ,"470182058" ,"470440101" ,"470444198" ,
        "470440102" ,"470443174" ,"470443689" ,"470439593" ,"470439594" ,"470444201" ,
        "470439085" ,"470439086" ,"470439597" ,"470444202" ,"470440106" ,"470439598" ,
        "470442666" ,"470438574" ,"470438573" ,"470440110" ,"470176430" ,"470438309" ,
        "470176165" ,"470438310" ,"470176166" ,"470438821" ,"470176677" ,"470438313" ,
        "470438822" ,"470176169" ,"470176678" ,"470438314" ,"470176170" ,"470439333" ,
        "470177189" ,"470438825" ,"470439334" ,"470176681" ,"470177190" ,"470176173" ,
        "470438826" ,"470176682" ,"470439845" ,"470177701" ,"470439337" ,"470177193" ,
        "470177702" ,"470176685" ,"470177194" ,"470176686" ,"470177705" ,"470177197" ,
        "470177706" ,"470177198" ,"470177709" ,"470177710" ,"470180261" ,"470180262" ,
        "470442917" ,"470180773" ,"470442409" ,"470180265" ,"470180774" ,"470442410" ,
        "470180266" ,"470443429" ,"470181285" ,"470442921" ,"470443430" ,"470180777" ,
        "470181286" ,"470176938" ,"470442922" ,"470180778" ,"470443941" ,"470181797" ,
        "470443433" ,"470443942" ,"470181289" ,"470181798" ,"470181290" ,"470181801" ,
        "470181802" ,"470442405" ,"470439846" ,"470442406" ,"470442918" ,"470443945" ,
        "470439338" ,"470439849" ,"470443946" ,"470439341" ,"470438829" ,"470439850" ,
        "470439342" ,"470439853" ,"470439854" ,"470443434" ,"470438318" ,"470438317" ,
        "470438830" ,"470176174" ,"470438565" ,"470176421" ,"470438566" ,"470176422" ,
        "470439077" ,"470176933" ,"470438569" ,"470439078" ,"470176425" ,"470176934" ,
        "470438570" ,"470176426" ,"470439589" ,"470177445" ,"470439081" ,"470439590" ,
        "470176937" ,"470177446" ,"470176429" ,"470439082" ,"470177957" 
    };

    for (unsigned int i = 0; i < nGraphs; i++) {
        TString filename = "./DeltaVdep_TEC_R5_W9"+DETIDS[i]+".root";
        TString GraphName = "DeltaVdep_TEC_R5_W9"+DETIDS[i];
        TFile* file = TFile::Open(filename);
        if (!file || file->IsZombie()) {
            std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
            // return;
            continue;
        }

        TGraph* graph = dynamic_cast<TGraph*>(file->Get(GraphName));
        if (!graph) {
            std::cerr << "Erreur : TGraph '" << GraphName << "' introuvable dans " << filename << std::endl;
            file->Close();
            continue;
        }

        graphs.push_back((TGraph*)graph->Clone()); // Clone pour garder les données même après fermeture du fichier
        file->Close();
        delete file; // On ferme et libère la mémoire
    }

    // On suppose que tous les TGraph ont le même nombre de points
    int nPoints = graphs[0]->GetN();
    if (nPoints == 0)
        {
            for (unsigned int i = 0; i < nGraphs; i++) 
                {
                    nPoints = graphs[i]->GetN();
                    std::cout << "Nombre de points  i : " << nPoints << std::endl;
                    if (nPoints != 0) break;
                }
        }
    // std::cout << "Nombre de points : " << nPoints << std::endl;
    // Vecteurs pour stocker les valeurs calculées
    std::vector<double> xVals(nPoints, 0.0);
    std::vector<double> minVals(nPoints, 0.0);
    std::vector<double> maxVals(nPoints, 0.0);
    std::vector<double> meanVals(nPoints, 0.0);

    // Calcul des min, max et moyenne pour chaque point
    for (int i = 0; i < nPoints; ++i) {
        std::vector<double> yVals; // Stocker les Y pour ce point

        // Récupération des Y pour le point i
        for (auto* graph : graphs) {
            double x, y;
            graph->GetPoint(i, x, y);
            // std::cout<<"i : "<<i<<" x: "<<x<<" y: "<<y<<std::endl;  
            xVals[i] = x; // Suppose que les X sont identiques pour tous les graphes
            yVals.push_back(y);
        }

        // Calcul des stats
        minVals[i] = *std::min_element(yVals.begin(), yVals.end());
        maxVals[i] = *std::max_element(yVals.begin(), yVals.end());
        meanVals[i] = std::accumulate(yVals.begin(), yVals.end(), 0.0) / yVals.size();
    }

    // for (int i = 0; i < nPoints; ++i)
    //     {
    //             std::cout << "xi : "<<xVals[i]<<std::endl;;
    //     }

    // Création des TGraph pour min, max, et moyenne
    TGraph* gMin = new TGraph(nPoints, xVals.data(), minVals.data());
    TGraph* gMax = new TGraph(nPoints, xVals.data(), maxVals.data());
    TGraph* gMean = new TGraph(nPoints, xVals.data(), meanVals.data());

    gMin->SetLineColor(kBlue);
    gMax->SetLineColor(kRed);
    gMean->SetLineColor(kGreen);
    gMin->SetTitle("Min;X;Y_{min}");
    gMax->SetTitle("Max;X;V_{max}");
    gMean->SetTitle("Mean;X;Y_{mean}");

    // Dessiner les graphes
    TCanvas* c = new TCanvas("c", "Graphs Stats", 800, 600);
    gMax->Draw("AL"); // Max en rouge
    gMin->Draw("L SAME"); // Min en bleu
    gMean->Draw("L SAME"); // Moyenne en vert

    gMax->GetYaxis()->SetRangeUser(-350, 250); // Ajuster l'axe Y
    gMax->GetXaxis()->SetTitle("Int. Lumi [fb^{-1}] "); // Ajuster l'axe X
    gMax->GetYaxis()->SetTitle("#Delta V_{fd} [V] "); // Ajuster l'axe X
    gMax->SetTitle("TEC R5 W9"); // Ajuster l'axe X
    // Légende
    auto legend = new TLegend(0.3, 0.7, 0.5, 0.9);
    legend->SetHeader("End 2024 L_{int} = 391 fb^{-1}");
    legend->AddEntry(gMin, "Min", "l");
    legend->AddEntry(gMax, "Max", "l");
    legend->AddEntry(gMean, "Mean", "l");
    legend->Draw();

   TLine *line = new TLine(391,-350,391,250);
    line->SetLineWidth(6);
   line->SetLineStyle(2);
   line->SetLineColor(kRed);
   line->Draw();

    TLatex *t2 = new TLatex();
    t2->SetTextFont(52);
    t2->SetTextAlign(11);
    t2->SetTextSize(0.04);
    t2->DrawLatex(410,100,"Simulation");
    // Nettoyage des TGraph d'origine (facultatif ici car le programme se termine)
    for (auto* graph : graphs) {
        delete graph;
    }

    c->SaveAs("DeltaVfd_TEC_R5_W9.pdf");
}
