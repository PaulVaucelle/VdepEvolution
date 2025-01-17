
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <TFile.h>

//Convertir un entier en string
string convertInt(int nombre)
{
   stringstream ss;ss << nombre;return ss.str();
}
//Convertir un entier en string
string convertFloat(float nombre)
{
   stringstream ss;ss << nombre;return ss.str();
}

void OldMakeOld500fbScenario()
{
   
    bool debug=false;
    const int periodes = 52; //41 until 2023
    //48 without dementeling of the tracker
    // 49 with dismantling of 100 days
    // 49 with dismantling of 300 days
    // 52 with dismantling of 500 days

    string filename = "./realistic_scenario_2025.txt";
    std::ofstream ofs (filename,std::ofstream::out);
    // periodes
    //---------
    
    Int_t t_at_T[periodes] = {
        18, 49, 6, //2010
        18, 49, 6, //2011
        18, 49, 6, //2012
        31, 18, 24, //2013
        18, 49, 6, //2014
        18, 49, 6, //2015
        18, 49, 6, //2016
        18, 49, 6, //2017
        18, 49, 6, //2018
        // 31, 18, 24, //2019
        // 31, 18, 24, //2020
        // 18, 49, 6, //2021
        // 18, 49, 6, //2022
        // 18, 49 //, 6, //2023
        12, 61, 0, //2019 //30
        0, 73, 0,//2020
        0, 73, 0, //2021
        50, 13, 10, //2022 13/4/6
        29, 18, 26, //2023
        25, 23, 25, //2024
        25, 24, 24, //2025
        73,0,0, //0.20 dismantling of 100 days __ 60 dismantling of 300 days __ 73,0,0 dismantling of 500 days
        27//,0,0 dismantling of 500 days
    }; // 5 days periods
    
    

    // center-of-mass enery
    //---------------------
    
    Float_t *SqrtS = new Float_t[periodes]; // in TeV
    SqrtS[0] = 0.;
    SqrtS[2] = 0.;
    SqrtS[3] = 0.;
    SqrtS[5] = 0.;
    SqrtS[6] = 0.;
    SqrtS[8] = 0.;
    SqrtS[9] = 0.;
    SqrtS[10] = 0.;
    SqrtS[11] = 0.;
    SqrtS[12] = 0.;
    SqrtS[13] = 0.;
    SqrtS[14] = 0.;
    SqrtS[15] = 0.;
    SqrtS[17] = 0.;
    SqrtS[18] = 0.;
    SqrtS[20] = 0.;
    SqrtS[21] = 0.;
    SqrtS[23] = 0.;
    SqrtS[24] = 0.;
    SqrtS[26] = 0.;
    SqrtS[27] = 0.;
    SqrtS[29] = 0.;
    SqrtS[30] = 0.;
    SqrtS[32] = 0.;
    SqrtS[33] = 0.;
    SqrtS[35] = 0.;
    SqrtS[36] = 0.;
    SqrtS[38] = 0.;
    SqrtS[39] = 0.;
    SqrtS[41] = 0.;
    SqrtS[42] = 0.;
    SqrtS[44] = 0.;
    SqrtS[45] = 0.;
    SqrtS[47] = 0.;
    SqrtS[48] = 0.;//dismantling 100 and 300 days
    SqrtS[49] = 0.;//dismantling 500 days    
    SqrtS[50] = 0.;//dismantling 500 days
    SqrtS[51] = 0.;//dismantling 500 days

    SqrtS[1] = 7; //2010
    SqrtS[4] = 7; //2011
    SqrtS[7] = 8; //2012
    SqrtS[16] = 13; //2015
    SqrtS[19] = 13; //2016
    SqrtS[22] = 13; //2017
    SqrtS[25] = 13; //2018
    SqrtS[28] = 0.; //2019
    SqrtS[31] = 0.; //2020
    SqrtS[34] = 0; //2021
    SqrtS[37] = 13.6; //2022
    SqrtS[40] = 13.6; //2023
    SqrtS[43] = 13.6; //2024
    SqrtS[46] = 13.6; //2025

    
    
    
    // Lumi
    //-----
    
    Float_t *Lumi = new Float_t[periodes]; // in fb-1
    Lumi[0] = 0.;
    Lumi[2] = 0.;
    Lumi[3] = 0.;
    Lumi[5] = 0.;
    Lumi[6] = 0.;
    Lumi[8] = 0.;
    Lumi[9] = 0.;
    Lumi[10] = 0.;
    Lumi[11] = 0.;
    Lumi[12] = 0.;
    Lumi[13] = 0.;
    Lumi[14] = 0.;
    Lumi[15] = 0.;
    Lumi[17] = 0.;
    Lumi[18] = 0.;
    Lumi[20] = 0.;
    Lumi[21] = 0.;
    Lumi[23] = 0.;
    Lumi[24] = 0.;
    Lumi[26] = 0.;
    Lumi[27] = 0.;
    Lumi[29] = 0.;
    Lumi[30] = 0.;
    Lumi[32] = 0.;
    Lumi[33] = 0.;
    Lumi[35] = 0.;
    Lumi[36] = 0.;
    Lumi[38] = 0.;
    Lumi[39] = 0.;
    Lumi[41] = 0.;
    Lumi[42] = 0.;
    Lumi[44] = 0.;
    Lumi[45] = 0.;
    Lumi[47] = 0.;
    Lumi[48] = 0.;//dismantling 100 and 300 days
    Lumi[49] = 0.;//dismantling 500 days
    Lumi[50] = 0.;//dismantling 500 days
    Lumi[51] = 0.;//dismantling 500 days
    
    Lumi[1] = 0.046; //2010
    Lumi[4] = 6.2; //2011
    Lumi[7] = 23.7; //2012
    Lumi[16] = 4.1; //2015
    Lumi[19] = 41.4; //2016
    Lumi[22] = 51.7; //2017
    Lumi[25] = 67.8; //2018
    Lumi[28] = 0.; //2019
    Lumi[31] = 0.; //2020
    //Run3 
    Lumi[34] = 0; //2021
    Lumi[37] = 38; //2022
    Lumi[40] = 75; // 300fb => 75 2023
    Lumi[43] = 193.5;//  300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 //2024
    Lumi[46] = 193.5; // 300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 // 2025
    // Lumi Run 2022 : 38 fb-1 (recorded)/41.4 delivered
    //Sum Run 3: 300 fb-1
    //Sum total : 487.95 fb-1
    
    
    
    // temperature
    //------------
    
    float Ton=4;
    float Toff = 6;
    float Toff2 = 0;
    float Toff3 = 5;

    float RT = 20;
    float RT2 = 20;

    // temperature shift
    float T1=19; // In Run 2
    float T2=24; // In 2018
    // float T3=29; // In Run 3
    float T3=24; // In Run 3
    // in C
    Double_t T_95[periodes] = {
        Toff, Ton, Toff, //2010
        Toff, Ton, Toff, //2011
        Toff, Ton, Toff, //2012
        RT, Toff, Toff2, //2013
        Toff2, Toff2, Toff2, //2014
        Toff2, Ton-T1, Toff2, //2015
        Toff2, Ton-T1, Toff2, //2016
        Toff2, Ton-T1, Toff2, //2017
        Toff2, Ton-T2, Toff2, //2018
        Toff2, Toff2, Toff2, //2019
        Toff2, Toff2, RT, //2020
        Toff2, Toff2, Toff2, //2021
        Toff3, Ton-T3, Toff3, //2022
        Toff3, Ton-T3, Toff3, //2023
        Toff3, Ton-T3, Toff3, //2024
        Toff3, Ton-T3, Toff3, //2025
        RT2,RT2,RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
        RT2//dismantling of 500 days
    };
    
    
    
    // Generate scenario description file
    //-----------------------------------
    
    Int_t maxTime=0;
    Int_t stepInYear=0;
    Int_t startingYear=2010;
    Int_t dayNumber=1;
    std::cout<<"#define StepInDays 1"<<std::endl;
    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;
    ofs<<"# Starting new year: " << startingYear << std::endl; 
    for(Int_t i=0; i<periodes; i++){
        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;}
        maxTime += t_at_T[i];
        // Loop over periodes steps
        for(Int_t j=0; j<t_at_T[i]; j++){
            //std::cout << dayNumber <<" "<< stepInYear+1 <<" "<< SqrtS[i] <<" "<< Lumi[i]/(t_at_T[i]) <<" "<< T_95[i] << std::endl;
            // Loop over days
            for(Int_t k=0; k<5; k++){
                std::cout << dayNumber <<" "<< stepInYear*5+k+1 <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] << std::endl;
                 if(ofs){
                        ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                        if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}
                        }
                else {std::cout<<"no file"<<std::endl;}
                dayNumber++;
            }
            stepInYear++;
        }
    }
    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    ofs.close();   
}

