#pragma once
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"

class ISoftingServerSettingsModuleOutput
{
public:
	virtual void GetServerSettings(std::string&& serverName, unsigned int port, SoftingServerCertificateOwnSettings&& certificateSettings, SoftingServerCertificatePkiLocationSettings&& pkiSettings) = 0;
	virtual ~ISoftingServerSettingsModuleOutput() {};
};