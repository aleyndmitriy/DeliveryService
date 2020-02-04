#include"SoftingServerEndPointSettings.h"

SoftingServerEndPointSettings::SoftingServerEndPointSettings(const std::string& url) :
	endPointUrl(url), securityConfiguration(), userTokenPolicyList()
{

}

SoftingServerEndPointSettings::SoftingServerEndPointSettings(const char* url) :
	SoftingServerEndPointSettings(std::string(url))
{

}

SoftingServerEndPointSettings::~SoftingServerEndPointSettings()
{
	endPointUrl.clear();
	securityConfiguration.clear();
	userTokenPolicyList.clear();
}

bool operator==(const SoftingServerEndPointSettings& lhs, const SoftingServerEndPointSettings& rhs)
{
	return lhs.endPointUrl == rhs.endPointUrl ;
}

bool operator!=(const SoftingServerEndPointSettings& lhs, const SoftingServerEndPointSettings& rhs)
{
	return lhs.endPointUrl != rhs.endPointUrl;
}

bool operator<(const SoftingServerEndPointSettings& lhs, const SoftingServerEndPointSettings& rhs)
{
	return lhs.endPointUrl < rhs.endPointUrl;
}

SoftingServerEndPointSecurityConfiguration getConfigurationFromInt(int index)
{
	switch (index) {
	case 1:
		return SoftingServerEndPointSecurityConfiguration::SIGN_BASIC128_RSA15;
		break;
	case 2:
		return SoftingServerEndPointSecurityConfiguration::SIGN_BASIC256;
		break;
	case 3:
		return SoftingServerEndPointSecurityConfiguration::SIGN_BASIC256_SHA256;
		break;
	case 4:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_RSA_OAEP;
		break;
	case 5:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA256_RSA_PSS;
		break;
	case 6:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_NIST_P256;
		break;
	case 7:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA384_NIST_P384;
		break;
	case 8:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_BRAINPOOL_P256_R1;
		break;
	case 9:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA384_BRAINPOOL_P384_R1;
		break;
	case 10:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_CURVE25519;
		break;
	case 11:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA384_CURVE448;
		break;
	case 12:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_BASIC128_RSA15;
		break;
	case 13:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_BASIC256;
		break;
	case 14:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_BASIC256_SHA256;
		break;
	case 15:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_RSA_OAEP;
		break;
	case 16:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA256_RSA_PSS;
		break;
	case 17:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_NIST_P256;
		break;
	case 18:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA384_NIST_P384;
		break;
	case 19:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_BRAINPOOL_P256_R1;
		break;
	case 20:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA384_BRAINPOOL_P384_R1;
		break;
	case 21:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_CURVE25519;
		break;
	case 22:
		return SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA384_CURVE448;
		break;
	default:
		return SoftingServerEndPointSecurityConfiguration::NONE;
		break;
	}
}

int getIntFromConfiguration(SoftingServerEndPointSecurityConfiguration config)
{
	switch (config) {
	case SoftingServerEndPointSecurityConfiguration::SIGN_BASIC128_RSA15:
		return 1;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_BASIC256:
		return 2;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_BASIC256_SHA256:
		return 3;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_RSA_OAEP:
		return 4;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA256_RSA_PSS:
		return 5;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_NIST_P256:
		return 6;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA384_NIST_P384:
		return 7;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_BRAINPOOL_P256_R1:
		return 8;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA384_BRAINPOOL_P384_R1:
		return 9;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES128_SHA256_CURVE25519:
		return 10;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AES256_SHA384_CURVE448:
		return 11;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_BASIC128_RSA15:
		return 12;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_BASIC256:
		return 13;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_BASIC256_SHA256:
		return 14;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_RSA_OAEP:
		return 15;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA256_RSA_PSS:
		return 16;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_NIST_P256:
		return 17;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA384_NIST_P384:
		return 18;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_BRAINPOOL_P256_R1:
		return 19;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA384_BRAINPOOL_P384_R1:
		return 20;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES128_SHA256_CURVE25519:
		return 21;
		break;
	case SoftingServerEndPointSecurityConfiguration::SIGN_AND_ENCRYPT_AES256_SHA384_CURVE448:
		return 22;
		break;
	default:
		return 0;
		break;
	}
}