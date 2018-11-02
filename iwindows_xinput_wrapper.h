#ifndef IWINDOWS_XINPUT_WRAPPER_H
#define IWINDOWS_XINPUT_WRAPPER_H

#include <QObject>
#include <qt_windows.h>
#include <XInput.h>

#include <QTimer>

/**
 * @brief DWORD
 * @param XInputGetStateEx_t
 * Function Prototype for polling
 */
typedef DWORD (__stdcall *XInputGetStateEx_t) (DWORD, XINPUT_STATE*);
typedef DWORD (__stdcall *XInputSetState_t) (DWORD, XINPUT_VIBRATION *);

enum IWindows_XInput_Enum
{
    X1_Left,
    XI_Right
};

/**
 * @brief The XboxOneButtons enum
 *      As I only have an X1 controller, I am only using enum for the X1
 */
enum XboxOneButtons
{
    X1_up = 1,
    X1_down = 2,
    X1_left = 4,
    X1_right = 8,
    X1_start = 16,
    X1_back = 32,
    X1_ltdown = 64,
    X1_rtdown = 128,
    X1_lbump = 256,
    X1_rbump = 512,
    X1_guide = 1024,

    X1_a = 4096,
    X1_b = 8192,
    X1_x = 16384,
    X1_y = 32768
};

class IWindows_XInput_Wrapper : public QObject
{
    Q_OBJECT
public:
    explicit IWindows_XInput_Wrapper(QObject *parent = 0);

signals:

    /**
     * @brief ButtonPressed
     * @param uID - UserID
     * @param PressedButtons - a list of all currently pressed buttons
     */
    void ButtonPressed(short uID, QList<XboxOneButtons> PressedButtons);
    /**
     * @brief LeftTrigger
     * @param uID - UserID
     * @param Value
     */
    void LeftTrigger(short uID, byte Value);
    /**
     * @brief RightTrigger
     * @param uID - UserID
     * @param Value
     */
    void RightTrigger(short uID, byte Value);

    void LeftThumbStick(short uID, double LX, double LY);

    void RightThumbStick(short uID, double RX, double RY);

public slots:

    /**
     * @brief Setup
     *  This loads the library once.
     *  Not runned in constructor, in case of faulty coding loading multiple xinputs
     */
    void Setup();

    /**
     * @brief Start
     *  Starts the thread of this class
     *  Also sets up what to send via signals
     *      If you want to update signals, Stop and Start again
     */
    void Start();

    /**
     * @brief Stop
     *  Stops main thread
     */
    void Stop();

    void VibrateController(short uID, WORD LeftMotorSpeed, WORD RightMotorSpeed);

private slots:

    /**
     * @brief XInput_Polling
     *  Main thread
     */
    void XInput_Polling();

    /**
     * @brief TranslateButtons
     * Determines which buttons are pressed, or if multiples are pressed
     */
    void TranslateButtons(short uID, WORD bID);

    /**
     * @brief TranslateTriggers
     * @param uID - userID
     * @param X - X param of stick
     * @param Y - Y param of stick
     * @param e - Should we translate Left or Right stick?
     */
    void TranslateTriggers(short uID, short X, short Y, IWindows_XInput_Enum e);

private:
    XInputGetStateEx_t XInputGetStateEx;
    XInputSetState_t XInputSetState;

    /**
     * @brief - Tells loop which signals to emit
     */
    bool bSendButtons;
    bool bSendLeftTrigger;
    bool bSendRightTrigger;
    bool bSendLeftThumbstick;
    bool bSendRightThumbstick;

    /**
     * @brief iTimer - Timer for polling
     */
    QTimer * iTimer;


    /**
     * @brief deadzoneX/Y
     *      Specifies thumbstick deadzones
     */
    double deadzoneX = 0.15;
    double deadzoneY = 0.15;
};

#endif // IWINDOWS_XINPUT_WRAPPER_H
