
#include "World.h"
#include "Constants.h"

// geometric objects
#include "Sphere.h"

// tracers
#include "SingleSphere.h"
#include "MultipleObjects.h"

// utilities
#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"

// 构造函数
// 背景色设为黑色
// 跟踪器为空
// 绘制场景设置为200*200
World::World(void)
	: background_color(black),
	tracer_ptr(NULL),
	paintArea(NULL)
{
}

// 析构函数
World::~World(void) {

	if (tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}

	delete_objects();
}


//渲染场景
// This uses orthographic viewing along the zw axis
// 使用正交视图
void
World::render_scene(void) const {

	RGBColor	pixel_color;
	Ray			ray;
	int 		hres = vp.hres;
	int 		vres = vp.vres;
	float		s = vp.s;
	float		zw = 100.0;				// hardwired in

	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c <= hres; c++) {	// across 					
			ray.o = Point3D(s * (c - hres / 2.0 + 0.5), s * (r - vres / 2.0 + 0.5), zw);
			pixel_color = tracer_ptr->trace_ray(ray);
			display_pixel(r, c, pixel_color);
		}

	paintArea->savePixel();
}


// clamp [0, 1]
RGBColor
World::max_to_one(const RGBColor& c) const {
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// clamp_to_color
// Set color to red if any component is greater than one
// 如果颜色超过1， 设置为红色
RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}

	return (c);
}


// ---------------------------------------------------------------------------display_pixel
// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);

	if (vp.gamma != 1.0)
		mapped_color = mapped_color.powc(vp.inv_gamma);

	//have to start from max y coordinate to convert to screen coordinates
	int x = column;
	int y = vp.vres - row - 1;

	// cout << x << " " << y << endl;
	paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
		(int)(mapped_color.g * 255),
		(int)(mapped_color.b * 255));

}


void
World::build(void) {
	// 输入图片长宽
	int weight, height;
	cout << "请输入长度：";
	cin >> weight;
	cout << "请输入宽度：";
	cin >> height;

	// 设置视平面
	vp.set_hres(weight);
	vp.set_vres(height);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);

	// 设置绘图区域
	paintArea = new PaintArea(weight, height);

	// 背景色
	background_color = black;

	/* single object */
	/*
	// 跟踪器
	tracer_ptr = new SingleSphere(this);

	// 绘制球体
	sphere.set_center(0.0);
	sphere.set_radius(85.0);
	*/

	/* multi object*/
	tracer_ptr = new MultipleObjects(this);

	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->set_center(0, -25, 0);
	sphere_ptr->set_radius(80.0);
	sphere_ptr->set_color(1, 0, 0);  // red
	add_object(sphere_ptr);

	sphere_ptr = new Sphere(Point3D(0, 30, 0), 60);
	sphere_ptr->set_color(1, 1, 0);	// yellow
	add_object(sphere_ptr);
}

// delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}

// hit_bare_bones_objects  计算光线与场景中的全部物体的相交检测，记录到ShadeRec中

ShadeRec
World::hit_bare_bones_objects(const Ray& ray)  {

	ShadeRec	sr(*this);
	double		t;
	double		tmin = kHugeValue;
	int 		num_objects = objects.size();

	// 遍历全部物体，计算最近的相交点，记录数据到shadeRec中
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j]->get_color();
		}

	return(sr);
}