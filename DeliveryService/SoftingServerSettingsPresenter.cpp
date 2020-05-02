#include"SoftingServerSettingsPresenter.h"

SoftingServerSettingsPresenter::SoftingServerSettingsPresenter( std::shared_ptr<ConnectionAttributes> connectionAttributes, std::shared_ptr<DataTypeAttributes> dataAttributes):
m_ptrView(), m_connectAttributes(connectionAttributes), m_dataAttributes(dataAttributes)
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

void SoftingServerSettingsPresenter::GetServerConfigurationViewOutput(std::string&& computerName, std::string&& serverName, unsigned int port)
{
	
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
	
}

void SoftingServerSettingsPresenter::GetServerSecurityPolicyIdViewOutput(std::string&& policyId)
{
	
}

void SoftingServerSettingsPresenter::GetServerUserNameViewOutput(std::string&& userName, std::string&& password)
{
	
}

void SoftingServerSettingsPresenter::SendMessageError(std::string&& message)
{

}

void SoftingServerSettingsPresenter::SendWarning(std::string&& message)
{

}

void SoftingServerSettingsPresenter::SendMessageInfo(std::string&& message)
{

}

void SoftingServerSettingsPresenter::GetServers(std::vector<std::string>&& servers, std::string&& discoveryUrl)
{
	//m_cmbServerName.ResetContent();
	size_t index = 0;
	for (std::vector<std::string>::const_iterator itr = servers.cbegin(); itr != servers.cend(); ++itr)
	{
		//int pos = m_cmbServerName.AddString(itr->c_str());
		//m_cmbServerName.SetItemData(pos, index++);
	}

	m_connectAttributes->configurationMode.serverSecurityName = discoveryUrl;
	//StopLoading();
}

void SoftingServerSettingsPresenter::SelectFoundedServer(const std::string& compName, unsigned int port, const std::string& serverName)
{

}

void SoftingServerSettingsPresenter::ChooseSecurityConfiguration()
{

}

void SoftingServerSettingsPresenter::GetEndPoints(std::vector<ServerSecurityModeConfiguration>&& servers)
{

}

void SoftingServerSettingsPresenter::GetPolicyIds(std::vector<SecurityUserTokenPolicy>&& policyIds)
{

}

void SoftingServerSettingsPresenter::GetAggregates(std::vector<std::pair<std::string, int> >&& aggregates)
{

}

