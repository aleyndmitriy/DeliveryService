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
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		
	}
}

void SoftingServerSettingsPresenter::GetCertificateViewOutput(std::string&& certificate, std::string&& key, std::string&& pass, std::string&& trusted, std::string&& rejected, std::string&& revocated)
{
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		output->GetServerCertificateSettings(std::move(certificate), std::move(key), std::move(pass), std::move(trusted),std::move(rejected),std::move(revocated));
	}
}