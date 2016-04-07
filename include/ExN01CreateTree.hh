#ifndef CreateTree_H
#define CreateTree_H 1

#include <iostream>
#include <vector>
#include <map>

#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"



class CreateTree
{
private:
  
  TTree*  ftree ;
  TString fname ;
  
public:
  
  CreateTree (TString name);

  
  ~CreateTree () ;
  
  
  TTree*             GetTree  () const { return ftree ; } ;
  TString            GetName  () const { return fname ; } ;

  int                Fill     () ;
  void               Write    (TFile *) ;
  void               Clear    () ;
  static CreateTree* Instance () { return fInstance ; } ;
  static CreateTree* fInstance ;
  
  
  int   Event ;

  float EnergyTotalCalo ;
  float EnergyTotalAbs1 ;
  float EnergyTotalAbs2 ;
  //float molt2;
  float EnergyTotal;
  std::vector<float> * Q1 ;
  std::vector<float> * Q2 ;
  std::vector<float> * E_sec;
  std::vector<float> * mult;
  //std::vector<float> * EnergyTotal;
} ;

#endif
