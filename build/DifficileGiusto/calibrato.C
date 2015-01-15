{
//=========Macro generated from canvas: c1/c1
//=========  (Sun Nov 23 14:41:20 2014) by ROOT version5.34/09
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,600,600);
   gStyle->SetOptFit(1);
   c1->SetHighLightColor(2);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(5);
   gre->SetName("");
   gre->SetTitle("Resolution Worsening With Energy Measurement");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#009900");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,100,0.2814079);
   gre->SetPointError(0,0,0.00190576);
   gre->SetPoint(1,10,1.021103);
   gre->SetPointError(1,0,0.007510956);
   gre->SetPoint(2,300,0.1762725);
   gre->SetPointError(2,0,0.001181203);
   gre->SetPoint(3,30,0.540145);
   gre->SetPointError(3,0,0.003750283);
   gre->SetPoint(4,3,2.011698);
   gre->SetPointError(4,0,0.01671547);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Resolution Worsening With Energy Measurement",100,0,329.7);
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

   ci = TColor::GetColor("#009900");
   iperbole->SetLineColor(ci);
   iperbole->SetLineWidth(5);
   iperbole->SetChisquare(454.9531);
   iperbole->SetNDF(4);
   iperbole->GetXaxis()->SetLabelFont(42);
   iperbole->GetXaxis()->SetLabelSize(0.035);
   iperbole->GetXaxis()->SetTitleSize(0.035);
   iperbole->GetXaxis()->SetTitleFont(42);
   iperbole->GetYaxis()->SetLabelFont(42);
   iperbole->GetYaxis()->SetLabelSize(0.035);
   iperbole->GetYaxis()->SetTitleSize(0.035);
   iperbole->GetYaxis()->SetTitleFont(42);
   iperbole->SetParameter(0,3.047762);
   iperbole->SetParError(0,0.009769217);
   iperbole->SetParLimits(0,0,0);
   gre->GetListOfFunctions()->Add(iperbole);
   gre->Draw("ap");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
