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

SimplePrimaryGeneratorAction::SimplePrimaryGeneratorAction(G4double d, 
							   G4double a,
							   G4double angle)
  : G4VUserPrimaryGeneratorAction(), fParticleSource(0)//fParticleGun(0)
{
  fPtr = this;
  //fParticleGun  = new G4ParticleGun(1);
  G4double ang = angle*degree;
  G4double D = 75*cm;
  G4double A;
  
  A = (2 * (a/d) * D);
  fParticleSource = new G4GeneralParticleSource();
  fParticleSource->SetParticleDefinition(G4MuonMinus::Definition());
  fParticleSource->GetCurrentSource()->GetEneDist()->SetMonoEnergy(500*MeV);
  fParticleSource->GetCurrentSource()->GetAngDist()->SetAngDistType("cos");
  fParticleSource->GetCurrentSource()->GetAngDist()->DefineAngRefAxes("angref1", G4ThreeVector(TMath::Cos(ang), 0, TMath::Sin(ang)));
  fParticleSource->GetCurrentSource()->GetAngDist()->DefineAngRefAxes("angref2", G4ThreeVector(0., 1., 0.));
  fParticleSource->GetCurrentSource()->GetPosDist()->SetPosDisType("Plane");
  fParticleSource->GetCurrentSource()->GetPosDist()->SetPosDisShape("Rectangle");
  fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0.*m, 0.*m, D));
  fParticleSource->GetCurrentSource()->GetPosDist()->SetHalfX(A/2);
  fParticleSource->GetCurrentSource()->GetPosDist()->SetHalfY(A/2);
  fParticleSource->GetCurrentSource()->GetPosDist()->ConfineSourceToVolume(true);
				     
  
}

SimplePrimaryGeneratorAction::~SimplePrimaryGeneratorAction()
{
  delete fParticleSource;
}

void SimplePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  fParticleSource->GeneratePrimaryVertex(anEvent);

}
