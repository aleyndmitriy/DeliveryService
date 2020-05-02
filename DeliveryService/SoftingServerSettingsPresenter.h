#pragma once
#include"ISoftingServerSettingsViewOutput.h"
#include"SoftingServerSettingsInteractorOutput.h"

class SoftingServerSettingsPresenter final: public std::enable_shared_from_this<SoftingServerSettingsPresenter>, public ISoftingServerSettingsViewOutput,
	public SoftingServerSettingsInteractorOutput
{
public:
	SoftingServerSettingsPresenter(std::shared_ptr<ConnectionAttributes> connectionAttributes, std::shared_ptr<DataTypeAttributes> dataAttributes);
	SoftingServerSettingsPresenter(const SoftingServerSettingsPresenter& src) = delete;
	SoftingServerSettingsPresenter& operator=(const SoftingServerSettingsPresenter& src) = delete;
	SoftingServerSettingsPresenter(SoftingServerSettingsPresenter&& src) = delete;
	SoftingServerSettingsPresenter& operator=(SoftingServerSettingsPresenter&& src) = delete;
	~SoftingServerSettingsPresenter();
	void SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input) override;
	void viewIsReady() override;
	void GetServerConfigurationViewOutput(std::string&& computerName, std::string&& serverName, unsigned int port) override;
	void GetServerSecurityConfigurationViewOutput(std::string&& securityConfiguration) override;
	void GetServerSecurityPolicyIdViewOutput(std::string&& policyId) override;
	void GetServerUserNameViewOutput(std::string&& userName, std::string&& password) override;
	void SendMessageError(std::string&& message) override;
	void SendWarning(std::string&& message) override;
	void SendMessageInfo(std::string&& message)override;
	void GetServers(std::vector<std::string>&& servers, std::string&& discoveryUrl) override;
	void SelectFoundedServer(const std::string& compName, unsigned int port, const std::string& serverName) override;
	void ChooseSecurityConfiguration() override;
	void GetEndPoints(std::vector<ServerSecurityModeConfiguration>&& servers) override;
	void GetPolicyIds(std::vector<SecurityUserTokenPolicy>&& policyIds) override;
	void GetAggregates(std::vector<std::pair<std::string, int> >&& aggregates) override;
private:
	std::weak_ptr<ISoftingServerSettingsViewInput> m_ptrView;
	std::shared_ptr<ConnectionAttributes> m_connectAttributes;
	std::shared_ptr<DataTypeAttributes> m_dataAttributes;
	std::vector<ServerSecurityModeConfiguration> m_endPointsConfigurations;
	std::vector<SecurityUserTokenPolicy> m_endPointPolicyIds;
	std::vector<std::pair<std::string, int> > m_aggregates;
	ServerSecurityModeConfiguration m_currentConfiguration;
	SecurityUserTokenPolicy m_currentPolicyId;
};