#include "BitmapImage.h"

BitmapImage::BitmapImage(Bitmap * bmap)
{
	_width = bmap->GetWidth();
	_height = bmap->GetHeight();

	BitmapData _bmD;
	bmap->LockBits(&Rect(0, 0, _width, _height), ImageLockModeRead, PixelFormat32bppARGB, &_bmD);
	
	BitmapDataPointer = &(_bmD.Scan0);	// store the address of the buffer pointer in the Bitmap object

	_stride = _bmD.Stride;
	//_scanLen = _bmD.Width * 4 + _stride; //_bmD.Width * 4 + _stride;

	_buffer = new byte[ abs(_stride) * _bmD.Height];		/* allocate memory with enough size for the bitmap */
	memcpy(_buffer, _bmD.Scan0, abs(_stride) * _bmD.Height);	/* copy image from Bitmap to My Image object */
	
	bmap->UnlockBits(&_bmD);

}

BitmapImage::~BitmapImage()
{
	delete[] _buffer;
}

GenericImage::Pixel BitmapImage::bGetPixel(int width, int height)
{
	if (width > _width || height > _height)
		throw("out of bounds coordinates");

	Pixel pixel;
	pixel.value = ((uint32_t*)_buffer + height * _scanLen + width);

	return pixel;
}