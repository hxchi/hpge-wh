// hxchi
// 08.05.2018
// copy from B2a


#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"

class RootIO;
class TFile;

// Event action class

class EventAction: public G4UserEventAction
{
public:
  EventAction(RootIO* thefRootIO);
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* );
  virtual void    EndOfEventAction(const G4Event* );

private:
  G4double erg;

  RootIO* fRootIO;

  TFile* fFile;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif