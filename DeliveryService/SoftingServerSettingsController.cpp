#include"SoftingServerSettingsController.h"
#include"SoftingServerSettingsPresenter.h"
#include"Utils.h"
#include<Shlobj.h>
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

void SoftingServerSettingsController::OnBtnOkTouched() {
	std::string serverName;
	if (!ReadText(IDC_SERVER_NAME_EDIT, serverName)) {
		return;
	}
	std::string serverPort;
	if (!ReadText(IDC_PORT_EDIT, serverPort)) {
		return;
	}
	unsigned int port = std::stoul(serverPort);
	if (port < 1000) {
		std::string message = "Port number is not correct!";
		MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
		return;
	}

	std::string certificate;
	if (!ReadText(IDC_CERTIFICATE_PATH_EDIT,certificate)) {
		return;
	}
	std::string privateKey;
	if (!ReadText(IDC_PRIVATE_KEY_PATH_EDIT, privateKey)) {
		return;
	}
	std::string trusted;
	if (!ReadText(IDC_TRUSTED_PATH_EDIT, trusted)) {
		return;
	}
	std::string rejected;
	if (!ReadText(IDC_REJECTED_PATH_EDIT, rejected)) {
		return;
	}
	std::string revocation;
	if (!ReadText(IDC_REVOCATION_PATH_EDIT, revocation)) {
		return;
	}
	std::string password;
	if (!ReadText(IDC_PASSWORD_EDIT, password)) {
		return;
	}
	m_ptrPresenter->GetViewOutput(std::move(serverName), port, std::move(certificate), std::move(privateKey), std::move(password),std::move(trusted), std::move(rejected),std::move(revocation));
	m_bIsOk = true;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingServerSettingsController::OnBtnCancelTouched()
{
	m_bIsOk = false;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingServerSettingsController::OnBtnChooseCertificatePathTouched()
{
	BOOL bOk = FALSE;
	TCHAR szPathname[_MAX_PATH];
	OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };
	ofn.hwndOwner = m_hWindow;
	ofn.lpstrFilter = TEXT("*.*\0");
	lstrcpy(szPathname, TEXT("*.*"));
	ofn.lpstrFile = szPathname;
	ofn.nMaxFile = _countof(szPathname);
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	ofn.lpstrTitle = TEXT("Select certificate file ");
	bOk = GetOpenFileName(&ofn);
	if (bOk) {
		bOk = SetDlgItemText(m_hWindow, IDC_CERTIFICATE_PATH_EDIT, szPathname);
		if (!bOk) {
			DWORD err = GetLastError();
			std::string message = GetErrorText(err);
			MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
		}
	}
}


void SoftingServerSettingsController::OnBtnChoosePrivateKeyPathTouched()
{
	BOOL bOk = FALSE;
	TCHAR szPathname[_MAX_PATH];
	OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };
	ofn.hwndOwner = m_hWindow;
	ofn.lpstrFilter = TEXT("*.*\0");
	lstrcpy(szPathname, TEXT("*.*"));
	ofn.lpstrFile = szPathname;
	ofn.nMaxFile = _countof(szPathname);
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
	ofn.lpstrTitle = TEXT("Select private key file ");
	bOk = GetOpenFileName(&ofn);
	if (bOk) {
		bOk = SetDlgItemText(m_hWindow, IDC_PRIVATE_KEY_PATH_EDIT, szPathname);
		if (!bOk) {
			DWORD err = GetLastError();
			std::string message = GetErrorText(err);
			MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
		}
	}
}

void SoftingServerSettingsController::OnBtnChoosePkiTrustedFolderPathTouched()
{
	WriteTextFromPathDlg(IDC_TRUSTED_PATH_BUTTON);
}

void SoftingServerSettingsController::OnBtnChoosePkiRejectedFolderPathTouched()
{
	WriteTextFromPathDlg(IDC_REJECTED_PATH_BUTTON);
}

void SoftingServerSettingsController::OnBtnChoosePkiRevocationFolderPathTouched()
{
	WriteTextFromPathDlg(IDC_REVOCATION_PATH_BUTTON);
}

bool SoftingServerSettingsController::ReadText(int itemId, std::string& text)
{
	TCHAR szPathname[_MAX_PATH];
	memset(szPathname, '\0', _MAX_PATH);
	size_t len = GetDlgItemText(m_hWindow, itemId, szPathname, _MAX_PATH);
	if (len <= 0) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
		MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
		return false;
	}
	text = std::string(szPathname);
	return true;
}

void SoftingServerSettingsController::WriteTextFromPathDlg(int itemId)
{
	BOOL bOk = FALSE;
	LPITEMIDLIST list = NULL;
	TCHAR szPathname[_MAX_PATH];
	BROWSEINFOA brs;
	brs.hwndOwner = m_hWindow;
	brs.pidlRoot = NULL;
	brs.pszDisplayName = szPathname;
	brs.ulFlags = BIF_NONEWFOLDERBUTTON | BIF_RETURNONLYFSDIRS;
	brs.lpfn = NULL;
	switch (itemId) {
	case IDC_TRUSTED_PATH_BUTTON:
		brs.lpszTitle = TEXT("Select Pki folder for trusted certificates ");
		list = SHBrowseForFolderA(&brs);
		if (list == NULL) {
			return;
		}
		if (SHGetPathFromIDListA(list, szPathname)) {
			bOk = SetDlgItemText(m_hWindow, IDC_TRUSTED_PATH_EDIT, szPathname);
		}
		break;
	case IDC_REJECTED_PATH_BUTTON:
		brs.lpszTitle = TEXT("Select Pki folder for rejected certificates ");
		list = SHBrowseForFolderA(&brs);
		if (list == NULL) {
			return;
		}
		if (SHGetPathFromIDListA(list, szPathname)) {
			bOk = SetDlgItemText(m_hWindow, IDC_REJECTED_PATH_EDIT, szPathname);
		}
		break;
	case IDC_REVOCATION_PATH_BUTTON:
		brs.lpszTitle = TEXT("Select Pki folder for revocation");
		list = SHBrowseForFolderA(&brs);
		if (list == NULL) {
			return;
		}
		if (SHGetPathFromIDListA(list, szPathname)) {
			bOk = SetDlgItemText(m_hWindow, IDC_REVOCATION_PATH_EDIT, szPathname);
		}
		break;
	default:
		return;
		break;
	}
	
	if (!bOk) {
		DWORD err = GetLastError();
		std::string message = GetErrorText(err);
		MessageBox(m_hWindow, TEXT(message.c_str()), "Warning", MB_ICONSTOP);
	}
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
		case IDC_CERTIFICATE_PATH_BUTTON:
			controller->OnBtnChooseCertificatePathTouched();
			break;
		case IDC_PRIVATE_KEY_PATH_BUTTON:
			controller->OnBtnChoosePrivateKeyPathTouched();
			break;
		case IDC_TRUSTED_PATH_BUTTON:
			controller->OnBtnChoosePkiTrustedFolderPathTouched();
			break;
		case IDC_REJECTED_PATH_BUTTON:
			controller->OnBtnChoosePkiRejectedFolderPathTouched();
			break;
		case IDC_REVOCATION_PATH_BUTTON:
			controller->OnBtnChoosePkiRevocationFolderPathTouched();
			break;
		}
		break;
	}
	return(FALSE);
}