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
// $Id: ExN01PrimaryGeneratorAction.hh,v 1.5 2006-06-29 17:47:17 gunter Exp $
// GEANT4 tag $Name: geant4-09-04-patch-02 $
//

#ifndef ExG4PrimaryGeneratorAction01_h
#define ExG4PrimaryGeneratorAction01_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "ExN01RandomGenerator.hh"

//#include "ExN01RandomGenerator.hh"

//ExN01RandomGenerator *randomizer = new ExN01RandomGenerator("profile_beam.root");


class G4ParticleGun;
class G4Event;

class ExG4PrimaryGeneratorAction01 : public G4VUserPrimaryGeneratorAction
{
  public:
    /*
    ExG4PrimaryGeneratorAction01(const G4String& particleName = "e-",G4double energy = 491.*MeV,
      G4ThreeVector position = G4ThreeVector(0.,0.,0.), //= G4ThreeVector(posx*mm, posy*mm, 0.),
      G4ThreeVector momentumDirection = G4ThreeVector(0,0,1));    
    */
    //ExG4PrimaryGeneratorAction01(const G4String& particleName, G4double energy, G4ThreeVector position, G4ThreeVector momentumDirection);
    ExG4PrimaryGeneratorAction01(std::string call, float gev);
    ~ExG4PrimaryGeneratorAction01();

    // methods
    virtual void GeneratePrimaries(G4Event*);

  private:
    // data members
    ExN01RandomGenerator *rand_;
    G4ParticleGun*  fParticleGun; //pointer a to G4 service class
    float gev_;
};

#endif


