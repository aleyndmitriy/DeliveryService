#include"SoftingEndPointSettingsController.h"
#include<strsafe.h>
#include"Constants.h"
SoftingEndPointSettingsController::SoftingEndPointSettingsController(HWND window, std::shared_ptr<ISoftingEndPointSettingsViewOutput> output):
	m_hWindow(window), m_ptrPresenter(output), m_bIsOk(false)
{

}

SoftingEndPointSettingsController::~SoftingEndPointSettingsController()
{
	m_ptrPresenter.reset();
	EndDialog(m_hWindow, m_bIsOk);
	m_bIsOk = false;
	m_hWindow = NULL;
}

void SoftingEndPointSettingsController::setupInitialState()
{
	m_ptrPresenter->SetViewInput(shared_from_this());
	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);
	createEndPointList();
	createUserPolicyList();
	enableUserPolicyView(FALSE);
	createConfigurationsList();
	createTokenTypesList();
	m_ptrPresenter->viewIsReady();
}

void SoftingEndPointSettingsController::createConfigurationsList()
{
	for (int ind = 0; ind < MAX_END_POINT_SECURITY_CONFIGURATIONS; ind++) {
		SendDlgItemMessage(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST, LB_ADDSTRING, 0, (LPARAM)getConfigurationsList(ind).c_str());
	}
}

std::string SoftingEndPointSettingsController::getConfigurationsList(int index)
{
	switch (index) {
	case 1:
		return std::string("SIGN BASIC128 RSA15");
		break;
	case 2:
		return std::string("SIGN BASIC256");
		break;
	case 3:
		return std::string("SIGN BASIC256 SHA256");
		break;
	case 4:
		return std::string("SIGN_AES128_SHA256_RSA_OAEP");
		break;
	case 5:
		return std::string("SIGN AES256 SHA256 RSA_PSS");
		break;
	case 6:
		return std::string("SIGN AES128 SHA256 NIST_P256");
		break;
	case 7:
		return std::string("SIGN AES256 SHA384 NIST_P384");
		break;
	case 8:
		return std::string("SIGN AES128 SHA256 BRAINPOOL P256_R1");
		break;
	case 9:
		return std::string("SIGN AES256 SHA384 BRAINPOOL P384_R1");
		break;
	case 10:
		return std::string("SIGN AES128 SHA256 CURVE25519");
		break;
	case 11:
		return std::string("SIGN AES256 SHA384 CURVE448");
		break;
	case 12:
		return std::string("SIGN AND ENCRYPT BASIC128 RSA15");
		break;
	case 13:
		return std::string("SIGN AND ENCRYPT BASIC256");
		break;
	case 14:
		return std::string("SIGN AND ENCRYPT BASIC256 SHA256");
		break;
	case 15:
		return std::string("SIGN AND ENCRYPT AES128 SHA256 RSA OAEP");
		break;
	case 16:
		return std::string("SIGN AND ENCRYPT AES256 SHA256 RSA_PSS");
		break;
	case 17:
		return std::string("SIGN AND ENCRYPT AES128 SHA256 NIST_P256");
		break;
	case 18:
		return std::string("SIGN AND ENCRYPT AES256 SHA384 NIST_P384");
		break;
	case 19:
		return std::string("SIGN AND ENCRYPT AES128 SHA256 BRAINPOOL P256_R1");
		break;
	case 20:
		return std::string("SIGN AND ENCRYPT AES256 SHA384 BRAINPOOL P384_R1");
		break;
	case 21:
		return std::string("SIGN AND ENCRYPT AES128 SHA256 CURVE25519");
		break;
	case 22:
		return std::string("SIGN AND ENCRYPT AES256 SHA384 CURVE448");
		break;
	default:
		return std::string("NONE");
		break;
	}
}

void SoftingEndPointSettingsController::createTokenTypesList()
{
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_RESETCONTENT, 0, 0);
	LRESULT pos = 0;
	pos = SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_ADDSTRING, 0, (LPARAM)TEXT("ANONYMOUS"));
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_SETITEMDATA, pos, (LPARAM)0);
	pos = SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_ADDSTRING, 0, (LPARAM)TEXT("USER NAME"));
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_SETITEMDATA, pos, (LPARAM)1);
	pos = SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_ADDSTRING, 0, (LPARAM)TEXT("CERTIFICATE"));
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_SETITEMDATA, pos, (LPARAM)2);
	pos = SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_ADDSTRING, 0, (LPARAM)TEXT("ISSUED TOKEN"));
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_SETITEMDATA, pos, (LPARAM)3);
}

