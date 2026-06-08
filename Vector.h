#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector
{
    union
    {
        float data[4];
        struct 
        {
            float x, y, z, w;
        };

        struct 
        {
            float r, g, b, a;
        };
        
        struct 
        {
            float s, t, p, q;
        };
        
    };

    Vector(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) : x(x), y(y), z(z), w(w) { };

    Vector operator + (const Vector& v2) const;
	void operator += (const Vector& v2);

	Vector operator - (const Vector& v2) const;
	void operator -= (const Vector& v2);

	Vector operator * (const Vector& v2) const;
	void operator *= (const Vector& v2);

	Vector operator * (const float& s) const;
	void operator *= (const float& s);

	bool operator == (const Vector& v2) const;
	bool operator != (const Vector& v2) const;

	Vector operator - () const;

} Vector;

inline Vector operator * (float s, const Vector& v)
{
    return const_cast<Vector&>(v) * s; 
}
#endif