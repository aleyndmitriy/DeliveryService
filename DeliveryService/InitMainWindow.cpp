#include"InitMainWindow.h"

HWND CreateStatusBar(HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts)
{
	//https://docs.microsoft.com/en-us/windows/win32/controls/status-bar-reference
	
	HWND hwndStatus;
	RECT rcClient;
	HLOCAL hloc;
	PINT paParts = NULL;
	int i, nWidth;
	INITCOMMONCONTROLSEX iccex;
	iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccex.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&iccex);
	hwndStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0, hwndParent, (HMENU)idStatus, hinst, NULL);
	
	// Get the coordinates of the parent window's client area.
	GetClientRect(hwndParent, &rcClient);

	// Allocate an array for holding the right edge coordinates.
	paParts = (PINT)malloc(sizeof(int) * cParts);
	if (paParts == NULL) {
		return NULL;
	}
	// Calculate the right edge coordinate for each part, and
	// copy the coordinates to the array.
	nWidth = rcClient.right / cParts;
	int rightEdge = nWidth;
	for (i = 0; i < cParts; i++) {
		*(paParts + i) = rightEdge;
		rightEdge += nWidth;
	}
	// Tell the status bar to create the window parts.
	SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)
		paParts);

	// Free the array, and return.
	free(paParts);
	SendMessage(hwndStatus, SB_SETTEXT, MAKEWPARAM(0, 0), (WPARAM)NETWORK_STATUSBAR_DEFAULT_STATE);
	SendMessage(hwndStatus, SB_SETTEXT, MAKEWPARAM(1, 0), (WPARAM)SERVICE_STATUSBAR_DEFAULT_STATE);
	return hwndStatus;
}

void ResizeStatusBar(HWND hwnd)
{
	RECT rcClient;
	int cParts = 0;
	PINT paParts = NULL;
	int i, nWidth;
	GetClientRect(GetParent(hwnd), &rcClient);
	cParts = (int)SendMessage(hwnd, SB_GETPARTS, (WPARAM)0, (LPARAM)0);
	if (cParts <= 0) {
		return;
	}
	paParts = (PINT)malloc(sizeof(int) * cParts);
	if (paParts == NULL) {
		return;
	}
	nWidth = rcClient.right / cParts;
	int rightEdge = nWidth;
	for (i = 0; i < cParts; i++) {
		*(paParts + i) = rightEdge;
		rightEdge += nWidth;
	}
	// Tell the status bar to create the window parts.
	SendMessage(hwnd, SB_SETPARTS, (WPARAM)cParts, (LPARAM)
		paParts);

	// Free the array, and return.
	free(paParts);
}