void SoftingEndPointSettingsController::WarningMessage(std::string message)
{
	MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONWARNING);
}

void SoftingEndPointSettingsController::ErrorMessage(std::string message)
{
	MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
}

void SoftingEndPointSettingsController::SelectEndPoint(std::string endPointUrl)
{
	activateEndPointView(endPointUrl);
	m_ptrPresenter->SelectEndPoint(endPointUrl);
	EnableWindow(GetDlgItem(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST), FALSE);
}

void SoftingEndPointSettingsController::SelectUserPolicy(int index)
{
	TCHAR wchEndPointName[MAX_PATH];
	GetDlgItemText(m_hWindow, IDC_END_POINT_URL_EDIT, wchEndPointName, MAX_PATH);
	std::string endPointName = std::string(wchEndPointName);
	if (index > -1)
	{
		TCHAR policyId[MAX_PATH];
		LVITEM item;
		item.iSubItem = 0;
		item.cchTextMax = MAX_PATH;
		item.pszText = policyId;
		int len = SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);
		if (len < MAX_PATH && len > 0) {
			policyId[len] = '\0';
			m_ptrPresenter->SelectUserPolicy(std::string(policyId), endPointName);
		}
	}
	
}

void SoftingEndPointSettingsController::UnselectUserPolicy()
{
	ClearUserPolicyView();
	enableUserPolicyView(TRUE);
	EnableWindow(GetDlgItem(m_hWindow, IDC_REMOVE_USER_POLICY_BUTTON), FALSE);
}


void SoftingEndPointSettingsController::activateEndPointView(std::string endPointUrl)
{
	SendDlgItemMessage(m_hWindow, IDC_END_POINT_URL_EDIT, EM_SETSEL, 0, -1);
	SendDlgItemMessage(m_hWindow, IDC_END_POINT_URL_EDIT, WM_CLEAR, 0, 0);
	EnableWindow(GetDlgItem(m_hWindow, IDC_ADD_ENDPOINT_BUTTON), FALSE);
	
	SendDlgItemMessage(m_hWindow, IDC_END_POINT_URL_EDIT, WM_SETTEXT, 0, (LPARAM)endPointUrl.c_str());
	EnableWindow(GetDlgItem(m_hWindow, IDC_END_POINT_URL_EDIT), FALSE);
	enableUserPolicyView(TRUE);
}

void SoftingEndPointSettingsController::AddEndPoint(std::string endPointUrl)
{
	HWND hUrlListControl = GetDlgItem(m_hWindow, IDC_END_POINT_LIST);
	LVITEM item;
	TCHAR wchUrlName[_MAX_PATH];
	StringCchCopy(wchUrlName, endPointUrl.length() + 1, endPointUrl.c_str());
	item.pszText = wchUrlName;
	item.mask = LVIF_TEXT | LVIF_STATE;
	item.stateMask = (UINT)-1;
	item.cchTextMax = endPointUrl.length() + 1;
	item.iSubItem = 0;
	item.state = 0;// LVIS_FOCUSED | LVIS_SELECTED;
	item.iItem = 0;
	item.cColumns = 1;
	item.lParam = 0;
	SendMessage(hUrlListControl, LVM_INSERTITEM, 0, (LPARAM)&item);
}

void SoftingEndPointSettingsController::AddEndPoint()
{
	TCHAR wendPointName[MAX_PATH];
	GetDlgItemText(m_hWindow, IDC_END_POINT_URL_EDIT, wendPointName, MAX_PATH);
	int configs[MAX_END_POINT_SECURITY_CONFIGURATIONS];
	int number = SendDlgItemMessage(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST, LB_GETSELITEMS, MAX_END_POINT_SECURITY_CONFIGURATIONS, (LPARAM)configs);
	std::set<int> numbers;
	for (int ind = 0; ind < number; ind++) {
		numbers.insert(configs[ind]);
	}
	m_ptrPresenter->AddEndPoint(std::string(wendPointName),numbers);

}


