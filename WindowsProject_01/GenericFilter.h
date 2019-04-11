#ifndef __GENERICFILTER_H__
#define __GENERICFILTER_H__

#include "GenericImage.h"

class GenericFilter
{
public:
	GenericFilter(int rad);
	virtual ~GenericFilter();

	virtual void filter(Bitmap* out) = 0;

private:
	int radius;
	//GenericImage *image;
};

#endif // __GENERICFILTER_H__