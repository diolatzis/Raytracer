#include "Image.h"

const Radiance3& Image::getValue(const int x, const int y)
{
	return m_values[x + y*m_width];
}

void Image::set(const int x, const int y, const Radiance3& value)
{
	m_values[x + y*m_width] = value;
}

//Save image to ppm
void Image::save(const std::string& filename, float d) const 
{
	FILE* file = fopen(filename.c_str(), "wt");
	fprintf(file, "P3 %d %d 255\n", m_width, m_height);
	for (int y = 0; y < m_height; ++y) 
	{
		fprintf(file, "\n# y = %d\n", y);
		for (int x = 0; x < m_width; ++x) 
		{
			const Radiance3& c(get(x, y));
			fprintf(file, "%d %d %d\n",
				PPMGammaEncode(c[0], d),
				PPMGammaEncode(c[1], d),
				PPMGammaEncode(c[2], d));
		}
	}
	fclose(file);
}