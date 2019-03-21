#include <Windows.h>
#include "resource.h"


BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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

	return (int)msg.wParam;
}


BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		//MessageBox(NULL, "Working", "DialogWindow", NULL);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case applyFilterb:
			MessageBox(NULL, "Applying Filter", "", NULL);				// TODO 
			//						// apply filter
			return 0;

		case BlurBoxr:
			MessageBox(NULL, "Changing filter to Box Blur", "", NULL);	// TODO
			return 0;

		case BWr:
			MessageBox(NULL, "Changing filter to B&W", "", NULL);		// TODO
			return 0;


		case Radiuss:
			MessageBox(NULL, "Change the radius according to slider", "", NULL);	// TODO
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
