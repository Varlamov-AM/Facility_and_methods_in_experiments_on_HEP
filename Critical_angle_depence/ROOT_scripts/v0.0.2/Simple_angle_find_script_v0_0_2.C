void Simple_angle_find_script_v0_0_2(){

  TFile* file[16];
  TFile* output = new TFile("output_simple_critical_angle_v0_0_2.root",
			    "Recreate");
  TH2D* hist[16];
  TCanvas* canv[16];
  TCanvas* canvas = new TCanvas("canvas", "canvas");
  canvas->Divide(4, 4);
  double angle[16];

  TH1D* crit_angle = new TH1D("Crit_angle", 
     "Depence of critical angle of particle from coordinate", 
			      16, 0., 1.);

  for(int i = 0; i <= 15; i++){
    TString name;
    if (i < 10){
      name = Form("both_scint_test_0%d.root", i);
    }
    else {
      name = Form("both_scint_test_%d.root", i);      
    }

    file[i] = new TFile(name.Data());
    hist[i] = (TH2D*)file[i]->Get("Scint_attached_statistics");
    hist[i]->SetName(((Form("Scint_attached_statistics_%02d_cm", i))));
    hist[i]->SetXTitle("#alpha_{crit}, deg");
    canv[i] = new TCanvas( Form("c%d", i), Form("c%d", i));
    canv[i]->cd();
    hist[i]->Draw("colz");
    canvas->cd(i + 1);
    hist[i]->Draw("colz");
    gStyle->SetOptStat(0);
    angle[i] = hist[i]->GetBinContent(1, 1);
    for (int j = 1; j < 100; j++){
      if ((hist[i]->GetBinContent(j, 1)) < 50){
	angle[i] = j;
	
	break;
      }
    }
    printf("%4.2f\n", angle[i]);
    crit_angle->SetBinContent(i, angle[i]);

  }
  TCanvas* c = new TCanvas("c", "c");
  crit_angle->Sumw2();
  crit_angle->SetYTitle("#alpha_{crit}, deg");
  crit_angle->Draw();


  output->cd();
  
  for (int i = 0; i <= 15; i++){
    hist[i]->Write();
  }

  crit_angle->Write();


  return;
}
