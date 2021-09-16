#ifndef SimpleEventAction_h
#define SimpleEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class SimpleEventAction : public G4UserEventAction
{
  public:
    SimpleEventAction();
    virtual ~SimpleEventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

  private:
    G4int  fPrintModulo;
};

#endif

    
