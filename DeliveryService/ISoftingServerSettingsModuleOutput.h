#pragma once
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"

class ISoftingServerSettingsModuleOutput
{
public:
	virtual void GetServerCertificateSettings(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated) = 0;
	virtual void GetServerConfigurationSettings(std::string&& computerName, std::string&& serverName, unsigned int port) = 0;
	virtual void GetServerSecurityConfigurationSettings(std::string&& serverSecurityName, std::string&& serverSecurityPolicy, std::string&& securityMode) = 0;
	virtual void GetServerSecurityPolicyIdSettings(std::string&& policyId) = 0;
	virtual void GetServerUserNamePasswordSettings(std::string&& userName, std::string&& password) = 0;
	virtual ~ISoftingServerSettingsModuleOutput() {};
};