void SoftingEndPointSettingsController::RemoveEndPoint()
{
	TCHAR wendPointName[MAX_PATH];
	GetDlgItemText(m_hWindow, IDC_END_POINT_URL_EDIT, wendPointName, MAX_PATH);
	std::string endPointName = std::string(wendPointName);
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_END_POINT_LIST, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_FOCUSED);
	if (res > -1) {
		m_ptrPresenter->RemoveEndPoint(endPointName);
		SendDlgItemMessage(m_hWindow, IDC_END_POINT_LIST, LVM_DELETEITEM, (WPARAM)res, (LPARAM)0);
		ClearEndPointView();
	}
}

void SoftingEndPointSettingsController::AddUserPolicy()
{
	TCHAR wendPointName[MAX_PATH];
	GetDlgItemText(m_hWindow, IDC_END_POINT_URL_EDIT, wendPointName, MAX_PATH);
	std::string endPointName = std::string(wendPointName);
	LRESULT index = SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_GETCURSEL, 0, 0);
	if (index > CB_ERR) {
		int mode = SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_GETITEMDATA, index, 0);
		if (mode < 4) {
			TCHAR policy[MAX_PATH];
			UINT len = GetDlgItemText(m_hWindow, IDC_POLICY_ID_EDIT, policy, MAX_PATH);
			if (len < MAX_PATH) {
				policy[len] = '\0';
			}
			std::string policyId(policy);
			len = GetDlgItemText(m_hWindow, IDC_POLICY_URI_EDIT, policy, MAX_PATH);
			if (len < MAX_PATH) {
				policy[len] = '\0';
			}
			std::string policyUri(policy);
			len = GetDlgItemText(m_hWindow, IDC_USER_NAME_EDIT, policy, MAX_PATH);
			if (len < MAX_PATH) {
				policy[len] = '\0';
			}
			std::string policyUserName(policy);
			len = GetDlgItemText(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT, policy, MAX_PATH);
			if (len < MAX_PATH) {
				policy[len] = '\0';
			}
			std::string policyUserNamePassword(policy);
			SoftingServerUserPolicySettings settings(policyId, policyUri, policyUserName, policyUserNamePassword, mode);
			m_ptrPresenter->AddUserPolicy(std::move(settings), endPointName);
		}
	}
}

void SoftingEndPointSettingsController::RemoveUserPolicy()
{
	CHAR wendPointName[MAX_PATH];
	GetDlgItemText(m_hWindow, IDC_END_POINT_URL_EDIT, wendPointName, MAX_PATH);
	std::string endPointName = std::string(wendPointName);
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_FOCUSED);
	if (res > -1)
	{
		TCHAR policyId[MAX_PATH];
		LVITEM item;
		item.iSubItem = 0;
		item.cchTextMax = MAX_PATH;
		item.pszText = policyId;
		int len = SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_GETITEMTEXT, (WPARAM)res, (LPARAM)&item);
		if (len < MAX_PATH && len > 0) {
			policyId[len] = '\0';
			m_ptrPresenter->RemoveUserPolicy(std::string(policyId), endPointName);
			SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_DELETEITEM, (WPARAM)res, (LPARAM)0);
		}
	}
}


void SoftingEndPointSettingsController::RemoveAllUserPolicies()
{
	CHAR wendPointName[MAX_PATH];
	GetDlgItemText(m_hWindow, IDC_END_POINT_URL_EDIT, wendPointName, MAX_PATH);
	std::string endPointName = std::string(wendPointName);
	LRESULT res = SendDlgItemMessage(m_hWindow, IDC_END_POINT_LIST, LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_FOCUSED);
	if (res > -1)
	{
		m_ptrPresenter->RemoveAllUserPolicies(endPointName);
		SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_DELETEALLITEMS, 0, 0);
		ClearUserPolicyView();
	}
}

