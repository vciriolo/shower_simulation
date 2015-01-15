//c++ -o merger merger.cpp `root-config --cflags --glibs` 

#include "TROOT.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TString.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TProfile.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TStyle.h"
#include "TPaveStats.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


int main()
{
	TChain *ch = new TChain("tree");
	ch -> SetDirectory(0);

	TString command = "ls ";
	command = command + "300* > input.tmp"; 
	gSystem -> Exec(command); 
	
	ifstream inFile("input.tmp");
	std::string line;

	while(getline(inFile,line))
		{
		TString nomeFile = (TString)line;
		cout<<nomeFile<<endl;
		ch -> Add(nomeFile);		
		}

	ch -> Merge("totale.root");
}
