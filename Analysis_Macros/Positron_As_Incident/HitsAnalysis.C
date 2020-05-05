#define HitsAnalysis_cxx
#include "HitsAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void HitsAnalysis::Loop()
	{
		//	In a ROOT session, you can do:
		//  root> .L HitsAnalysis.C
		// 	root> HitsAnalysis t
		//  root> t.GetEntry(12); 														// Fill t data members with entry number 12
		//  root> t.Show();       														// Show values of entry 12
		//  root> t.Show(16);     														// Read and show values of entry 16
		//  root> t.Loop();       														// Loop on all entries

		//  This is the loop skeleton where:
		//  jentry is the global entry number in the chain
		//  ientry is the entry number in the current Tree
		// 	Note that the argument to GetEntry must be:
		//  jentry for TChain::GetEntry
		//  ientry for TTree::GetEntry and TBranch::GetEntry
		//
		//  To read only selected branches, Insert statements like:
		// 		METHOD1:
		//    	fChain->SetBranchStatus("*",0);  							// disable all branches
		//    	fChain->SetBranchStatus("branchname",1);  		// activate branchname
		// 		METHOD2: replace line
		//    	fChain->GetEntry(jentry);       							//read all branches by  
		//			b_branchname->GetEntry(ientry); 							//read only this branch
   
   	if (fChain == 0) return;

   	Long64_t nentries = fChain->GetEntriesFast();
   	Long64_t nbytes = 0, nb = 0;
   
   	f = new TFile("HitsAnalysis.root", "RECREATE");
   	
   	double binEdge[151] = {10.0e-13,
   												 1.2589254e-12, 1.5848932e-12, 1.9952623e-12, 2.5118864e-12, 3.1622777e-12, 3.981072e-12, 5.011872e-12, 6.309573e-12, 7.943282e-12, 10.0e-12,
   												 1.2589254e-11, 1.5848932e-11, 1.9952623e-11, 2.5118864e-11, 3.1622777e-11, 3.981072e-11, 5.011872e-11, 6.309573e-11, 7.943282e-11, 10.0e-11,
   												 1.2589254e-10, 1.5848932e-10, 1.9952623e-10, 2.5118864e-10, 3.1622777e-10, 3.981072e-10, 5.011872e-10, 6.309573e-10, 7.943282e-10, 10.0e-10,
   												 1.2589254e-9, 1.5848932e-9, 1.9952623e-9, 2.5118864e-9, 3.1622777e-9, 3.981072e-9, 5.011872e-9, 6.309573e-9, 7.943282e-9, 10.0e-9,
   												 1.2589254e-8, 1.5848932e-8, 1.9952623e-8, 2.5118864e-8, 3.1622777e-8, 3.981072e-8, 5.011872e-8, 6.309573e-8, 7.943282e-8, 10.0e-8,
   												 1.2589254e-7, 1.5848932e-7, 1.9952623e-7, 2.5118864e-7, 3.1622777e-7, 3.981072e-7, 5.011872e-7, 6.309573e-7, 7.943282e-7, 10.0e-7,
   												 1.2589254e-6, 1.5848932e-6, 1.9952623e-6, 2.5118864e-6, 3.1622777e-6, 3.981072e-6, 5.011872e-6, 6.309573e-6, 7.943282e-6, 10.0e-6,
   												 1.2589254e-5, 1.5848932e-5, 1.9952623e-5, 2.5118864e-5, 3.1622777e-5, 3.981072e-5, 5.011872e-5, 6.309573e-5, 7.943282e-5, 10.0e-5,
   												 1.2589254e-4, 1.5848932e-4, 1.9952623e-4, 2.5118864e-4, 3.1622777e-4, 3.981072e-4, 5.011872e-4, 6.309573e-4, 7.943282e-4, 10.0e-4,
   												 1.2589254e-3, 1.5848932e-3, 1.9952623e-3, 2.5118864e-3, 3.1622777e-3, 3.981072e-3, 5.011872e-3, 6.309573e-3, 7.943282e-3, 10.0e-3,
   												 1.2589254e-2, 1.5848932e-2, 1.9952623e-2, 2.5118864e-2, 3.1622777e-2, 3.981072e-2, 5.011872e-2, 6.309573e-2, 7.943282e-2, 10.0e-2,
   												 1.2589254e-1, 1.5848932e-1, 1.9952623e-1, 2.5118864e-1, 3.1622777e-1, 3.981072e-1, 5.011872e-1, 6.309573e-1, 7.943282e-1, 10.0e-1,
   												 1.2589254, 1.5848932, 1.9952623, 2.5118864, 3.1622777, 3.981072, 5.011872, 6.309573, 7.943282, 10.00000,
   												 12.589254, 15.848932, 19.952623, 25.118864, 31.622777, 39.81072, 50.11872, 63.09573, 79.43282, 100.0000,
   												 125.89254, 158.48932, 199.52623, 251.18864, 316.22777, 398.1072, 501.1872, 630.9573, 794.3282, 1000.000
   											};
   	
   	TH1D* h_PrimaryEnergy = new TH1D("h_PrimaryEnergy"," Primary Energy of Positrons ", 150, binEdge);
    h_PrimaryEnergy->GetXaxis()->SetTitle("Energy (MeV)");
    h_PrimaryEnergy->GetYaxis()->SetTitle("Number of Events"); 
   	
  	TH1D* h_PositronSensitivity = new TH1D("h_PositronSensitivity"," Positron Sensitivity vs Kinetic Energy", 150, binEdge);
   	h_PositronSensitivity->GetXaxis()->SetTitle("Energy (MeV)");
   	h_PositronSensitivity->GetYaxis()->SetTitle("Positron Sensitivity");	
   	
   	TH1I* h_NumberInteraction = new TH1I("h_NumberInteraction"," Number of Interactions of Primary Positron ", 40, 0, 40);
    h_NumberInteraction->GetXaxis()->SetTitle("Number of Interaction");
    h_NumberInteraction->GetYaxis()->SetTitle("Number of Events");
    	
   	TH1D* h_InteractionLength = new TH1D("h_InteractionLength"," Length Traversed within the Detector by Primary Positron ", 1000, 0, 500);
    h_InteractionLength->GetXaxis()->SetTitle("Traversed Length (mm)");
    h_InteractionLength->GetYaxis()->SetTitle("Number of Events");
    
    TH2D* h_EnergyInterNumber = new TH2D("h_EnergyInterNumber"," Primary Energy vs Number of Interactions ", 150, binEdge, 40, 0, 40);
   	h_EnergyInterNumber->GetXaxis()->SetTitle("Energy (MeV)");
   	h_EnergyInterNumber->GetYaxis()->SetTitle("Number of Interactions");	
    
    TH2D* h_LengthInterNumber = new TH2D("h_LengthInterNumber"," Number of Interaction vs Length Traversed by Primary Positron ", 40, 0, 40, 1000, 0, 200);
   	h_LengthInterNumber->GetXaxis()->SetTitle("Number of Interactions");
   	h_LengthInterNumber->GetYaxis()->SetTitle("Traversed Length (mm)");	
    
    TH1I* h_NumberPositron = new TH1I("h_NumberPositron"," Number of Secondary Positrons Produced per Event ", 20, 0, 20);
    h_NumberPositron->GetXaxis()->SetTitle("Number of Positron ");
    h_NumberPositron->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberNeutron = new TH1I("h_NumberNeutron"," Number of Neutrons Produced per Event ", 20, 0, 20);
    h_NumberNeutron->GetXaxis()->SetTitle("Number of Neutron ");
    h_NumberNeutron->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberProton = new TH1I("h_NumberProton"," Number of Protons Produced per Event ", 20, 0, 20);
    h_NumberProton->GetXaxis()->SetTitle("Number of Proton");
    h_NumberProton->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberElectron = new TH1I("h_NumberElectron"," Number of Electrons Produced per Event ", 40, 0, 40);
    h_NumberElectron->GetXaxis()->SetTitle("Number of Electron");
    h_NumberElectron->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberElectronGap1 = new TH1I("h_NumberElectronGap1"," Number of Electrons Produced (in Gap1) per Event ", 40, 0, 40);
    h_NumberElectronGap1->GetXaxis()->SetTitle("Number of Electron");
    h_NumberElectronGap1->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberElectronGap2 = new TH1I("h_NumberElectronGap2"," Number of Electrons Produced (in Gap2) per Event ", 40, 0, 40);
    h_NumberElectronGap2->GetXaxis()->SetTitle("Number of Electron");
    h_NumberElectronGap2->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberElectronGap3 = new TH1I("h_NumberElectronGap3"," Number of Electrons Produced (in Gap3) per Event ", 40, 0, 40);
    h_NumberElectronGap3->GetXaxis()->SetTitle("Number of Electron");
    h_NumberElectronGap3->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberElectronGap4 = new TH1I("h_NumberElectronGap4"," Number of Electrons Produced (in Gap4) per Event ", 40, 0, 40);
    h_NumberElectronGap4->GetXaxis()->SetTitle("Number of Electron");
    h_NumberElectronGap4->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberGamma = new TH1I("h_NumberGamma"," Number of Gammas Produced per Event ", 20, 0, 20);
    h_NumberGamma->GetXaxis()->SetTitle("Number of Gamma");
    h_NumberGamma->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberPosPi = new TH1I("h_NumberPosPi"," Number of Pi+ Produced per Event ", 20, 0, 20);
    h_NumberPosPi->GetXaxis()->SetTitle("Number of Pi+");
    h_NumberPosPi->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberNegPi = new TH1I("h_NumberNegPi"," Number of Pi- Produced per Event ", 20, 0, 20);
    h_NumberNegPi->GetXaxis()->SetTitle("Number of Pi-");
    h_NumberNegPi->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberDeuteron = new TH1I("h_NumberDeuteron"," Number of Deuterons Produced per Event ", 20, 0, 20);
    h_NumberDeuteron->GetXaxis()->SetTitle("Number of Deuteron");
    h_NumberDeuteron->GetYaxis()->SetTitle("Number of Events");
    
    TH1I* h_NumberO16 = new TH1I("h_NumberO16"," Number of O-16 ions Produced per Event ", 40, 0, 40);
    h_NumberO16->GetXaxis()->SetTitle("Number of O16");
    h_NumberO16->GetYaxis()->SetTitle("Number of Events");
  
   	int totNum = 0 ;
   	int event = 0 ;
   	int nPositron = 0 ; 	int nElectron = 0 ; 	int nNeutron = 0 ;		int nProton = 0 ;		int nPosPions = 0;		int nNegPions = 0;
   	int nElectronGap1Gas = 0 ;		int nElectronGap2Gas = 0 ;		int nElectronGap3Gas = 0 ;		int nElectronGap4Gas = 0 ;
   	
   	int nDeuteron = 0 ;		int nO16 = 0 ;		int nGamma = 0 ;
   	bool positronSensitive = false ;
   	int previousTrack = 0;		int track = 0 ;		int nextTrack = 0 ;
   	double primEnergy = 0.0 ;
   	double interLength = 0.0 ;
   	double sensNeut = 0.0 ;
   	double energyNeut = 0.0 ;
   	double sensitivity = 0.0 ;
   	int totalInter = 0.0;
   	double totalLength = 0.0 ;
   	
   	for (Long64_t jentry=0; jentry<nentries;jentry++) 
   		{ 
      	Long64_t ientry = LoadTree(jentry);
      	if (ientry < 0) break;
      	nb = fChain->GetEntry(jentry);   nbytes += nb;
      	// if (Cut(ientry) < 0) continue;
      	//	if(*ParticleName != "neutron" && *ParticleName != "gamma" && *ParticleName != "e-" && *ParticleName != "e+" && *ParticleName != "proton")
      	//{//cout<<EventID<<"...particle..= "<<*ParticleName<<"..charge..= "<<Charge<<"...pdg..= "<<PDG<<endl;}
      	
      	int event_id = EventID ;
      	if (event != event_id)  
      		{      			
      			totalInter += totNum ;
      			totalLength += interLength ;
      			nElectron = (nElectronGap1Gas + nElectronGap2Gas + nElectronGap3Gas + nElectronGap4Gas) ;
      			//cout<<"..nElectron..= "<<nElectron<<"..GasGap1..= "<<nElectronGap1Gas<<"..GasGap2..= "<<nElectronGap2Gas<<"..GasGap3..= "<<nElectronGap3Gas<<"..GasGap4..= "<<nElectronGap4Gas<<endl;
      			cout<<event<<"...total gamma ... = "<<nGamma<<"..total electron.= "<<nElectron<<"..protons.. = "<<nProton<<endl;
      			if (positronSensitive == true)
      				{
      					h_PositronSensitivity->Fill(primEnergy);
      				}
      			h_EnergyInterNumber->Fill(primEnergy,totNum);
      			h_LengthInterNumber->Fill(totNum,interLength );
      			h_PrimaryEnergy->Fill(primEnergy);
      			h_NumberInteraction->Fill(totNum);
      			h_NumberGamma->Fill(nGamma);
      			h_NumberNeutron->Fill(nNeutron);
      			h_NumberProton->Fill(nProton);
      			h_NumberElectron->Fill(nElectron);
      			h_NumberElectronGap1->Fill(nElectronGap1Gas);
      			h_NumberElectronGap2->Fill(nElectronGap2Gas);
      			h_NumberElectronGap3->Fill(nElectronGap3Gas);
      			h_NumberElectronGap4->Fill(nElectronGap4Gas);
      			h_NumberPositron->Fill(nPositron);
      			h_NumberPosPi->Fill(nPosPions);
      			h_NumberNegPi->Fill(nNegPions);
      			h_NumberDeuteron->Fill(nDeuteron);
      			h_NumberO16->Fill(nO16);
      			h_InteractionLength->Fill(interLength);
      			
      			primEnergy = 0.0 ;
      			totNum = 0 ;
      			nGamma = 0 ;
      			nNeutron = 0 ;
      			nElectron = 0 ;
      			nElectronGap1Gas = 0 ;
      			nElectronGap2Gas = 0 ;
      			nElectronGap3Gas = 0 ;
      			nElectronGap4Gas = 0 ;
      			nPositron = 0 ;
      			nProton = 0 ;
      			nPosPions = 0 ;
      			nNegPions = 0 ;
      			nDeuteron = 0 ;
      			nO16 = 0 ;
      			previousTrack = 0 ;
      			interLength = 0.0 ;
      			positronSensitive = false ;
      			event++ ;
      		}
      	if (event == event_id)
      		{
      			int nextTrack = TrackID ;
      			primEnergy = PrimaryEnergy; 
      			if (Charge != 0 && TrackID != 1 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop")																		
      				{    				
      					positronSensitive = true ;     							
      				}      			
 						
 						if (ParentID == 0 && TrackID == 1)
 							{
 								interLength = InteractionLength - 3.0 ;
 							}
 						
 						// neutrons produced 	
 						if (Charge == 0 && *ParticleName == "neutron" && PDG == 2112 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop") 												
 							{ 
 								nNeutron++;
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    		{ nNeutron-- ; }
 								previousTrack = track ; 
 							}
 						
 						// positrons -- secondary produced	
 						if (Charge == +1 && *ParticleName == "e+" && PDG == -11 && TrackID != 1 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop")
 							{ 
 								nPositron++;
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    	{ nPositron--; }
 								previousTrack = track ; 
 							}
 							 				
 						// electron produced
 						if (Charge == -1 && *ParticleName == "e-" && PDG == 11 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop") 													
 							{ 
 								if (*VolumeName == "GasGap1") 			
 									{
 										nElectronGap1Gas++;
 										track = nextTrack ;
 										if (previousTrack == nextTrack)    	{nElectronGap1Gas--;}
 										previousTrack = track ; 
 									}
 								if (*VolumeName == "GasGap2") 													
 									{ 
 										nElectronGap2Gas++;
 										track = nextTrack ;
 										if (previousTrack == nextTrack)    {nElectronGap2Gas--;}
 										previousTrack = track ; 
 									}	
 								if (*VolumeName == "GasGap3") 													
 									{ 
 										nElectronGap3Gas++;
 										track = nextTrack ;
 										if (previousTrack == nextTrack)    {nElectronGap3Gas--;}
 										previousTrack = track ; 
 									}	
 								if (*VolumeName == "GasGap4") 													
 									{ 
 										nElectronGap4Gas++;
 										track = nextTrack ;
 										if (previousTrack == nextTrack)    {nElectronGap4Gas--;}
 										previousTrack = track ; 
 									}	
 							}
 						
 						// gammas produced
 						if (Charge == 0 && *ParticleName == "gamma" && PDG == 22 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop") 													
 							{ 
 								nGamma++; 
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    {nGamma--;}
 								previousTrack = track ; 
 							}
 						
 						// protons produced
 						if (Charge == +1 && *ParticleName == "proton" && PDG == 2212 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop") 										
 							{ 
 								nProton++; 
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    {nProton--;}
 								previousTrack = track ; 
 							}
 							
 						// pi+ produced
 						if (Charge == +1 && *ParticleName == "pi+" && PDG == 211 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop")													
 							{ 
 								nPosPions++; 
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    {nPosPions--;}
 								previousTrack = track ; 
 							}
 							
 						// pi- produced
 						if (Charge == -1 && *ParticleName == "pi-" && PDG == -211 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop")												
 							{ 
 								nNegPions++; 
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    {nNegPions--;}
 								previousTrack = track ; 
 							}
 							
 						// deuterons produced
 						if (Charge == +1 && *ParticleName == "deuteron" && PDG == 1000010020 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop")							
 							{ 
 								nDeuteron++; 
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    {nDeuteron--;}
 								previousTrack = track ;
 							}
 							
 						// O-16 ions prodeuced
 						if (Charge == +8 && *ParticleName == "O16" && PDG == 1000080160 && *VolumeName != "FakeBottom" && *VolumeName != "FakeTop")									
 							{ 
 								nO16++; 
 								track = nextTrack ;
 								if (previousTrack == nextTrack)    {nO16--;}
 								previousTrack = track ;
 							}
      			totNum += NumberInteraction ;
      		}
   		}
   	cout<<event<<"...total gamma ... = "<<nGamma<<"..total electron.= "<<nElectron<<"..protons.. = "<<nProton<<endl;
   	totalInter += totNum ;
    totalLength += interLength ;
   	cout<<"interaction number = "<<totalInter<<"..Length = "<<totalLength<<endl;
   	// Fill last entery
   	if (positronSensitive == true)
    	{
     		h_PositronSensitivity->Fill(primEnergy);
      }
     
    h_EnergyInterNumber->Fill(primEnergy,totNum);
    h_LengthInterNumber->Fill(totNum,interLength );
    h_PrimaryEnergy->Fill(primEnergy);
    h_NumberInteraction->Fill(totNum);
    h_NumberGamma->Fill(nGamma);
    h_NumberNeutron->Fill(nNeutron);
    h_NumberProton->Fill(nProton);
    h_NumberElectron->Fill(nElectron);
    h_NumberElectronGap1->Fill(nElectronGap1Gas);
    h_NumberElectronGap2->Fill(nElectronGap2Gas);
  	h_NumberElectronGap3->Fill(nElectronGap3Gas);
    h_NumberElectronGap4->Fill(nElectronGap4Gas);  
    h_NumberPositron->Fill(nPositron);
    h_NumberPosPi->Fill(nPosPions);
    h_NumberNegPi->Fill(nNegPions);
    h_NumberDeuteron->Fill(nDeuteron);
    h_NumberO16->Fill(nO16);
    h_InteractionLength->Fill(interLength);
   	h_PositronSensitivity->Divide(h_PrimaryEnergy);
   	
   	// Write Histo
   	h_PositronSensitivity->Write();
   	h_PrimaryEnergy->Write(); 		
   	h_EnergyInterNumber->Write();
   	h_LengthInterNumber->Write();
   	h_NumberInteraction->Write();
   	h_NumberGamma->Write();
   	h_NumberNeutron->Write();
    h_NumberProton->Write();
    h_NumberElectron->Write();
    h_NumberElectronGap1->Write();
    h_NumberElectronGap2->Write();
    h_NumberElectronGap3->Write();
    h_NumberElectronGap4->Write();
    h_NumberPositron->Write();
    h_NumberPosPi->Write();
    h_NumberNegPi->Write();
    h_NumberDeuteron->Write();
    h_NumberO16->Write();
    h_InteractionLength->Write();  
    
    
    cout<<"Inetraction per unit length (mm) is : "<<(totalInter/totalLength)<<endl;
    // Close File
   	f->Close();
	}
	
	
	
	
	
