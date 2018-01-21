#include "Raytracer.h"

const int NUMBER_OF_SAMPLES = 500;

std::default_random_engine raytracerGenerator;
std::uniform_real_distribution<double> raytracerDistribution(0.0, 1.0);

//Main ray tracing function
void Raytracer::rayTrace(Image& image, Scene& scene, const Camera& camera, int x0, int x1, int y0, int y1)
{
	//Loop through every pixel
	for (int y = y0; y < y1; ++y)
	{
		for (int x = x0; x < x1; ++x)
		{
			Radiance3 pixelRadiance(0.0, 0.0, 0.0);

			//Ray through the pixel
			const Ray3& R = computeEyeRay(x + 0.5f, y + 0.5f, image.getWidth(),image.getHeight(), camera);
			
			for (int i = 0; i < NUMBER_OF_SAMPLES; i++)
			{
				pixelRadiance = pixelRadiance + pathTrace(scene, R, true);
			}

			//Average out the pixel radiance
			pixelRadiance = pixelRadiance / ((float)NUMBER_OF_SAMPLES);

			image.set(x, y, pixelRadiance);
		}
	}
}

//Function that computes ray which passes through x,y pixel
Ray3 Raytracer::computeEyeRay(float x, float y, int width, int height, const Camera& camera)
{
	const float aspect = float(height) / width;

	const float s = -2.0f * tan(camera.getFovX()*0.5f);

	const Vec3<float>& start = Vec3<float>((x / width - 0.5f)*s* camera.getZNear(), -(y / height - 0.5f)*s*aspect* camera.getZNear(), 1.0f* camera.getZNear());

	return Ray3(start, start.getNormal());
}

Radiance3 Raytracer::pathTrace(Scene& scene, const Ray3& ray, bool isEyeRay)
{
	Radiance3 output(0.0, 0.0, 0.0);

	float dist;
	SurfaceElement *surfel = NULL;

	if (scene.intersect(ray, surfel, dist))	//If there is an intersection
	{
		//Point of impact
		const Vec3<float> P = ray.m_org + ray.m_dir * dist;

		//If the object is an area light
		if (isEyeRay && surfel->emits())
		{
			output = output + surfel->m_pow;
		}

		//If the object reflects direct
		if ((!isEyeRay) || surfel->reflectsDirect())
		{
			output = output + estimateDirectPointLight(scene, surfel, ray, dist);	//Calculate point light reflection
			output = output + estimateDirectAreaLight(scene, surfel, ray, dist);	//Calculate area light reflection
		}

		//If indirect lighting is enabled
		if ((!isEyeRay) || m_indirectLight)
		{
			//If the object has impulse scattering 
			if (surfel->scattersImpulse())
			{
				output = output + estimateImpulseScattering(scene, P, surfel, ray, false);
			}
			//Else compute indirect lighting using random ray
			else
			{
				output = output + estimateIndirectLight(scene, P, surfel, ray, false);
			}
		}
	}

	return output;
}

Radiance3 Raytracer::estimateDirectPointLight(Scene& scene, SurfaceElement *surfel, Ray3 ray, float dist)
{
	Radiance3 L_o(0, 0, 0);

	for (int i = 0; i < scene.getLights().size(); i++)
	{
		
		//Point of intersection
		const Vec3<float> P = ray.m_org + ray.m_dir * dist;

		if (scene.lineOfSight(P + surfel->getNormal(P)*0.00001f, scene.getLights().at(i)->m_pos))
		{
			//Vector from light to point of intersection
			const Vec3<float>& offset = scene.getLights().at(i)->m_pos - P;
			const Vec3<float>& w_i = offset.getNormal();

			const Vec3<float>& n = surfel->getNormal(P);
			const Vec3<float> w_o = -ray.m_dir;

			//Light input
			const Radiance3& L_i = scene.getLights().at(i)->m_pow / (4 * PI*pow(offset.getLength(), 2));

			//Maximum used for scattering
			float max = fmaxf(0.0, w_i.dotProduct(n));

			//Get percentage of light input reflected
			Colour3 value = surfel->getBSDF().evaluateBSDF(w_i, w_o, n);

			Radiance3 total(L_i[0] * value[0] * max, L_i[1] * value[1] * max, L_i[2] * value[2] * max);

			//Add to the total light output
			L_o = L_o + total;
		}

		
	}

	return L_o;

	
}

Radiance3 Raytracer::estimateDirectAreaLight(Scene& scene, SurfaceElement *surfel, Ray3 ray, float dist)
{
	Radiance3 L_o(0, 0, 0);

	for (int i = 0; i < scene.getAreaLights().size(); i++)
	{
		//if not in shadow

		//Point of intersection
		const Vec3<float> P = ray.m_org + ray.m_dir * dist;

		if (scene.lineOfSight(P + surfel->getNormal(P)*0.001f, scene.getAreaLights().at(i)->samplePoint()))
		{
			//Vector from light to point of intersection
			const Vec3<float>& offset = scene.getAreaLights().at(i)->samplePoint() - P;
			Vec3<float>& w_i = offset.getNormal();

			const Vec3<float>& n = surfel->getNormal(P);
			const Vec3<float> w_o = -ray.m_dir;

			//Light input
			const Radiance3& L_i = scene.getAreaLights().at(i)->m_pow / PI;

			//Maximum used for scattering
			float max = fmaxf(0.0, w_i.dotProduct(n));

			//Get percentage of light input reflected
			Colour3 value = surfel->getBSDF().evaluateBSDF(w_i, w_o, n);

			Radiance3 total(L_i[0] * value[0] * max, L_i[1] * value[1] * max, L_i[2] * value[2] * max);

			//Add to the total light output
			L_o = L_o + total;
		}

		
	}

	return L_o;
}

Radiance3 Raytracer::estimateImpulseScattering(Scene &scene, Vec3<float> P, SurfaceElement * surfel, Ray3 ray, bool isEyeRay)
{
	//If ray is extinguished
	if (randomRange(0.0f, 1.0f) > surfel->extProb())
		return Radiance3(0, 0, 0);
	else
	{
		//Mirror reflection
		Vec3<float> w_o = ray.m_dir;

		Vec3 <float> w_i = (w_o - (surfel->getNormal(P) * w_o.dotProduct(surfel->getNormal(P)) * 2)).getNormal();

		
		Ray3 ray2(P+surfel->getNormal(P)*0.0001f, w_i);

		return pathTrace(scene, ray2, false);
	}

	return Radiance3();
}

Radiance3 Raytracer::estimateIndirectLight(Scene &scene, Vec3<float> P, SurfaceElement * surfel, Ray3 ray, bool isEyeRay)
{
	if (randomRange(0.0f,1.0f) > surfel->extProb())
		return Radiance3(0, 0, 0);
	else
	{
		//Create a random reflected ray
		Vec3<float> bounceVector = randomVector(surfel->getNormal(P));
		Ray3 bounceRay(P+surfel->getNormal(P)*0.0001f, bounceVector);

		return pathTrace(scene, bounceRay, false);	
	}

	return Radiance3();
}

Vec3<float> Raytracer::randomVector(Vec3<float> n)
{
	while (true)
	{
		Vec3<float> v(randomRange(-1, 1), randomRange(-1, 1), randomRange(-1, 1));

		float length = v.getLength();

		if (length > 1.0f || length < 0.1f)
		{
			return (v-n).getNormal();
		}
	}

	return Vec3<float>(0, 0, 0);
}

float Raytracer::randomRange(float min, float max)
{
	float range = max - min;
	float random = raytracerDistribution(raytracerGenerator);

	random *= range;

	random += min;

	return random;

	return 0.0f;
}

