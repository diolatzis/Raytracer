#ifndef CAMERA_H
#define CAMERA_H

#include "Misc.h"

class Camera
{
	float zNear, zFar, fovX;

public:

	//Initialize camera with constant zNear, zFar and field of view
	Camera() : zNear(-0.1f), zFar(-100.0f), fovX(PI / 2.0f) {}

	float getFovX() const { return fovX; }
	float getZNear() const { return zNear; }
	float getZFar() const { return zFar; }

};

#endif
