#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT messaege, WPARAM wParam, LPARAM IParam);
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR IpszCmdLine, int nCmdShow){
	HWND			hwnd;
	MSG				msg;
	WNDCLASSEX	WndClass;

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hinstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = "EasyText";
	WndClass.hIconSm = 0;

	RegisterClassEx(&WndClass);

	hwnd = CreateWindow(
		"EasyText",
		"Practice1a",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinstance,
		NULL
		);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM IParam) {
	HDC hdc;
	RECT rect;
	PAINTSTRUCT ps;
	LPCSTR szMsg1 = "I love Window Programming!";
	LPCSTR szMsg2 = "키보드가 눌러졌습니다.";
	LPCSTR szMsg3 = "키보드가 떼어졌습니다.";
	LPCSTR szMsg4 = "마우스가 눌러졌습니다.";
	LPCSTR szMsg5 = "마우스가 이동 중입니다.";
	LPSTR szMsg6 = new char[10];

	switch(message) {
		case WM_CREATE:
			break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			TextOut(hdc, 10, 10, szMsg1, strlen(szMsg1));
			EndPaint(hwnd, &ps);
			break;
		case WM_KEYDOWN:
			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rect);
			DrawText(hdc, szMsg2, strlen(szMsg2), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ReleaseDC(hwnd, hdc);
			break;
		case WM_KEYUP:
			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rect);
			DrawText(hdc, szMsg3, strlen(szMsg3), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ReleaseDC(hwnd, hdc);
			break;
		case WM_LBUTTONDBLCLK:
			MessageBox(hwnd, "마우스 더블 클릭!", "마우스 메시지", MB_OK | MB_ICONASTERISK);
			break;
		case WM_LBUTTONDOWN:
			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rect);
			DrawText(hdc, szMsg4, strlen(szMsg4), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			POINT MousePoint;
			MousePoint.x = LOWORD(IParam);
			MousePoint.y = HIWORD(IParam);
			wsprintf(szMsg6, "X:%ld, Y:%ld", MousePoint.x, MousePoint.y);
			TextOut(hdc, MousePoint.x, MousePoint.y, szMsg6, strlen(szMsg6));
			ReleaseDC(hwnd, hdc);
			break;
		case WM_LBUTTONUP:
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		case WM_MOUSEMOVE:
			hdc = GetDC(hwnd);
			GetClientRect(hwnd, &rect);
			DrawText(hdc, szMsg5, strlen(szMsg5), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ReleaseDC(hwnd, hdc);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, IParam);
	}
	return 0;
}