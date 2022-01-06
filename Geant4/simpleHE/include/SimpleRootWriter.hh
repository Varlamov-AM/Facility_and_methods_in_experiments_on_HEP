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

  static SimpleRootWriter* GetPointer(){
    if(pInstance==0) pInstance = new SimpleRootWriter();
    return pInstance;
  };
  
  void Initialize(double angle);
	void Incr_counter();
  void Fill();    // store an event
  void Finalize();	// write tree to a file  
  void SetAngle(G4double angle);
  void FinalizeEvent(){
		if(counter != 0){
			hist->Fill(fAngle);
		}
	};

private:

  //SimpleRootWriter(){};	// empty constructor

  static SimpleRootWriter* pInstance;
  G4int counter;
  G4double fAngle;
  TFile* file;
  TH1D* hist = new TH1D("hist", "Check_logic", 1000, 0., 80.);

  
};

#endif