void MakeOld500fbScenario(int scenario, int femto){
    
     bool debug=false;
    string filename = "./realistic_scenario_2025.txt";
    int shiftdays= 4660; //4660: 1st of january 2023, 4750 with the early historic of 2023

    //---------Except you need to change temperatures or number of days of running/shutdown/dismantling, nothing needs to be changed after this--//
    int shiftperiodes = 0;
    int shiftdayNumber = 0;
    if (shiftdays > 4660){shiftdayNumber = shiftdays-4660;shiftperiodes = shiftdayNumber/5;}//There are 90 days in the temp histo of 2023 (18*5=90) => this shift day thing is only valid for the first period of 2023 (29 periods)
    //but can be easily reused for other periods but numbers have to be changed
    std::ofstream ofs (filename,std::ofstream::out);
    //------------
    // temperature
    //------------
    
    float Ton=4.;//4 by default
    float Toff = 6.;//6 by default
    float Toff2 = 0.;//0 by default
    float Toff3 = 5.;
    float RT = 20.;//20 by default
    float RT2 = 15.;//20 by default
    
    // temperature shift
    float T1=19.; //19 In Run 2
    float T2=24.; //24 In 2018
    float T3=24.; //was29 but currently 24 In Run 3


    //---------
    // periodes
    //---------
    if (scenario==0)//no dismantling
        {
            const int periodes = 48; 
                Int_t t_at_T[periodes] = {
                                                       18, 49, 6, //2010
        18, 49, 6, //2011
        18, 49, 6, //2012
        31, 18, 24, //2013
        18, 49, 6, //2014
        18, 49, 6, //2015
        18, 49, 6, //2016
        18, 49, 6, //2017
        18, 49, 6, //2018
        // 31, 18, 24, //2019
        // 31, 18, 24, //2020
        // 18, 49, 6, //2021
        // 18, 49, 6, //2022
        // 18, 49 //, 6, //2023
        12, 61, 0, //2019 //30
        0, 73, 0,//2020
        0, 73, 0, //2021
        50, 13, 10, //2022 13/4/6
                                                29, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24 //2025
                                         }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                            Toff, Ton, Toff, //2010
        Toff, Ton, Toff, //2011
        Toff, Ton, Toff, //2012
        RT, Toff, Toff2, //2013
        Toff2, Toff2, Toff2, //2014
        Toff2, Ton-T1, Toff2, //2015
        Toff2, Ton-T1, Toff2, //2016
        Toff2, Ton-T1, Toff2, //2017
        Toff2, Ton-T2, Toff2, //2018
        Toff2, Toff2, Toff2, //2019
        Toff2, Toff2, RT, //2020
        Toff2, Toff2, Toff2, //2021
        Toff3, Ton-T3, Toff3, //2022
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3 //2025
                    //RT2,   RT2,    RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    //RT2                //dismantling of 500 days
                };

            //-----
            // Lumi
            //-----
    
            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
    Lumi[2] = 0.;
    Lumi[3] = 0.;
    Lumi[5] = 0.;
    Lumi[6] = 0.;
    Lumi[8] = 0.;
    Lumi[9] = 0.;
    Lumi[10] = 0.;
    Lumi[11] = 0.;
    Lumi[12] = 0.;
    Lumi[13] = 0.;
    Lumi[14] = 0.;
    Lumi[15] = 0.;
    Lumi[17] = 0.;
    Lumi[18] = 0.;
    Lumi[20] = 0.;
    Lumi[21] = 0.;
    Lumi[23] = 0.;
    Lumi[24] = 0.;
    Lumi[26] = 0.;
    Lumi[27] = 0.;
    Lumi[29] = 0.;
    Lumi[30] = 0.;
    Lumi[32] = 0.;
    Lumi[33] = 0.;
    Lumi[35] = 0.;
    Lumi[36] = 0.;
    Lumi[38] = 0.;
    Lumi[39] = 0.;
    Lumi[41] = 0.;
    Lumi[42] = 0.;
    Lumi[44] = 0.;
    Lumi[45] = 0.;
    Lumi[47] = 0.;
    // Lumi[48] = 0.;//dismantling 100 and 300 days
    // Lumi[49] = 0.;//dismantling 500 days
    // Lumi[50] = 0.;//dismantling 500 days
    // Lumi[51] = 0.;//dismantling 500 days
    
    Lumi[1] = 0.046; //2010
    Lumi[4] = 6.2; //2011
    Lumi[7] = 23.7; //2012
    Lumi[16] = 4.1; //2015
    Lumi[19] = 41.4; //2016
    Lumi[22] = 51.7; //2017
    Lumi[25] = 67.8; //2018
    Lumi[28] = 0.; //2019
    Lumi[31] = 0.; //2020
    //Run3 
    Lumi[34] = 0; //2021
    Lumi[37] = 38; //2022
    Lumi[40] = 75; // 300fb => 75 2023
    Lumi[43] = 93.5+femto/2;//2024//  300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 //2024
    Lumi[46] = 93.5+femto/2;//2024 // 300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 // 2025



            
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
    SqrtS[2] = 0.;
    SqrtS[3] = 0.;
    SqrtS[5] = 0.;
    SqrtS[6] = 0.;
    SqrtS[8] = 0.;
    SqrtS[9] = 0.;
    SqrtS[10] = 0.;
    SqrtS[11] = 0.;
    SqrtS[12] = 0.;
    SqrtS[13] = 0.;
    SqrtS[14] = 0.;
    SqrtS[15] = 0.;
    SqrtS[17] = 0.;
    SqrtS[18] = 0.;
    SqrtS[20] = 0.;
    SqrtS[21] = 0.;
    SqrtS[23] = 0.;
    SqrtS[24] = 0.;
    SqrtS[26] = 0.;
    SqrtS[27] = 0.;
    SqrtS[29] = 0.;
    SqrtS[30] = 0.;
    SqrtS[32] = 0.;
    SqrtS[33] = 0.;
    SqrtS[35] = 0.;
    SqrtS[36] = 0.;
    SqrtS[38] = 0.;
    SqrtS[39] = 0.;
    SqrtS[41] = 0.;
    SqrtS[42] = 0.;
    SqrtS[44] = 0.;
    SqrtS[45] = 0.;
    SqrtS[47] = 0.;
 
    SqrtS[1] = 7; //2010
    SqrtS[4] = 7; //2011
    SqrtS[7] = 8; //2012
    SqrtS[16] = 13; //2015
    SqrtS[19] = 13; //2016
    SqrtS[22] = 13; //2017
    SqrtS[25] = 13; //2018
    SqrtS[28] = 0.; //2019
    SqrtS[31] = 0.; //2020
    SqrtS[34] = 0; //2021
    SqrtS[37] = 13.6; //2022
    SqrtS[40] = 13.6; //2023
    SqrtS[43] = 13.6; //2024
    SqrtS[46] = 13.6; //2025



                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  
        }

