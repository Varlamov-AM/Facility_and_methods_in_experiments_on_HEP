#include "SimpleRootWriter.hh"
#include <string>

SimpleRootWriter* SimpleRootWriter::pInstance=0;

void SimpleRootWriter::Initialize(double angle){
  fAngle = angle;
  //char fname[30];
  //sprintf(fname,("simpleHE" + std::to_string(0) +".root").c_str());
  //sprintf(fname,("Logic_test.root").c_str());
  file = new TFile("Angle_test.root","RECREATE");
  
}

void SimpleRootWriter::Fill(){
  
}

void SimpleRootWriter::Incr_counter(){
  counter++;	
}

void SimpleRootWriter::Finalize(){
 
  file->cd();
  hist->Sumw2();
  Both_scint_att->Write();
  hist->Write();
  file->Close();
  
}

