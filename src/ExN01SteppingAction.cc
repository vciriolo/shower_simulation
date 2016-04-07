/**
* @file   SteppingAction.cc
*
* @date   17 Dec 2009
* @author adotti
*
* @brief  Implements user class SteppingAction.
*/
#include <vector>
#include <map>

#include "ExN01CreateTree.hh"
#include "B4Analysis.hh"
#include "LinkDef.h"
#include "ExN01SteppingAction.hh"
#include "ExN01EventAction.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"
#include "G4Electron.hh"
#include "G4RunManager.hh"
#include "G4Gamma.hh"
#include "ExN01DetectorConstruction.hh"

double casualen (double min, double max)			//random numbers generator
    {
    return (min + (max - min)*rand()/(1.*RAND_MAX));
    }

using namespace std ;

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
fScoringVolume(0)

	{}

SteppingAction::~SteppingAction()
	{

	}	

/*void SteppingAction::UserSteppingAction( const G4Step * theStep ) 
	{  */



void SteppingAction::UserSteppingAction(const G4Step* theStep)
{


G4StepPoint* point1 = theStep->GetPreStepPoint();
	G4StepPoint* point2 = theStep->GetPostStepPoint();

G4TouchableHandle touch1 = point1->GetTouchableHandle();
	G4VPhysicalVolume* pre_volume = touch1->GetVolume();
    	G4String pre_volName = "" ; if ( pre_volume ) pre_volName = pre_volume -> GetName () ;

    	//get the name of the volume in which the particles is at the end of the step
   	G4TouchableHandle touch2 = point2->GetTouchableHandle();
   	G4VPhysicalVolume* post_volume = touch2->GetVolume();
    	G4String post_volName = "" ; if ( post_volume ) post_volName = post_volume -> GetName () ;
//cout<<"prevol:"<<"\t"<<pre_volName<<endl;
//cout<<"postVol:"<<"\t"<<post_volName<<endl;
//if ( (pre_volName == "World" && post_volName == "mcp2") || (pre_volName == "mcp2" && post_volName == "World")|| (post_volName == "mcp2") )	{
if  (pre_volName == "mcp2"){// && post_volName == "mcp2"){// && post_volName == "World")|| (post_volName == "mcp2") )	{  
//if(post_volName == "mcp2" && pre_volName == "mcp2"){
  /*if (!fScoringVolume) { 
    const ExN01DetectorConstruction* detectorConstruction
      = static_cast<const ExN01DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume 
    = theStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  /*if (volume != fScoringVolume) {
  cout<<"return"<<endl;
return;}*/

/*if (!fScoringVolume) { 
    const ExN01DetectorConstruction* detectorConstruction
      = static_cast<const ExN01DetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }*/

  // get volume of the current step
  G4LogicalVolume* volume 
    = theStep->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  //    cout<<"before"<<endl;
G4double edepStep;
  // check if we are in scoring volume
  //if (volume != fScoringVolume)  edepStep = 0.;//theStep->GetTotalEnergyDeposit();;

//if(fScoringVolume){


  // collect energy deposited in this step
  edepStep = theStep->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  
//cout<<edepStep<<endl;
//cout<<"jjj"<<endl;
}

}