//-------------------end of 0-----------------------//

    else if(scenario==1)//dematneling of 100 
        {
            const int periodes = 49;
            Int_t t_at_T[periodes] = {
                                                       18, 49, 6, //2010
        18, 49, 6, //2011
        18, 49, 6, //2012
        31, 18, 24, //2013
        18, 49, 6, //2014
        18, 49, 6, //2015
        18, 49, 6, //2016
        18, 49, 6, //2017
        18, 49, 6, //2018
        // 31, 18, 24, //2019
        // 31, 18, 24, //2020
        // 18, 49, 6, //2021
        // 18, 49, 6, //2022
        // 18, 49 //, 6, //2023
        12, 61, 0, //2019 //30
        0, 73, 0,//2020
        0, 73, 0, //2021
        50, 13, 10, //2022 13/4/6
                                                29, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                20//,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                            Toff, Ton, Toff, //2010
        Toff, Ton, Toff, //2011
        Toff, Ton, Toff, //2012
        RT, Toff, Toff2, //2013
        Toff2, Toff2, Toff2, //2014
        Toff2, Ton-T1, Toff2, //2015
        Toff2, Ton-T1, Toff2, //2016
        Toff2, Ton-T1, Toff2, //2017
        Toff2, Ton-T2, Toff2, //2018
        Toff2, Toff2, Toff2, //2019
        Toff2, Toff2, RT, //2020
        Toff2, Toff2, Toff2, //2021
        Toff3, Ton-T3, Toff3, //2022
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2//,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
    Lumi[2] = 0.;
    Lumi[3] = 0.;
    Lumi[5] = 0.;
    Lumi[6] = 0.;
    Lumi[8] = 0.;
    Lumi[9] = 0.;
    Lumi[10] = 0.;
    Lumi[11] = 0.;
    Lumi[12] = 0.;
    Lumi[13] = 0.;
    Lumi[14] = 0.;
    Lumi[15] = 0.;
    Lumi[17] = 0.;
    Lumi[18] = 0.;
    Lumi[20] = 0.;
    Lumi[21] = 0.;
    Lumi[23] = 0.;
    Lumi[24] = 0.;
    Lumi[26] = 0.;
    Lumi[27] = 0.;
    Lumi[29] = 0.;
    Lumi[30] = 0.;
    Lumi[32] = 0.;
    Lumi[33] = 0.;
    Lumi[35] = 0.;
    Lumi[36] = 0.;
    Lumi[38] = 0.;
    Lumi[39] = 0.;
    Lumi[41] = 0.;
    Lumi[42] = 0.;
    Lumi[44] = 0.;
    Lumi[45] = 0.;
    Lumi[47] = 0.;
    Lumi[48] = 0.;//dismantling 100 and 300 days
    // Lumi[49] = 0.;//dismantling 500 days
    // Lumi[50] = 0.;//dismantling 500 days
    // Lumi[51] = 0.;//dismantling 500 days
    
    Lumi[1] = 0.046; //2010
    Lumi[4] = 6.2; //2011
    Lumi[7] = 23.7; //2012
    Lumi[16] = 4.1; //2015
    Lumi[19] = 41.4; //2016
    Lumi[22] = 51.7; //2017
    Lumi[25] = 67.8; //2018
    Lumi[28] = 0.; //2019
    Lumi[31] = 0.; //2020
    //Run3 
    Lumi[34] = 0; //2021
    Lumi[37] = 38; //2022
    Lumi[40] = 75; // 300fb => 75 2023
    Lumi[43] = 93.5+femto/2;//2025//  300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 //2024
    Lumi[46] = 93.5+femto/2;//2025 // 300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 // 2025
                // Lumi[0] = 0.;
                // Lumi[1] = 75.;//2023
                // Lumi[2] = 0.;
                // Lumi[3] = 0.;
                // Lumi[4] = 93.5+femto/2;//2024
                // Lumi[5] = 0.;
                // Lumi[6] = 0.;
                // Lumi[7] = 93.5+femto/2;//2025
                // Lumi[8] = 0.;
                // Lumi[9] = 0.;
                // Lumi[10] = 0.;
                // Lumi[11] = 0.;

    
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
    SqrtS[2] = 0.;
    SqrtS[3] = 0.;
    SqrtS[5] = 0.;
    SqrtS[6] = 0.;
    SqrtS[8] = 0.;
    SqrtS[9] = 0.;
    SqrtS[10] = 0.;
    SqrtS[11] = 0.;
    SqrtS[12] = 0.;
    SqrtS[13] = 0.;
    SqrtS[14] = 0.;
    SqrtS[15] = 0.;
    SqrtS[17] = 0.;
    SqrtS[18] = 0.;
    SqrtS[20] = 0.;
    SqrtS[21] = 0.;
    SqrtS[23] = 0.;
    SqrtS[24] = 0.;
    SqrtS[26] = 0.;
    SqrtS[27] = 0.;
    SqrtS[29] = 0.;
    SqrtS[30] = 0.;
    SqrtS[32] = 0.;
    SqrtS[33] = 0.;
    SqrtS[35] = 0.;
    SqrtS[36] = 0.;
    SqrtS[38] = 0.;
    SqrtS[39] = 0.;
    SqrtS[41] = 0.;
    SqrtS[42] = 0.;
    SqrtS[44] = 0.;
    SqrtS[45] = 0.;
    SqrtS[47] = 0.;
    SqrtS[48] = 0.;//dismantling 100 and 300 days
    // SqrtS[49] = 0.;//dismantling 500 days    
    // SqrtS[50] = 0.;//dismantling 500 days
    // SqrtS[51] = 0.;//dismantling 500 days

    SqrtS[1] = 7; //2010
    SqrtS[4] = 7; //2011
    SqrtS[7] = 8; //2012
    SqrtS[16] = 13; //2015
    SqrtS[19] = 13; //2016
    SqrtS[22] = 13; //2017
    SqrtS[25] = 13; //2018
    SqrtS[28] = 0.; //2019
    SqrtS[31] = 0.; //2020
    SqrtS[34] = 0; //2021
    SqrtS[37] = 13.6; //2022
    SqrtS[40] = 13.6; //2023
    SqrtS[43] = 13.6; //2024
    SqrtS[46] = 13.6; //2025
                
                    // SqrtS[0] = 0.;
                    // SqrtS[1] = 13.6;
                    // SqrtS[2] = 0.;
                    // SqrtS[3] = 0.;
                    // SqrtS[4] = 13.6;
                    // SqrtS[5] = 0.;
                    // SqrtS[6] = 0.;
                    // SqrtS[7] = 13.6; 
                    // SqrtS[8] = 0.;
                    // SqrtS[9] = 0.; 
                    // SqrtS[10] = 0.; 
                    // SqrtS[11] = 0.;
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  

        }

//-------------------end of 1-----------------------//


    else if (scenario == 2)
        {
            const int periodes = 49;
            Int_t t_at_T[periodes] = {
                       18, 49, 6, //2010
        18, 49, 6, //2011
        18, 49, 6, //2012
        31, 18, 24, //2013
        18, 49, 6, //2014
        18, 49, 6, //2015
        18, 49, 6, //2016
        18, 49, 6, //2017
        18, 49, 6, //2018
        // 31, 18, 24, //2019
        // 31, 18, 24, //2020
        // 18, 49, 6, //2021
        // 18, 49, 6, //2022
        // 18, 49 //, 6, //2023
        12, 61, 0, //2019 //30
        0, 73, 0,//2020
        0, 73, 0, //2021
        50, 13, 10, //2022 13/4/6
                                                29, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                60//,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                            Toff, Ton, Toff, //2010
        Toff, Ton, Toff, //2011
        Toff, Ton, Toff, //2012
        RT, Toff, Toff2, //2013
        Toff2, Toff2, Toff2, //2014
        Toff2, Ton-T1, Toff2, //2015
        Toff2, Ton-T1, Toff2, //2016
        Toff2, Ton-T1, Toff2, //2017
        Toff2, Ton-T2, Toff2, //2018
        Toff2, Toff2, Toff2, //2019
        Toff2, Toff2, RT, //2020
        Toff2, Toff2, Toff2, //2021
        Toff3, Ton-T3, Toff3, //2022
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2//,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                            Lumi[0] = 0.;
    Lumi[2] = 0.;
    Lumi[3] = 0.;
    Lumi[5] = 0.;
    Lumi[6] = 0.;
    Lumi[8] = 0.;
    Lumi[9] = 0.;
    Lumi[10] = 0.;
    Lumi[11] = 0.;
    Lumi[12] = 0.;
    Lumi[13] = 0.;
    Lumi[14] = 0.;
    Lumi[15] = 0.;
    Lumi[17] = 0.;
    Lumi[18] = 0.;
    Lumi[20] = 0.;
    Lumi[21] = 0.;
    Lumi[23] = 0.;
    Lumi[24] = 0.;
    Lumi[26] = 0.;
    Lumi[27] = 0.;
    Lumi[29] = 0.;
    Lumi[30] = 0.;
    Lumi[32] = 0.;
    Lumi[33] = 0.;
    Lumi[35] = 0.;
    Lumi[36] = 0.;
    Lumi[38] = 0.;
    Lumi[39] = 0.;
    Lumi[41] = 0.;
    Lumi[42] = 0.;
    Lumi[44] = 0.;
    Lumi[45] = 0.;
    Lumi[47] = 0.;
    Lumi[48] = 0.;//dismantling 100 and 300 days
    // Lumi[49] = 0.;//dismantling 500 days
    // Lumi[50] = 0.;//dismantling 500 days
    // Lumi[51] = 0.;//dismantling 500 days
    
    Lumi[1] = 0.046; //2010
    Lumi[4] = 6.2; //2011
    Lumi[7] = 23.7; //2012
    Lumi[16] = 4.1; //2015
    Lumi[19] = 41.4; //2016
    Lumi[22] = 51.7; //2017
    Lumi[25] = 67.8; //2018
    Lumi[28] = 0.; //2019
    Lumi[31] = 0.; //2020
    //Run3 
    Lumi[34] = 0; //2021
    Lumi[37] = 38; //2022
    Lumi[40] = 75; // 300fb => 75 2023
    Lumi[43] = 93.5+femto/2;//2025//  300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 //2024
    Lumi[46] = 93.5+femto/2;//2025 // 300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 // 2025
                // Lumi[0] = 0.;
                // Lumi[1] = 75.;//2023
                // Lumi[2] = 0.;
                // Lumi[3] = 0.;
                // Lumi[4] = 93.5+femto/2;//2024
                // Lumi[5] = 0.;
                // Lumi[6] = 0.;
                // Lumi[7] = 93.5+femto/2;//2025
                // Lumi[8] = 0.;
                // Lumi[9] = 0.;
                // Lumi[10] = 0.;
                // Lumi[11] = 0.;

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
    SqrtS[2] = 0.;
    SqrtS[3] = 0.;
    SqrtS[5] = 0.;
    SqrtS[6] = 0.;
    SqrtS[8] = 0.;
    SqrtS[9] = 0.;
    SqrtS[10] = 0.;
    SqrtS[11] = 0.;
    SqrtS[12] = 0.;
    SqrtS[13] = 0.;
    SqrtS[14] = 0.;
    SqrtS[15] = 0.;
    SqrtS[17] = 0.;
    SqrtS[18] = 0.;
    SqrtS[20] = 0.;
    SqrtS[21] = 0.;
    SqrtS[23] = 0.;
    SqrtS[24] = 0.;
    SqrtS[26] = 0.;
    SqrtS[27] = 0.;
    SqrtS[29] = 0.;
    SqrtS[30] = 0.;
    SqrtS[32] = 0.;
    SqrtS[33] = 0.;
    SqrtS[35] = 0.;
    SqrtS[36] = 0.;
    SqrtS[38] = 0.;
    SqrtS[39] = 0.;
    SqrtS[41] = 0.;
    SqrtS[42] = 0.;
    SqrtS[44] = 0.;
    SqrtS[45] = 0.;
    SqrtS[47] = 0.;
    SqrtS[48] = 0.;//dismantling 100 and 300 days
    // SqrtS[49] = 0.;//dismantling 500 days    
    // SqrtS[50] = 0.;//dismantling 500 days
    // SqrtS[51] = 0.;//dismantling 500 days

    SqrtS[1] = 7; //2010
    SqrtS[4] = 7; //2011
    SqrtS[7] = 8; //2012
    SqrtS[16] = 13; //2015
    SqrtS[19] = 13; //2016
    SqrtS[22] = 13; //2017
    SqrtS[25] = 13; //2018
    SqrtS[28] = 0.; //2019
    SqrtS[31] = 0.; //2020
    SqrtS[34] = 0; //2021
    SqrtS[37] = 13.6; //2022
    SqrtS[40] = 13.6; //2023
    SqrtS[43] = 13.6; //2024
    SqrtS[46] = 13.6; //2025
                    // SqrtS[0] = 0.;
                    // SqrtS[1] = 13.6;
                    // SqrtS[2] = 0.;
                    // SqrtS[3] = 0.;
                    // SqrtS[4] = 13.6;
                    // SqrtS[5] = 0.;
                    // SqrtS[6] = 0.;
                    // SqrtS[7] = 13.6; 
                    // SqrtS[8] = 0.;
                    // SqrtS[9] = 0.; 
                    // SqrtS[10] = 0.; 
                    // SqrtS[11] = 0.;  
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();          
                      
        }

//-------------------end of 2-----------------------//


    else if (scenario == 3)
        {
            const int periodes = 52;
            Int_t t_at_T[periodes] = {
                       18, 49, 6, //2010
        18, 49, 6, //2011
        18, 49, 6, //2012
        31, 18, 24, //2013
        18, 49, 6, //2014
        18, 49, 6, //2015
        18, 49, 6, //2016
        18, 49, 6, //2017
        18, 49, 6, //2018
        // 31, 18, 24, //2019
        // 31, 18, 24, //2020
        // 18, 49, 6, //2021
        // 18, 49, 6, //2022
        // 18, 49 //, 6, //2023
        12, 61, 0, //2019 //30
        0, 73, 0,//2020
        0, 73, 0, //2021
        50, 13, 10, //2022 13/4/6
                                                29, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                27
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                            Toff, Ton, Toff, //2010
        Toff, Ton, Toff, //2011
        Toff, Ton, Toff, //2012
        RT, Toff, Toff2, //2013
        Toff2, Toff2, Toff2, //2014
        Toff2, Ton-T1, Toff2, //2015
        Toff2, Ton-T1, Toff2, //2016
        Toff2, Ton-T1, Toff2, //2017
        Toff2, Ton-T2, Toff2, //2018
        Toff2, Toff2, Toff2, //2019
        Toff2, Toff2, RT, //2020
        Toff2, Toff2, Toff2, //2021
        Toff3, Ton-T3, Toff3, //2022
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
    Lumi[2] = 0.;
    Lumi[3] = 0.;
    Lumi[5] = 0.;
    Lumi[6] = 0.;
    Lumi[8] = 0.;
    Lumi[9] = 0.;
    Lumi[10] = 0.;
    Lumi[11] = 0.;
    Lumi[12] = 0.;
    Lumi[13] = 0.;
    Lumi[14] = 0.;
    Lumi[15] = 0.;
    Lumi[17] = 0.;
    Lumi[18] = 0.;
    Lumi[20] = 0.;
    Lumi[21] = 0.;
    Lumi[23] = 0.;
    Lumi[24] = 0.;
    Lumi[26] = 0.;
    Lumi[27] = 0.;
    Lumi[29] = 0.;
    Lumi[30] = 0.;
    Lumi[32] = 0.;
    Lumi[33] = 0.;
    Lumi[35] = 0.;
    Lumi[36] = 0.;
    Lumi[38] = 0.;
    Lumi[39] = 0.;
    Lumi[41] = 0.;
    Lumi[42] = 0.;
    Lumi[44] = 0.;
    Lumi[45] = 0.;
    Lumi[47] = 0.;
    Lumi[48] = 0.;//dismantling 100 and 300 days
    Lumi[49] = 0.;//dismantling 500 days
    Lumi[50] = 0.;//dismantling 500 days
    Lumi[51] = 0.;//dismantling 500 days
    
    Lumi[1] = 0.046; //2010
    Lumi[4] = 6.2; //2011
    Lumi[7] = 23.7; //2012
    Lumi[16] = 4.1; //2015
    Lumi[19] = 41.4; //2016
    Lumi[22] = 51.7; //2017
    Lumi[25] = 67.8; //2018
    Lumi[28] = 0.; //2019
    Lumi[31] = 0.; //2020
    //Run3 
    Lumi[34] = 0; //2021
    Lumi[37] = 38; //2022
    Lumi[40] = 75; // 300fb => 75 2023
    Lumi[43] = 93.5+femto/2;//2025//  300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 //2024
    Lumi[46] = 93.5+femto/2;//2025 // 300fb => 93.5 ___ 400fb => 143.5 ___ 500fb => 193.5 // 2025

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
    SqrtS[2] = 0.;
    SqrtS[3] = 0.;
    SqrtS[5] = 0.;
    SqrtS[6] = 0.;
    SqrtS[8] = 0.;
    SqrtS[9] = 0.;
    SqrtS[10] = 0.;
    SqrtS[11] = 0.;
    SqrtS[12] = 0.;
    SqrtS[13] = 0.;
    SqrtS[14] = 0.;
    SqrtS[15] = 0.;
    SqrtS[17] = 0.;
    SqrtS[18] = 0.;
    SqrtS[20] = 0.;
    SqrtS[21] = 0.;
    SqrtS[23] = 0.;
    SqrtS[24] = 0.;
    SqrtS[26] = 0.;
    SqrtS[27] = 0.;
    SqrtS[29] = 0.;
    SqrtS[30] = 0.;
    SqrtS[32] = 0.;
    SqrtS[33] = 0.;
    SqrtS[35] = 0.;
    SqrtS[36] = 0.;
    SqrtS[38] = 0.;
    SqrtS[39] = 0.;
    SqrtS[41] = 0.;
    SqrtS[42] = 0.;
    SqrtS[44] = 0.;
    SqrtS[45] = 0.;
    SqrtS[47] = 0.;
    SqrtS[48] = 0.;//dismantling 100 and 300 days
    SqrtS[49] = 0.;//dismantling 500 days    
    SqrtS[50] = 0.;//dismantling 500 days
    SqrtS[51] = 0.;//dismantling 500 days

    SqrtS[1] = 7; //2010
    SqrtS[4] = 7; //2011
    SqrtS[7] = 8; //2012
    SqrtS[16] = 13; //2015
    SqrtS[19] = 13; //2016
    SqrtS[22] = 13; //2017
    SqrtS[25] = 13; //2018
    SqrtS[28] = 0.; //2019
    SqrtS[31] = 0.; //2020
    SqrtS[34] = 0; //2021
    SqrtS[37] = 13.6; //2022
    SqrtS[40] = 13.6; //2023
    SqrtS[43] = 13.6; //2024
    SqrtS[46] = 13.6; //2025
                    // SqrtS[0] = 0.;
                    // SqrtS[1] = 13.6;
                    // SqrtS[2] = 0.;
                    // SqrtS[3] = 0.;
                    // SqrtS[4] = 13.6;
                    // SqrtS[5] = 0.;
                    // SqrtS[6] = 0.;
                    // SqrtS[7] = 13.6; 
                    // SqrtS[8] = 0.;
                    // SqrtS[9] = 0.; 
                    // SqrtS[10] = 0.; 
                    // SqrtS[11] = 0.; 
                    // SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 3-----------------------//
    else
        {
            std::cout<<"Please select : 0 for no dismantling (by debault); 1 for 100 days of dismantling; 2 for 300 days of dismantling and 3 for 500 days of dismantling :D"<<std::endl;
        }
//-------------------end of error-----------------------//


}


//-----------------------------------------------//
// scenario 0 : no dismanteling
// scenario 1 : dismanteling of 100 days
// scenario 2 : dismanteling of 300 days 
// scenario 3 : dismanteling of 500 days 
// The expected scenario atm(April 2023) is 300 fb-1, femto gives the option of adding lumi that will be separeted in half between 2024 and 2025==> (300+femto)
//-----------------------------------------------//
// function good when doing thepredictions in March 2023 ...
void MakeRun3Scenario(int scenario=0, int femto=0){
    
    bool debug=false;
    string filename = "./realistic_scenario_2025.txt";
    int shiftdays= 4660; //4660: 1st of january 2023, 4750 with the early historic of 2023

    //---------Except you need to change temperatures or number of days of running/shutdown/dismanteling, nothing needs to be changed after this--//
    int shiftperiodes = 0;
    int shiftdayNumber = 0;
    if (shiftdays > 4660){shiftdayNumber = shiftdays-4660;shiftperiodes = shiftdayNumber/5;}//There are 90 days in the temp histo of 2023 (18*5=90) => this shift day thing is only valid for the first period of 2023 (29 periods)
    //but can be easily reused for other periods but numbers have to be changed
    std::ofstream ofs (filename,std::ofstream::out);
    //------------
    // temperature
    //------------
    
    float Ton=4.;//4 by default
    float Toff = 6.;//6 by default
    float Toff2 = 0.;//0 by default
    float Toff3 = 5.;
    float RT = 20.;//20 by default
    float RT2 = 15.;//20 by default
    
    // temperature shift
    float T1=19.; //19 In Run 2
    float T2=24.; //24 In 2018
    float T3=24.; //was29 but currently 24 In Run 3


    //---------
    // periodes
    //---------
    if (scenario==0)//no dismantling
        {
            const int periodes = 9; //was 15 , until 2023
                Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24 //2025
                                         }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3 //2025
                    //RT2,   RT2,    RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    //RT2                //dismantling of 500 days
                };

            //-----
            // Lumi
            //-----
    
            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;


            
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;//2023
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;//2024
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; //2025
                    SqrtS[8] = 0.;

                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  
        }

//-------------------end of 0-----------------------//

    else if(scenario==1)//dematneling of 100 
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                20,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

    
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  

        }

//-------------------end of 1-----------------------//


    else if (scenario == 2)
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                60,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;  
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();          
                      
        }

