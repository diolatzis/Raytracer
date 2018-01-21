#include "Raytracer.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"

int main()
{
	Raytracer r;

	Camera camera;

	Image img(500, 500);

	Sphere sphere = Sphere(Vec3<float>(0.6, 0.155, -1.35), 0.45, Colour3(1, 0, 0),false, true, true);

	//---- Vertical Wall ----//

	//Vertical Wall triangle 1

	Vec3<float> triangleVer[3];
	triangleVer[0] = Vec3<float>(-1,-0.2, -2);
	triangleVer[1] = Vec3<float>(1, 1.8, -2);
	triangleVer[2] = Vec3<float>(-1,1.8, -2);

	Vec3<float> triangleNorm[3];
	triangleNorm[0] = Vec3<float>(0, 0, 1).getNormal();
	triangleNorm[1] = Vec3<float>(0, 0, 1).getNormal();
	triangleNorm[2] = Vec3<float>(0, 0, 1).getNormal();

	Triangle3 VT1(triangleVer, triangleNorm, Colour3(0.25,0.6,0.8),false,true,false);

	//Vertical wall triangle 2

	Vec3<float> triangleVer2[3];
	triangleVer2[0] = Vec3<float>(-1, -0.2, -2);
	triangleVer2[1] = Vec3<float>(1, -0.2, -2);
	triangleVer2[2] = Vec3<float>(1, 1.8, -2);

	Vec3<float> triangleNorm2[3];
	triangleNorm2[0] = Vec3<float>(0, 0, 1).getNormal();
	triangleNorm2[1] = Vec3<float>(0, 0, 1).getNormal();
	triangleNorm2[2] = Vec3<float>(0, 0, 1).getNormal();

	Triangle3 VT2(triangleVer2, triangleNorm2, Colour3(0.25, 0.6, 0.8), false, true, false);

	//---- Horizontal Wall ----//

	//Horizontal Wall Triangle 1

	Vec3<float> triangleVer5[3];
	triangleVer5[0] = Vec3<float>(1, -0.3,-2);
	triangleVer5[1] = Vec3<float>(-1, -0.3, -2);
	triangleVer5[2] = Vec3<float>(1, -0.3, 0);

	Vec3<float> triangleNorm5[3];
	triangleNorm5[0] = Vec3<float>(0, 1, 0).getNormal();
	triangleNorm5[1] = Vec3<float>(0, 1, 0).getNormal();
	triangleNorm5[2] = Vec3<float>(0, 1, 0).getNormal();

	Triangle3 HT1(triangleVer5, triangleNorm5, Colour3(0.5, 0.5, 0.5), false, true, false);

	//Horizontal Wall Triangle 2

	Vec3<float> triangleVer6[3];
	triangleVer6[0] = Vec3<float>(-1, -0.3, -2);
	triangleVer6[1] = Vec3<float>(-1, -0.3, 0);
	triangleVer6[2] = Vec3<float>(1, -0.3, 0);

	Vec3<float> triangleNorm6[3];
	triangleNorm6[0] = Vec3<float>(0, 1, 0).getNormal();
	triangleNorm6[1] = Vec3<float>(0, 1, 0).getNormal();
	triangleNorm6[2] = Vec3<float>(0, 1, 0).getNormal();

	Triangle3 HT2(triangleVer6, triangleNorm6, Colour3(0.5, 0.5, 0.5), false, true, false);

	//---- Area Lights ----//

	//Areal Light Triangle 1

	Vec3<float> triangleVer7[3];
	triangleVer7[0] = Vec3<float>(-0.6, 2, -1.8);
	triangleVer7[2] = Vec3<float>( 0.6, 2, -1.8);
	triangleVer7[1] = Vec3<float>( 0.6, 2, -1);

	Vec3<float> triangleNorm7[3];
	triangleNorm7[0] = Vec3<float>(0, -1, 0).getNormal();
	triangleNorm7[1] = Vec3<float>(0, -1, 0).getNormal();
	triangleNorm7[2] = Vec3<float>(0, -1, 0).getNormal();

	Triangle3 ALT1(triangleVer7, triangleNorm7, Colour3(0.8, 0.8, 0.8), true, true, false, Radiance3(0.001,0.001,0.001));

	Vec3<float> triangleVer8[3];
	triangleVer8[0] = Vec3<float>(-0.6, 2, -1.8);
	triangleVer8[1] = Vec3<float>(0.6, 2, -1);
	triangleVer8[2] = Vec3<float>(0.6, 2, -1);

	Vec3<float> triangleNorm8[3];
	triangleNorm8[0] = Vec3<float>(0, -1, 0).getNormal();
	triangleNorm8[1] = Vec3<float>(0, -1, 0).getNormal();
	triangleNorm8[2] = Vec3<float>(0, -1, 0).getNormal();

	Triangle3 ALT2(triangleVer8, triangleNorm8, Colour3(0.8, 0.8, 0.8), true, true, false, Radiance3(0.001, 0.001, 0.001));

	//---- Lights ----//

	Light light(Vec3<float>(-0.2, 2, -0.6), Vec3<float>(2.5, 2.5, 2.5));

	Scene scene;

	//Build the scene
	scene.addSurfel(&VT1);
	scene.addSurfel(&VT2);
	scene.addSurfel(&HT1);
	scene.addSurfel(&HT2);
	scene.addLight(&light);
	scene.addAreaLight(&ALT1);
	scene.addAreaLight(&ALT2);
	scene.addSurfel(&sphere);

	r.rayTrace(img, scene, camera, 0, img.getWidth(), 0, img.getHeight());

	img.save("raster.ppm", 10);

	return 0;
}