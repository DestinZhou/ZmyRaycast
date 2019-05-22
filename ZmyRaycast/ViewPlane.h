#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__

//��ƽ����

class ViewPlane {
public:
	int 			hres;   					// horizontal image resolution	ˮƽͼ������
	int 			vres;   					// vertical image resolution	��ֱͼ������
	float			s;							// pixel size					���ش�С
	int				num_samples;				// number of samples per pixel	ÿ�����ص�Ĳ���

	float			gamma;						// gamma correction factor		gamma��������
	float			inv_gamma;					// the inverse of the gamma correction factor  1/gamma
	bool			show_out_of_gamut;			// display red if RGBColor out of gamut			�Ƿ񳬹���ɫֵ��Χʱ����ʾ��ɫ



public:

	ViewPlane();   								// default Constructor

	ViewPlane(const ViewPlane& vp);				// copy constructor

	ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator

	~ViewPlane();   							// destructor

	void
		set_hres(const int h_res);

	void
		set_vres(const int v_res);

	void
		set_pixel_size(const float size);

	void
		set_gamma(const float g);

	void
		set_gamut_display(const bool show);

	void
		set_samples(const int n);
};




// set_hres

inline void
ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}


// set_vres

inline void
ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}


//  set_pixel_size

inline void
ViewPlane::set_pixel_size(const float size) {
	s = size;
}


//  set_gamma

inline void
ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}


//  set_gamut_display

inline void
ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}


// set_samples

inline void
ViewPlane::set_samples(const int n) {
	num_samples = n;
}

#endif