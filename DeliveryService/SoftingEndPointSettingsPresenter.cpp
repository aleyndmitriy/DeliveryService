#include"SoftingEndPointSettingsPresenter.h"

SoftingEndPointSettingsPresenter::SoftingEndPointSettingsPresenter(std::shared_ptr< ISoftingEndPointSettingsModuleOutput> output): m_ptrView(), m_ptrOutput(output), m_endPoints()
{

}

SoftingEndPointSettingsPresenter::~SoftingEndPointSettingsPresenter()
{

}

void SoftingEndPointSettingsPresenter::viewIsReady()
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		for (std::map<std::string, SoftingServerEndPointSettings>::const_iterator itr = m_endPoints.cbegin(); itr != m_endPoints.cend(); ++itr) {
			viewOutput->AddEndPoint(itr->first);
		}
	}
}

void SoftingEndPointSettingsPresenter::SetViewInput(std::shared_ptr<ISoftingEndPointSettingsViewInput> input)
{
	m_ptrView = input;
}

void SoftingEndPointSettingsPresenter::SelectEndPoint(std::string endPointUrl)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		std::map<std::string, SoftingServerEndPointSettings>::const_iterator itrFind = m_endPoints.find(endPointUrl);
		if (itrFind != m_endPoints.cend()) {
			std::set<int> configs;
			for (std::set<SoftingServerEndPointSecurityConfiguration>::const_iterator itr = itrFind->second.securityConfiguration.cbegin();
				itr != itrFind->second.securityConfiguration.cend(); ++itr) {
				configs.insert(getIntFromConfiguration(*itr));
			}
			viewOutput->SelectedEndPointConfigurations(configs);
			int index = 0;
			for (std::map<std::string, SoftingServerUserPolicySettings>::const_iterator itr = itrFind->second.userTokenPolicyList.cbegin();
				itr != itrFind->second.userTokenPolicyList.cend(); ++itr) {
				viewOutput->AddUserPolicy(itr->second, index++);
			}
		}
		else {
			viewOutput->WarningMessage(std::string("There is not such end point in the list!"));
		}
	}
}

void SoftingEndPointSettingsPresenter::AddEndPoint(std::string endPointUrl, const std::set<int>& configs)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		if (endPointUrl.empty()) {
			viewOutput->WarningMessage(std::string("Please, enter end point url name!"));
			return;
		}
		if (configs.empty()) {
			viewOutput->WarningMessage(std::string("Please, end point configurations!"));
			return;
		}
		std::map<std::string, SoftingServerEndPointSettings>::iterator itrFind = m_endPoints.find(endPointUrl);
		if (itrFind != m_endPoints.end()) {
			viewOutput->WarningMessage(std::string("End point with such url already exist!"));
			return;
		}
		std::pair<std::map<std::string, SoftingServerEndPointSettings>::iterator, bool> itr = 
			m_endPoints.insert(std::make_pair<std::string, SoftingServerEndPointSettings>(std::string(endPointUrl),SoftingServerEndPointSettings(endPointUrl)));
		if (itr.second) {
			for (std::set<int>::const_iterator itrConf = configs.cbegin(); itrConf != configs.cend(); ++itrConf) {
				itr.first->second.securityConfiguration.insert(getConfigurationFromInt(*itrConf));
			}
			viewOutput->AddEndPoint(endPointUrl);
		}
		else {
			viewOutput->WarningMessage(std::string("Error of End point inserting inserting!"));
		}
	}
}

void SoftingEndPointSettingsPresenter::RemoveEndPoint(std::string endPointUrl)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		std::map<std::string, SoftingServerEndPointSettings>::iterator itrFind = m_endPoints.find(endPointUrl);
		if (itrFind != m_endPoints.end()) {
			m_endPoints.erase(itrFind);
		}
		else {
			viewOutput->WarningMessage(std::string("There is not such end point in list!"));
		}
	}
}

void SoftingEndPointSettingsPresenter::AddUserPolicy(SoftingServerUserPolicySettings&& policy, std::string endPointUrl)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		std::map<std::string, SoftingServerEndPointSettings>::iterator itrFind = m_endPoints.find(endPointUrl);
		if (itrFind != m_endPoints.end()) {
			std::string policyId = std::string(policy.policyId);
			std::pair<std::map<std::string, SoftingServerUserPolicySettings>::iterator, bool> itr =
			itrFind->second.userTokenPolicyList.insert(std::make_pair<std::string, SoftingServerUserPolicySettings>(std::string(policyId),std::move(policy)));
			if (itr.second) {
				viewOutput->AddUserPolicy(itr.first->second, itrFind->second.userTokenPolicyList.size() - 1);
			}
			else {
				std::string message = std::string("There is already exists such user policy with Id ") + policyId;
				viewOutput->WarningMessage(message);
			}
		}
		else {
			viewOutput->WarningMessage(std::string("There is not such end point in list!"));
		}
	}
}

void SoftingEndPointSettingsPresenter::RemoveUserPolicy(const std::string& policyId, std::string endPointUrl)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		std::map<std::string, SoftingServerEndPointSettings>::iterator itrFind = m_endPoints.find(endPointUrl);
		if (itrFind != m_endPoints.end()) {
			std::map<std::string, SoftingServerUserPolicySettings>::iterator itr = itrFind->second.userTokenPolicyList.find(policyId);
			if (itr != itrFind->second.userTokenPolicyList.cend()) {
				itrFind->second.userTokenPolicyList.erase(itr);
			}
			else {
				viewOutput->WarningMessage(std::string("There is not such user policy in list!"));
			}
		}
		else {
			viewOutput->WarningMessage(std::string("There is not such end point in list!"));
		}
	}
}

void SoftingEndPointSettingsPresenter::RemoveAllUserPolicies(std::string endPointUrl)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		std::map<std::string, SoftingServerEndPointSettings>::iterator itrFind = m_endPoints.find(endPointUrl);
		if (itrFind != m_endPoints.end()) {
			itrFind->second.userTokenPolicyList.clear();
		}
		else {
			viewOutput->WarningMessage(std::string("There is not such end point in list!"));
		}
	}
}


void SoftingEndPointSettingsPresenter::SelectUserPolicy(const std::string& policyId, std::string endPointName)
{
	std::shared_ptr<ISoftingEndPointSettingsViewInput> viewOutput = m_ptrView.lock();
	if (viewOutput) {
		std::map<std::string, SoftingServerEndPointSettings>::const_iterator itrFind = m_endPoints.find(endPointName);
		if (itrFind != m_endPoints.cend()) {
			std::map<std::string, SoftingServerUserPolicySettings>::const_iterator itr = itrFind->second.userTokenPolicyList.find(policyId);
			if (itr != itrFind->second.userTokenPolicyList.cend()) {
				viewOutput->SelectedUserPolicy(itr->second);
			}
			else {
				viewOutput->WarningMessage(std::string("There is not such user policy in list!"));
			}
		}
		else {
			viewOutput->WarningMessage(std::string("There is not such end point in list!"));
		}
	}
}

void SoftingEndPointSettingsPresenter::SaveEndPoints()
{
	std::shared_ptr<ISoftingEndPointSettingsModuleOutput> output = m_ptrOutput.lock();
	if (output) {
		output->GetEndPoints(m_endPoints);
	}
}