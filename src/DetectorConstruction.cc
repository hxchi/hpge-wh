// hxchi
// 07.05.2018
// copy from B2a

#include "DetectorConstruction.hh"
#include "TrackerSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4Tubs.hh"
#include "G4Hype.hh"
#include "G4Trd.hh"
#include "G4Orb.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"


namespace{
  const G4double worldsizeX = 25 * cm;
  const G4double worldsizeY = 25 * cm;
  const G4double worldsizeZ  = 25 * cm;
  const G4double cryDia  = 56.1 * mm;
  const G4double cryLen  = 67.6 * mm;
  const G4double cryTorRad  = 8 * mm;
  const G4double holeDia  = 10.3 * mm;
  const G4double holeDep  = 61 * mm;
  const G4double holeOrbRad  = 5 * mm;
  const G4double LideadTh  = 0.7 * mm;
  const G4double BdeadTh  = 0.3 / 1000 * mm;
  const G4double Al_Mylar  = 0.03 * mm;
  const G4double AlShieK  = 0.8 * mm;
  const G4double AlShieL  = 1 * mm;
  const G4double space4  = 4 * mm;
  const G4double space3  = 3 * mm;
  const G4double cupLen  = 105 * mm;
  const G4double DiaK  = cryDia + 3 * mm;
  const G4double DiaL  = cryDia + 10 * mm;
  const G4double TopBeTh  = 0.5 * mm;
  const G4double TopAlTh  = 1.5 * mm;
}


