//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug  2 10:42:51 2017 by ROOT version 6.08/04
// from TTree vidatree/Tree del experimento
// found on file: vida2.root
//////////////////////////////////////////////////////////

#ifndef timedependent_h
#define timedependent_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class timedependent : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Long64_t> t_sec = {fReader, "t_sec"};
   TTreeReaderValue<Long64_t> t_nsec = {fReader, "t_nsec"};
   TTreeReaderValue<Bool_t> trigger = {fReader, "trigger"};
   TTreeReaderValue<Bool_t> ch0_re = {fReader, "ch0_re"};
   TTreeReaderValue<Bool_t> ch0_fe = {fReader, "ch0_fe"};
   TTreeReaderValue<Double_t> ch0_t_re = {fReader, "ch0_t_re"};
   TTreeReaderValue<Double_t> ch0_t_fe = {fReader, "ch0_t_fe"};
   TTreeReaderValue<Bool_t> ch1_re = {fReader, "ch1_re"};
   TTreeReaderValue<Bool_t> ch1_fe = {fReader, "ch1_fe"};
   TTreeReaderValue<Double_t> ch1_t_re = {fReader, "ch1_t_re"};
   TTreeReaderValue<Double_t> ch1_t_fe = {fReader, "ch1_t_fe"};
   TTreeReaderValue<Bool_t> ch2_re = {fReader, "ch2_re"};
   TTreeReaderValue<Bool_t> ch2_fe = {fReader, "ch2_fe"};
   TTreeReaderValue<Double_t> ch2_t_re = {fReader, "ch2_t_re"};
   TTreeReaderValue<Double_t> ch2_t_fe = {fReader, "ch2_t_fe"};
   TTreeReaderValue<Bool_t> ch3_re = {fReader, "ch3_re"};
   TTreeReaderValue<Bool_t> ch3_fe = {fReader, "ch3_fe"};
   TTreeReaderValue<Double_t> ch3_t_re = {fReader, "ch3_t_re"};
   TTreeReaderValue<Double_t> ch3_t_fe = {fReader, "ch3_t_fe"};
   TTreeReaderValue<Bool_t> status = {fReader, "status"};


   timedependent(TTree * /*tree*/ =0) { }
   virtual ~timedependent() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(timedependent,0);

};

#endif

#ifdef timedependent_cxx
void timedependent::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t timedependent::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef timedependent_cxx
