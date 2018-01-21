#include "BSDF.h"

Colour3  BSDF::evaluateBSDF(const Vec3<float>& w_i, const Vec3<float>& w_o, const Vec3<float>& n) const
{
	const Vec3<float>& w_h = (w_i + w_o).getNormal();

	return (k_L + k_G * ((s + 8.0f) * powf(fmaxf(0.0f, w_h.dotProduct(n)), s) / 8.0f)) / PI;
}