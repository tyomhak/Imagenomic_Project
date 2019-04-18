#ifndef __GENERICFILTER_H__
#define __GENERICFILTER_H__

#include "BitmapImage.h"
#include <thread>

class GenericFilter
{
public:
	GenericFilter(int rad);
	virtual ~GenericFilter();

	virtual void filter(BitmapImage* out) = 0;

private:
	int radius;
};

#endif // __GENERICFILTER_H__