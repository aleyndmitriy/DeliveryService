#pragma once
#include<memory>
#include<string>
#include"ISoftingServerSettingsViewInput.h"

class ISoftingServerSettingsViewOutput {

public:
	virtual void viewIsReady() = 0;
	virtual void SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input) = 0;
	virtual void UpdateComputerName(std::string&& compName) = 0;
	virtual void UpdatePortNumber(std::string&& strPort) = 0;
	virtual void UpdateLogin(std::string&& login) = 0;
	virtual void UpdatePassword(std::string&& password) = 0;
	virtual void GetServerSecurityConfigurations(std::string&& serverName) = 0;
	virtual void GetServerSecurityPolicyIds(std::string&& endPoint) = 0;
	virtual void UpdatePolicyIds(std::string&& policyId, int securityType) = 0;
	virtual ~ISoftingServerSettingsViewOutput() {};
};