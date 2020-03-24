#include"stdafx.h"
#include"WIN.h"
#include<iostream>
#include<vector>
using namespace std;
class asd
{
public:
	void point(HDC hdc);
	void zp(POINTS a);
	static vector<asd*>ppp;
protected:
	vector<POINTS>save;
};
vector<asd*>asd::ppp;
void asd::point(HDC hdc)
{
	int i = 0, j = 0;
	if (asd::ppp.size() != 0)
	{
		for (; i<asd::ppp.size(); i++)
		{
			MoveToEx(hdc, asd::ppp[i]->save[i].x, asd::ppp[i]->save[i].y, NULL);
			for (; j<asd::ppp[j]->save.size(); j++)
			{
				LineTo(hdc, asd::ppp[i]->save[j].x, asd::ppp[i]->save[j].y);
				MoveToEx(hdc, asd::ppp[i]->save[j].x, asd::ppp[i]->save[j].y, NULL);
			}
			j = 0;
		}
	}
}

void asd::zp(POINTS a)
{
	save.push_back(a);
}

static TCHAR szAppName[] = TEXT("IDR_MENU");
asd bb;
POINTS pt;
int i = 0;
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	switch (message)
	{
	case WM_CREATE:
		rect.left = LOWORD(lParam);
		rect.top = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		bb.point(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//这里是我想通过菜单来控制清除的，实现不了，没用 没反应
		case ID_EDIT_OPEN:
			RedrawWindow(hwnd, &rect, 0, RDW_ERASE);
			return 0;
		}
		return 0;
	case WM_LBUTTONDOWN:
		pt = MAKEPOINTS(lParam);
		asd::ppp.push_back(new asd);
		return 0;
	case WM_LBUTTONUP:
		++i;
		return 0;
	case WM_MOUSEMOVE:
		if (wParam == MK_LBUTTON)
		{
			POINTS p;
			p = MAKEPOINTS(lParam);
			hdc = GetDC(hwnd);
			MoveToEx(hdc, pt.x, pt.y, NULL);
			LineTo(hdc, p.x, p.y);
			pt = p;
			asd::ppp[i]->zp(p);
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstace, HINSTANCE hp, PSTR szCmd, int iCmd)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS w;
	w.style = CS_HREDRAW;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	w.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	w.hInstance = hinstace;
	w.lpfnWndProc = WndProc;
	w.lpszClassName = szAppName;
	w.lpszMenuName = szAppName;
	RegisterClass(&w);
	hwnd = CreateWindow(szAppName, TEXT("b"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hinstace, NULL);
	ShowWindow(hwnd, iCmd);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}