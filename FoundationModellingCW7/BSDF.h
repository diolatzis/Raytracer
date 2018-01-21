#ifndef BSDF_H
#define BSDF_H

#include "Vec3.h"
#include "Misc.h"
#include <math.h>

class BSDF
{
public:

	BSDF() {};

	Colour3 k_L; //Lambertian constant
	Colour3 k_G; //Magnitude of glossy lobe

	
	float s;	//Smoothness

	Colour3 evaluateBSDF(const Vec3<float>& w_i, const Vec3<float>& w_o, const Vec3<float>& n) const;

	void setKL(const Colour3& KL) { k_L = KL; }

	void setKG(const Colour3& KG) { k_G = KG; }
	
};

#endif