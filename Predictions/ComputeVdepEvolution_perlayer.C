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
    bool ComputeOverTime = true; //draw Final Vdep vs time
    //--------------------------------
    std::string fb = "300";//300-400-500
    std::string d = "1000";//100-300-500
    std::string type = "realistic"; //simu-realistic
    HamburgModelFactory factory;
    factory.setGlobalTree("Inputs/GlobalTree_perlayer.root");//
    factory.readLumiTempScenario("Inputs/realistic_scenario_150fb_2025_2026.txt");//without dismantling
    //  factory.readLumiTempScenario("Inputs/"+type+"_scenario_"+fb+"fb_"+d+"d_15C.txt");//with dismantling
    // factory.readLumiTempScenario("Inputs/run3_projection_scenario_step1day_repl-5oC.txt");
    factory.runSimuForAvgModules(true); // drawNeff
    factory.drawLumiTempScenario();

    //----------Draw Final Vdep vs time-----------------

    // if (ComputeOverTime)
    //     {
    //         //-> Tourner sur 10 scenarios a lumi et temp fixée fixée; Le seule paramètre étant la durée de démantèlement
    //         float Vdepf[10][40];//40 devrait être remplacé apr le nombre de layers
    //         for (int i=0; i < 10; i++)
    //             {   
    //                 std::string index = std::to_string(i);
    //                 factory.readLumiTempScenario("Inputs/VdepVsTime/"+type+"_scenario_"+fb+"fb_"+index+".txt");//with dismantling // => mettre le i dans le nom du ficheir
    //                 Vdepf[i] = factory.runSimuForAvgModules(true); 
    //                 // => rajouter une fonction pour faire ce plot de Vdep vs time
    //             }
    //         factory.drawVdepFinalvsTime(9,Vdepf);
    //     }
    return 0;
}
