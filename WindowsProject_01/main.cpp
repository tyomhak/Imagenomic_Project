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

std::shared_ptr<Bitmap> visibleImage = nullptr;
std::shared_ptr<Bitmap> filteredImage = nullptr;
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
			PAINTSTRUCT ps;
			HDC hdc;

			hdc = BeginPaint(hWnd, &ps);

															// should move this part into a seperate function (OnPaint)
			Gdiplus::Graphics graphics(hdc);
			std::shared_ptr<Bitmap> paintImage = (clicked ? filteredImage : visibleImage);

			int height	= 600;
			int width	= 1000;

			if (paintImage.get())
			{
				float ratio = static_cast<float>(paintImage->GetWidth()) / paintImage->GetHeight();
				width		= ratio * height;
			}

					// keeps the image inside the bounds
			Rect rectangle(40, 130, width > 1000 ? 1000 : width, height);
			graphics.DrawImage(paintImage.get(), rectangle);


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
					if (currFilter.get())
					{
						std::wstring wtemp(imagePath.begin(), imagePath.end());
						filteredImage = std::shared_ptr<Bitmap>(Bitmap::FromFile(wtemp.c_str()));


						//filteredImage.reset<Bitmap>((visibleImage->Clone(Rect(0,0, visibleImage->GetWidth(), visibleImage->GetHeight()), visibleImage->GetPixelFormat())));
						currFilter->filter(filteredImage.get());
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
					std::wstring wtemp = getFilePath(hWnd);
					
					visibleImage		= std::shared_ptr<Bitmap>(Bitmap::FromFile(wtemp.c_str()));
					filteredImage		= std::shared_ptr<Bitmap>(Bitmap::FromFile(wtemp.c_str()));

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

std::wstring 		getFilePath(HWND hwnd)
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