//-------------------end of 2-----------------------//


    else if (scenario == 3)
        {
            const int periodes = 13;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                27
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 3-----------------------//
    else
        {
            std::cout<<"Please select : 0 for no dismantling (by debault); 1 for 100 days of dismantling; 2 for 300 days of dismantling and 3 for 500 days of dismantling :D"<<std::endl;
        }
//-------------------end of error-----------------------//    
}


//-----------------------------------------------//
// scenario 0 : no dismanteling
// scenario 1 : dismanteling of 100 days
// scenario 2 : dismanteling of 300 days 
// scenario 3 : dismanteling of 500 days 
// The expected scenario atm(April 2023) is 300 fb-1, femto gives the option of adding lumi that will be separeted in half between 2024 and 2025==> (300+femto)
//-----------------------------------------------//
// function good when doing thepredictions in March 2023 ...
void MakeRun20252026Scenario(int scenario=0, int femto=0){
    
    bool debug=false;
    string filename = "./realistic_scenario_2025_2026.txt";
    int shiftdays= 5391; //5392: 1st of january 2025

    //---------Except you need to change temperatures or number of days of running/shutdown/dismanteling, nothing needs to be changed after this--//
    int shiftperiodes = 0;
    int shiftdayNumber = 0;
    if (shiftdays > 5391){shiftdayNumber = shiftdays-5391;shiftperiodes = shiftdayNumber/5;}//There are 90 days in the temp histo of 2023 (18*5=90) => this shift day thing is only valid for the first period of 2023 (29 periods)
    //but can be easily reused for other periods but numbers have to be changed
    std::ofstream ofs (filename,std::ofstream::out);
    //------------
    // temperature
    //------------
    
    float Ton=4.;//4 by default
    float Toff = 6.;//6 by default
    float Toff2 = 0.;//0 by default
    float Toff3 = 5.;
    float RT = 20.;//20 by default
    float RT2 = 15.;//20 by default
    
    // temperature shift
    float T1=19.; //19 In Run 2
    float T2=24.; //24 In 2018
    float T3=24.; //was29 but currently 24 In Run 3


    //---------
    // periodes
    //---------
    if (scenario==0)//no dismantling
        {
            const int periodes = 6; 
                Int_t t_at_T[periodes] = {
                                                24-shiftperiodes, 28, 21, //2025
                                                25, 7, 41 //2026
                                         }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2025
                    Toff3, Ton-T3, Toff3 //2026
                };

            //-----
            // Lumi
            //-----
    
            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 120.;//2025
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 30.;//2026
                Lumi[5] = 0.;



            
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;//2025
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;//2026
                    SqrtS[5] = 0.;


                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2025;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2025)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2025)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2025)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2025)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  
        }

