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
// $Id: ExN01DetectorConstruction.cc,v 1.9 2006-06-29 17:47:19 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//

#include "ExN01DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "ExN01CreateTree.hh"

//pre-shower = |abs = X0| |mcp| |	abs = 2*X0	| |mcp|
   		

float n = 1;    //absorber thickness
float b = 20;    //silica window thickness
float mcp_z = 0.8; //mcp thickness

//Cu
/*
double X_0 = 0.0143;       //Cu
G4double abs_hx = 0.1*m;
G4double abs_hy = 0.1*m;
*/

//Pb
//double X_0 = 0.0143;       //Cu
double X_0 = 0.0056 ;       //Pb (X_0 = 0.0056, but absorber thickness is 0.004)
G4double abs_hx = 0.3*m;
G4double abs_hy = 0.3*m;


ExN01DetectorConstruction::ExN01DetectorConstruction()
 :  worldLog(0), absLog(0), outLog(0),
    worldPhys(0), absPhys(0), outPhys(0)
{;}

ExN01DetectorConstruction::~ExN01DetectorConstruction()
{
}

G4VPhysicalVolume* ExN01DetectorConstruction::Construct()
{

  //------------------------------------------------------ materials

G4String name, symbol;
G4double z, a, density,fractionmass;
G4int ncomponents, natoms;


//defining Pb
density = 11.34*g/cm3;
a = 207.2*g/mole;
G4Element* elPb  = new G4Element(name="Lead"  ,symbol="Pb" , z= 82., a);
G4Material* Pb = new G4Material(name="Lead", z=82., a, density);

//defining Cu
density = 8.96*g/cm3;
a = 63.546*g/mole;
G4Element* elCu  = new G4Element(name="Copper"  ,symbol="Cu" , z= 29., a);
G4Material* Cu = new G4Material(name="Cu", z=29., a, density);

//defining O and O2
density = 0.001429*g/cm3;
a = 15.9994*g/mole;
G4Element* elO  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

//defining Si
density = 2.33*g/cm3;
a = 28.0855*g/mole;
G4Element* elSi  = new G4Element(name="Silicon"  ,symbol="Si" , z= 14., a);
G4Material* matSi = new G4Material(name="Silicon",density,ncomponents=1);
matSi->AddElement(elSi, natoms=1);

//defining N and N2
density = 0.001251*g/cm3;
a = 14.0067*g/mole;
G4Element* elN  = new G4Element(name="Nitrogen"  ,symbol="N" , z= 7., a);

//defining air
density = 0.001275*g/cm3;
G4Material* Air = new G4Material(name="Air",density,ncomponents=2);

Air->AddElement(elN, fractionmass=70.*perCent);
Air->AddElement(elO, fractionmass=30.*perCent);

//defining Si02
density = 2.196*g/cm3;
G4Material* SiO2 = new G4Material(name="Silica",density,ncomponents=2);
SiO2->AddElement(elSi, natoms=1);
SiO2->AddElement(elO, natoms=2);
G4MaterialPropertiesTable* SiO2_MPT = new G4MaterialPropertiesTable();
G4double ppckov[9] = {0.62*eV,0.69*eV,0.775*eV,0.8856*eV,1.0332*eV,1.2398*eV,1.5498*eV,2.0664*eV,3.0996*eV};
G4double rindex[9] = {1.52   ,1.524  ,1.529   ,1.531    ,1.532    ,1.536    ,1.539    ,1.543    ,1.558};
SiO2_MPT->AddProperty("RINDEX",ppckov,rindex,9);
SiO2 -> SetMaterialPropertiesTable(SiO2_MPT);

//defining PbO
density = 9.5*g/cm3;
G4Material* PbO = new G4Material(name="Lead Oxide",density,ncomponents=2);
PbO->AddElement(elPb, natoms=1);
PbO->AddElement(elO, natoms=1);
  
//defining lead glass
density = 5.12*g/cm3;
G4Material* LeadGlass = new G4Material(name="LeadGlass",density,ncomponents=2);

//defining silicon material


LeadGlass->AddMaterial(PbO, fractionmass=40.*perCent);
LeadGlass->AddMaterial(SiO2, fractionmass=60.*perCent);  
  
  //------------------------------------------------------ experimental apparatus

//defining world environment
G4double world_hx = 0.3*m;
G4double world_hy = 0.3*m;
G4double world_hz = 1.*m;

G4Box* worldBox = new G4Box("World", world_hx, world_hy, world_hz);
G4LogicalVolume* worldLog = new G4LogicalVolume(worldBox, Air, "World");
G4PVPlacement* worldPhys = new G4PVPlacement(0,G4ThreeVector(),worldLog,"World",0,false,0);

//defining first absorber: X0

G4double abs_hz = 2*0.5*X_0*m;

G4Box* absBox = new G4Box("Abs", abs_hx, abs_hy, abs_hz);

//G4LogicalVolume* absLog = new G4LogicalVolume(absBox, Cu, "Abs");
G4LogicalVolume* absLog = new G4LogicalVolume(absBox, Pb, "Abs");

G4double pos_x =  0.0*meter;
G4double pos_y =  0.0*meter;
//G4double pos_z =  4.*0.5*n*X_0;//+0.1*meter;
G4double pos_z =  0.1 * meter;
//G4double pos_z =  0.20*meter;

G4PVPlacement* absPhys = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),absLog,"Abs",worldLog,false,0);

