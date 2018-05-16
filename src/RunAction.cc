// hxchi
// 08.05.2018
// copy from B2a

#include "RunAction.hh"
#include "RootIO.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleGun.hh"
#include "unistd.h"
#include <fstream>
#include <string>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(RootIO* therootIO, PrimaryGeneratorAction* thefPriGen)
: G4UserRunAction(),
  fRootIO(therootIO),
  fPriGen(thefPriGen)
{ 
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(1000);

  fTimer = new G4Timer;     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  delete fTimer;
  fTimer = NULL;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* frun)
{ 
  //inform the runManager to save random number seed

  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  //  creat RootIO file

  G4cout << "---" << G4endl;
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  G4double beamErg = fPriGen->GetParticleGun()->GetParticleEnergy();
  fRootIO->Open(1000 * beamErg);

  int fRunID = frun->GetRunID();
  fTimer->Start();
  G4cout << "======================   RunID = " 
         << fRunID << "  ======================" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* frun)
{
  fRootIO->Close();

  fTimer->Stop();
  G4cout << "number of event = " 
         << frun->GetNumberOfEvent() << G4endl;

  G4cout << " time:  " << *fTimer << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
