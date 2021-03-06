#pragma once
#include"SoftingApplication.h"
#include"SoftingServerInteractorOutput.h"

class SoftingServerInteractor: public SoftingApplicationOutput, public std::enable_shared_from_this<SoftingServerInteractor> {
public:
	SoftingServerInteractor(std::shared_ptr<ConnectionAttributes> connectionAttributes, std::shared_ptr<DataTypeAttributes> dataAttributes);
	SoftingServerInteractor() = delete;
	SoftingServerInteractor(const SoftingServerInteractor& src) = delete;
	SoftingServerInteractor& operator=(const SoftingServerInteractor& src) = delete;
	SoftingServerInteractor(SoftingServerInteractor&& src) = delete;
	SoftingServerInteractor& operator=(SoftingServerInteractor&& src) = delete;
	~SoftingServerInteractor();
	void SetOutput(std::shared_ptr<SoftingServerInteractorOutput> output);
	void GetServers();
	void GetAggregates();
	void ChooseCurrentServer();
	void ChooseCurrentEndPoint();
	void ChooseCurrentTokenPolicy();
	void OpenConnectionWithUUID(const std::string& connectionID);
	void CloseConnectionWithUUID(const std::string& connectionID);
	void OpenConnection();
	void TestConnection();
	void GetTags(const std::vector<std::string>& tagsPath, const std::string& connectionID);
	void GetRecords(const SYSTEMTIME& startTime, const SYSTEMTIME& endTime,
		const std::map<std::string, std::vector<std::string> >& fullPaths, const std::string& connectionID);
	void SendMessageError(std::string&& message) override;
	void SendWarning(std::string&& message) override;
	void SendMessageInfo(std::string&& message) override;
	void GetServerPropertyByEndPoint(const std::string& endPointName, bool isDialog);
	void GetServerPropertyByUrn(const std::string& urn);
private:
	std::shared_ptr<SoftingServerCertificateOwnSettings> m_pCertificateSettings;
	std::shared_ptr<ConnectionAttributes> m_pServerAttributes;
	std::shared_ptr<DataTypeAttributes> m_pDataAttributes;
	std::weak_ptr<SoftingServerInteractorOutput> m_pOutput;
	EnumStatusCode m_enumResult;
	std::unique_ptr<SoftingOPCToolbox5::EndpointDescription> m_selectedEndPointDescription;
	std::unique_ptr<SoftingOPCToolbox5::UserTokenPolicy> m_userToken;
	std::map<std::string, SoftingOPCToolbox5::Client::SessionPtr> m_sessionsList;
	bool startApplication();
	EnumStatusCode getServersByEndPoint(const std::string& endPointName);
	EnumStatusCode chooseCurrentServer(const std::string& endPointName, const std::vector<std::string>& serverURIs);
	void chooseEndPointAndPolicyId();
	bool findNode(const SoftingOPCToolbox5::NodeId& originNodeId, SoftingOPCToolbox5::NodeId& finalNodeId, const std::string& path, SoftingOPCToolbox5::Client::SessionPtr session);
	bool findNode(SoftingOPCToolbox5::NodeId& nodeId, const std::vector<std::string>& fullPath, SoftingOPCToolbox5::Client::SessionPtr session);
	void getTags(SoftingOPCToolbox5::NodeId& nodeId, std::set<TagInfo>& tags, std::vector<std::string>& receivedTags, SoftingOPCToolbox5::Client::SessionPtr session);
	void getHistoricalValues(const std::vector<SoftingOPCToolbox5::NodeId>& nodesToRead, const SoftingOPCToolbox5::DateTime& startTime, const SoftingOPCToolbox5::DateTime& endTime,
		std::map<std::string, std::vector<SoftingOPCToolbox5::DataValue> >& historicalValuesOfNodes, SoftingOPCToolbox5::Client::SessionPtr session);
	void getProcessedHistoricalValues(const std::vector<SoftingOPCToolbox5::NodeId>& nodesToRead, const SoftingOPCToolbox5::DateTime& startTime, const SoftingOPCToolbox5::DateTime& endTime,
		std::map<std::string, std::vector<SoftingOPCToolbox5::DataValue> >& historicalValuesOfNodes, SoftingOPCToolbox5::Client::SessionPtr session);
	TagInfo readNodeInfo(const SoftingOPCToolbox5::ReferenceDescription& refDesc, SoftingOPCToolbox5::Client::SessionPtr session);
	void getAggregateFunctions(std::vector<HierarchicalTagInfo>& tags, std::vector<SoftingOPCToolbox5::NodeId>& aggregateNodes, SoftingOPCToolbox5::Client::SessionPtr session);
	TagInfo readAggregateInfo(const SoftingOPCToolbox5::ReferenceDescription& refDesc, SoftingOPCToolbox5::Client::SessionPtr session);
	void getAggregateNodes(SoftingOPCToolbox5::INodeId* nodeId, std::vector<HierarchicalTagInfo>& tags, const std::vector<std::string>& parentTags, std::vector<SoftingOPCToolbox5::NodeId>& aggregateNodes, SoftingOPCToolbox5::Client::SessionPtr session);
	SoftingOPCToolbox5::NodeId getAggregateNode(const std::pair<std::string, int>& aggregateType, SoftingOPCToolbox5::Client::SessionPtr session);
};

bool admitToAttributes(const SoftingOPCToolbox5::EndpointDescription& desc, const ConnectionAttributes& attributes);
bool admitToSecurityPolicy(const SoftingOPCToolbox5::UserTokenPolicy& policy, const SecurityUserTokenPolicy& attributesPolicy);
ServerSecurityModeConfiguration mapConfigFromEndPointDesc(const SoftingOPCToolbox5::EndpointDescription& desc);
SecurityUserTokenPolicy mapEndPointTokenFromPolicy(const SoftingOPCToolbox5::UserTokenPolicy& policy);
Record mapRecordFromDataValue(const SoftingOPCToolbox5::DataValue& dataValue);