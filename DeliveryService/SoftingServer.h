#pragma once
#include<Toolbox.h>
#include<Application.h>
#include<memory>
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"
#include"SoftingServerOutput.h"

class SoftingServer final {
public:
	static SoftingServer& Instance();
	SoftingServer(const SoftingServer& src) = delete;
	SoftingServer& operator=(const SoftingServer& src) = delete;
	SoftingServer(SoftingServer&& src) = delete;
	SoftingServer& operator=(SoftingServer&& src) = delete;
	~SoftingServer();
	

private:
	SoftingServer() = default;
	std::weak_ptr<SoftingServerOutput> m_pOutput;
	SoftingOPCToolbox5::ApplicationPtr m_pApp;
	std::unique_ptr<SoftingOPCToolbox5::ApplicationDescription> m_AppDesc;

};