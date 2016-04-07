//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: exampleN01.cc,v 1.6 2006-06-29 17:47:10 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//
// 
// --------------------------------------------------------------
//      GEANT 4 - exampleN01
// --------------------------------------------------------------

#include "G4EmUserPhysics.hh"

#include "ExN01EventAction.hh"
#include "ExN01CreateTree.hh"

#include <string>
#include <vector>
#include <map>
#include "B4Analysis.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "ExN01DetectorConstruction.hh"
#include "ExN01PhysicsList.hh"
#include "ExN01PrimaryGeneratorAction.hh"

#include "ExN01SteppingAction.hh"

#include "ExN01RandomGenerator.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#include "ExN01VisAction.hh"
#endif

#include "G4SystemOfUnits.hh"

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

using namespace CLHEP;
using namespace std;

int main(int argc,char** argv) 
{
  float energia;
  TString nome_file;
  /*
  if ( argc == 2 )
  	{
	TString argomento = (argv[1]);
	nome_file = argomento + "GeV.root";		
  	energia = atof (argv[1]);
  	}
  
  cout<<nome_file<<endl;
    */	
  // Construct the default run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  //
  G4VUserDetectorConstruction* detector = new ExN01DetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new ExN01PhysicsList;
  runManager->SetUserInitialization(physics);

  // set mandatory user action class
  

  //std::string name = ("/afs/cern.ch/user/n/ntrevisa/geant4/molteplice/profile_beam.root");
    std::string name = ("/afs/cern.ch/user/n/ntrevisa/public/profile_beam.root");
  G4VUserPrimaryGeneratorAction* gen_action = new ExG4PrimaryGeneratorAction01(name,energia);
  runManager->SetUserAction(gen_action);
cout<<"check1"<<endl;
  //Creating Tree
    CreateTree* mytree = new CreateTree ("tree") ; 

  G4UserEventAction* event_action = new EventAction();
  runManager->SetUserAction(event_action);

    
  G4UserSteppingAction* stpAct = new SteppingAction();
  runManager->SetUserAction(stpAct);
  
  
  runManager->Initialize();
  //G4int numberOfEvent = 15000;
  //unManager->BeamOn(numberOfEvent);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef G4VIS_USE
  // Initialize visualization                                                                                                                               
G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.                                                                              
  //G4VisManager* visManager = new G4VisExecutive("Quiet");                                                                                                
  visManager->Initialize();
#endif
    cout<<"check2"<<endl;
  // Get the pointer to the User Interface manager                                                                                                          
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  /*if (argc!=1) {
    // batch mode                 
    cout<<"check2-if"<<endl;                                                                                                                          
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
       cout<<"checkUImanager"<<endl;
    UImanager->ApplyCommand(command+fileName);
    cout<<"checkApllyCommand"<<endl;
  }
  else{
    cout<<"checkElse"<<endl;
    // interactive mode : define UI session                                                                                                                
*/
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute vis.mac");
#endif
    ui->SessionStart();
    delete ui;
#endif
  //}
#ifdef G4VIS_USE
  delete visManager;
#endif

    cout<<"check3"<<endl;//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Get the pointer to the UI manager and set verbosities
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");

cout<<"check4"<<endl;
  // Start a run
  //

  //G4int numberOfEvent = 15000;
  //runManager->BeamOn(numberOfEvent);
  
   cout<<"checkBeamON"<<endl;
 // TFile *output = new TFile(nome_file,"RECREATE");
  //mytree->Write(output);
  //output->Close();
  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
  delete runManager;

  return 0;
}


