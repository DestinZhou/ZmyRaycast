#ifndef __WORLD__
#define __WORLD__

// 世界类

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

	ViewPlane					vp;					//视平面
	RGBColor					background_color;	//背景色
	Tracer*						tracer_ptr;			//跟踪器
	Sphere 						sphere;				// for Chapter 3 only， 球体
	PaintArea* 					paintArea;			//绘制器

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