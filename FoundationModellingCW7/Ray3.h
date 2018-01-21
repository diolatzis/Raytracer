#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray3
{
public:
	Vec3<float> m_org, m_dir; //Origin, direction

	Ray3(const Vec3<float>& org, const Vec3<float>& dir) : m_org(org), m_dir(dir) { }
};

#endif