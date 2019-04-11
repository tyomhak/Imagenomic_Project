#pragma once
#include "GenericFilter.h"
class BoxBlur :
	public GenericFilter
{
public:
	BoxBlur(int radius);
	~BoxBlur();

	void filter(Bitmap* out)override;


private:
	void static verticalAvg(GenericImage& img, int color, int radius);

	void static horizAvg(GenericImage& img, int color, int radius);
};

