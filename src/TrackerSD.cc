// hxchi
// 08.05.2018
// copy from B2a

#include "TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(const G4String& theSDname, const G4String& thehitsCollectionName)
: G4VSensitiveDetector(theSDname), fHitsCollection(NULL)
{
  // hitcollection's name, have to be defined
  collectionName.insert(thehitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//  build collection between hitsclooection and G4Event
//  call before G4Event start

void TrackerSD::Initialize(G4HCofThisEvent* hce)
{
  // set energy to 0
  edep = 0;
  etotalDep = 0;

  // Create hits collection
  fHitsCollection = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  // energy deposit
  edep = aStep->GetTotalEnergyDeposit();

  if(edep == 0){
    return false;
  }
  etotalDep += edep;

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  //  set hitclooection's energy

  TrackerHit* newHit = new TrackerHit();
  newHit->SetEdep(etotalDep);

  fHitsCollection->insert(newHit);

  //  newHit->Print();

  //  print some information

  if(verboseLevel>1 ){ 
    G4int nofHits = fHitsCollection->entries();
    G4cout << G4endl
           << "-------->Hits Collection: in this event they are " << nofHits 
           << " hits in the tracker chambers: " << G4endl;

    for(G4int i = 0; i < nofHits; i++){
      (*fHitsCollection)[i]->Print();
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......