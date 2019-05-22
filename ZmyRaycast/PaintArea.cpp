#include "PaintArea.h"

PaintArea::PaintArea(void):width(400),height(300)
{
	pixelList = new RGBColor*[width];
	for (int i = 0; i <= width; i++) {
		pixelList[i] = new RGBColor[height+1];
	}
}

PaintArea::PaintArea(int w, int h):width(w),height(h)
{
	pixelList = new RGBColor*[width];
	for (int i = 0; i <= width; i++) {
		pixelList[i] = new RGBColor[height+1];
	}
}

PaintArea::~PaintArea()
{
	for (int i = 0; i <= width; i++) {
		delete[]pixelList;
	}

	pixelList = nullptr;
}

void PaintArea::setPixel(int x, int y, int r, int g, int b)
{
	pixelList[x][y] = RGBColor(r,g,b);
}

void PaintArea::savePixel()
{
	string fileName;
	cout << "input file name: ";
	cin >> fileName;
	ofstream fout(fileName);
	if (fout.is_open()) {
		fout << "P3\n" << width << " " << height << "\n255\n";
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				RGBColor col = pixelList[i][j];

				int ir = int(col.r);
				int ig = int(col.g);
				int ib = int(col.b);

				fout << ir << " " << ig << " " << ib << "\n";
			}
		}
		fout.close();
		cout << "complished\n" << endl;
	}
	else {
		cerr << "error\n" << endl;
	}
}
