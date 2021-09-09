#include <TFile.h>
#include <TH1.h>
#include <TRandom.h>
#include <TMath>


void ROOT_script_muon_in_msterial_ions_loose(){

  TFile* outfile = new TFile("outfile.root", "RECREATE");

  TH1D* hist_with_Landau = new TH1D("hist_with_Landau", "Hist_title", 1000, -10., 10.);

  const int npl = 20;

  hist_with_Landau->FillRandom("landau",100000);

  TH1D* hist_arr[npl];

  for (int i = 0; i < npl; i++){
    TString name = Form("hist_with_Landau_%d", i + 1);
    TString title = Form("hist_title_%d", i + 1);

    hist_arr[i] = new TH1D(name.Data(), title.Data(), 1000, -10, 10 * (i + 1));
  }

  double en_lose[100000][npl];



  for (int i = 0; i < 100000; i++){
    for (int j = 0; j < npl; j++){
      en_lose[i][j] = gRandom->Landau();
    }
  }

  double sum_en_lose[100000][npl];

  for (int i = 0; i < 100000; i++){
    for (int j = 0; j < npl; j++){
      for (int k = 0; k <= j; k++){
	sum_en_lose[i][j] += en_lose[i][k]; 
	printf("i = %d, j = %d\n", i, j);
      }
    }
  }

  for (int i = 0; i < 100000; i++){
    for (int j = 0; j < npl; j++){
      hist_arr[j]->Fill(sum_en_lose[i][j]);   
    }
  }

  hist_with_Landau->Write();

  TCanvas* c1 = new TCanvas("c1", "c1");
  c1->Divide(3, 3);
  c1->cd(1);
  hist_with_Landau->Draw();

  for (int i = 0; i < npl; i++){
    c1->cd(i + 2);
    hist_arr[i]->Draw();
    hist_arr[i]->Write();
  }

  TCanvas* c2 = new TCanvas("c2", "c2");

  c2->cd();

  hist_arr[0]->SetLineColor(kBlue);
  hist_arr[1]->SetLineColor(kRed);
  hist_arr[2]->SetLineColor(kGreen);
  hist_arr[3]->SetLineColor(kCyan);
  hist_arr[4]->SetLineColor(kOrange);

  hist_arr[7]->Draw();
  hist_arr[6]->Draw("same");
  hist_arr[5]->Draw("same");
  hist_arr[4]->Draw("same");
  hist_arr[3]->Draw("same");
  hist_arr[2]->Draw("same");
  hist_arr[1]->Draw("same");
  hist_arr[0]->Draw("same");
  //hist_arr[4]->SetAxisRange(0, 30000, "Y");

  return;
}
