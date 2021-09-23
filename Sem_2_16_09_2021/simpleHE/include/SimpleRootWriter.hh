#ifndef SimpleRootWriter_H
#define SimpleRootWriter_H 1

#include "G4Types.hh"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TFile.h"
#include <string>
#include <iostream>
#include "G4SystemOfUnits.hh"

using namespace std;

class SimpleRootWriter{
  public:
    void Initialize(bool SaveTree=false);	
    void Fill();		// store an event
    void Finalize();	// write tree to a file
    static SimpleRootWriter* GetPointer(){
      if(pInstance==0) pInstance = new SimpleRootWriter();
      return pInstance;
    };
    void ResetEdep(){
      edepScint1 = 0.;
      edepScint2 = 0.;
    };
    void AddEdep1(G4double edep){edepScint1 += edep;};
    void AddEdep2(G4double edep){edepScint2 += edep;};

    void FinalizeEvent(){
      G4double thr = 100*keV;
      cout << "edep1: " << edepScint1/MeV << endl;
      h1[0]->Fill(edepScint1/MeV);
      if (edepScint1 > thr && edepScint2 > thr){
	std::cout << "hit in both detectors!" << std::endl;
      }
    } 

  private:
    SimpleRootWriter(){fSaveTree = false;};	// empty constructor
    static SimpleRootWriter* pInstance;

    bool fSaveTree;

    G4double edepScint1;
    G4double edepScint2;

  public:

    TH1F*  h1[500];
    TH2F*  h2[100];
     
    TTree* tree;

  private:
    TFile* file;
};

#endif
