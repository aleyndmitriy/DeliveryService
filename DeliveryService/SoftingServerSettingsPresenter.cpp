#include"SoftingServerSettingsPresenter.h"
#include<algorithm>

SoftingServerSettingsPresenter::SoftingServerSettingsPresenter( std::shared_ptr<ConnectionAttributes> connectionAttributes, std::shared_ptr<DataTypeAttributes> dataAttributes):
m_ptrView(), m_connectAttributes(connectionAttributes), m_dataAttributes(dataAttributes), m_pSoftingInteractor(std::make_unique<SoftingServerInteractor>(connectionAttributes,dataAttributes)),
m_endPointsConfigurations(), m_endPointPolicyIds(), m_aggregates()
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
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	if (m_pSoftingInteractor) {
		m_pSoftingInteractor->SetOutput(shared_from_this());
	}
	else {
		return;
	}
	if (m_connectAttributes) {
		if (!m_connectAttributes->configuration.computerName.empty()) {
			input->SetNameOfComputer(m_connectAttributes->configuration.computerName);
		}
		if (m_connectAttributes->configuration.port > 0) {
			std::string serverPort = std::to_string(m_connectAttributes->configuration.port);
			input->SetServerPort(serverPort);
		}
		if (!m_connectAttributes->configuration.serverName.empty()) {
			input->SetServerName(m_connectAttributes->configuration.serverName);
			input->ClearServerConfigurationView();
			m_pSoftingInteractor->GetServerPropertyByUrn(m_connectAttributes->configuration.serverName);
		}
		if (!m_connectAttributes->configurationMode.serverSecurityName.empty()) {
			for (int index = 0; index < m_endPointsConfigurations.size(); index++) {
				if (m_endPointsConfigurations.at(index) == m_connectAttributes->configurationMode) {
					input->SelectEndPoint(index);
					if (m_pSoftingInteractor) {
						m_pSoftingInteractor->ChooseCurrentEndPoint();
					}
					break;
				}
			}
			if (m_endPointsConfigurations.empty()) {
				std::string desc = m_connectAttributes->configurationMode.serverSecurityName + std::string("#") + GetStringFromSecurityMode(m_connectAttributes->configurationMode.securityMode) +
					std::string("#") + m_connectAttributes->configurationMode.serverSecurityPolicy;
				input->SetServerEndPoints(std::vector<std::string>{desc});
				m_endPointsConfigurations.push_back(m_connectAttributes->configurationMode);
			}
		}
		if (!m_connectAttributes->configurationAccess.m_policy.m_policyId.empty()) {

			for (int index = 0; index < m_endPointPolicyIds.size(); index++) {
				if (m_endPointPolicyIds.at(index) == m_connectAttributes->configurationAccess.m_policy) {
					input->SelectPolicyId(index, m_connectAttributes->configurationAccess.m_policy.m_securityPolicyUri);
					break;
				}
			}
			if (m_endPointPolicyIds.empty()) {
				std::string desc = std::string("Id: ") + m_connectAttributes->configurationAccess.m_policy.m_policyId +
					std::string("type: ") + GetStringFromSecurityType(m_connectAttributes->configurationAccess.m_policy.m_securityType);
				input->SetPolicyIds(std::vector<std::string>{ desc });
				input->SelectPolicyId(0, m_connectAttributes->configurationAccess.m_policy.m_securityPolicyUri);
				m_endPointPolicyIds.push_back(m_connectAttributes->configurationAccess.m_policy);
			}
		}
		if (!m_connectAttributes->configurationAccess.m_userLogin.m_login.empty()) {
			input->SetUserLogin(m_connectAttributes->configurationAccess.m_userLogin.m_login);
			if (!m_connectAttributes->configurationAccess.m_userLogin.m_password.empty()) {
				input->SetUserPassword(m_connectAttributes->configurationAccess.m_userLogin.m_password);
			}
		}
	}
}

void SoftingServerSettingsPresenter::UpdateComputerName(std::string&& compName)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	input->ClearServerListView();
	if (m_connectAttributes) {
		m_connectAttributes->configuration.computerName = compName;
		m_connectAttributes->configuration.serverName.clear();
		m_connectAttributes->configurationMode.Clear();
		m_connectAttributes->configurationAccess.m_policy.Clear();
	}
}

