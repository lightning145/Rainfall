#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"

enum CameraType{
    FIRST_PERSON,
    FREE
};

class Camera
{
private:
    Vector camPos;

    Vector camRight;
    Vector camUp;
    Vector camForward;

    CameraType camType;

    float  currPitch;
public:
    Camera(CameraType type, Vector pos, Vector right, Vector up, Vector forward) :
        camPos(pos), camRight(right), camUp(up), camForward(forward), camType(type), currPitch(0.0f) {};

    void SetPos(Vector pos) { camPos = pos; };
    Vector GetPos() { return camPos; };

    void SetRight(Vector right) { camRight = right; };
    Vector GetRight() { return camRight; };

    void SetUp(Vector up) { camUp = up; };
    Vector GetUp() { return camUp; };

    void SetForward(Vector forward) { camForward = forward; };
    Vector GetForward() { return camForward; };

    void Move(float front, float right, float up)
    {
        camPos += camForward * front;
        camPos += camRight * right;
        camPos += camUp * up;
    }

    void Rotate(float pitch, float yaw, float roll)
    {
        if (camType == FIRST_PERSON)
        {
            if (currPitch + pitch > 89.0f)
            {
                pitch = 89.0f - currPitch;
            }
            else if (currPitch + pitch < -89.0f)
            {
                pitch = -89.0f - currPitch;
            }
            currPitch += pitch;
        }

        Quaternion qPitch = AxisAngle(ToRad(pitch), camRight);
        Quaternion qYaw = AxisAngle(ToRad(yaw), VEC3(0.0f, 1.0f, 0.0f)); // yaw around world-up
        Quaternion qRoll = AxisAngle(ToRad(roll), camForward);

        Quaternion rot = qPitch * qYaw * qRoll; // qPitch * qYaw applies yaw then pitch
        rot = Normalize(rot);

        camRight = camRight * rot;
        camUp = camUp * rot;
        camForward = camForward * rot;
    }
};

#endif