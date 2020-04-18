#pragma once
#include"MainWindowViewInput.h"
#include<memory>

class IMainWindowViewOutput {
public:
	virtual void viewIsReady() = 0;
	virtual void SetViewInput(std::shared_ptr<IMainWindowViewInput> input) = 0;
	virtual void GetIpAddress() = 0;
	virtual void CreateServiceSettingsModule() = 0;
	virtual ~IMainWindowViewOutput() {};
};