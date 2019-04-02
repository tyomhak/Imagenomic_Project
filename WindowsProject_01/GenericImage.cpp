#include "GenericImage.h"



GenericImage::GenericImage(Bitmap *bmap)
	:	_bmap(bmap)
{

	//BYTE* byteptr = (BYTE*)bmap.GetBits();

	////You can use other functions for HBITMAP and HGDIOBJ methods to find out the 
	////container for bitmap color table.
	////For instance when you use GDI and HBITMAPS, you should use
	////BYTE* byteptr = (BYTE*)(HBITMAPINFOHEADER + HBITMAPINFOHEADER->biSize);
	////simple pointer arithmetics

	//int pitch = bitmapzor.GetPitch(); //This is a pointer offset to get new line of the bitmap

	//for (int i = 0; i < bitmapzor.GetWidth(); i++)
	//	for (int j = 0; j < bitmapzor.GetHeight(); j++)
	//	{
	//		//pointer arithmetics to find (i,j) pixel colors:
	//		R = *(byteptr + pitch * j + 3 * i);
	//		G = *(byteptr + pitch * j + 3 * i + 1);
	//		B = *(byteptr + pitch * j + 3 * i + 2);

	//		//allter pixel G color:
	//		G = (int)((float)G*1.3);
	//		if (G > 255) G = 255;
	//		//write down the new G-Color
	//		*(byteptr + pitch * j + 3 * i + 1) = G;
	//	}
}


GenericImage::~GenericImage()
{
}
