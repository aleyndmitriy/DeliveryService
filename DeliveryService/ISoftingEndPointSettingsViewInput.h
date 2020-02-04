#pragma once
#include"SoftingServerEndPointSettings.h"

class ISoftingEndPointSettingsViewInput
{
public:
	virtual void setupInitialState() = 0;
	virtual void WarningMessage(std::string message) = 0;
	virtual void ErrorMessage(std::string message) = 0;
	virtual void AddEndPoint(std::string endPointUrl) = 0;
	virtual void AddUserPolicy(const SoftingServerUserPolicySettings& userPolicy, int index) = 0;
	virtual void SelectedUserPolicy(const SoftingServerUserPolicySettings& userPolicy) = 0;
	virtual void SelectedEndPointConfigurations(const std::set<int>& configs) = 0;
	virtual void StartLoading() = 0;
	virtual void StopLoading() = 0;
	virtual ~ISoftingEndPointSettingsViewInput() {};
};