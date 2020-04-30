//////////////////////////////////
// ExG4PrimaryGeneratorAction01.hh
//////////////////////////////////
#ifndef ExG4PrimaryGeneratorAction01_h
#define ExG4PrimaryGeneratorAction01_h 1
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

class G4ParticleGun;
class G4Event;
class ExG4PrimaryGeneratorAction01 : public G4VUserPrimaryGeneratorAction
{
public:
ExG4PrimaryGeneratorAction01(
const G4String& particleName = "mu-",
G4double energy = 1*GeV,
G4ThreeVector position= G4ThreeVector(0,0,-3*cm),
G4ThreeVector momentumDirection = G4ThreeVector(0,0,1));
~ExG4PrimaryGeneratorAction01();
// methods
virtual void GeneratePrimaries(G4Event*);
private:
// data members
G4ParticleGun* fParticleGun; //pointer a to G4 service class
};
#endif
