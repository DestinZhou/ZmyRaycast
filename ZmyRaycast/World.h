#ifndef __WORLD__
#define __WORLD__

// ������
#include <vector>

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Tracer.h"
#include "GeometricObject.h"
#include "Sphere.h"
#include "Ray.h"
#include "SingleSphere.h"
#include "PaintArea.h"

using namespace std;

class World {
public:

	ViewPlane					vp;					//��ƽ��
	RGBColor					background_color;	//����ɫ
	Tracer*						tracer_ptr;			//������
	Sphere 						sphere;				// for Chapter 3 only�� ����
	vector<GeometricObject*>	objects;
	PaintArea* 					paintArea;			//������

public:

	World(void);

	~World();

	void
		add_object(GeometricObject* object_ptr);

	void
		build(void);

	void
		render_scene(void) const;

	RGBColor
		max_to_one(const RGBColor& c) const;

	RGBColor
		clamp_to_color(const RGBColor& c) const;

	void
		display_pixel(const int row, const int column, const RGBColor& pixel_color) const;

	ShadeRec
		hit_bare_bones_objects(const Ray& ray);
private:

	void
		delete_objects(void);
};


// add_object

inline void
World::add_object(GeometricObject* object_ptr) {
	objects.push_back(object_ptr);
}

#endif