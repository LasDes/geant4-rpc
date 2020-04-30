#ifndef ExG4RunAction01_h
#define ExG4RunAction01_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"


class G4Run;


class ExG4RunAction01 : public G4UserRunAction
{
  public:
    ExG4RunAction01();
    virtual ~ ExG4RunAction01();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
};


#endif

