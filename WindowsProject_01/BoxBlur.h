#pragma once
#include "GenericFilter.h"
class BoxBlur :
	public GenericFilter
{
public:
	BoxBlur(int radius);
	~BoxBlur();

	void filter(Bitmap* out)override;
};

