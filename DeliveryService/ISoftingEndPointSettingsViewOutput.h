#pragma once
#include<memory>
#include<string>
#include"ISoftingEndPointSettingsViewInput.h"
#include<set>
class ISoftingEndPointSettingsViewOutput
{
public:
	virtual void viewIsReady() = 0;
	virtual void SetViewInput(std::shared_ptr<ISoftingEndPointSettingsViewInput> input) = 0;
	virtual void SelectEndPoint(std::string endPointUrl) = 0;
	virtual void AddEndPoint(std::string endPointUrl, const std::set<int>& configs) = 0;
	virtual void RemoveEndPoint(std::string endPointUrl) = 0;
	virtual void AddUserPolicy(SoftingServerUserPolicySettings&& condition, std::string endPointUrl) = 0;
	virtual void RemoveUserPolicy(const std::string& policyId, std::string endPointUrl) = 0;
	virtual void RemoveAllUserPolicies(std::string endPointUrl) = 0;
	virtual void SelectUserPolicy(const std::string& policyId, std::string endPointName) = 0;
	virtual void SaveEndPoints() = 0;
	virtual ~ISoftingEndPointSettingsViewOutput() {};
};