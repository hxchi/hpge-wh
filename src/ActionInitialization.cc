// hxchi
// 08.05.2018
// copy from B2a

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "RootIO.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(G4int thesaveFlag)
: G4VUserActionInitialization(),
  saveFlag(thesaveFlag)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  PrimaryGeneratorAction* fPriGen = new PrimaryGeneratorAction();
  RootIO* fRootIO = new RootIO(saveFlag);

  SetUserAction(new RunAction(fRootIO, fPriGen));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* fPriGen = new PrimaryGeneratorAction();
  RootIO* fRootIO = new RootIO(saveFlag);

  SetUserAction(fPriGen);
  SetUserAction(new RunAction(fRootIO, fPriGen));
  SetUserAction(new EventAction(fRootIO));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