//-------------------end of 0-----------------------//

    else if(scenario==1)//dematneling of 100 
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                20,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

    
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  

        }

//-------------------end of 1-----------------------//


    else if (scenario == 2)
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                60,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;  
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();          
                      
        }

//-------------------end of 2-----------------------//


    else if (scenario == 3)
        {
            const int periodes = 13;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                27
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 3-----------------------//
    else
        {
            std::cout<<"Please select : 0 for no dismantling (by debault); 1 for 100 days of dismantling; 2 for 300 days of dismantling and 3 for 500 days of dismantling :D"<<std::endl;
        }
//-------------------end of error-----------------------//    
}

//-----------------------------------------------//
// scenario 0 : no dismantling
// scenario 1 : dismantling of 100 days
// scenario 2 : dismantling of 200 days 
// scenario 3 : dismantling of 300 days
// scenario 4 : dismantling of 400 days
// scenario 5 : dismantling of 500 days
// scenario 6 : dismantling of 600 days
// scenario 7 : dismantling of 700 days
// scenario 8 : dismantling of 800 days
// scenario 9 : dismantling of 900 days
// scenario 10 : dismantling of 1000 days
// The expected scenario atm(April 2023) is 300 fb-1, femto gives the option of adding lumi that will be separeted in half between 2024 and 2025==> (300+femto)
//-----------------------------------------------//

