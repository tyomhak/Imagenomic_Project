#ifndef _GENERICIMAGE_H__
#define _GENERICIMAGE_H__

#include <memory>
#include <vector>

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


class GenericImage
{
public:
	GenericImage();
	virtual ~GenericImage();

	virtual byte* bGetPixel(int width, int height) = 0;


public :
	int		_width;
	int		_height;

	void* _buffer = nullptr;
};

#endif // _GENERICIMAGE__