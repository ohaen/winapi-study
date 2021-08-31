#include <Windows.h>

HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("윈도우 시작");


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE hPrevInstance, LPSTR _lpszParam, int nCmdShow)
{
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClass(&wndClass);

	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 1200, 900, NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);

	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

	}

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	char text[128];
	/*
		static 변수 ( <-> 함수 내에서 변수선언)
		데이터영역에 선언
		프로그램이 종료되는 시점에 메모리 해제
		해당 영역(함수) 내에서만 접근이 가능하다.
	*/
	static int mousePosX = 0, mousePosY = 0;
	static int dan = 1;


	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		if (dan <= 9)
		{
		dan += 1;
		}

		break;
	case WM_RBUTTONDOWN:
		if (dan > 1)
		{
		dan -= 1;
		}
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);

		break;

	case WM_PAINT:	//윈도우 화면이 다시 그려지는 경우 발생하는 메시지
		hdc = BeginPaint(g_hWnd, &ps);
		wsprintf(text, "hello,winMain!!");
		//TextOut(hdc, 10,10, "Hello, WinMain!!", 16);	//HDC 디바이스컨텍스트
		TextOut(hdc, 10, 10, text, strlen(text));	//HDC 디바이스컨텍스트

		wsprintf(text, "MousePosX : %d", mousePosX);
		TextOut(hdc, 10, 30, text, strlen(text));
		wsprintf(text, "MousePosY : %d", mousePosY);
		TextOut(hdc, 10, 50, text, strlen(text));
		wsprintf(text, "단 수 : %d", (dan)-1);
		TextOut(hdc, 10, 70, text, strlen(text));
		/*
			구구단 출력

			과제1. 마우스 좌클릭 시 출력단수가 1씩 늘어난다.
			과제2. 마우스 우클릭 시 출력단수가 1씩 줄어든다.
		*/
		for (int i = 1; i < dan; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				wsprintf(text, "%d X %d = %d", i, j, i*j);
				TextOut(hdc, ((i*80)+20), ((j*20)+90), text, strlen(text));
			}
		}


		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
