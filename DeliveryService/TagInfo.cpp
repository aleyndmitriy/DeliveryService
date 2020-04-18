#include"TagInfo.h"

TagInfo::TagInfo(const std::string& name, const std::string& desc, int type) : m_strName(name), m_strDescription(desc), m_iType(type)
{

}

TagInfo::~TagInfo()
{
	m_strName.clear();
	m_strDescription.clear();
	m_iType = 0;
}



bool operator < (const TagInfo& lhs, const TagInfo& rhs)
{
	return lhs.m_strName < rhs.m_strName;
}

HierarchicalTagInfo::HierarchicalTagInfo(const std::vector<std::string>& address, const std::string& desc, int type) :
	m_strAddress(address), m_strDescription(desc), m_iType(type)
{

}

HierarchicalTagInfo::~HierarchicalTagInfo()
{
	m_strAddress.clear();
	m_strDescription.clear();
	m_iType = 0;
}