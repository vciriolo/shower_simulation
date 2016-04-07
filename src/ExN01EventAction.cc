#include "ExN01EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "ExN01CreateTree.hh"
#include "B1Run.hh"

#include <vector>

using namespace CLHEP;



EventAction::EventAction ()

: G4UserEventAction(),
  fEdep(0.)
 {} 



// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


EventAction::~EventAction ()
{}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void EventAction::BeginOfEventAction (const G4Event* evt)
{
  G4int evtNb = evt->GetEventID () ;
 std::cout<<"eventActio"<<std::endl;
  //CreateTree::Instance ()->Clear () ;
  // INSTANCE RUN/EVENT IN TREE
  //CreateTree::Instance ()->Event = evt->GetEventID () ;
  fEdep = 0.;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void EventAction::EndOfEventAction(const G4Event* evt)
{
float EnergyTotal;
  evt -> GetEventID();
  CreateTree::Instance ()->EnergyTotal = fEdep;
  B1Run* run  = static_cast<B1Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);
//EnergyTotal = fEdep;

CreateTree::Instance ()->Fill ();
  std::cout<<EnergyTotal<<std::endl;
//  EventAction::AddEdep(G4double edep);
}

// ----------------




 





