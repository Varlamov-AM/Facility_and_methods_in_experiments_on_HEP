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
  
	void Initialize(double angle); // initialization method. Declare in SimpleROOTWriter.cc
  void Incr_counter();
	void Scint_1_att(bool flag){
		scint_1_att = flag;
	}
	void Scint_2_att(bool flag){
		scint_2_att = flag;
	}
  void Fill();    // store an event
  void Finalize();	// write tree to a file  
  void SetAngle(G4double angle);
  void FinalizeEvent(){
		if(counter != 0){
			hist->Fill(fAngle);
		}

		if ((scint_1_att == true) || 
				(scint_2_att == true)){
			if ((scint_1_att == true) && 
					(scint_2_att == true)){
				Both_scint_att->Fill(fAngle, 0.1);
				scint_1_att = false;
        scint_2_att = false;
			}
			if (scint_1_att == true){
				Both_scint_att->Fill(fAngle, 1.1);
			}			
			if (scint_2_att == true){
				Both_scint_att->Fill(fAngle, 2.1);
			}

		}
	};

private:

  //SimpleRootWriter(){};	// empty constructor

  static SimpleRootWriter* pInstance;
  G4int counter;
	bool scint_1_att;
	bool scint_2_att;
  G4double fAngle;
  TFile* file;
  TH1D* hist = new TH1D("hist", "Check_logic", 1000, 0., 80.);
	TH2D* Both_scint_att = new TH2D("Scint_attached_statistics",	"First, second or both scint attached", 90, 0., 90., 3, 0., 3.);

  
};

#endif
