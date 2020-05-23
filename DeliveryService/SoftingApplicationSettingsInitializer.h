#pragma once
#include<Windows.h>
#include<memory>
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"

class SoftingApplicationSettingsInitializer final
{
public:
	static int CreateModule(HINSTANCE hInstance, HWND parent, std::shared_ptr<SoftingServerCertificateOwnSettings> certificateSettings, std::shared_ptr<SoftingServerCertificatePkiLocationSettings> pkiLocation);
};