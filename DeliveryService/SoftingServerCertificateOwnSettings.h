#pragma once
#include<string>

struct SoftingServerCertificateOwnSettings
{
	std::string certificatePath;
	std::string privateKeyPath;
	std::string password;
	SoftingServerCertificateOwnSettings(const std::string& certificate, const std::string privateKey, const std::string& pass);
	SoftingServerCertificateOwnSettings() = delete;
	SoftingServerCertificateOwnSettings(const SoftingServerCertificateOwnSettings& src) = default;
	SoftingServerCertificateOwnSettings& operator=(const SoftingServerCertificateOwnSettings& src) = default;
	SoftingServerCertificateOwnSettings(SoftingServerCertificateOwnSettings&& src) = default;
	SoftingServerCertificateOwnSettings& operator=(SoftingServerCertificateOwnSettings&& src) = default;
	~SoftingServerCertificateOwnSettings();
};

bool operator==(const SoftingServerCertificateOwnSettings& lhs, const SoftingServerCertificateOwnSettings& rhs);
bool operator!=(const SoftingServerCertificateOwnSettings& lhs, const SoftingServerCertificateOwnSettings& rhs);