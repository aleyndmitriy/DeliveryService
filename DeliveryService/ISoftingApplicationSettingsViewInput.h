#pragma once

class ISoftingApplicationSettingsViewInput
{
public:
	virtual void SetCertificateViewOutput(const std::string& certificate, const std::string& key, const std::string& pass, const std::string& trusted,
		const std::string& rejected, const std::string& revocated) = 0;
	virtual ~ISoftingApplicationSettingsViewInput() {};
};