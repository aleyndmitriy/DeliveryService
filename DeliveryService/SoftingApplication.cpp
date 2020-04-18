#include"SoftingApplication.h"
#include "Utils.h"
#include"Constants.h"
#include<algorithm>

SoftingApplication::SoftingApplication() :m_pApp(), m_AppDesc(), m_enumResult(), m_CertificateInfo(), m_pkiStore(), m_pOutputList()
{

}

void SoftingApplication::SetSertificate(const SoftingServerCertificateOwnSettings& certificateInfo)
{
	if (m_pApp.isNull()) {
		m_CertificateInfo = certificateInfo;
	}
}

void SoftingApplication::SetPKILocation(const SoftingServerCertificatePkiLocationSettings& pkiLocation)
{
	if (m_pApp.isNull()) {
		m_pkiStore = pkiLocation;
	}
}


SoftingApplication::~SoftingApplication()
{
	stopApplication();
}

void SoftingApplication::AddDelegate(std::shared_ptr<SoftingApplicationOutput> delegate)
{
	std::vector< std::weak_ptr<SoftingApplicationOutput> >::iterator newEnd = std::remove_if(m_pOutputList.begin(), m_pOutputList.end(), [&](std::weak_ptr<SoftingApplicationOutput> ptr) {
		std::shared_ptr<SoftingApplicationOutput> output = ptr.lock();
		if (output == nullptr || output == delegate) {
			return true;
		}
		return false; });
	m_pOutputList.erase(newEnd, m_pOutputList.end());
	m_pOutputList.push_back(delegate);
}

void SoftingApplication::initApplicationDescription()
{
	std::string computerName;
	if (getComputerName(computerName) == false) {
		computerName = std::string("localhost");
	}
	m_AppDesc.clear();
	std::string folder = std::string("/ODS/DreamReport/System/");
	m_AppDesc.setApplicationType(EnumApplicationType_Client);
	m_AppDesc.setApplicationName(SoftingOPCToolbox5::LocalizedText(_T("DreamReport OpcUa Histotical Items Client"), _T("en")));
	m_AppDesc.setApplicationUri(_T("urn:") + computerName + folder + std::string(APPLICATION_NAME));	// The ApplicationUri should match with the URI in the application certificate
	m_AppDesc.setProductUri(_T("urn:") + folder + std::string(APPLICATION_NAME));
}

bool SoftingApplication::StartApplication()
{
	if (m_pApp.isNotNull()) {
		return true;
	}
	m_enumResult = SoftingOPCToolbox5::loadToolbox(NULL);
	if (StatusCode::isBad(m_enumResult))
	{
		std::string message = std::string("Failed to load the SDK: ") + std::string(getEnumStatusCodeString(m_enumResult));
		sendErrorMessageToDelegates(std::move(message));
		return false;
	}

	m_pApp = SoftingOPCToolbox5::Application::instance();
	if (!m_pkiStore.trustedFolderPath.empty()) {
		SoftingOPCToolbox5::PkiStoreConfiguration storeConfiguration;
		storeConfiguration.setCertificateTrustListLocation(m_pkiStore.trustedFolderPath.c_str());
		storeConfiguration.setCertificateRevocationListLocation(m_pkiStore.revocationFolderPath.c_str());
		storeConfiguration.setRejectedCertificateLocation(m_pkiStore.rejectedFolderPath.c_str());
		m_enumResult = m_pApp->setPkiStoreConfiguration(&storeConfiguration);
		if (StatusCode::isBad(m_enumResult))
		{
			std::string message = std::string("Failed to set the PKI store configuration: ") + std::string(getEnumStatusCodeString(m_enumResult));
			sendErrorMessageToDelegates(std::move(message));
			resetApplication();
			return false;
		}
	}
	
	initApplicationDescription();
	m_enumResult = m_pApp->initialize(&m_AppDesc);
	if (StatusCode::isBad(m_enumResult))
	{
		std::string message = std::string("Failed to initialize the application: ") + std::string(getEnumStatusCodeString(m_enumResult));
		sendErrorMessageToDelegates(std::move(message));
		resetApplication();
		return false;
	}

	if (StatusCode::isGood(m_enumResult))
	{
		if (m_CertificateInfo.certificatePath.empty() == false && m_CertificateInfo.privateKeyPath.empty() == false &&
			m_CertificateInfo.password.empty() == false) {
			m_enumResult = m_pApp->setInstanceCertificate(m_CertificateInfo.certificatePath.c_str(), m_CertificateInfo.privateKeyPath.c_str(), m_CertificateInfo.password.c_str());
			if (StatusCode::isBad(m_enumResult))
			{
				std::string message = std::string("Failed to load the application certificate: ") + std::string(getEnumStatusCodeString(m_enumResult));
				sendErrorMessageToDelegates(std::move(message));
				resetApplication();
				return false;
			}
		}
		m_enumResult = m_pApp->start();
		if (StatusCode::isBad(m_enumResult))
		{
			std::string message = std::string("Failed to start the application: ") + std::string(getEnumStatusCodeString(m_enumResult));
			sendErrorMessageToDelegates(std::move(message));
			resetApplication();
			return false;
		}
	}
	return true;
}