void MakeRun3_10Scenario(int scenario=0, int femto=0){
    
    bool debug=false;
    string scenari = std::to_string(scenario);
    int FullLumi = 300+femto;
    string fulllumi = std::to_string(FullLumi);
    string filename = "./realistic_scenario_"+fulllumi+"fb_"+scenari+".txt";
    int shiftdays= 4750; //4660: 1st of january 2023, 4750 with the early historic of 2023

    //---------Except you need to change temperatures or number of days of running/shutdown/dismantling, nothing needs to be changed after this--//
    int shiftperiodes = 0;
    int shiftdayNumber = 0;
    if (shiftdays > 4660){shiftdayNumber = shiftdays-4660;shiftperiodes = shiftdayNumber/5;}//There are 90 days in the temp histo of 2023 (18*5=90) => this shift day thing is only valid for the first period of 2023 (29 periods)
    //but can be easily reused for other periods but numbers have to be changed
    std::ofstream ofs (filename,std::ofstream::out);
    //------------
    // temperature
    //------------
    
    float Ton=4.;//4 by default
    float Toff = 6.;//6 by default
    float Toff2 = 0.;//0 by default
    float Toff3 = 5.;
    float TCave = 15;
    float RT = 20.;//20 by default
    float RT2 = 15.;//20 by default
    
    // temperature shift
    float T1=19.; //19 In Run 2
    float T2=24.; //24 In 2018
    float T3=24.; //was29 but currently 24 In Run 3


    //---------
    // periodes
    //---------
    if (scenario==0)//no dismanteling
        {
            // const int periodes = 9; //was 15 , until 2023
            //     Int_t t_at_T[periodes] = {
            //                                     29-shiftperiodes, 18, 26, //2023

            //                                     25, 23, 25, //2024

            //                                     25, 24, 24 //2025
            //                              }; // 5 days periods => 73 periods 
            // Double_t T_95[periodes] = 
            //     {
            //         Toff3, Ton-T3, Toff3, //2023

            //         Toff3, Ton-T3, Toff3, //2024

            //         Toff3, Ton-T3, Toff3 //2025
            //         //RT2,   RT2,    RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
            //         //RT2                //dismantling of 500 days
            //     };

            // const int periodes = 15; // , 3 month cold 
            //     Int_t t_at_T[periodes] = {
            //                                     0,13,18,18,6, //2023: 0 and  13 since we are starting the predictions for the 1st of March 2013

            //                                     12,15,24,16,6, //2024

            //                                    12,15,25,15,6//2025
            //                              }; // 5 days periods => 73 periods 


            // const int periodes = 15; //, 2 month cold 
            //     Int_t t_at_T[periodes] = {
            //                                     0,13,18,18,6, //2023: 0 and  13 since we are starting the predictions for the 1st of March 2013

            //                                     6,19,24,18,6, //2024

            //                                    6,18,25,18,6//2025
            //                              }; // 5 days periods => 73 periods 


            const int periodes = 15; // , 1 month cold 
                Int_t t_at_T[periodes] = {
                                                0,13,18,18,6, //2023: 0 and  13 since we are starting the predictions for the 1st of March 2013

                                                0,22,24,21,6, //2024

                                               0,21,25,21,6//2025
                                         }; // 5 days periods => 73 periods 


            Double_t T_95[periodes] = 
                {
                    Toff3,Ton-T3, Ton-T3, Ton-T3,Toff3, //2023

                    Toff3, Ton-T3,Ton-T3,Ton-T3, Toff3, //2024

                    Toff3, Ton-T3,Ton-T3,Ton-T3, Toff3 //2025

                };

            //-----
            // Lumi
            //-----
    
            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 0.;
                Lumi[2] = 32.4;//2023
                Lumi[3] = 0.;
                Lumi[4] = 0.;

                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2024
                Lumi[8] = 0.;
                Lumi[9] = 0.;

                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 93.5+femto/2;//2025
                Lumi[13] = 0.;
                Lumi[14] = 0.;


            
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 0.;
                    SqrtS[2] = 13.6;//2023
                    SqrtS[3] = 0.;
                    SqrtS[4] = 0.;

                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6;//2024
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.;

                    SqrtS[10] = 0.;
                    SqrtS[11] = 0.;
                    SqrtS[12] = 13.6; //2025
                    SqrtS[13] = 0.;
                    SqrtS[14] = 0.;

                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%5==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/5 << std::endl;ofs <<"# Starting new year: " << startingYear+i/5 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/5)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/5)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/5)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/5)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  
        }

