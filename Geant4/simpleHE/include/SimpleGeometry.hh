#ifndef SimpleGeometry_h
#define SimpleGeometry_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;

class SimpleGeometry : public G4VUserDetectorConstruction
{
  public:
  SimpleGeometry(G4double, G4double, G4double);
  virtual ~SimpleGeometry();
  
  virtual G4VPhysicalVolume* Construct();
  
  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
  
  G4Material* DefineMaterial(G4String material);
  
protected:
  G4LogicalVolume*  fScoringVolume;
private:
  G4double fAngle;
  G4double scinLength;
  G4double scinHeight;
  G4double scinWidth; 
  G4double dist;
  G4double world_sizeX;
  G4double world_sizeY;
  G4double world_sizeZ;
  
  
};

#endif

