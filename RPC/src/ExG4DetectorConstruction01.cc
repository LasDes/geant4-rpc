//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "ExG4DetectorConstruction01.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4Box.hh"

#include "G4AutoDelete.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SubtractionSolid.hh"

#include "G4FieldManager.hh"

#include "G4TransportationManager.hh"

#include "G4ChordFinder.hh"

#include "G4MagIntegratorStepper.hh"
 
#include "G4Colour.hh"
#include "G4VisAttributes.hh"



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::ExG4DetectorConstruction01()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{}


// mendatory construction class

G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  
  
  //
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

   
  

  //     
  // World
  //
  G4double world_sizeXY = 140*cm;

  G4double world_sizeZ  = 10*cm;
  
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps
 

  //     
  // readout strips 1
  //  

  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4ThreeVector pos1 = G4ThreeVector(0*cm, 0*cm, -6.3*mm);



  G4Box* solidShape1 =
    new G4Box("Shape1",
    20*cm, 20*cm, 0.4*mm);

  G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicWorld,               //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  G4VisAttributes* Shape1VisAtt= new G4VisAttributes(G4Colour(1,1,1));

  logicShape1     ->SetVisAttributes(Shape1VisAtt);


  //
  // insulator layer
  //

  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_MYLAR");
  G4ThreeVector pos2a = G4ThreeVector(0*cm, 0*cm, 5.5*mm),
                pos2b = G4ThreeVector(0*cm, 0*cm, -5.5*mm);


  G4Box* solidShape2 =
    new G4Box("Shape2",
    20*cm, 20*cm, 0.4*mm);

  G4LogicalVolume* logicShape2 =
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos2a,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  new G4PVPlacement(0,                       //no rotation
                    pos2b,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  

  G4VisAttributes* Shape2VisAtt= new G4VisAttributes(G4Colour(0,0.8,0.5));

  logicShape2     ->SetVisAttributes(Shape2VisAtt);



  //
  //voltage plates
  //
  G4Material* shape3_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4ThreeVector pos3a = G4ThreeVector(0*cm, 0*cm, 4.7*mm),
                pos3b = G4ThreeVector(0*cm, 0*cm, -4.7*mm);



  G4Box* solidShape3 =
    new G4Box("Shape3",
    20*cm, 20*cm, 0.4*mm);

  G4LogicalVolume* logicShape3 =
    new G4LogicalVolume(solidShape3,         //its solid
                        shape3_mat,          //its material
                        "Shape3");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos3a,                    //at position
                    logicShape3,             //its logical volume
                    "Shape3",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  new G4PVPlacement(0,                       //no rotation
                    pos3b,                    //at position
                    logicShape3,             //its logical volume
                    "Shape3",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  


 G4VisAttributes* Shape3VisAtt= new G4VisAttributes(G4Colour(0,0,1.0));

  logicShape3     ->SetVisAttributes(Shape3VisAtt);




  //
  //electrodes
  //
  G4Material* shape4_mat = nist->FindOrBuildMaterial("G4_BAKELITE");
  G4ThreeVector pos4a = G4ThreeVector(0*cm, 0*cm, -2.9*mm), pos4b = G4ThreeVector(0*cm, 0*cm, 2.9*mm);



  G4Box* solidShape4 =
    new G4Box("Shape4",
    20*cm, 20*cm, 1.4*mm);

  logicShape4 =
    new G4LogicalVolume(solidShape4,         //its solid
                        shape4_mat,          //its material
                        "Shape4");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos4a,                   //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  elecPV =
  new G4PVPlacement(0,                       //no rotation
                    pos4b,                   //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


    G4VisAttributes* Shape4VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0));

  logicShape4     ->SetVisAttributes(Shape4VisAtt);
  

  //
  //spacer
  //
G4Material* shape5_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4ThreeVector pos5 = G4ThreeVector(0*cm, 0*cm, 0*cm);



  G4Box* box1 =
new G4Box("box1",20*cm, 20*cm, 1.5*mm);
G4Box* box2 =
new G4Box("box2", 19.5*cm, 19.5*cm, 1.5*mm );
G4SubtractionSolid* solidShape5 =
new G4SubtractionSolid("box1-box2", box1, box2);


  G4LogicalVolume* logicShape5 =
    new G4LogicalVolume(solidShape5,         //its solid
                        shape5_mat,          //its material
                        "box1-box2");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos5,                    //at position
                    logicShape5,             //its logical volume
                    "box1-box2",                //its name
                    logicWorld,                //its mother  volume
                    true,                    //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  
  G4VisAttributes* Shape5VisAtt= new G4VisAttributes(G4Colour(1.0,0,1.0));

  logicShape5     ->SetVisAttributes(Shape5VisAtt);


  
  //
  //RPC gas mix
  //

 G4int ncomponents, natoms; G4double density, fractionmass; G4String sf6, rpcgas;
 
 G4Element* S = nist->FindOrBuildElement("S");
 
 G4Element* F = nist->FindOrBuildElement("F");
 
 G4Material* SF6 = new G4Material("sf6",density = 0.006164*g/cm3, ncomponents=2);
 
 SF6->AddElement(S, natoms=1);
 
 SF6->AddElement(F, natoms=6);

 
 G4Material* Butane = nist->FindOrBuildMaterial("G4_BUTANE");

 
 G4Material* Freon = nist->FindOrBuildMaterial("G4_FREON-13B1");

 
 G4Material* ActiveMaterial = new G4Material("rpcgas",density= 0.00418*g/cm3,
 ncomponents=3);
 
 ActiveMaterial->AddMaterial(Freon, fractionmass=95.15*perCent);
 
 ActiveMaterial->AddMaterial(Butane, fractionmass=4.51*perCent);
 
 ActiveMaterial->AddMaterial(SF6, fractionmass=0.34*perCent);





  //
  //gas
  //
   G4Material* shape6_mat = ActiveMaterial;
   G4ThreeVector pos6 = G4ThreeVector(0*cm, 0*cm, 0*cm);



  G4Box* solidShape6 =
    new G4Box("Shape6",
    19.5*cm, 19.5*cm, 1.5*mm );

   logicShape6 =
    new G4LogicalVolume(solidShape6,         //its solid
                        shape6_mat,          //its material
                        "Shape6");           //its name

   
   gasPV=
   new G4PVPlacement(0,                       //no rotation
                    pos6,                    //at position
                    logicShape6,             //its logical volume
                    "Shape6",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  G4VisAttributes* Shape6VisAtt= new G4VisAttributes(G4Colour(0,0.5,1));

  logicShape6     ->SetVisAttributes(Shape6VisAtt);


   
  //                 
  //readout plates2
  //  
   G4Material* shape7_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4ThreeVector pos7a = G4ThreeVector(0*cm, -3.5*cm, 6.3*mm),
                pos7b = G4ThreeVector(0*cm, -10.5*cm, 6.3*mm),
                pos7c = G4ThreeVector(0*cm, -17.5*cm, 6.3*mm),
                pos7d = G4ThreeVector(0*cm, 3.5*cm, 6.3*mm),
                pos7e = G4ThreeVector(0*cm, 10.5*cm, 6.3*mm),
                pos7f = G4ThreeVector(0*cm, 17.5*cm, 6.3*mm);

                    		 

  G4Box* solidShape7 =
    new G4Box("Shape7",
    20*cm, 2.5*cm, 1.5*mm);

  G4LogicalVolume* logicShape7 =
    new G4LogicalVolume(solidShape7,         //its solid
                        shape7_mat,          //its material
                        "Shape7");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos7a,                   //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

   new G4PVPlacement(0,                       //no rotation
                    pos7b,                   //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


   new G4PVPlacement(0,                       //no rotation
                    pos7c,                   //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

   new G4PVPlacement(0,                       //no rotation
                    pos7d,                   //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking



   new G4PVPlacement(0,                       //no rotation
                    pos7e,                   //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking




   new G4PVPlacement(0,                       //no rotation
                    pos7f,                   //at position
                    logicShape7,             //its logical volume
                    "Shape7",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  logicShape7     ->SetVisAttributes(Shape1VisAtt);



  //
  //always return the physical World
  //
  return physWorld;
}



void ExG4DetectorConstruction01::ConstructSDandField()


{
// Create global electric field

fEMfield = new G4UniformElectricField(
G4ThreeVector(0.0,0,1600*kilovolt/cm));


// Create an equation of motion for this field
fEquation = new G4EqMagElectricField(fEMfield);
G4int nvar = 8;


// Create the Runge-Kutta 'stepper' using the efficient 'DoPri5' method
fStepper = new G4DormandPrince745( fEquation, nvar );


// Get the global field manager
fFieldMgr= G4TransportationManager::GetTransportationManager()->
GetFieldManager();


// Set this field to the global field manager
fFieldMgr->SetDetectorField( fEMfield );
fMinStep = 0.010*mm ; // minimal step of 10 microns
// The driver will ensure that integration is control to give
//acceptable integration error


fIntgrDriver = new G4MagInt_Driver(fMinStep,
fStepper,
fStepper->GetNumberOfVariables());

fChordFinder = new G4ChordFinder(fIntgrDriver);

fFieldMgr->SetChordFinder(fChordFinder);


G4bool allLocal = true;
logicShape6->SetFieldManager(fFieldMgr, allLocal);

logicShape4->SetFieldManager(fFieldMgr, allLocal);

}














//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
