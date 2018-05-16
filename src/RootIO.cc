// hxchi
// 08.05.2018
// copy from zh

#include "RootIO.hh"

#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::RootIO(G4int saveFlag)
: fsave(saveFlag),
  fRootFile(NULL),
  fErgFile(0)
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RootIO::~RootIO()
{
  if(fRootFile ){
    delete fRootFile;
    fRootFile = NULL;
  }    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Open(G4int beamErg)
{
  if(fsave){
    G4String strRO = GetFileName(beamErg, ".root");
    fRootFile = new TFile(strRO, "RECREATE");

    //  check fRootFile
    if(!fRootFile){
      G4cout << " RootIO::book :" 
             << " problem creating the ROOT TFile!!!"
             << G4endl;
      
      return ;
    }

    //  creat histogram
    fHist = new TH1D("fHist", "", 6000, 0, 3000);

    G4String strErg = GetFileName(beamErg, ".rec");
    fErgFile.open(strErg.c_str());

    //  check fErgFile
    //  ...
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::FillHist(G4double theerg)
{
  fHist->Fill(theerg);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::RecordEnergy(G4double erg){
  if(fErgFile){
    fErgFile << erg << G4endl;
  }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RootIO::Close()
{
  if(!fRootFile){
    return;
  }

  fRootFile->Write();
  fRootFile->Close();
  // fHists.clear();

  if(!fErgFile){
    return;
  }
  fErgFile.close();

  G4cout << "\n----> RootIO is saved. \n" << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//  no member function

G4String GetFileName(G4int beamErg, const G4String &fileType)
{
  std::stringstream strm;
  // strm << "./data/" << beamErg;
  strm << beamErg;
  G4String str = strm.str() + fileType;

  G4cout << "filename is " << str << G4endl;
  return str;
}