#pragma once
#include<Windows.h>
#include<CommCtrl.h>
#include<tchar.h>
#include "resource.h"
#include"Constants.h"
HWND CreateStatusBar(HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
void ResizeStatusBar(HWND hwnd);