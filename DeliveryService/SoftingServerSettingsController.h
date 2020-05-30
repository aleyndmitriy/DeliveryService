#pragma once
#include<Windows.h>
#include"ISoftingServerSettingsViewOutput.h"
#include"resource.h"

class SoftingServerSettingsController final : public std::enable_shared_from_this<SoftingServerSettingsController>, public ISoftingServerSettingsViewInput
{
public:
	SoftingServerSettingsController(HWND window, std::shared_ptr<ISoftingServerSettingsViewOutput> output);
	SoftingServerSettingsController(SoftingServerSettingsController&& rhs) = delete;
	SoftingServerSettingsController& operator=(SoftingServerSettingsController&& rhs) = delete;
	SoftingServerSettingsController(const SoftingServerSettingsController& src) = delete;
	SoftingServerSettingsController& operator=(const SoftingServerSettingsController& rhs) = delete;
	~SoftingServerSettingsController();
	void setupInitialState();
	void OnEditComputerNameChanged();
	void OnEditPortChanged();
	void OnEditLoginChanged();
	void OnEditPasswordChanged();
	void OnBtnBrowseNetworkTouched();
	void OnBtnDiscoveryServerTouched();
	void OnBtnGetServerPropertiesTouched();
	void OnBtnOkTouched();
	void OnBtnCancelTouched();
	void OnCbnSelchangeComboSelectServer();
	void OnCbnSelChangeComboConfiguration();
	void OnCbnSelChangeComboPolicyId();
	void SetNameOfComputer(const std::string& computerName) override;
	void SetServerPort(const std::string& serverPort) override;
	void SetServerName(const std::string& serverName) override;
	void SetServerList(std::vector<std::string>&& servers) override;
	void SetServerEndPoints(std::vector<std::string>&& endPoints) override;
	void SelectEndPoint(int index) override;
	void SetPolicyIds(std::vector<std::pair<std::string, int> >&& policyIds) override;
	void SelectPolicyId(int index) override;
	void SelectPolicyAttribute(const std::string& attr) override;
	void SetUserLogin(const std::string& login) override;
	void SetUserPassword(const std::string& password) override;
	void ClearSecurityPolicyView() override;
	void ClearServerConfigurationView() override;
	void ClearServerListView() override;
	void SetModeConfiguration(const std::string& serverSecurityName, const std::string& serverSecurityPolicy, const std::string& mode) override;
private:
	HWND m_hWindow;
	std::shared_ptr<ISoftingServerSettingsViewOutput> m_ptrPresenter;
	bool m_bIsOk;
	bool readText(int itemId, std::string& text);
	bool readComboText(int itemId, std::string& text);
	void startLoading();
	void stopLoading();
};

INT_PTR WINAPI SoftingSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);