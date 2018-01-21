#include "Triangle3.h"

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0.0, 1.0);


Triangle3::Triangle3(Vec3<float> vertices[3], Vec3<float> normals[3], Colour3 colour, bool emits, bool reflectsDirect, bool scattersImpulse, Radiance3 pow)
{
	m_reflectsDirect = reflectsDirect;
	m_scattersImpulse = scattersImpulse;

	m_extProb = 0.7f;

	m_vertices[0] = vertices[0];
	m_vertices[1] = vertices[1];
	m_vertices[2] = vertices[2];

	m_normals[0] = normals[0];
	m_normals[1] = normals[1];
	m_normals[2] = normals[2];

	m_pow = pow;

	bsdf.s = 60;
	bsdf.k_G = Colour3(0.05, 0.05, 0.05);

	bsdf.k_L = colour;

	m_emits = emits;
}

bool Triangle3::intersect(Ray3& ray, float& dist)
{
	const Vec3<float> e1 = m_vertices[1] - m_vertices[0];
	const Vec3<float> e2 = m_vertices[2] - m_vertices[0];

	const Vec3<float> q = ray.m_dir.crossProduct(e2);

	float a = e1.dotProduct(q);

	const Vec3<float>& s = ray.m_org - m_vertices[0];
	const Vec3<float>& r = s.crossProduct(e1);

	float weight[3];

	//Barycentric coordinates
	weight[1] = s.dotProduct(q) / a;
	weight[2] = ray.m_dir.dotProduct(r) / a;
	weight[0] = 1.0f - (weight[1] + weight[2]);

	float distance = e2.dotProduct(r) / a;
	static const float epsilon = 1e-7f;
	static const float epsilon2 = 1e-10;

	if ((a <= epsilon) || (weight[0] < -epsilon2) ||
		(weight[1] < -epsilon2) || (weight[2] < -epsilon2) ||
		(dist <= 0.0f))
	{
		
		//The ray either does not intersect the triangle or is too parallel to it
		return false;
	}
	else
	{
		dist = distance;
		return true;
	}

	return false;
}

Vec3<float> Triangle3::getNormal(Vec3<float> P)
{
	return m_normals[0];
}

Vec3<float> Triangle3::samplePoint()
{
	double a = distribution(generator);
	double b = distribution(generator);

	Vec3<float> random = m_vertices[0] + (m_vertices[1] - m_vertices[0])*a + (m_vertices[2] - m_vertices[0])*b;

	return random;
}
