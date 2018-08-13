// Script that calculates the lifetime of the muon via an expo fit
// of the time difference between the muon absorption and the electron emission.
//
// The code takes in account the following cases (a,b,c,d):
//
// Scintillator 0 :::::::::::::::::   |   a            |
//                                    |   |            |
// Scintillator 1 :::::::::::::::::   X-> |            |  c
//                                        |            |  |
// Scintillator 2 :::::::::::::::::       b            X->|
//                                                        |
// Scintillator 3 :::::::::::::::::                       d
//
// Where the events with x represent the muon absorption, from outside->x, and
// {a,b,c,d} represent the electron emission from x->{a,b,c,d}
//
// Pablo Bravo Collado        ptbravo@uc.cl

#define timedependent_cxx
// The class definition in timedependent.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("timedependent.C")
// root> T->Process("timedependent.C","some options")
// root> T->Process("timedependent.C+")
//


#include "timedependent.h"
#include <TH2.h>
#include <TStyle.h>

Bool_t muon_detect_1, muon_detect_2, electron_up_1, electron_down_1, electron_up_2, electron_down_2;
Int_t n, m;
Bool_t r0, r1, r2, r3, f0, f1, f2, f3;
Bool_t er0, er1, er2, er3, ef0, ef1, ef2, ef3;
Int_t c1_up, c1_down, c2_up, c2_down;
Long_t time_muon, time_electron, time_decay;
Bool_t decay_event, decay1, decay2;
TH1* h1 = NULL;
Long_t tm0, tm1, tm2, tm3;
Long_t te0, te1, te2, te3;
Int_t nm0, nm1, nm2, nm3;
Int_t ne0, ne1, ne2, ne3;
Float_t tn_m0, tn_m1, tn_m2, tn_m3;
Float_t tn_e0, tn_e1, tn_e2, tn_e3;
Int_t contador;

void timedependent::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   c1_up = 0;
   c1_down = 0;
   c2_up = 0;
   c2_down = 0;
   //gStyle->SetOptStat(0);
   h1 = new TH1F ("h1", "Tiempo de decaimiento, 178 horas", 16 ,0 ,10);
   h1->GetXaxis()->SetTitle("#Deltat (#mus)");
   h1->GetYaxis()->SetTitle("Eventos");
   //h1->SetOption("Show Fit Parameters");

}

