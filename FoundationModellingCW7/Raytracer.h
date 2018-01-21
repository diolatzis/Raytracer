#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <stdlib.h>
#include "Ray3.h"
#include "Triangle3.h"
#include "Misc.h"
#include "Camera.h"
#include "Image.h"
#include "Scene.h"
#include "SurfaceElement.h"

class Raytracer
{
	bool m_indirectLight = true;

public:

	Raytracer() {}

	void rayTrace(Image& image, Scene& scene, const Camera& camera, int x0, int x1, int y0, int y1);

	Ray3 computeEyeRay(float x, float y, int width, int height, const Camera& camera);

	Radiance3 pathTrace(Scene& scene, const Ray3& ray, bool isEyeRay);

	Radiance3 estimateDirectPointLight(Scene &scene, SurfaceElement *surfel, Ray3 ray, float dist);

	Radiance3 estimateDirectAreaLight(Scene &scene, SurfaceElement *surfel, Ray3 ray, float dist);

	Radiance3 estimateImpulseScattering(Scene &scene, Vec3<float> P, SurfaceElement *surfel, Ray3 ray, bool isEyeRay);

	Radiance3 estimateIndirectLight(Scene &scene, Vec3<float> P, SurfaceElement *surfel, Ray3 ray, bool isEyeRay);

	Vec3<float> randomVector(Vec3<float> n);

	float randomRange(float min, float max);
};

#endif