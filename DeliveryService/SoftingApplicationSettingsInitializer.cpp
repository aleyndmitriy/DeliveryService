#include"SoftingApplicationSettingsInitializer.h"
#include"SoftingApplicationSettingsController.h"
#include"SoftingApplicationSettingsPresenter.h"

int SoftingApplicationSettingsInitializer::CreateModule(HINSTANCE hInstance, HWND parent)
{
	SoftingApplicationSettingsPresenter* presenter = new SoftingApplicationSettingsPresenter();
	return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SOFTING_APPLICATION_SETTINGS_DIALOG), parent, SoftingAppSettingDlg_Proc, (LPARAM)presenter);
}