#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
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
// root> T->Process("MyAnalysis.C")
// root> T->Process("MyAnalysis.C","some options")
// root> T->Process("MyAnalysis.C+")
//


#include "MyAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>

void MyAnalysis::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void MyAnalysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   cout << "SlaveBegin" << endl;
   for(int ich=0; ich < 2; ich++){
     for(int i=0; i < 4; i++){
     
       h_NJet[ich][i] = new TH1D(Form("h_NJet_Ch%i_S%i_%s",ich,i,option.Data()), "Number of jets", 14, 0, 14);
       h_NJet[ich][i]->SetXTitle("Jet Multiplicity");
       h_NJet[ich][i]->Sumw2();
       fOutput->Add(h_NJet[ich][i]);
     
       h_NBJet_CSVv2M[ich][i] = new TH1D(Form("h_NBJet_CSVv2M_Ch%i_S%i_%s",ich,i,option.Data()), "Number of b tagged jets (medium)", 6, 0, 6);
       h_NBJet_CSVv2M[ich][i]->SetXTitle("b-tagged Jet Multiplicity (CSVv2M)");
       h_NBJet_CSVv2M[ich][i]->Sumw2();
       fOutput->Add(h_NBJet_CSVv2M[ich][i]);

       h_NBJet_CSVv2T[ich][i] = new TH1D(Form("h_NBJet_CSVv2T_Ch%i_S%i_%s",ich,i,option.Data()), "Number of b tagged jets (tight)", 6, 0, 6);
       h_NBJet_CSVv2T[ich][i]->SetXTitle("b-tagged Jet Multiplicity (CSVv2T)");
       h_NBJet_CSVv2T[ich][i]->Sumw2();
       fOutput->Add(h_NBJet_CSVv2T[ich][i]);

       h_NCJet_M[ich][i] = new TH1D(Form("h_NCJet_M_Ch%i_S%i_%s",ich,i,option.Data()), "Number of c tagged jets", 6, 0, 6);
       h_NCJet_M[ich][i]->SetXTitle("c-tagged Jet Multiplicity (M)");
       h_NCJet_M[ich][i]->Sumw2();
       fOutput->Add(h_NCJet_M[ich][i]);  

       h_MET[ich][i] = new TH1D(Form("h_MET_Ch%i_S%i_%s",ich,i,option.Data()), "MET", 40,0,400);
       h_MET[ich][i]->SetXTitle("MET (GeV)");
       h_MET[ich][i]->Sumw2();
       fOutput->Add(h_MET[ich][i]);

     }
   }
} 

Bool_t MyAnalysis::Process(Long64_t entry)
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

   int mode = 999; 
   mode = *channel;

   if( mode > 2) return kTRUE;

   float genweight = *genWeight;
   float puweight = PUWeight[0];
   float EventWeight = puweight*genweight;

   //Object selection
   int njets = 0;
   int nbjets_m = 0; 
   int nbjets_t = 0; 
   int ncjets_m = 0; 

   TLorentzVector lepton;
   lepton.SetPtEtaPhiE(*lepton_pT, *lepton_eta, *lepton_phi, *lepton_E);

   //Event selection 
   bool passmuon = (mode == 0) && (lepton.Pt() > 30);
   bool passelectron = (mode == 1) && (lepton.Pt() > 35);

   if( passmuon || passelectron ){

     for (unsigned int iJet = 0; iJet < jet_pT.GetSize() ; ++iJet) {

       TLorentzVector jet;
       jet.SetPtEtaPhiE(jet_pT[iJet], jet_eta[iJet], jet_phi[iJet], jet_E[iJet]);

       if( jet.Pt() > 30 ){
         njets++;
         if( jet_CSV[iJet] > 0.8484 )  nbjets_m++;
         if( jet_CSV[iJet] > 0.9535 )  nbjets_t++;
         if( jet_CvsL[iJet] > -0.1 && jet_CvsL[iJet] > 0.08 )  ncjets_m++;
       }

     }  

     h_NJet[mode][0]->Fill(njets, EventWeight);
     h_NBJet_CSVv2M[mode][0]->Fill(nbjets_m, EventWeight);
     h_NBJet_CSVv2T[mode][0]->Fill(nbjets_t, EventWeight);
     h_NCJet_M[mode][0]->Fill(ncjets_m, EventWeight);
     h_MET[mode][0]->Fill(*MET, EventWeight);

     if( njets >= 6) {
       h_NJet[mode][1]->Fill(njets, EventWeight);
       h_NBJet_CSVv2M[mode][1]->Fill(nbjets_m, EventWeight);
       h_NBJet_CSVv2T[mode][1]->Fill(nbjets_t, EventWeight);
       h_NCJet_M[mode][1]->Fill(ncjets_m, EventWeight);
       h_MET[mode][1]->Fill(*MET, EventWeight);

       if( nbjets_m >=2 ){
         h_NJet[mode][2]->Fill(njets, EventWeight);
         h_NBJet_CSVv2M[mode][2]->Fill(nbjets_m, EventWeight);
         h_NBJet_CSVv2T[mode][2]->Fill(nbjets_t, EventWeight);
         h_NCJet_M[mode][2]->Fill(ncjets_m, EventWeight);
         h_MET[mode][2]->Fill(*MET, EventWeight);
       }

       if( nbjets_t >=2 ){
         h_NJet[mode][3]->Fill(njets, EventWeight);
         h_NBJet_CSVv2M[mode][3]->Fill(nbjets_m, EventWeight);
         h_NBJet_CSVv2T[mode][3]->Fill(nbjets_t, EventWeight);
         h_NCJet_M[mode][3]->Fill(ncjets_m, EventWeight);
         h_MET[mode][3]->Fill(*MET, EventWeight);
       }
   
     }

   }

   return kTRUE;
}

void MyAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

   TString option = GetOption();

}
   

void MyAnalysis::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   TString option = GetOption();

   TFile * out = TFile::Open(Form("hist_%s.root",option.Data()),"RECREATE");

   for(int ich = 0; ich < 2; ich++){
     for(int i = 0; i < 4; i++){
       fOutput->FindObject(Form("h_NJet_Ch%i_S%i_%s",ich,i,option.Data()))->Write();
       fOutput->FindObject(Form("h_NBJet_CSVv2M_Ch%i_S%i_%s",ich,i,option.Data()))->Write();
       fOutput->FindObject(Form("h_NBJet_CSVv2T_Ch%i_S%i_%s",ich,i,option.Data()))->Write();
       fOutput->FindObject(Form("h_NCJet_M_Ch%i_S%i_%s",ich,i,option.Data()))->Write();
       fOutput->FindObject(Form("h_MET_Ch%i_S%i_%s",ich,i,option.Data()))->Write();
     }
   }

   //fOutput->FindObject("ttbbLepJets/EventInfo")->Write();

   out->Write();
   out->Close();

}
