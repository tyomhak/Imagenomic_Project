#include "GenericImage.h"
#include <iostream>


GenericImage::GenericImage(Bitmap *bmap)
	:	_bitMap(bmap)
{
	_width = bmap->GetWidth();
	_height = bmap->GetHeight();

	bmap->LockBits(&Rect(0, 0, _width, _height), ImageLockModeWrite, PixelFormat32bppARGB, &_bmD);
	_current = std::shared_ptr<byte>(((byte*)(void*)_bmD.Scan0));
	_pixelSize = 4;
	_stride = _bmD.Stride;//_pixelSize * _width;
}


GenericImage::~GenericImage()
{
	_bitMap->UnlockBits(&_bmD);
}

byte * GenericImage::GetPixel(int width, int height)
{
	if (width > _width || height > _height)
		throw("out of bounds");

	return (byte*)(void*)(_current.get() + height * _stride + width);
}
