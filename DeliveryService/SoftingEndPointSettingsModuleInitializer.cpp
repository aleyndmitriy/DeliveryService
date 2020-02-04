#include"SoftingEndPointSettingsModuleInitializer.h"
#include"SoftingEndPointSettingsController.h"
#include"SoftingEndPointSettingsPresenter.h"
int SoftingEndPointSettingsModuleInitializer::CreateModule(HINSTANCE hInstance, HWND parent, std::shared_ptr<ISoftingEndPointSettingsModuleOutput> output)
{
	SoftingEndPointSettingsPresenter* presenter = new SoftingEndPointSettingsPresenter(output);
	return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_ENDPOINT_SETTINGSDIALOG), parent, SoftingEndPointSettingDlg_Proc, (LPARAM)presenter);
}