void SoftingServerSettingsPresenter::UpdatePortNumber(std::string&& strPort)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	input->ClearServerListView();
	if (m_connectAttributes) {
		m_connectAttributes->configuration.port = std::stoul(strPort);
		m_connectAttributes->configuration.serverName.clear();
		m_connectAttributes->configurationMode.Clear();
		m_connectAttributes->configurationAccess.m_policy.Clear();
	}
}

void SoftingServerSettingsPresenter::UpdateLogin(std::string&& login)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	if (m_connectAttributes) {
		m_connectAttributes->configurationAccess.m_userLogin.m_login = login;
	}
}

void SoftingServerSettingsPresenter::UpdatePassword(std::string&& password)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	if (m_connectAttributes) {
		m_connectAttributes->configurationAccess.m_userLogin.m_password = password;
	}
}


void SoftingServerSettingsPresenter::GetServerSecurityConfigurations(std::string&& serverName)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	input->ClearServerConfigurationView();
	if (m_connectAttributes) {
		m_connectAttributes->configuration.serverName = serverName;
		m_connectAttributes->configurationMode.Clear();
		m_connectAttributes->configurationAccess.m_policy.Clear();
	}
	if (m_pSoftingInteractor) {
		m_pSoftingInteractor->ChooseCurrentServer();
	}
}

void SoftingServerSettingsPresenter::GetServerSecurityPolicyIds(std::string&& endPoint)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	input->ClearSecurityPolicyView();
	if (m_connectAttributes) {
		size_t posFirstPartOfName = endPoint.find('#');
		if (posFirstPartOfName != std::string::npos) {
			m_connectAttributes->configurationMode.serverSecurityName = endPoint.substr(0, posFirstPartOfName);
			size_t posSecondPartOfName = endPoint.rfind('#');
			m_connectAttributes->configurationMode.serverSecurityPolicy = endPoint.substr(posSecondPartOfName + 1, endPoint.size() - posSecondPartOfName);
			std::string securityMode = endPoint.substr(posFirstPartOfName + 1, posSecondPartOfName - posFirstPartOfName - 1);
			m_connectAttributes->configurationMode.securityMode = GetModeFromString(securityMode);
			m_connectAttributes->configurationAccess.m_policy.Clear();
			if (m_pSoftingInteractor) {
				m_pSoftingInteractor->ChooseCurrentEndPoint();
			}
		}
	}
}

void SoftingServerSettingsPresenter::UpdatePolicyIds(std::string&& policyId)
{
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (!input) {
		return;
	}
	if (m_connectAttributes) {
		size_t posFirstPartOfName = policyId.find('#');
		if (posFirstPartOfName != std::string::npos) {
			m_connectAttributes->configurationAccess.m_policy.m_policyId = policyId.substr(0, posFirstPartOfName);
			
		}
	}
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

void SoftingServerSettingsPresenter::GetEndPoints(std::vector<ServerSecurityModeConfiguration>&& endPoints)
{
	m_endPointsConfigurations.clear();
	m_endPointsConfigurations.assign(endPoints.cbegin(), endPoints.cend());
	std::vector<std::string> endPointsList;
	std::transform(endPoints.cbegin(), endPoints.cend(), std::back_inserter(endPointsList), [](const ServerSecurityModeConfiguration& config) {
		std::string desc = config.serverSecurityName + std::string("#") + GetStringFromSecurityMode(config.securityMode) + std::string("#") + config.serverSecurityPolicy;
		return desc; });
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (input) {
		input->SetServerEndPoints(std::move(endPointsList));
	}
}

void SoftingServerSettingsPresenter::GetPolicyIds(std::vector<SecurityUserTokenPolicy>&& policyIds)
{
	m_endPointPolicyIds.clear();
	m_endPointPolicyIds.assign(policyIds.cbegin(),policyIds.cend());
	std::vector<std::pair<std::string, int> > policyIdsList;
	std::transform(policyIds.cbegin(), policyIds.cend(), std::back_inserter(policyIdsList), [](const SecurityUserTokenPolicy& policy) {
		return std::make_pair<std::string, int>(std::string(policy.m_policyId), GetIntFromSecurityType(policy.m_securityType));
		});
	std::shared_ptr<ISoftingServerSettingsViewInput> input = m_ptrView.lock();
	if (input) {
		input->SetPolicyIds(std::move(policyIdsList));
	}
}
 
void SoftingServerSettingsPresenter::GetAggregates(std::vector<std::pair<std::string, int> >&& aggregates)
{

}

