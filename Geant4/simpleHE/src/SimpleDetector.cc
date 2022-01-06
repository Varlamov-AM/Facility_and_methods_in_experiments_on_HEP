#include "SimpleDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "SimpleRootWriter.hh"
#include <iostream>

using namespace CLHEP;

SimpleDetector::SimpleDetector(const G4String& name) 
  : G4VSensitiveDetector(name)
{
    //std::cout << "hello detector " << SensitiveDetectorName << std::endl;
}
SimpleDetector::~SimpleDetector() 
{}

void SimpleDetector::Initialize(G4HCofThisEvent* hce)
{

}

G4bool SimpleDetector::ProcessHits(G4Step* step, 
                           G4TouchableHistory*)
{  
  if (SensitiveDetectorName == "sc1sd") {
		SimpleRootWriter::GetPointer()->Incr_counter();		
  }

  return true;
}

void SimpleDetector::EndOfEvent(G4HCofThisEvent*)
{

}

