#include <Windows.h>

HINSTANCE g_hInstance;
HWND g_hWnd;
LPSTR g_lpszClass = (LPSTR)TEXT("������ ����");


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
		static ���� ( <-> �Լ� ������ ��������)
		�����Ϳ����� ����
		���α׷��� ����Ǵ� ������ �޸� ����
		�ش� ����(�Լ�) �������� ������ �����ϴ�.
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

	case WM_PAINT:	//������ ȭ���� �ٽ� �׷����� ��� �߻��ϴ� �޽���
		hdc = BeginPaint(g_hWnd, &ps);
		wsprintf(text, "hello,winMain!!");
		//TextOut(hdc, 10,10, "Hello, WinMain!!", 16);	//HDC ����̽����ؽ�Ʈ
		TextOut(hdc, 10, 10, text, strlen(text));	//HDC ����̽����ؽ�Ʈ

		wsprintf(text, "MousePosX : %d", mousePosX);
		TextOut(hdc, 10, 30, text, strlen(text));
		wsprintf(text, "MousePosY : %d", mousePosY);
		TextOut(hdc, 10, 50, text, strlen(text));
		wsprintf(text, "�� �� : %d", (dan)-1);
		TextOut(hdc, 10, 70, text, strlen(text));
		/*
			������ ���

			����1. ���콺 ��Ŭ�� �� ��´ܼ��� 1�� �þ��.
			����2. ���콺 ��Ŭ�� �� ��´ܼ��� 1�� �پ���.
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
