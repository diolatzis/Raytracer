#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3.h"

class Light
{


public:

	Light(const Vec3<float>& pos, const Vec3<float>& pow) : m_pos(pos), m_pow(pow) {};

	Vec3<float> m_pos;	//Position
	Vec3<float> m_pow;	//Power
	
};

#endif