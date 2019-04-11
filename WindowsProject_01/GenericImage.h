#ifndef _GENERICIMAGE_H__
#define _GENERICIMAGE_H__

#include <memory>
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


class GenericImage
{
public:
	GenericImage(Bitmap *bmap);
	~GenericImage();

	//virtual
	byte* GetPixel(int width, int height);


public :
	std::shared_ptr<Bitmap> _bitMap;
	BitmapData _bmD;
	
	int		_pixelSize;
	int		_width;
	int		_height;
	int _stride;

	byte* _current;
};

#endif // _GENERICIMAGE__