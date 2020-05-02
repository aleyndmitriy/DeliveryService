#include"SoftingApplicationSettingsController.h"
#include"Utils.h"
#include<Shlobj.h>
SoftingApplicationSettingsController::SoftingApplicationSettingsController(HWND window, std::shared_ptr<ISoftingApplicationSettingsViewOutput> output) :
	m_hWindow(window), m_ptrPresenter(output), m_bIsOk(false)
{

}

SoftingApplicationSettingsController::~SoftingApplicationSettingsController()
{
	m_ptrPresenter.reset();
	EndDialog(m_hWindow, m_bIsOk);
	m_bIsOk = false;
	m_hWindow = NULL;
}

void SoftingApplicationSettingsController::setupInitialState()
{
	m_ptrPresenter->SetViewInput(shared_from_this());
}

void SoftingApplicationSettingsController::OnBtnOkTouched() {

	m_bIsOk = true;
	readAttributes();
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingApplicationSettingsController::OnBtnCancelTouched()
{
	m_bIsOk = false;
	SendMessage(m_hWindow, WM_CLOSE, 0, 0);
}

void SoftingApplicationSettingsController::OnBtnChooseCertificatePathTouched()
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


void SoftingApplicationSettingsController::OnBtnChoosePrivateKeyPathTouched()
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

void SoftingApplicationSettingsController::OnBtnChoosePkiTrustedFolderPathTouched()
{
	writeTextFromPathDlg(IDC_TRUSTED_PATH_BUTTON);
}

void SoftingApplicationSettingsController::OnBtnChoosePkiRejectedFolderPathTouched()
{
	writeTextFromPathDlg(IDC_REJECTED_PATH_BUTTON);
}

void SoftingApplicationSettingsController::OnBtnChoosePkiRevocationFolderPathTouched()
{
	writeTextFromPathDlg(IDC_REVOCATION_PATH_BUTTON);
}

bool SoftingApplicationSettingsController::readText(int itemId, std::string& text)
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

void SoftingApplicationSettingsController::writeTextFromPathDlg(int itemId)
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

void SoftingApplicationSettingsController::readAttributes()
{
	std::string certificate;
	if (!readText(IDC_CERTIFICATE_PATH_EDIT, certificate)) {
		return;
	}

	std::string privateKey;
	if (!readText(IDC_PRIVATE_KEY_PATH_EDIT, privateKey)) {
		return;
	}
	std::string trusted;
	if (!readText(IDC_TRUSTED_PATH_EDIT, trusted)) {
		return;
	}
	std::string rejected;
	if (!readText(IDC_REJECTED_PATH_EDIT, rejected)) {
		return;
	}
	std::string revocation;
	if (!readText(IDC_REVOCATION_PATH_EDIT, revocation)) {
		return;
	}
	std::string password;
	if (!readText(IDC_PASSWORD_EDIT, password)) {
		return;
	}

	m_ptrPresenter->GetCertificateViewOutput(std::move(certificate), std::move(privateKey), std::move(password), std::move(trusted), std::move(rejected), std::move(revocation));
}

INT_PTR WINAPI SoftingAppSettingDlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static std::shared_ptr<SoftingApplicationSettingsController> controller;
	switch (uMsg) {
	case WM_INITDIALOG:
		controller = std::make_shared<SoftingApplicationSettingsController>(hwnd, std::shared_ptr<ISoftingApplicationSettingsViewOutput>(reinterpret_cast<ISoftingApplicationSettingsViewOutput*>(lParam)));
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