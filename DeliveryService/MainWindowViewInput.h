#pragma once
#include<string>
#include<Windows.h>

class IMainWindowViewInput {
public:
	virtual void WarningMessage(std::string message) = 0;
	virtual void ErrorMessage(std::string message) = 0;
	virtual void StartLoading() = 0;
	virtual void StopLoading() = 0;
	virtual HWND GetWindowHandle() = 0;
	virtual HINSTANCE GetAppInstance() = 0;
	virtual ~IMainWindowViewInput() {};
};