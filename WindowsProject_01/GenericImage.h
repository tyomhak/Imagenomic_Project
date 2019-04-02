#pragma once

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")



class GenericImage
{
public:
	GenericImage(Bitmap *bmap);
	virtual ~GenericImage();



private:
	int _rOffset;
	int _gOffset;
	int _bOffset;


	Bitmap * _bmap;
	int		_pixelSize;
	int		_nWidth;
	int		_nHeight;


};

