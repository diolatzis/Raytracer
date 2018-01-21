#ifndef SURFACE_ELEMENT_H
#define SURFACE_ELEMENT_H

#include "Ray3.h"
#include "BSDF.h"

class SurfaceElement
{
protected:

	bool m_emits, m_reflectsDirect, m_scattersImpulse;

	BSDF bsdf;

	float m_extProb;

public:

	Radiance3 m_pow;

	virtual bool intersect(Ray3 &ray, float &dist) = 0;

	bool emits() { return m_emits; }

	bool reflectsDirect() { return m_reflectsDirect; }

	bool scattersImpulse() { return m_scattersImpulse; }

	BSDF& getBSDF() { return bsdf; }

	virtual Vec3<float> getNormal(Vec3<float> P) = 0;

	virtual Vec3<float> samplePoint() = 0;

	float extProb() { return m_extProb; }
};


#endif

