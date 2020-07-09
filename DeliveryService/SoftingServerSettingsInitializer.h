#pragma once
#include<Windows.h>
#include<memory>
#include"ConnectionAttributes.h"

class SoftingServerSettingsInitializer final
{
public:
	static int CreateModule(HINSTANCE hInstance,  HWND parent);
};