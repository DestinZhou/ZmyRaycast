#ifndef __WORLD__
#define __WORLD__

// ������

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
	PaintArea* 					paintArea;			//������

public:

	World(void);

	~World();

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
};

#endif