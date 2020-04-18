#pragma once
#include<string>
#include<vector>

struct TagInfo
{
	static const int TYPE_ITEM = 1;
	static const int TYPE_BRANCH = 2;
	std::string m_strName;
	std::string m_strDescription;
	int m_iType;
	TagInfo() = delete;
	TagInfo(const std::string& name, const std::string& desc, int type);
	~TagInfo();
	TagInfo(const TagInfo& src) = default;
	TagInfo& operator=(const TagInfo& src) = default;
	TagInfo(TagInfo&& src) = default;
	TagInfo& operator=(TagInfo&& src) = default;
};

bool operator < (const TagInfo& lhs, const TagInfo& rhs);

struct HierarchicalTagInfo
{
	std::vector<std::string> m_strAddress;
	std::string m_strDescription;
	int m_iType;
	HierarchicalTagInfo() = delete;
	HierarchicalTagInfo(const std::vector<std::string>& address, const std::string& desc, int type);
	~HierarchicalTagInfo();
	HierarchicalTagInfo(const HierarchicalTagInfo& src) = default;
	HierarchicalTagInfo& operator=(const HierarchicalTagInfo& src) = default;
	HierarchicalTagInfo(HierarchicalTagInfo&& src) = default;
	HierarchicalTagInfo& operator=(HierarchicalTagInfo&& src) = default;
};