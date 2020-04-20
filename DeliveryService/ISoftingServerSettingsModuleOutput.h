#pragma once
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"

class ISoftingServerSettingsModuleOutput
{
public:
	virtual void GetServerCertificateSettings(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated) = 0;
	virtual ~ISoftingServerSettingsModuleOutput() {};
};