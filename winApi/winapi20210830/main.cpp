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
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}