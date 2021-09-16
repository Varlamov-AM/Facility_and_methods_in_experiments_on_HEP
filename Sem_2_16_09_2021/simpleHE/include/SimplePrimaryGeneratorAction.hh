#ifndef SimplePrimaryGeneratorAction_h
#define SimplePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;

class SimplePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    SimplePrimaryGeneratorAction();    
    virtual ~SimplePrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);         

    static SimplePrimaryGeneratorAction* GetPointer() {return fPtr;}
  
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
    G4double GetEnergy(){return energy;}
   
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4double energy;
    static SimplePrimaryGeneratorAction* fPtr;
};

#endif


