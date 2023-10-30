# sp1000g-test-minimal
 
The aim of this project is to demonstrate the usage of SP1000G series logic analyzers and pattern generators API. Only 64bit system is supported.

More info about the API can be found here: https://www.ikalogic.com/kb/ihwapi/logic-analyzer-api-guide/

# Installation
First, please download and install ScanaStudio for your platform. While ScanaStudio is not needed, this will ensure drivers are isntalled in windows, and correct UDEV rules are set for UNIX. 

## Windows
Compile against the sp1000g_api library in `dependencies/win` folder.
important: sp1000g library needs to dynamicaly load the FTD3XX library, so the file `FTD3XX.DLL` need to be copied next to your executable.

## Linux
Compile against the sp1000g_api library in `dependencies/linux` folder.
important: sp1000g library needs to dynamicaly load the FTD3XX library, so the file `libftd3xx.so` need to be copied next to your executable.

## Mac
Compile against the sp1000g_api library in `dependencies/mac` folder.
important: sp1000g library needs to dynamicaly load the FTD3XX library, so the file `libftd3xx.dylib` need to be copied next to your executable.
