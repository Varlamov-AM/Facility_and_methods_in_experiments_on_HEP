void Exercise_23_09_2021(){

  TFile* files[6];

  files[0] = new TFile("00_degree.root");
  files[1] = new TFile("10_degree.root");
  files[2] = new TFile("20_degree.root");
  files[3] = new TFile("30_degree.root");
  files[4] = new TFile("40_degree.root");
  files[5] = new TFile("50_degree.root");

  TH1F* hists[6];

  for (int i = 0; i < 6; i++){
    hists[i] = (TH1F*)files[i]->Get("edep1");
    TString title = Form("Energy deposition for %d0 degrees", i);
    TString name = Form("en_dep_%d", i);
    hists[i]->SetTitle(title.Data());
    hists[i]->SetName(name.Data());
  }

  TCanvas* c1 = new TCanvas("c1", "c1");

  c1->Divide(2, 3);

  double mean[6];
  double sigm[6];
  TF1* fit_f[6];
  

  for (int i = 0; i < 6; i++){
    c1->cd(i + 1);
    hists[i]->Draw();
    TString name = Form("func_%d", i + 1);
    fit_f[i] = new TF1(name.Data(), "landau", 0., 20.);
    hists[i]->Fit(fit_f[i]);
    sigm[i] = fit_f[i]->GetParameter(2); 
    mean[i] = fit_f[i]->GetParameter(1); 
  }

  TCanvas* c2 = new TCanvas("c2", "c2");
  TCanvas* c3 = new TCanvas("c3", "c3");

  TH1F* means = new TH1F("means", "", 6, -5., 55.);
  TH1F* sigma = new TH1F("sigma", "", 6, -5., 55.);

  for (int i = 0; i < 6; i++){
    means->SetBinContent(i + 1, mean[i]); 
    sigma->SetBinContent(i + 1, sigm[i]);
  }

  c2->cd();
  means->Draw();
  c3->cd();
  sigma->Draw();
  

  TFile* outfile = new TFile("output.root", "RECREATE");

  for (int i = 0; i < 6; i++){
    hists[i]->Write();
  }

  means->Write();
  sigma->Write();
  
  

  return;
}
