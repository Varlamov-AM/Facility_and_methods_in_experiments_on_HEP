#include "SimplePrimaryGeneratorAction.hh"

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

SimplePrimaryGeneratorAction* SimplePrimaryGeneratorAction::fPtr = 0;

SimplePrimaryGeneratorAction::SimplePrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(), fParticleGun(0)
{
  fPtr = this;
  fParticleGun  = new G4ParticleGun(1);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particle);
}

SimplePrimaryGeneratorAction::~SimplePrimaryGeneratorAction()
{
  delete fParticleGun;
}

void SimplePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // fParticleGun->SetParticleEnergy(100*MeV);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

