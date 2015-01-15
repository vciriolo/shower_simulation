//c++ -o analisi analisi.cpp `root-config --cflags --glibs` 

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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

TGraphErrors *g = new TGraphErrors(); 
TGraphErrors *gCalib = new TGraphErrors(); 
TCanvas cmap[5];

float semplice(TString name, int num)
{
	gSystem->Load("libTree");

	TGraphErrors *g1 = new TGraphErrors(); 
	TGraphErrors *g2 = new TGraphErrors(); 
	
	TFile *f = new TFile(name,"read");
	TTree *t = (TTree*) f -> Get("tree");

	t->SetDirectory(0);

	float EnergyTotalCalo;
	float EnergyTotalAbs1;
	float EnergyTotalAbs2;
	float Q1;
	float Q2;
	
	t->SetBranchAddress("EnergyTotalCalo",&EnergyTotalCalo);
	t->SetBranchAddress("EnergyTotalAbs1",&EnergyTotalAbs1);
	t->SetBranchAddress("EnergyTotalAbs2",&EnergyTotalAbs2);		
	t->SetBranchAddress("Q1",&Q1);
	t->SetBranchAddress("Q2",&Q2);			

	Ssiz_t s = name.Sizeof();
	name.Remove(s-9,s);
	float energyMax = atof(name);
	energyMax = energyMax * 1000.;

	TH1F *h = new TH1F("h","h",1000,0.,energyMax);
	TH1F *energyPrimo = new TH1F("energyPrimo","energyPrimo",1000,-0.5*energyMax,0.5*energyMax);

	for (int i = 0; i < t -> GetEntries(); ++i)
		{
		t->GetEntry(i);
		h->Fill(EnergyTotalCalo);
		}

	float mean = h->GetMean();
	float RMS = h->GetRMS();

	for (int j = 0; j < t -> GetEntries(); ++j)
		{
		t->GetEntry(j);
		energyPrimo-> Fill(EnergyTotalCalo*energyMax/mean - energyMax);
		g1->SetPoint(i, Q1, EnergyTotalAbs1);
		g2->SetPoint(i, Q2, EnergyTotalAbs2);			
		}

	g->SetPoint(num, energyMax / 1000., 100. * energyPrimo -> GetRMS() / energyMax);
	g->SetPointError(num, 0., 100. * energyPrimo -> GetRMSError() / energyMax);

	gCalib->SetPoint(num, habs->GetMean(), Q1 + Q2);	

	char cmapName[20];
	sprintf (cmapName,"canvas%d.C",num);
	TString mapName = TString(cmapName);
	cmap[num].Divide(2,0);
	cmap[num].cd(1);
	g1->Draw();
	cmap[num].cd(2);
	g2->Draw();
	cmap[num].Print(mapName);

	name = name + ".C";
	TCanvas *c1 = new TCanvas();
	c1->cd();
	energyPrimo -> Draw();
	c1->Print(name);
}		
	
int main()
{
	gROOT->ProcessLine("#include <vector>");
		
	TString command = "ls ";
	command = command + "*.root > input.tmp"; 
	gSystem -> Exec(command); 
	
	ifstream inFile("input.tmp");
	std::string line;
	
	int k = 0;
	
	while(getline(inFile,line))
		{
		TString nomeFile = (TString)line;
		semplice(nomeFile,k);		
		++k;
		}

	g->GetYaxis()->SetTitle("Energy Resolution [%]");
	g->GetXaxis()->SetTitle("Energy [GeV]");
	g->SetTitle("Resolution Worsen Due to Pre-Shower (no energy measurement)");
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kRed);

	gCalib->GetYaxis()->SetTitle("Total Generated Charge [arbitrary units]");
	gCalib->GetXaxis()->SetTitle("Energy Deposited in Pre-Shower [GeV]");
	gCalib->SetTitle("Pre-Shower Energy Calibration");
	gCalib->SetMarkerStyle(20);
	gCalib->SetMarkerColor(kRed);
		
	TCanvas *graph = new TCanvas();
	graph->cd();
	g->Draw("AP"),
	graph->Print("grafico.C");

	TCanvas *calibrazione = new TCanvas();
	calibrazione->cd();
	gCalib->Draw("AP"),
	calibrazione->Print("calibrazione.C");

}		
