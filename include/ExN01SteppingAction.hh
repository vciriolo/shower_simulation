#ifndef SteppingAction_H
#define SteppingAction_H 1
 
/*!
* \file
* \brief User' Stepping Action
*/

#include <vector> 
#include "globals.hh"
#include "G4UserSteppingAction.hh"

/*!
* \brief User's SteppingAction class
* This class implements the Stepping Action
* The relevant method is \sa UserSteppingAction
* This class allows the user to have an handle on each G4Step
*/
class SteppingAction : public G4UserSteppingAction {
 
public:
         //! constructor
         SteppingAction();
         //! destructor
         virtual ~SteppingAction();
         //! Called for each G4Step
         virtual void UserSteppingAction( const G4Step* );
	 
private:
};

 
 
#endif
