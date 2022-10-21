#pragma once
#include "Scene.h"
#include "Color.h"
#include "Barrier.h"
#include "Sphere.h"
#include "utils.h"

namespace pr {

class RayTracerJob : public Job {

	void calcul () {
		for (int  y = 0 ; y < scene.getHeight() ; y++) {

			// le point de l'ecran par lequel passe ce rayon
			auto & screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon  ray(scene.getCameraPos(), screenPoint);

			int targetSphere = findClosestInter(scene, ray);

			if (targetSphere == -1) {
				// keep background color
				continue ;
			} else {
				const Sphere & obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color & pixel = pixels[y*scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
			}
		}
	}

	int x;
	const Scene::screen_t & screen;
	Scene& scene;
	Color * pixels;
	Barrier& b;
	vector<Vec3D>& lights;

public :
	RayTracerJob(	int x_, int y_, const Scene::screen_t & screen_, Scene& scene_,Color* pixels_,vector<Vec3D>& lights_,Barrier& b_) : 
	x(x_),screen(screen_),scene(scene_),pixels(pixels_),b(b_),lights(lights_) {}
	void run () {
		calcul();
		b.done();
	}
	~RayTracerJob(){}
};

}