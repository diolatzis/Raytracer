#include "Sphere.h"

Sphere::Sphere(const Vec3<float> & pos ,float rad, Colour3 colour, bool emits, bool reflectsDirect, bool scattersImpulse)
{
	m_pos = pos;
	m_rad = rad;

	m_extProb = 0.7f;

	m_emits = emits;
	m_reflectsDirect = reflectsDirect;
	m_scattersImpulse = scattersImpulse;

	bsdf.s = 1000;
	bsdf.k_G = Colour3(0.8, 0.8, 0.8);

	bsdf.k_L = colour;

	m_emits = false;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Ray3 & ray, float & dist)
{
	Vec3<float> v = ray.m_dir.getNormal();
	Vec3<float> u = ray.m_org - m_pos;

	float A = v.dotProduct(v);
	float B = u.dotProduct(v) * 2;
	float C = u.dotProduct(u) - (m_rad*m_rad);

	float D = B*B - (4 * A*C);

	if (D < 0) return false;
	else
	{

		float t1 = (-B + sqrt(B*B - 4 * A*C)) / (2 * A);
		float t2 = (-B - sqrt(B*B - 4 * A*C)) / (2 * A);

		if (t1 > 0 && t2 > 0)
		{
			if (t1 < t2)
			{
				dist = t1;
				return true;
			}
			else
			{
				dist = t2;
				return true;
			}
			dist = t1;
		}
		else if (t1 > 0)
		{
			dist = t1;
			return true;
		}
		else if (t2 > 0)
		{
			dist = t2;
			return true;
		}
		else return false;
	}

	return false;
}

Vec3<float> Sphere::getNormal(Vec3<float> P)
{

	return (P-m_pos).getNormal();
}

Vec3<float> Sphere::samplePoint()
{
	return Vec3<float>();
}
