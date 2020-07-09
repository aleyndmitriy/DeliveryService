#pragma once
#include"ISoftingServerSettingsViewOutput.h"
#include"SoftingServerInteractorOutput.h"
#include"SoftingServerInteractor.h"

class SoftingServerSettingsPresenter final: public std::enable_shared_from_this<SoftingServerSettingsPresenter>, public ISoftingServerSettingsViewOutput,
	public SoftingServerInteractorOutput
{
public:
	SoftingServerSettingsPresenter();
	SoftingServerSettingsPresenter(const SoftingServerSettingsPresenter& src) = delete;
	SoftingServerSettingsPresenter& operator=(const SoftingServerSettingsPresenter& src) = delete;
	SoftingServerSettingsPresenter(SoftingServerSettingsPresenter&& src) = delete;
	SoftingServerSettingsPresenter& operator=(SoftingServerSettingsPresenter&& src) = delete;
	~SoftingServerSettingsPresenter();
	void SetViewInput(std::shared_ptr<ISoftingServerSettingsViewInput> input) override;
	void viewIsReady() override;
	void UpdateComputerName(std::string&& compName) override;
	void UpdatePortNumber(std::string&& strPort) override;
	void UpdateLogin(std::string&& login) override;
	void UpdatePassword(std::string&& password) override;
	void GetServersList() override;
	void GetServerSecurityConfigurations(std::string&& serverName) override;
	void GetServerSecurityPolicyIds(std::string&& endPoint) override;
	void UpdatePolicyIds(std::string&& policyId, int securityType) override;
	void SendMessageError(std::string&& message) override;
	void SendWarning(std::string&& message) override;
	void SendMessageInfo(std::string&& message)override;
	void GetServers(std::vector<std::string>&& servers, std::string&& discoveryUrl) override;
	void SelectFoundedServer(const std::string& compName, unsigned int port, const std::string& serverName) override;
	void ChooseSecurityConfiguration() override;
	void GetEndPoints(std::vector<ServerSecurityModeConfiguration>&& endPoints) override;
	void GetPolicyIds(std::vector<SecurityUserTokenPolicy>&& policyIds) override;
	void GetAggregates(std::vector<std::pair<std::string, int> >&& aggregates) override;
	void GetRecords(std::map<std::string, std::vector<Record> >&& recordsData) override;
	void GetTags(std::set<TagInfo>&& tagsData) override;
	void GetNewConnectionGuide(std::string&& uuid) override;
	void CloseConnectionWithGuide(std::string&& uuid) override;
private:
	std::weak_ptr<ISoftingServerSettingsViewInput> m_ptrView;
	std::shared_ptr<ConnectionAttributes> m_connectAttributes;
	std::shared_ptr<DataTypeAttributes> m_dataAttributes;
	std::unique_ptr<SoftingServerInteractor> m_pSoftingInteractor;
	std::vector<ServerSecurityModeConfiguration> m_endPointsConfigurations;
	std::vector<SecurityUserTokenPolicy> m_endPointPolicyIds;
	std::vector<std::pair<std::string, int> > m_aggregates;
};