# Installation instructions

My current code is tested on [Gameplay](https://github.com/blackberry/GamePlay) v2.0

1. Create New Project:
  * Project Name: BillardOnline3D
  * Title: Billard Online 3D
  * Description: A multiplatform billard game online
  * Unique ID: es.jaumesingla.billardonline
  * Author: Jaume Singla Valls
  * Class name: BillardMainClass
  * Path: /Users/dracks/Documents/Programacio/Jocs/ (this is my path)
2. Import all the code of this repository (Usually I clone the repository, copy the .git folder, and restore the status of git, to ensure I don't forgot any file)


### Preparing Xcode
  * Add files.. in src group
  * select all folders inside src folder : don't copy,  add group for new folders
  * Build and run!

### Preparing qde (BB-PlayBook or BBOS10)
  * Import ...
  * existing project into workspace 
  * Select the Gameplay folder
  * Only needs the Gameplay project. (only import Gameplay)
  * Build gameplay
  * Import ...
  * Existing project into workspace
  * Select BillardOnline3D Folder
  * Import Billard only.
  * Open Billard project Properties
  * Select C/C++ Generals->Paths and symbols
  * Select all configurations and GNU C option
  * Add all the folders inside src, including Game/ModeGames
  * Build and run!


  