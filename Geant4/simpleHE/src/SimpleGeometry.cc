#include "SimpleGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "SimpleDetector.hh"

using namespace CLHEP;

SimpleGeometry::SimpleGeometry(double alpha)
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{
    fAngle = alpha * degree; 

}

SimpleGeometry::~SimpleGeometry()
{ }

G4VPhysicalVolume* SimpleGeometry::Construct()
{ 
  G4bool checkOverlaps = true;

  G4Material* air = DefineMaterial("G4_AIR");



  G4double scinLength = 30*cm;
  G4double scinHeight = 2*cm;
  G4double scinWidth = 30*cm; 
  G4double dist = 30*cm;

  G4Material* water = DefineMaterial("G4_WATER");
  //     
  // World
  //
  G4double world_sizeXY =  2*m;
  G4double world_sizeZ  = 2*m;
  
  G4Box* solidWorld =    
    new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld, air, "World");
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     
                      G4ThreeVector(),       
                      logicWorld,            
                      "World",               
                      0,                     
                      false,                 
                      0,                     
                      checkOverlaps);        


  //     
  // Detector
  //  
  G4Box* sc1box = new G4Box("sc1box", scinWidth/2, scinLength/2, scinHeight/2);
  G4Box* sc2box = new G4Box("sc2box", scinWidth/2, scinLength/2, scinHeight/2);

  G4LogicalVolume* sc1lv = new G4LogicalVolume(sc1box, water, "sc1lv");
  G4LogicalVolume* sc2lv = new G4LogicalVolume(sc2box, water, "sc2lv");
 
	G4RotationMatrix* rot = new G4RotationMatrix();
	rot->rotateX(fAngle);

 
  new G4PVPlacement(rot, G4ThreeVector(0.,sin(fAngle),cos(fAngle))*dist/2,
                    sc1lv, "sc1pv", logicWorld, true,     
                    0, checkOverlaps);
  new G4PVPlacement(rot, G4ThreeVector(0.,-sin(fAngle),-cos(fAngle))*dist/2,
                    sc2lv, "sc2pv", logicWorld, true, 
                    0, checkOverlaps);

  SimpleDetector* sd1 = new SimpleDetector("sc1sd");
  SimpleDetector* sd2 = new SimpleDetector("sc2sd");
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->AddNewDetector(sd1);
  SDman->AddNewDetector(sd2);
  sc1lv->SetSensitiveDetector(sd1);
  sc2lv->SetSensitiveDetector(sd2)
;
  return physWorld;
}
G4Material* SimpleGeometry::DefineMaterial(G4String material, G4double density)
{
    G4int ncomponents,natoms;
    G4double fractionmass;
    G4NistManager* nist = G4NistManager::Instance();
    
    G4Material* mat = 0;
    
    mat = nist->FindOrBuildMaterial(material);
    if (mat != 0)
        return mat;
    
    if (material == "Steel12H18N10T")
    {
      G4Element* Fe = nist->FindOrBuildElement("Fe");
      G4Element* Ni = nist->FindOrBuildElement("Ni");
      G4Element* Cr = nist->FindOrBuildElement("Cr");
      G4Element* Mn = nist->FindOrBuildElement("Mn");
      mat = new G4Material("Steel12H18N10T", 7.92*g/cm3, ncomponents=4);
      mat->AddElement(Fe, fractionmass=68*perCent);
      mat->AddElement(Ni, fractionmass=11*perCent);
      mat->AddElement(Cr, fractionmass=19*perCent);
      mat->AddElement(Mn, fractionmass=2*perCent);
    }
    else
    {
        G4cerr << "Unknown material: " << material << G4endl;
    }
    return mat;
}


