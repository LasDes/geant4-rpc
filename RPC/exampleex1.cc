#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "ExG4DetectorConstruction01.hh"
#include "QGSP_BERT.hh"
#include "ExG4ActionInitialization01.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"




int main(int argc,char** argv)
{

G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
	
	
	
	
// construct the default run manager
G4RunManager* runManager = new G4RunManager;
// set mandatory initialization classes

 auto detConstruction = new ExG4DetectorConstruction01();
  runManager->SetUserInitialization(detConstruction);



runManager->SetUserInitialization(new QGSP_BERT);




auto actionInitialization = new ExG4ActionInitialization01(detConstruction);
runManager->SetUserInitialization(actionInitialization);

// Initialize visualization
//
  G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();


 // get the pointer to the UI manager and set verbosities
G4UImanager* UI = G4UImanager::GetUIpointer();
// Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UI->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }


// job termination
delete runManager;
delete visManager;

}
