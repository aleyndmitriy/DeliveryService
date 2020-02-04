#pragma once
#include<Toolbox.h>
#include<Application.h>
#include<memory>
#include"SoftingServerInteractorOutput.h"

class SoftingServerInteractor {
public:
	SoftingServerInteractor(std::shared_ptr<SoftingServerInteractorOutput> output);
	SoftingServerInteractor();
	~SoftingServerInteractor();
	bool OpenConnectionWithUUID(const std::string& connectionID);
	std::string OpenConnection();
private:
	std::weak_ptr<SoftingServerInteractorOutput> m_pOutput;
	SoftingOPCToolbox5::ApplicationPtr m_pApp;
	SoftingOPCToolbox5::ApplicationDescription m_AppDesc;
	EnumStatusCode m_enumResult;
	std::vector<SoftingOPCToolbox5::ApplicationDescription> m_serversList;
	void InitApplicationDescription();
};