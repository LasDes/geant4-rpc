#ifndef ExG4EventAction01_h
#define ExG4EventAction01_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


class  ExG4EventAction01 : public G4UserEventAction
{
  public:
    ExG4EventAction01();
    virtual ~ ExG4EventAction01();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void Pass(G4double de, G4double dl, G4double dK, G4double dP);
  
  
  private:
    G4double  fEnergy, fstepl, fKE, fPz;
};

inline void ExG4EventAction01::Pass(G4double de, G4double dl, G4double dK, G4double dP) {
  fEnergy = de; fstepl = dl; fKE = dK; fPz = dP;}

#endif
