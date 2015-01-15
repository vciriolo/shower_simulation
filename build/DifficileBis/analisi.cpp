//c++ -o analisi analisi.cpp `root-config --cflags --glibs` 

//Il programma trova una relazione lineare tra l'energia depositata in un assorbitore e la carica generata nell'mcp ad esso successivo.
//I risultati così ottenuti sono salvati nel file calib.txt
//E' inoltre stimata la perdita di risoluzione dovuta alla presenza dell'apparato (pre-shower), nell'ipotesi che esso non sia in grado di misurare 
//l'energia depositata. I risultati si trovano in grafico.C

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

TGraphErrors *g = new TGraphErrors(); 

TProfile *profilone1 = new TProfile ("profilone1","profilone1",50,0.,20);	
TProfile *profilone2 = new TProfile ("profilone2","profilone2",500,0.,100);	
	
float semplice(TString name, int num)
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
		float charge1 = 0.;
		for (int c1 = 0; c1 < Q1 -> size(); ++c1)
		charge1 += Q1 -> at (c1);
		float charge2 = 0.;
		for (int c2 = 0; c2 < Q2 -> size(); ++c2)
		charge2 += Q2 -> at (c2);
		energyPrimo-> Fill(EnergyTotalCalo*energyMax/mean - energyMax);
		profilone1 -> Fill (charge1,EnergyTotalAbs1);
		profilone2 -> Fill (charge2,EnergyTotalAbs2);		
		}

	g->SetPoint(num, energyMax / 1000., 100. * energyPrimo -> GetRMS() / energyMax);
	g->SetPointError(num, 0., 100. * energyPrimo -> GetRMSError() / energyMax);

	name = name + ".C";
	TCanvas *c1 = new TCanvas();
	c1->cd();
	energyPrimo -> Draw();
	c1->Print(name);
}		
	
int main()
{
	gROOT->ProcessLine("#include <vector>");
	gStyle->SetOptFit(1111);
	
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
	
	profilone1->GetYaxis()->SetTitle("Energy Deposited in First Absorber [MeV]");
	profilone1->GetYaxis()->SetTitleOffset(1.5);
	profilone1->GetYaxis()->SetLabelOffset(0.);	
	profilone1->GetXaxis()->SetTitle("Charge Delivered [Arbitrary Units]");
	profilone1->SetTitle("First mcp Calibration");
	TF1 *retta1 = new TF1("retta1","pol1",0.,20.);
	profilone1->Fit("retta1","","",0.,10.);
	float a1 = retta1->GetParameter(0);		//intercetta
	float err_a1 = retta1->GetParError(0);
	float m1 = retta1->GetParameter(1);		//coefficiente angolare
	float err_m1 = retta1->GetParError(1);
	
	profilone2->GetYaxis()->SetTitle("Energy Deposited in Second Absorber [MeV]");
	profilone2->GetXaxis()->SetTitle("Charge Delivered [Arbitrary Units]");
	profilone2->GetYaxis()->SetTitleOffset(1.5);
	profilone2->GetYaxis()->SetLabelOffset(0.);	
	profilone2->SetTitle("Second mcp Calibration");
	TF1 *retta2 = new TF1("retta2","pol1",0.,100.);
	profilone2->Fit("retta2","","",0.,70.);
	float a2 = retta2->GetParameter(0);		//intercetta
	float err_a2 = retta2->GetParError(0);
	float m2 = retta2->GetParameter(1);		//coefficiente angolare
	float err_m2 = retta2->GetParError(1);
		
	std::ofstream outFile("calib.txt",std::ios::out);
	outFile<<a1<<"	"<<err_a1<<endl;
	outFile<<m1<<"	"<<err_m1<<endl;	
	outFile<<a2<<"	"<<err_a2<<endl;
	outFile<<m2<<"	"<<err_m2<<endl;	
	outFile.close();
			
	g->GetYaxis()->SetTitle("Energy Resolution [%]");
	g->GetXaxis()->SetTitle("Energy [GeV]");
	g->SetTitle("Resolution Worsen Due to Pre-Shower (no energy measurement)");
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kRed);

	TF1 *iperbole = new TF1("iperbole","[0]/sqrt(x)",0.,300.);
	TCanvas *graph = new TCanvas();
	graph->cd();
	g->Draw("AP");
	g->Fit("iperbole");
	graph->Print("grafico.C");

	TCanvas *profili = new TCanvas();
	profili -> Divide (2,0);
	profili -> cd(1);
	profilone1 -> Draw();
	profili->Update();
	TPaveStats *box1 = (TPaveStats*) (profilone1->GetListOfFunctions())->FindObject("stats");
	if ( box1 )
		{
   		box1->SetY1NDC(0.65);
   		box1->SetY2NDC(0.85);
   		box1->SetX1NDC(0.15);
   		box1->SetX2NDC(0.35);
   		}
	profili -> cd(2);
	profilone2 -> Draw();
	profili->Update();
	TPaveStats *box2 = (TPaveStats*) (profilone2->GetListOfFunctions())->FindObject("stats");
	if ( box2 )
		{
   		box2->SetY1NDC(0.65);
   		box2->SetY2NDC(0.85);
   		box2->SetX1NDC(0.15);
   		box2->SetX2NDC(0.35);
   		}
	profili -> Print ("profilato.C");
}		
