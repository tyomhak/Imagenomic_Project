#include <Windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "resource.h"

Bitmap *visibleImage;
Bitmap *filteredImage;

// TESTING GDI+
void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	graphics.DrawLine(&pen, 0, 0, 200, 100);
}


BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Start GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


	// input of new image
	visibleImage = new Bitmap(L"Photo.JPG");


	HWND dialog{};

	dialog = CreateDialog(hInstance, MAKEINTRESOURCE(mainWindow), NULL, DialogProc);

	if (!dialog)
	{
		// Message box
		return 1;
	}

	ShowWindow(dialog, nCmdShow);

	MSG msg;

	while (GetMessage(&msg, 0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	// End GDI+
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}


BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	//	TESTING PURPOSES ONLY
	//Image image(L"Photo.JPG");
	
	 //draws the image in our Dialogue box
	// on our window 10 to right, 150 to bottom is the start of the input image
	



	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case applyFilterb:
		{
			MessageBox(NULL, L"Applying Filter", L"", NULL);				// TODO 
			//						// apply filter
			Graphics graphics(hwnd);
			//graphics.DrawImage(visibleImage, 10, 150);


			UINT PictureHeight = 700;
			UINT PictureWidth = (UINT)PictureHeight * ((float)visibleImage->GetWidth() / visibleImage->GetHeight());
			Rect destinationRect(10, 120, PictureHeight, PictureWidth);
			graphics.DrawImage(
				visibleImage,
				destinationRect,
				0, 0,
				visibleImage->GetHeight(), visibleImage->GetWidth(),
				UnitPixel
			);
			return 0;
		}
		case BlurBoxr:
			MessageBox(NULL, L"Changing filter to Box Blur", L"", NULL);	// TODO
			return 0;

		case BWr:
			MessageBox(NULL, L"Changing filter to B&W", L"", NULL);		// TODO
			return 0;


		case Radiuss:
			MessageBox(NULL, L"Change the radius according to slider", L"", NULL);	// TODO
			return 0;
		}

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return TRUE;
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return TRUE;
	}

	return FALSE;
}
