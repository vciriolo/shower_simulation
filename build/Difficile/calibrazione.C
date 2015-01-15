{
//=========Macro generated from canvas: c1_n11/c1_n11
//=========  (Thu Jul 17 12:18:10 2014) by ROOT version5.34/09
   TCanvas *c1_n11 = new TCanvas("c1_n11", "c1_n11",0,0,700,500);
   c1_n11->SetHighLightColor(2);
   c1_n11->Range(0,0,1,1);
   c1_n11->SetFillColor(0);
   c1_n11->SetBorderMode(0);
   c1_n11->SetBorderSize(2);
   c1_n11->SetFrameBorderMode(0);
   
   TGraphErrors *gre = new TGraphErrors(4);
   gre->SetName("");
   gre->SetTitle("Pre-Shower Energy Calibration");
   gre->SetFillColor(1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetPoint(0,0,0.9974794);
   gre->SetPointError(0,0,0);
   gre->SetPoint(1,0,1.360099);
   gre->SetPointError(1,0,0);
   gre->SetPoint(2,0,2.069921);
   gre->SetPointError(2,0,0);
   gre->SetPoint(3,0,1.844333);
   gre->SetPointError(3,0,0);
   
   TH1F *Graph_Graph2 = new TH1F("Graph_Graph2","Pre-Shower Energy Calibration",100,0,1.1);
   Graph_Graph2->SetMinimum(0.8902352);
   Graph_Graph2->SetMaximum(2.177166);
   Graph_Graph2->SetDirectory(0);
   Graph_Graph2->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph2->SetLineColor(ci);
   Graph_Graph2->GetXaxis()->SetTitle("Energy Deposited in Pre-Shower [GeV]");
   Graph_Graph2->GetXaxis()->SetLabelFont(42);
   Graph_Graph2->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetXaxis()->SetTitleFont(42);
   Graph_Graph2->GetYaxis()->SetTitle("Total Generated Charge [arbitrary units]");
   Graph_Graph2->GetYaxis()->SetLabelFont(42);
   Graph_Graph2->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetYaxis()->SetTitleFont(42);
   Graph_Graph2->GetZaxis()->SetLabelFont(42);
   Graph_Graph2->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph2->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph2);
   
   gre->Draw("ap");
   c1_n11->Modified();
   c1_n11->cd();
   c1_n11->SetSelected(c1_n11);
}
