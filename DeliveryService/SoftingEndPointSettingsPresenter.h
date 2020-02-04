#pragma once
#include"ISoftingEndPointSettingsViewOutput.h"
#include"ISoftingEndPointSettingsModuleOutput.h"

class SoftingEndPointSettingsPresenter final : public std::enable_shared_from_this<SoftingEndPointSettingsPresenter>, public ISoftingEndPointSettingsViewOutput
{
public:
	SoftingEndPointSettingsPresenter(std::shared_ptr< ISoftingEndPointSettingsModuleOutput> output);
	SoftingEndPointSettingsPresenter(const SoftingEndPointSettingsPresenter& src) = delete;
	SoftingEndPointSettingsPresenter& operator=(const SoftingEndPointSettingsPresenter& src) = delete;
	SoftingEndPointSettingsPresenter(SoftingEndPointSettingsPresenter&& src) = delete;
	SoftingEndPointSettingsPresenter& operator=(SoftingEndPointSettingsPresenter&& src) = delete;
	~SoftingEndPointSettingsPresenter();
	void viewIsReady() override;
	void SetViewInput(std::shared_ptr<ISoftingEndPointSettingsViewInput> input) override;
	void SelectEndPoint(std::string endPointUrl) override;
	void AddEndPoint(std::string endPointUrl, const std::set<int>& configs) override;
	void RemoveEndPoint(std::string endPointUrl) override;
	void AddUserPolicy(SoftingServerUserPolicySettings&& condition, std::string endPointUrl) override;
	void RemoveUserPolicy(const std::string& policyId, std::string endPointUrl) override;
	void RemoveAllUserPolicies(std::string endPointUrl) override;
	void SelectUserPolicy(const std::string& policyId, std::string endPointName) override;
	void SaveEndPoints() override;
private:
	std::weak_ptr<ISoftingEndPointSettingsViewInput> m_ptrView;
	std::weak_ptr<ISoftingEndPointSettingsModuleOutput> m_ptrOutput;
	std::map<std::string, SoftingServerEndPointSettings> m_endPoints;
};