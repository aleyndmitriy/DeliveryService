#include"ConnectionAttributes.h"

int GetIntFromSecurityMode(ConfigurationSecurityMode mode)
{
	switch (mode) {
	case ConfigurationSecurityMode::INVALID:
		return 0;
		break;
	case ConfigurationSecurityMode::NONE:
		return 1;
		break;
	case ConfigurationSecurityMode::SIGN:
		return 2;
		break;
	case  ConfigurationSecurityMode::SIGN_AND_ENCRYPT:
		return 3;
		break;
	default:
		return 0;
		break;
	}
}

std::string GetStringFromSecurityMode(ConfigurationSecurityMode mode)
{
	switch (mode) {
	case ConfigurationSecurityMode::NONE:
		return std::string("None");
		break;
	case ConfigurationSecurityMode::SIGN:
		return std::string("Sign");
		break;
	case  ConfigurationSecurityMode::SIGN_AND_ENCRYPT:
		return std::string("Sign and Encrypt");
		break;
	default:
		return std::string("Invalid");
	}
}

ConfigurationSecurityMode GetModeFromString(const std::string& mode)
{
	if (mode == std::string("None")) {
		return ConfigurationSecurityMode::NONE;
	}
	else if (mode == std::string("Sign")) {
		return ConfigurationSecurityMode::SIGN;
	}
	else if (mode == std::string("Sign and Encrypt")) {
		return ConfigurationSecurityMode::SIGN_AND_ENCRYPT;
	}
	else {
		return ConfigurationSecurityMode::INVALID;
	}
}

ConfigurationSecurityMode GetModeFromInt(int mode)
{
	switch (mode) {
	case 3:
		return ConfigurationSecurityMode::SIGN_AND_ENCRYPT;
		break;
	case 2:
		return ConfigurationSecurityMode::SIGN;
		break;
	case 1:
		return ConfigurationSecurityMode::NONE;
		break;
	default:
		return ConfigurationSecurityMode::INVALID;
		break;
	}
}

int GetIntFromSecurityType(ConfigurationSecurityType type)
{
	switch (type) {
	case ConfigurationSecurityType::USER_NAME:
		return 1;
	case ConfigurationSecurityType::CERTIFICATE:
		return 2;
	case  ConfigurationSecurityType::ISSUED_TOKEN:
		return 3;
	default:
		return 0;
	}
}

std::string GetStringFromSecurityType(ConfigurationSecurityType type)
{
	switch (type) {
	case ConfigurationSecurityType::USER_NAME:
		return std::string("User Name");
		break;
	case ConfigurationSecurityType::CERTIFICATE:
		return std::string("Certificate");
		break;
	case  ConfigurationSecurityType::ISSUED_TOKEN:
		return std::string("Issued Token");
		break;
	default:
		return std::string("Anonymous");
		break;
	}
}

ConfigurationSecurityType GetTypeFromInt(int type)
{
	switch (type) {
	case 3:
		return ConfigurationSecurityType::ISSUED_TOKEN;
		break;
	case 2:
		return ConfigurationSecurityType::CERTIFICATE;
		break;
	case 1:
		return ConfigurationSecurityType::USER_NAME;
		break;
	default:
		return ConfigurationSecurityType::ANONYMOUS;
		break;
	}
}

ServerConfiguration::ServerConfiguration(const std::string& computer, const std::string& server, unsigned int number) :
	computerName(computer), serverName(server), port(number)
{

}

ServerConfiguration::ServerConfiguration(const std::string& computer, unsigned int number) :
	ServerConfiguration(computer, std::string(), number)
{

}

ServerConfiguration::ServerConfiguration(const std::string& computer): ServerConfiguration(computer, 0)
{

}

ServerConfiguration::ServerConfiguration(): ServerConfiguration(std::string())
{

}

ServerConfiguration::~ServerConfiguration()
{
	computerName.clear();
	serverName.clear();
	port = 0;
}

bool operator==(const ServerConfiguration& lhs, const ServerConfiguration& rhs)
{
	return lhs.computerName == rhs.computerName && lhs.serverName == rhs.serverName && lhs.port == rhs.port;
}

bool operator!=(const ServerConfiguration& lhs, const ServerConfiguration& rhs)
{
	return lhs.computerName != rhs.computerName || lhs.serverName != rhs.serverName || lhs.port != rhs.port;
}


ServerSecurityModeConfiguration::ServerSecurityModeConfiguration(const std::string& config, const std::string& policy, ConfigurationSecurityMode mode):
	serverSecurityName(config), serverSecurityPolicy(policy), securityMode(mode)
{

}

ServerSecurityModeConfiguration::ServerSecurityModeConfiguration(): ServerSecurityModeConfiguration(std::string(), std::string(), ConfigurationSecurityMode::INVALID)
{

}

ServerSecurityModeConfiguration::~ServerSecurityModeConfiguration()
{
	serverSecurityName.clear();
	serverSecurityPolicy.clear();
	securityMode = ConfigurationSecurityMode::INVALID;
}

bool operator==(const ServerSecurityModeConfiguration& lhs, const ServerSecurityModeConfiguration& rhs)
{
	return lhs.serverSecurityName == rhs.serverSecurityName && lhs.securityMode == rhs.securityMode && rhs.serverSecurityPolicy == lhs.serverSecurityPolicy;
}

bool operator!=(const ServerSecurityModeConfiguration& lhs, const ServerSecurityModeConfiguration& rhs)
{
	return lhs.serverSecurityName != rhs.serverSecurityName || lhs.securityMode != rhs.securityMode || rhs.serverSecurityPolicy == lhs.serverSecurityPolicy;
}

