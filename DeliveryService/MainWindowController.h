#pragma once
#include"MainWindowViewOutput.h"
#include<Windows.h>
#include<memory>
class MainWindowController final: public std::enable_shared_from_this<MainWindowController>, public IMainWindowViewInput {
public:
	MainWindowController(HINSTANCE hInstance, HWND hwnd);
	MainWindowController(const MainWindowController& src) = delete;
	MainWindowController(MainWindowController&& src) = delete;
	MainWindowController& operator=(const MainWindowController& src) = delete;
	MainWindowController& operator=(MainWindowController&& src) = delete;
	~MainWindowController();
	void setupInitialState();
	void WarningMessage(std::string message) override;
	void ErrorMessage(std::string message) override;
	void StartLoading() override;
	void StopLoading() override;
	HWND GetWindowHandle() override;
	HINSTANCE GetAppInstance() override;
	HWND GetStatusBarHandler() const;
	void ResizeStatusBar(long height, long width);
	void CreateConnectionMenu(POINT pt);
	void CreateServiceMenu(POINT pt);
	void CreateSoftingServerCertificateLocationsDialog();
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HWND m_hStatusBar;
	int m_isBind;
	int m_isService;
	std::shared_ptr<IMainWindowViewOutput> m_ptrPresenter;
	void CreateStatusBar();
};