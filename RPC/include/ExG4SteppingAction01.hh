/// \file ExG4SteppingAction01.hh
/// \brief Definition of the ExG4SteppingAction01 class

#ifndef ExG4SteppingAction01_h
#define ExG4SteppingAction01_h 1

#include "G4UserSteppingAction.hh"

class ExG4DetectorConstruction01;
class ExG4EventAction01;




class ExG4SteppingAction01 : public G4UserSteppingAction


{
  
public:
  ExG4SteppingAction01(const ExG4DetectorConstruction01* detectorConstruction, ExG4EventAction01* eventAction);
  virtual ~ExG4SteppingAction01();

  virtual void UserSteppingAction(const G4Step* step);

private:
  const ExG4DetectorConstruction01* fDetConstruction;
  ExG4EventAction01*  fEventAction;


};

#endif
