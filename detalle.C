// Script that reads through all the tree and recopiles some relevant data
// in form of counters.
// The data it saves is the following:
//
// Distribution of activaed scintillators per event:
//          4 configs when 1 scintillator signal
//          6 configs when 2 scintillators signal
//          4 configs when 3 scintillators signal
//          1 config when 4 scintillators signal
// Number of entries in the TTree
// NUmber of events in the TTree
// Length (in entries) of the event
// Total time(real time) that the TTree spans
//
// The original purpose of the script was to compare GPS data with non-GPS data
// and to find out if non-GPS data was useful for certain
// studies (aka flux, lifetime)
//
// Pablo Bravo Collado        ptbravo@uc.cl

#define detalle_cxx
// The class definition in detalle.h has been generated automatically
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
// root> T->Process("detalle.C")
// root> T->Process("detalle.C","some options")
// root> T->Process("detalle.C+")
//


#include "detalle.h"
#include <TH2.h>
#include <TStyle.h>

Int_t entradas, eventos;

Int_t l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19; //Largo del evento
//Tipo de Coincidencia en el evento
Int_t uno, dos, tres, cuatro;
Int_t uno_a, uno_b, uno_c, uno_d;
Int_t dos_a, dos_b, dos_c, dos_d, dos_e, dos_f;
Int_t tres_a, tres_b, tres_c, tres_d;
Long_t t_start, t_end, t_total;
Bool_t r0, r1, r2, r3;
Bool_t f0, f1, f2, f3;
Int_t n;
Bool_t entradas_check;

void detalle::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   entradas = 0;
   eventos = 0;
   uno = 0;
   dos = 0;
   tres = 0;
   cuatro = 0;
   uno_a = 0;
   uno_b = 0;
   uno_c = 0;
   uno_d = 0;
   dos_a = 0;
   dos_b = 0;
   dos_c = 0;
   dos_d = 0;
   dos_e = 0;
   dos_f = 0;
   tres_a = 0;
   tres_b = 0;
   tres_c = 0;
   tres_d = 0;
   t_start = 0;
   t_end = 0;
   t_total = 0;
   entradas_check = 0;

}

