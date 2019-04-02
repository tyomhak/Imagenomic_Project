#ifndef _BW_FILTER_H_
#define _BW_FILTER_H_

#include <Windows.h>
#include <gdiplus.h>

#include "GenericFilter.h"
class BW_Filter :
	public GenericFilter
{
public:
	BW_Filter(int radius);
	~BW_Filter();

	void filter(Bitmap* in, Bitmap* out)const override;
};

#endif // _BW_FILTER_H_