bool operator<(const ServerSecurityModeConfiguration& lhs, const ServerSecurityModeConfiguration& rhs)
{
	if (lhs.serverSecurityName < rhs.serverSecurityName) {
		return true;
	}
	else {
		if (lhs.serverSecurityName == rhs.serverSecurityName) {
			if (lhs.securityMode < rhs.securityMode) {
				return true;
			}
			else {
				if (lhs.securityMode == rhs.securityMode) {
					return lhs.serverSecurityPolicy < rhs.serverSecurityPolicy;
				}
				return false;
			}
		}
		return false;
	}
}

SecurityUserNameAccess::SecurityUserNameAccess(const std::string& login, const std::string& password) :
	m_login(login), m_password(password)
{

}

SecurityUserNameAccess::SecurityUserNameAccess() :SecurityUserNameAccess(std::string(), std::string())
{

}

SecurityUserNameAccess::~SecurityUserNameAccess()
{

}

bool operator==(const SecurityUserNameAccess& lhs, const SecurityUserNameAccess& rhs)
{
	return lhs.m_login == rhs.m_login && lhs.m_password == rhs.m_password;
}

bool operator!=(const SecurityUserNameAccess& lhs, const SecurityUserNameAccess& rhs)
{
	return lhs.m_login != rhs.m_login || lhs.m_password != rhs.m_password;
}

SecurityUserTokenPolicy::SecurityUserTokenPolicy(const std::string& policyId, const std::string& securityPolicyUri, int type):
	m_policyId(policyId), m_securityPolicyUri(securityPolicyUri), m_securityType(GetTypeFromInt(type))
{

}

SecurityUserTokenPolicy::SecurityUserTokenPolicy(const std::string& policyId, const std::string& securityPolicyUri, ConfigurationSecurityType type) :
	m_policyId(policyId), m_securityPolicyUri(securityPolicyUri), m_securityType(type)
{

}

SecurityUserTokenPolicy::SecurityUserTokenPolicy() : SecurityUserTokenPolicy(std::string(), std::string(), ConfigurationSecurityType::ANONYMOUS)
{

}

SecurityUserTokenPolicy::~SecurityUserTokenPolicy()
{

}

bool operator==(const SecurityUserTokenPolicy& lhs, const SecurityUserTokenPolicy& rhs)
{
	return lhs.m_policyId == rhs.m_policyId && lhs.m_securityType == rhs.m_securityType && lhs.m_securityPolicyUri == rhs.m_securityPolicyUri;
}

bool operator!=(const SecurityUserTokenPolicy& lhs, const SecurityUserTokenPolicy& rhs)
{
	return lhs.m_policyId != rhs.m_policyId || lhs.m_securityType != rhs.m_securityType || lhs.m_securityPolicyUri != rhs.m_securityPolicyUri;
}

bool operator<(const SecurityUserTokenPolicy& lhs, const SecurityUserTokenPolicy& rhs)
{
	if (lhs.m_policyId < rhs.m_policyId) {
		return true;
	}
	else {
		if (lhs.m_policyId == rhs.m_policyId) {
			if (lhs.m_securityType < rhs.m_securityType) {
				return true;
			}
			else {
				if (lhs.m_securityType == rhs.m_securityType) {
					return lhs.m_securityPolicyUri == rhs.m_securityPolicyUri;
				}
				return false;
			}
		}
		return false;
	}
}

SecurityAccessConfiguration::SecurityAccessConfiguration(const SecurityUserNameAccess& user,  const SecurityUserTokenPolicy& policy):
	m_userLogin(user), m_policy(policy)
{

}


SecurityAccessConfiguration::SecurityAccessConfiguration():
	SecurityAccessConfiguration(SecurityUserNameAccess(),  SecurityUserTokenPolicy())
{

}

SecurityAccessConfiguration::~SecurityAccessConfiguration()
{

}

bool operator==(const SecurityAccessConfiguration& lhs, const SecurityAccessConfiguration& rhs)
{
	return lhs.m_userLogin == rhs.m_userLogin && lhs.m_policy == rhs.m_policy;
}

bool operator!=(const SecurityAccessConfiguration& lhs, const SecurityAccessConfiguration& rhs)
{
	return lhs.m_userLogin != rhs.m_userLogin || lhs.m_policy != rhs.m_policy;
}

ConnectionAttributes::ConnectionAttributes(const ServerConfiguration& server, const ServerSecurityModeConfiguration& mode, const SecurityAccessConfiguration& accessType) :
	configuration(server), configurationMode(mode), configurationAccess(accessType)
{

}

ConnectionAttributes::ConnectionAttributes(const ServerConfiguration& server, const ServerSecurityModeConfiguration& mode) :
	ConnectionAttributes(server, mode, SecurityAccessConfiguration())
{

}

ConnectionAttributes::ConnectionAttributes(const ServerConfiguration& server) :
	ConnectionAttributes(server, ServerSecurityModeConfiguration())
{

}

ConnectionAttributes::ConnectionAttributes(): ConnectionAttributes(ServerConfiguration())
{

}

ConnectionAttributes::~ConnectionAttributes()
{

}

bool operator==(const ConnectionAttributes& lhs, const ConnectionAttributes& rhs)
{
	return lhs.configuration == rhs.configuration && lhs.configurationMode == rhs.configurationMode && lhs.configurationAccess == rhs.configurationAccess;
}

bool operator!=(const ConnectionAttributes& lhs, const ConnectionAttributes& rhs)
{
	return lhs.configuration != rhs.configuration || lhs.configurationMode != rhs.configurationMode || lhs.configurationAccess != rhs.configurationAccess;
}