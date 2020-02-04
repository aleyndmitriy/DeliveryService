#include"SoftingServerSettingsInitializer.h"
#include"SoftingServerSettingsController.h"
#include"SoftingServerSettingsPresenter.h"
int SoftingServerSettingsInitializer::CreateModule(HINSTANCE hInstance, HWND parent, std::shared_ptr<ISoftingServerSettingsModuleOutput> output)
{
	SoftingServerSettingsPresenter* presenter = new SoftingServerSettingsPresenter(output);
	
	return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SOFTING_SERVER_SETTINGS_DIALOG), parent, SoftingSettingDlg_Proc, (LPARAM)presenter);
}