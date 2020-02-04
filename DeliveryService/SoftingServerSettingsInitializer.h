#pragma once
#include<Windows.h>
#include<memory>
#include"ISoftingServerSettingsModuleOutput.h"

class SoftingServerSettingsInitializer final
{
public:
	static int CreateModule(HINSTANCE hInstance,  HWND parent, std::shared_ptr<ISoftingServerSettingsModuleOutput> output);
};