//defining second absorber: 2*X0
/*
abs_hz = X_0*m;

G4Box* absBox_2 = new G4Box("Abs2", abs_hx, abs_hy, abs_hz);

//G4LogicalVolume* absLog_2 = new G4LogicalVolume(absBox_2, Cu, "Abs2");
G4LogicalVolume* absLog_2 = new G4LogicalVolume(absBox_2, Pb, "Abs");

pos_x =  0.0*meter;
pos_y =  0.0*meter;
pos_z = 2.*meter;
//pos_z =  2.*n*X_0*meter+0.01*meter;
//pos_z =  2.*n*X_0*meter + 2*mcp_z*0.001*meter + 2.*cm;

G4PVPlacement* absPhys_2 = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),absLog_2,"Abs2",worldLog,false,0);


//defining third absorber: 3*X0

abs_hz = X_0*m;

G4Box* absBox_3 = new G4Box("Abs3", abs_hx, abs_hy, abs_hz);

//G4LogicalVolume* absLog_2 = new G4LogicalVolume(absBox_2, Cu, "Abs2");
G4LogicalVolume* absLog_3 = new G4LogicalVolume(absBox_3, Pb, "Abs");

pos_x =  0.0*meter;
pos_y =  0.0*meter;
pos_z = 3.*meter;
//pos_z =  3.*n*X_0*meter + 0.01*meter;

G4PVPlacement* absPhys_3 = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),absLog_3,"Abs3",worldLog,false,0);
*/

//defining first mcp 
/*
G4double innerRadius = 0.*cm;
G4double outerRadius = 0.3*m;;
G4double hz = 0.26*mm;
G4double startAngle = 0.*deg;
G4double spanningAngle = 360.*deg;

pos_z = (X_0 + mcp_z*0.001)*meter + 1.*cm;// + 1.*meter;
G4Tubs* mcpTube = new G4Tubs("mcp", innerRadius, outerRadius, mcp_z, startAngle, spanningAngle);
G4LogicalVolume* mcpLog = new G4LogicalVolume(mcpTube, LeadGlass, "mcp");

G4PVPlacement* mcpPhys_1 = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),mcpLog,"mcp",worldLog,false,0);
*/
//defining second mcp 

G4double innerRadius = 0.*cm;
//G4double outerRadius = 0.02*m;;
//G4double outerRadius = 0.0039*m;;
//G4double outerRadius = 0.56*cm;
G4double outerRadius = 0.39*cm;
G4double hz = 0.15*mm;
G4double startAngle = 0.*deg;
G4double spanningAngle = 360.*deg;

//G4double pos_x = 0.*meter;
//G4double pos_y = 0.*meter; 0.1112
//pos_z = 0.065*meter - 4*0.5*X_0*2 *meter - 0.01*meter * 0.5* 0.0056 * meter + 1.5 * 2.5 * X_0 * meter - 0.005 * meter;//+ 0.000160*meter;// + 0.001*meter;      //no absorber
//pos_z = 0.1196 * meter + 
pos_z = 0.133* meter;
//pos_z = 5.0*0.5*X_0*meter + 0.5*X_0*meter+0.01*meter;  //X0!=0
//pos_z = (5.*X_0 + 4.*mcp_z*0.001)*meter + 4.*cm;
G4Tubs* mcpTube = new G4Tubs("mcp2", innerRadius, outerRadius, hz, startAngle, spanningAngle);
G4LogicalVolume* mcpLog = new G4LogicalVolume(mcpTube, matSi, "mcp2");

G4PVPlacement* mcpPhys_2 = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),mcpLog,"mcp2",worldLog,false,0);
 
//defining calorimeter   
/*

abs_hz = 12.5*X_0*m;

G4Box* CaloBox = new G4Box("Calo", abs_hx, abs_hy, abs_hz);

//G4LogicalVolume* CaloLog = new G4LogicalVolume(CaloBox_2, Cu, "Calo");
G4LogicalVolume* CaloLog = new G4LogicalVolume(CaloBox, Pb, "Calo");

pos_x =  0.0*meter;
pos_y =  0.0*meter;
pos_z =  15.5*n*X_0*meter + 3*mcp_z*0.001*meter + 4.*cm;

G4PVPlacement* CaloPhys = new G4PVPlacement(0,G4ThreeVector(pos_x, pos_y, pos_z),CaloLog,"Calo",worldLog,false,0); 
*/
  //------------------------------------------------------------------

  return worldPhys;
}

