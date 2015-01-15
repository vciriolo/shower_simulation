#include "ExN01EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "ExN01CreateTree.hh"

#include <vector>

using namespace CLHEP;



EventAction::EventAction ()
{}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


EventAction::~EventAction ()
{}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void EventAction::BeginOfEventAction (const G4Event* evt)
{
  G4int evtNb = evt->GetEventID () ;
  CreateTree::Instance ()->Clear () ;
  // INSTANCE RUN/EVENT IN TREE
  CreateTree::Instance ()->Event = evt->GetEventID () ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void EventAction::EndOfEventAction(const G4Event* evt)
{
  evt -> GetEventID();
  CreateTree::Instance ()->Fill ();
}
