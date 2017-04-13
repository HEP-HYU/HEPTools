void QCDEstimate(){

  TFile * f = new TFile("hist_qcd.root");

  TH1F * qcd_mu_S0 = (TH1F*) f->Get("h_LepIsoQCD_Ch0_S0_qcd");
  TH1F * qcd_ele_S0 = (TH1F*) f->Get("h_LepIsoQCD_Ch1_S0_qcd");

  double mu_B = qcd_mu_S0->Integral(1,15);
  double mu_A = qcd_mu_S0->Integral(16,100);
  double mu_ratio = mu_B / mu_A ;

  cout << "[Mu] ratio B/A = " << mu_ratio << endl;

  TCanvas * mu_c = new TCanvas("mu_c","mu_c",1);
  qcd_mu_S0->Draw();
  mu_c->Print("qcd_mu_S0.pdf");

  double ele_B = qcd_ele_S0->Integral();
  double ele_A = qcd_ele_S0->Integral(16,100);
  double ele_ratio = ele_B / ele_A ;
  cout << "[Ele] ratio B/A = " << ele_ratio << endl;

  TCanvas * ele_c = new TCanvas("ele_c","ele_c",1);
  qcd_ele_S0->Draw();
  ele_c->Print("qcd_ele_S0.pdf");
}
