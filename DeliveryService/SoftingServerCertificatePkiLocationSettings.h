#pragma once
#include<string>

struct SoftingServerCertificatePkiLocationSettings
{
	std::string trustedFolderPath;
	std::string rejectedFolderPath;
	std::string revocationFolderPath;
	SoftingServerCertificatePkiLocationSettings(const std::string& trusted, const std::string& rejected, const std::string& revocation);
	SoftingServerCertificatePkiLocationSettings() = default;
	SoftingServerCertificatePkiLocationSettings(const SoftingServerCertificatePkiLocationSettings& src) = default;
	SoftingServerCertificatePkiLocationSettings& operator=(const SoftingServerCertificatePkiLocationSettings& src) = default;
	SoftingServerCertificatePkiLocationSettings(SoftingServerCertificatePkiLocationSettings&& src) = default;
	SoftingServerCertificatePkiLocationSettings& operator=(SoftingServerCertificatePkiLocationSettings&& src) = default;
	~SoftingServerCertificatePkiLocationSettings();
	bool isEmpty();
};

bool operator== (const SoftingServerCertificatePkiLocationSettings & lhs, const SoftingServerCertificatePkiLocationSettings & rhs);
bool operator!= (const SoftingServerCertificatePkiLocationSettings & lhs, const SoftingServerCertificatePkiLocationSettings & rhs);