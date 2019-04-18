#include "BitmapImage.h"

BitmapImage::BitmapImage(Bitmap * bmap)
{
	_width = bmap->GetWidth();
	_height = bmap->GetHeight();

	BitmapData _bmD;
	bmap->LockBits(&Rect(0, 0, _width, _height), ImageLockModeWrite, PixelFormat32bppARGB, &_bmD);

	_buffer = new byte[abs(_bmD.Stride) * _bmD.Height];		/* allocate memory with enough size for the bitmap */
	memcpy(_buffer, _bmD.Scan0, abs(_bmD.Stride) * _bmD.Height);	/* copy image from Bitmap to My Image object */

	bmap->UnlockBits(&_bmD);
}

BitmapImage::~BitmapImage()
{
	delete[] _buffer;
}

byte * BitmapImage::bGetPixel(int width, int height)
{
	return nullptr;
}