void SoftingEndPointSettingsController::AddUserPolicy(const SoftingServerUserPolicySettings& userPolicy, int index)
{
	LVITEM item;
	TCHAR policyId[MAX_PATH];
	TCHAR policyUri[MAX_PATH];
	TCHAR policyType[15];
	StringCchCopy(policyId, userPolicy.policyId.size() + 1, userPolicy.policyId.c_str());
	item.pszText = policyId;
	item.mask = LVIF_TEXT | LVIF_STATE;
	item.stateMask = (UINT)-1;
	item.cchTextMax = MAX_PATH;
	item.iSubItem = 0;
	item.state = 0;// LVIS_FOCUSED | LVIS_SELECTED;
	item.iItem = index;
	item.cColumns = 3;
	item.lParam = 0;
	SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_INSERTITEM, 0, (LPARAM)&item);
	StringCchCopy(policyUri, userPolicy.policyUri.size() + 1, userPolicy.policyUri.c_str());
	item.iSubItem = 1;
	item.pszText = policyUri;
	SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_SETITEM, 0, (LPARAM)&item);
	switch (userPolicy.tokenType) {
	case SoftingServerUserTokenType::ANONYMOUS:
		StringCchCopy(policyType, 15, TEXT("ANONYMOUS"));
		break;
	case SoftingServerUserTokenType::USER_NAME:
		StringCchCopy(policyType, 15, TEXT("USER NAME"));
		break;
	case SoftingServerUserTokenType::CERTIFICATE:
		StringCchCopy(policyType, 15, TEXT("CERTIFICATE"));
		break;
	case SoftingServerUserTokenType::ISSUED_TOKEN:
		StringCchCopy(policyType, 15, TEXT("ISSUED TOKEN"));
		break;
	default:
		break;
	}
	item.iSubItem = 2;
	item.pszText = policyType;
	SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_SETITEM, 0, (LPARAM)&item);
	UnselectUserPolicy();
}

void SoftingEndPointSettingsController::SelectedUserPolicy(const SoftingServerUserPolicySettings& userPolicy)
{
	int index = -1;
	switch (userPolicy.tokenType) {
	case SoftingServerUserTokenType::ANONYMOUS:
		index = 0;
		break;
	case SoftingServerUserTokenType::USER_NAME:
		index = 1;
		break;
	case SoftingServerUserTokenType::CERTIFICATE:
		index = 2;
		break;
	case SoftingServerUserTokenType::ISSUED_TOKEN:
		index = 3;
		break;
	default:
		break;
	}
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_SETCURSEL, (WPARAM)index, 0);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_EDIT, WM_SETTEXT, 0, (LPARAM)userPolicy.policyId.c_str());
	SendDlgItemMessage(m_hWindow, IDC_POLICY_URI_EDIT, WM_SETTEXT, 0, (LPARAM)userPolicy.policyUri.c_str());
	if (userPolicy.tokenType == SoftingServerUserTokenType::USER_NAME) {
		SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_SETTEXT, 0, (LPARAM)userPolicy.userName.c_str());
		SendDlgItemMessage(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT, WM_SETTEXT, 0, (LPARAM)userPolicy.password.c_str());
	}
	else {
		SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, EM_SETSEL, 0, -1);
		SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_CLEAR, 0, 0);
		SendDlgItemMessage(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT, EM_SETSEL, 0, -1);
		SendDlgItemMessage(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT, WM_CLEAR, 0, 0);
	}
	enableUserPolicyView(FALSE);
	EnableWindow(GetDlgItem(m_hWindow, IDC_REMOVE_USER_POLICY_BUTTON), TRUE);
	EnableWindow(GetDlgItem(m_hWindow, IDC_USER_POLICY_LIST), TRUE);

}

void SoftingEndPointSettingsController::SelectedEndPointConfigurations(const std::set<int>& configs)
{
	SendDlgItemMessage(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST, LB_SETSEL, (WPARAM)FALSE, (LPARAM)-1);
	for (std::set<int>::const_iterator itr = configs.cbegin(); itr != configs.cend(); ++itr) {
		SendDlgItemMessage(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST, LB_SETSEL, (WPARAM)TRUE, (LPARAM)(*itr));
	}
}

