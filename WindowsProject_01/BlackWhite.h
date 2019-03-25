#pragma once
#include "GenericFilter.h"
#pragma comment( lib, "gdiplus.lib" ) // what is this??
#include <gdiplus.h>

class BlackWhite :
	public GenericFilter
{
public:
	BlackWhite(Gdiplus::Image* temp);
	~BlackWhite();

	void Filter();
};

