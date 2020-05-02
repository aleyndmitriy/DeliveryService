#pragma once
#include<Windows.h>
#include<memory>
#include"ConnectionAttributes.h"

class SoftingServerSettingsInitializer final
{
public:
	static int CreateModule(HINSTANCE hInstance,  HWND parent, std::shared_ptr<ConnectionAttributes> connectionAttributes, std::shared_ptr<DataTypeAttributes> dataAttributes);
};