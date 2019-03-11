#pragma once
#include <string>
#include "typedef.h"

using namespace std;


#define  MAXCHANNELNUM  64
#include "tinyxml/tinyxml.h"


class CXMLConfigure
{
public:
	CXMLConfigure(void);
	~CXMLConfigure(void);

public:
	int ParaseXMLInside(CONFIG_TYPE ntype,string strInfo,void* pBuf,int nChannel,int nNum=0,long nParam1 = 0,long nParam2=0);
	int PacketXMLInside(CONFIG_TYPE ntype,string& strinfo,void* pBufIn, int nChannel,int nNum=0,long nParam1 = 0,long nParam2=0);
private:
	int PacketAbility(Ability nType,string& strinfo, void* pBufIn,TiXmlElement* root,long lParam1);
	int ParaseAbility(Ability nType,void* pBuf,TiXmlElement* root,long lParam1);
public:
	static CXMLConfigure* Instance();
	static void		      UnInstance();
public:
	static CXMLConfigure* s_config;
public:
	char   m_buffer[1024*1024];
};

#define CURRENTCONFIGURE  CXMLConfigure::Instance()