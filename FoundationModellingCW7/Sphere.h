#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Ray3.h"
#include "SurfaceElement.h"

class Sphere : public SurfaceElement
{
	Vec3<float> m_pos;
	float m_rad;

public:

	Sphere(const Vec3<float> & pos, float rad, Colour3 colour, bool emits, bool reflectsDirect, bool scattersImpulse);
	~Sphere();

	Vec3<float> getPos() { return m_pos; }
	float getRad() { return m_rad; }

	bool intersect(Ray3& ray, float& dist);

	Vec3<float> getNormal(Vec3<float> P);

	Vec3<float> samplePoint();


};


#endif

