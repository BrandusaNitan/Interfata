#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

HINSTANCE _hInstance;
int _nCmdShow;
MSG msg;

#define ID_FISIER				1201
#define ID_RANDOM				1202

#define IDC_AFISAREGRAF			1204
#define IDC_INSTRUCTIUNI		1206

int metoda_ins = 0;				//Monitor pentru metoda de insertie


LRESULT CALLBACK WndProc_AlegeInsertie(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, holdBrush;
	HPEN hPen, holdPen;

	switch (msg) {

	case WM_CREATE:

		CreateWindowW(L"Button", L"Alege Metoda insertie",WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			5, 1, 200, 90, hwnd, (HMENU)0, _hInstance, NULL);
		CreateWindowW(L"Button", L"Fisier",WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,	
			55, 25, 100, 30, hwnd, (HMENU)ID_FISIER, _hInstance, NULL);
		CreateWindowW(L"Button", L"Random",WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			55, 55, 100, 30, hwnd, (HMENU)ID_RANDOM, _hInstance, NULL);

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case ID_FISIER:
			metoda_ins = 1;
			break;
		case ID_RANDOM:
			metoda_ins = 2;
			break;

		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void Butoane(HWND hwnd)
{
	CreateWindow("BUTTON", "Afisare Grafic", WS_BORDER | WS_CHILD | WS_VISIBLE, 320, 10, 250, 30, hwnd, (HMENU)IDC_AFISAREGRAF, _hInstance, NULL);
	CreateWindow("BUTTON", "Instructiuni", WS_BORDER | WS_CHILD | WS_VISIBLE, 680, 10, 250, 30, hwnd, (HMENU)IDC_INSTRUCTIUNI, _hInstance, NULL);

	CreateWindowW(L"Button", L"Legenda ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,20, 250, 250, 270, hwnd, (HMENU)0, _hInstance, NULL);
	CreateWindowW(L"Button", L"Grafic ", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 310, 100, 630, 420, hwnd, (HMENU)0, _hInstance, NULL);

	CreateWindowW(L"static", L" >>> Vector", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 120, 302, 140, 25, hwnd, (HMENU)0, _hInstance, NULL);
	CreateWindowW(L"static", L" >>> Liste Simplu", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 120, 382, 140, 25, hwnd, (HMENU)0, _hInstance, NULL);
	CreateWindowW(L"static", L" >>> Liste Dublu", WS_CHILDWINDOW | WS_VISIBLE | WS_BORDER, 120, 462, 140, 25, hwnd, (HMENU)0, _hInstance, NULL);
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT Ps;
		hdc = BeginPaint(hWnd, &Ps);

		HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		HBRUSH hBrush, holdBrush;

		qLineColor = RGB(255, 255, 255);
		hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 40, 300, 100, 330);

		hBrush = CreateSolidBrush(RGB(0, 133, 0));
		holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 40, 380, 100, 410);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		holdBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, 40, 460, 100, 490);

		EndPaint(hWnd, &Ps);
		break;

	case WM_CREATE:
	{
		WNDCLASSW wc = { 0 };
		wc.lpszClassName = L"AlegeInsertie";
		wc.hInstance = _hInstance;
		wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		wc.lpfnWndProc = WndProc_AlegeInsertie;
		wc.hCursor = LoadCursor(0, IDC_ARROW);

		RegisterClassW(&wc);
		CreateWindowW(L"AlegeInsertie", NULL, WS_CHILD | WS_VISIBLE, 20, 10, 210, 95, hWnd, (HMENU)1, NULL, NULL);

		//Butoanele
		Butoane(hWnd);
	}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	_nCmdShow = nShowCmd;
	_hInstance = hInst;

	HBRUSH hh = CreateSolidBrush(RGB(160, 32, 240));

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = hh;
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = _hInstance;
	wClass.lpfnWndProc = (WNDPROC)WinProc;
	wClass.lpszClassName = "MainWnd";
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wClass);

	HWND hWnd = CreateWindowEx(NULL, "MainWnd", "RadixSort", WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 1000, 600, NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}