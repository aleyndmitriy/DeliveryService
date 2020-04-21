#pragma once
#include"ISoftingServerSettingsViewOutput.h"
#include"ISoftingServerSettingsModuleOutput.h"

class SoftingServerSettingsPresenter final : public std::enable_shared_from_this<SoftingServerSettingsPresenter>, public ISoftingServerSettingsViewOutput
{
public:
	SoftingServerSettingsPresenter(std::shared_ptr<ISoftingServerSettingsModuleOutput> output);
	SoftingServerSettingsPresenter(const SoftingServerSettingsPresenter& src) = delete;
	SoftingServerSettingsPresenter& operator=(const SoftingServerSettingsPresenter& src) = delete;
	SoftingServerSettingsPresenter(SoftingServerSettingsPresenter&& src) = delete;
	SoftingServerSettingsPresenter& operator=(SoftingServerSettingsPresenter&& src) = delete;
	~SoftingServerSettingsPresenter();
	void SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input) override;
	void viewIsReady() override;
	void GetCertificateViewOutput(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated) override;
	void GetServerConfigurationViewOutput(std::string&& computerName, std::string&& serverName, unsigned int port) override;
	void GetServerSecurityConfigurationViewOutput(std::string&& securityConfiguration) override;
	void GetServerSecurityPolicyIdViewOutput(std::string&& policyId) override;
	void GetServerUserNameViewOutput(std::string&& userName, std::string&& password) override;
private:
	std::weak_ptr<ISoftingServerSettingsViewInput> m_ptrView;
	std::weak_ptr<ISoftingServerSettingsModuleOutput> m_ptrOutput;
};