{
//=========Macro generated from canvas: graph/graph
//=========  (Sat Nov 22 21:40:17 2014) by ROOT version5.34/09
   TCanvas *graph = new TCanvas("graph", "graph",0,0,600,600);
   gStyle->SetOptFit(1);
   graph->SetHighLightColor(2);
   graph->Range(0,0,1,1);
   graph->SetFillColor(0);
   graph->SetBorderMode(0);
   graph->SetBorderSize(2);
   graph->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(5);
   gre->SetName("");
   gre->SetTitle("Resolution Worsening With No Energy Measurement");
   gre->SetFillColor(1);
   gre->SetLineWidth(3);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,100,1.198658);
   gre->SetPointError(0,0,0.006920457);
   gre->SetPoint(1,10,4.40174);
   gre->SetPointError(1,0,0.02541346);
   gre->SetPoint(2,300,0.6896928);
   gre->SetPointError(2,0,0.003981943);
   gre->SetPoint(3,30,2.39065);
   gre->SetPointError(3,0,0.01380242);
   gre->SetPoint(4,3,8.778701);
   gre->SetPointError(4,0,0.05068386);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Resolution Worsening With No Energy Measurement",100,0,329.7);
   Graph_Graph1->SetMinimum(0);
   Graph_Graph1->SetMaximum(10);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1->SetLineColor(ci);
   Graph_Graph1->GetXaxis()->SetTitle("Energy [GeV]");
   Graph_Graph1->GetXaxis()->SetRange(1,101);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleOffset(1.2);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetTitle("Energy Resolution [%/#sqrt{E}]");
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleOffset(1.2);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);
   
   
   TF1 *iperbole = new TF1("iperbole","[0]/sqrt(x)",0,332.997);
   iperbole->SetFillColor(19);
   iperbole->SetFillStyle(0);
   iperbole->SetLineColor(2);
   iperbole->SetLineWidth(5);
   iperbole->SetChisquare(1211.355);
   iperbole->SetNDF(4);
   iperbole->GetXaxis()->SetLabelFont(42);
   iperbole->GetXaxis()->SetLabelSize(0.035);
   iperbole->GetXaxis()->SetTitleSize(0.035);
   iperbole->GetXaxis()->SetTitleFont(42);
   iperbole->GetYaxis()->SetLabelFont(42);
   iperbole->GetYaxis()->SetLabelSize(0.035);
   iperbole->GetYaxis()->SetTitleSize(0.035);
   iperbole->GetYaxis()->SetTitleFont(42);
   iperbole->SetParameter(0,13.0134);
   iperbole->SetParError(0,0.03373694);
   iperbole->SetParLimits(0,0,0);
   gre->GetListOfFunctions()->Add(iperbole);
   gre->Draw("ap");
   graph->Modified();
   graph->cd();
   graph->SetSelected(graph);
}
