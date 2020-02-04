#pragma once
#include<string>

enum class SoftingServerUserTokenType
{
	ANONYMOUS = 0,
	USER_NAME = 1,
	CERTIFICATE = 2,
	ISSUED_TOKEN = 3
};

struct SoftingServerUserPolicySettings
{
	std::string policyId;
	std::string policyUri;
	std::string userName;
	std::string password;
	SoftingServerUserTokenType tokenType;
	explicit SoftingServerUserPolicySettings(const std::string& id, const std::string& uri, const std::string& user, const std::string& pwd, SoftingServerUserTokenType type);
	explicit SoftingServerUserPolicySettings(const char* id, const char* uri, const char* user, const char* pwd, SoftingServerUserTokenType type);
	explicit SoftingServerUserPolicySettings(const std::string& id, const std::string& uri, const std::string& user, const std::string& pwd, int type);
	explicit SoftingServerUserPolicySettings(const char* id, const char* uri, const char* user, const char* pwd, int type);
	SoftingServerUserPolicySettings(const SoftingServerUserPolicySettings& src) = default;
	SoftingServerUserPolicySettings& operator=(const SoftingServerUserPolicySettings& src) = default;
	SoftingServerUserPolicySettings(SoftingServerUserPolicySettings&& src) = default;
	SoftingServerUserPolicySettings& operator=(SoftingServerUserPolicySettings&& src) = default;
	~SoftingServerUserPolicySettings();
};

bool operator==(const SoftingServerUserPolicySettings& lhs, const SoftingServerUserPolicySettings& rhs);
bool operator!=(const SoftingServerUserPolicySettings& lhs, const SoftingServerUserPolicySettings& rhs);
bool operator<(const SoftingServerUserPolicySettings& lhs, const SoftingServerUserPolicySettings& rhs);