void detalle::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t detalle::Process(Long64_t entry)
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
   entradas += 1;
   // Tiempo
   if (entry==1) {t_start = *t_sec.Get();}
   if (entry==98096406) {t_end = *t_sec.Get();} //Encontré la ultima entrada a
   //mano, mala idea.

   //Revisar evento
   if ((entradas<98096406) && (*trigger.Get()==true)) {
       cout << eventos << endl;
       eventos += 1;
       n = 1;
       //if (*ch0_re.Get()) {cout << *ch0_t_re.Get() << endl;}
       r0 = 0;
       r1 = 0;
       r2 = 0;
       r3 = 0;
       f0 = 0;
       f1 = 0;
       f2 = 0;
       f3 = 0;

       //Recorrer el evento y asignar rising edges para cada canal
       //No recuerdo si asignar tambien falling edges significa un cambio
       //rX se asignaría cuando ambos están presentes en el evento.
       if (*ch0_re.Get()==true) {r0 = 1;}
       if (*ch1_re.Get()==true) {r1 = 1;}
       if (*ch2_re.Get()==true) {r2 = 1;}
       if (*ch3_re.Get()==true) {r3 = 1;}
       fReader.SetEntry(entry+n);
       while (*trigger.Get()==false) {
           if (*ch0_re.Get()==true) {r0 = 1;}
           if (*ch1_re.Get()==true) {r1 = 1;}
           if (*ch2_re.Get()==true) {r2 = 1;}
           if (*ch3_re.Get()==true) {r3 = 1;}
           n += 1;
           fReader.SetEntry(entry+n);
       }

       //Largo
       if (n==1) {l1 += 1;}
       if (n==2) {l2 += 1;}
       if (n==3) {l3 += 1;}
       if (n==4) {l4 += 1;}
       if (n==5) {l5 += 1;}
       if (n==6) {l6 += 1;}
       if (n==7) {l7 += 1;}
       if (n==8) {l8 += 1;}
       if (n==9) {l9 += 1;}
       if (n==10) {l10 += 1;}
       if (n==11) {l11 += 1;}
       if (n==12) {l12 += 1;}
       if (n==13) {l13 += 1;}
       if (n==14) {l14 += 1;}
       if (n==15) {l15 += 1;}
       if (n==16) {l16 += 1;}
       if (n==17) {l17 += 1;}
       if (n==18) {l18 += 1;}
       if (n==19) {l19 += 1;}

       //Coincidencias
       if ((r0==1) && (r1==0) && (r2==0) && (r3==0)) {
           uno += 1;
           uno_a += 1;
       }
       if ((r0==0) && (r1==1) && (r2==0) && (r3==0)) {
           uno += 1;
           uno_b += 1;
       }
       if ((r0==0) && (r1==0) && (r2==1) && (r3==0)) {
           uno += 1;
           uno_c += 1;
       }
       if ((r0==0) && (r1==0) && (r2==0) && (r3==1)) {
           uno += 1;
           uno_d += 1;
       }
       if ((r0==1) && (r1==1) && (r2==0) && (r3==0)) {
           dos += 1;
           dos_a += 1;
       }
       if ((r0==1) && (r1==0) && (r2==1) && (r3==0)) {
           dos += 1;
           dos_b += 1;
       }
       if ((r0==1) && (r1==0) && (r2==0) && (r3==1)) {
           dos += 1;
           dos_c += 1;
       }
       if ((r0==0) && (r1==1) && (r2==1) && (r3==0)) {
           dos += 1;
           dos_d += 1;
       }
       if ((r0==0) && (r1==1) && (r2==0) && (r3==1)) {
           dos += 1;
           dos_e += 1;
       }
       if ((r0==0) && (r1==0) && (r2==1) && (r3==1)) {
           dos += 1;
           dos_f += 1;
       }
       if ((r0==1) && (r1==1) && (r2==1) && (r3==0)) {
           tres += 1;
           tres_a += 1;
       }
       if ((r0==1) && (r1==1) && (r2==0) && (r3==1)) {
           tres += 1;
           tres_b += 1;
       }
       if ((r0==1) && (r1==0) && (r2==1) && (r3==1)) {
           tres += 1;
           tres_c += 1;
       }
       if ((r0==0) && (r1==1) && (r2==1) && (r3==1)) {
           tres += 1;
           tres_d += 1;
       }
       if ((r0==1) && (r1==1) && (r2==1) && (r3==1)) {
           cuatro += 1;
       }
   }
   return kTRUE;
}

void detalle::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void detalle::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
    //cout << entradas << endl;
    t_total = t_end - t_start;
    cout << "Entradas" << "\t" <<entradas << "\t" << "Eventos" << "\t" << eventos << endl;
    cout << "t_end:" << "\t" << t_end << "\t" << "t_start" << t_start << "\t" << "Duracion" << "\t" << t_total << endl;
    cout << "Largo de evento:" << "\t" << l1 << "\t" << l2 << "\t" << l3 << "\t" << l4 << "\t" << l5 << "\t" << l6 << "\t" << l7 << "\t" << l8 << "\t" << l9 << "\t" << l10 << "\t" << l11 << "\t" << l12 << "\t" << l13 << "\t" << l14 << "\t" << l15 << "\t" << l16 << "\t" << l17 << "\t" << l18 << "\t" << l9 << endl;
    cout << "1 Coincidencias:" << "\t" << uno << "\t" << uno_a << "\t" << uno_b << "\t" << uno_c << "\t" << uno_d << endl;
    cout << "2 Coincidencias:" << "\t" << dos << "\t" << dos_a << "\t" << dos_b << "\t" << dos_c << "\t" << dos_d << "\t" << dos_e << "\t" << dos_f << endl;
    cout << "3 Coincidencias:" << "\t" << tres << "\t" << tres_a << "\t" << tres_b << "\t" << tres_c << "\t" << tres_d << endl;
     cout << "4 Coincidencias:" << "\t" << cuatro << endl;

}
