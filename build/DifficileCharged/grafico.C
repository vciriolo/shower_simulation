{
//=========Macro generated from canvas: c1_n6/c1_n6
//=========  (Wed Sep  3 09:51:44 2014) by ROOT version5.34/09
   TCanvas *c1_n6 = new TCanvas("c1_n6", "c1_n6",0,0,700,500);
   gStyle->SetOptFit(1);
   c1_n6->SetHighLightColor(2);
   c1_n6->Range(0,0,1,1);
   c1_n6->SetFillColor(0);
   c1_n6->SetBorderMode(0);
   c1_n6->SetBorderSize(2);
   c1_n6->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(5);
   gre->SetName("");
   gre->SetTitle("Resolution Worsen Due to Pre-Shower (no energy measurement)");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,100,1.500474);
   gre->SetPointError(0,0,0.008662989);
   gre->SetPoint(1,10,5.433887);
   gre->SetPointError(1,0,0.03137256);
   gre->SetPoint(2,30,2.959326);
   gre->SetPointError(2,0,0.01708568);
   gre->SetPoint(3,3,10.51597);
   gre->SetPointError(3,0,0.06071399);
   gre->SetPoint(4,300,0.7917757);
   gre->SetPointError(4,0,0.004571319);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Resolution Worsen Due to Pre-Shower (no energy measurement)",100,0,329.7);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(11.55563);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("Energy [GeV]");
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Energy Resolution [%]");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);
   
   
   TF1 *iperbole = new TF1("iperbole","[0]/sqrt(x)",0,329.7);
   iperbole->SetFillColor(19);
   iperbole->SetFillStyle(0);
   iperbole->SetLineColor(2);
   iperbole->SetLineWidth(2);
   iperbole->SetChisquare(1517.165);
   iperbole->SetNDF(4);
   iperbole->GetXaxis()->SetLabelFont(42);
   iperbole->GetXaxis()->SetLabelSize(0.035);
   iperbole->GetXaxis()->SetTitleSize(0.035);
   iperbole->GetXaxis()->SetTitleFont(42);
   iperbole->GetYaxis()->SetLabelFont(42);
   iperbole->GetYaxis()->SetLabelSize(0.035);
   iperbole->GetYaxis()->SetTitleSize(0.035);
   iperbole->GetYaxis()->SetTitleFont(42);
   iperbole->SetParameter(0,15.74464);
   iperbole->SetParError(0,0.04085966);
   iperbole->SetParLimits(0,0,0);
   gre->GetListOfFunctions()->Add(iperbole);
   gre->Draw("ap");
   c1_n6->Modified();
   c1_n6->cd();
   c1_n6->SetSelected(c1_n6);
}
