#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "SurfaceElement.h"
#include "Ray3.h"
#include "Light.h"

class Scene
{

	std::vector<SurfaceElement*> m_surfels;
	std::vector<Light*> m_lights;
	std::vector<SurfaceElement *> m_areaLights;

public:

	Scene();

	void addSurfel(SurfaceElement *surfel);

	void addAreaLight(SurfaceElement *areaLight);

	void addLight(Light *light);

	std::vector<Light*>& getLights() { return m_lights; }

	std::vector<SurfaceElement*>& getAreaLights() { return m_areaLights; }

	bool intersect(Ray3 ray, SurfaceElement * &surfel, float& dist);

	bool lineOfSight(Vec3<float> start, Vec3<float> end);
};

#endif
