#ifndef GAMEPADSTATE_H
#define GAMEPADSTATE_H

#include <QObject>

#include <cinttypes>

class GamepadState : public QObject
{
    Q_OBJECT

public:

    // Joystick Definition
    struct JoyStick {
        double xAxis = 0;
        double yAxis = 0;
        bool pressed=false;
    };

    GamepadState();
    void updateButtonPress(const uint32_t & btn);

    // Player Buttons
    bool m_pad_a = false;
    bool m_pad_b = false;
    bool m_pad_x = false;
    bool m_pad_y = false;

    // Shoulder Buttons
    bool m_rShoulder = false;
    bool m_lShoulder = false;

    // Trigger Buttons
    double m_rTrigger = 0;
    double m_lTrigger = 0;

    // Directional Buttons
    bool m_pad_up = false;
    bool m_pad_down = false;
    bool m_pad_left = false;
    bool m_pad_right = false;

    // Meta Buttons
    bool m_pad_start = false;
    bool m_pad_back = false;

    // Joysticks
    JoyStick m_lThumb;
    JoyStick m_rThumb;

};

#endif // GAMEPADSTATE_H
