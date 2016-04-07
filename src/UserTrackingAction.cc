/////////////////////////////////////////////////////////////////////////
// G4Tutorial:
//
// UserTrackingAction.hh
// 
// Defining actions performed at the start/end point of processing a
// track
//
/////////////////////////////////////////////////////////////////////////


#include "UserTrackingAction.hh"
#include "G4TrackingManager.hh"
#include "G4Electron.hh"


UserTrackingAction::UserTrackingAction() :
    counter(0) {

}


void UserTrackingAction::UserPostTrackingAction(const G4Track*) {

  // The user tracking action class holds the pointer to the tracking manager:
  // fpTrackingManager

  // From the tracking manager we can retrieve the secondary track vector,
  // which is a container class for tracks:
  G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();

  // You can use the secTracks vector to retrieve the number of secondary 
  // electrons
  if(secTracks) { 
     size_t nmbSecTracks = (*secTracks).size();       

     for(size_t i = 0; i < nmbSecTracks; i++) { 
        if((*secTracks)[i] -> GetDefinition() == G4Electron::Definition()) 
              counter++;
     }
  }
}

