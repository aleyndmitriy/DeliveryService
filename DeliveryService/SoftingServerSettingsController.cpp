#include"SoftingServerSettingsController.h"
#include"Utils.h"
#include<shlobj_core.h>

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
	SendDlgItemMessage(m_hWindow, IDC_COMPUTER_NAME_EDIT, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
	SendDlgItemMessage(m_hWindow, IDC_COMPUTER_NAME_EDIT, WM_CLEAR, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_PORT_EDIT, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
	SendDlgItemMessage(m_hWindow, IDC_PORT_EDIT, WM_CLEAR, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)"");
	SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
	SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_CLEAR, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_USER_PASSWORD_EDIT, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
	SendDlgItemMessage(m_hWindow, IDC_USER_PASSWORD_EDIT, WM_CLEAR, NULL, NULL);
	m_ptrPresenter->viewIsReady();
}

void SoftingServerSettingsController::SetNameOfComputer(const std::string& computerName)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_COMPUTER_NAME_EDIT, WM_SETTEXT, NULL, (LPARAM)computerName.c_str());
	if (!res) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
	}
	
}

void SoftingServerSettingsController::SetServerPort(const std::string& serverPort)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_PORT_EDIT, WM_SETTEXT, NULL, (LPARAM)serverPort.c_str());
	if (!res) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
	}
}

void SoftingServerSettingsController::SetServerName(const std::string& serverName)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_ADDSTRING, NULL, (LPARAM)serverName.c_str());
	if (res > CB_ERR) {
		res = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_SETCURSEL, (WPARAM)res, (LPARAM)NULL);
	}
	else {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
	}
}

void SoftingServerSettingsController::SetUserLogin(const std::string& login)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_SETTEXT, NULL, (LPARAM)login.c_str());
	if (!res) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
	}
}

void SoftingServerSettingsController::SetUserPassword(const std::string& password)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_USER_PASSWORD_EDIT, WM_SETTEXT, NULL, (LPARAM)password.c_str());
	if (!res) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
	}
}

void SoftingServerSettingsController::ClearSecurityPolicyView()
{
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)"");
}

void SoftingServerSettingsController::ClearServerConfigurationView()
{
	SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)"");
}

void SoftingServerSettingsController::ClearServerListView()
{
	SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_RESETCONTENT, NULL, NULL);
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)"");
}


void SoftingServerSettingsController::SetServerList(std::vector<std::string>&& servers)
{
	LRESULT res = CB_ERR;
	size_t index = 0;
	for (std::vector<std::string>::const_iterator itr = servers.cbegin(); itr != servers.cend(); itr++)
	{
		res = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_ADDSTRING, NULL, (LPARAM)itr->c_str());
		if (res > CB_ERR) {
			res = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_SETITEMDATA, (WPARAM)res, (LPARAM)index);
		}
		index++;
	}
	stopLoading();
}

void SoftingServerSettingsController::SetServerEndPoints(std::vector<std::string>&& endPoints)
{
	LRESULT res = CB_ERR;
	size_t index = 0;
	for(std::vector<std::string>::const_iterator itr = endPoints.cbegin(); itr != endPoints.cend(); itr++)
	{
		res = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_ADDSTRING, NULL, (LPARAM)itr->c_str());
		if (res > CB_ERR) {
			res = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_SETITEMDATA, (WPARAM)res, (LPARAM)index);
		}
		index++;
	}
	stopLoading();
}

void SoftingServerSettingsController::SelectEndPoint(int index)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_GETCOUNT, NULL, NULL);
	if (res > 0 && index > CB_ERR && index < res) {
		res = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_SETCURSEL, (WPARAM)index, NULL);
		if (res == CB_ERR) {
			DWORD err = GetLastError();
			std::string message = GetErrorText(err);
		}
	}
}

void SoftingServerSettingsController::SetPolicyIds(std::vector<std::pair<std::string, int> >&& policyIds)
{
	LRESULT res = CB_ERR;
	for (std::vector<std::pair<std::string, int> >::const_iterator itr = policyIds.cbegin(); itr != policyIds.cend(); itr++)
	{
		res = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_ADDSTRING, NULL, (LPARAM)itr->first.c_str());
		if (res > CB_ERR) {
			res = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_SETITEMDATA, (WPARAM)res, (LPARAM)itr->second);
		}
	}
}

void SoftingServerSettingsController::SelectPolicyId(int index)
{
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_GETCOUNT, NULL, NULL);
	if (res > 0 && index > CB_ERR && index < res) {
		res = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_SETCURSEL, (WPARAM)index, NULL);
		if (res == CB_ERR) {
			DWORD err = GetLastError();
			std::string message = GetErrorText(err);
		}
	}
}

void SoftingServerSettingsController::SelectPolicyAttribute(const std::string& attr)
{
	SendDlgItemMessage(m_hWindow, IDC_LOGIN_TYPE_STATIC, WM_SETTEXT, NULL, (LPARAM)attr.c_str());
}

void SoftingServerSettingsController::SetModeConfiguration(const std::string& serverSecurityName, const std::string& serverSecurityPolicy, const std::string& mode)
{
	std::string desc = serverSecurityName + std::string("#") + mode + std::string("#") + serverSecurityPolicy;
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_ADDSTRING, NULL, (LPARAM)desc.c_str());
	if (res > CB_ERR) {
		res = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_SETCURSEL, (WPARAM)res, (LPARAM)NULL);
	}
}

