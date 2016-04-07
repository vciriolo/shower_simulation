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
  //this->GetTree ()->Branch ("molt2", &this->molt2, "molt2/F");
  //this->GetTree ()->Branch ("EnergyTotal", &this->EnergyTotal, "EnergyTotal/F") ;
  
  Q1 = new vector<float> () ;
  this->GetTree ()->Branch ("Q1","vector<float>",&Q1) ;
  
  Q2 = new vector<float> () ;
  this->GetTree ()->Branch ("Q2","vector<float>",&Q2) ;

  E_sec= new vector<float> ();
  this->GetTree ()->Branch ("E_sec", "vector<float>", &E_sec);
//  Energies_0 = new vector<float> () ;
//  this->GetTree ()->Branch ("Energies_0","vector<float>",&Energies_0) ;
  mult = new vector<float> ();
  this->GetTree ()->Branch ("mult", "vector<float>", &mult);
  //EnergyTotal = new vector<float> ();
  //this->GetTree ()->Branch ("EnergyTotal", "vector<float>", &EnergyTotal) ;
  this->GetTree ()->Branch ("EnergyTotal", &this->EnergyTotal, "EnergyTotal/F") ;    
  this->Clear () ;
cout<<"tree"<<endl;
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
  E_sec -> clear();
  mult -> clear();
  
  Q1 -> clear();
  Q2 -> clear();  
  
//  Energies_0->clear () ;
 }
