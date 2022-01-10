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


SimplePrimaryGeneratorAction* SimplePrimaryGeneratorAction::fPtr = 0;

SimplePrimaryGeneratorAction::SimplePrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(), fParticleSource(0)//fParticleGun(0)
{
  fPtr = this;
  //fParticleGun  = new G4ParticleGun(1);
  fParticleSource = new G4GeneralParticleSource();
  fParticleSource->SetParticleDefinition(G4MuonMinus::Definition());
  fParticleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(500*MeV);
  //fParticleSource->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1));
  fParticleSource->GetCurrentSource()->GetAngDist()->SetAngDistType("cos");
  //fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(30*cm, 30*cm, 30*cm));
  G4SingleParticleSource* test = fParticleSource->GetCurrentSource();
  G4SPSPosDistribution* testtest = test->GetPosDist();
  testtest->SetPosDisType("Plane");
  testtest->SetPosDisShape("Rectangle");
  testtest->SetCentreCoords(G4ThreeVector(0.*m, 0.*m, 0.5*m));
  testtest->SetHalfX(30*cm);
  testtest->SetHalfY(30*cm);
  testtest->ConfineSourceToVolume(true);
				     
  
}

SimplePrimaryGeneratorAction::~SimplePrimaryGeneratorAction()
{
  delete fParticleSource;
}

void SimplePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  fParticleSource->GeneratePrimaryVertex(anEvent);

}
