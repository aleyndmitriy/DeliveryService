#pragma once
#include"SoftingServerEndPointSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"
#include"SoftingServerCertificateOwnSettings.h"
#include"ConnectionAttributes.h"

class XMLSettingsDataSource
{
public:
	XMLSettingsDataSource() = default;
	XMLSettingsDataSource(const XMLSettingsDataSource& src) = delete;
	XMLSettingsDataSource(XMLSettingsDataSource&& src) = delete;
	XMLSettingsDataSource& operator=(const XMLSettingsDataSource& rhs) = delete;
	XMLSettingsDataSource& operator=(XMLSettingsDataSource&& rhs) = delete;
	bool SaveCertificateSettings(const SoftingServerCertificateOwnSettings& certificatesSettings, const SoftingServerCertificatePkiLocationSettings& pkiLocation, std::ostream& stream);
	bool SaveConnectionAttributes(const ConnectionAttributes& connectionAttributes, std::ostream& stream);
	bool LoadCertificateSettings(SoftingServerCertificateOwnSettings& certificatesSettings, SoftingServerCertificatePkiLocationSettings& pkiLocation, std::istream& stream);
	bool LoadConnectionAttributes(ConnectionAttributes& connectionAttributes, std::istream& stream);
};