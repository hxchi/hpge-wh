// hxchi
// 07.05.2018
// copy from B2a

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  // other methods
  G4LogicalVolume* GetCrystal();
  G4LogicalVolume* GetBDeadLayer();
  G4LogicalVolume* GetLiDeadLayer();
  G4LogicalVolume* GetDoubleAlShell();
  G4LogicalVolume* GetBeWindow();
  G4LogicalVolume* GetPlasticHat();

private:
  void DefineMaterials();
  G4VPhysicalVolume* DefineVolumes();

  G4Material* matAir;
  G4Material* matGe;
  G4Material* matAl;
  G4Material* matBe;
  G4Material* matB;
  G4Material* matLi;
  G4Material* matMylar;
  G4Material* matPlastic;
};

#endif