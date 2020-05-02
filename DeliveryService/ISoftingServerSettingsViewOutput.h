#pragma once
#include<memory>
#include<string>
#include"ISoftingServerSettingsViewInput.h"

class ISoftingServerSettingsViewOutput {

public:
	virtual void viewIsReady() = 0;
	virtual void SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input) = 0;
	virtual void GetServerConfigurationViewOutput(std::string&& computerName, std::string&& serverName, unsigned int port) = 0;
	virtual void GetServerSecurityConfigurationViewOutput(std::string&& securityConfiguration) = 0;
	virtual void GetServerSecurityPolicyIdViewOutput(std::string&& policyId) = 0;
	virtual void GetServerUserNameViewOutput(std::string&& userName, std::string&& password) = 0;
	virtual ~ISoftingServerSettingsViewOutput() {};
};