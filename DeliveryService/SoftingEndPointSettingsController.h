#pragma once
#include<Windows.h>
#include<CommCtrl.h>
#include"resource.h"

#include"ISoftingEndPointSettingsViewOutput.h"

class SoftingEndPointSettingsController final :public std::enable_shared_from_this<SoftingEndPointSettingsController>, public ISoftingEndPointSettingsViewInput
{
public:
	SoftingEndPointSettingsController(HWND window, std::shared_ptr<ISoftingEndPointSettingsViewOutput> output);
	SoftingEndPointSettingsController(const SoftingEndPointSettingsController& src) = delete;
	SoftingEndPointSettingsController& operator=(const SoftingEndPointSettingsController& src) = delete;
	SoftingEndPointSettingsController(SoftingEndPointSettingsController&& src) = delete;
	SoftingEndPointSettingsController& operator=(SoftingEndPointSettingsController&& src) = delete;
	~SoftingEndPointSettingsController();
	void setupInitialState() override;
	void WarningMessage(std::string message) override;
	void ErrorMessage(std::string message) override;
	void AddEndPoint(std::string endPointUrl) override;
	void AddUserPolicy(const SoftingServerUserPolicySettings& userPolicy, int index) override;
	void SelectedUserPolicy(const SoftingServerUserPolicySettings& userPolicy) override;
	void SelectedEndPointConfigurations(const std::set<int>& configs) override;
	void StartLoading() override;
	void StopLoading() override;
	void ClearEndPointView();
	void ClearUserPolicyView();
	void SelectEndPoint(std::string endPointUrl);
	void SelectUserPolicy(int index);
	void UnselectUserPolicy();
	void AddEndPoint();
	void AddUserPolicy();
	void RemoveEndPoint();
	void RemoveUserPolicy();
	void RemoveAllUserPolicies();
	void OnBtnOkTouched();
	void OnBtnCancelTouched();
private:
	HWND m_hWindow;
	std::shared_ptr<ISoftingEndPointSettingsViewOutput> m_ptrPresenter;
	bool m_bIsOk;
	void createEndPointList();
	void createUserPolicyList();
	void enableUserPolicyView(BOOL bEnable);
	void activateEndPointView(std::string endPointUrl);
	void createConfigurationsList();
	void createTokenTypesList();
	std::string getConfigurationsList(int index);
};

INT_PTR WINAPI SoftingEndPointSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);