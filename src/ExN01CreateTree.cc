#include "ExN01CreateTree.hh"
#include <algorithm>
#include <vector>

using namespace std ;

CreateTree* CreateTree::fInstance = NULL ;


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


CreateTree::CreateTree (TString name)
{
  if ( fInstance )
  {
    return ;
  }


  this->fInstance = this ;
  this->fname     = name ;
  this->ftree     = new TTree (name,name) ;
  
  this->ftree->SetDirectory(0);

  
  this->GetTree ()->Branch ("Event", &this->Event, "Event/I") ;
  
  this->GetTree ()->Branch ("EnergyTotalCalo", &this->EnergyTotalCalo, "EnergyTotalCalo/F") ;
  this->GetTree ()->Branch ("EnergyTotalAbs1", &this->EnergyTotalAbs1, "EnergyTotalAbs1/F") ;  
  this->GetTree ()->Branch ("EnergyTotalAbs2", &this->EnergyTotalAbs2, "EnergyTotalAbs2/F") ;    

  Q1 = new vector<float> () ;
  this->GetTree ()->Branch ("Q1","vector<float>",&Q1) ;
  
  Q2 = new vector<float> () ;
  this->GetTree ()->Branch ("Q2","vector<float>",&Q2) ;

//  Energies_0 = new vector<float> () ;
//  this->GetTree ()->Branch ("Energies_0","vector<float>",&Energies_0) ;

  this->Clear () ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


CreateTree::~CreateTree ()
{}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


int CreateTree::Fill () 
{ 
  return this->GetTree ()->Fill () ; 
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void CreateTree::Write (TFile * outfile)
{
  outfile->cd () ;
  ftree->Write () ;
}


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


void CreateTree::Clear ()
{
  Event	= 0 ;

  EnergyTotalCalo = 0. ;
  EnergyTotalAbs1 = 0. ;  
  EnergyTotalAbs2 = 0. ;  
  
  Q1 -> clear();
  Q2 -> clear();  
  
//  Energies_0->clear () ;
 }
