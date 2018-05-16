// hxchi
// 08.05.2018
// copy from B2a

#include "EventAction.hh"
#include "TrackerHit.hh"
#include "RootIO.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4DCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(RootIO* thefRootIO)
: G4UserEventAction(),
  fRootIO(thefRootIO)
{
  fFile = new TFile("result.root", "recreate");
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{
  fFile->Write();
  fFile->Close();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  erg = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event)
{
  // get number of stored trajectories

  G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing

  G4int eventID = event->GetEventID();
  if ( eventID < 100 || eventID % 100 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
    if ( trajectoryContainer ) {
      G4cout << "    " << n_trajectories
             << " trajectories stored in this event." << G4endl;
    }
    G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
    G4cout << "    "  
           << hc->GetSize() << " hits stored in this event" << G4endl;

    TrackerHitsCollection *fHC = (TrackerHitsCollection*)event->GetHCofThisEvent()->GetHC(0);
    G4cout << "    "  
           << (*fHC)[0]->GetEdep() << " kev energy stored in this event" << G4endl;
  }

  //  fill RootIO
  TrackerHitsCollection *fHC = (TrackerHitsCollection*)event->GetHCofThisEvent()->GetHC(0);
  erg = (*fHC)[0]->GetEdep();
  if(erg > 0){
    erg = G4RandGauss::shoot(erg, erg * 0.01);

    fRootIO->FillHist(1000*erg);
    fRootIO->RecordEnergy(1000*erg);
  }
  
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......