//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 16 15:39:20 2020 by ROOT version 6.16/00
// from TTree HitsSteps/Tree keeps output from G4Step Geant4 Simulation
// found on file: test_g.root
//////////////////////////////////////////////////////////

#ifndef HitsAnalysis_h
#define HitsAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <THStack.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include "TH1.h"
#include "TH2.h"
#include <TMinuit.h>
#include <TRandom.h>
#include <TMath.h>
#include <stdio.h>
#include <TString.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH1I.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>
#include <TCanvas.h>
#include <Riostream.h> 
#include <TGraphAsymmErrors.h>
#include <map>
#include "TMath.h"
#include <vector>
#include <TList.h>
#include <set>
#include "TPaveStats.h"
#include "TColor.h"
#include "TFractionFitter.h"
#include "TPad.h"
#include "TLegend.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TStyle.h" 
#include "TKey.h"
#include "TLatex.h" 

#include <string>
#include <iostream>
#include <fstream>

// Header file for the classes stored in the TTree if any.
#include "string"
#include "vector"

using namespace std;
using namespace ROOT;

class HitsAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TFile 					*f ;
// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxeventID = 1;
   static constexpr Int_t kMaxparentID = 1;
   static constexpr Int_t kMaxtrackID = 1;
   static constexpr Int_t kMaxtotNumHits = 1;
   static constexpr Int_t kMaxstepNum = 1;
   static constexpr Int_t kMaxaNumInteraction = 1;

   // Declaration of leaf types
   Int_t           EventID;
   Int_t           ParentID;
   Int_t           TrackID;
   Double_t        Edep;
   Double_t        KineticEnergy;
   Int_t           TotalNumHits;
   Int_t           HitNumber;
   Int_t           PDG;
   Int_t           Charge;
   Double_t        PositionX;
   Double_t        PositionY;
   Double_t        PositionZ;
   Double_t        MomentumDirectionX;
   Double_t        MomentumDirectionY;
   Double_t        MomentumDirectionZ;
   Double_t        MomentumX;
   Double_t        MomentumY;
   Double_t        MomentumZ;
   Int_t           StepNumber;
   Double_t        InteractionLength;
   string          *VolumeName;
   string          *ProcessName;
   string          *ParticleName;
   Int_t           NumberInteraction;
   Double_t        PrimaryEnergy;
   Int_t           PrimaryParticlePDGCode;

   // List of branches
   TBranch        *b_eventID_;   //!
   TBranch        *b_parentID_;   //!
   TBranch        *b_trackID_;   //!
   TBranch        *b_Edep;   //!
   TBranch        *b_KineticEnergy;   //!
   TBranch        *b_totNumHits_;   //!
   TBranch        *b_HitNumber;   //!
   TBranch        *b_PDG;   //!
   TBranch        *b_Charge;   //!
   TBranch        *b_PositionX;   //!
   TBranch        *b_PositionY;   //!
   TBranch        *b_PositionZ;   //!
   TBranch        *b_MomentumDirectionX;   //!
   TBranch        *b_MomentumDirectionY;   //!
   TBranch        *b_MomentumDirectionZ;   //!
   TBranch        *b_MomentumX;   //!
   TBranch        *b_MomentumY;   //!
   TBranch        *b_MomentumZ;   //!
   TBranch        *b_stepNum_;   //!
   TBranch        *b_InteractionLength;   //!
   TBranch        *b_VolumeName;   //!
   TBranch        *b_ProcessName;   //!
   TBranch        *b_ParticleName;   //!
   TBranch        *b_aNumInteraction_;   //!
   TBranch        *b_PrimaryEnergy;   //!
   TBranch        *b_primParticlePDG;   //!

   HitsAnalysis(TTree *tree=0);
   virtual ~HitsAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HitsAnalysis_cxx
HitsAnalysis::HitsAnalysis(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("test_g.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("test_g.root");
      }
      f->GetObject("HitsSteps",tree);

   }
   Init(tree);
}

HitsAnalysis::~HitsAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HitsAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HitsAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HitsAnalysis::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   VolumeName = 0;
   ProcessName = 0;
   ParticleName = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventID", &EventID, &b_eventID_);
   fChain->SetBranchAddress("ParentID", &ParentID, &b_parentID_);
   fChain->SetBranchAddress("TrackID", &TrackID, &b_trackID_);
   fChain->SetBranchAddress("Edep", &Edep, &b_Edep);
   fChain->SetBranchAddress("KineticEnergy", &KineticEnergy, &b_KineticEnergy);
   fChain->SetBranchAddress("TotalNumHits", &TotalNumHits, &b_totNumHits_);
   fChain->SetBranchAddress("HitNumber", &HitNumber, &b_HitNumber);
   fChain->SetBranchAddress("PDG", &PDG, &b_PDG);
   fChain->SetBranchAddress("Charge", &Charge, &b_Charge);
   fChain->SetBranchAddress("PositionX", &PositionX, &b_PositionX);
   fChain->SetBranchAddress("PositionY", &PositionY, &b_PositionY);
   fChain->SetBranchAddress("PositionZ", &PositionZ, &b_PositionZ);
   fChain->SetBranchAddress("MomentumDirectionX", &MomentumDirectionX, &b_MomentumDirectionX);
   fChain->SetBranchAddress("MomentumDirectionY", &MomentumDirectionY, &b_MomentumDirectionY);
   fChain->SetBranchAddress("MomentumDirectionZ", &MomentumDirectionZ, &b_MomentumDirectionZ);
   fChain->SetBranchAddress("MomentumX", &MomentumX, &b_MomentumX);
   fChain->SetBranchAddress("MomentumY", &MomentumY, &b_MomentumY);
   fChain->SetBranchAddress("MomentumZ", &MomentumZ, &b_MomentumZ);
   fChain->SetBranchAddress("StepNumber", &StepNumber, &b_stepNum_);
   fChain->SetBranchAddress("InteractionLength", &InteractionLength, &b_InteractionLength);
   fChain->SetBranchAddress("VolumeName", &VolumeName, &b_VolumeName);
   fChain->SetBranchAddress("ProcessName", &ProcessName, &b_ProcessName);
   fChain->SetBranchAddress("ParticleName", &ParticleName, &b_ParticleName);
   fChain->SetBranchAddress("NumberInteraction", &NumberInteraction, &b_aNumInteraction_);
   fChain->SetBranchAddress("PrimaryEnergy", &PrimaryEnergy, &b_PrimaryEnergy);
   fChain->SetBranchAddress("PrimaryParticlePDGCode", &PrimaryParticlePDGCode, &b_primParticlePDG);
   Notify();
}

Bool_t HitsAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HitsAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HitsAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HitsAnalysis_cxx
