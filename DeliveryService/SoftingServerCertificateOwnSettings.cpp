#include"SoftingServerCertificateOwnSettings.h"

SoftingServerCertificateOwnSettings::SoftingServerCertificateOwnSettings(const std::string& certificate, const std::string privateKey, const std::string& pass) :
	certificatePath(certificate), privateKeyPath(privateKey), password(pass)
{

}

SoftingServerCertificateOwnSettings::~SoftingServerCertificateOwnSettings() 
{
	certificatePath.clear();
	privateKeyPath.clear();
	password.clear();
}

bool operator==(const SoftingServerCertificateOwnSettings& lhs, const SoftingServerCertificateOwnSettings& rhs)
{
	return lhs.certificatePath == rhs.certificatePath && lhs.privateKeyPath == rhs.privateKeyPath && lhs.password == rhs.password;
}

bool operator!=(const SoftingServerCertificateOwnSettings& lhs, const SoftingServerCertificateOwnSettings& rhs)
{
	return lhs.certificatePath != rhs.certificatePath || lhs.privateKeyPath != rhs.privateKeyPath || lhs.password != rhs.password;
}