//-------------------end of 0-----------------------//

    else if(scenario==1)//dematneling of 100 
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                20,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

    
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  

        }

//-------------------end of 1-----------------------//
else if(scenario==2)//dematneling of 200 
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                40,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;

    
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();  

        }

//-------------------end of 2-----------------------//

    else if (scenario == 3) // 300 days
        {
            const int periodes = 12;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                60,  0,  0  //2026
                                     }; // 5 days periods => 73 periods 
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2//dismanteling of 100 and 300 days +> RT2//,RT2,RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.;  
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close();          
                      
        }

//-------------------end of 3-----------------------//


    else if (scenario == 4) // 400 days
        {
            const int periodes = 13;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                7
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 4-----------------------//
else if (scenario == 5) // 500 days
        {
            const int periodes = 13;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                27
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 5-----------------------//

else if (scenario == 6) // 600 days
        {
            const int periodes = 13;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                47
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 6-----------------------//


else if (scenario == 7) // 700 days
        {
            const int periodes = 13;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                67
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2                //dismantling of 500 days
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;


                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.; 
                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 7-----------------------//

else if (scenario == 8) // 800 days
        {
            const int periodes = 16;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                63,  0,  0, //2027
                                                6
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2,      RT2,   RT2,//dismantling of 500 days
                    RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Lumi[13] = 0.;
                Lumi[14] = 0.;
                Lumi[15] = 0.;
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.;
                    SqrtS[13] = 0.; 
                    SqrtS[14] = 0.; 
                    SqrtS[15] = 0.; 



                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 8-----------------------//


else if (scenario == 9) // 900 days
        {
            const int periodes = 16;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 24, //2025
                                                73,  0,  0,  //2026
                                                73,  0,  0, //2027
                                                27
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, Toff3, //2025
                    RT2,      RT2,   RT2,//dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2,      RT2,   RT2,//dismantling of 500 days
                    RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Lumi[13] = 0.;
                Lumi[14] = 0.;
                Lumi[15] = 0.;
                
                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.;
                    SqrtS[13] = 0.; 
                    SqrtS[14] = 0.; 
                    SqrtS[15] = 0.; 



                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 9-----------------------//


else if (scenario == 10) // 1000 days
        {
            const int periodes = 16;
            Int_t t_at_T[periodes] = {
                                                29-shiftperiodes, 18, 26, //2023
                                                25, 23, 25, //2024
                                                25, 24, 12,12, //2025
                                                73,  0,  //2026
                                                73,  0,  0, //2027
                                                47
                                     }; // 5 days periods => 73 periods
            Double_t T_95[periodes] = 
                {
                    Toff3, Ton-T3, Toff3, //2023
                    Toff3, Ton-T3, Toff3, //2024
                    Toff3, Ton-T3, TCave, RT2, //2025
                    RT2,      RT2,  //dismantling of 100 and 300 days +> RT2//,RT2,RT2
                    RT2,      RT2,   RT2,//dismantling of 500 days
                    RT2
                };

            Float_t *Lumi = new Float_t[periodes]; // in fb-1
                Lumi[0] = 0.;
                Lumi[1] = 75.;//2023
                Lumi[2] = 0.;
                Lumi[3] = 0.;
                Lumi[4] = 93.5+femto/2;//2024
                Lumi[5] = 0.;
                Lumi[6] = 0.;
                Lumi[7] = 93.5+femto/2;//2025
                Lumi[8] = 0.;
                Lumi[9] = 0.;
                Lumi[10] = 0.;
                Lumi[11] = 0.;
                Lumi[12] = 0.;
                Lumi[13] = 0.;
                Lumi[14] = 0.;
                Lumi[15] = 0.;

                Float_t *SqrtS = new Float_t[periodes]; // in TeV
                    SqrtS[0] = 0.;
                    SqrtS[1] = 13.6;
                    SqrtS[2] = 0.;
                    SqrtS[3] = 0.;
                    SqrtS[4] = 13.6;
                    SqrtS[5] = 0.;
                    SqrtS[6] = 0.;
                    SqrtS[7] = 13.6; 
                    SqrtS[8] = 0.;
                    SqrtS[9] = 0.; 
                    SqrtS[10] = 0.; 
                    SqrtS[11] = 0.; 
                    SqrtS[12] = 0.;
                    SqrtS[13] = 0.; 
                    SqrtS[14] = 0.; 
                    SqrtS[15] = 0.; 



                // Generate scenario description file
                //-----------------------------------
    
                    Int_t maxTime=0;
                    Int_t stepInYear=0;
                    Int_t startingYear=2023;
                    Int_t dayNumber=1+shiftdays;
                    std::cout<<"#define StepInDays 1"<<std::endl;
                    std::cout<<"Index dayInYear sqrt(s) lumi temperature"<<std::endl;           
                    for(Int_t i=0; i<periodes; i++){
                        if(i%3==0) {stepInYear=0; std::cout << "# Starting new year: " << startingYear+i/3 << std::endl;ofs <<"# Starting new year: " << startingYear+i/3 << std::endl;}
                        maxTime += t_at_T[i];
                        // Loop over periodes steps
                        for(Int_t j=0; j<t_at_T[i]; j++){
                            // Loop over days
                            for(Int_t k=0; k<5; k++){
                                // if (dayNumber%365==0){stepInYear=0;}
                                        if((startingYear+i/3)>2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1<<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                std::cout << dayNumber <<" "<< stepInYear*5+k+1+shiftdayNumber <<" "<< SqrtS[i] <<" "<< Lumi[i]/(5.*t_at_T[i]) <<" "<< T_95[i] <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                //---------Fil section-----------//
                                if(ofs)
                                    {
                                        // if (dayNumber%365==0){ofs<<"Starting new year: " << startingYear+i/3+1 << std::endl;}//stepInYear=1;
                                        if((startingYear+i/3)>2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                        else if ((startingYear+i/3)==2023)
                                            {
                                                ofs << convertInt(dayNumber)<<" "<<convertInt(stepInYear*5+k+1+shiftdayNumber) <<" "<< convertFloat(SqrtS[i]) <<" "<< convertFloat(Lumi[i]/(5.*t_at_T[i])) <<" "<<convertFloat( T_95[i]) <<" "<< "0.0" <<" "<< "0.0"<< std::endl;
                                            }
                                    }
                                else {std::cout<<"no file"<<std::endl;}
                                

                                //--END of File Section------------//
                                dayNumber++;
                            }
                            stepInYear++;
                        }
                    }
                    if(debug) std::cout << " maxtime "<< maxTime << std::endl;
    
                   ofs.close(); 
        }

//-------------------end of 8-----------------------//
    else
        {
            std::cout<<"Please select : 0 for no dismantling (by debault); 1 for 100 days of dismantling; 2 for 300 days of dismantling and 3 for 500 days of dismantling :D"<<std::endl;
        }
//-------------------end of error-----------------------//

    
}

void MakeSimplifiedLumiTempScenario(int scenario, int femto, bool compute10=false){
    
    // MakeOld500fbScenario();//only simulation, does not take into account histo until begining of 2023
    // MakeRun3_10Scenario(scenario,femto);//Compute from 0 to 1000 days of dismantling and 300fb-1


    // MakeRun3Scenario(scenario, femto);// computes the simulation from early 2023 to 2025 and beyond depending on the scenarios
    
    
    // OldMakeOld500fbScenario();
    //Combine the output pf Run3Scenario with temp_histo.txt to get the most accurate output


    // !! Latest version of the Predictions !!
    MakeRun20252026Scenario(0,0);
    return;
}
