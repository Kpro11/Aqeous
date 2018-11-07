## Requirements
We recomend using a 64 bit compiler, spesifically the MSVC 2015 one. You can get this by installing Visual Studio 2015

## Installation instructions

### QtAV 
1. Download a QtAV 1.11.0 64 bit executable installer (not 1.12.0) from http://www.qtav.org/install.html
_We have tested this with the VS2015x64 1.11.0 version_ 

2. Install it with default options (install with development tools & examples and to location C:/QtAV)

3. Go to install folder and run the sdk_deploy.bat 

4. In qtcreator, switch from "debug" to "release". This switch located in the bottom left above the run, debug and build buttons.

5. Make sure to run qmake before running project again. (QtCreator status bar -> build -> run qmake)

Alternativly check this link: https://github.com/wang-bin/QtAV/wiki/Deploy-SDK-Without-Building-QtAV or build it yourself
_The reason you have to use the release option and potential fix is discussed in pr #1 https://github.com/Kpro11/RovyMcRovFace/pull/1_

### Simulator and stream:
1. Follow internal instructions to set up propiatery simulator, located on our google drive (sorry open source gods)
2. Install Open Brodcaster Software from https://obsproject.com/ (be sure to install the 64 bit version!)
3. In obs menu bar: profile -> import: RovyMcRovFace/obs/RovSimProfile/
4. In obs menu bar: scene -> import: RovyMcRovFace/obs/RovSimScene.json

**This does only work on windows** because 1. the simulator only works on windows, and 2. the path's to the different programs are, for now, hardcoded to windows locations. 

After that you should be good to go. If not, check that obs is properly recording the fhsim window and then check that the settings are set according to this https://obsproject.com/forum/resources/obs-studio-send-an-udp-stream-to-a-second-pc-using-obs.455/
