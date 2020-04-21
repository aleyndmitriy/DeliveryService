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

void SoftingServerSettingsPresenter::GetServerConfigurationViewOutput(std::string&& computerName, std::string&& serverName, unsigned int port)
{
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		output->GetServerConfigurationSettings(std::move(computerName), std::move(serverName), port);
	}
}

void SoftingServerSettingsPresenter::GetServerSecurityConfigurationViewOutput(std::string&& securityConfiguration)
{
	size_t posFirstPartOfName = securityConfiguration.find('#');
	std::string serverName;
	std::string securityName;
	std::string securityMode;
	if (posFirstPartOfName != std::string::npos) {
		serverName = securityConfiguration.substr(0, posFirstPartOfName);
		size_t posSecondPartOfName = securityConfiguration.rfind('#');
		securityName = securityConfiguration.substr(posSecondPartOfName + 1, securityConfiguration.size() - posSecondPartOfName);
		securityMode = securityConfiguration.substr(posFirstPartOfName + 1, posSecondPartOfName - posFirstPartOfName - 1);
	}
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		output->GetServerSecurityConfigurationSettings(std::move(serverName), std::move(securityName), std::move(securityMode));
	}
}

void SoftingServerSettingsPresenter::GetServerSecurityPolicyIdViewOutput(std::string&& policyId)
{
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		output->GetServerSecurityPolicyIdSettings(std::move(policyId));
	}
}

void SoftingServerSettingsPresenter::GetServerUserNameViewOutput(std::string&& userName, std::string&& password)
{
	std::shared_ptr<ISoftingServerSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		
	}
}