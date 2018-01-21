#ifndef TRIANGLE_3_H
#define TRIANGLE_3_H

#include "Vec3.h"
#include "Ray3.h"
#include "SurfaceElement.h"
#include <random>

class Triangle3 : public SurfaceElement
{

private:

	Vec3<float> m_vertices[3];
	Vec3<float> m_normals[3];

public:

	Triangle3(Vec3<float> vertices[3], Vec3<float> normals[3], Colour3 colour, bool emits, bool reflectsDirect, bool scattersImpulse, Radiance3 pow = Radiance3(0,0,0));

	Vec3<float> getVertex(int i) const { return m_vertices[i]; }
	const Vec3<float>& getNormal(int i) const { return m_normals[i]; }

	bool intersect(Ray3& ray, float& dist);

	Vec3<float> getNormal(Vec3<float> P);

	virtual Vec3<float> samplePoint();


};

#endif