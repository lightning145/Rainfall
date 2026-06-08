
#include "Math.h"

Quaternion Quaternion::operator + (const Quaternion& q2) const
{
    Quaternion result;
    result.w = w + q2.w;
    result.v = v + q2.v;
    return result;
}

void Quaternion::operator += (const Quaternion& q2)
{
    w += q2.w;
    v += q2.v;
}

Quaternion Quaternion::operator - (const Quaternion& q2) const
{
    Quaternion result;
    result.w = w - q2.w;
    result.v = v - q2.v;
    return result;
}

void Quaternion::operator -= (const Quaternion& q2)
{
    w -= q2.w;
    v -= q2.v;
}

Quaternion Quaternion::operator * (const Quaternion& q2) const
{
    Quaternion result;

    float dot3d = this->v.x * q2.v.x + this->v.y * q2.v.y + this->v.z * q2.v.z;

    result.w = this->w * q2.w - dot3d;
    
    Vector crossRes = Cross(this->v, q2.v);
    result.v.x = crossRes.x + this->w * q2.v.x + q2.w * this->v.x;
    result.v.y = crossRes.y + this->w * q2.v.y + q2.w * this->v.y;
    result.v.z = crossRes.z + this->w * q2.v.z + q2.w * this->v.z;
    result.v.w = 0.0f; 

    return result;
}

void Quaternion::operator *= (const Quaternion& q2)
{
    *this = (*this) * q2;
}

Quaternion Quaternion::operator * (const float& s) const
{
    return Quaternion(w * s, v * s);
}

void Quaternion::operator *= (const float& s)
{
    w *= s;
    v *= s;
}

Vector Quaternion::operator * (const Vector& vec) const
{
    Vector result;
     Quaternion vecQuat(0.0f, vec);
     Quaternion resQuat = (*this) * vecQuat * Inverse(*this);

    result = resQuat.v;
    return result;  
}

void Quaternion::operator *= (const Vector& vec)
{
    Quaternion vecQuat(0.0f, vec);
    *this = (*this) * vecQuat * Inverse(*this);
}