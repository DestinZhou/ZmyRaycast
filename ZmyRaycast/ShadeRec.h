#ifndef __SHADE_REC__
#define __SHADE_REC__


// 渲染区域类
// 存储光线追踪器的所有信息，并对光线对象碰撞点着色

// We can use forward references for Material and World because they are a pointer and a reference

// 引用类型，只用前置声明
class Material;
class World;

// We need the following as #includes instead of forward class declarations,
// because we have the objects themselves, not pointers or references to them

#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRec {
public:

	bool				hit_an_object;		// did the ray hit an object?
	Material* 			material_ptr;		// pointer to the nearest object's material
	Point3D 			hit_point;			// world coordinates of intersection
	Point3D				local_hit_point;	// world coordinates of hit point on untransformed object (used for texture transformations)
	Normal				normal;				// normal at hit point
	Ray					ray;				// required for specular highlights and area lights
	int					depth;				// recursion depth
	RGBColor			color;				// used in the Chapter 3 only
	double				t;					// ray parameter
	float				u;					// texture coordinate
	float				v;					// texture coordinate
	World&				w;					// world reference

	ShadeRec(World& wr);					// constructor
	ShadeRec(const ShadeRec& sr);			// copy constructor
	~ShadeRec(void);						// destructor
};

#endif
