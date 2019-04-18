#pragma once
#include "GenericImage.h"

class BitmapImage :
	public GenericImage
{
public:
	BitmapImage(Bitmap* bmap);
	~BitmapImage();

	byte* bGetPixel(int width, int height) override;
};

