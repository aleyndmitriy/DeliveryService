#include"SoftingServerSettingsPresenter.h"

SoftingServerSettingsPresenter::SoftingServerSettingsPresenter(std::shared_ptr<ISoftingServerSettingsModuleOutput> output):m_ptrView(),m_ptrOutput(output)
{

}

SoftingServerSettingsPresenter::~SoftingServerSettingsPresenter()
{

}

void SoftingServerSettingsPresenter::SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input)
{
	m_ptrView = input;
}

void SoftingServerSettingsPresenter::viewIsReady()
{

}

void SoftingServerSettingsPresenter::GetViewOutput(std::string&& serverName, unsigned int port, std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated)
{
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		output->GetServerSettings(std::move(serverName), port, SoftingServerCertificateOwnSettings(certificate, key, pass), SoftingServerCertificatePkiLocationSettings(trusted,rejected,revocated));
	}
}