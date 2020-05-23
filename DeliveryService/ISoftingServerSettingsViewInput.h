#pragma once
#include<string>
#include<vector>
#include<utility>

class ISoftingServerSettingsViewInput
{
public:
	virtual void SetNameOfComputer(const std::string& computerName) = 0;
	virtual void SetServerPort(const std::string& serverPort) = 0;
	virtual void SetServerName(const std::string& serverName) = 0;
	virtual void SetServerEndPoints(std::vector<std::string>&& endPoints) = 0;
	virtual void SelectEndPoint(int index) = 0;
	virtual void SetPolicyIds(std::vector<std::pair<std::string,int> >&& policyIds) = 0;
	virtual void SelectPolicyId(int index, const std::string& uri) = 0;
	virtual void SetUserLogin(const std::string& login) = 0;
	virtual void SetUserPassword(const std::string& password) = 0;
	virtual void ClearSecurityPolicyView() = 0;
	virtual void ClearServerConfigurationView() = 0;
	virtual void ClearServerListView() = 0;
	virtual void SetModeConfiguration(const std::string& serverSecurityName, const std::string& serverSecurityPolicy, const std::string& mode) = 0;
	virtual ~ISoftingServerSettingsViewInput() {};
};