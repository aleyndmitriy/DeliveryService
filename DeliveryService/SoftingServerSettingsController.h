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
	std::shared_ptr<ISoftingServerSettingsViewOutput> m_ptrPresenter;
	bool m_bIsOk;
	bool ReadText(int itemId, std::string& text);
	void WriteTextFromPathDlg(int itemId);
};

INT_PTR WINAPI SoftingSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);