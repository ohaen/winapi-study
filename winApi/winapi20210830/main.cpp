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
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}