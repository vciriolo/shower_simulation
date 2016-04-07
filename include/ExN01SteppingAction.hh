#ifndef SteppingAction_H
#define SteppingAction_H 1
 
/*!
* \file
* \brief User' Stepping Action
*/

#include <vector> 
#include "globals.hh"
#include "G4UserSteppingAction.hh"
#include "ExN01EventAction.hh"

/*!
* \brief User's SteppingAction class
* This class implements the Stepping Action
* The relevant method is \sa UserSteppingAction
* This class allows the user to have an handle on each G4Step
*/

class EventAction;
class G4LogicalVolume; 

class SteppingAction : public G4UserSteppingAction {
 
public:
         //! constructor
         SteppingAction(EventAction* EventAction);
         //! destructor
         virtual ~SteppingAction();
         //! Called for each G4Step
         virtual void UserSteppingAction( const G4Step* );
 
	 
private:
EventAction* fEventAction;
G4LogicalVolume* fScoringVolume;
};

 
 
#endif
