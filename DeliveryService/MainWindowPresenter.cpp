#include"MainWindowPresenter.h"
#include"SoftingServerSettingsInitializer.h"
#include"Utils.h"
#include"Constants.h"
#include<functional>

MainWindowPresenter::MainWindowPresenter() :m_ptrView(), m_pool(nullptr), m_callBackEnviron{ 0 }, m_cleanupGroup(NULL), m_work(NULL)
{
	InitializeThreadpoolEnvironment(&m_callBackEnviron);
}

MainWindowPresenter::~MainWindowPresenter()
{
	CloseThreadpoolCleanupGroupMembers(m_cleanupGroup, FALSE, NULL);
	CloseThreadpoolCleanupGroup(m_cleanupGroup);
	CloseThreadpool(m_pool);
	m_ptrView.reset();
}

void MainWindowPresenter::viewIsReady()
{
	std::shared_ptr<IMainWindowViewInput> view = m_ptrView.lock();
	if (view) {
		m_pool = CreateThreadpool(NULL);
		if (m_pool) {
			SetThreadpoolThreadMaximum(m_pool, 1);
			BOOL bRet = SetThreadpoolThreadMinimum(m_pool, 1);
			if (bRet == FALSE) {
				CloseThreadpool(m_pool);
				DWORD err = GetLastError();
				view->ErrorMessage(GetErrorText(err));
			}
			else {
				m_cleanupGroup = CreateThreadpoolCleanupGroup();
				if (m_cleanupGroup == NULL) {
					CloseThreadpool(m_pool);
					DWORD err = GetLastError();
					view->ErrorMessage(GetErrorText(err));
				}
				else {
					SetThreadpoolCallbackPool(&m_callBackEnviron, m_pool);
					SetThreadpoolCallbackCleanupGroup(&m_callBackEnviron, m_cleanupGroup, NULL);
				}
			}
		}
		else {
			DWORD err = GetLastError();
				view->ErrorMessage(GetErrorText(err));
		}
	}
}

void MainWindowPresenter::SetViewInput(std::shared_ptr<IMainWindowViewInput> input)
{
	m_ptrView = input;
}

void MainWindowPresenter::GetIpAddress()
{
	std::shared_ptr<IMainWindowViewInput> view = m_ptrView.lock();
	if (view) {
		view->StartLoading();
		BOOL isSubmit = TrySubmitThreadpoolCallback(GetIPList, this, &m_callBackEnviron);
		if (!isSubmit) {
			view->StopLoading();
			DWORD err = GetLastError();
			view->ErrorMessage(GetErrorText(err));
		}
		//SubmitThreadpoolWork(m_work);
	}
}

void MainWindowPresenter::GetMessageInfo(std::string message)
{
	std::shared_ptr<IMainWindowViewInput> view = m_ptrView.lock();

}
void MainWindowPresenter::GetErrorInfo(std::string error)
{
	std::shared_ptr<IMainWindowViewInput> view = m_ptrView.lock();
	if (view) {
		view->ErrorMessage(error);
	}
}

void MainWindowPresenter::GetIpAddressList()
{
	std::shared_ptr<IMainWindowViewInput> view = m_ptrView.lock();
	if (view) {
		DWORD curID = GetCurrentThreadId();
		//Sleep(2000);
		view->StopLoading();
		//CloseThreadpoolWork(m_work);
	}
}

void MainWindowPresenter::CreateServiceSettingsModule()
{
	std::shared_ptr<IMainWindowViewInput> view = m_ptrView.lock();
	if (view) {
		int res = SoftingServerSettingsInitializer::CreateModule(view->GetAppInstance(),view->GetWindowHandle(), shared_from_this());
		if (res) {

		}
	}
}



VOID CALLBACK GetIPList(PTP_CALLBACK_INSTANCE pInstance, PVOID pvContext)
{
	UNREFERENCED_PARAMETER(pInstance);
	MainWindowPresenter* presenter = reinterpret_cast<MainWindowPresenter*>(pvContext);
	if (presenter == nullptr) {
		return;
	}
	DWORD curID = GetCurrentThreadId();
	HMODULE hConnectionDll = GetModuleHandle(NETWORK_LIBRARY);
	if (!hConnectionDll) {
		hConnectionDll = LoadLibraryEx(NETWORK_LIBRARY, NULL, 0);
		if (!hConnectionDll) {
			DWORD err = GetLastError();
			presenter->GetErrorInfo(GetErrorText(err));
			return;
		}
	}
	typedef int (CALLBACK* GetIPInterfaces)(char** ipv4List, int* ipv4Number, char** ipv6List, int* ipv6Number);
	GetIPInterfaces getInterfaces = (GetIPInterfaces)GetProcAddress(hConnectionDll, "_GetIPInterfaces@16");
	if (getInterfaces != NULL) {
		int ip4Num = 0;
		char* ip4List = nullptr;
		int ip6Num = 0;
		char* ip6List = nullptr;
		if (getInterfaces(&ip4List, &ip4Num, &ip6List, &ip6Num)) {
			
		}
		presenter->GetIpAddressList();
	}
	else {
		presenter->GetErrorInfo(std::string("Can't get Ip interfaces"));
	}
}
