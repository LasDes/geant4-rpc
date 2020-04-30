/// \file B4aSteppingAction.cc
/// \brief Implementation of the B4aSteppingAction class

#include "ExG4SteppingAction01.hh"
#include "ExG4EventAction01.hh"
#include "ExG4DetectorConstruction01.hh"
#include "G4StepPoint.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4SteppingAction01::ExG4SteppingAction01(
                      const ExG4DetectorConstruction01* detectorConstruction,
                      ExG4EventAction01* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)	

{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4SteppingAction01::~ExG4SteppingAction01()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void ExG4SteppingAction01::UserSteppingAction(const G4Step* step)

{
 
 
	   
  auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  
  if (volume == fDetConstruction->gasPV)
  
  { G4double edep = step->GetDeltaEnergy();

  G4double Slen = step->GetStepLength(); 
 
  G4StepPoint* thePostPoint = step->GetPostStepPoint();


  G4double exitKe = thePostPoint->GetKineticEnergy();

  G4double Pz = thePostPoint->GetMomentum().z();
 

  fEventAction-> Pass(edep, Slen, exitKe, Pz);	  
   
  } 

}
