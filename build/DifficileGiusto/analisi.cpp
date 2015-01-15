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

TGraphErrors *g = new TGraphErrors(); 

TProfile *profilone1 = new TProfile ("profilone1","profilone1",50,0.,20);	
TProfile *profilone2 = new TProfile ("profilone2","profilone2",500,0.,100);	

TH1F *h_distr1[20];
TH1F *h_distr2[100];

float findErrors(int scorri, TH1F *h_, char parola[1])
{
	float max = h_ -> GetBinContent(scorri);
	float buffer = h_->GetXaxis()->GetBinCenter(scorri);
	if (parola == "d")
	{
	while ( h_->GetBinContent(scorri) > 0.5*max )
		++scorri;
	float right = h_->GetXaxis()->GetBinCenter(scorri);
	return fabs(buffer - right);
	}

	if (parola == "s")
	{
	while ( h_->GetBinContent(scorri) > 0.5*max )
		--scorri;
	float left = h_->GetXaxis()->GetBinCenter(scorri);
	return fabs(buffer - left);
	}
}

	
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
		for (int cariscan1 = 0; cariscan1 < 20; ++cariscan1)
		if (charge1 > cariscan1 && charge1 < cariscan1 + 1.)
		h_distr1[cariscan1] -> Fill(EnergyTotalAbs1);
		for (int cariscan2 = 0; cariscan2 < 100; ++cariscan2)
		if (charge2 > cariscan2 && charge2 < cariscan2 + 1.)
		h_distr2[cariscan2] -> Fill(EnergyTotalAbs2);
		}
		
	g->SetPoint(num, energyMax / 1000., 100. * energyPrimo -> GetRMS() / energyMax);
	g->SetPointError(num, 0., 100. * energyPrimo -> GetRMSError() / energyMax);

	name = name + ".C";
	TCanvas *c1 = new TCanvas();
	c1->cd();
	energyPrimo -> Draw();
	c1->Print(name);
}		

