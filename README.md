# Code for predicting full depletion voltage evolution

Code for making predictions for the full depletion voltage using data up until a point and using the Hamburg Model to predit the evolution of Vfd.


## EnvConditions

Codes and data files for creating an luminosity and temperature scenario.
Main code is MakeSimplifiedLumiTempScenario.C file  (use root to compile):

The code is quie long but quite easy. Look at the MakeSimplifiedLumiTempScenario()function at the end that calls the correct function to make the prediction.
The last one used is MakeRun20252026Scenario(0,0) => (0,0) are the only value possible at the moment, see the comment around the MakeRun20252026Scenario function.

The predictions are made day by day. What we call periods in the code are set of 5 days. So in a year, there are 73 periods of 5 days.

The code will produce a txt file  like "realistic_scenario_2025_2026.txt"

!! It does not contain the data. First, you have to check the indices of the days of both data and simulation files and see if there are matching.

=> Like "realistic_scenario_2025_2026.txt" starts at 5392 since there is a
shiftdays parameter of 5391.


When Jean-Laurent gives you the data which is a txt file that looks like "realistic_scenario_2025_2026.txt", you have to use these two macros (only if you see that it is needed)

If you need to shift the value of the first column (the day ID let's say), you can run the ShiftTempHistory.sh code (really easy ot use).

You can also remove the first colmumn of a scenario file with ModifyTempistory.sh (also really easy to use).

## InputData

All input information needed for the predictions like fluence, temperature and leakage current maps. A code allows to merge everything in a single .root file.
You don't really need to change the code inside that directory.

## Predictions

Directory where you combine data and simulation to make the final plots.

The reference scenario with the data is : public/VdepEvolution/Predictions/Inputs/temphistory_reference_2010_2024.txt

The last scenario used is : public/VdepEvolution/Predictions/Inputs/realistic_scenario_150fb_2025_2026.txt

The Hamburg Model is used to make the predictions, see : public/VdepEvolution/Predictions/include/HamburgModelFactory.cc.

The two functions to look at are "runSimuForAllModules" and "runSimuForAvgModules".

In the first one, you can actually select the modules you wan to run on (good for analysing spcific Power Supplies). The second one makes the predictions averaging the behavior of all the modules of a layer/ ring

With these two functions comes two way of making the predictions :

!! please check the input and the parameters before running the code !!

public/VdepEvolution/Predictions/ComputeVdepEvolution.C (make)

public/VdepEvolution/Predictions/ComputeVdepEvolution_perlayer.C (make)

When you are done with that, yo ucan make the plots. There are many you can produce (using root to compile with .L):

- CompareDetidPrediction.C : Compare Vfd preditions by taking the mean,max and min value for  a set of modules

- CompareDeltaVfdDetidPrediction.C : Compare DeltaVfd preditions by taking the mean,max and min value for  a set of modules

- plot_IntLumi.C : Plot Integrated luminosity

- plot_Temp_L.C : Plot temprature w.r.t time

- plot_Temp.C : Plot temprature w.r.t time (I don't remember the difference and I think both works ina the same way)

- plot_Vdep.C : Plot vdep evolution w.r.t time
 
- plot_VdepLumi.C :Plot vdep evolution w.r.t integrated lumi

- plotDeltaV_fd.C : Plot both initial and final vfd value (after predictions) in a signle plot for all layers

======================

Last Update : 13/03/2025 Paul Vaucelle (Ph.D 2022-2025) BZH



