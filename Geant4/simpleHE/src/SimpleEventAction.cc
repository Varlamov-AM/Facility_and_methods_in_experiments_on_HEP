#include "SimpleEventAction.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "SimpleRootWriter.hh"

SimpleEventAction::SimpleEventAction()
: G4UserEventAction()
{} 

SimpleEventAction::~SimpleEventAction()
{}

void SimpleEventAction::BeginOfEventAction(const G4Event* event)
{

  G4long total = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  fPrintModulo = G4int(total/20);
  if(fPrintModulo<1) fPrintModulo=1;

  G4int eventNb = event->GetEventID();
  if (eventNb%fPrintModulo == 0) { 
    G4cout << "\n---> Begin of event: " << eventNb << G4endl;
  }
}

void SimpleEventAction::EndOfEventAction(const G4Event*)
{   
    SimpleRootWriter::GetPointer()->FinalizeEvent(); 
}
