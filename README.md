Insert things here

## Install instructions

Install QtAV from http://www.qtav.org/install.html
Make sure you have the same Qt major&minor version as QtAV release packages and same same compiler(mingw or vc)
Alternativly check this link: https://github.com/wang-bin/QtAV/wiki/Deploy-SDK-Without-Building-QtAV or build it yourself

Simulator and stream:
1. Follow internal instructions to set up propiatery simulator (sorry open source gods)
2. Install Open Brodcaster Software from https://obsproject.com/ (be sure to install the 64 bit version!)
3. In obs menu bar: profile -> import:./obs/RovSimProfile/
4. In obs menu bar: scene -> import:./obs/RovSimScene.json
5. you should be good to go. If not, check that obs is properly recording the fhsim window and then check that the settings are set according to this https://obsproject.com/forum/resources/obs-studio-send-an-udp-stream-to-a-second-pc-using-obs.455/
