#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include"InitMainWindow.h"
#include"MainWindowController.h"
#include"Constants.h"
#define MAX_LOADSTRING 17

// Глобальные переменные:
HINSTANCE hInst;   // текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
ATOM RegisterMainClassWindow(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	int num = LoadString(hInstance, IDS_APPL_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_MAINWINDOWS_TYPE, szWindowClass, MAX_LOADSTRING);
	RegisterMainClassWindow(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	//HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECTEXAMPLE));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		//{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		//}
	}

	return (int)msg.wParam;
}


ATOM RegisterMainClassWindow(HINSTANCE hInstance) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WHEAT));
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	DWORD err;
	UINT_PTR uNotifyParam = 0;
	UINT uNotifyCode = 0;
	static std::shared_ptr<MainWindowController> controller;
	switch (message)
	{
	case WM_CREATE:
		controller = std::make_shared<MainWindowController>(hInst, hWnd);
		controller->setupInitialState();
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case ID_SOFTINGSERVERSETTINGS_CERTIFICATES_LOCATIONS:
			controller->CreateSoftingServerCertificateLocationsDialog();
			break;
		case ID_SOFTINGSERVERSETTINGS_ENDPOINTSSETTINGS:
			controller->CreateSoftingServerEndPointsSettingsDialog();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_NOTIFY:
	{
		uNotifyParam = ((LPNMHDR)lParam)->idFrom;
		uNotifyCode = ((LPNMHDR)lParam)->code;
		switch (uNotifyCode) {
		case NM_RCLICK:
		{
			LPNMMOUSE lpnm = (LPNMMOUSE)lParam;
			if (lpnm->hdr.hwndFrom == controller->GetStatusBarHandler()) {
				switch (lpnm->dwItemSpec) {
				case 0:
					controller->CreateConnectionMenu(lpnm->pt);
					break;
				case 1:
					controller->CreateServiceMenu(lpnm->pt);
				}
			}
			return TRUE;
		}
			break;
		default:
			break;
		}
	}
	break;
	case WM_SIZE:
	{
		LONG width = LOWORD(lParam);
		LONG height = HIWORD(lParam);
		controller->ResizeStatusBar(height, width);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/*const char locList[] = "E:/MyProjects/first2019/Customers.csv";
	CSVParser<Customer> parser(locList);
	int count = 0;
	for (CSVParser<Customer>::const_iterator itr = parser.begin(); itr != parser.end(); ++itr) {
		count++;
		std::cout << *itr;
	}
	std::cout << std::endl;
	std::cout << count;*/