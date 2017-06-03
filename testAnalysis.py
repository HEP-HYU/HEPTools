#!/usr/bin/python

from ROOT import TChain, TProof, TFile, TH1D, TH1F, TCanvas

Proof = False

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
runAna(inputdir,"Tree_LepJets_Final_v8-0-6_Spring16-80X_36814pb-1_ttbar_LepJetsPowhegPythiattbb.root","ttbb")

