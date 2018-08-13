# quarknet_root
Quarknet Data preparation/analysis using ROOT

Scripts for Data Analysis from Quarknet's Muon Detector in ROOT.

First scripts written in C++/ROOT, it clearly lacks style and can be greatly optimized.
The code should still work and get the job done.

copiar.C : merges datafiles in order to have them all in one TTree, the alternative is to load different files separatedly and then merge the data on ROOT.

simplev2.C : loads QuarkNet data file and exports it to a ROOT TTree

detalle.C : Gives the detail of the different events in the data file, this script does not give out much relevant information for analysis, but it was useful for some debugging of the device since the GPS was faulty.

timedependent.C : script that collects muon decay in the scintillators and then makes a histogram in order to extract the muon lifetime. (Does not distingish between charges)
