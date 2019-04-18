#include "BW_Filter.h"
#include <iostream>


BW_Filter::BW_Filter(int radius)
	: GenericFilter(radius)
{
}


void BW_Filter::filter(BitmapImage * out)		
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


	for (unsigned int i = 0; i < out->_width; ++i)
	{
		for (unsigned int j = 0; j < out->_height; ++j)
		{
			BitmapImage::Pixel temp = out->bGetPixel(i, j);
			int avg = (temp.getR() + temp.getG() + temp.getB())/3;
			temp.setR(avg);
			temp.setG(avg);
			temp.setB(avg);
		}
	}
}
