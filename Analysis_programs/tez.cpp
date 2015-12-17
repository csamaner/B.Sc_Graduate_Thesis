#include <TSystem.h>
#include <TChain.h>
#include <TROOT.h>
#include <TRint.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TEventList.h>
#include "TClonesArray.h"
#include <TH1D.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TF1.h>
#include "TLorentzVector.h"
#include "TCanvas.h"
#include <TMath.h>
#include <TProfile.h>
#include "TStyle.h"
#include <time.h>
#include <TString.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

#include <algorithm> // std sort icin

#include "TLatex.h"
#include "TLegend.h"

#include "TVectorD.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include "DelphesClasses.h"


using namespace std;


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

int main(int argc, char*argv[])
{
 gSystem->Load("libDelphes");


string inputFile=argv[1];

string outputFile=argv[2];



 // Create chain of root trees
 TChain chain("Delphes");
 chain.Add(inputFile.c_str());

 // Create object of class ExRootTreeReader
 ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
 Long64_t numberOfEntries = treeReader->GetEntries();

 // Get pointers to branches used in this analysis
 TClonesArray *branchJet  = treeReader->UseBranch("Jet");
 TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");

 // Book histograms
 
 TH1 *histhtjetn2 = new TH1F("2jetHT", "Ht for jet no >=2 ", 500, 0, 10000.0);

 TH1 *histhtjetn3 = new TH1F("3jetHT", "Ht for jet no >=3 ", 500, 0, 10000.0);

 TH1 *histcalojetPT = new TH1F("calojetpt", "pT of calojets", 500, 0.0, 6000.0);

 TH1 *histgenjetPT = new TH1F("genjetpt", "pT of genjets", 500, 0.0, 6000.0);

 TH2F *hist_Rapi_Reso = new TH2F("rapiReso", "Ygen-Ycalo Vs Ygen", 50, -5, 5 , 100, -0.4, 0.4);

 TH1 *histhtcalojet = new TH1F("calojetHT", "Ht dist for calojets", 500, 0, 10000.0);
 
 TH1 *histhtgenjet = new TH1F("genjetHT", "Ht dist for genjets", 500, 0, 10000.0);

 TH1 *histcaloLeadingJetPT = new TH1F("leadingCalojetpt", "pT of Leading calojets", 500, 0.0, 6000.0);

 TH1 *histgenLeadingJetPT = new TH1F("leadingGenjetpt", "pT of Leading genjets", 500, 0.0, 6000.0);

 TH2F *histPtReso = new TH2F("PtReso", "PtReso over LeadingGenjetPT", 500, 0.0, 1000.0 , 100, 0.0, 0.5);

 TH1 *histJetMass = new TH1F("JetInvMass", "Jet Invariant Mass" , 500, 0.0, 15000.0);



 
// some definitions

 vector<Jet *> jetta;

 vector<Jet *> genjetta;

 vector<double> tempVector2;

 vector<double> tempVector3;

 vector< vector<double> > Jtwo;

 vector< vector<double> > Jthree;

 double noJetEvents = 0 ;

 double nogenJetEvents = 0 ;

 TLorentzVector p4[2];

 double Jmass;



 Jet *jet;

 Jet *genjet;

 Int_t entry, i;

 // Loop over all events


 	for(entry = 0; entry < numberOfEntries; ++entry)
 	{
   		if(entry%1000 == 0) cout << "event number: " << entry << endl;

   		// Load selected branches with data from specified event
   		treeReader->ReadEntry(entry);


		double PtResolution = 0;

///////////////////////////////CALO JET/////////////////////////////////


                   	
		jetta.clear();


   		for(i = 0; i < branchJet->GetEntriesFast(); ++i)
   		{
			
			jet = (Jet*) branchJet->At(i);

			
			jetta.push_back(jet);
			
		 }

		if (jetta.size() == 0)
		{
			noJetEvents++ ;	
		}

		// Ht and PT distribution of CaloJets

		if(jetta.size() > 0)
		{
			histcaloLeadingJetPT->Fill(jetta[0]->PT);
		
			double htcalojet = 0;


			for ( i = 0 ; i < jetta.size() ; ++i)
			{

				histcalojetPT->Fill(jetta[i]->PT);
			
				htcalojet = htcalojet + jetta[i]->PT ;		


			}

			histhtcalojet->Fill(htcalojet);

		}
		

		


///////////////////////////////GEN JET/////////////////////////////////

		genjetta.clear();		

   		for(i = 0; i < branchGenJet->GetEntriesFast(); ++i)
   		{
			
			genjet = (Jet*) branchGenJet->At(i);

			
			genjetta.push_back(genjet);	
			
 		 }

		// HT and PT dist of GenJets

		if (genjetta.size() == 0)
		{
			nogenJetEvents++ ;	
		}

		if (genjetta.size() > 0)
		{

			histgenLeadingJetPT->Fill(genjetta[0]->PT);		

			double htgenjet = 0;

			for ( i = 0 ; i < genjetta.size() ; ++i)
			{

				histgenjetPT->Fill(genjetta[i]->PT);
		

				htgenjet = htgenjet + genjetta[i]->PT ;


			}

			histhtgenjet->Fill(htgenjet);

		}





		// PT resolution over GenJetPt


		PtResolution = abs( ( (genjetta[0]->PT) - (jetta[0]->PT) ) / (genjetta[0]->PT) ) ;


		histPtReso->Fill(genjetta[0]->PT,PtResolution);

	
		
		
		// rapıdite resolutıon
		if( genjetta.size() == jetta.size() )
		{
			for ( i = 0 ; i < genjetta.size() ; ++i )
			{
				if( 60.00 <= (genjetta[i]->PT) <= 100.00 && 60.00 <= (jetta[i]->PT) <= 100.00 )								
				{
			
					hist_Rapi_Reso->Fill(genjetta[i]->Eta,genjetta[i]->Eta - jetta[i]->Eta)	;
				}


			}
		}


   		// select events with at least 2 jets
   		
		if(jetta.size() > 1)
		{

			double HTjetta2 = 0 ;

			tempVector2.clear();	

				
			for(i = 0; i < jetta.size(); ++i)
			{
			
					

				HTjetta2 = HTjetta2 + jetta[i]->PT ;

				
				
			}

			p4[0].SetPtEtaPhiM(jetta[0]->PT, jetta[0]->Eta, jetta[0]->Phi, jetta[0]->Mass);
	   
			p4[1].SetPtEtaPhiM(jetta[1]->PT, jetta[1]->Eta, jetta[1]->Phi, jetta[1]->Mass);

			Jmass = ((p4[0]) + (p4[1])).M();

			histJetMass->Fill(Jmass);

			tempVector2.push_back(HTjetta2);

			tempVector2.push_back(jetta.size());

			Jtwo.push_back(tempVector2);
			
			histhtjetn2->Fill(HTjetta2);
		}

		

		// select events with at least 3 jets
   		if(jetta.size() > 2)
		{

			double HTjetta3 = 0 ;

			tempVector3.clear();	


					
			for(i = 0; i < jetta.size(); ++i)
			{
			
					

				HTjetta3 = HTjetta3 + jetta[i]->PT ;

			
			
			}

			tempVector3.push_back(HTjetta3);

			tempVector3.push_back(jetta.size());

			Jthree.push_back(tempVector3);

			histhtjetn3->Fill(HTjetta3);		

			
		}
		
		// SORT ALGO Jtwo ve Jthree
		
		
 		  
	 }


	cout << "csamaner! jet cıkmayan olay sayısı  " << noJetEvents << endl;

	cout << "csamaner! genjet cıkmayan olay sayısı  " << nogenJetEvents << endl;

	
		





 TFile *fout = TFile::Open(outputFile.c_str(),"RECREATE");
 fout->cd();

histhtjetn2->Write();

histhtjetn3->Write();
 
histgenjetPT->Write();

histcalojetPT->Write();

hist_Rapi_Reso->Write();

histhtcalojet->Write();

histhtgenjet->Write();

histcaloLeadingJetPT->Write();

histgenLeadingJetPT->Write();

histPtReso->Write();

histJetMass->Write();







 
}
