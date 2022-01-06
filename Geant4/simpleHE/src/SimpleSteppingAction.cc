#include "SimpleSteppingAction.hh"
#include "G4Step.hh"

#include <cmath>

using namespace CLHEP;

SimpleSteppingAction::SimpleSteppingAction() : G4UserSteppingAction()
{}

SimpleSteppingAction::~SimpleSteppingAction() {}

void SimpleSteppingAction::UserSteppingAction(const G4Step* step)
{
  int pdg = step->GetTrack()->GetDefinition()->GetPDGEncoding();

  double edep = step->GetTotalEnergyDeposit();
  G4ThreeVector position = step->GetTrack()->GetPosition();

/*  if (fabs(pdg) == 13 && edep>0) // only muon, edep > 0
  {
    G4cout << "Pos: " << position << " edep " << edep/MeV << " [MeV]" << G4endl;
  }
*/
}

