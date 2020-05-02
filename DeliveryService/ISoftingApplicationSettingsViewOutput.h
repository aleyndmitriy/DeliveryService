#pragma once

#include<memory>
#include<string>
#include"ISoftingApplicationSettingsViewInput.h"

class ISoftingApplicationSettingsViewOutput {
public:
	virtual void viewIsReady() = 0;
	virtual void SetViewInput(std::shared_ptr<ISoftingApplicationSettingsViewInput> input) = 0;
	virtual void GetCertificateViewOutput(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated) = 0;
	virtual ~ISoftingApplicationSettingsViewOutput() {};
};