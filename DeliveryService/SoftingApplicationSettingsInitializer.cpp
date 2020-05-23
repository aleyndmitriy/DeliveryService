#include"SoftingApplicationSettingsInitializer.h"
#include"SoftingApplicationSettingsController.h"
#include"SoftingApplicationSettingsPresenter.h"

int SoftingApplicationSettingsInitializer::CreateModule(HINSTANCE hInstance, HWND parent, std::shared_ptr<SoftingServerCertificateOwnSettings> certificateSettings, std::shared_ptr<SoftingServerCertificatePkiLocationSettings> pkiLocation)
{
	SoftingApplicationSettingsPresenter* presenter = new SoftingApplicationSettingsPresenter(certificateSettings, pkiLocation);

	return DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SOFTING_APPLICATION_SETTINGS_DIALOG), parent, SoftingAppSettingDlg_Proc, (LPARAM)presenter);
}