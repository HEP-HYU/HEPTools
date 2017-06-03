#!/usr/bin/python

from ROOT import TChain, TProof, TFile, TH1D, TH1F, TCanvas

Proof = True

def runAna(dir, file, name):
  chain = TChain("ttbbLepJets/tree","events")
  chain.Add(dir+"/"+file)
  if Proof :
    chain.SetProof();
  chain.Process("MyAnalysis.C+",name)

  f = TFile(dir+"/"+file,"read")

  ## save Event Summary histogram ##
  out = TFile("hist_"+name+".root","update")
  hevt = f.Get("ttbbLepJets/EventInfo")
  hevt.Write()
  out.Write()
  out.Close()


if Proof:
  p = TProof.Open("", "workers=8")

inputdir = "/xrootd/store/user/brochero/v8-0-6/"

runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_DataSingleEG.root","DataSingleEG")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_DataSingleMu.root","DataSingleMu")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_WJets_aMCatNLO.root","wjets")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ZJets_M50_aMCatNLO.root","zjets")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ZJets_M10to50_aMCatNLO.root","zjets10to50")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_WW_Pythia.root","ww")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_WZ_Pythia.root","wz")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ZZ_Pythia.root","zz")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_t_tchannel_Powheg.root","tchannel")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_tbar_tchannel_Powheg.root","tbarchannel")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_tW_Powheg.root","tWchannel")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_tbarW_Powheg.root","tbarWchannel")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_LepJetsPowhegPythiattbb.root","ttbb")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_LepJetsPowhegPythiattbj.root","ttbj")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_LepJetsPowhegPythiattcc.root","ttcc")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_LepJetsPowhegPythiattLF.root","ttLF")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_LepJetsPowhegPythiatt.root","tt")
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_PowhegPythiaBkg.root","ttBkg")

"""
inputdir = "/xrootd/store/user/jhgoh/CATTools/HEPHY/hep2016/v806_1/"

runAna(inputdir,"DataSingleEG.root","DataSingleEG")
runAna(inputdir,"DataSingleMu.root","DataSingleMu")
runAna(inputdir,"WJets_aMCatNLO.root","wjets")
runAna(inputdir,"ZJets_M50_aMCatNLO.root","zjets")
runAna(inputdir,"ZJets_M10to50_aMCatNLO.root","zjets10to50")
runAna(inputdir,"WW_Pythia.root","ww")
runAna(inputdir,"WZ_Pythia.root","wz")
runAna(inputdir,"ZZ_Pythia.root","zz")
runAna(inputdir,"t_tchannel_Powheg.root","tchannel")
runAna(inputdir,"tbar_tchannel_Powheg.root","tbarchannel")
runAna(inputdir,"tW_Powheg.root","tWchannel")
runAna(inputdir,"tbarW_Powheg.root","tbarWchannel")
runAna(inputdir,"ttbar_LepJetsPowhegPythiattbb.root","ttbb")
runAna(inputdir,"ttbar_LepJetsPowhegPythiattbj.root","ttbj")
runAna(inputdir,"ttbar_LepJetsPowhegPythiattcc.root","ttcc")
runAna(inputdir,"ttbar_LepJetsPowhegPythiattLF.root","ttLF")
runAna(inputdir,"ttbar_LepJetsPowhegPythiatt.root","tt")
runAna(inputdir,"ttbar_PowhegPythiaBkg.root","ttBkg")
runAna(inputdir,"TT_TopLeptonicDecay_TH_1L3B_Eta_Hct.root","Top_Hct")
runAna(inputdir,"TT_TopLeptonicDecay_TH_1L3B_Eta_Hut.root","Top_Hut")
runAna(inputdir,"TT_AntitopLeptonicDecay_TH_1L3B_Eta_Hct.root","AntiTop_Hct")
runAna(inputdir,"TT_AntitopLeptonicDecay_TH_1L3B_Eta_Hut.root","AntiTop_Hut")
"""

