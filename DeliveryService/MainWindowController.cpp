#include"MainWindowController.h"
#include"InitMainWindow.h"
#include"MainWindowPresenter.h"
MainWindowController::MainWindowController(HINSTANCE hInstance, HWND hwnd):m_hInstance(hInstance), m_hWnd(hwnd), m_hStatusBar(NULL), m_isBind(0), m_isService(0), m_ptrPresenter(nullptr)
{

}


MainWindowController::~MainWindowController()
{
	m_hInstance = nullptr;
	m_hWnd = nullptr;
	m_ptrPresenter.reset();
}

void MainWindowController::setupInitialState()
{
	CreateStatusBar();
	m_ptrPresenter = std::make_shared<MainWindowPresenter>();
	m_ptrPresenter->SetViewInput(shared_from_this());
	m_ptrPresenter->viewIsReady();
}

void MainWindowController::WarningMessage(std::string message)
{
	MessageBox(m_hWnd, TEXT(message.c_str()), "Warning", MB_ICONWARNING);
}

void MainWindowController::ErrorMessage(std::string message)
{
	MessageBox(m_hWnd, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
}

void MainWindowController::StartLoading()
{
	HCURSOR hCurs = LoadCursor(m_hInstance, IDC_WAIT);
	SetCursor(hCurs);
}

void MainWindowController::StopLoading()
{
	HCURSOR hCurs = LoadCursor(NULL, IDC_ARROW);
	SetCursor(hCurs);
}

HWND MainWindowController::GetWindowHandle()
{
	return m_hWnd;
}

HINSTANCE MainWindowController::GetAppInstance()
{
	return m_hInstance;
}

void MainWindowController::CreateStatusBar()
{
	m_hStatusBar = ::CreateStatusBar(m_hWnd, IDD_STATUS_BAR, m_hInstance, 4);
}

HWND MainWindowController::GetStatusBarHandler() const
{
	return m_hStatusBar;
}

void MainWindowController::ResizeStatusBar(long height, long width)
{
	SendMessage(m_hStatusBar, WM_SIZE, SIZE_RESTORED, MAKELPARAM(width, height));
	::ResizeStatusBar(m_hStatusBar);
}

void MainWindowController::CreateConnectionMenu(POINT pt)
{
	DWORD err;
	BOOL res = 0;
	HMENU hMenu = CreateMenu();
	HMENU hMenuPopup = CreatePopupMenu();
	HANDLE hImg = LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_CONNECTION_BITMAP), IMAGE_BITMAP, 25, 25, LR_DEFAULTCOLOR);
	MENUITEMINFO item = { 0 };

	item.cbSize = sizeof(MENUITEMINFO);
	item.fMask = MIIM_BITMAP | MIIM_STRING | MIIM_ID | MIIM_SUBMENU;
	item.fType = MFT_BITMAP | MFT_STRING | IMFT_SUBMENU;
	TCHAR title[MAX_MENU_TITLE_LENGTH];
	if (m_isBind == 0) {
		_tcscpy_s(title, MAX_MENU_TITLE_LENGTH, NETWORK_MENU_CHOOSE_CONNECTION_INTERFACE);
		item.wID = (UINT)IDD_MENU_CONNECTIONS_IP_LIST;
	}
	else if (m_isBind > 0) {
		_tcscpy_s(title, MAX_MENU_TITLE_LENGTH, NETWORK_MENU_CLOSE_CONNECTION);
		item.wID = (UINT)IDD_MENU_CONNECTION_CLOSE;
	}
	else {
		_tcscpy_s(title, MAX_MENU_TITLE_LENGTH, NETWORK_MENU_ERROR_CONNECTION);
		item.wID = (UINT)IDD_MENU_CONNECTION_ERROR;
	}

	item.hbmpItem = (HBITMAP)hImg;
	item.dwTypeData = title;
	if (!InsertMenuItem(hMenuPopup, 0, TRUE, &item)) {
		err = GetLastError();
		return;
	}
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenuPopup, NULL);
	ClientToScreen(m_hStatusBar, (LPPOINT)&pt);
	res = TrackPopupMenuEx(hMenuPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD,
		pt.x, pt.y, GetParent(m_hStatusBar), NULL);
	if (!res) {
		err = GetLastError();
		DestroyMenu(hMenu);
		DestroyMenu(hMenuPopup);
	}
	else {
		HMENU hSubMenu = GetSubMenu(hMenu, 0);
		DestroyMenu(hMenu);
		switch (res) {
		case IDD_MENU_CONNECTIONS_IP_LIST:
			m_ptrPresenter->GetIpAddress();
			break;
		default:
			break;
		}
	}
} 

void MainWindowController::CreateServiceMenu(POINT pt)
{
	DWORD err;
	BOOL res = 0;
	HMENU hMenu = CreateMenu();
	HMENU hMenuPopup = CreatePopupMenu();
	HANDLE hImg = LoadImage(m_hInstance, MAKEINTRESOURCE(IDB_CONNECTION_BITMAP), IMAGE_BITMAP, 25, 25, LR_DEFAULTCOLOR);
	MENUITEMINFO item = { 0 };

	item.cbSize = sizeof(MENUITEMINFO);
	item.fMask = MIIM_BITMAP | MIIM_STRING | MIIM_ID | MIIM_SUBMENU;
	item.fType = MFT_BITMAP | MFT_STRING | IMFT_SUBMENU;
	TCHAR title[MAX_MENU_TITLE_LENGTH];
	if (m_isService == 0) {
		_tcscpy_s(title, MAX_MENU_TITLE_LENGTH, SERVICE_MENU_START);
		item.wID = (UINT)IDD_MENU_SERVICE_START;
	}
	else if (m_isService > 0) {
		_tcscpy_s(title, MAX_MENU_TITLE_LENGTH, SERVICE_MENU_STOP);
		item.wID = (UINT)IDD_MENU_SERVICE_STOP;
	}
	else {
		_tcscpy_s(title, MAX_MENU_TITLE_LENGTH, SERVICE_MENU_ERROR);
		item.wID = (UINT)IDD_MENU_SERVICE_ERROR;
	}

	item.hbmpItem = (HBITMAP)hImg;
	item.dwTypeData = title;
	if (!InsertMenuItem(hMenuPopup, 0, TRUE, &item)) {
		err = GetLastError();
		return;
	}
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hMenuPopup, NULL);
	ClientToScreen(m_hStatusBar, (LPPOINT)&pt);
	res = TrackPopupMenuEx(hMenuPopup, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD,
		pt.x, pt.y, GetParent(m_hStatusBar), NULL);
	if (!res) {
		err = GetLastError();
		DestroyMenu(hMenu);
		DestroyMenu(hMenuPopup);
	}
	else {
		HMENU hSubMenu = GetSubMenu(hMenu, 0);
		DestroyMenu(hMenu);
		switch (res) {
		case IDD_MENU_SERVICE_START:
			
			break;
		default:
			break;
		}
	}
}

void MainWindowController::CreateSoftingServerCertificateLocationsDialog()
{
	m_ptrPresenter->CreateApplicationSettingsModule();
}

void MainWindowController::CreateSoftingServerEndPointsSettingsDialog()
{
	m_ptrPresenter->CreateServiceSettingsModule();
}