void SoftingServerSettingsController::OnEditComputerNameChanged()
{
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_COMPUTER_NAME_EDIT, WM_GETTEXTLENGTH, NULL, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT res = SendDlgItemMessage(m_hWindow, IDC_COMPUTER_NAME_EDIT, WM_GETTEXT, (WPARAM)textLength, (LPARAM)str);
			if (res == textLength - 1) {
				*(str + res) = '\0';
				m_ptrPresenter->UpdateComputerName(std::string(str));
			}
			free(str);
		}
	}
}

void SoftingServerSettingsController::OnEditPortChanged()
{
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_PORT_EDIT, WM_GETTEXTLENGTH, NULL, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT res = SendDlgItemMessage(m_hWindow, IDC_PORT_EDIT, WM_GETTEXT, (WPARAM)textLength, (LPARAM)str);
			if (res == textLength - 1) {
				*(str + res) = '\0';
				m_ptrPresenter->UpdatePortNumber(std::string(str));
			}
			free(str);
		}
	}
}


void SoftingServerSettingsController::OnEditLoginChanged()
{
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_GETTEXTLENGTH, NULL, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT res = SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_GETTEXT, (WPARAM)textLength, (LPARAM)str);
			if (res == textLength - 1) {
				*(str + res) = '\0';
				m_ptrPresenter->UpdateLogin(std::string(str));
			}
			free(str);
		}
	}
}

void SoftingServerSettingsController::OnEditPasswordChanged()
{
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_USER_PASSWORD_EDIT, WM_GETTEXTLENGTH, NULL, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT res = SendDlgItemMessage(m_hWindow, IDC_USER_PASSWORD_EDIT, WM_GETTEXT, (WPARAM)textLength, (LPARAM)str);
			if (res == textLength - 1) {
				*(str + res) = '\0';
				m_ptrPresenter->UpdatePassword(std::string(str));
			}
			free(str);
		}
	}
}


void SoftingServerSettingsController::OnBtnBrowseNetworkTouched()
{
	TCHAR szPathname[_MAX_PATH];
	BROWSEINFOA brs;
	brs.hwndOwner = m_hWindow;
	brs.pidlRoot = NULL;
	brs.pszDisplayName = szPathname;
	brs.lpszTitle = TEXT("Select Computer Name");
	brs.ulFlags = BIF_NONEWFOLDERBUTTON | BIF_BROWSEFORCOMPUTER;
	brs.lpfn = NULL;
	LPITEMIDLIST list = SHBrowseForFolderA(&brs);
	if (list != NULL) {
		LRESULT res = SendDlgItemMessage(m_hWindow, IDC_COMPUTER_NAME_EDIT, WM_SETTEXT, NULL, (LPARAM)szPathname);
		if (!res) {
			DWORD err = GetLastError();
			std::string message = GetErrorText(err);
		}
	}
}

void SoftingServerSettingsController::OnBtnDiscoveryServerTouched()
{
	startLoading();
	m_ptrPresenter->GetServersList();
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
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_GETCURSEL, NULL, NULL);
	if (res == CB_ERR) {
		stopLoading();
		return;
	}
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_GETLBTEXTLEN, (WPARAM)res, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT len = SendDlgItemMessage(m_hWindow, IDC_SELECT_SERVER_COMBO, CB_GETLBTEXT, (WPARAM)res, (LPARAM)str);
			if (len == textLength - 1) {
				*(str + len) = '\0';
				m_ptrPresenter->GetServerSecurityConfigurations(std::string(str));
			}
			free(str);
		}
	}
	stopLoading();
}

void SoftingServerSettingsController::OnCbnSelChangeComboConfiguration()
{
	startLoading();
	LRESULT index = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_GETCURSEL, NULL, NULL);
	if (index == CB_ERR) {
		stopLoading();
		return;
	}
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_GETLBTEXTLEN, (WPARAM)index, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT len = SendDlgItemMessage(m_hWindow, IDC_CONFIGURATION_COMBO, CB_GETLBTEXT, (WPARAM)index, (LPARAM)str);
			if (len == textLength - 1) {
				*(str + len) = '\0';
				m_ptrPresenter->GetServerSecurityPolicyIds(std::string(str));
			}
			free(str);
		}
	}
	stopLoading();
}

void SoftingServerSettingsController::OnCbnSelChangeComboPolicyId()
{
	startLoading();
	LRESULT index = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_GETCURSEL, NULL, NULL);
	if (index == CB_ERR) {
		stopLoading();
		return;
	}
	int type = (int)SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_GETITEMDATA, (WPARAM)index, NULL);
	LRESULT textLength = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_GETLBTEXTLEN, (WPARAM)index, NULL);
	if (textLength > 0) {
		++textLength;
		PTCHAR str = (PTCHAR)malloc(sizeof(TCHAR) * textLength);
		if (str != NULL) {
			LRESULT len = SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_COMBO, CB_GETLBTEXT, (WPARAM)index, (LPARAM)str);
			if (len == textLength - 1) {
				*(str + len) = '\0';
				m_ptrPresenter->UpdatePolicyIds(std::string(str),type);
			}
			free(str);
		}
	}
	stopLoading();
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
		case IDC_COMPUTER_NAME_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				controller->OnEditComputerNameChanged();
				break;
			default:
				break;
			}
			break;
		case IDC_PORT_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				controller->OnEditPortChanged();
				break;
			default:
				break;
			}
			break;
		case IDC_USER_NAME_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				controller->OnEditLoginChanged();
				break;
			default:
				break;
			}
			break;
		case IDC_USER_PASSWORD_EDIT:
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				controller->OnEditPasswordChanged();
				break;
			default:
				break;
			}
			break;
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