void timedependent::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t timedependent::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetEntry(entry);

   if (entry < 98096406) {  //obtained manually, not good
       if (*trigger.Get()==true) {

           //Cycle Variables
           muon_detect_1 = 0;
           muon_detect_2 = 0;
           n = 1;
           m = 1;
           r0 = 0;
           r1 = 0;
           r2 = 0;
           r3 = 0;
           f0 = 0;
           f1 = 0;
           f2 = 0;
           f3 = 0;
           er0 = 0;
           er1 = 0;
           er2 = 0;
           er3 = 0;
           ef0 = 0;
           ef1 = 0;
           ef2 = 0;
           ef3 = 0;
           time_muon = 0;
           time_electron = 0;
           time_decay = 0;
           tm0 = 0;
           tm1 = 0;
           tm2 = 0;
           tm3 = 0;
           te0 = 0;
           te1 = 0;
           te2 = 0;
           te3 = 0;
           decay_event = 0;
           decay1 = 0;
           decay2 = 0;

           //Asignar tiempos a evento
           if (*ch0_re.Get()==true) {
               r0 = 1;
               tm0 = *t_sec.Get()*1000000000 + *t_nsec.Get();
               tn_m0 = *ch0_t_re.Get();
           }
           if (*ch1_re.Get()==true) {
               r1 = 1;
               tm1 = *t_sec.Get()*1000000000 + *t_nsec.Get();
               tn_m1 = *ch1_t_re.Get();
           }
           if (*ch2_re.Get()==true) {
               r2 = 1;
               tm2 = *t_sec.Get()*1000000000 + *t_nsec.Get();
               tn_m2 = *ch2_t_re.Get();
           }
           if (*ch3_re.Get()==true) {
               r3 = 1;
               tm3 = *t_sec.Get()*1000000000 + *t_nsec.Get();
               tn_m3 = *ch3_t_re.Get();
           }
           if (*ch0_fe.Get()==true) {f0 = 1;}
           if (*ch1_fe.Get()==true) {f1 = 1;}
           if (*ch2_fe.Get()==true) {f2 = 1;}
           if (*ch3_fe.Get()==true) {f3 = 1;}
           fReader.SetEntry(entry+n);
           while (*trigger.Get()==false) {
               if (*ch0_re.Get()==true) {
                   r0 = 1;
                   tm0 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_m0 = *ch0_t_re.Get();
               }
               if (*ch1_re.Get()==true) {
                   r1 = 1;
                   tm1 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_m1 = *ch1_t_re.Get();
               }
               if (*ch2_re.Get()==true) {
                   r2 = 1;
                   tm2 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_m2 = *ch2_t_re.Get();
               }
               if (*ch3_re.Get()==true) {
                   r3 = 1;
                   tm3 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_m3 = *ch3_t_re.Get();
               }
               if (*ch0_fe.Get()==true) {f0 = 1;}
               if (*ch1_fe.Get()==true) {f1 = 1;}
               if (*ch2_fe.Get()==true) {f2 = 1;}
               if (*ch3_fe.Get()==true) {f3 = 1;}
               n = n + 1;
               fReader.SetEntry(entry+n);
           }

           //Muon 1100
           if ((r0==1) && (r1==1) && (r2==0) && (r3==0) && (f0==1) && (f1==1) && (f2==0) && (f3==0)) {
               if (tm0 < tm1) {
                   muon_detect_1 = 1;
               }
               if (tm0 == tm1) {
                   if (tn_m0<tn_m1) {
                       muon_detect_1 = 1;
                   }
               }
           }

           //Muon 1110
           if ((r0==1) && (r1==1) && (r2==1) && (r3==0) && (f0==1) && (f1==1) && (f2==1) && (f3==0)) {
               if (tm0 < tm1 < tm2) {
                   muon_detect_2 = 1;
               }
               if (tm0 < tm1 == tm2) {
                   if (tn_m1 < tn_m2) {
                       muon_detect_2 = 1;
                   }
               }
               if (tm0 == tm1 << tm2) {
                   if (tn_m0 < tn_m1) {
                       muon_detect_2 = 1;
                   }
               }
               if (tm0 == tm1 == tm2) {
                   if (tn_m0 < tn_m1 < tn_m2) {
                       muon_detect_2 = 1;
                   }
               }
           }

           if (muon_detect_1 || muon_detect_2) {
               fReader.SetEntry(entry);
               if (muon_detect_1) {time_muon = *t_sec.Get()*1000000000 + *t_nsec.Get() + *ch1_t_re.Get();}
               if (muon_detect_2) {time_muon = *t_sec.Get()*1000000000 + *t_nsec.Get() + *ch2_t_re.Get();}
               fReader.SetEntry(entry+n);
               if (*ch0_re.Get()==true) {
                   er0 = 1;
                   te0 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_e0 = *ch0_t_re.Get();
               }
               if (*ch1_re.Get()==true) {
                   er1 = 1;
                   te1 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_e1 = *ch1_t_re.Get();
               }
               if (*ch2_re.Get()==true) {
                   er2 = 1;
                   te2 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_e2 = *ch2_t_re.Get();
               }
               if (*ch3_re.Get()==true) {
                   er3 = 1;
                   te3 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                   tn_e3 = *ch3_t_re.Get();
               }
               if (*ch0_fe.Get()==true) {ef0 = 1;}
               if (*ch1_fe.Get()==true) {ef1 = 1;}
               if (*ch2_fe.Get()==true) {ef2 = 1;}
               if (*ch3_fe.Get()==true) {ef3 = 1;}
               fReader.SetEntry(entry+n+m);
               while (*trigger.Get()==false) {
                   if (*ch0_re.Get()==true) {
                       er0 = 1;
                       te0 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                       tn_e0 = *ch0_t_re.Get();
                   }
                   if (*ch1_re.Get()==true) {
                       er1 = 1;
                       te1 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                       tn_e1 = *ch1_t_re.Get();
                   }
                   if (*ch2_re.Get()==true) {
                       er2 = 1;
                       te2 = *t_sec.Get()*1000000000 + *t_nsec.Get();
                       tn_e2 = *ch2_t_re.Get();
                   }
                   if (*ch3_re.Get()==true) {
                       er3 = 1;
                       te3 = *t_sec.Get()*1000000000 + *t_nsec.Get() + round(*ch3_t_re.Get());
                       tn_e3 = *ch3_t_re.Get();
                   }
                   if (*ch0_fe.Get()==true) {ef0 = 1;}
                   if (*ch1_fe.Get()==true) {ef1 = 1;}
                   if (*ch2_fe.Get()==true) {ef2 = 1;}
                   if (*ch3_fe.Get()==true) {ef3 = 1;}
                   m += 1;
                   fReader.SetEntry(entry+n+m);
               }
               cout << er0 << er1 << er2 << er3 << "\t" << ef0 << ef1 << ef2 << ef3 << endl;

               //Muon 1100
               if (muon_detect_1) {
                   time_electron = te1 + round (tn_e1);
                   time_decay = time_electron - time_muon;
                   //electron up 1100
                   if ((er0==1) && (er1==1) && (er2==0) && (er3==0) && (ef0==1) && (ef1==1) && (ef2==0) && (ef3==0)) {
                       if (te1<te0) {
                           c1_up += 1;
                           decay_event = 1;
                           decay1 = 1;
                       }
                       if (te1 == te0) {
                           if (tn_e1 < tn_e0) {
                               c1_up += 1;
                               decay_event = 1;
                               decay1 = 1;
                           }
                       }
                   }


                   //electron down 0110
                   if ((er0==0) && (er1==1) && (er2==1) && (er3==0) && (ef0==0) && (ef1==1) && (ef2==1) && (ef3==0)) {
                       if (te1<te2) {
                           c1_down += 1;
                           decay_event = 1;
                           decay1 = 1;
                       }
                       if (te1 == te2) {
                           if (tn_e1 < tn_e2) {
                               c1_down += 1;
                               decay_event = 1;
                               decay1 = 1;
                           }
                       }
                   }
               }

               if (muon_detect_2) {
                   time_electron = te2 + round (tn_e2);
                   time_decay = time_electron - time_muon;
                   //electron up 0110
                   if ((er0==0) && (er1==1) && (er2==1) && (er3==0) && (ef0==0) && (ef1==1) && (ef2==1) && (ef3==0)) {
                       if (te2<te1) {
                           c2_up += 1;
                           decay_event = 1;
                           decay2 = 1;
                       }
                       if (te2 == te1) {
                           if (tn_e2 < tn_e1) {
                               c2_up += 1;
                               decay_event = 1;
                               decay2 = 1;
                           }
                       }
                   }
                   //electron down 0011
                   if ((er0==0) && (er1==0) && (er2==1) && (er3==1) && (ef0==0) && (ef1==0) && (ef2==1) && (ef3==1)) {
                       if (te2<te3) {
                           c2_down += 1;
                           decay_event = 1;
                           decay2 = 1;
                       }
                       if (te2 == te3) {
                           if (tn_e2 < tn_e3) {
                               c2_down += 1;
                               decay_event = 1;
                               decay2 = 1;
                           }
                       }
                   }
               }
               fReader.SetEntry(entry+n);
               if (decay1) {
                   time_electron = *t_sec.Get()*1000000000 + *t_nsec.Get() + round(*ch1_t_re.Get());
               }
               if (decay2) {
                   time_electron = *t_sec.Get()*1000000000 + *t_nsec.Get() + round(*ch2_t_re.Get());
               }
            }
            if (decay_event == 1) {
                time_decay = time_electron - time_muon;
               if (time_decay/1000.0>0) {
                   h1->Fill(time_decay/1000.000);
               }
               cout << c1_up+c1_down+c2_up+c2_down << "\t" << c1_up << "\t" << c1_down << "\t" << c2_up << "\t" << c2_down << endl;
           }
       }
    }
   return kTRUE;
}

void timedependent::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void timedependent::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
    gStyle->SetOptFit();
    h1->Fit("expo");
    h1->Draw();
    //h1->Update();
    cout << contador << endl;

}
