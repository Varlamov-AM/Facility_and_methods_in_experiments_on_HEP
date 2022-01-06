#include "SimpleRootWriter.hh"
#include <string>

SimpleRootWriter* SimpleRootWriter::pInstance=0;

void SimpleRootWriter::Initialize(double angle){
  fAngle = angle;
  //char fname[30];
  //sprintf(fname,("simpleHE" + std::to_string(0) +".root").c_str());
  //sprintf(fname,("Logic_test.root").c_str());
  file = new TFile("Logic_test.root","RECREATE");
  
}

void SimpleRootWriter::Fill(){
	printf("Testing!\n");
}

void SimpleRootWriter::Incr_counter(){
	counter++;	
}

void SimpleRootWriter::Finalize(){
	file->cd();
  hist->Sumw2();
	hist->Write();
  file->Close();

}

