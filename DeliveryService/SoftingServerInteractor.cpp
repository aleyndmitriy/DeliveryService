#include"SoftingServerInteractor.h"
#include"Utils.h"
#include"Constants.h"
#include<algorithm>

SoftingServerInteractor::SoftingServerInteractor(std::shared_ptr<SoftingServerInteractorOutput> output) :m_pOutput(output), m_pApp(), m_AppDesc(), m_enumResult(), m_serversList()
{
	m_enumResult = SoftingOPCToolbox5::loadToolbox(NULL);
	if (StatusCode::isBad(m_enumResult))
	{
		_tprintf(_T("ERROR: Failed to load the SDK: %s\n"), getEnumStatusCodeString(m_enumResult));
		return;
	}
	m_pApp = SoftingOPCToolbox5::Application::instance();
	InitApplicationDescription();	// this function is user defined
	// initialize the application (also initializes the underlying stack to get access to its functions)
	m_enumResult = m_pApp->initialize(&m_AppDesc);
	if (StatusCode::isBad(m_enumResult))
	{
		_tprintf(_T("ERROR: Failed to initialize the application: %s\n"), getEnumStatusCodeString(m_enumResult));
	}
	if (StatusCode::isGood(m_enumResult))
	{
		m_enumResult = m_pApp->start();
		if (StatusCode::isBad(m_enumResult))
		{
			_tprintf(_T("ERROR: Failed to start the application: %s\n"), getEnumStatusCodeString(m_enumResult));
		}
	}
}

SoftingServerInteractor::SoftingServerInteractor():SoftingServerInteractor(nullptr)
{

}

SoftingServerInteractor::~SoftingServerInteractor()
{
	if (StatusCode::isGood(m_enumResult))
	{
		m_enumResult = m_pApp->stop();
		if (StatusCode::isBad(m_enumResult))
		{
			_tprintf(_T("ERROR: An error occurred while stopping the application: %s\n"), getEnumStatusCodeString(m_enumResult));
		}

		m_enumResult = m_pApp->uninitialize();
		if (StatusCode::isBad(m_enumResult))
		{
			_tprintf(_T("ERROR: An error occurred while uninitializing the application: %s\n"), getEnumStatusCodeString(m_enumResult));
		}
	}
	m_enumResult = SoftingOPCToolbox5::unloadToolbox();
	if (StatusCode::isBad(m_enumResult))
	{
		_tprintf(_T("ERROR: An error occurred while unloading the SDK: %s\n"), getEnumStatusCodeString(m_enumResult));
	}
}

void SoftingServerInteractor::InitApplicationDescription()
{
	std::string hostName;
	if (getComputerName(hostName) == false)
	{
		// use the default host name
		hostName = std::string("localhost");
	}
	std::string folder = std::string("D:/VisualStudioProjects/DeliveryService/Debug");
	m_AppDesc.setApplicationType(EnumApplicationType_Server);
	m_AppDesc.setApplicationName(SoftingOPCToolbox5::LocalizedText(_T("Delivery Service Items Server"), _T("en")));
	m_AppDesc.setApplicationUri(_T("urn:") + hostName + folder + std::string(APPLICATION_NAME));	// The ApplicationUri should match with the URI in the application certificate
	m_AppDesc.setProductUri(_T("urn:") + folder + std::string(APPLICATION_NAME));
}

std::string SoftingServerInteractor::OpenConnection()
{
	GUID guid;
	if (CoCreateGuid(&guid) != S_OK) {
		return std::string();
	}
	WCHAR strGuide[MAX_UUID_LENGTH];
	int res = StringFromGUID2(guid, strGuide, MAX_UUID_LENGTH);
	std::string key = std::string(Wstr2Str(std::wstring(strGuide)));
	if (OpenConnectionWithUUID(key)) {
		return key;
	}
	else {
		return std::string();
	}
}

bool SoftingServerInteractor::OpenConnectionWithUUID(const std::string& connectionID)
{
	if (connectionID.empty()) {
		return false;
	}
	else {
		return true;
	}
}



