#include "BW_Filter.h"
#include <iostream>


BW_Filter::BW_Filter(int radius)
	: GenericFilter(radius)
{
}


void BW_Filter::filter(BitmapImage * out)		
{
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
