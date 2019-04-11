#include "BW_Filter.h"
#include <iostream>


BW_Filter::BW_Filter(int radius)
	: GenericFilter(radius)
{
}


void BW_Filter::filter(Bitmap * out)		
{
	// switch commented and uncommented parts when GetPixel() is fixed

	//GenericImage image(out);

	//for (int i = 0; i < 100; ++i)
	//{
	//	for (int j = 0; j < 100; ++j)
	//	{
	//		byte* pix = image.GetPixel(i, j);
	//		int avg = (pix[0] + pix[1] + pix[2])/3;
	//		pix[0] = pix[1] = pix[2] = (byte)avg;
	//	}
	//}




	BitmapData bmD;
	out->LockBits(&Rect(0, 0, out->GetWidth(), out->GetHeight()), ImageLockModeWrite, PixelFormat32bppARGB, &bmD);

	int _pixelSize = 4;
	byte* _current = (byte*)(void*)bmD.Scan0;


	// grayscale
	for (int i = 0; i < bmD.Width * bmD.Height; ++i)
	{
		int avg = (_current[0] + _current[1] + _current[2])/3;
		_current[0] = _current[1] = _current[2] = avg;

		_current += _pixelSize;
	}

	out->UnlockBits(&bmD);
	
}
