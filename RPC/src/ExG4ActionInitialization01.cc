#include "ExG4ActionInitialization01.hh"
#include "ExG4PrimaryGeneratorAction01.hh"
#include "ExG4RunAction01.hh"
#include "ExG4EventAction01.hh"
#include "ExG4SteppingAction01.hh"

#include "ExG4DetectorConstruction01.hh"


////////////////////////////////////


ExG4ActionInitialization01::ExG4ActionInitialization01(ExG4DetectorConstruction01* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//////////////////////////////////////


ExG4ActionInitialization01::~ExG4ActionInitialization01()
{}

/////////////////////////////////////

void ExG4ActionInitialization01::Build() const
{
 SetUserAction(new ExG4PrimaryGeneratorAction01);

 SetUserAction(new ExG4RunAction01);

 auto eventAction = new ExG4EventAction01;
 
 SetUserAction(eventAction);
 
 SetUserAction(new ExG4SteppingAction01(fDetConstruction,eventAction));


}
