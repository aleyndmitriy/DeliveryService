#pragma once
#include<map>
#include<set>
#include"SoftingServerUserPolicySettings.h"

enum class SoftingServerEndPointSecurityConfiguration
{
	NONE = 0,
	SIGN_BASIC128_RSA15 = 1,
	SIGN_BASIC256 = 2,
	SIGN_BASIC256_SHA256 = 3,
	SIGN_AES128_SHA256_RSA_OAEP = 4,
	SIGN_AES256_SHA256_RSA_PSS = 5,
	SIGN_AES128_SHA256_NIST_P256 = 6,
	SIGN_AES256_SHA384_NIST_P384 = 7,
	SIGN_AES128_SHA256_BRAINPOOL_P256_R1 = 8,
	SIGN_AES256_SHA384_BRAINPOOL_P384_R1 = 9,
	SIGN_AES128_SHA256_CURVE25519 = 10,
	SIGN_AES256_SHA384_CURVE448 = 11,
	SIGN_AND_ENCRYPT_BASIC128_RSA15 = 12,
	SIGN_AND_ENCRYPT_BASIC256 = 13,
	SIGN_AND_ENCRYPT_BASIC256_SHA256 = 14,
	SIGN_AND_ENCRYPT_AES128_SHA256_RSA_OAEP = 15,
	SIGN_AND_ENCRYPT_AES256_SHA256_RSA_PSS = 16,
	SIGN_AND_ENCRYPT_AES128_SHA256_NIST_P256 = 17,
	SIGN_AND_ENCRYPT_AES256_SHA384_NIST_P384 = 18,
	SIGN_AND_ENCRYPT_AES128_SHA256_BRAINPOOL_P256_R1 = 19,
	SIGN_AND_ENCRYPT_AES256_SHA384_BRAINPOOL_P384_R1 = 20,
	SIGN_AND_ENCRYPT_AES128_SHA256_CURVE25519 = 21,
	SIGN_AND_ENCRYPT_AES256_SHA384_CURVE448 = 22,
};


struct SoftingServerEndPointSettings final
{
	std::string endPointUrl;
	std::set<SoftingServerEndPointSecurityConfiguration> securityConfiguration;
	std::map<std::string, SoftingServerUserPolicySettings> userTokenPolicyList;
	explicit SoftingServerEndPointSettings(const std::string& url);
	explicit SoftingServerEndPointSettings(const char* url);
	SoftingServerEndPointSettings(const SoftingServerEndPointSettings& src) = default;
	SoftingServerEndPointSettings& operator=(const SoftingServerEndPointSettings& src) = default;
	SoftingServerEndPointSettings(SoftingServerEndPointSettings&& src) noexcept = default;
	SoftingServerEndPointSettings& operator=(SoftingServerEndPointSettings && src) = default;
	~SoftingServerEndPointSettings();
};

bool operator==(const SoftingServerEndPointSettings& lhs, const SoftingServerEndPointSettings& rhs);
bool operator!=(const SoftingServerEndPointSettings& lhs, const SoftingServerEndPointSettings& rhs);
bool operator<(const SoftingServerEndPointSettings& lhs, const SoftingServerEndPointSettings& rhs);

SoftingServerEndPointSecurityConfiguration getConfigurationFromInt(int index);
 int getIntFromConfiguration(SoftingServerEndPointSecurityConfiguration config);