#include "SimplePrimaryGeneratorAction.hh"
#include "SimpleRootWriter.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Gamma.hh"
#include "G4MuonMinus.hh"
#include "TMath.h"
#include "G4GeneralParticleSource.hh"


Double_t Function(Double_t*, Double_t*);

SimplePrimaryGeneratorAction* SimplePrimaryGeneratorAction::fPtr = 0;

SimplePrimaryGeneratorAction::SimplePrimaryGeneratorAction(G4double angle)
  : G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  fPtr = this;
  fParticleGun  = new G4ParticleGun(1);
  fAngle = angle;

  angle_distribution_par_0 = 1.;
  angle_distribution_par_1 = 1.;
  angle_distribution_par_2 = 8/5;
  angle_distribution_par_3 = -1.;
  
  angle_distribution = 
    new TF1("angle_distribution", Function, 0, 3.1415, 4);
  
  angle_distribution->SetParameters(angle_distribution_par_0,
				    angle_distribution_par_1,
				    angle_distribution_par_2,
				    angle_distribution_par_3);

  fParticleGun->SetParticleDefinition(G4MuonMinus::Definition());
  

}

SimplePrimaryGeneratorAction::~SimplePrimaryGeneratorAction()
{
  delete fParticleGun;
}

void SimplePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
  fParticleGun_x = (coord_and_az_angle_distr->GetRandom()) * 80;
  fParticleGun_y = (coord_and_az_angle_distr->GetRandom()) * 80;
  Particle_momentum_phi =
    TMath::Pi() + (coord_and_az_angle_distr->GetRandom()) * TMath::Pi();
  Particle_momentum_theta = angle_distribution->GetRandom();
  Particle_momentum_x =
    TMath::Sin(Particle_momentum_theta) * TMath::Cos(Particle_momentum_phi);
  Particle_momentum_y =
    TMath::Sin(Particle_momentum_theta) * TMath::Sin(Particle_momentum_phi);
  Particle_momentum_z = 
    -TMath::Cos(Particle_momentum_theta);
  
  /*printf("(%6.3f, %6.3f, %6.3f)\n", 
	 Particle_momentum_x, 
	 Particle_momentum_y, 
	 Particle_momentum_z);*/
  SimpleRootWriter::GetPointer()->
    SetThetaPhiAngle(Particle_momentum_theta, 
		     Particle_momentum_phi);

  G4ThreeVector* position_vector = new G4ThreeVector(fParticleGun_x * cm, 
						     fParticleGun_y * cm,
						     99 * cm);
  
  position_vector->rotateY(-fAngle * degree);
  
  fParticleGun->SetParticlePosition(*position_vector);
  /*fParticleGun->SetParticlePosition(G4ThreeVector(fParticleGun_x * cm,
				      fParticleGun_y * cm,
				      99 * cm));*/
  fParticleGun->
    SetParticleMomentumDirection(G4ThreeVector(Particle_momentum_x,
					       Particle_momentum_y,
					       Particle_momentum_z));
  
  fParticleGun->SetParticleEnergy(500*MeV);


  fParticleGun->GeneratePrimaryVertex(anEvent);
  
}


Double_t Function(Double_t* x, Double_t* p){

  Double_t result;

  if (fabs(p[1]*x[0] - 3.1415926/2) < 1e-1){
    result = 0.0001;
  } else {
    result = p[0] * (pow((fabs(cos(p[1] * x[0]))), p[2])) * 
      exp(p[3]/fabs(cos(p[1] * x[0])));
  }

  return result;
}
