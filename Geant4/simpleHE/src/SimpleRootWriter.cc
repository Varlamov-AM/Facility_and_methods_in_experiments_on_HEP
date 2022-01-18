#include "SimpleRootWriter.hh"
#include <string>

SimpleRootWriter* SimpleRootWriter::pInstance=0;

void SimpleRootWriter::Initialize(double angle){
  fAngle = angle;
  //char fname[30];
  //sprintf(fname,("simpleHE" + std::to_string(0) +".root").c_str());
  //sprintf(fname,("Logic_test.root").c_str());
  TString name = Form("Signal_test%04.1f.root", fAngle);
    file = new TFile(name.Data(),"RECREATE");
  
}

void SimpleRootWriter::Fill(){
  
}


void SimpleRootWriter::SetThetaPhiAngle(double theta, double phi){
  theta_particle = theta;
  phi_particle = phi;
}


void SimpleRootWriter::Finalize(){
 
  file->cd();
  Both_scint_att->Write();
  Born_phi_theta_distribution->Write();
  Registred_phi_theta_distribution->Write();
  Signal_depence_from_angle->Write();
  file->Close();
  
}

