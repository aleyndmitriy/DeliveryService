#include"SoftingServerUserPolicySettings.h"

SoftingServerUserPolicySettings::SoftingServerUserPolicySettings(const std::string& id, const std::string& uri, const std::string& user, const std::string& pwd, SoftingServerUserTokenType type) :
	policyId(id),policyUri(uri),userName(user),password(pwd), tokenType(type)
{

}

SoftingServerUserPolicySettings::SoftingServerUserPolicySettings(const char* id, const char* uri, const char* user, const char* pwd, SoftingServerUserTokenType type) :
	policyId(id), policyUri(uri), userName(user), password(pwd), tokenType(type)
{

}

SoftingServerUserPolicySettings::SoftingServerUserPolicySettings(const std::string& id, const std::string& uri, const std::string& user, const std::string& pwd, int type) :
	SoftingServerUserPolicySettings(id, uri, user, pwd, SoftingServerUserTokenType())
{
	switch (type) {
	case 1:
		tokenType = SoftingServerUserTokenType::USER_NAME;
		break;
	case 2:
		tokenType = SoftingServerUserTokenType::CERTIFICATE;
		break;
	case 3:
		tokenType = SoftingServerUserTokenType::ISSUED_TOKEN;
	default:
		tokenType = SoftingServerUserTokenType::ANONYMOUS;
		break;
	}
}

SoftingServerUserPolicySettings::SoftingServerUserPolicySettings(const char* id, const char* uri, const char* user, const char* pwd, int type) :
	SoftingServerUserPolicySettings(std::string(id), std::string(uri), std::string(user), std::string(pwd), type)
{
	
}

SoftingServerUserPolicySettings::~SoftingServerUserPolicySettings()
{
	policyId.clear();
	policyUri.clear();
	userName.clear();
	password.clear();
	tokenType = SoftingServerUserTokenType::ANONYMOUS;
}

bool operator==(const SoftingServerUserPolicySettings& lhs, const SoftingServerUserPolicySettings& rhs)
{
	return lhs.policyId == rhs.policyId && lhs.policyUri == rhs.policyUri && lhs.userName == rhs.userName &&
		lhs.password == rhs.password && lhs.tokenType == rhs.tokenType;
}

bool operator!=(const SoftingServerUserPolicySettings& lhs, const SoftingServerUserPolicySettings& rhs)
{
	return lhs.policyId != rhs.policyId || lhs.policyUri != rhs.policyUri || lhs.userName != rhs.userName ||
		lhs.password != rhs.password || lhs.tokenType != rhs.tokenType;
}

bool operator<(const SoftingServerUserPolicySettings& lhs, const SoftingServerUserPolicySettings& rhs)
{
	if (lhs.policyId < rhs.policyId) {
		return true;
	}
	if (lhs.policyId > rhs.policyId) {
		return false;
	}
	if (lhs.policyUri < rhs.policyUri) {
		return true;
	}
	if (lhs.policyUri > rhs.policyUri) {
		return false;
	}
	if (lhs.tokenType < rhs.tokenType) {
		return true;
	}
	if (lhs.tokenType > rhs.tokenType) {
		return false;
	}
	if (lhs.userName < rhs.userName) {
		return true;
	}
	if (lhs.userName > rhs.userName) {
		return false;
	}
	return lhs.password < rhs.password;
}