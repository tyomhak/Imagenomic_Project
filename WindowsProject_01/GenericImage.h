#pragma once

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")



class GenericImage
{
public:
	GenericImage();
	~GenericImage();

	//virtual int GetPixelR(int i, int j);
	//virtual int GetPixelG(int i, int j);
	//virtual int GetPixelB(int i, int j);


	//virtual int SetPixelR(int i, int j);
	//virtual int SetPixelG(int i, int j);
	//virtual int SetPixelB(int i, int j);

private:
	int rOffset;
	int gOffset;
	int bOffset;
};