float pezzi(int num)
{
	gSystem->Load("libTree");

	float energyMax = 300000.;

	TH1F *h_pezzi = new TH1F("h_pezzi","h_pezzi",1000,0.,energyMax);
	TH1F *energyPrimo_pezzi = new TH1F("energyPrimo_pezzi","energyPrimo_pezzi",1000,-0.5*energyMax,0.5*energyMax);

	TString command = "ls ";
	command = command + "300*> input_pezzi.tmp"; 
	gSystem -> Exec(command); 
	
	ifstream inFile("input_pezzi.tmp");
	std::string line;

	while(getline(inFile,line))
		{
		TString nome = (TString)line;

		TFile *f = new TFile(nome,"read");
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
	
		for (int i = 0; i < t -> GetEntries(); ++i)
			{
			t->GetEntry(i);
			h_pezzi->Fill(EnergyTotalCalo);
			}
		}
	
	float mean = h_pezzi->GetMean();
	float RMS = h_pezzi->GetRMS();

	ifstream intFile("input_pezzi.tmp");
	std::string linet;

	while(getline(intFile,linet))
		{
		TString nome = (TString)linet;		

		TFile *f = new TFile(nome,"read");
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
		
		for (int j = 0; j < t -> GetEntries(); ++j)
			{
			t->GetEntry(j);
			float charge1 = 0.;
			for (int c1 = 0; c1 < Q1 -> size(); ++c1)
			charge1 += Q1 -> at (c1);
			float charge2 = 0.;
			for (int c2 = 0; c2 < Q2 -> size(); ++c2)
			charge2 += Q2 -> at (c2);
			energyPrimo_pezzi-> Fill(EnergyTotalCalo*energyMax/mean - energyMax);
			profilone1 -> Fill (charge1,EnergyTotalAbs1);
			profilone2 -> Fill (charge2,EnergyTotalAbs2);		
			for (int cariscan1 = 0; cariscan1 < 20; ++cariscan1)
			if (charge1 > cariscan1 && charge1 < cariscan1 + 1.)
			h_distr1[cariscan1] -> Fill(EnergyTotalAbs1);
			for (int cariscan2 = 0; cariscan2 < 100; ++cariscan2)
			if (charge2 > cariscan2 && charge2 < cariscan2 + 1.)
			h_distr2[cariscan2] -> Fill(EnergyTotalAbs2);
			}
		}

	g->SetPoint(num, energyMax / 1000., 100. * energyPrimo_pezzi -> GetRMS() / energyMax);
	g->SetPointError(num, 0., 100. * energyPrimo_pezzi -> GetRMSError() / energyMax);
}			

	
int main()
{
	gROOT->ProcessLine("#include <vector>");
	gStyle->SetOptFit(0001);
	
	char histoName[50];
	for (int q = 0; q < 20; ++q)
		{
		sprintf(histoName,"h_distr1_%d", &q);
		h_distr1[q] = new TH1F(histoName,histoName,1000,0.,1000.);
		}
	
	for (int q = 0; q < 100; ++q)
		{
		sprintf(histoName,"h_distr2_%d", &q);
		h_distr2[q] = new TH1F(histoName,histoName,1000,0.,10000.);
		}

	TString command = "ls ";
	command = command + "*GeV.root > input.tmp"; 
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
//	pezzi(k);

	TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
	float MPV1;
	for (int u = 0; u < 20; ++u)
		{
		float MPB1 = h_distr1[u]->GetMaximumBin ();		//MostProbableBin
		MPV1 = h_distr1[u]->GetXaxis()->GetBinCenter(MPB1);	
		g1 -> SetPoint (u,u,MPV1);
		g1 -> SetPointError (u,0.,0.,findErrors(MPB1,h_distr1[u],"s"),findErrors(MPB1,h_distr1[u],"d"));
		}	

	TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
	float MPV2;
	for (int u = 0; u < 100; ++u)
		{
		float MPB2 = h_distr2[u]->GetMaximumBin ();		//MostProbableBin
		MPV2 = h_distr2[u]->GetXaxis()->GetBinCenter(MPB2);	
		g2 -> SetPoint (u,u,MPV2);
		g2 -> SetPointError (u,0.,0.,findErrors(MPB2,h_distr2[u],"s"),findErrors(MPB2,h_distr2[u],"d"));		
		}	
	
	gStyle -> SetTitleW(0.9);  //per cent of the pad width
	gStyle -> SetTitleH(0.06); //per cent of the pad height			

	g1->SetMarkerStyle(20);
	g1->SetMarkerColor(kRed);
	g2->SetMarkerStyle(20);
	g2->SetMarkerColor(kRed);
	
	TFile *ch = new TFile("istogrammi.root","recreate");
	for (int hh = 0; hh < 20; ++hh)
	h_distr1[hh]->Write();
	for (int hh = 0; hh < 100; ++hh)
	h_distr2[hh]->Write();
	
	g1->GetYaxis()->SetTitle("Energy Deposited in First Absorber [MeV]");
	g1->GetYaxis()->SetTitleOffset(1.5);
	g1->GetYaxis()->SetLabelOffset(0.);	
	g1->GetXaxis()->SetTitle("Charge Delivered [Arbitrary Units]");
	g1->GetXaxis()->SetTitleSize(1.);
	g1->GetYaxis()->SetTitleSize(1.);	
	g1->GetXaxis()->SetRangeUser(0.,15.);
	g1->GetYaxis()->SetRangeUser(0.,60.);	
	g1->SetTitle("First mcp Calibration");
	TF1 *retta1 = new TF1("retta1","pol1",0.,20.);
	retta1 -> FixParameter(0,0.);
	g1->Fit("retta1","","",0.,10.);
	float a1 = retta1->GetParameter(0);		//intercetta
	float err_a1 = retta1->GetParError(0);
	float m1 = retta1->GetParameter(1);		//coefficiente angolare
	float err_m1 = retta1->GetParError(1);
	
	g2->GetYaxis()->SetTitle("Energy Deposited in Second Absorber [MeV]");
	g2->GetXaxis()->SetTitle("Charge Delivered [Arbitrary Units]");
	g2->GetYaxis()->SetTitleOffset(1.5);
	g2->GetYaxis()->SetLabelOffset(0.);	
	g2->GetXaxis()->SetTitleSize(1.);
	g2->GetYaxis()->SetTitleSize(1.);	
	g2->GetXaxis()->SetRangeUser(0.,120.);
	g2->GetYaxis()->SetRangeUser(0.,1500.);	
	g2->SetTitle("Second mcp Calibration");
	TF1 *retta2 = new TF1("retta2","pol1",0.,100.);
	retta2 -> FixParameter(0.,0.);
	g2->Fit("retta2","","",0.,70.);
	float a2 = retta2->GetParameter(0);		//intercetta
	float err_a2 = retta2->GetParError(0);
	float m2 = retta2->GetParameter(1);		//coefficiente angolare
	float err_m2 = retta2->GetParError(1);
		
	TCanvas *gg = new TCanvas("gg","gg",1200.,600.);
	gg -> Divide(2,0);
	gg -> cd(1);
	g1 -> Draw("AP");
	gg -> cd(2);			
	g2 -> Draw("AP");
	gg -> Print("grafici.C");		
	gg -> Print("grafici.pdf","pdf");	
	
	std::ofstream outFile("calib.txt",std::ios::out);
	outFile<<a1<<"	"<<err_a1<<endl;
	outFile<<m1<<"	"<<err_m1<<endl;	
	outFile<<a2<<"	"<<err_a2<<endl;
	outFile<<m2<<"	"<<err_m2<<endl;	
	outFile.close();

	gStyle -> SetTitleW(0.9);  //per cent of the pad width
	gStyle -> SetTitleH(0.07); //per cent of the pad height			
			
	g->GetYaxis()->SetTitle("Energy Resolution [%/#sqrt{E}]");
	g->GetXaxis()->SetTitle("Energy [GeV]");
	g->GetYaxis()->SetTitleOffset(1.2);
	g->GetXaxis()->SetTitleOffset(1.2);	
	g1->GetXaxis()->SetTitleSize(1.);
	g1->GetYaxis()->SetTitleSize(1.);	
	g->GetYaxis()->SetRangeUser(0.,10.);
	g->GetXaxis()->SetRangeUser(0.,350.);
	g->SetTitle("Resolution Worsening With No Energy Measurement"); //Due to Pre-Shower \n (no energy measurement)");
	g->SetMarkerStyle(20);
	g->SetMarkerColor(kRed);

	TF1 *iperbole = new TF1("iperbole","[0]/sqrt(x)",0.,300.);
	TCanvas *graph = new TCanvas("graph","graph",600.,600.);
	graph->cd();
	g->SetLineWidth(3);
	iperbole->SetLineWidth(5);	
	g->Draw("AP");
	g->Fit("iperbole");
	graph->Print("grafico.C");

	TCanvas *c3 = new TCanvas("c3","c3",600,600);
	c3 -> cd();
	g -> Draw("AP");
	g -> Fit("iperbole");
	c3 -> Print ("grafico.pdf","pdf");
	c3 -> Print ("grafico.root","root");

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
