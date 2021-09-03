//main.cpp

/*
	Win32 API
	api = Application Programming Interface
	�ü���� ���� ���α׷� ������ ���� �����ϴ� �Լ��� ����

	�ϵ���� ---------------�ü��(Windows)-------------�������α׷�
							(API �Լ�)

	apientry = ���� �ǹ̴� ����
	HINSTANCE = H - handle(�ڵ�) : �� ������ ��ü�� �����ϴ� �ε��� (����)	��
				Instance : �޸� �� ������� ��ü						���ν��Ͻ��� �ڵ� �̶�� ��
	LPSTR = char���� ������ ���ڿ�

	Message (�޽���) : �����쿡�� �߻��ϴ� �̺�Ʈ �ü���� �����쿡 �����ϴ� ������ ����
*/

#include <Windows.h>

//��������
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("�������� ����");





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
	//�����츦 �����ϱ� ���� �⺻ ����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �ڵ� ����ȯ
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;	//�ݹ��Լ� (�Լ��� �ּҸ� �˷��ְ� ������ ���� �ñ⸦ �Ǵ�)�Լ�������
	wndClass.lpszClassName = g_lpszClass;//sz�پ��ִ°� ���ڿ�
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW; // bit����

	//������ Ŭ���� ���
	RegisterClass(&wndClass); //


	//������ ����,
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 100, 100, 1200, 900, NULL, NULL, g_hInstance, NULL);

	//������ ���
	ShowWindow(g_hWnd, nCmdShow);

	//�޽��� ť�� �ִ� �޽��� ó��
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