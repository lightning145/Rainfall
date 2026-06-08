#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <cmath>

#include "Matrix.h"
#include "Quaternion.h"

#define VEC(x) Vector(x, x, x, x)
#define VEC2(x, y) Vector(x, y, 0.0f, 0.0f)
#define VEC3(x, y, z) Vector(x, y, z, 0.0f)
#define VEC4(x, y, z, w) Vector(x, y, z, w)

#define POINT(x, y, z) Vector(x, y, z, 1.0f)

extern const float PI;
extern const float EPSILON;

float Rtan(float number);
float Rsqrt(float number);
float ToRad(float angle);
float ToAngle(float rad);
float Equal(float x, float y);
float Lerp(float x, float y, float a);

float Dot(Vector v1, Vector v2);
Vector Cross(Vector v1, Vector v2);

float Length(Vector vec);
Vector Normalize(Vector vec);

Vector Lerp(Vector v1, Vector v2, float a);

Matrix Indentity();
Matrix Transpose(Matrix m);
float Det(Matrix m);
Matrix Inverse(Matrix m);

float Dot(Quaternion q1, Quaternion q2);
float Length(Quaternion q);
Quaternion Normalize(Quaternion q);
Quaternion Conjugate(Quaternion q);
Quaternion Inverse(Quaternion q);
Quaternion Lerp(Quaternion q1, Quaternion q2, float a);
Quaternion Slerp(Quaternion q1, Quaternion q2, float a);

inline Vector operator * (const Vector& vec, const Quaternion& q)
{
    Quaternion vecQuat(0.0f, vec);
    Quaternion resQuat = q * vecQuat * Inverse(q);
    return resQuat.v;
}

Quaternion AxisAngle(float angle, Vector axis);

#endif