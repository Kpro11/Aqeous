# Aqeous
_This project is a part of the course TDT4290 customer driven project in the autumn of 2018._

Check out our promo video:
[![Promo video](https://i.imgur.com/QeHmBUT.jpg)](https://www.youtube.com/watch?v=6YARfOoRswI)

## Requirements
We recommend using a 64 bit compiler, specifically MSVC 2015. You can get this by installing Visual Studio 2015 from https://visualstudio.microsoft.com/vs/older-downloads/

We also recommend using Qt version 5.11.2 or higher, and Qt Creator version 4.7.1 or higher. Both can be downloaded from https://www.qt.io/download

## Installation instructions

### QtAV 
1. Download a QtAV version 1.11.0 64 bit executable installer (not the 1.12.0 version) from http://www.qtav.org/install.html
_We have tested this with the VS2015x64 1.11.0 version, which we recommend_

2. Install it with default options, i.e. with "Development Tools and Examples" and to the C:/QtAV location

3. Go to the install folder and run the sdk_deploy.bat file

4. In Qt Creator, switch from "Debug" to "Release". This switch located in the bottom left, above the run, debug and build buttons

5. Make sure to run qmake before running the project again. It can be found in the Qt Creator status bar at the top, under "Build", and then "Run qmake"

Alternativly check this link: https://github.com/wang-bin/QtAV/wiki/Deploy-SDK-Without-Building-QtAV or build it yourself
_The reason the release option has to be used, and a potential fix is discussed in pr #1 https://github.com/Kpro11/Aqeous/pull/1_

### Simulator and stream:
1. Follow internal instructions to set up the propiatery simulator that belongs to SINTEF
2. Install Open Brodcaster Software (OBS) from https://obsproject.com/, make sure to install the 64 bit version
3. In the OBS menu bar, go to "Profile" and then "Import". Pick the Aqeous/obs/RovSimProfile/ folder
4. In the OBS menu bar, go to "Profile" and then select "RovSimProfile"
5. In the OBS menu bar, go to "Scene Collection" and then "Import". Pick the Aqeous/obs/RovSimScene.json file
6. In the OBS menu bar, go to "Scene Collection" and then select RovSimScene

**This does only work on windows** as the simulator only works on windows, and the paths to the different programs are, for now, hardcoded to windows locations

After that you should be good to go. If not, check that OBS is properly recording the fhsim window and then check that the settings are set in accordance with this link:
https://obsproject.com/forum/resources/obs-studio-send-an-udp-stream-to-a-second-pc-using-obs.455/


[![Promo video](https://i.imgur.com/Y7KXcFS.jpg)](https://www.youtube.com/watch?v=6YARfOoRswI)
