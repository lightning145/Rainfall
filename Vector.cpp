#include "Vector.h"

#include "Math.h"

Vector Vector::operator + (const Vector& v2) const
{
	Vector result;

	for (size_t i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] + v2.data[i];
	}

	return result;
}

void Vector::operator += (const Vector& v2)
{
	for (size_t i = 0; i < 4; i++)
	{
		this->data[i] += v2.data[i];
	}
}

Vector Vector::operator - (const Vector& v2) const
{
	Vector result;

	for (size_t i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] - v2.data[i];
	}

	return result;
}

void Vector::operator -= (const Vector& v2)
{
	for (size_t i = 0; i < 4; i++)
	{
		this->data[i] -= v2.data[i];
	}
}

Vector Vector::operator * (const Vector& v2) const
{
	Vector result;

	for (size_t i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] * v2.data[i];
	}

	return result;
}

void Vector::operator *= (const Vector& v2)
{
	for (size_t i = 0; i < 4; i++)
	{
		this->data[i] *= v2.data[i];
	}
}

Vector Vector::operator * (const float& s) const
{
	Vector result;

	for (size_t i = 0; i < 4; i++)
	{
		result.data[i] = this->data[i] * s;
	}

	return result;
}

void Vector::operator *= (const float& s)
{
	for (size_t i = 0; i < 4; i++)
	{
		this->data[i] *= s;
	}
}

bool Vector::operator == (const Vector& v2) const
{
	for (size_t i = 0; i < 4; i++)
	{
		if (!Equal(this->data[i], v2.data[i]))
			return false;
	}

	return true;
}

bool Vector::operator != (const Vector& v2) const
{
	for (size_t i = 0; i < 4; i++)
	{
		if (!Equal(this->data[i], v2.data[i]))
			return true;
	}

	return false;
}

Vector Vector::operator - () const
{
	Vector result;
	result = *this * -1.0f;
	return result;
}