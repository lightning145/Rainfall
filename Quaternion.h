#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"

typedef struct Quaternion {
    float w;
    Vector v;

    Quaternion(float w = 0.0f, Vector v = Vector()) : w(w), v(v) { };
    
    Quaternion operator + (const Quaternion& q2) const;
    void operator += (const Quaternion& q2);

    Quaternion operator - (const Quaternion& q2) const;
    void operator -= (const Quaternion& q2);

    Quaternion operator * (const Quaternion& q2) const;
    void operator *= (const Quaternion& q2);

    Vector operator * (const Vector& vec) const;
    void operator *= (const Vector& vec);

    Quaternion operator * (const float& s) const;
    void operator *= (const float& s);

} Quaternion;

#endif