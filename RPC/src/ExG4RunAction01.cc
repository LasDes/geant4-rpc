#include "ExG4RunAction01.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4RunAction01::ExG4RunAction01()
 : G4UserRunAction()

{
	  G4RunManager::GetRunManager()->SetPrintProgress(1);

	  
	  G4double c = 3.e08*m/s;
	  
	  
	  auto analysisManager = G4AnalysisManager::Instance();
         
	  analysisManager->SetVerboseLevel(1);

	  analysisManager->CreateH1("Edep","erg deposit in gas", 10000, 0, 100*keV);
          
	  analysisManager->CreateH1("stepL","steplength in gas", 10000, 0, 100*cm);

          analysisManager->CreateH1("exitKE","exit KE in gas", 10000, 0, 100*MeV);

          analysisManager->CreateH1("Pz","Momentum(z) in gas", 10000, -1000000000000000000*MeV/c, 10000000000000000000000000000000*MeV/c);
  









}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4RunAction01::~ExG4RunAction01()
{
  delete G4AnalysisManager::Instance();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4RunAction01::BeginOfRunAction(const G4Run*)

{
	 auto analysisManager = G4AnalysisManager::Instance();
         
	  G4String fileName = "project";
          
	  analysisManager->OpenFile(fileName);


}

	
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4RunAction01::EndOfRunAction(const G4Run*)

{

	auto analysisManager = G4AnalysisManager::Instance();

	{
         G4cout << " Edep : mean = "
       << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")

       << " rms = "
       << G4BestUnit(analysisManager->GetH1(0)->rms(), "Energy") << G4endl;
 
           G4cout << " stepL : mean = "
       << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length")

       << " rms = "
       << G4BestUnit(analysisManager->GetH1(1)->rms(), "Length") << G4endl;

	
	   G4cout << " exitKE : mean = "
       << G4BestUnit(analysisManager->GetH1(2)->mean(), "Energy")

       << " rms = "
       << G4BestUnit(analysisManager->GetH1(2)->rms(), "Energy") << G4endl;

	
	   G4cout << " Pz : mean = "
       << analysisManager->GetH1(3)->mean()

       << " rms = "
       << analysisManager->GetH1(3)->rms() << G4endl;

	}
         

  analysisManager->Write();
  analysisManager->CloseFile();


}













