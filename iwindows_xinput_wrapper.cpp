#include "iwindows_xinput_wrapper.h"

IWindows_XInput_Wrapper::IWindows_XInput_Wrapper(QObject *parent) : QObject(parent)
{
    // Initialize function as NULL;
    XInputGetStateEx = NULL;
    iTimer = NULL;
}

void IWindows_XInput_Wrapper::Setup()
{
    // We already have the function, so that means Setup() is being runned twice
    // Therefore we cancel the Setup() call;
    if (!XInputGetStateEx == false)
        return;

    // get xInput1_3.dll path
    char dll_path[MAX_PATH];
    GetSystemDirectoryA(dll_path, sizeof(dll_path));
    strcat_s(dll_path, "/xinput1_3.dll");

    //Load Library
    HINSTANCE xinputDll = LoadLibraryA(dll_path);

    // get function from xinput dllXInputGetStateEx_t
    XInputGetStateEx = (XInputGetStateEx_t) GetProcAddress(xinputDll, "XInputGetState");
    XInputSetState = (XInputSetState_t) GetProcAddress(xinputDll, "XInputSetState");

    // Create timer for polling
    iTimer = new QTimer(this);
    connect(iTimer, SIGNAL(timeout()), this, SLOT(XInput_Polling()));
    iTimer->setInterval(1);
}

void IWindows_XInput_Wrapper::Start()
{

    if (!XInputGetStateEx == true)
    {
        printf("Setup() was never called or has failed. Unable to start IWindows_XInput_Wrapper\n");
        return;
    }

    // If there is a slot connected to our signal, we shall emit the signal for it
    // If there is no slot connected, no reason to emit a signal;
    bSendButtons = receivers(SIGNAL(ButtonPressed(short, QList<XboxOneButtons>))) > 0 ? true : false;
    bSendLeftTrigger = receivers(SIGNAL(LeftTrigger(short , byte ))) > 0 ? true : false;
    bSendRightTrigger = receivers(SIGNAL(RightTrigger(short , byte ))) > 0 ? true : false;
    bSendLeftThumbstick = receivers(SIGNAL(LeftThumbStick(short , double , double ))) > 0 ? true : false;
    bSendRightThumbstick = receivers(SIGNAL(RightThumbStick(short , double , double ))) > 0 ? true : false;

    // Start polling
    iTimer->start();
}

void IWindows_XInput_Wrapper::Stop()
{
    if (!iTimer == true)
    {
        printf("Setup() was never called or has failed. Unable to stop IWindows_XInput_Wrapper, as it was never started nor Setup'd\n");
        return;
    }

    iTimer->stop();
}

void IWindows_XInput_Wrapper::VibrateController(short uID, WORD LeftMotorSpeed, WORD RightMotorSpeed)
{
    XINPUT_VIBRATION vibration;
    ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );

    if (LeftMotorSpeed < 0) LeftMotorSpeed = 0;
    if (LeftMotorSpeed > 65535) LeftMotorSpeed = 65535;


    if (RightMotorSpeed < 0) RightMotorSpeed = 0;
    if (RightMotorSpeed > 65535) RightMotorSpeed = 65535;

    vibration.wLeftMotorSpeed = LeftMotorSpeed; // use any value between 0-65535 here
    vibration.wRightMotorSpeed = RightMotorSpeed; // use any value between 0-65535 here

    XInputSetState( uID, &vibration );
}

void IWindows_XInput_Wrapper::XInput_Polling()
{
    XINPUT_STATE xState;

    // Iterate over all possible controllers
    for (int i = 0; i < XUSER_MAX_COUNT; i++)
    {
        // If a controller is connected, we can then get its state
        if (XInputGetStateEx(i, &xState) == ERROR_SUCCESS)
        {

            if (bSendButtons)
                TranslateButtons(i, xState.Gamepad.wButtons);
            if (bSendLeftTrigger)
                emit LeftTrigger(i, xState.Gamepad.bLeftTrigger);
            if (bSendRightTrigger)
                emit RightTrigger(i, xState.Gamepad.bRightTrigger);
            if (bSendLeftThumbstick)
                TranslateTriggers(i, xState.Gamepad.sThumbLX, xState.Gamepad.sThumbLY, X1_Left);
            if (bSendRightThumbstick)
                TranslateTriggers(i, xState.Gamepad.sThumbRX, xState.Gamepad.sThumbRY, XI_Right);
        }
    }

}
void IWindows_XInput_Wrapper::TranslateButtons(short uID, WORD bID)
{
    //wish I could iterate over enum, ah well
    QList<XboxOneButtons> bPressed;

    if ((X1_up & bID ) != 0)
        bPressed.append(X1_up);

    if ((X1_down & bID ) != 0)
        bPressed.append(X1_down);

    if ((X1_left & bID ) != 0)
        bPressed.append(X1_left);

    if ((X1_right & bID ) != 0)
        bPressed.append(X1_right);

    if ((X1_start & bID ) != 0)
        bPressed.append(X1_start);

    if ((X1_back & bID ) != 0)
        bPressed.append(X1_back);

    if ((X1_ltdown & bID ) != 0)
        bPressed.append(X1_ltdown);

    if ((X1_rtdown & bID ) != 0)
        bPressed.append(X1_rtdown);

    if ((X1_rbump & bID ) != 0)
        bPressed.append(X1_rbump);

    if ((X1_lbump & bID ) != 0)
        bPressed.append(X1_lbump);

    if ((X1_guide & bID ) != 0)
        bPressed.append(X1_guide);

    if ((X1_a & bID ) != 0)
        bPressed.append(X1_a);

    if ((X1_b & bID ) != 0)
        bPressed.append(X1_b);

    if ((X1_x & bID ) != 0)
        bPressed.append(X1_x);

    if ((X1_y & bID ) != 0)
        bPressed.append(X1_y);

    emit ButtonPressed(uID, bPressed);

}

void IWindows_XInput_Wrapper::TranslateTriggers(short uID, short X, short Y, IWindows_XInput_Enum e)
{
    // Normalize values between -1.0 and 1.0
    double normX = fmax(-1.0, (double) X / 32767.0);
    double normY = fmax(-1.0, (double) Y / 32767.0);

    // Factoring in deadzone
    double StickX = (abs(normX) < deadzoneX ? 0 : normX);
    double StickY = (abs(normY) < deadzoneY ? 0 : normY);

    // Send signal to corrent thumbstick
    /// TODO: can potentially simplify this to one function
    if (e == X1_Left)
        emit LeftThumbStick(uID, StickX, StickY);
    if (e == XI_Right)
        emit RightThumbStick(uID, StickX, StickY);
}
