#include <TSystem.h>
#include <TFile.h>
#include <TGraph.h>
#include <TList.h>
#include <iostream>
#include <string>
using namespace std;
void mergeFiles() {
    // Nom du fichier de sortie
    const char* outputFileName = "simulation2025.root";
    
    // Création d'une liste pour stocker tous les TGraph
    TList* graphList = new TList();

    // Liste des fichiers dans le répertoire courant
    void* dir = gSystem->OpenDirectory(".");
    const char* file;
    TString fileNamesIn[20] = {
        "lumigr_TIB_L1", "lumigr_TIB_L2", "lumigr_TIB_L3", "lumigr_TIB_L4",
        "lumigr_TOB_L1", "lumigr_TOB_L2", "lumigr_TOB_L3", "lumigr_TOB_L4","lumigr_TOB_L5", "lumigr_TOB_L6",
        "lumigr_1", "lumigr_2", "lumigr_3",
        "lumigr_1", "lumigr_2", "lumigr_3", "lumigr_4","lumigr_5", "lumigr_6","lumigr_7"
        };
    TString fileNamesOut[20] = {
                "lumigr_TIB_L1", "lumigr_TIB_L2", "lumigr_TIB_L3", "lumigr_TIB_L4",
        "lumigr_TOB_L1", "lumigr_TOB_L2", "lumigr_TOB_L3", "lumigr_TOB_L4","lumigr_TOB_L5", "lumigr_TOB_L6",
        "lumigr_TID_R1", "lumigr_TID_R2", "lumigr_TID_R3",
        "lumigr_TEC_R1", "lumigr_TEC_R2", "lumigr_TEC_R3", "lumigr_TEC_R4","lumigr_TEC_R5", "lumigr_TEC_R6","lumigr_TEC_R7"
    };

    int count = 0;
    // Parcourir tous les fichiers du répertoire
    while (count<20) { //(file = gSystem->GetDirEntry(dir))
        // TString fileName(file);//file or fileNamesIn[count]
        TString fileName = fileNamesOut[count]+".root";
        // Sélectionner uniquement les fichiers qui commencent par "lumigr_"
        if (fileName.BeginsWith("lumigr_") && fileName.EndsWith(".root")) {

            // Ouvrir le fichier ROOT
            TFile* inputFile = TFile::Open(fileName);
            if (!inputFile || inputFile->IsZombie()) {
                std::cerr << "Impossible d'ouvrir le fichier : " << fileName << std::endl;
                continue;
            }
            size_t pos = fileName.Index(".");
            TString firstPart = fileName(0, pos);        // Avant le séparateur
            std::cout << "fileNamesIn[count] : " << fileNamesIn[count] << std::endl;
            TGraph* graph = (TGraph*) inputFile->Get(fileNamesIn[count]);
            if (!graph) {
                std::cerr << "TGraph introuvable dans le fichier : " << fileName << std::endl;
                inputFile->Close();
                continue;
            }
            
            graphList->Add(graph->Clone());  // On clone pour ne pas pointer vers le fichier d'origine

            inputFile->Close();
            
        }
        count++;
    }
    gSystem->FreeDirectory(dir);

    // Sauvegarde des TGraph dans le fichier de sortie
    TFile outputFile(outputFileName, "RECREATE");
    if (!outputFile.IsOpen()) {
        std::cerr << "Erreur à l'ouverture du fichier de sortie : " << outputFileName << std::endl;
        return;
    }
    int count2 =0;
    // Écrire tous les TGraph dans le fichier de sortie
    TIter next(graphList);
    TGraph* graph;
    int graphIndex = 0;
    while ((graph = (TGraph*) next())) {
        TString graphName = fileNamesOut[count2];
        graph->SetName(graphName);  // Renomme chaque graph pour éviter les conflits
        graph->Write();
        count2++;
    }

    std::cout << "Fichier fusionné créé : " << outputFileName << std::endl;

    outputFile.ls();
    // Nettoyage
    outputFile.Close();
    delete graphList;  // Libérer la mémoire utilisée par la liste des TGraph
}
