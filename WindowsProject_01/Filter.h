#ifndef __FILTER_H__
#define __FILTER_H__

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


using namespace Gdiplus;

class Filter
{
public:
	Filter();
	~Filter();

	virtual void applyFilter(Bitmap * original, Bitmap* other, unsigned int radius) = 0;

private:
	unsigned int radius_;
};

#endif	// __FILTER_H__