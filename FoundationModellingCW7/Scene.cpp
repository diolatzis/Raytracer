#include "Scene.h"

Scene::Scene()
{
}

void Scene::addSurfel(SurfaceElement *surfel)
{
	m_surfels.push_back(surfel);
}

void Scene::addAreaLight(SurfaceElement * areaLight)
{
	m_areaLights.push_back(areaLight);
}

void Scene::addLight(Light * light)
{
	m_lights.push_back(light);
}

bool Scene::intersect(Ray3 ray, SurfaceElement * &surfel, float& dist)
{
	dist = INFINITY;
	float surfelDist = INFINITY;

	//For each surfel if there is and intersection with smaller distance save distance and surfel
	for (int i = 0; i < m_surfels.size(); i++)
	{
		if (m_surfels.at(i)->intersect(ray, surfelDist))
		{
				dist = surfelDist;
				surfel = m_surfels.at(i);
		}
	}

	//If there is no intersection return false
	if (dist == INFINITY)
	{
		return false;
	}

	else
	{
		return true;
	}

}

bool Scene::lineOfSight(Vec3<float> start, Vec3<float> end)
{
	Ray3 ray(start, end - start);
	float dist = INFINITY;

	for (int i = 0; i < m_surfels.size(); i++)
	{
		if (m_surfels.at(i)->intersect(ray, dist))
		{
			//If there is a surfel that intersects before the end point of ray
			//and the distance is bigger than a threshold to avoid intersection
			//with self
			if (dist > 1e-4 && dist < (end - start).getLength())
				return false;
		}
	}

	return true;
}
