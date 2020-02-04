#pragma once
#include<Windows.h>
#include<memory>
#include"ISoftingEndPointSettingsModuleOutput.h"

class SoftingEndPointSettingsModuleInitializer final {
public:
	static int CreateModule(HINSTANCE hInstance, HWND parent, std::shared_ptr<ISoftingEndPointSettingsModuleOutput> output);
};