#include"SoftingApplicationSettingsPresenter.h"
#include"XMLSettingsDataSource.h"
#include"Constants.h"
#include<fstream>

SoftingApplicationSettingsPresenter::SoftingApplicationSettingsPresenter():
	m_certificateSettings(nullptr),m_pkiLocation(nullptr)
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
	XMLSettingsDataSource xmlSource;
	SoftingServerCertificateOwnSettings cert;
	SoftingServerCertificatePkiLocationSettings pki;
	std::ifstream inStream;
	inStream.open(SOFTING_SEVER_PKI_LOCATION_XML);
	if (!inStream.is_open()) {
		return;
	}
	if (xmlSource.LoadCertificateSettings(cert, pki, inStream))
	{
		m_certificateSettings = std::make_shared<SoftingServerCertificateOwnSettings>(std::move(cert));
		m_pkiLocation = std::make_shared<SoftingServerCertificatePkiLocationSettings>(std::move(pki));
		inStream.close();
	}
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
	if (m_certificateSettings->isEmpty() || m_pkiLocation->isEmpty()) {
		return;
	}
	std::ofstream outStream(SOFTING_SEVER_PKI_LOCATION_XML);
	if (!outStream.is_open()) {
		return;
	}
	XMLSettingsDataSource xmlSource;
	xmlSource.SaveCertificateSettings(*m_certificateSettings, *m_pkiLocation, outStream);
	outStream.close();
}