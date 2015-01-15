//
// ********************************************************************
// * License and Disclaimer *
// * *
// * The Geant4 software is copyright of the Copyright Holders of *
// * the Geant4 Collaboration. It is provided under the terms and *
// * conditions of the Geant4 Software License, included in the file *
// * LICENSE and available at http://cern.ch/geant4/license . These *
// * include a list of copyright holders. *
// * *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work make any representation or warranty, express or implied, *
// * regarding this software system or assume any liability for its *
// * use. Please see the license in the file LICENSE and URL above *
// * for the full disclaimer and the limitation of liability. *
// * *
// * This code implementation is the result of the scientific and *
// * technical work of the GEANT4 collaboration. *
// * By using, copying, modifying or distributing the software (or *
// * any work based on the software) you agree to acknowledge its *
// * use in resulting scientific publications, and indicate your *
// * acceptance of all terms of the Geant4 Software license. *
// ********************************************************************
//
// $Id: B4bRunAction.cc 68835 2013-04-06 07:12:41Z asaim $
//
/// \file B4bRunAction.cc
/// \brief Implementation of the B4bRunAction class

#include "ExN01RunAction.hh"
//#include "B4bRunData.hh"
#include "B4Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN01RunAction::ExN01RunAction() : G4UserRunAction()
	{
  	// Create analysis manager
  	G4AnalysisManager* man = G4AnalysisManager::Instance();
	
  	// Creating histograms 
  	analysisManager->CreateH1("1","Energy Left", 500, 0., 500*MeV);
  	}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B4bRunAction::~B4bRunAction()
{
 delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4bRunAction::BeginOfRunAction(const G4Run* run)
	{
 	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
 	G4String fileName = "output";
 	analysisManager->OpenFile(fileName);
	}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B4EventAction::EndOfEventAction(const G4Run* aRun)
	{
	G4AnalysisManager* man = G4AnalysisManager::Instance();
  	man->FillH1(1, fEnergyAbs);
	}

void B4bRunAction::EndOfRunAction(const G4Run* /*aRun*/)
{
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->GetH1(1) ) 
  	{
  	G4cout << "\n ----> print histograms statistic ";
  	if(isMaster) 
  		{
 		G4cout << "for the entire run \n" << G4endl;
 		}
 	else 
 	{
 	G4cout << "for the local thread \n" << G4endl;
	}

 G4cout << " EAbs : mean = "
 << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
 << " rms = "
 << G4BestUnit(analysisManager->GetH1(1)->rms(), "Energy") << G4endl;

  	}

 analysisManager->Write();
 analysisManager->CloseFile();
 }

