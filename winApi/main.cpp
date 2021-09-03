//main.cpp

/*
	Win32 API
	api = Application Programming Interface
	운영체제가 응용 프로그램 개발을 위해 제공하는 함수의 집합

	하드웨어 ---------------운영체제(Windows)-------------응용프로그램
							(API 함수)

	apientry = 딱히 의미는 없음
	HINSTANCE = H - handle(핸들) : 각 윈도우 객체를 구분하는 인덱스 (정수)	┐
				Instance : 메모리 상에 만들어진 객체						┴인스턴스의 핸들 이라는 뜻
	LPSTR = char형의 포인터 문자열

	Message (메시지) : 윈도우에서 발생하는 이벤트 운영체제가 윈도우에 전달하는 데이터 모음
*/

#include <Windows.h>

//전역변수
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("윈메인의 시작");





LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


struct rect
{
	int x, y;
	int size;
};


void DrawRect(HDC hdc, int x, int y, int size)
{
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x, y + size);
	LineTo(hdc, x + size, y + size);
	LineTo(hdc, x + size, y);
	LineTo(hdc, x, y);
}


int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpszCmdParam, int nCmdShow)
{
	//윈도우를 생성하기 위한 기본 셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 핸들 형변환
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;	//콜백함수 (함수의 주소만 알려주고 스스로 실행 시기를 판단)함수포인터
	wndClass.lpszClassName = g_lpszClass;//sz붙어있는건 문자열
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW; // bit연산

	//윈도우 클래스 등록
	RegisterClass(&wndClass); //


	//윈도우 생성,
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 1200, 900, NULL, NULL, g_hInstance, NULL);

	//윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	//메시지 큐에 있는 메시지 처리
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

	static int pushKey = 0;


	static rect player;
	static rect car[2];

	static bool playerSt = 0;



	switch (iMessage)
	{
	case WM_CREATE:
		car[0].x = 200;
		car[0].y = 200;
		car[0].size = 200;
		car[1].x = 500;
		car[1].y = 200;
		car[1].size = 200;
		player.x = car[0].x + (car[0].size / 4);
		player.y = car[0].y + (car[0].size / 4);
		player.size = 100;
		
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		wsprintf(text, "pushKey %d", pushKey);
		TextOut(hdc, 200, 10, text, strlen(text));

		DrawRect(hdc, car[0].x, car[0].y, car[0].size);
		DrawRect(hdc, car[1].x, car[1].y, car[1].size);
		DrawRect(hdc, player.x, player.y, player.size);


		EndPaint(g_hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_RIGHT)
		{
			if (playerSt == 0)
			{
				if ((car[0].y + car[0].size <= car[1].y + car[1].size && car[0].y + car[0].size >= car[1].y) || (car[0].y <= car[1].y + car[1].size && car[0].y >= car[1].y))
				{
					if (car[0].x + car[0].size < car[1].x)
					{
						car[0].x += 5;
						if (car[0].x > player.x)
						{
							player.x += 5;
						}
					}
					else
					{
						if (player.x + player.size < car[0].x + car[0].size)
						{
							player.x += 5;
						}
						else
						{
							player.x = car[1].x + (car[1].size / 4);
							player.y = car[1].y + (car[1].size / 4);
							playerSt = 1;
						}
					}
				}
				else
				{
					car[0].x += 5;
					if (car[0].x > player.x)
					{
						player.x += 5;
					}
				}
			}
			else
			{
				car[1].x += 5;
				if (car[1].x > player.x)
				{
					player.x += 5;
				}
			}
			pushKey += 1;
		}
		
		InvalidateRect(g_hWnd, NULL, true);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}