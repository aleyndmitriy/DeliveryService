#pragma once
#include"MainWindowViewOutput.h"
#include"SoftingServerInteractorOutput.h"
#include"ISoftingServerSettingsModuleOutput.h"
#include<memory>
#include<Windows.h>
#include<Toolbox.h>
#include<Application.h>

class MainWindowPresenter final : public std::enable_shared_from_this<MainWindowPresenter>, public IMainWindowViewOutput, public SoftingServerInteractorOutput, 
public ISoftingServerSettingsModuleOutput {
public:
	MainWindowPresenter();
	MainWindowPresenter(const MainWindowPresenter& src) = delete;
	MainWindowPresenter(MainWindowPresenter&& src) = delete;
	MainWindowPresenter& operator=(const MainWindowPresenter& src) = delete;
	MainWindowPresenter& operator=(MainWindowPresenter&& src) = delete;
	~MainWindowPresenter();
	void viewIsReady() override;
	void SetViewInput(std::shared_ptr<IMainWindowViewInput> input) override;
	void GetServerSettings(std::string&& serverName, unsigned int port, SoftingServerCertificateOwnSettings&& certificateSettings, SoftingServerCertificatePkiLocationSettings&& pkiSettings) override;
	void GetIpAddress() override;
	void CreateServiceSettingsModule() override;
	void GetMessageInfo(std::string message);
	void GetErrorInfo(std::string error);
	void GetIpAddressList();
	void SendMessageError(std::string&& message) override;
	void SendWarning(std::string&& message) override;
	void SendMessageInfo(std::string&& message)override;
	void GetServers(std::vector<std::string>&& servers, std::string&& discoveryUrl) override;
	void SelectFoundedServer(const std::string& compName, unsigned int port, const std::string& serverName) override;
	void ChooseSecurityConfiguration() override;
	void GetEndPoints(std::vector<ServerSecurityModeConfiguration>&& servers) override;
	void GetPolicyIds(std::vector<SecurityUserTokenPolicy>&& policyIds) override;
	void GetAggregates(std::vector<std::pair<std::string, int> >&& aggregates) override;
	void GetNewConnectionGuide(std::string&& uuid) override;
	void CloseConnectionWithGuide(std::string&& uuid) override;
private:
	std::weak_ptr<IMainWindowViewInput> m_ptrView;
	PTP_POOL m_pool = NULL;
	TP_CALLBACK_ENVIRON m_callBackEnviron;
	PTP_CLEANUP_GROUP m_cleanupGroup;
	PTP_WORK m_work;
};

VOID CALLBACK GetIPList(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext);