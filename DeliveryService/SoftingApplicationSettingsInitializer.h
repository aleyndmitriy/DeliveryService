#pragma once
#include<Windows.h>
#include<memory>

class SoftingApplicationSettingsInitializer final
{
public:
	static int CreateModule(HINSTANCE hInstance, HWND parent);
};