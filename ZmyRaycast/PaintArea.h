#ifndef __PAINTAREA__
#define __PAINTAREA__

// 绘制类：保存为PPM格式


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "RGBColor.h"

class PaintArea {
public:
	RGBColor**	pixelList;	//保存图片
	int		width;			//图片宽
	int		height;			//图片长

public:
	PaintArea(void);

	PaintArea(int width, int height);

	~PaintArea();

	void
		setPixel(int x, int y, int r, int g, int b);

	void
		savePixel();
};

#endif