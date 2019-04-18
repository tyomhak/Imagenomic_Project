#include <Windows.h>
#include <gdiplus.h>
#include <string>
#include "resource.h"
#include <tchar.h>
#include <memory>
#include "BitmapImage.h"
#include "BW_Filter.h"


using namespace Gdiplus;


/*			global variables			*/
std::shared_ptr<Bitmap> visibleImage = nullptr;
std::shared_ptr<BitmapImage> original = nullptr;
std::shared_ptr<BitmapImage> filtered = nullptr;
std::shared_ptr<GenericFilter> currFilter = nullptr;

std::wstring imagePath;
bool clicked = false;
int radius = 1;

const int screenHeight = 600;



/*			function declarations		*/
std::wstring			getFilePath(HWND hwnd);
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
			if (visibleImage.get())
			{
				PAINTSTRUCT ps;
				HDC hdc;

				hdc = BeginPaint(hWnd, &ps);
				Gdiplus::Graphics graphics(hdc);

				BitmapImage* temp = filtered.get();//clicked ? original.get() : filtered.get();
				Bitmap paintBmap(temp->_width, temp->_height, temp->_stride, PixelFormat32bppARGB, temp->_buffer);

				int height = 600;
				int width = 1000;

				if (visibleImage.get())
				{
					float ratio = static_cast<float>(paintBmap.GetWidth()) / paintBmap.GetHeight();
					width = ratio * height;
				}

				// keeps the image inside the bounds
				Rect rectangle(40, 130, width > 1000 ? 1000 : width, height);
				graphics.DrawImage(&paintBmap, rectangle);


				EndPaint(hWnd, &ps);
			}
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
					if (currFilter.get())		
					{
						currFilter->filter(filtered.get());
						InvalidateRect(hWnd, NULL, true);
					}
					else
						MessageBox(NULL, L"Choose filter first", L"", NULL);
					break;
				}

				case BlurBoxr:
				{
					MessageBox(NULL, L"Changing filter to Box Blur", L"", NULL);	// TODO
					break;
				}

				case BWr:
				{
					currFilter = std::make_shared<BW_Filter>(BW_Filter(radius));					
					break;
				}

				case Radiuss:
				{
					MessageBox(NULL, L"Change the radius according to slider", L"", NULL);	// TODO
					break;
				}

																	
				case BrowseImage_b:									// choose original Image from file explorer//
				{
					imagePath					= getFilePath(hWnd);					
					visibleImage		= std::shared_ptr<Bitmap>(Bitmap::FromFile(imagePath.c_str()));
					original			= std::shared_ptr<BitmapImage>(new BitmapImage(visibleImage.get()));
					filtered			= std::shared_ptr<BitmapImage>(new BitmapImage(visibleImage.get()));	// temporary // change to copy from original to skip Bitmap heavy operations
					InvalidateRect(hWnd, NULL, true);						// redraw window (with new image)
					break;
				}
			}
			break;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);
			DestroyWindow(hWnd);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return FALSE;
		}
	}

	return FALSE;
}

std::wstring			getFilePath(HWND hwnd)
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

	return ofn.lpstrFile;
}