// public methods
DetectorConstruction::DetectorConstruction()
: matAir(NULL),
  matGe(NULL),
  matAl(NULL),
  matBe(NULL),
  matB(NULL),
  matLi(NULL),
  matMylar(NULL)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  G4NistManager* nist = G4NistManager::Instance();
  matAir = nist->FindOrBuildMaterial("G4_AIR");
  matGe = nist->FindOrBuildMaterial("G4_Ge");
  matAl = nist->FindOrBuildMaterial("G4_Al");
  matBe = nist->FindOrBuildMaterial("G4_Be");
  matB = nist->FindOrBuildMaterial("G4_B");
  matLi = nist->FindOrBuildMaterial("G4_Li");
  matMylar = nist->FindOrBuildMaterial("G4_Mylar");

  // G4Element* elN  = new G4Element("Nitrogen", symbol = "N", z = 7., a = 14.01*g/mole);
  // G4Element* elH  = new G4Element("Hydrogen", symbol = "H"  z = 1., a = 1.01*g/mole);
  // matPlastic = new G4Material("plastic", density = 1.19*g/cm3, ncomponents = 2);
  // matPlastic->AddElement(elC, fractionmass = 0.8562844);
  // matPlastic->AddElement(elH, fractionmass = 0.1437155);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4LogicalVolume* DetectorConstruction::GetCrystal()
{
  G4cout<<" --->: GetCrystal, begin" << G4endl;

  G4LogicalVolume* fCrystal = NULL;

  G4Tubs* solidCrystalTub = 
    new G4Tubs("CrystalTub",
        0,
        cryDia / 2,
        cryLen / 2,
        0,
        360 * degree);

  G4Tubs* solidCrystalHole = 
    new G4Tubs("CrystalHole",
        0,
        holeDia / 2,
        holeDep / 2,
        0,
        360 * degree);
  
  G4ThreeVector zTransHole(0, 0, (holeDep - cryLen) / 2);

  G4SubtractionSolid* solidCrystal = 
    new G4SubtractionSolid("Crystal",
        solidCrystalTub,
        solidCrystalHole,
        0,  // rad
        zTransHole);  // tran

  fCrystal = new G4LogicalVolume(solidCrystal,
                 matGe,
                 "fCrystal");

  //  color
  G4VisAttributes  *pVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.3));
                    pVisAtt->SetForceSolid(true);
                    fCrystal->SetVisAttributes(pVisAtt);

  return fCrystal;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetBDeadLayer()
{
  G4cout<<" --->: GetBDeadLayer, begin" << G4endl;

  G4LogicalVolume* fBDeadLayer = NULL;

  G4Tubs* solidBDeadLayer = 
    new G4Tubs("BDeadLayer",
        cryDia / 2,
        cryDia / 2 + BdeadTh,
        cryLen / 2,
        0,
        360 * degree);


  fBDeadLayer = new G4LogicalVolume(solidBDeadLayer,
                    matB,
                    "fBDeadLayer");

  //  color
  G4VisAttributes *pVisAtt = new G4VisAttributes(G4Colour(0.86, 0.86, 0.86, 0.4)); 
                   pVisAtt->SetForceSolid(true);
                   fBDeadLayer->SetVisAttributes( pVisAtt );

  return fBDeadLayer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLiDeadLayer()
{
  G4cout<<" --->: GetLiDeadLayer, begin" << G4endl;

  G4LogicalVolume* fLiDeadLayer = NULL;

  G4Tubs* solidLiDeadLayer = 
    new G4Tubs("LiDeadLayer",
        holeDia / 2 - LideadTh,
        holeDia / 2,
        holeDep / 2,
        0,
        360 * degree);

  fLiDeadLayer = new G4LogicalVolume(solidLiDeadLayer,
                     matLi,
                     "fLiDeadLayer");

  //  color
  G4VisAttributes *pVisAtt = new G4VisAttributes( G4Colour(0.86, 0.86, 0.86) ); 
                   pVisAtt->SetForceSolid(true);
                   fLiDeadLayer->SetVisAttributes( pVisAtt );

  return fLiDeadLayer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetDoubleAlShell()
{
  G4cout<<" --->: GetDoubleAlShell, begin" << G4endl;

  G4LogicalVolume* fDoubleAlShell = NULL;

  G4Tubs* solidInsideAlShell = 
    new G4Tubs("InsideAlShell",
        DiaK / 2 - AlShieK,
        DiaK / 2,
        cupLen / 2,
        0,
        360 * degree);

  G4Tubs* solidOutsideAlShell = 
    new G4Tubs("OutsideAlShell",
        DiaL / 2 - AlShieL,
        DiaL / 2,
        cupLen / 2,
        0,
        360 * degree);

  G4Tubs* solidTopAlHat = 
    new G4Tubs("solidTopAlHat",
        DiaL / 2 - space4,
        DiaL / 2,
        AlShieL / 2,
        0,
        360 * degree);

  G4ThreeVector zTransTopAlHat(0, 0, cupLen / 2);

  G4UnionSolid* solidOutsideAl =
    new G4UnionSolid("OutsideAl",
        solidOutsideAlShell,
        solidTopAlHat,
        0,
        zTransTopAlHat);

  G4ThreeVector zTransOutsideAlShell(0, 0, space4);

  G4UnionSolid* solidDoubleAlShell =
    new G4UnionSolid("DoubleAlShell",
        solidInsideAlShell,
        solidOutsideAl,
        0,
        zTransOutsideAlShell);


  fDoubleAlShell = new G4LogicalVolume(solidDoubleAlShell,
                       matAl,
                       "fDoubleAlShell");

  //  color
  G4VisAttributes *pVisAtt = new G4VisAttributes( G4Colour(0.4, 0.81, 0.67, 0.2) ); 
                   pVisAtt->SetForceSolid(true);
                   fDoubleAlShell->SetVisAttributes( pVisAtt );

  return fDoubleAlShell;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetBeWindow()
{
  G4cout<<" --->: GetBeWindow, begin" << G4endl;

  G4LogicalVolume* fBeWindow = NULL;

  G4Tubs* solidBeWindow = 
    new G4Tubs("BeWindow",
        0,
        DiaK / 2,
        TopBeTh / 2,
        0,
        360 * degree);

  fBeWindow = new G4LogicalVolume(solidBeWindow,
                  matBe,
                  "fBeWindow");

  //  color
  G4VisAttributes *pVisAtt = new G4VisAttributes( G4Colour(1.0, 0.0, 0.0, 0.1) ); 
                   pVisAtt->SetForceSolid(true);
                   fBeWindow->SetVisAttributes( pVisAtt );

  return fBeWindow;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetPlasticHat()
{
  G4cout << " --->: GetPlasticHat, begin" << G4endl;

  G4LogicalVolume* fPlasticHat = NULL;

  return fPlasticHat;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  G4cout<<" --->: Construct, begin" << G4endl;

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = false;

  //  define world

  G4Box* solidWorld =
    new G4Box("World",
        0.5 * worldsizeX,
        0.5 * worldsizeY,
        0.5 * worldsizeZ);

  G4LogicalVolume* logicWorld = 
    new G4LogicalVolume(solidWorld,
        matAir,
        "World");

  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,
        G4ThreeVector(),
        logicWorld,
        "World",
        0,
        false,
        0,
        checkOverlaps);

  // logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

  //  Crystal

  G4ThreeVector positionCrystal = G4ThreeVector(0, 0, 0);

  G4LogicalVolume* fCrystal = GetCrystal();
  new G4PVPlacement(0, //  no no rotation
      positionCrystal,     //  at (x,y,z)
      fCrystal,            //  its logical volume
      "Crystal",           //  its name
      logicWorld,          //  its mother volume
      false,               //  no boolean operations
      0,                   //  copy number
      checkOverlaps);      //  checking overlaps

  //  BDeadLayer

  G4ThreeVector positionBDeadLayer = G4ThreeVector(0, 0, 0);

  G4LogicalVolume* fBDeadLayer = GetBDeadLayer();
  new G4PVPlacement(0,
      positionBDeadLayer,
      fBDeadLayer,
      "BDeadLayer",
      logicWorld,
      false,
      0,
      checkOverlaps);

  //  LiDeadLayer

  G4ThreeVector positionLiDeadLayer = G4ThreeVector(0, 0, (holeDep - cryLen) / 2);

  G4LogicalVolume* fLiDeadLayer = GetLiDeadLayer();
  new G4PVPlacement(0,
      positionLiDeadLayer,
      fLiDeadLayer,
      "LiDeadLayer",
      logicWorld,
      false,
      0,
      checkOverlaps);

  //  DoubleAlShell

  G4ThreeVector positionDoubleAlShell = G4ThreeVector(0, 0, (cryLen- cupLen) / 2);

  G4LogicalVolume* fDoubleAlShell = GetDoubleAlShell();
  new G4PVPlacement(0,
      positionDoubleAlShell,
      fDoubleAlShell,
      "DoubleAlShell",
      logicWorld,
      false,
      0,
      checkOverlaps);

  //  BeWindow

  G4ThreeVector positionBeWindow = G4ThreeVector(0, 0, cryLen / 2 + space4);

  G4LogicalVolume* fBeWindow = GetBeWindow();
  new G4PVPlacement(0,
      positionBeWindow,
      fBeWindow,
      "BeWindow",
      logicWorld,
      false,
      0,
      checkOverlaps);
  
  //  PlasticHat

  // G4ThreeVector positionPlasticHat = G4ThreeVector(0, 0, 0);
  // G4LogicalVolume* fPlasticHat = GetPlasticHat();
  // new G4PVPlacement(0,
  //            positionPlasticHat,
  //            fPlasticHat,
  //            "PlasticHat",
  //            logicWorld,
  //            false,
  //            0,
  //            checkOverlaps);

  //------------------------------------------------
  // Sensitive detectors
  //------------------------------------------------

  G4String HPGeSDname = "HPGeSD";
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  TrackerSD* SDHPGe= new TrackerSD(HPGeSDname, "SDHPGe"); 
  fCrystal->SetSensitiveDetector(SDHPGe);
  SDman->AddNewDetector(SDHPGe);


  return physWorld;
}

