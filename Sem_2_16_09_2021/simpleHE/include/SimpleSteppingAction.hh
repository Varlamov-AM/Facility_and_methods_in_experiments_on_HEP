#ifndef SimpleSteppingAction_h
#define SimpleSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SimpleSteppingAction : public G4UserSteppingAction
{
  public:
    SimpleSteppingAction();
    virtual ~SimpleSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
