// hxchi
// 08.05.2018
// copy from zh

#ifndef RootIO_H
#define RootIO_H 1

#include <globals.hh>

#include <fstream>
#include <map>

class TFile;
class TH1D;
class TTree;

G4String GetFileName(G4int beamErg, const G4String &);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RootIO
{
public:
  RootIO(G4int saveFlag);
  ~RootIO();

  void Open(G4int beamErg);
  void Close();
  void FillHist(G4double theerg);
  void RecordEnergy(G4double erg);

private:
  G4int fsave;
  std::ofstream fErgFile;

  TFile* fRootFile;
  TH1D* fHist;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
