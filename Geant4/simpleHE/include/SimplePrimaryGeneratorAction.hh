#ifndef SimplePrimaryGeneratorAction_h
#define SimplePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"
#include "TF1.h"

class G4Event;

class SimplePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  SimplePrimaryGeneratorAction(G4double);    
  virtual ~SimplePrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event*);         
  
  static SimplePrimaryGeneratorAction* GetPointer() {return fPtr;}
  
  const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  /*const 
    G4GeneralParticleSource* GetParticleSource()const{ 
    return fParticleSource; 
    }*/
  
   
private:
  
  TF1* angle_distribution;
  
  TF1* coord_and_az_angle_distr = new TF1("coord_and_az_angle_distr",
					  "1.", -1., 1.);

  double angle_distribution_par_0;
  double angle_distribution_par_1;
  double angle_distribution_par_2;
  double angle_distribution_par_3;

  G4double fAngle;

  G4ParticleGun* fParticleGun;

  double fParticleGun_x;
  double fParticleGun_y;
  double Particle_momentum_phi;
  double Particle_momentum_theta;
  double Particle_momentum_x;
  double Particle_momentum_y;
  double Particle_momentum_z;
  static SimplePrimaryGeneratorAction* fPtr;
};

#endif


