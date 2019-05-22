#ifndef __PAINTAREA__
#define __PAINTAREA__

// �����ࣺ����ΪPPM��ʽ


#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "RGBColor.h"

class PaintArea {
public:
	RGBColor**	pixelList;	//����ͼƬ
	int		width;			//ͼƬ��
	int		height;			//ͼƬ��

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