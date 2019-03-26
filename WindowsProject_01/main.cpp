#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include "resource.h"
#include <tchar.h>
#include <atlstr.h>	// for CW2A conversion
using namespace Gdiplus;



Bitmap *visibleImage;
Bitmap *filteredImage;

std::string getPath(HWND hwnd)
{
	wchar_t filename[MAX_PATH];
	OPENFILENAME ofn;

	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = _T("Any File\0*.*\0");
	ofn.lpstrFile	= filename;
	ofn.nMaxFile	= MAX_PATH;
	ofn.lpstrTitle	= _T("Select the Image...");
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn))
		throw "Invalid File input";

	return std::string(CW2A(ofn.lpstrFile));
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
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case applyFilterb:
		{
			MessageBox(NULL, L"Applying Filter", L"", NULL);	// TODO
																// apply filter
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

		case BrowseImage_b:
		{
			// choose original Image
			std::string temp = getPath(hwnd);
			std::wstring wtemp(temp.begin(), temp.end());
			visibleImage = Bitmap::FromFile(wtemp.c_str());


			// Draws the image in the dialog box
			// Problematic: does not remove the old image once updated
			Graphics graphics(hwnd);
			UINT PictureHeight = 700;
			UINT PictureWidth = (UINT)PictureHeight * ((float)visibleImage->GetWidth() / visibleImage->GetHeight());
			Rect destinationRect(20, 150, PictureHeight, PictureWidth);
			graphics.DrawImage(
				visibleImage,
				destinationRect,
				0, 0,
				visibleImage->GetHeight(), visibleImage->GetWidth(),
				UnitPixel
			);


			return 0;
		}
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





/*			// FOR FUTURE INSPECTION	//


			int _pixelSize = 3;
			byte* _current = (byte*)(void*)bmData.Scan0;
			int _nWidth = bmData.Width * _pixelSize;
			int _nHeight = bmData.Height;




			void SetColor(, Color color)
			{
				_current[0] = color.R;
				_current[1] = color.G;
				_current[2] = color.B;
			}



			for (int y = 0; y < _nHeight; y++)
			{
				for (int x = 0; x < _nWidth; x++)
				{
					if (x % _pixelSize == 0 || x == 0)
					{
						SetColor(new Color.Black);
					}
					_current++;
				}
			}


			//////////////////


			BitmapData bmData;

			Rect rec(0, 0, visibleImage->GetWidth(), visibleImage->GetHeight());

			visibleImage->LockBits(&rec, ImageLockModeRead, PixelFormat32bppARGB, &bmData);

			INT iStride = abs(bmData.Stride);
			HBITMAP img = NULL;
			visibleImage->GetHBITMAP(0, &img);

			SendDlgItemMessage(hwnd, ImageWindow, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)img);


*/