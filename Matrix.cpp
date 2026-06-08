#include "Matrix.h"
#include "Math.h"

Matrix Matrix::operator + (const Matrix& m2) const
{
    Matrix result;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result.data[i][j] = this->data[i][j] + m2.data[i][j];
        }
    }

    return result;
}

void Matrix::operator += (const Matrix& m2)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            this->data[i][j] = this->data[i][j] + m2.data[i][j];
        }
    }
}

Matrix Matrix::operator * (const float& s) const
{
    Matrix result;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            result.data[i][j] = this->data[i][j] * s;
        }
    }

    return result;
}

void Matrix::operator *= (const float& s)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            this->data[i][j] = this->data[i][j] * s;
        }
    }
}

Matrix Matrix::operator - (const Matrix& m2) const
{
    Matrix result;
    result = *this + (m2 * -1.0f);
    return result;
}

void Matrix::operator -= (const Matrix& m2)
{
    *this = *this + (m2 * -1.0f);
}

Matrix Matrix::operator * (const Matrix& m2) const
{
    Matrix result;

   for (size_t i = 0; i < 4; i++)
   {
    for (size_t j = 0; j < 4; j++)
    {
        result.data[i][j] = 
            this->data[i][0] * m2.data[0][j] +
            this->data[i][1] * m2.data[1][j] +
            this->data[i][2] * m2.data[2][j] +
            this->data[i][3] * m2.data[3][j]
        ;
    }
   } 

    return result;
}

void Matrix::operator *= (const Matrix& m2)
{
    for (size_t i = 0; i < 4; i++)
   {
    for (size_t j = 0; j < 4; j++)
    {
        this->data[i][j] = 
            this->data[i][0] * m2.data[0][j] +
            this->data[i][1] * m2.data[1][j] +
            this->data[i][2] * m2.data[2][j] +
            this->data[i][3] * m2.data[3][j]
        ;
    }
   } 
}


Vector Matrix::operator * (const Vector& v2) const
{
    Vector result;

    for (size_t i = 0; i < 4; i++)
    {
        result.data[i] = 
            this->data[i][0] * v2.data[0] +
            this->data[i][1] * v2.data[1] +
            this->data[i][2] * v2.data[2] +
            this->data[i][3] * v2.data[3]
        ;
    }

    return result;
}

bool Matrix::operator == (const Matrix& m2) const
{
    for (size_t i = 0; i < 4; i++)
	{
        for (size_t j = 0; j < 4; j++)
        {
            if (!Equal(this->data[i][j], m2.data[i][j]))
			    return false;
        }
	}

	return true;
}

bool Matrix::operator != (const Matrix& m2) const
{
    for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
        {
            if (!Equal(this->data[i][j], m2.data[i][j]))
			    return true;
        }
	}

	return false;
}
