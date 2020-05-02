#include"SoftingServerSettingsController.h"
#include"Utils.h"

SoftingServerSettingsController::SoftingServerSettingsController(HWND window, std::shared_ptr<ISoftingServerSettingsViewOutput> output): 
	m_hWindow(window), m_ptrPresenter(output), m_bIsOk(false)
{

}

SoftingServerSettingsController::~SoftingServerSettingsController()
{
	m_ptrPresenter.reset();
	EndDialog(m_hWindow, m_bIsOk);
	m_bIsOk = false;
	m_hWindow = NULL;
}

void SoftingServerSettingsController::setupInitialState()
{
	m_ptrPresenter->SetViewInput(shared_from_this());
}

void SoftingServerSettingsController::OnBtnBrowseNetworkTouched()
{

}

void SoftingServerSettingsController::OnBtnDiscoveryServerTouched()
{

}

void SoftingServerSettingsController::OnBtnGetServerPropertiesTouched()
{

}

void SoftingServerSettingsController::OnBtnOkTouched() {
	
	m_bIsOk = true;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingServerSettingsController::OnBtnCancelTouched()
{
	m_bIsOk = false;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingServerSettingsController::OnCbnSelchangeComboSelectServer()
{
	startLoading();
	readAttributes();
	getConfigurationsListForSelectedServer();
}

void SoftingServerSettingsController::OnCbnSelChangeComboConfiguration()
{
	startLoading();
	readAttributes();
	getPolicyListForSelectedConfiguration();
}

void SoftingServerSettingsController::OnCbnSelChangeComboPolicyId()
{
	startLoading();
	//SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)" ");
	readAttributes();
	//m_pSoftingInteractor->ChooseCurrentTokenPolicy();
}


void SoftingServerSettingsController::getConfigurationsListForSelectedServer()
{
	SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_RESETCONTENT, NULL, NULL);
	m_ptrPresenter->GetServerSecurityConfigurationViewOutput(std::string());
	//m_endPointsConfigurations.clear();
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)" ");
	m_ptrPresenter->GetServerSecurityPolicyIdViewOutput(std::string());
	//m_endPointPolicyIds.clear();
	
	//m_pSoftingInteractor->ChooseCurrentServer();
}

void SoftingServerSettingsController::getPolicyListForSelectedConfiguration()
{
	LRESULT index = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_GETCURSEL, NULL, NULL);
	if (index == CB_ERR) {
		return;
	}
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)" ");

	//m_pSoftingInteractor->ChooseCurrentEndPoint();
}

bool SoftingServerSettingsController::readText(int itemId, std::string& text)
{
	TCHAR szPathname[_MAX_PATH];
	memset(szPathname, '\0', _MAX_PATH);
	size_t len = GetDlgItemText(m_hWindow, itemId, szPathname, _MAX_PATH);
	if (len <= 0) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
		//MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONWARNING);
		return false;
	}
	text = std::string(szPathname);
	return true;
}

bool SoftingServerSettingsController::readComboText(int itemId, std::string& text)
{
	TCHAR szPathname[_MAX_PATH];
	memset(szPathname, '\0', _MAX_PATH);
	LRESULT ind = SendDlgItemMessage(m_hWindow, itemId, CB_GETCURSEL,NULL,NULL);
	if (ind == CB_ERR) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
		return false;
	}
	LRESULT res = SendDlgItemMessage(m_hWindow, itemId, CB_GETLBTEXTLEN, ind, NULL);
	if (res < 1 || res > _MAX_PATH) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
		return false;
	}
	res = SendDlgItemMessage(m_hWindow, itemId, CB_GETLBTEXT, ind, (LPARAM)szPathname);
	if (res == CB_ERR) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
		return false;
	}
	text = std::string(szPathname);
	return true;
}

void SoftingServerSettingsController::startLoading()
{
	HCURSOR hCurs = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCurs);
}

void SoftingServerSettingsController::stopLoading()
{
	HCURSOR hCurs = LoadCursor(NULL, IDC_ARROW);
	SetCursor(hCurs);
}


void SoftingServerSettingsController::readAttributes()
{
	std::string compName;
	if (!readText(IDC_COMPUTER_NAME_EDIT, compName)) {
		return;
	}
	std::string serverPort;
	if (!readText(IDC_PORT_EDIT, serverPort)) {
		return;
	}
	unsigned int port = std::stoul(serverPort);
	if (port < 1000) {
		std::string message = "Port number is not correct!";
		MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
		return;
	}

	std::string serverName;
	if (!readComboText(IDC_SELECT_SERVER_COMBO, serverName)) {
		return;
	}

	m_ptrPresenter->GetServerConfigurationViewOutput(std::move(compName), std::move(serverName), port);

	std::string serverConfig;
	if (!readComboText(IDC_CONFIGURATION_COMBO, serverConfig)) {
		m_ptrPresenter->GetServerSecurityConfigurationViewOutput(std::move(serverConfig));
	}

	std::string serverPolicy;
	if (!readComboText(IDC_POLICY_ID_COMBO, serverPolicy)) {
		m_ptrPresenter->GetServerSecurityPolicyIdViewOutput(std::move(serverPolicy));
	}

	std::string user;
	if (!readText(IDC_USER_NAME_EDIT, user)) {
		
	}

	std::string userPass;
	if (!readText(IDC_USER_PASSWORD_EDIT, userPass)) {
		return;
	}
	m_ptrPresenter->GetServerUserNameViewOutput(std::move(user), std::move(userPass));
}

INT_PTR WINAPI SoftingSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static std::shared_ptr<SoftingServerSettingsController> controller;
	switch (uMsg) {
	case WM_INITDIALOG:
		controller = std::make_shared<SoftingServerSettingsController>(hwnd, std::shared_ptr<ISoftingServerSettingsViewOutput>(reinterpret_cast<ISoftingServerSettingsViewOutput*>(lParam)));
		controller->setupInitialState();
		break;
	case WM_CLOSE:
		controller.reset();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			controller->OnBtnOkTouched();
			break;
		case IDCANCEL:
			controller->OnBtnCancelTouched();
			break;
		case IDC_BROWSE_NETWORK_BUTTON:
			controller->OnBtnBrowseNetworkTouched();
			break;
		case IDC_DICOVER_SERVER_LIST_BUTTON:
			controller->OnBtnDiscoveryServerTouched();
			break;
		case IDC_GET_SERVER_PROPERTIES_BUTTON:
			controller->OnBtnGetServerPropertiesTouched();
			break;
		case IDC_SELECT_SERVER_COMBO:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				controller->OnCbnSelchangeComboSelectServer();
				break;
			default:
				break;
			}
			break;
		case IDC_CONFIGURATION_COMBO:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				controller->OnCbnSelChangeComboConfiguration();
				break;
			default:
				break;
			}
			break;
		case IDC_POLICY_ID_COMBO:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				controller->OnCbnSelChangeComboPolicyId();
				break;
			default:
				break;
			}
			break;
		}
		break;
	}
	return(FALSE);
}

