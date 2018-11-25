#ifndef CONSTANTVALUES_H
#define CONSTANTVALUES_H


class constantValues {
public:
    //Related to tcprov
    static constexpr double depthAdjustment = 0.005;
    static constexpr double headingAdjustment = 0.00125;
    static constexpr double maxThrusterHorizontal = 400;
    static constexpr double maxThrusterVertical = 200;
    static constexpr double maxThrusterHeading = 80; //FIND RIGHT VALUE

    //Related to gamepadserver
    // Gamepad update period
    static const int UPDATE_PERIOD_MS = 15;
    static constexpr double deadzoneX = 0.15;
    static constexpr double deadzoneY = 0.15;
    static const int maxJoystickValue = 32767;
    static const int maxTriggerValue = 255;

};
#endif // CONSTANTVALUES_H

