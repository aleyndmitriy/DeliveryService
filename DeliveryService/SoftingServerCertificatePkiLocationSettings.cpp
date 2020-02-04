#include"SoftingServerCertificatePkiLocationSettings.h"

SoftingServerCertificatePkiLocationSettings::SoftingServerCertificatePkiLocationSettings(const std::string& trusted, const std::string& rejected, const std::string& revocation):
	trustedFolderPath(trusted),rejectedFolderPath(rejected),revocationFolderPath(revocation)
{

}

SoftingServerCertificatePkiLocationSettings::~SoftingServerCertificatePkiLocationSettings()
{

}

bool operator== (const SoftingServerCertificatePkiLocationSettings& lhs, const SoftingServerCertificatePkiLocationSettings& rhs)
{
	return lhs.trustedFolderPath == rhs.trustedFolderPath && lhs.rejectedFolderPath == rhs.rejectedFolderPath && lhs.revocationFolderPath == rhs.revocationFolderPath;
}

bool operator!= (const SoftingServerCertificatePkiLocationSettings& lhs, const SoftingServerCertificatePkiLocationSettings& rhs)
{
	return lhs.trustedFolderPath != rhs.trustedFolderPath || lhs.rejectedFolderPath != rhs.rejectedFolderPath || lhs.revocationFolderPath != rhs.revocationFolderPath;
}