void SoftingEndPointSettingsController::ClearEndPointView()
{
	EnableWindow(GetDlgItem(m_hWindow, IDC_END_POINT_URL_EDIT), TRUE);
	EnableWindow(GetDlgItem(m_hWindow, IDC_ADD_ENDPOINT_BUTTON), TRUE);
	SendDlgItemMessage(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST, LB_SETSEL, (WPARAM)FALSE, (LPARAM)-1);
	EnableWindow(GetDlgItem(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST), TRUE);
	SendDlgItemMessage(m_hWindow, IDC_SECURITY_CONFIGURATION_LIST, LB_SETCURSEL, -1, 0);
	SendDlgItemMessage(m_hWindow, IDC_END_POINT_URL_EDIT, EM_SETSEL, 0, -1);
	SendDlgItemMessage(m_hWindow, IDC_END_POINT_URL_EDIT, WM_CLEAR, 0, 0);
	SendDlgItemMessage(m_hWindow, IDC_USER_POLICY_LIST, LVM_DELETEALLITEMS, 0, 0);
	ClearUserPolicyView();
	enableUserPolicyView(FALSE);
}

void SoftingEndPointSettingsController::ClearUserPolicyView()
{
	SendDlgItemMessage(m_hWindow, IDC_TOKEN_TYPE_COMBO, CB_SETCURSEL, (WPARAM)-1, 0);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_EDIT, EM_SETSEL, 0, -1);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_ID_EDIT, WM_CLEAR, 0, 0);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_URI_EDIT, EM_SETSEL, 0, -1);
	SendDlgItemMessage(m_hWindow, IDC_POLICY_URI_EDIT, WM_CLEAR, 0, 0);
	SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, EM_SETSEL, 0, -1);
	SendDlgItemMessage(m_hWindow, IDC_USER_NAME_EDIT, WM_CLEAR, 0, 0);
	SendDlgItemMessage(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT, EM_SETSEL, 0, -1);
	SendDlgItemMessage(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT, WM_CLEAR, 0, 0);
	
}

void SoftingEndPointSettingsController::StartLoading()
{
	HCURSOR hCurs = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCurs);
}

void SoftingEndPointSettingsController::StopLoading()
{
	HCURSOR hCurs = LoadCursor(NULL, IDC_ARROW);
	SetCursor(hCurs);
}

void SoftingEndPointSettingsController::OnBtnOkTouched()
{
	m_ptrPresenter->SaveEndPoints();
	m_bIsOk = true;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingEndPointSettingsController::OnBtnCancelTouched()
{
	m_bIsOk = false;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingEndPointSettingsController::createEndPointList()
{
	LVCOLUMN col;
	TCHAR wcColumnText[15] = TEXT("EndPoint Url");
	HWND hUrlListControl = GetDlgItem(m_hWindow, IDC_END_POINT_LIST);
	RECT listRect;
	GetWindowRect(hUrlListControl, &listRect);

	memset(&col, 0, sizeof(col));
	col.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	col.pszText = wcColumnText;
	col.cx = listRect.right - listRect.left;
	SendMessage(hUrlListControl, LVM_INSERTCOLUMN, 0, (LPARAM)(&col));
}

void SoftingEndPointSettingsController::createUserPolicyList()
{
	LVCOLUMN col;
	TCHAR wcColumnText[3][12] = { TEXT("Policy Id"),TEXT("Policy Uri"),TEXT("Policy Mode") };
	HWND hUserPoliciesListControl = GetDlgItem(m_hWindow, IDC_USER_POLICY_LIST);
	ListView_SetExtendedListViewStyle(hUserPoliciesListControl, LVS_EX_FULLROWSELECT);
	RECT listRect;
	GetWindowRect(hUserPoliciesListControl, &listRect);
	for (int i = 0; i < 3; i++)
	{
		memset(&col, 0, sizeof(col));
		col.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH;
		col.fmt = LVCFMT_LEFT;
		col.pszText = wcColumnText[i];
		if (i == 0) {
			col.cx = (listRect.right - listRect.left) / 10;
		}
		col.cx = 9 * (listRect.right - listRect.left) / 20;
		int ind = SendMessage(hUserPoliciesListControl, LVM_INSERTCOLUMN, i, (LPARAM)(&col));
	}
}

void SoftingEndPointSettingsController::enableUserPolicyView(BOOL bEnable)
{
	EnableWindow(GetDlgItem(m_hWindow, IDC_REMOVE_ENDPOINT_BUTTON), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_USER_POLICY_LIST), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_ADD_USER_POLICY_BUTTON), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_REMOVE_USER_POLICY_BUTTON), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_REMOVE_ALL_USER_POLICY_BUTTON), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_TOKEN_TYPE_COMBO), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_POLICY_ID_EDIT), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_POLICY_URI_EDIT), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_USER_NAME_EDIT), bEnable);
	EnableWindow(GetDlgItem(m_hWindow, IDC_USER_NAME_PASSWORD_EDIT), bEnable);
}


