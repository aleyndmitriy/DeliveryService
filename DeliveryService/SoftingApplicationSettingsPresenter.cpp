#include"SoftingApplicationSettingsPresenter.h"

SoftingApplicationSettingsPresenter::SoftingApplicationSettingsPresenter(std::shared_ptr<SoftingServerCertificateOwnSettings> certificateSettings, std::shared_ptr<SoftingServerCertificatePkiLocationSettings> pkiLocation):
	m_certificateSettings(certificateSettings),m_pkiLocation(pkiLocation)
{

}

SoftingApplicationSettingsPresenter::~SoftingApplicationSettingsPresenter()
{
	m_ptrView.reset();
	m_certificateSettings.reset();
	m_pkiLocation.reset();
}

void SoftingApplicationSettingsPresenter::SetViewInput(std::shared_ptr<ISoftingApplicationSettingsViewInput> input)
{
	m_ptrView = input;
}

void SoftingApplicationSettingsPresenter::viewIsReady()
{
	std::shared_ptr<ISoftingApplicationSettingsViewInput> input = m_ptrView.lock();
	if (input) {
		if (m_certificateSettings && m_pkiLocation) {
			input->SetCertificateViewOutput(m_certificateSettings->certificatePath, m_certificateSettings->privateKeyPath, m_certificateSettings->password,
				m_pkiLocation->trustedFolderPath, m_pkiLocation->rejectedFolderPath, m_pkiLocation->revocationFolderPath);
		}
	}
}

void SoftingApplicationSettingsPresenter::GetCertificateViewOutput(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated)
{
	m_certificateSettings->certificatePath = certificate;
	m_certificateSettings->privateKeyPath = key;
	m_certificateSettings->password = pass;
	m_pkiLocation->trustedFolderPath = trusted;
	m_pkiLocation->rejectedFolderPath = rejected;
	m_pkiLocation->revocationFolderPath = revocated;
}