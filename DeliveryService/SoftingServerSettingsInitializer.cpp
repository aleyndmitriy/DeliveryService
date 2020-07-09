#include"SoftingServerSettingsInitializer.h"
#include"SoftingServerSettingsController.h"
#include"SoftingServerSettingsPresenter.h"

int SoftingServerSettingsInitializer::CreateModule(HINSTANCE hInstance, HWND parent)
{
	SoftingServerSettingsPresenter* presenter = new SoftingServerSettingsPresenter();
	
	return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SOFTING_SERVER_SETTINGS_DIALOG), parent, SoftingSettingDlg_Proc, (LPARAM)presenter);
}