INT_PTR WINAPI SoftingEndPointSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPNMLISTVIEW itemView;
	memset(&itemView, 0, sizeof(itemView));
	LVITEM itemList;
	memset(&itemList, 0, sizeof(itemList));
	int iItem = 0;
	UINT_PTR uNotifyParam = 0;
	UINT uNotifyCode = 0;
	static std::shared_ptr<SoftingEndPointSettingsController> controller;
	switch (uMsg) {
	case WM_INITDIALOG:
		controller = std::make_shared<SoftingEndPointSettingsController>(hwnd, std::shared_ptr<ISoftingEndPointSettingsViewOutput>(reinterpret_cast<ISoftingEndPointSettingsViewOutput*>(lParam)));
		controller->setupInitialState();
		break;
	case WM_CLOSE:
		controller.reset();
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_TOKEN_TYPE_COMBO:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				//controller->ChooseConditionPropertyType();
				break;
			}
			break;
		case IDOK:
			controller->OnBtnOkTouched();
			break;
		case IDCANCEL:
			controller->OnBtnCancelTouched();
			break;
		case IDC_ADD_ENDPOINT_BUTTON:
			controller->AddEndPoint();
			break;
		case IDC_REMOVE_ENDPOINT_BUTTON:
			controller->RemoveEndPoint();
			break;
		case IDC_ADD_USER_POLICY_BUTTON:
			controller->AddUserPolicy();
			break;
		case IDC_REMOVE_USER_POLICY_BUTTON:
			controller->RemoveUserPolicy();
			break;
		case IDC_REMOVE_ALL_USER_POLICY_BUTTON:
			controller->RemoveAllUserPolicies();
			break;
		}
		break;
	case WM_NOTIFY:
		uNotifyParam = ((LPNMHDR)lParam)->idFrom;
		uNotifyCode = ((LPNMHDR)lParam)->code;
		switch (uNotifyParam)
		{
		case IDC_END_POINT_LIST:
			switch (uNotifyCode)
			{
			case LVN_INSERTITEM:
				itemView = (LPNMLISTVIEW)lParam;
				controller->ClearEndPointView();
				break;
			case  LVN_ITEMCHANGED:
				itemView = (LPNMLISTVIEW)lParam;
				iItem = itemView->iItem;
				if ((itemView->uNewState & LVIS_FOCUSED) && (itemView->uNewState & LVIS_SELECTED)) {
					TCHAR wchEndPointName[_MAX_PATH];
					itemList.pszText = wchEndPointName;
					itemList.cchTextMax = _MAX_PATH;
					size_t nameLength = SendMessage(GetDlgItem(hwnd, IDC_END_POINT_LIST), LVM_GETITEMTEXT, iItem, LPARAM(&itemList));
					wchEndPointName[nameLength + 1] = '\0';
					controller->SelectEndPoint(std::string(wchEndPointName));
				}
				break;
			case LVN_ITEMCHANGING:
				itemView = (LPNMLISTVIEW)lParam;
				iItem = itemView->iItem;
				if ((itemView->uOldState & LVIS_SELECTED) && (itemView->uNewState == 0)) {
					controller->ClearEndPointView();
				}
				break;
			}
			break;
		case IDC_USER_POLICY_LIST:
			switch (uNotifyCode)
			{
			case LVN_INSERTITEM:
				controller->ClearUserPolicyView();
				break;
			case  LVN_ITEMCHANGED:
				itemView = (LPNMLISTVIEW)lParam;
				iItem = itemView->iItem;
				if ((itemView->uNewState & LVIS_FOCUSED) && (itemView->uNewState & LVIS_SELECTED)) {
					controller->SelectUserPolicy(iItem);
				}
				break;
			case LVN_ITEMCHANGING:
				itemView = (LPNMLISTVIEW)lParam;
				iItem = itemView->iItem;
				if ((itemView->uOldState & LVIS_SELECTED) && (itemView->uNewState == 0)) {
					controller->UnselectUserPolicy();
				}
				break;
			}
			break;
		}
		break;
	
	}
	return(FALSE);
}