/// \file ExG4EventAction01.cc
/// \brief Implementation of the B4aEventAction class

#include "ExG4EventAction01.hh"
#include "ExG4RunAction01.hh"
#include "g4root.hh"


#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"


ExG4EventAction01::ExG4EventAction01()
 : G4UserEventAction()
{}

//.............//............//................//...............//


ExG4EventAction01::~ExG4EventAction01()
{}


//.............//............//................//...............//



void ExG4EventAction01::BeginOfEventAction(const G4Event*)
{}

//.............//............//................//...............//


void ExG4EventAction01::EndOfEventAction(const G4Event* event)

{
// get analysis manager
auto analysisManager = G4AnalysisManager::Instance();


// fill histograms
analysisManager->FillH1(0, fEnergy);
analysisManager->FillH1(1, fstepl);
analysisManager->FillH1(2, fKE);
analysisManager->FillH1(3, fPz);


//
// Print per event (modulo n)
//
  auto eventID = event->GetEventID();
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) ) 
  { G4cout << "---> End of event: " << eventID << G4endl;}


}












