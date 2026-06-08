#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

typedef struct Matrix
{
    union 
    {
        float data[4][4];
        struct 
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        
    };

    Matrix(
        float _11 = 0.0f, float _12 = 0.0f, float _13 = 0.0f, float _14 = 0.0f,
        float _21 = 0.0f, float _22 = 0.0f, float _23 = 0.0f, float _24 = 0.0f,
        float _31 = 0.0f, float _32 = 0.0f, float _33 = 0.0f, float _34 = 0.0f,
        float _41 = 0.0f, float _42 = 0.0f, float _43 = 0.0f, float _44 = 0.0f
    ) : _11(_11), _12(_12), _13(_13), _14(_14),
        _21(_21), _22(_22), _23(_23), _24(_24),
        _31(_31), _32(_32), _33(_33), _34(_34),
        _41(_41), _42(_42), _43(_43), _44(_44)
    {}

    Matrix operator + (const Matrix& m2) const;
	void operator += (const Matrix& m2);

    Matrix operator * (const float& s) const;
	void operator *= (const float& s);

	Matrix operator - (const Matrix& m2) const;
	void operator -= (const Matrix& m2);

	Matrix operator * (const Matrix& m2) const;
	void operator *= (const Matrix& m2);

    Vector operator * (const Vector& v2) const;

	bool operator == (const Matrix& m2) const;
	bool operator != (const Matrix& m2) const;
    
} Matrix;

inline Matrix operator * (float s, const Matrix& m)
{
    return const_cast<Matrix&>(m) * s; 
}

inline Vector operator * (const Vector& vec, const Matrix& m)
{
    return const_cast<Matrix&>(m) * vec; 
}

#endif