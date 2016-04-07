#ifndef USERTRACKINGACTION_HH
#define USERTRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "globals.hh"


// G4UserTrackingAction is the base class for defining user actions performed 
// at the beginning and in the end of processing one track:

class UserTrackingAction : public G4UserTrackingAction {

 public:
   UserTrackingAction();
   virtual ~UserTrackingAction() { }

   // G4UserTrackingAction has two method, UserPreTrackingAction and
   // UserPostTrackingAction, which can be overloaded by the user to define 
   // specific actions performed at the beginning and the end of processing 
   // one track.
   // Information about the track can be retrieved from the G4Track object 
   // passed to this function, or from the tracking manager pointer.
   void UserPreTrackingAction(const G4Track*) { }
   virtual void UserPostTrackingAction(const G4Track*);

 private:
   G4int counter;
};

#endif // USERTRACKINGACTION_HH

