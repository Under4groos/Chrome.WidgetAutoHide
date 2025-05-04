// Chrome.WidgetAutoHide.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

#define null 0
#define Time 250

RECT rect;
int width;
int height;
std::vector<HWND> windows = {};
HANDLE threadloop;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (!IsWindowVisible(hwnd))
		return true;
	wchar_t win_class[_MAX_PATH];
	if (!GetClassNameW(hwnd, win_class, _MAX_PATH))
		return true;
	if (wcscmp(win_class, L"Chrome_WidgetWin_1"))
		return true;
	if (!GetWindowRect(hwnd, &rect))
		return true;


	width = rect.right - rect.left;
	height = rect.bottom - rect.top;
	if (width == 389 && height == 268) {
		wcout << L"Hide: " << L"Window Handle: " << hwnd << L", Class Name: " << win_class << endl;
		cout << width << " " << height << endl;
		DestroyWindow(hwnd);
		ShowWindow(hwnd, SW_HIDE);
	}
	return TRUE;
}

//274 128
//Hide: Window Handle : 0000000000CD0C12, Class Name : Chrome_WidgetWin_1
//274 128
//Hide : Window Handle : 0000000000CD0C12, Class Name : Chrome_WidgetWin_1
//274 128
//Hide : Window Handle : 0000000000CD0C12, Class Name : Chrome_WidgetWin_1
//274 128
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268
//Hide : Window Handle : 00000000002C098E, Class Name : Chrome_WidgetWin_1
//389 268

DWORD WINAPI ThreadLoop(LPVOID lpParam) {
	while (true)
	{
		EnumWindows(EnumWindowsProc, null);
		Sleep(Time);
	}

}

void main_l() {
	threadloop = CreateThread(
		NULL,
		0,
		ThreadLoop,
		0,
		0,
		NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	CloseHandle(threadloop);
}

//int main()
//{
//	main_l();
//}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	main_l();
	return 0;
}