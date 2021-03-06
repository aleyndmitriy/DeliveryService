#pragma once
#include<Toolbox.h>
#include<Application.h>
#include<ClientSession.h>
#include<memory>
#include"ConnectionAttributes.h"
#include "SoftingApplicationOutput.h"
#include"SoftingServerCertificateOwnSettings.h"
#include"SoftingServerCertificatePkiLocationSettings.h"

class SoftingApplication
{
	public:
		static  SoftingApplication& Instance();
		SoftingApplication(const SoftingApplication& src) = delete;
		SoftingApplication& operator=(const SoftingApplication& src) = delete;
		SoftingApplication(SoftingApplication&& src) = delete;
		SoftingApplication& operator=(SoftingApplication&& src) = delete;
		~SoftingApplication();
		void AddDelegate(std::shared_ptr<SoftingApplicationOutput> delegate);
		void SetSertificate(const SoftingServerCertificateOwnSettings& certificateInfo);
		void SetPKILocation(const SoftingServerCertificatePkiLocationSettings& pkiLocation);
		bool StartApplication();
		EnumStatusCode AddSession(SoftingOPCToolbox5::Client::SessionPtr session);
		EnumStatusCode RemoveSession(SoftingOPCToolbox5::Client::SessionPtr session);
		EnumStatusCode FindServers(const std::string& discoveryServerUrl, const std::vector<std::string>& serverURIs, std::vector<SoftingOPCToolbox5::ApplicationDescription>& serversList);
		EnumStatusCode GetEndpointsFromServer(const std::string& serverUrl, const std::vector<std::string>& transportProfiles, std::vector<SoftingOPCToolbox5::EndpointDescription>& endpointDescriptions);
	private:
		SoftingApplication();
		SoftingOPCToolbox5::ApplicationPtr m_pApp;
		SoftingOPCToolbox5::ApplicationDescription m_AppDesc;
		EnumStatusCode m_enumResult;
		SoftingServerCertificateOwnSettings m_CertificateInfo;
		SoftingServerCertificatePkiLocationSettings m_pkiStore;
		std::vector<std::weak_ptr<SoftingApplicationOutput> > m_pOutputList;
		void resetApplication();
		bool stopApplication();
		void initApplicationDescription();
		void sendErrorMessageToDelegates(std::string&& message);
	};