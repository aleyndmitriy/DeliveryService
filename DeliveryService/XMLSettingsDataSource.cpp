#include"XMLSettingsDataSource.h"
#include<pugixml.hpp>

bool XMLSettingsDataSource::Save(const ConnectionAttributes& connectionAttributes, const SoftingServerCertificateOwnSettings& certificatesSettings, const SoftingServerCertificatePkiLocationSettings& pkiLocation, std::ostream& stream)
{
	pugi::xml_document doc;
	pugi::xml_node rootNode = doc.append_child("Settings");
	pugi::xml_node serverNode = rootNode.append_child("ServerConfiguration");
	serverNode.append_attribute("Computer").set_value(connectionAttributes.configuration.computerName.c_str());
	serverNode.append_attribute("Server").set_value(connectionAttributes.configuration.serverName.c_str());
	serverNode.append_attribute("Port").set_value(connectionAttributes.configuration.port);
	pugi::xml_node securityModeNode = rootNode.append_child("SecurityModeConfiguration");
	securityModeNode.append_attribute("Configuration").set_value(connectionAttributes.configurationMode.serverSecurityName.c_str());
	securityModeNode.append_attribute("SecurityMode").set_value(GetIntFromSecurityMode(connectionAttributes.configurationMode.securityMode));
	securityModeNode.append_attribute("SecurityPolicy").set_value(connectionAttributes.configurationMode.serverSecurityPolicy.c_str());
	pugi::xml_node connectionNode = rootNode.append_child("SecurityAccessConfiguration");
	connectionNode.append_attribute("PolicyId").set_value(connectionAttributes.configurationAccess.m_policy.m_policyId.c_str());
	connectionNode.append_attribute("PolicyUri").set_value(connectionAttributes.configurationAccess.m_policy.m_securityPolicyUri.c_str());
	connectionNode.append_attribute("SecurityType").set_value(GetIntFromSecurityType(connectionAttributes.configurationAccess.m_policy.m_securityType));
	connectionNode.append_attribute("UserName").set_value(connectionAttributes.configurationAccess.m_userLogin.m_login.c_str());
	std::string encryptUserPass = connectionAttributes.configurationAccess.m_userLogin.m_password;
	connectionNode.append_attribute("UserPassword").set_value(encryptUserPass.c_str());
	pugi::xml_node certificateNode = rootNode.append_child("CertificatesAccessConfiguration");
	certificateNode.append_attribute("CertificatePath").set_value(certificatesSettings.certificatePath.c_str());
	std::string encryptCertificatePass = certificatesSettings.password;
	certificateNode.append_attribute("CertificatePassword").set_value(encryptCertificatePass.c_str());
	certificateNode.append_attribute("PrivateKeyPath").set_value(certificatesSettings.privateKeyPath.c_str());

	certificateNode.append_attribute("PkiTrustedStore").set_value(pkiLocation.trustedFolderPath.c_str());
	certificateNode.append_attribute("PkiRevocationStore").set_value(pkiLocation.revocationFolderPath.c_str());
	certificateNode.append_attribute("PkiRejectedStore").set_value(pkiLocation.rejectedFolderPath.c_str());
	return true;
}

bool XMLSettingsDataSource::Load(ConnectionAttributes& connectionAttributes, SoftingServerCertificateOwnSettings& certificatesSettings, SoftingServerCertificatePkiLocationSettings& pkiLocation, std::istream& stream)
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load(stream);
	if (!res) {
		return false;
	}
	pugi::xml_node rootNode = doc.child("Settings");
	pugi::xml_node serverNode = rootNode.child("ServerConfiguration");
	std::string computerName = std::string(serverNode.attribute("Computer").as_string());
	std::string serverName = std::string(serverNode.attribute("Server").as_string());
	unsigned int port = serverNode.attribute("Port").as_uint();
	ServerConfiguration serverConfiguration(computerName, serverName, port);

	pugi::xml_node securityModeNode = rootNode.child("SecurityModeConfiguration");
	std::string serverSecurityName = std::string(securityModeNode.attribute("Configuration").as_string());
	int intMode = securityModeNode.attribute("SecurityMode").as_int();
	std::string serverSecurityPolicy = std::string(securityModeNode.attribute("SecurityPolicy").as_string());
	ServerSecurityModeConfiguration modeConfiguration(serverSecurityName, serverSecurityPolicy, GetModeFromInt(intMode));

	pugi::xml_node connectionNode = rootNode.child("SecurityAccessConfiguration");
	std::string loginName = std::string(connectionNode.attribute("UserName").as_string());
	std::string loginPass = std::string(connectionNode.attribute("UserPassword").as_string());
	std::string policyId = std::string(connectionNode.attribute("PolicyId").as_string());
	std::string policyUri = std::string(connectionNode.attribute("PolicyUri").as_string());
	int type = connectionNode.attribute("SecurityType").as_int();
	SecurityUserTokenPolicy policy(policyId, policyUri, type);
	SecurityUserNameAccess userAccess(loginName, loginPass);
	SecurityAccessConfiguration configurationAccess(userAccess, policy);

	std::string certificate = std::string(connectionNode.attribute("CertificatePath").as_string());
	std::string certificatePassword = std::string(connectionNode.attribute("CertificatePassword").as_string());
	std::string privateKey = std::string(connectionNode.attribute("PrivateKeyPath").as_string());
	certificatesSettings.certificatePath = certificate;
	certificatesSettings.password = certificatePassword;
	certificatesSettings.password = certificatePassword;

	std::string trusted = std::string(connectionNode.attribute("PkiTrustedStore").as_string());
	std::string revoced = std::string(connectionNode.attribute("PkiRevocationStore").as_string());
	std::string rejected = std::string(connectionNode.attribute("PkiRejectedStore").as_string());
	pkiLocation.trustedFolderPath = trusted;
	pkiLocation.revocationFolderPath = revoced;
	pkiLocation.rejectedFolderPath = rejected;
	connectionAttributes.configuration = serverConfiguration;
	connectionAttributes.configurationMode = modeConfiguration;
	connectionAttributes.configurationAccess = configurationAccess;
	return true;
}
