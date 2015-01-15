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

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "ExN01DetectorConstruction.hh"
#include "ExN01PhysicsList.hh"
#include "ExN01PrimaryGeneratorAction.hh"

G4String name, symbol;
G4double z, a, density;
G4int ncomponents, natoms;

//defining Cu
density = 8.96*g/cm3;
a = 63.546*g/mole;

//G4Material* Cu = new G4Material(name="Cu", z=29., a, density);
G4Element* elCu  = new G4Element(name="Copper"  ,symbol="Cu" , z= 29., a);

//defining O and O2
density = 0.001429*g/cm3;
a = 15.9994*g/mole;

//G4Material* O = new G4Material(name="O", z=8., a, density);
G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

//density = 0.001309*g/cm3;
//G4Material* O2 = new G4Material(name="O2",density,ncomponents=1);
//O2->AddElement(elO,natoms=2);

//defining N and N2
density = 0.001251*g/cm3;
a = 14.0067*g/mole;

//G4Material* N = new G4Material(name="N", z=7., a, density);
G4Element* elN  = new G4Element(name="Nitrogen"  ,symbol="N" , z= 7., a);

//density = 0.001145*g/cm3;
//G4Material* N2 = new G4Material(name="N2",density,ncomponents=1);
//N2->AddElement(elN,natoms=2);

//defining air
density = 0.001275*g/cm3;
G4Material* Air = new G4Material(name="Air",density,ncomponents=2);

Air->AddElement(elN, fractionmass=70*perCent);
Air->AddElement(elO, fractionmass=30*perCent);

//constructing particles
void MyPhysicsList::ConstructParticles()
{
  G4Electron::ElectronDefinition();
  G4Gamma::GammaDefinition();
}
//defining processes
void MyPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
}

void MyPhysicsList::ConstructEM()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  G4ParticleDefinition* particle = G4Gamma::GammaDefinition(); 
  ph->RegisterProcess(new G4PhotoElectricEffect(), particle);
  ph->RegisterProcess(new G4ComptonScattering(), particle);
  ph->RegisterProcess(new G4GammaConversion(), particle);
}



//defining world environment
G4double world_hx = 4.0*m;
G4double world_hy = 4.0*m;
G4double world_hz = 4.0*m;

G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);
G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Air, "World");

//defining absorber
double X_0 = 0.0143;

G4double abs_hx = 0.05*m;
G4double abs_hy = 0.05*m;
G4double abs_hx = X_0*m;

G4Box* absBox = new G4Box("abs", abs_hx, abs_hy, abs_hz);
G4LogicalVolume* absLog = new G4LogicalVolume(absBox, Cu, "abs");

G4double pos_x =  2.0*meter;
G4double pos_y =  2.0*meter;
G4double pos_z =  2.0*meter;


//G4VPhysicalVolume* trackerPhys = new G4PVPlacement(rotation angle,translation position,logical volume,"logical volume name", mother,boolean operator, copy number);
G4VPhysicalVolume* trackerPhys = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),absBox,"abs",worldLog,false,0);


int main()
{
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
  //
  G4VUserPrimaryGeneratorAction* gen_action = new ExN01PrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);

  // Initialize G4 kernel
  //
  runManager->Initialize();

  // Get the pointer to the UI manager and set verbosities
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI->ApplyCommand("/run/verbose 1");
  UI->ApplyCommand("/event/verbose 1");
  UI->ApplyCommand("/tracking/verbose 1");

  // Start a run
  //
  G4int numberOfEvent = 3;
  runManager->BeamOn(numberOfEvent);

  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
  delete runManager;

  return 0;
}


