// ROOT macro file for plotting histograms 
// 
// Can be run from ROOT session:
// root[0] .x plotHisto.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
  TFile f("project.root");

  // Create a canvas and divide it into 1x1 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 1000);
  c1->Divide(2,2);
  
  // Draw  histogram in the pads
  c1->cd(1);
  TH1D* hist1 = (TH1D*)f.Get("Edep");
  hist1->Draw("HIST");
  

  c1->cd(2);
  TH1D* hist2 = (TH1D*)f.Get("stepL");
  hist2->Draw("HIST");



  c1->cd(3);
  TH1D* hist3 = (TH1D*)f.Get("exitKE");
  hist3->Draw("HIST");



  c1->cd(4);
  TH1D* hist4 = (TH1D*)f.Get("Pz");
  hist4->Draw("HIST");



 }  
