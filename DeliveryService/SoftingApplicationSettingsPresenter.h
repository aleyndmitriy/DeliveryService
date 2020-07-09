#pragma once
#include"ISoftingApplicationSettingsViewOutput.h"
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"

class SoftingApplicationSettingsPresenter final : public std::enable_shared_from_this<SoftingApplicationSettingsPresenter>, public ISoftingApplicationSettingsViewOutput
{
public:
	SoftingApplicationSettingsPresenter();
	SoftingApplicationSettingsPresenter(const SoftingApplicationSettingsPresenter& src) = delete;
	SoftingApplicationSettingsPresenter& operator=(const SoftingApplicationSettingsPresenter& src) = delete;
	SoftingApplicationSettingsPresenter(SoftingApplicationSettingsPresenter&& src) = delete;
	SoftingApplicationSettingsPresenter& operator=(SoftingApplicationSettingsPresenter&& src) = delete;
	~SoftingApplicationSettingsPresenter();
	void SetViewInput(std::shared_ptr<ISoftingApplicationSettingsViewInput> input) override;
	void viewIsReady() override;
	void GetCertificateViewOutput(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated) override;
private:
	std::weak_ptr<ISoftingApplicationSettingsViewInput> m_ptrView;
	std::shared_ptr<SoftingServerCertificateOwnSettings> m_certificateSettings;
	std::shared_ptr<SoftingServerCertificatePkiLocationSettings> m_pkiLocation;
};