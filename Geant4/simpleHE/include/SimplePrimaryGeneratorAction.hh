#ifndef SimplePrimaryGeneratorAction_h
#define SimplePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"

class G4Event;

class SimplePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  SimplePrimaryGeneratorAction(G4double, G4double, G4double);    
  virtual ~SimplePrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event*);         
  
  static SimplePrimaryGeneratorAction* GetPointer() {return fPtr;}
  
  //const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  const 
  G4GeneralParticleSource* GetParticleSource()const{ 
    return fParticleSource; 
  }
 
   
private:
  G4GeneralParticleSource* fParticleSource;
  G4double energy;
  static SimplePrimaryGeneratorAction* fPtr;
};

#endif


