#ifndef _GENERICIMAGE_H__
#define _GENERICIMAGE_H__

#include <memory>
#include <vector>

#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")



class GenericImage
{
public:
	struct Pixel
	{
		uint32_t* value;

		 /* getters */
		int getB()const { return *value & 0xff;	}
		int getG()const { return (*value & 0xff00) >> 8; }
		int getR()const { return (*value & 0xff0000) >> 16; }
		int getA()const { return (*value & 0xff000000) >> 24; }

		/* setters */
		void setR(int newValue)	{	*((byte*)value  ) = (byte)newValue; }
		void setG(int newValue) {	*((byte*)value+1) = (byte)newValue; }
		void setB(int newValue) {	*((byte*)value+2) = (byte)newValue; }
		void setA(int newValue) {	*((byte*)value+3) = (byte)newValue; }
	};

public:
	GenericImage();
	virtual ~GenericImage();

	virtual Pixel bGetPixel(int width, int height) = 0;
	

public :
	int		_width;
	int		_height;

	int _stride = 0;
	UINT _scanLen = 0;
	void* _buffer = nullptr;

};

#endif // _GENERICIMAGE__