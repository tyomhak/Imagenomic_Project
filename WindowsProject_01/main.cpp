#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include "resource.h"
#include <tchar.h>
#include <atlstr.h>	// for CW2A conversion
#include <memory>
#include "GenericFilter.h"
#include "BW_Filter.h"

using namespace Gdiplus;


/*			global variables			*/

Bitmap* visibleImage;
Bitmap* filteredImage;
GenericFilter* CurrFilter;
std::string imagePath;
bool clicked = false;

const int screenHeight = 600;



/*			function declarations		*/
std::string			getFilePath(HWND hwnd);
LRESULT CALLBACK	DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int		WINAPI		WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);




/*			function definitions		*/

int WINAPI			WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Start GDI+
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	HWND dialog{};

	dialog = CreateDialog(hInstance, MAKEINTRESOURCE(mainWindow), NULL, DialogProc);

	// Error handling
	if (!dialog)
	{
		return 1;
	}

	ShowWindow(dialog, nCmdShow);

	MSG msg;								// Message Handling Loop
	while (GetMessage(&msg, 0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	// End GDI+
	GdiplusShutdown(gdiplusToken);
	return (int)msg.wParam;
}

LRESULT CALLBACK	DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case WM_PAINT:										// All drawing must be in this case
		{
			PAINTSTRUCT ps;
			HDC hdc;

			hdc = BeginPaint(hWnd, &ps);
			Gdiplus::Graphics graphics(hdc);
			Gdiplus::Bitmap* paintImage = (clicked ? filteredImage : visibleImage);

			int height	= 600;
			int width	= 1000;

			if (paintImage)
			{
				float ratio = static_cast<float>(paintImage->GetWidth()) / paintImage->GetHeight();
				width		= ratio * height;
			}

			Rect rectangle(40, 130, width > 1000 ? 1000 : width, height);			// keeps the image inside the bounds
			graphics.DrawImage(paintImage, rectangle);
			//graphics.DrawImage(paintImage, 40, 130, width, height);			// wide image not inside bounds
			EndPaint(hWnd, &ps);
			break;
		}
														 
															// show filtered image //											
		case WM_LBUTTONDOWN:								// mouse left button down
		{
			clicked = true;
			InvalidateRect(hWnd, NULL, true);				// redraw window
			break;
		}
											
															// show original image //				
		case WM_LBUTTONUP:									// mouse left button up
		{
			clicked = false;
			InvalidateRect(hWnd, NULL, true);				// redraw window
			break;
		}


		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case applyFilterb:
				{
					MessageBox(NULL, L"Applying Filter", L"", NULL);	// TODO
																		// apply filter
					return 0;
				}

				case BlurBoxr:
				{
					MessageBox(NULL, L"Changing filter to Box Blur", L"", NULL);	// TODO
					return 0;
				}

				case BWr:
				{

					//MessageBox(NULL, L"Changing filter to B&W", L"", NULL);		// TODO
					return 0;
				}

				case Radiuss:
				{
					MessageBox(NULL, L"Change the radius according to slider", L"", NULL);	// TODO
					return 0;
				}

																	
				case BrowseImage_b:									// choose original Image from file explorer//
				{

					std::string temp	= getFilePath(hWnd);
					imagePath			= temp;
					std::wstring wtemp(temp.begin(), temp.end());
					visibleImage		= Bitmap::FromFile(wtemp.c_str());

					InvalidateRect(hWnd, NULL, true);						// redraw window (with new image)
					return 0;
				}
			}
		}

		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			if (visibleImage)
				delete visibleImage;
			if (filteredImage)
				delete filteredImage;
			return TRUE;
			break;
		}

		case WM_DESTROY:
		{
			if (visibleImage)
				delete visibleImage;
			if (filteredImage)
				delete filteredImage;

			PostQuitMessage(0);
			return TRUE;
		}
	}

	return FALSE;
}

std::string			getFilePath(HWND hwnd)
{
	wchar_t filename[MAX_PATH];
	OPENFILENAME ofn;

	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = _T("Any File\0*.*\0");
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = _T("Select the Image...");
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn))
		throw "Invalid File input";

	return std::string(CW2A(ofn.lpstrFile));
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