//c++ -o risoluzione risoluzione.cpp `root-config --cflags --glibs` 

//Il programma recupera la calibrazione in energia salvata in calib.txt per ricostruire l'energia delle particelle entranti come somma dell'energia misurata nel calorimetro ed energia misurata nel pre-shower (data la carica generata). In questo modo si ottiene una stima della risoluzione dello sciamatore.

#include "TROOT.h"
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
#include "TStyle.h"
#include "TPaveStats.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

std::vector<float> parametri;
std::vector<float> errori;

TGraphErrors *g = new TGraphErrors();

float conversione(float carica1, float carica2, std::vector<float> vettore)
{
return vettore.at(0) + vettore.at(2) + carica1*vettore.at(1) + carica2*vettore.at(3);
}

float dispersione( TString name , int aa)
{
	gSystem->Load("libTree");

	TFile *f = new TFile(name,"read");
	TTree *t = (TTree*) f -> Get("tree");

	t->SetDirectory(0);

	float EnergyTotalCalo;
	float EnergyTotalAbs1;
	float EnergyTotalAbs2;
	std::vector<float> *Q1 = 0;
	std::vector<float> *Q2 = 0;
	
	t->SetBranchAddress("EnergyTotalCalo",&EnergyTotalCalo);
	t->SetBranchAddress("EnergyTotalAbs1",&EnergyTotalAbs1);
	t->SetBranchAddress("EnergyTotalAbs2",&EnergyTotalAbs2);		
	t->SetBranchAddress("Q1",&Q1);
	t->SetBranchAddress("Q2",&Q2);			

	Ssiz_t s = name.Sizeof();
	name.Remove(s-9,s);
	float energyMax = atof(name);
	energyMax = energyMax * 1000.;

	TH1F *h = new TH1F("h","h",1000,- 0.5 * energyMax, 0.5 * energyMax);
	TH1F *h1 = new TH1F("h1","h1",1000, 0., energyMax);
		
	for (int j = 0; j < t -> GetEntries(); ++j)
		{
		t->GetEntry(j);
		float charge1 = 0.;
		for (int c1 = 0; c1 < Q1 -> size(); ++c1)
		charge1 += Q1 -> at (c1);
		float charge2 = 0.;
		for (int c2 = 0; c2 < Q2 -> size(); ++c2)
		charge2 += Q2 -> at (c2);
		if (charge1 != 0 && charge2 != 0)
			{
			float Esh = conversione(charge1,charge2,parametri);
			h1 -> Fill (Esh);
			h -> Fill ( energyMax - EnergyTotalCalo - Esh );
			}
		}		
	
	TCanvas *p1 = new TCanvas();
	p1 -> cd();
	h1 -> Draw();
	p1 -> Print ("prova.C");
		
	float mean = h -> GetMean();
	float RMS = h -> GetRMS();
	
	g -> SetPoint ( aa, energyMax / 1000., 100. * RMS / energyMax );
	g -> SetPointError ( aa, 0., 100. * h -> GetRMSError() / energyMax ); 
	
}

int main()
{
	gROOT->ProcessLine("#include <vector>");
	gStyle->SetOptFit(1111);
		
	std::ifstream inFile;
	inFile.open("calib.txt",std::ios::in);
	
	int i = 0;
	while (!inFile.eof())		//a1, err_a1, m1, err_m1, a2, err_a2, m2, err_m2
		{
		float num;
		inFile >> num;
		parametri.push_back(num);
		inFile >> num;
		errori.push_back(num);
		++i;
		}
		
	TString command = "ls ";
	command = command + "*.root > input.tmp"; 
	gSystem -> Exec(command); 
	
	ifstream inputFile("input.tmp");
	std::string line;
	
	int k = 0;

	while(getline(inputFile,line))
		{
		TString nomeFile = (TString)line;
		dispersione(nomeFile,k);		
		++k;
		}
	
	g->GetYaxis()->SetTitle("Energy Resolution [%]");
	g->GetXaxis()->SetTitle("Energy [GeV]");
	g->SetTitle("Resolution Worsen Due to Pre-Shower (with energy measurement)");
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kRed);
	
	TF1 *iperbole = new TF1("iperbole","[0]/sqrt(x)",0.,300.);
	TCanvas *c1 = new TCanvas();
	c1 -> cd();
	g -> Draw("AP");
	g->Fit("iperbole");
	c1 -> Print ("calibrato.C");
}		
