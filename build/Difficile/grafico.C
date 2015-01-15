{
//=========Macro generated from canvas: c1_n10/c1_n10
//=========  (Thu Jul 17 12:18:10 2014) by ROOT version5.34/09
   TCanvas *c1_n10 = new TCanvas("c1_n10", "c1_n10",0,0,700,500);
   c1_n10->SetHighLightColor(2);
   c1_n10->Range(0,0,1,1);
   c1_n10->SetFillColor(0);
   c1_n10->SetBorderMode(0);
   c1_n10->SetBorderSize(2);
   c1_n10->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(4);
   gre->SetName("");
   gre->SetTitle("Resolution Worsen Due to Pre-Shower (no energy measurement)");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,100000,1.034343);
   gre->SetPointError(0,0,0.005971784);
   gre->SetPoint(1,10000,3.828508);
   gre->SetPointError(1,0,0.0221039);
   gre->SetPoint(2,30000,2.102518);
   gre->SetPointError(2,0,0.01213889);
   gre->SetPoint(3,3000,7.369492);
   gre->SetPointError(3,0,0.04254778);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Resolution Worsen Due to Pre-Shower (no energy measurement)",100,0,109700);
   Graph_Graph1->SetMinimum(0.3900048);
   Graph_Graph1->SetMaximum(8.050407);
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
   
   gre->Draw("ap");
   c1_n10->Modified();
   c1_n10->cd();
   c1_n10->SetSelected(c1_n10);
}