/*
	float edepStep = 0.;
cout<<"check"<<endl;
	//get the two points of a step
	G4StepPoint* point1 = theStep->GetPreStepPoint();
	G4StepPoint* point2 = theStep->GetPostStepPoint();
    
    	//get the particle involved in the step	
	G4ParticleDefinition* particle = theStep->GetTrack()->GetDefinition(); 

	//get the name of the volume in which the particles is at the beginning of the step
	G4TouchableHandle touch1 = point1->GetTouchableHandle();
	G4VPhysicalVolume* pre_volume = touch1->GetVolume();
    	G4String pre_volName = "" ; if ( pre_volume ) pre_volName = pre_volume -> GetName () ;

    	//get the name of the volume in which the particles is at the end of the step
   	G4TouchableHandle touch2 = point2->GetTouchableHandle();
   	G4VPhysicalVolume* post_volume = touch2->GetVolume();
    	G4String post_volName = "" ; if ( post_volume ) post_volName = post_volume -> GetName () ;

	//if ( particle -> GetParticleName() == "e-" || particle -> GetParticleName() == "mu-")
	//	{  
		/*	if ( pre_volName == "World" && post_volName == "mcp" )
			{
			float R1 = casualen (0.,1.);		//efficiency
			if (R1 > 0.5)
			CreateTree::Instance() -> Q1 -> push_back (casualen (0.,2.));		//charge
			else CreateTree::Instance() -> Q1 -> push_back(0.);
			}
	
		if ( pre_volName == "Abs" )
			{
			CreateTree::Instance() -> EnergyTotalAbs1 += theStep->GetTotalEnergyDeposit();
			}
	
		/*if ( pre_volName == "World" && post_volName == "mcp2" )
			{
			float R2 = casualen (0.,1.);
			if (R2 > 0.5)
			CreateTree::Instance() -> Q2 -> push_back (casualen (0.,2.));
			else CreateTree::Instance() -> Q2 -> push_back(0.);
			}*/
	
	/*	if ( pre_volName == "Abs2" )
			{
			CreateTree::Instance() -> EnergyTotalAbs2 += theStep->GetTotalEnergyDeposit();
			}

               		if ( pre_volName == "Calo" )
	               		{
   			        CreateTree::Instance() -> EnergyTotalCalo += theStep->GetTotalEnergyDeposit();       
			        }
	*/
	    //if ( pre_volName == "Abs"  && post_volName == "World" )         //secondaries
		//if ( pre_volName == "World"  && post_volName == "mcp2" )         //secondaries
		//	{
			//cout<<"SteppingActionStart"<<endl;
			  //  cout<<"checkVolume"<<endl;
		/*	const G4TrackVector* secondaries_tracks = theStep->GetSecondary();    //get number of all secondaries
            //G4Track* track = theStep->GetTrack();
            //G4int partID= track->GetTrackID();
            G4TrackVector::const_iterator ite;
            std::map<G4int,G4int> nElecMap;
            std::map<G4int,G4int>::const_iterator iteMap;
            std::vector<float> nElec;
            //int i =0;
            //G4int id = theStep->GetTrack()->GetVolume()->GetCopyNo(); 
              G4int id = theStep->GetTrack()->GetTrackID(); 
            //G4StepPoint* point3=theStep->GetPreStepPoint();
            //double nElec=point3->GetBeta();
          
            //ite=secondaries_tracks->begin();
         //while(ite!=secondaries_tracks->end())


         //energy deposition
	edepStep = theStep->GetTotalEnergyDeposit();

         //CreateTree::Instance() -> EnergyTotal += edepStep;//push_back( edepStep);
	 fEventAction->AddEdep(edepStep);

            
          int n=0;
         //   int i=0;
        for( ite = secondaries_tracks->begin(); ite != secondaries_tracks->end(); ite++)
            {     
           //                     i++;
                                //if( (*ite)->GetDefinition() != G4Gamma::Gamma()  )     
                            if( (*ite)->GetDefinition() == G4Electron::Electron() )//|| (*ite)->GetDefinition() != G4Gamma::Gamma() )     
                                //identify electrons among secondaries particles
                    {
                            //void theStep->GetSecondaries()->DeleteSecondaryVector();   
                            //const G4Step * aStep; 
                            //const G4TrackVector* secondaries_tracks = aStep->GetSecondary();
                            //G4Step* step = theStep->GetStep();
                            //theStep->DeleteSecondaryVector();
                            //(step)->DeleteSecondaryVector();
                            //void G4Step::theStep.DeleteSecondaryVector();
                            //for(int i = 0; i<100; i++)  
                              nElec.push_back(1.);
                                 //cout<<n<<"\t"<<nElec.size()<<"\t"<<i<<endl;
                               n++;               
                nElecMap[id]++;
                //ite++;
                 
                
                       }
                       }
                        //cout<<n<<"\t"<<nElec.size()<<"\t"<<nElecMap[id]<<"\t"<<n<<endl;
                        G4RunManager::GetRunManager()->AbortEvent(); 
                        
                      //
            //G4int molt1=nElec[id].size_type();
            //float nSeco=secondaries_tracks->size();
               // cout<<"checkSegmentation"<<endl;
              
              // if(sec_energy>0.4){
                //cout<<n<<"\t"<<nElec.size()<<endl;}
           // float nElecSeco=nElec->size();
     /*       if ( particle->GetParticleName() != "e-")
               {   
                      cout<<"nSeco-1"<<endl;
                    //nSeco==nSeco-1.;
               }         
            //G4float molt = nElec.pop_back(); 
           // if (nElec.size()>1. || nElec.size()==1.)    
            //cout<<nElecMap[id]<<endl;
//            iteMap=nElecMap.end();
            //int moltMap=iteMap->second;
           // CreateTree::Instance()->E_sec -> push_back(sec_energy);
            CreateTree::Instance()->mult->push_back(1.+n);
cout<<n<<endl;
            //CreateTree::Instance()->mult->push_back(1.+nElec.size());
            CreateTree::Instance()->E_sec->push_back(1.+nElec.size());
            //CreateTree::Instance()->E_sec->push_back(1.+*iteMap->second());
            //CreateTree::Instance()->particleID -> push_back(ite);
			//CreateTree::Instance()->molt2 = theStep -> GetSecondary();
			
        	//}
	cout<<"SteppingActionEnd"<<endl;*/	
//	}
//}
//}		
		

