#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

class G4Event;

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  ~EventAction();
  
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void AddEdep(G4double edepStep) { fEdep += edepStep; }  

private:
  G4int printModulo;
  G4double fEdep;
};


#endif
