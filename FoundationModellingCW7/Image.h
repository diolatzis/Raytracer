#ifndef IMAGE_H
#define IMAGE_H

#include "Misc.h"
#include "math.h"
#include <vector>

class Image
{

private:

	int m_width, m_height;
	std::vector<Radiance3> m_values; //Radiance of each pixel

public:

	Image() {};

	Image(const int width, const int height) : m_width(width), m_height(height), m_values(height*width) {};

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	const Radiance3& getValue(const int x, const int y);

	void set(const int x, const int y, const Radiance3& value);

	void set(const int i, const Radiance3& value)
	{
		m_values[i] = value;
	}

	const Radiance3& get(int x, int y) const 
	{
		return m_values[x + y * m_width];
	}

	//Get radiance from RGB
	Radiance3 getRadiance(Colour3 RGB, float d) const
	{

		return Radiance3(pow(RGB[0] / 255.0f, 2.2f) / d, pow(RGB[1] / 255.0f, 2.2f) / d, pow(RGB[2] / 255.0f, 2.2f) / d);
	}

	//Get RGB from radiance
	int PPMGammaEncode(float radiance, float d) const 
	{
		return int(pow(fminf(1.0f, fmaxf(0.0f, radiance * d)),
			1.0f / 2.2f) * 255.0f);
	}

	void save(const std::string& filename, float d) const;
};

#endif