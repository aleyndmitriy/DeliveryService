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
	bool Save(const ConnectionAttributes& connectionAttributes, const SoftingServerCertificateOwnSettings& certificatesSettings, const SoftingServerCertificatePkiLocationSettings& pkiLocation, std::ostream& stream);
	bool Load(ConnectionAttributes& connectionAttributes, SoftingServerCertificateOwnSettings& certificatesSettings, SoftingServerCertificatePkiLocationSettings& pkiLocation, std::istream& stream);
};