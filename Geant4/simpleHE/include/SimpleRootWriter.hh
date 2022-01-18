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

  void Scint_1_att(bool flag){
    scint_1_att = flag;
  }
  void Scint_2_att(bool flag){
    scint_2_att = flag;
  }


  void Fill();    
  void Finalize();
  void SetThetaPhiAngle(double theta, double phi);
  void FinalizeEvent(){

    Born_phi_theta_distribution->Fill(phi_particle, theta_particle);
    
    if ((scint_1_att == true) || 
	(scint_2_att == true)){
      if ((scint_1_att == true) && 
	  (scint_2_att == true)){
	Both_scint_att->Fill(fAngle, 0.1);
	Signal_depence_from_angle->Fill((fAngle/180.)*3.1415926);
	scint_1_att = false;
        scint_2_att = false;
	
	Registred_phi_theta_distribution->Fill(phi_particle, theta_particle);	
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

  bool scint_1_att;
  bool scint_2_att;

  double theta_particle;
  double phi_particle;

  G4double fAngle;

  TFile* file;
  TH2D* Both_scint_att = 
    new TH2D("Scint_attached_statistics",
	     "First, second or both scint attached",
	     90, 0., 90.,
	     3, 0., 3.);
  TH2D* Born_phi_theta_distribution = 
    new TH2D("Born_phi_theta_distribution",
	     "All simulated particle theta and phi angle distribution",
	     360., 0., 2 * 3.1415926,
	     180., 0., 3.1415926);
  TH2D* Registred_phi_theta_distribution = 
    new TH2D("Registered_phi_theta_distribution",
	     "Registered particle theta and phi angle distribution",
	     360., 0., 2 * 3.1415926,
	     180., 0., 3.1415926);

  TH1D* Signal_depence_from_angle = 
    new TH1D("Signal_depence_from_angle", 
	     "Depence of registered signal from angle",
	     90, 0., 3.141592/2);
  
};

#endif
