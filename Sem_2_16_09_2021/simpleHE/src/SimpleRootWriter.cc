#include "SimpleRootWriter.hh"

SimpleRootWriter* SimpleRootWriter::pInstance=0;

void SimpleRootWriter::Initialize(bool SaveTree){

  char fname[30];
  sprintf(fname,"simpleHE.root");
  file = new TFile(fname,"RECREATE");

  int hidx = 0;
  for (hidx=0; hidx<100; hidx++)
  {
    h1[hidx]=0;
    h2[hidx]=0;
  }

  fSaveTree = SaveTree;
}

void SimpleRootWriter::Fill(){
  if(fSaveTree) tree->Fill();
}

void SimpleRootWriter::Finalize(){
  file->cd();

  int hidx = 0;
  for (hidx=0; hidx<100; hidx++)
  {
    if (h1[hidx]!=0) {h1[hidx]->Sumw2(); h1[hidx]->Write();}
    if (h2[hidx]!=0) {h2[hidx]->Sumw2(); h2[hidx]->Write();}
  }

  if(fSaveTree && tree!=0) tree->Write();

  file->Close();
}