void SoftingApplication::resetApplication()
{
	m_pApp.reset();
	EnumStatusCode m_enumResult = SoftingOPCToolbox5::unloadToolbox();
	if (StatusCode::isBad(m_enumResult))
	{
		std::string message = std::string("An error occurred while unloading the SDK:") + std::string(getEnumStatusCodeString(m_enumResult));
		sendErrorMessageToDelegates(std::move(message));
	}
}

bool SoftingApplication::stopApplication()
{
	if (m_pApp.isNull()) {
		return true;
	}
	if (StatusCode::isGood(m_enumResult))
	{
		m_enumResult = m_pApp->stop();
		if (StatusCode::isBad(m_enumResult))
		{
			std::string message = std::string("An error occurred while stopping the application: ") + std::string(getEnumStatusCodeString(m_enumResult));
			sendErrorMessageToDelegates(std::move(message));
			resetApplication();
			return false;
		}

		m_enumResult = m_pApp->uninitialize();
		if (StatusCode::isBad(m_enumResult))
		{
			std::string message = std::string("An error occurred while uninitializing the application: ") + std::string(getEnumStatusCodeString(m_enumResult));
			sendErrorMessageToDelegates(std::move(message));
			resetApplication();
			return false;
		}
		m_AppDesc.clear();
		resetApplication();
	}
	return true;
}

EnumStatusCode SoftingApplication::AddSession(SoftingOPCToolbox5::Client::SessionPtr session)
{
	return  m_pApp->addSession(session);
}

EnumStatusCode SoftingApplication::RemoveSession(SoftingOPCToolbox5::Client::SessionPtr session)
{
	return  m_pApp->removeSession(session);
}


EnumStatusCode SoftingApplication::FindServers(const std::string& discoveryServerUrl, const std::vector<std::string>& serverURIs, std::vector<SoftingOPCToolbox5::ApplicationDescription>& serversList)
{
	return  m_pApp->findServers(discoveryServerUrl, serverURIs, serversList);
}


EnumStatusCode SoftingApplication::GetEndpointsFromServer(const std::string& serverUrl, const std::vector<std::string>& transportProfiles, std::vector<SoftingOPCToolbox5::EndpointDescription>& endpointDescriptions)
{
	return m_pApp->getEndpointsFromServer(serverUrl, transportProfiles, endpointDescriptions);
}

void SoftingApplication::sendErrorMessageToDelegates(std::string&& message)
{
	std::for_each(m_pOutputList.begin(), m_pOutputList.end(), [&](std::weak_ptr<SoftingApplicationOutput> ptr) {
		std::shared_ptr<SoftingApplicationOutput> output = ptr.lock();
		if (output) { output->SendMessageError(std::move(message)); }
		});
}


SoftingApplication& SoftingApplication::Instance()
{
	static SoftingApplication shared;
	return shared;
}
