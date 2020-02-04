#pragma once
#include<memory>
#include<string>
#include"ISoftingServerSettingsViewInput.h"

class ISoftingServerSettingsViewOutput {

public:
	virtual void viewIsReady() = 0;
	virtual void SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input) = 0;
	virtual void GetViewOutput(std::string&& serverName, unsigned int port, std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated) = 0;
	virtual ~ISoftingServerSettingsViewOutput() {};
};