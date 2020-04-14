#pragma once
#include"SoftingServerEndPointSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"
#include"SoftingServerCertificateOwnSettings.h"

class XMLSettingsDataSource
{
public:
	XMLSettingsDataSource() = default;
	XMLSettingsDataSource(const XMLSettingsDataSource& src) = delete;
	XMLSettingsDataSource(XMLSettingsDataSource&& src) = delete;
	XMLSettingsDataSource& operator=(const XMLSettingsDataSource& rhs) = delete;
	XMLSettingsDataSource& operator=(XMLSettingsDataSource&& rhs) = delete;
}