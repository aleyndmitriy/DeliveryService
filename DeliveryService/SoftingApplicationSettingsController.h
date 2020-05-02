#pragma once

#include<Windows.h>
#include"ISoftingApplicationSettingsViewOutput.h"
#include"resource.h"

class SoftingApplicationSettingsController final : public std::enable_shared_from_this<SoftingApplicationSettingsController>, public ISoftingApplicationSettingsViewInput
{
public:
	SoftingApplicationSettingsController(HWND window, std::shared_ptr<ISoftingApplicationSettingsViewOutput> output);
	SoftingApplicationSettingsController(SoftingApplicationSettingsController&& rhs) = delete;
	SoftingApplicationSettingsController& operator=(SoftingApplicationSettingsController&& rhs) = delete;
	SoftingApplicationSettingsController(const SoftingApplicationSettingsController& src) = delete;
	SoftingApplicationSettingsController& operator=(const SoftingApplicationSettingsController& rhs) = delete;
	~SoftingApplicationSettingsController();
	void setupInitialState() override;
	void OnBtnOkTouched();
	void OnBtnCancelTouched();
	void OnBtnChooseCertificatePathTouched();
	void OnBtnChoosePrivateKeyPathTouched();
	void OnBtnChoosePkiTrustedFolderPathTouched();
	void OnBtnChoosePkiRejectedFolderPathTouched();
	void OnBtnChoosePkiRevocationFolderPathTouched();
private:
	HWND m_hWindow;
	std::shared_ptr<ISoftingApplicationSettingsViewOutput> m_ptrPresenter;
	bool m_bIsOk;
	bool readText(int itemId, std::string& text);
	void writeTextFromPathDlg(int itemId);
	void readAttributes();
};

INT_PTR WINAPI SoftingAppSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);