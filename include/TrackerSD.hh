// hxchi
// 08.05.2018
// copy from B2a

#ifndef TrackerSD_h
#define TrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "TrackerHit.hh"

#include <vector>

class G4Step;
class G4HCofThisEvent;  //  save multi SD hitcollection objects

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Tracker sensitive detector class
///
/// The hits are accounted in hits in ProcessHits() function which is called
/// by Geant4 kernel at each step. A hit is created with each step with non zero 
/// energy deposit.

class TrackerSD: public G4VSensitiveDetector
{
public:
  TrackerSD(const G4String& theSDname, const G4String& thehitsCollectionName);
  virtual ~TrackerSD();

  //  methods from base class
  virtual void  Initialize(G4HCofThisEvent* thehitCollection);
  virtual G4bool ProcessHits(G4Step* thestep, G4TouchableHistory* thehistory);
  virtual void   EndOfEvent(G4HCofThisEvent* thehitCollection);

private:
  G4double edep;
  G4double etotalDep;
  TrackerHitsCollection* fHitsCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif