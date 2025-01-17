#include "include/HamburgModelFactory.h"
#include "include/HamburgModelFactory.cc"

#define tecringoffset_   5
#define subdetoffset_   25
#define layerstartbit_  14
#define tecringmask_   0x7
#define subdetmask_    0x7
#define layermask_     0x7


// Computation for each detid

//void ComputeVdepEvolution_v2(){
int main(){
    std::string fb = "300";// 300 - 400 - 500
    std::string d = "500";// 100 - 300 - 500
    HamburgModelFactory factory;
    std::string type = "realistic"; //simu-realistic
    factory.setGlobalTree("Inputs/GlobalTree.root");
        // factory.readLumiTempScenario("Inputs/realistic_scenario_2025.txt");
    // factory.readLumiTempScenario("Inputs/realistic_scenario_"+fb+"fb.txt");
    // factory.readLumiTempScenario("Inputs/realistic_scenario_"+fb+"fb_"+d+"d.txt");
    factory.readLumiTempScenario("Inputs/realistic_scenario_150fb_2025_2026.txt");
    //factory.runSimuForAllModules(1);//test modules
    factory.runSimuForAllModules(2, true); // small scans modules

    factory.drawLumiTempScenario();    
}
