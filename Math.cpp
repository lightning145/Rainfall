#include "Math.h"

const float PI = 3.14159265358979323846f;
const float EPSILON = 1.192092896e-07f;

float Rtan(float number)
{
	return 1.0f / std::tanf(number);
}

float Rsqrt(float number)
{
	return 1.0f / std::sqrtf(number);
}

float ToRad(float angle)
{
	return angle * 0.01745329251994329577f;// PI / 180.0f
}

float ToAngle(float rad)
{
	return rad * 57.2957795130823208768f; // 180.0f / PI
}

float Equal(float x, float y)
{
	return (std::fabsf(x - y) < EPSILON) ? true : false;
}

float Lerp(float x, float y, float a)
{
	return (1.0f - a) * x + a * y;
}

float Dot(Vector v1, Vector v2)
{
	float result = 0.0f;

	for (size_t i = 0; i < 4; i++)
	{
		result += v1.data[i] * v2.data[i];
	}

	return result;
}

Vector Cross(Vector v1, Vector v2)
{
	Vector result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

float Length(Vector vec)
{
	return std::sqrtf(Dot(vec, vec));
}

Vector Normalize(Vector vec)
{
	float Rlength = Rsqrt(Dot(vec, vec));
	Vector result;
	result = vec * Rlength;
	return result;
}

Vector Lerp(Vector v1, Vector v2, float a)
{
	Vector result;

	result = v1 * (1.0f - a) + v2 * a;

	return result;
}

Matrix Indentity()
{
    return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix Transpose(Matrix m)
{
    Matrix result;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result.data[i][j] = m.data[j][i];
        }
    }

    return result;
}

//Tool Funcation---------------------------------

float Det2x2(float m[2][2])
{
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

float Det3x3(float m[3][3])
{
    return m[0][0] * Det2x2((float[2][2]){ { m[1][1], m[1][2] }, { m[2][1], m[2][2] } }) -
           m[0][1] * Det2x2((float[2][2]){ { m[1][0], m[1][2] }, { m[2][0], m[2][2] } }) +
           m[0][2] * Det2x2((float[2][2]){ { m[1][0], m[1][1] }, { m[2][0], m[2][1] } });
}

float Sgin(int i, int j)
{
    return (i + j) % 2 == 0 ? 1.0f : -1.0f;
}

//-----------------------------------------------

float Det(Matrix m)
{
    float result = 0.0f;
    float temp_m[3][3];
    for (size_t k = 0; k < 4; k++)
    {
        size_t _i = 1;
        for (size_t i = 0; i < 3; i++)
        {
            size_t _j = 0;
            for (size_t j = 0; j < 3; j++)
            {
                if (_j == k)
                    _j++;

                temp_m[i][j] = m.data[_i][_j];
                _j++;
            }

            _i++;
        }

        result += Sgin(0, (int)k) * m.data[0][k] * Det3x3(temp_m);
    }
    
    return result;
}

//Adj Mat-----------------------------------------------------------

Matrix Adjoint(Matrix m)
{
    Matrix result;
    float temp_m[3][3];

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            size_t _i = 0;

            for (size_t t_i = 0; t_i < 3; t_i++)
            {
                size_t _j = 0;
                
                if (_i == i)
                    _i++;

                for (size_t t_j = 0; t_j < 3; t_j++)
                {
                    if (_j == j)
                        _j++;

                    temp_m[t_i][t_j] = m.data[_i][_j];
                    _j++;
                }

                _i++;
            }

            result.data[i][j] = Sgin((int)i, (int)j) * Det3x3(temp_m);
        }
    }

    return Transpose(result);
}

//------------------------------------------------------------------

Matrix Inverse(Matrix m)
{
    Matrix result;

    float det = Det(m);
    if (Equal(det, 0.0f))
    {
        return result;
    }

    result = Adjoint(m) * (1.0f / det);

    return result;
}

float Dot(Quaternion q1, Quaternion q2)
{
    Vector v_q1 = q1.v;
    Vector v_q2 = q2.v;

    return q1.w * q2.w + Dot(v_q1, v_q2);
}

float Length(Quaternion q)
{
    return std::sqrtf(Dot(q, q));
}

Quaternion Normalize(Quaternion q)
{
    float Rlength = Rsqrt(Dot(q, q));
    Quaternion result;
    result.w = q.w * Rlength;
    result.v = q.v * Rlength;
    return result;
}

Quaternion Conjugate(Quaternion q)
{
    Quaternion result;
    result.w = q.w;
    result.v = -q.v;
    return result;
}

Quaternion Inverse(Quaternion q)
{
    float len = Dot(q, q);
    if (Equal(len, 0.0f))
    {
        return Quaternion();
    }

    return Conjugate(q) * (1.0f / len);
}

Quaternion Lerp(Quaternion q1, Quaternion q2, float a)
{
    return Normalize(q1 * (1.0f - a) + q2 * a);
}

Quaternion Slerp(Quaternion q1, Quaternion q2, float a)
{
    float dot = Dot(q1, q2);

    if (dot < 0.0f)
    {
        q2 = q2 * -1.0f;
        dot = -dot;
    }

    if (dot > 1.0f) dot = 1.0f;

    float phi = std::acosf(dot);

    float sin_phi = std::sinf(phi);
    if (Equal(sin_phi, 0.0f))
    {
        return Lerp(q1, q2, a);
    }

    float l_q1 = std::sinf((1.0f - a) * phi) / sin_phi;
    float l_q2 = std::sinf(a * phi) / sin_phi;

    return Normalize(q1 * l_q1 + q2 * l_q2);
}

Quaternion AxisAngle(float angle, Vector axis)
{
    if (Equal(Dot(axis, axis), 0.0f))
    {
        return Quaternion(1.0f, Vector(0.0f, 0.0f, 0.0f));
    }

    float half_angle = angle * 0.5f;
    float s = std::sinf(half_angle);
    float c = std::cosf(half_angle);

    return Quaternion(c, Normalize(axis) * s);
}