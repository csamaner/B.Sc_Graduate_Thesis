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
#include <TString.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>


#include <algorithm>

#include "TLatex.h"
#include "TLegend.h"

#include "TVectorD.h"
#include "ExRootAnalysis/ExRootTreeReader.h"
#include "DelphesClasses.h"
#include "Math/GenVector/VectorUtil.h"

#include <TProfile.h>



using namespace std;

const double JETPTCUT = 50.00 ;

const double JETETACUT = 2.5 ;


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

int main(int argc, char*argv[])
{

 string inputFile=argv[1];

 string outputFile=argv[2];


 TFile *outf = new TFile(outputFile.c_str(),"RECREATE");



 /////////////////////// Book histograms ///////////////////////////////

    //    TDirectory *dene= outf->mkdir("deneme");
    //    dene->cd();

     // Pt distribution ---------------------------------------------------------------------------------------

     TH1 *histcalojetPT           = new TH1F("calojetpt", "pT of calojets", 500, 0.0, 6000.0);
     TH1 *histgenjetPT            = new TH1F("genjetpt", "pT of genjets", 500, 0.0, 6000.0);

     // Rapi resolution ---------------------------------------------------------------------------------------

     TH2F *hist_Rapi_Reso1        = new TH2F("rapiReso60-100", "Ygen-Ycalo Vs Ygen 60-100 Gev", 100, -5, 5 , 100, -0.4, 0.4);
     TH2F *hist_Rapi_Reso2        = new TH2F("rapiReso100-150", "Ygen-Ycalo Vs Ygen 100-150 Gev", 100, -5, 5 , 100, -0.4, 0.4);
     TH2F *hist_Rapi_Reso3        = new TH2F("rapiReso150-200", "Ygen-Ycalo Vs Ygen 150-200 Gev", 100, -5, 5 , 100, -0.4, 0.4);

     // HT and PT distributions---------------------------------------------------------------------------

     TH1 *histhtcalojet           = new TH1F("calojetHT", "Ht dist for calojets", 500, 0, 10000.0);
     TH1 *histhtgenjet            = new TH1F("genjetHT", "Ht dist for genjets", 500, 0, 10000.0);
     TH1 *histcaloLeadingJetPT    = new TH1F("leadingCalojetpt", "pT of Leading calojets", 500, 0.0, 6000.0);
     TH1 *histgenLeadingJetPT     = new TH1F("leadingGenjetpt", "pT of Leading genjets", 500, 0.0, 6000.0);

     // PT RESO ---------------------------------------------------------------------------------------
     TH2F *hist_Pt_Reso[3];

     hist_Pt_Reso[0]              = new TH2F("LeadingJetPtReso", "pT Resolution for the leadingJet", 500, 0.0, 1000.0 , 100, 0.0, 0.5);
     hist_Pt_Reso[1]              = new TH2F("SecondJetPtReso", "pT Resolution for the secondJet", 500, 0.0, 1000.0 , 100, 0.0, 0.5);
     hist_Pt_Reso[2]              = new TH2F("ThirdJetPtReso", "pT Resolution for the thirdJet", 500, 0.0, 400.0 , 100, 0.0, 0.5);

     TProfile *Ptprof[3];

     Ptprof[0]                    = new TProfile("PtprofLeadingJet","Profile of LeadingJet" ,100 ,0.0 ,1000.0 , 0 , 10);
     Ptprof[1]                    = new TProfile("PtprofSecJet","Profile of SecJet" , 100, 0.0, 1000.0 , 0, 10);
     Ptprof[2]                    = new TProfile("PtprofThirdJet","Profile of ThirdJet" , 100 ,0.0 ,400.0 , 0 , 10);

     TH1 *hist_Pt_Reso_only       = new TH1F("Pt_Reso_only","asd",100,0.0,2.0);

     // Invariant Mass ---------------------------------------------------------------------------------------

     TH1 *histJetMass             = new TH1F("JetInvMass", "Jet Invariant Mass" , 500, 0.0, 12000.0);
     TH1 *hist_alpha_t	          = new TH1F("hist_alpha_t", "Apha_T PT_2/M12", 100, 0, 3.0);
     TH1 *hist_hoca_invM          = new TH1F("hoca_InvMass","Hoca inv mass",500,0.0,12000.0);

     // SCALAR HT ---------------------------------------------------------------------------------------
     //    TDirectory *scaHT= outf->mkdir("ScalarHT");
     //    scaHT->cd();

     TH1 *hist_SHT                = new TH1F("hist_SHT", "Scalar ht cekerek aldık" , 500, 0.0, 10000.0);
     TH1 *hist_jets_no_2_HT       = new TH1F("hist_jets_no_2_HT", " HT dist for jet no > 2 " , 500, 0.0, 10000.0);
     TH1 *hist_jets_no_3_HT       = new TH1F("hist_jets_no_3_HT", " HT dist for jet no > 3 " , 500, 0.0, 10000.0);

     // Delta R ---------------------------------------------------------------------------------------

     TH1 *hist_delta_phi          = new TH1F("delta phi" , "Delta phi" , 100, 0, 5.0);
     TH1 *hist_delta_eta          = new TH1F("delta eta" , "Delta eta" , 100, -5.0, 5.0);
     TH1 *hist_deltaR             = new TH1F("Delta R" , "Delta R " , 100 , 0 , 7.0 );



      gSystem->Load("libDelphes");
	  gSystem->Load("libExRootAnalysis");

 // Create chain of root trees
 TChain chain("Delphes");
 chain.Add(inputFile.c_str());

 // Create object of class ExRootTreeReader
 ExRootTreeReader *treeReader   = new ExRootTreeReader(&chain);
 Long64_t numberOfEntries       = treeReader->GetEntries();

 // Get pointers to branches used in this analysis
 TClonesArray *branchJet    = treeReader->UseBranch("Jet");
 TClonesArray *branchGenJet = treeReader->UseBranch("GenJet");
 TClonesArray *branchSHT 	= treeReader->UseBranch("ScalarHT");


// some definitions

 vector<Jet *> jetta;
 vector<Jet *> genjetta;

 TLorentzVector p4[2];
 double Jmass;

 ScalarHT* sht = 0;

 Jet *jet;
 Jet *genjet;

 int decade = 0;

 // counters for checks

 int counter_PtReso_eta_cut = 0 ;
 int counter_PtReso_entries = 0 ;
 int counter_PtReso_deltaR_cut = 0 ;
 int counter_no_jet_events = 0 ;
 int counter_no_genjet_events = 0 ;



 // Loop over all events

	for(int entry = 0; entry < numberOfEntries; ++entry)
 	{
//   		if(entry%1000 == 0) cout << "event number: " << entry << endl;


        double progress = 10.0*entry/(1.0*numberOfEntries);
        int k = TMath::FloorNint(progress);
        if (k > decade) {   cout << 10*k << "%\t"; gSystem->Exec("date '+%H:%M:%S'"); cout << endl;	}
        decade = k;

   		// Load selected branches with data from specified event
   		treeReader->ReadEntry(entry);



///////////////////////////////CALO JET/////////////////////////////////



		jetta.clear();


   		for(int i = 0; i < branchJet->GetEntriesFast(); ++i)
        {

			jet = (Jet*) branchJet->At(i);


			jetta.push_back(jet);

		 }

		if (jetta.size() == 0)
		{
			counter_no_jet_events++ ;
		}

		// Ht and PT distribution of CaloJets

		if(jetta.size() > 0)
		{
			histcaloLeadingJetPT->Fill(jetta[0]->PT);

			double htcalojet = 0;


			for(unsigned i = 0 ; i < jetta.size() ; ++i)
			{

				histcalojetPT->Fill(jetta[i]->PT);

				htcalojet = htcalojet + jetta[i]->PT ;


			}

			histhtcalojet->Fill(htcalojet);
		}





///////////////////////////////GEN JET/////////////////////////////////

		genjetta.clear();

   		for(int i = 0; i < branchGenJet->GetEntriesFast(); ++i)
   		{

			genjet = (Jet*) branchGenJet->At(i);


			genjetta.push_back(genjet);

 		 }

		// HT and PT dist of GenJets

		if (genjetta.size() < 1)
		{
			counter_no_genjet_events++ ;
		}

		else
		{

			histgenLeadingJetPT->Fill(genjetta[0]->PT);

			double htgenjet = 0;

			for(unsigned i = 0 ; i < genjetta.size() ; ++i)
			{

				histgenjetPT->Fill(genjetta[i]->PT);


				htgenjet = htgenjet + genjetta[i]->PT ;


			}

			histhtgenjet->Fill(htgenjet);

		}

		// PT resolution

        char PtReso[100] ;

        if( genjetta.size() == jetta.size() )
        {
            if ( jetta.size() > 2 && genjetta.size() > 2 )
            {
                for ( int i = 0 ; i < 3 ; i++ )
                {
                    counter_PtReso_entries++;

                    if(abs(genjetta[i]->Eta) <= 2.5 && abs(jetta[i]->Eta) <= 2.5)
                    {
                        double delta_phi_for_Reso = abs(jetta[0]->Phi - genjetta[0]->Phi) ;
                        double delta_eta_for_Reso = abs(jetta[0]->Eta - genjetta[0]->Eta) ;
                        double delta_r_for_Reso = sqrt( pow( delta_phi_for_Reso ,2 ) + pow( delta_eta_for_Reso ,2 ) );

                        counter_PtReso_eta_cut++;

                        if ( delta_r_for_Reso < 0.25 )
                        {
                            counter_PtReso_deltaR_cut++;

                            sprintf(PtReso,"PtResolution%i",i);

                            double PtReso =  abs( ( (genjetta[i]->PT) - (jetta[i]->PT) ) ) / (genjetta[i]->PT)   ;


                            hist_Pt_Reso_only->Fill(PtReso);
                            hist_Pt_Reso[i]->Fill(genjetta[i]->PT,PtReso);
                            Ptprof[i]->Fill(genjetta[i]->PT,PtReso);
                        }
                    }
                }

            }
        }


        // rapıdite resolutıon
		if( genjetta.size() == jetta.size() )
		{
			for(unsigned i = 0 ; i < genjetta.size() ; ++i )
			{

                double genjet_pt = genjetta[i]->PT ;
//                double genjet_eta = genjetta[i]->Eta ;
//                double jet_eta = jetta[i]->Eta ;

            	if( ( 150 < genjet_pt ) && ( genjet_pt < 200 ))
                {

                    hist_Rapi_Reso3->Fill(genjetta[i]->Eta, genjetta[i]->Eta - jetta[i]->Eta)	;
                }

            	if( ( 100.00 < genjet_pt ) && ( genjet_pt < 150.00 ))
                {

                    hist_Rapi_Reso2->Fill(genjetta[i]->Eta, genjetta[i]->Eta - jetta[i]->Eta)	;
                }

    			if( ( 60.00 < genjet_pt ) && ( genjet_pt < 100.00 ))
    			{

    				hist_Rapi_Reso1->Fill(genjetta[i]->Eta, genjetta[i]->Eta - jetta[i]->Eta)	;
    			}

			}
		}


   		// select events with at least 1 jets

        if(jetta.size() > 0)
        {

            int counter_njets = 0;


            if(branchSHT->GetEntries() > 0)
            {
      			sht = (ScalarHT *) branchSHT->At(0);

      		    hist_SHT->Fill(sht->HT);


                for(unsigned i = 0; i < jetta.size(); ++i)
      			{

                    if ( ( jetta[i]->PT > JETPTCUT ) && ( abs(jetta[i]->Eta) <= JETETACUT ) )
                    {

                        counter_njets++ ;

                    }

      			}

            }

            if(counter_njets >= 2)
            {
                hist_jets_no_2_HT->Fill(sht->HT);
            }

            if(counter_njets >= 3)
            {
                hist_jets_no_3_HT->Fill(sht->HT);
            }
        }

   		// select events with at least 2 jets

        double  alpha_t=0;

        if(branchJet->GetEntries() > 1)
        {
            // Invariant Mass calculation with TLorentzVector

            p4[0].SetPtEtaPhiM(jetta[0]->PT, jetta[0]->Eta, jetta[0]->Phi, jetta[0]->Mass);

            p4[1].SetPtEtaPhiM(jetta[1]->PT, jetta[1]->Eta, jetta[1]->Phi, jetta[1]->Mass);

            Jmass = ((p4[0]) + (p4[1])).M();

            histJetMass->Fill(Jmass);

            // Invariant Mass calculation

            double jet_inv_mass12=sqrt(2*jetta[0]->PT*jetta[1]->PT*(cosh(jetta[0]->Eta-jetta[1]->Eta)-cos(jetta[0]->Phi-jetta[1]->Phi)));
            alpha_t=(double)(jetta[1]->PT)/jet_inv_mass12;
            hist_alpha_t->Fill(alpha_t);
            hist_hoca_invM->Fill(jet_inv_mass12);

            // Delta R calculation

            double delta_phi = abs( (jetta[0]->Phi) - (jetta[1]->Phi) ) ;
            double delta_eta = jetta[0]->Eta - jetta[1]->Eta ;
            double delta_r = sqrt( pow( delta_phi ,2 ) + pow( delta_eta ,2 ) );


            hist_delta_phi->Fill(delta_phi);
            hist_delta_eta->Fill(delta_eta);
            hist_deltaR->Fill(delta_r);



        }

	 }

    cout << "csamaner! For inputfile " << inputFile << "..." << endl;
	cout << "csamaner! number of events with no calojet : " << counter_no_jet_events << endl;
	cout << "csamaner! number of events with no genjet : " << counter_no_genjet_events << endl;
	cout << "csamaner! number of total entries : "<< numberOfEntries << endl;
    cout << "csamaner! number of Pt Resolution entries : " << counter_PtReso_entries << endl;
    cout << "csamaner! number of entries after Pt y < 2.5 cut : " << counter_PtReso_eta_cut << endl;
    cout << "csamaner! number of entries after Pt y < 2.5 and deltaR < 0.25 cut : " << counter_PtReso_deltaR_cut << endl;
    cout << "csamaner! ----------------------------------------------------------------------\n" ;

    outf->Write();
    outf->Close();


}
