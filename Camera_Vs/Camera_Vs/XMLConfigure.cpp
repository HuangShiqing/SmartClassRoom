#include "stdafx.h"
#include "XMLConfigure.h"
//#include "QDateTime"

#define READ_ATTRIBUTE_INT(node, attr, var)		\
	tmp = node->Attribute(attr);				\
	if ( NULL == tmp )							\
{											\
	return -1;							\
}											\
	else										\
{											\
	var = atol(tmp);						\
}

#define READ_ATTRIBUTE_INT_NO_RETURN(node, attr, var)		\
	tmp = node->Attribute(attr);				\
	if ( NULL != tmp )							\
{											\
	nRet= 0;								\
	var = atol(tmp);						\
}											\
else										\
{											\
	nRet= -1;								\
}


#define READ_ATTRIBUTE_STR_NO_RETURN(node, attr, var, maxlen) \
	tmp = node->Attribute(attr);				\
	if ( NULL != tmp )							\
{											\
	nRet = 0;								\
	strncpy(var, tmp, (maxlen) - 1);		\
}											\
else										\
{											\
	nRet =-1;								\
}

//using namespace XMLCONFIGURE;

CXMLConfigure* CXMLConfigure::s_config = NULL;
CXMLConfigure::CXMLConfigure(void)
{

}
CXMLConfigure::~CXMLConfigure(void)
{

}

CXMLConfigure* CXMLConfigure::Instance()
{
	if(!s_config)
	{
		s_config = new CXMLConfigure();
	}
	return s_config;
}
void  CXMLConfigure::UnInstance()
{
	if(s_config)
	{
		delete s_config;
		s_config = NULL;
	}
}

int CXMLConfigure::ParaseXMLInside(CONFIG_TYPE ntype,string strInfo,void* pBufout,int nChannel,int nNum,long nParam1/* = 0*/,long nParam2/*=0*/)
{
	int nRet = 0;
	const char* tmp = NULL;
	TiXmlDocument doc;

	doc.Parse(strInfo.c_str());
	if ( doc.Error() )
	{
		return -101;
	}

	switch(ntype)
	{
	case CFG_DEV_INFO:
		{
			VG_DevInfo* pDevInfo = (VG_DevInfo*)pBufout;

			TiXmlElement* root = doc.FirstChildElement(XML_TAG_DEVICEINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_TOTALCHANNEL,pDevInfo->nTotalchannel)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ALARMCHANNEL,pDevInfo->nAlarmchannel)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ALARMOUTCHANNEL,pDevInfo->nAlarmOutchannel)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_DIGICHANNEL,pDevInfo->nDigichannel)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_NEWSEARCHPIC,pDevInfo->bsearchnewpic)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SVAC,pDevInfo->bsvac)
		}
		break;
	case CFG_CHANNEL_NAME:
		{

			//modify xwy
			VG_CHANNELNAME_CFG* pcfg = (VG_CHANNELNAME_CFG*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_CHANNELNAME);
			if(!root)
			{
				nRet = -1;
				break;
			}
			int nChannel = 0;
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SIZE,nChannel);
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_CHANNEL);
			//const char* tmpStr = NULL;
			int i=0;
			while(ptmp)
			{
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pcfg->channel[i].iChannel)
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_NAME,pcfg->channel[i].strChannelName,VG_MAX_CHANNELNUM)
					ptmp=  ptmp->NextSiblingElement(XML_TAG_CHANNEL);
				i++;
			}
			//end
			//RV_CHANNELNAME_CFG* pcfg = (RV_CHANNELNAME_CFG*)pBufout;
			//TiXmlElement* root = doc.FirstChildElement(XML_TAG_CHANNELNAME);
			//if(!root)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SIZE,pcfg->dwSize);
			//TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_CHANNEL);
			//const char* tmpStr = NULL;
			//int i=0;
			//while(ptmp)
			//{
			//	READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_NAME,pcfg->stChannelName[i].strChannelName,MAX_HHCHANNELNAME_LEN)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pcfg->stChannelName[i].iChannel)
			//	ptmp=  ptmp->NextSiblingElement(XML_TAG_CHANNEL);
			//	i++;
			//}
		}
		break;
	case CFG_TALKFORMATLIST:
		{
			//RVDEV_TALKFORMAT_LIST* pcfg = (RVDEV_TALKFORMAT_LIST*)pBufout;

			//TiXmlElement* root = doc.FirstChildElement(XML_TAG_TALKFORMAT);
			//if(!root)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_NUM,pcfg->nSupportNum)
			//TiXmlElement* pEncode = root->FirstChildElement(XML_TAG_TALKENCORDINFO);
			//int i=0;
			//while(pEncode)
			//{
			//	int nType = 0;
			//	READ_ATTRIBUTE_INT_NO_RETURN(pEncode,XML_ATTR_ENCODETYPE,nType)
			//	pcfg->type[i].encodeType = (RV_TALK_CODING_TYPE)nType;
			//	READ_ATTRIBUTE_INT_NO_RETURN(pEncode,XML_ATTR_SAMPLERATE,pcfg->type[i].dwSampleRate)
			//	READ_ATTRIBUTE_INT_NO_RETURN(pEncode,XML_ATTR_SAMPLEBIT,pcfg->type[i].reserved[0])
			//	READ_ATTRIBUTE_INT_NO_RETURN(pEncode,XML_ATTR_AUDIOBIT,pcfg->type[i].nAudioBit)
			//	pEncode = pEncode->NextSiblingElement(XML_TAG_TALKENCORDINFO);
			//	i++;
			//}
		}
		break;
	case CFG_PTZPRESET_SCHEDULE:
		{
			VG_PTZ_PRESET_SCHEDULE* pcfg = (VG_PTZ_PRESET_SCHEDULE*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_PRESETSCHEDULE);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_NUM,pcfg->dwCount)
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_PRESETINFO);
			int i=0;
			while(ptmp)
			{			

				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_DWELLTIME,pcfg->struPreset[i].iDWellTime)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_SPEED,pcfg->struPreset[i].iSpeed)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_PRESETID,pcfg->struPreset[i].ucPresetID)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_PRESETNAME,(char*)&pcfg->struPreset[i].szPresetName[0],32)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pcfg->struPreset[i].ucChannel)
				ptmp = ptmp->NextSiblingElement(XML_TAG_PRESETINFO);
				i++;
			}	
		}
		break;
	case CFG_ADDPRESET_CFG:
	case CFG_DELETEPRESET_CFG:
		{
			VG_PRESET_INFO* pCfg = (VG_PRESET_INFO*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_PRESETINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pCfg->ucChannel)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_PRESETID,pCfg->ucPresetID)
			//modify xwy
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SPEED,pCfg->iSpeed)
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SPEED,pCfg->ucPresetID)
			//end
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_DWELLTIME,pCfg->iDWellTime)
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_PRESETNAME,(char*)&pCfg->szPresetName[0],32)
		}
		break;
	case CFG_ADDTOURPRESET_CFG:
	case CFG_DEV_DELTOURPRESET_CFG:
		{
			VG_PTZ_TOUR_PRESET* pCfg = (VG_PTZ_TOUR_PRESET*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_TOURPRESET);
			if(!root)
			{
				nRet = -1;
				break;
			}
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_PTZCHANNEL);
			if(ptmp)
			{
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pCfg->struChannel.iChannel)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_PRESETID,pCfg->struChannel.iIndex)
			}
			TiXmlElement* pTmp2 = root->FirstChildElement(XML_TAG_PRESETINFO);
			if(pTmp2)
			{
				READ_ATTRIBUTE_INT_NO_RETURN(pTmp2,XML_ATTR_CHANNNELNO,pCfg->struPreset.ucChannel)
				READ_ATTRIBUTE_INT_NO_RETURN(pTmp2,XML_ATTR_PRESETID,pCfg->struPreset.ucPresetID)
				READ_ATTRIBUTE_INT_NO_RETURN(pTmp2,XML_ATTR_SPEED,pCfg->struPreset.iSpeed)
				READ_ATTRIBUTE_INT_NO_RETURN(pTmp2,XML_ATTR_DWELLTIME,pCfg->struPreset.iDWellTime)
				READ_ATTRIBUTE_STR_NO_RETURN(pTmp2,XML_ATTR_PRESETNAME,(char*)&pCfg->struPreset.szPresetName[0],32)
			}			
		}
		break;	
	case CFG_DEV_CLEARTOUR_CFG:
		{
			VG_PTZ_CHANNEL* pCfg = (VG_PTZ_CHANNEL*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_TOURPRESET);
			if(!root)
			{
				return -1;
			}

			TiXmlElement* ptmp =root->FirstChildElement(XML_TAG_PTZCHANNEL);
			if(ptmp)
			{
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pCfg->iChannel)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_PRESETID,pCfg->iIndex)
			}
		}
		break;
	case CFG_TOUR_SCHEDULE:
		{
			VG_PTZ_TOUR_SCHEDULE* pcfg = (VG_PTZ_TOUR_SCHEDULE*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_TOURSCHEDULE);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_NUM,pcfg->dwCount)

			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_TOURINFO);
			TiXmlElement *ptmp2 = NULL;
			int i = 0, j = 0;
			while(ptmp)
			{
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pcfg->struTour[i].ucChannel)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_TOURINDEX,pcfg->struTour[i].ucTourIndex)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_PRESETCOUNT,pcfg->struTour[i].ucPresetCnt)

				// 预置点信息
				j = 0;
				ptmp2 = ptmp->FirstChildElement(XML_TAG_PRESETINFO);
				while(ptmp2 && j < 64)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_DWELLTIME, pcfg->struTour[i].preset[j].iDWellTime)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_SPEED, pcfg->struTour[i].preset[j].iSpeed)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_PRESETID, pcfg->struTour[i].preset[j].ucPresetID)
					ptmp2 = ptmp2->NextSiblingElement(XML_TAG_PRESETINFO);
					++j;
				}	
				
				ptmp= ptmp->NextSiblingElement(XML_TAG_TOURINFO);
				i++;
			}
		}
		break;
	case CFG_DIGICHAN_TOUR:
		{			
			VG_DIGI_CH_TOUR_CFG* pcfg = (VG_DIGI_CH_TOUR_CFG*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_DIGICHTOUR);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SIZE,pcfg->dwSize)
			TiXmlElement* ptmp =root->FirstChildElement(XML_TAG_LOCALCFG);
			int i=0;
			while(ptmp)
			{
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_REMOTECHCNT,pcfg->stLocalChan[i].dwRemoteChanCount);
				TiXmlElement* ptmpDigiLocal = ptmp->FirstChildElement(XML_TAG_DIGILOCALCH);
				if(ptmpDigiLocal)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_BENABLE,pcfg->stLocalChan[i].stLocalChCfg.BEnable)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_CHANNELTYPE,pcfg->stLocalChan[i].stLocalChCfg.iDeviceChannelType)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_MODE,pcfg->stLocalChan[i].stLocalChCfg.iMode)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_TOURTIME,pcfg->stLocalChan[i].stLocalChCfg.uiTourTime)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_NOTTOURINDEX,pcfg->stLocalChan[i].stLocalChCfg.uiNotTourCfgIndex)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_DECODEPOLICY,pcfg->stLocalChan[i].stLocalChCfg.iDecodePolicy)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiLocal,XML_ATTR_AVENABLE,pcfg->stLocalChan[i].stLocalChCfg.iAVEnable)
				}
				TiXmlElement* ptmpDigiremote = ptmp->FirstChildElement(XML_TAG_DIGIREMOTECH);
				int j=0;
				while(ptmpDigiremote&&j<pcfg->stLocalChan[i].dwRemoteChanCount)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_BENABLE,pcfg->stLocalChan[i].stRemoteChanCfg[j].BEnable)
					READ_ATTRIBUTE_STR_NO_RETURN(ptmpDigiremote,XML_ATTR_DEVIP,pcfg->stLocalChan[i].stRemoteChanCfg[j].cDeviceIP,64)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_DEVPORT,pcfg->stLocalChan[i].stRemoteChanCfg[j].iDevicePort)
					READ_ATTRIBUTE_STR_NO_RETURN(ptmpDigiremote,XML_ATTR_USERNAME,pcfg->stLocalChan[i].stRemoteChanCfg[j].cDeviceUserName,32)
					READ_ATTRIBUTE_STR_NO_RETURN(ptmpDigiremote,XML_ATTR_PASSWORD,pcfg->stLocalChan[i].stRemoteChanCfg[j].cDevicePassword,32)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_DEVCTYPE,pcfg->stLocalChan[i].stRemoteChanCfg[j].iDevType)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_CHANNNELNO,pcfg->stLocalChan[i].stRemoteChanCfg[j].iRemoteChannelNo)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_PRESETID,pcfg->stLocalChan[i].stRemoteChanCfg[j].iRemotePtzPreset)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_PRESETENABLE,pcfg->stLocalChan[i].stRemoteChanCfg[j].iRemotePtzPreset)
					READ_ATTRIBUTE_INT_NO_RETURN(ptmpDigiremote,XML_ATTR_CONNECTYPE,pcfg->stLocalChan[i].stRemoteChanCfg[j].iConType)
					ptmpDigiremote = ptmpDigiremote->NextSiblingElement(XML_TAG_DIGIREMOTECH);
					j++;
				}
				ptmp = ptmp->NextSiblingElement(XML_TAG_LOCALCFG);
				i++;
			}
		}
		break;
	case CFG_DISPLAY_SPLITTOUR:
		{
			//RV_WSCC* pcfg = (RV_WSCC*)pBufout;
			//TiXmlElement* root = doc.FirstChildElement(XML_TAG_SPLIT);
			//if(!root)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SIZE,pcfg->dwSize)
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_COMBINNUM,pcfg->iCombineNum)
			//TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_DISPLAYSPLIT);
			//if(ptmp)
			//{
			//	TiXmlElement* ptmpsub = ptmp->FirstChildElement(XML_TAG_SPLITMODE);
			//	if(ptmpsub)
			//	{
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_SPLITMODE,pcfg->stSplitCfg.stSplitMode.iSplitMode)
			//	}
			//	TiXmlElement* ptmpsub2 = ptmp->FirstChildElement(XML_TAG_SPLITCOMBINECH);
			//	if(ptmpsub2)
			//	{
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub2,XML_ATTR_CHMASK,pcfg->stSplitCfg.stCombineCH.iChMask)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub2,XML_ATTR_SPECIALCH,pcfg->stSplitCfg.stCombineCH.ucSpecialCh)
			//	}
			//}	
			//TiXmlElement* ptmp2 = root->FirstChildElement(XML_TAG_DISPLAYTOUR);
			//if(ptmp2)
			//{
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BENABLE,pcfg->stTourCfg.bTourEnable)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_INTERVALTIME,pcfg->stTourCfg.usIntervalTime)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_RES,pcfg->stTourCfg.ucRes)
			//}
			//int i=0;
			//TiXmlElement* ptmp3= root->FirstChildElement(XML_TAG_SPLITCOMBIN);
			//while( ptmp3 && i < pcfg->iCombineNum)
			//{
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_SPLITMODE,pcfg->stSplitCombine[i].ucSplitMode)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTRSPLITTYPE, pcfg->stSplitCombine[i].ucSplitType)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_COMBINNUM, pcfg->stSplitCombine[i].ucCombinNums)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_RES, pcfg->stSplitCombine[i].ucRes)
			//	TiXmlElement* ptmp4= ptmp3->FirstChildElement(XML_TAG_SPLITCOMBINECH);
			//	int j=0;
			//	while(ptmp4&&j<pcfg->stSplitCombine[i].ucCombinNums)
			//	{
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp4,XML_ATTR_CHMASK,pcfg->stSplitCombine[i].stCombineCh[j].iChMask);
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp4,XML_ATTR_SPECIALCH,pcfg->stSplitCombine[i].stCombineCh[j].ucSpecialCh);
			//		ptmp4 = ptmp4->NextSiblingElement(XML_TAG_SPLITCOMBINECH);
			//		j++;
			//	}
			//	ptmp3 = ptmp3->NextSiblingElement(XML_TAG_SPLITCOMBIN);
			//	i++;
			//}
		}
		break;
	case CFG_ENCODE_MAIN_CFG:
		{			
			//RV_NET_ENCODE* pcfg = (RV_NET_ENCODE*)pBufout;
			//TiXmlElement* root = doc.FirstChildElement(XML_TAG_NETENCODE);
			//if(!root)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_STREAMINDEX,pcfg->iSteamIndex);
			//TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_MEDIAFMT);
			//if(ptmp)
			//{
			//	TiXmlElement* ptmp2 = ptmp->FirstChildElement(XML_TAG_VIDEOFMT);
			//	if(ptmp2)
			//	{
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_COMRESSION,pcfg->dstFmt.vfFormat.iCompression)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_RESOLUTION,pcfg->dstFmt.vfFormat.iResolution)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BITRATECONTROL,pcfg->dstFmt.vfFormat.iBitRateControl)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_QUALITY,pcfg->dstFmt.vfFormat.iQuality)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_FPS,pcfg->dstFmt.vfFormat.nFPS)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BITRATE,pcfg->dstFmt.vfFormat.nBitRate)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_GOP,pcfg->dstFmt.vfFormat.iGOP)			
			//	}
			//	TiXmlElement* ptmp3 = ptmp->FirstChildElement(XML_TAG_AUDIOFMT);
			//	if(ptmp3)
			//	{
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_BITRATE,pcfg->dstFmt.afFormat.nBitRate);
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_FREQUENCE,pcfg->dstFmt.afFormat.nFrequency);
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_LAUDIOVOLUMN,pcfg->dstFmt.afFormat.ucLAudioVolumn);
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_RAUDIOVOLUMN,pcfg->dstFmt.afFormat.ucRAudioVolumn);						
			//	}		
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BAUDIOENABLE,pcfg->dstFmt.bAudioEnable);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BVIDEOENABLE,pcfg->dstFmt.bVideoEnable);
			//}
		}
		break;
	case  CFG_CODE_SVAC_CFG:
		{
			//RV_NET_SVAC_PARAM* pcfg = (RV_NET_SVAC_PARAM*)pBufout;
			//TiXmlElement* root = doc.FirstChildElement(XML_TAG_SVACPARAM);
			//if(!root)
			//{
			//	nRet = -1;
			//	break;
			//}
			//
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pcfg->ucChannel)
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ENTRYTYPE,pcfg->ucEncryptType)
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_PICQUAL,pcfg->ucQuality)
			//READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_ENTRYKEY,(char *)&pcfg->ucEncryptKey[0],16)

			//TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_SVACROIENC);
			//if(ptmp)
			//{
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BENABLE,pcfg->stROIENC.ucEnable)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ROINK,pcfg->stROIENC.ucROI_NK)
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_QPLEVEL,pcfg->stROIENC.ucROI_QP_LEVEL)
			//	TiXmlElement* ptmpsub = ptmp->FirstChildElement(XML_TAG_ROIAREA);
			//	int i=0;
			//	while(ptmpsub&&i<4)
			//	{
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_BENABLE,pcfg->stROIENC.stROIArea[i].ucEnable)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_LEVEL,pcfg->stROIENC.stROIArea[i].ucLevel)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_BMOTION,pcfg->stROIENC.stROIArea[i].ucMotionDetectEnable)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_LEFT,pcfg->stROIENC.stROIArea[i].stArea.left)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_RIGHT,pcfg->stROIENC.stROIArea[i].stArea.right)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_TOP,pcfg->stROIENC.stROIArea[i].stArea.top)
			//		READ_ATTRIBUTE_INT_NO_RETURN(ptmpsub,XML_ATTR_BOTTOM,pcfg->stROIENC.stROIArea[i].stArea.bottom)
			//		ptmpsub = ptmpsub->NextSiblingElement(XML_TAG_ROIAREA);
			//		i++;
			//	}				
			//}
			//TiXmlElement* ptmp2 = root->FirstChildElement(XML_TAG_SVACSVCENC);
			//if(ptmp2)
			//{
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BENABLE,pcfg->stSVCENC.ucEnable);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_RCMODE,pcfg->stSVCENC.ucSVC_RC_MODE);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_ROINK,pcfg->stSVCENC.ucSVC_ROI_NK);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_STMMODE,pcfg->stSVCENC.ucSVC_STM_MODE);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BLQUALITY,pcfg->stSVCENC.ucSVC_BL_Quality);
			//}
			//TiXmlElement* ptmp3 = root->FirstChildElement(XML_TAG_SVACSEEXTENC);
			//if(ptmp3)
			//{
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_BENABLE,pcfg->stEXTENC.ucEnable);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_EXTTIME,pcfg->stEXTENC.ucSE_EXT_TIME);
			//	READ_ATTRIBUTE_INT_NO_RETURN(ptmp3,XML_ATTR_EXTINFO,pcfg->stEXTENC.ucSE_EXT_INFO);			
			//}
		}
		break;
	case  CFG_DEV_TALKFDECODE_INFO:
		{
			VG_TALKDECODE_INFO* pcfg = (VG_TALKDECODE_INFO*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_TALKENCORDINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			int nType = 0;
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ENCODETYPE,nType)
			pcfg->encodeType = (VG_TALK_CODING_TYPE)nType;
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BITRATE,pcfg->nBitRate)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SAMPLERATE,pcfg->nSampleRate)	
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SAMPLEBIT,pcfg->nSampleBit)
		}
		break;
	case CFG_QUERY_RECODR:
		{
			Vix_QUERY_RECORD* pcfg = (Vix_QUERY_RECORD*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_TALKENCORDINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BPIC,pcfg->bPic)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BNEWSEARD,pcfg->bNewSeard)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_QUERYID,pcfg->nQueryID)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_LOGINID,pcfg->lLoginID)
			/*char cdevid[256] ={0};
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_DEVID,cdevid,256)
			pcfg->lDevID =cdevid;*/
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_DEVID,pcfg->lDevID)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pcfg->nChannelNo)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BEGTIME,pcfg->lBegTime)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ENDTIME,pcfg->lEndTime)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_RECORDTYPE,pcfg->nRecordType)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_MAXSIZE,pcfg->nMaxSize)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SOURCE,pcfg->nSource)

			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_DEVIP,pcfg->szDevIP,256)
		}
		break;
	case CFG_QUERY_RECODR_RESULT:
		{
			Vix_RECORD_INFO* pcfg = (Vix_RECORD_INFO*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_QUERYRECORD_RESULT);
			if(!root)
			{
				nRet = -1;
				break;
			}
			int nTmp = 0;
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_NUM,nTmp)
			if(nTmp!=nNum)
			{
				nRet = -1;
				break;
			}
			int i = 0;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_RECORDINFO);
			while(ptmp&& i< nNum)
			{
				//modify xwy
				//pcfg = pcfg + i;
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_DEVID,pcfg->szID,256)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_SOURCE,pcfg->source)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BPIC,pcfg->bPic)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_RECORDTYPE,pcfg->recordType)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,pcfg->chn)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BEGTIME,pcfg->lstartTime)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ENDTIME,pcfg->lendTime)				
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_LENGTH,pcfg->length)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_DRIVENUM,pcfg->dskInfo.a.ndriveno)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_STARTCRUSTER,pcfg->dskInfo.a.nstartcluster)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_PARTNO,pcfg->dskInfo.a.npartno)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_HINT,pcfg->dskInfo.a.nhint)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_NAME,pcfg->name,256)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_DEVIP,pcfg->szIp,256)
				ptmp = ptmp->NextSiblingElement(XML_TAG_RECORDINFO);
				//add xwy
				pcfg = pcfg + 1;

				i++;
			}
		}
		break;
	case CFG_RECORD_INFO:
		{
			Vix_RECORD_INFO* pcfg = (Vix_RECORD_INFO*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_RECORDINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_DEVID,pcfg->szID,32)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SOURCE,pcfg->source)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BPIC,pcfg->bPic)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_RECORDTYPE,pcfg->recordType)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pcfg->chn)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BEGTIME,pcfg->lstartTime)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ENDTIME,pcfg->lendTime)				
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_LENGTH,pcfg->length)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_DRIVENUM,pcfg->dskInfo.a.ndriveno)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_STARTCRUSTER,pcfg->dskInfo.a.nstartcluster)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_PARTNO,pcfg->dskInfo.a.npartno)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_HINT,pcfg->dskInfo.a.nhint)
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_NAME,pcfg->name,256)
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_DEVIP,pcfg->szIp,256)
		}
		break;
	//--
	case CFG_DEVSEARCH_RESULT:
		{
			DevSearchInfo* pcfg = (DevSearchInfo*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_DEVSEARCHRESULT);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_NUM,nNum)
			int i = 0;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_SEARCHDEVICE);
			while(ptmp&& i< nNum)
			{
				//modify xwy 改为+1
				//pcfg = pcfg + i;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_DEVPORT,pcfg->nPort)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_DEVCTYPE,pcfg->nDevType,24)
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_FAC,pcfg->nDevFac)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_NAME,pcfg->szDevName,32)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_DEVIP,pcfg->szIP,32)
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_MAC,pcfg->szMac,40)
				ptmp = ptmp->NextSiblingElement(XML_TAG_SEARCHDEVICE);
				pcfg = pcfg + 1;
				i++;
			}
		}
		break;
	case CFG_NETWORK_INFO:
		{
			VG_NET_CONFIGURE* pinfo = (VG_NET_CONFIGURE*)pBufout;

			TiXmlElement* root = doc.FirstChildElement(XML_TAG_NETWORK);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_DEVIP,pinfo->szIp,20)
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_SUBMASK,pinfo->szSubMask,20)
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_GATEWAY,pinfo->szGatWay,20)
			READ_ATTRIBUTE_STR_NO_RETURN(root,XML_ATTR_MAC,pinfo->szMacAddr,32)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_TCPPORT,pinfo->TCPPort)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_UDPPORT,pinfo->UDPPort)
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_DHCP,pinfo->nValid)
		}
		break;
	case CFG_CODE_CFG:
		{
			VG_CODE_CFG* pinfo = (VG_CODE_CFG*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_CODECFG);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pinfo->nChannel);
			int i = 0;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_CODEONCHANNEL);
			while(ptmp)
			{
				int nTmpChannel = 0;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,nTmpChannel);
				TiXmlElement* psubmain =ptmp->FirstChildElement(XML_TAG_MAINCODECFG);
				if(psubmain)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_BAUDIOENABLE,pinfo->mainEncode[nTmpChannel].iAudioEnable );
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_BVIDEOENABLE,pinfo->mainEncode[nTmpChannel].iVideoEnable );
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_COMRESSION,pinfo->mainEncode[nTmpChannel].iCompressionType );
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_RESOLUTION,pinfo->mainEncode[nTmpChannel].iResolution );
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_FPS,pinfo->mainEncode[nTmpChannel].nFPS );
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_BITRATE,pinfo->mainEncode[nTmpChannel].nBitRate );
					READ_ATTRIBUTE_INT_NO_RETURN(psubmain,XML_ATTR_GOP,pinfo->mainEncode[nTmpChannel].iGOP );
				}
				TiXmlElement* psub=ptmp->FirstChildElement(XML_TAG_SUBCODECFG1);
				if(psub)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_BAUDIOENABLE,pinfo->SubEncode[nTmpChannel].iAudioEnable );
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_BVIDEOENABLE,pinfo->SubEncode[nTmpChannel].iVideoEnable );
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_COMRESSION,pinfo->SubEncode[nTmpChannel].iCompressionType );
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_RESOLUTION,pinfo->SubEncode[nTmpChannel].iResolution );
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_FPS,pinfo->SubEncode[nTmpChannel].nFPS );
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_BITRATE,pinfo->SubEncode[nTmpChannel].nBitRate );
					READ_ATTRIBUTE_INT_NO_RETURN(psub,XML_ATTR_GOP,pinfo->SubEncode[nTmpChannel].iGOP );
				}
				ptmp = ptmp->NextSiblingElement(XML_TAG_CODEONCHANNEL);
			}		
		}
		break;
	//osd信息叠加---------------------------------------------------------
	case  CFG_OSD_INFO:
		{
			VG_OSD_PLASEINFO* pinfo = (VG_OSD_PLASEINFO*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_OSDINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pinfo->nCurchannel);
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SIZE,pinfo->nsize);
			int i = 0;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_OSDINFO);
			while(ptmp)
			{
				int nChannel= 0;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,nChannel);
				pinfo->info[nChannel].cfg.iChannel = nChannel;
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_NAME,pinfo->info[nChannel].cfg.strChannelName,32);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BTIMEOSD,pinfo->info[nChannel].btimeEnable);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BNAMEOSD,pinfo->info[nChannel].bNameEnable);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_NAMELEFT,pinfo->info[nChannel].namePose.nleft);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_NAMERIGHT,pinfo->info[nChannel].namePose.nright);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_NAMETOP,pinfo->info[nChannel].namePose.ntop);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_NAMEBOTTOM,pinfo->info[nChannel].namePose.nbottom);

				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_TIMELEFT,pinfo->info[nChannel].timepose.nleft);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_TIMERIGHT,pinfo->info[nChannel].timepose.nright);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_TIMETOP,pinfo->info[nChannel].timepose.ntop);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_TIMEBOTTOM,pinfo->info[nChannel].timepose.nbottom);				

				ptmp = ptmp->NextSiblingElement(XML_TAG_OSDINFO);
			}
		}
		break;
	case CFG_PTZ_PROTOCOL:
		{
			VG_PTZ_PROCFG* pinfo = (VG_PTZ_PROCFG*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_PTZINFO);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pinfo->nChannel);
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SIZE,pinfo->nTotalChanel);
			int i = 0;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_PTZINFO);
			while(ptmp)
			{
				int nChannel= 0;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,nChannel);
				pinfo->cfg[nChannel].nChannel = nChannel;
				READ_ATTRIBUTE_STR_NO_RETURN(ptmp,XML_ATTR_PTZPROTOCOL,pinfo->cfg[nChannel].szProtocol,32);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_DATABIT,pinfo->cfg[nChannel].nDataBit);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_STOPBIT,pinfo->cfg[nChannel].nStopBit);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_PARITY,pinfo->cfg[nChannel].nParity);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BAURATE,pinfo->cfg[nChannel].nBaudRate);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ADDRESS,pinfo->cfg[nChannel].nAddress);
				ptmp = ptmp->NextSiblingElement(XML_TAG_PTZINFO);
			}			
		}
		break;
	case CFG_ALARM_ALARMIN:
		{	
			VG_ALARMIN_CFG_SCHEDULE* pinfo = (VG_ALARMIN_CFG_SCHEDULE*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_ALARMIN);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pinfo->nCurChannel);
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_TOTALCHANNEL,pinfo->nTotalChannel);
			int i = 0;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_ALARMIN);
			while(ptmp)
			{
				int nChannel= 0;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,nChannel)
				pinfo->alarmInCfg[nChannel].iChannel = nChannel;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ALARMTYPE,pinfo->alarmInCfg[nChannel].byAlarmType);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ALARMENABLE,pinfo->alarmInCfg[nChannel].byAlarmEn);

				TiXmlElement* ptmp1= ptmp->FirstChildElement(XML_TAG_TIMESECT);
				int m=0,n=0;
				while(ptmp1)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BENABLE,pinfo->alarmInCfg[nChannel].stSect[m][n].bEnable);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BEGHOUR,pinfo->alarmInCfg[nChannel].stSect[m][n].iBeginHour);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BEGMIN,pinfo->alarmInCfg[nChannel].stSect[m][n].iBeginMin);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BEGSEC,pinfo->alarmInCfg[nChannel].stSect[m][n].iBeginSec);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_ENDHOUR,pinfo->alarmInCfg[nChannel].stSect[m][n].iEndHour);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_ENDMIN,pinfo->alarmInCfg[nChannel].stSect[m][n].iEndMin);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_ENDSEC,pinfo->alarmInCfg[nChannel].stSect[m][n].iEndSec);

					ptmp1 = ptmp1->NextSiblingElement(XML_TAG_TIMESECT);
					n++;
					if(n==6)
					{
						m++;
						n = 0;
					}

				}
				TiXmlElement *ptmp2 = ptmp->FirstChildElement(XML_TAG_MSGHAND);
				if(ptmp2)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BPROMPT,pinfo->alarmInCfg[nChannel].struHandle.bPrompt);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BMAILE,pinfo->alarmInCfg[nChannel].struHandle.bMail);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BALARMOUTPUT,pinfo->alarmInCfg[nChannel].struHandle.bAlarmoutput);

					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_RELALARMOUT,(char*)pinfo->alarmInCfg[nChannel].struHandle.byRelAlarmOut,32);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_DURATION,pinfo->alarmInCfg[nChannel].struHandle.dwDuration);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BRECORD,pinfo->alarmInCfg[nChannel].struHandle.bRecord);	
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_RECORDCHANNEL,(char*)pinfo->alarmInCfg[nChannel].struHandle.byRecordChannel,32);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_RECLATCH,pinfo->alarmInCfg[nChannel].struHandle.dwRecLatch);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BSNAP,pinfo->alarmInCfg[nChannel].struHandle.bSnap);	
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_SNAPCHANNEL,(char*)pinfo->alarmInCfg[nChannel].struHandle.bySnap,32);	

					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BTOUR,pinfo->alarmInCfg[nChannel].struHandle.bTour);	
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_TOURCHANNEL,(char*)pinfo->alarmInCfg[nChannel].struHandle.byTour,32);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_EVENTLATCH,pinfo->alarmInCfg[nChannel].struHandle.dwEventLatch);	
				}	
				ptmp = ptmp->NextSiblingElement(XML_TAG_ALARMIN);
			}			
		}
		break;

	case CFG_ALARM_OTHER:
		{
			VG_ALARM_CFG_SCHEDULE* pinfo = (VG_ALARM_CFG_SCHEDULE*)pBufout;
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_ALARM);
			if(!root)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_CHANNNELNO,pinfo->nCurChannel);
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_TOTALCHANNEL,pinfo->nTotalChannel);
			READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ALARMTYPE,pinfo->nAlarmType);

			int nType = pinfo->nAlarmType;
			int i = 0;

			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_ALARM);
			while(ptmp)
			{
				int nChannel= 0;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHANNNELNO,nChannel)
					pinfo->alarmInCfg[nType][nChannel].iChannel = nChannel;
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ALARMENABLE,pinfo->alarmInCfg[nType][nChannel].byAlarmEn);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ROW,pinfo->alarmInCfg[nType][nChannel].iRow);
				READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_COL,pinfo->alarmInCfg[nType][nChannel].iCol);

				TiXmlElement*pSelect = ptmp->FirstChildElement(XML_TAG_SELECT);
				int k=0;
				//选中区域
				while(pSelect)
				{
					//此处以1表示未选中，2表示选中
					READ_ATTRIBUTE_STR_NO_RETURN(pSelect,XML_ATTR_SELECT,(char*)pinfo->alarmInCfg[nType][nChannel].bySelect[k],33);
					pSelect = pSelect->NextSiblingElement(XML_TAG_SELECT);
				}

				TiXmlElement* ptmp1= ptmp->FirstChildElement(XML_TAG_TIMESECT);
				int m=0,n=0;
				while(ptmp1)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BENABLE,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].bEnable);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BEGHOUR,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].iBeginHour);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BEGMIN,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].iBeginMin);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_BEGSEC,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].iBeginSec);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_ENDHOUR,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].iEndHour);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_ENDMIN,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].iEndMin);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp1,XML_ATTR_ENDSEC,pinfo->alarmInCfg[nType][nChannel].stSect[m][n].iEndSec);

					ptmp1 = ptmp1->NextSiblingElement(XML_TAG_TIMESECT);
					n++;
					if(n==6)
					{
						m++;
						n = 0;
					}
				}
				TiXmlElement *ptmp2 = ptmp->FirstChildElement(XML_TAG_MSGHAND);
				if(ptmp2)
				{
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BPROMPT,pinfo->alarmInCfg[nType][nChannel].struHandle.bPrompt);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BMAILE,pinfo->alarmInCfg[nType][nChannel].struHandle.bMail);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BALARMOUTPUT,pinfo->alarmInCfg[nType][nChannel].struHandle.bAlarmoutput);

					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_RELALARMOUT,(char*)pinfo->alarmInCfg[nType][nChannel].struHandle.byRelAlarmOut,32);
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_DURATION,pinfo->alarmInCfg[nType][nChannel].struHandle.dwDuration);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BRECORD,pinfo->alarmInCfg[nType][nChannel].struHandle.bRecord);	
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_RECORDCHANNEL,(char*)pinfo->alarmInCfg[nType][nChannel].struHandle.byRecordChannel,32);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_RECLATCH,pinfo->alarmInCfg[nType][nChannel].struHandle.dwRecLatch);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BSNAP,pinfo->alarmInCfg[nType][nChannel].struHandle.bSnap);	
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_SNAPCHANNEL,(char*)pinfo->alarmInCfg[nType][nChannel].struHandle.bySnap,32);	

					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_BTOUR,pinfo->alarmInCfg[nType][nChannel].struHandle.bTour);	
					READ_ATTRIBUTE_STR_NO_RETURN(ptmp2,XML_ATTR_TOURCHANNEL,(char*)pinfo->alarmInCfg[nType][nChannel].struHandle.byTour,32);	
					READ_ATTRIBUTE_INT_NO_RETURN(ptmp2,XML_ATTR_EVENTLATCH,pinfo->alarmInCfg[nType][nChannel].struHandle.dwEventLatch);	
				}	
				ptmp = ptmp->NextSiblingElement(XML_TAG_ALARM);
			}			
		}
		break;
	case CFG_DEV_COMMON:
		{
			VG_COMM_CFG* pinfo = (VG_COMM_CFG*)pBufout;

			TiXmlElement* root = doc.FirstChildElement(XML_TAG_COMMON);
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_GENERAL);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_SUPPORTVIDEOFMT,pinfo->stGeneral.ucSupportVideoFmt);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_TOTALCHANNEL,pinfo->stGeneral.ucCurVideoFmt);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ALARMTYPE,pinfo->stGeneral.uiSupportLanguage);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ALARMTYPE,pinfo->stGeneral.uiCurLanguage);
		}
		break;
	case CFG_VIDEO_CAPTURE_CFG:
		{
			//RV_CONFIG_CAMERA* pInfo = (RV_CONFIG_CAMERA*)pBufout;
			//TiXmlElement* root = doc.FirstChildElement(XML_TAG_CAMERAVIDCAP);

			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_HORREVERSE,			pInfo->HorReverse);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_VERREVERSE,			pInfo->VerReverse);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_EXPOSURETYPE,		pInfo->ExposureType);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_AESENSITIVITY,		pInfo->AESensitivity);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BACKLIGHT,			pInfo->Backlight);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_WHITEBALANCEMODE,	pInfo->WhiteBalanceMode);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SHADECORR,			pInfo->ShadeCorr);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BADCORR,			pInfo->BadCorr);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SHUTTER,			pInfo->shutter);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_ANTIFLICKER,		pInfo->AntiFlicker);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_COLORTEMP,			pInfo->ColorTemp);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_YUVCUT,				pInfo->YUVCut);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_IRCUT,				pInfo->IRCut);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_PAA,				pInfo->PAA);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_COLOR2WHITEBLACK,	pInfo->Color2WhiteBlack);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_SENSORTYPE,			pInfo->SensorType);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_WDRENABLE,			pInfo->WDRenbale);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_BACKLIGHTCOM,		pInfo->BackLightCompensate);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_D1LOOPBACKOUTPUT,	pInfo->D1_loopback_output);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_LIGHTINHIBITION,	pInfo->LightInhibition);
			//READ_ATTRIBUTE_INT_NO_RETURN(root,XML_ATTR_AOTOSHUTTER,		pInfo->shutter);
		}
		break;
	case CFG_DEV_ABILITY:
		{
			TiXmlElement* root = doc.FirstChildElement(XML_TAG_ABILITY);
			if(!root)
			{
				return -101;
			}
			ParaseAbility((Ability)nParam1,pBufout,root,0);			
		}
		break;
	}

	return nRet;
}
int CXMLConfigure::PacketXMLInside(CONFIG_TYPE ntype,string& strinfo,void* pBufIn, int nChannel,int nNum,long nParam1 /*= 0*/,long nParam2/*=0*/)
{

	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc.LinkEndChild(decl);
	
	switch(ntype)
	{
	//case CFG_DEV_INFO:
	//	{
	//		VG_DevInfo* pDevInfo = (VG_DevInfo*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_DEVICEINFO);
	//		root->SetAttribute(XML_ATTR_TOTALCHANNEL, pDevInfo->nTotalchannel);
	//		root->SetAttribute(XML_ATTR_ALARMCHANNEL, pDevInfo->nAlarmchannel);
	//		root->SetAttribute(XML_ATTR_DIGICHANNEL,  pDevInfo->nDigichannel);
	//		root->SetAttribute(XML_ATTR_NEWSEARCHPIC,  pDevInfo->bsearchnewpic);
	//		root->SetAttribute(XML_ATTR_ALARMOUTCHANNEL,pDevInfo->nAlarmOutchannel);
	//		root->SetAttribute(XML_ATTR_SVAC,pDevInfo->bsvac);
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_CHANNEL_NAME:
	//	{
	//		VG_CHANNELNAME_CFG* pcfg = (VG_CHANNELNAME_CFG*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_CHANNELNAME);
	//		root->SetAttribute(XML_ATTR_SIZE,nChannel);			
	//		for(int i=0;i < nChannel;i++)
	//		{
	//			TiXmlElement* pChannel = new TiXmlElement(XML_TAG_CHANNEL);
	//			pChannel->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//			pChannel->SetAttribute(XML_ATTR_NAME,pcfg->channel[i].strChannelName);
	//			root->LinkEndChild(pChannel);
	//		}
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_TALKFORMATLIST:
	//	{
	//		//RVDEV_TALKFORMAT_LIST* pcfg = (RVDEV_TALKFORMAT_LIST*)pBufIn;
	//		//TiXmlElement* root = new TiXmlElement(XML_TAG_TALKFORMAT);
	//		//root->SetAttribute(XML_ATTR_NUM,pcfg->nSupportNum);
	//		//for(int i=0;i<pcfg->nSupportNum;i++)
	//		//{
	//		//	TiXmlElement* pEncode = new TiXmlElement(XML_TAG_TALKENCORDINFO);
	//		//	pEncode->SetAttribute(XML_ATTR_ENCODETYPE,pcfg->type[i].encodeType);
	//		//	pEncode->SetAttribute(XML_ATTR_SAMPLERATE,(int)pcfg->type[i].dwSampleRate);
	//		//	pEncode->SetAttribute(XML_ATTR_SAMPLEBIT,pcfg->type[i].reserved[0]);
	//		//	pEncode->SetAttribute(XML_ATTR_AUDIOBIT,pcfg->type[i].nAudioBit);
	//		//	root->LinkEndChild(pEncode);
	//		//}
	//		//doc.LinkEndChild(root);
	//	}
	//	break;
	case CFG_ADDPRESET_CFG:
	case CFG_DELETEPRESET_CFG:
		{
			//modify 去掉注释
			VG_PRESET_INFO* pCfg = (VG_PRESET_INFO*)pBufIn;
			//RV_PRESET_INFO* pCfg = (RV_PRESET_INFO*)pBufIn;	
			TiXmlElement* root = new TiXmlElement(XML_TAG_PRESETINFO);

			root->SetAttribute(XML_ATTR_CHANNNELNO,pCfg->ucChannel);
			root->SetAttribute(XML_ATTR_PRESETID,pCfg->ucPresetID);
			root->SetAttribute(XML_ATTR_SPEED,pCfg->ucPresetID);
			root->SetAttribute(XML_ATTR_DWELLTIME,pCfg->iDWellTime);
			root->SetAttribute(XML_ATTR_PRESETNAME,(char*)&pCfg->szPresetName[0]);
			doc.LinkEndChild(root);
			//end
		}
		break;
	//case CFG_ADDTOURPRESET_CFG:
	//case CFG_DEV_DELTOURPRESET_CFG:
	//	{
	//		//modify xwy qu diao zhu shi
	//		VG_PTZ_TOUR_PRESET* pCfg = (VG_PTZ_TOUR_PRESET*)pBufIn;

	//		//RV_PTZ_TOUR_PRESET* pCfg = (RV_PTZ_TOUR_PRESET*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_TOURPRESET);	
	//		TiXmlElement* ptmp = new TiXmlElement(XML_TAG_PTZCHANNEL);
	//		if(ptmp)
	//		{
	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,pCfg->struChannel.iChannel);
	//			ptmp->SetAttribute(XML_ATTR_PRESETID,pCfg->struChannel.iIndex);
	//		}
	//		TiXmlElement* pTmp2 = new TiXmlElement(XML_TAG_PRESETINFO);
	//		if(pTmp2)
	//		{
	//			pTmp2->SetAttribute(XML_ATTR_CHANNNELNO,pCfg->struPreset.ucChannel);
	//			pTmp2->SetAttribute(XML_ATTR_PRESETID,pCfg->struPreset.ucPresetID);
	//			pTmp2->SetAttribute(XML_ATTR_SPEED,pCfg->struPreset.iSpeed);
	//			pTmp2->SetAttribute(XML_ATTR_DWELLTIME,pCfg->struPreset.iDWellTime);
	//			pTmp2->SetAttribute(XML_ATTR_PRESETNAME,(char*)&pCfg->struPreset.szPresetName[0]);

	//		}	
	//		root->LinkEndChild(ptmp);
	//		root->LinkEndChild(pTmp2);
	//		doc.LinkEndChild(root);
	//		//end
	//	}
	//	break;	
	//case CFG_DEV_CLEARTOUR_CFG:
	//	{
	//		//RV_PTZ_CHANNEL* pCfg = (RV_PTZ_CHANNEL*)pBufIn;
	//		//TiXmlElement* root = new TiXmlElement(XML_TAG_PTZCHANNEL);
	//		//if(root)
	//		//{
	//		//	root->SetAttribute(XML_ATTR_CHANNNELNO,pCfg->iChannel);
	//		//	root->SetAttribute(XML_ATTR_PRESETID,pCfg->iIndex);
	//		//}
	//		//doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_PTZPRESET_SCHEDULE:
	//	{
	//		VG_PTZ_PRESET_SCHEDULE* pcfg = (VG_PTZ_PRESET_SCHEDULE*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_PRESETSCHEDULE);
	//		root->SetAttribute(XML_ATTR_NUM,(int)pcfg->dwCount);
	//		for(int i=0;i<pcfg->dwCount;i++)
	//		{
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_PRESETINFO);
	//			ptmp->SetAttribute(XML_ATTR_DWELLTIME,pcfg->struPreset[i].iDWellTime);
	//			ptmp->SetAttribute(XML_ATTR_SPEED,pcfg->struPreset[i].iSpeed);
	//			ptmp->SetAttribute(XML_ATTR_PRESETID,pcfg->struPreset[i].ucPresetID);
	//			ptmp->SetAttribute(XML_ATTR_PRESETNAME,(char*)&pcfg->struPreset[i].szPresetName[0]);
	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,pcfg->struPreset[i].ucChannel);
	//			root->LinkEndChild(ptmp);
	//		}
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	///*case CFG_TOUR_SCHEDULE:
	//	{
	//		VG_PTZ_TOUR_SCHEDULE* pcfg = (VG_PTZ_TOUR_SCHEDULE*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_TOURSCHEDULE);
	//		root->SetAttribute(XML_ATTR_NUM,(int)pcfg->dwCount);
	//		int nCount = 0;
	//		TiXmlElement *ptmp2 = NULL;
	//		for(int i=0;i<pcfg->dwCount;i++)
	//		{				
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_TOURINFO);
	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,(int)pcfg->struTour[i].ucChannel);
	//			ptmp->SetAttribute(XML_ATTR_TOURINDEX,pcfg->struTour[i].ucTourIndex);
	//			ptmp->SetAttribute(XML_ATTR_PRESETCOUNT,pcfg->struTour[i].ucPresetCnt);
	//			
	//			nCount = min(64, (int)pcfg->struTour[i].ucPresetCnt);
	//			for(int j=0;j<nCount;j++)
	//			{
	//				ptmp2 = new TiXmlElement(XML_TAG_PRESETINFO);
	//				ptmp2->SetAttribute(XML_ATTR_DWELLTIME, pcfg->struTour[i].preset[j].iDWellTime);
	//				ptmp2->SetAttribute(XML_ATTR_SPEED, pcfg->struTour[i].preset[j].iSpeed);
	//				ptmp2->SetAttribute(XML_ATTR_PRESETID, pcfg->struTour[i].preset[j].ucPresetID);
	//				ptmp->LinkEndChild(ptmp2);
	//			}	
	//			root->LinkEndChild(ptmp);
	//		}
	//		doc.LinkEndChild(root);
	//	}
	//	break;*/
	//case CFG_DIGICHAN_TOUR:
	//	{			
	//		VG_DIGI_CH_TOUR_CFG* pcfg = (VG_DIGI_CH_TOUR_CFG*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_DIGICHTOUR);
	//		root->SetAttribute(XML_ATTR_SIZE,(int)pcfg->dwSize);
	//		for(int i=0;i<32;i++)
	//		{				
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_LOCALCFG);
	//			ptmp->SetAttribute(XML_ATTR_REMOTECHCNT,(unsigned long)pcfg->stLocalChan[i].dwRemoteChanCount);
	//			TiXmlElement* ptmpsub = new TiXmlElement(XML_TAG_DIGILOCALCH);
	//			ptmpsub->SetAttribute(XML_ATTR_BENABLE,pcfg->stLocalChan[i].stLocalChCfg.BEnable);
	//			ptmpsub->SetAttribute(XML_ATTR_CHANNELTYPE,pcfg->stLocalChan[i].stLocalChCfg.iDeviceChannelType);
	//			ptmpsub->SetAttribute(XML_ATTR_MODE,pcfg->stLocalChan[i].stLocalChCfg.iMode);
	//			ptmpsub->SetAttribute(XML_ATTR_TOURTIME,(int)pcfg->stLocalChan[i].stLocalChCfg.uiTourTime);
	//			ptmpsub->SetAttribute(XML_ATTR_NOTTOURINDEX,(int)pcfg->stLocalChan[i].stLocalChCfg.uiNotTourCfgIndex);
	//			ptmpsub->SetAttribute(XML_ATTR_DECODEPOLICY,pcfg->stLocalChan[i].stLocalChCfg.iDecodePolicy);
	//			ptmpsub->SetAttribute(XML_ATTR_AVENABLE,pcfg->stLocalChan[i].stLocalChCfg.iAVEnable);
	//			ptmp->LinkEndChild(ptmpsub);
	//			for(int j=0;j<32&&j<pcfg->stLocalChan[i].dwRemoteChanCount;j++)
	//			{
	//				TiXmlElement* ptmprem = new TiXmlElement(XML_TAG_DIGIREMOTECH);
	//				ptmprem->SetAttribute(XML_ATTR_BENABLE,pcfg->stLocalChan[i].stRemoteChanCfg[j].BEnable);
	//				ptmprem->SetAttribute(XML_ATTR_CFGNAME,pcfg->stLocalChan[i].stRemoteChanCfg[j].cChName);
	//				ptmprem->SetAttribute(XML_ATTR_DEVIP,pcfg->stLocalChan[i].stRemoteChanCfg[j].cDeviceIP);
	//				ptmprem->SetAttribute(XML_ATTR_DEVPORT,pcfg->stLocalChan[i].stRemoteChanCfg[j].iDevicePort);
	//				ptmprem->SetAttribute(XML_ATTR_USERNAME,pcfg->stLocalChan[i].stRemoteChanCfg[j].cDeviceUserName);
	//				ptmprem->SetAttribute(XML_ATTR_PASSWORD,pcfg->stLocalChan[i].stRemoteChanCfg[j].cDevicePassword);
	//				ptmprem->SetAttribute(XML_ATTR_DEVCTYPE,pcfg->stLocalChan[i].stRemoteChanCfg[j].iDevType);
	//				ptmprem->SetAttribute(XML_ATTR_CHANNNELNO,pcfg->stLocalChan[i].stRemoteChanCfg[j].iRemoteChannelNo);
	//				ptmprem->SetAttribute(XML_ATTR_PRESETID,pcfg->stLocalChan[i].stRemoteChanCfg[j].iRemotePtzPreset);
	//				ptmprem->SetAttribute(XML_ATTR_PRESETENABLE,pcfg->stLocalChan[i].stRemoteChanCfg[j].iRemotePtzPreset);
	//				ptmprem->SetAttribute(XML_ATTR_CONNECTYPE,pcfg->stLocalChan[i].stRemoteChanCfg[j].iConType);
	//				ptmp->LinkEndChild(ptmprem);
	//			}
	//			root->LinkEndChild(ptmp);
	//		}
	//			doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_DISPLAY_SPLITTOUR:
	//	{
	//		//RV_WSCC* pcfg = (RV_WSCC*)pBufIn;
	//		//TiXmlElement* root = new TiXmlElement(XML_TAG_SPLIT);
	//		//root->SetAttribute(XML_ATTR_SIZE,(int)pcfg->dwSize);
	//		//root->SetAttribute(XML_ATTR_COMBINNUM,pcfg->iCombineNum);

	//		//TiXmlElement* ptmp = new TiXmlElement(XML_TAG_DISPLAYSPLIT);
	//		//{
	//		//	TiXmlElement* ptmpsub = new TiXmlElement(XML_TAG_SPLITMODE);
	//		//	ptmpsub->SetAttribute(XML_ATTR_SPLITMODE,(unsigned long)pcfg->stSplitCfg.stSplitMode.iSplitMode);
	//		//	TiXmlElement* ptmpsub2 = new TiXmlElement(XML_TAG_SPLITCOMBINECH);
	//		//	ptmpsub2->SetAttribute(XML_ATTR_CHMASK,(unsigned long)pcfg->stSplitCfg.stCombineCH.iChMask);
	//		//	ptmpsub2->SetAttribute(XML_ATTR_SPECIALCH,pcfg->stSplitCfg.stCombineCH.ucSpecialCh);
	//		//	ptmp->LinkEndChild(ptmpsub);
	//		//	ptmp->LinkEndChild(ptmpsub2);
	//		//}
	//		//root->LinkEndChild(ptmp);
	//		//TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_DISPLAYTOUR);
	//		//{
	//		//	ptmp2->SetAttribute(XML_ATTR_BENABLE,pcfg->stTourCfg.bTourEnable);
	//		//	ptmp2->SetAttribute(XML_ATTR_INTERVALTIME,pcfg->stTourCfg.usIntervalTime);
	//		//	ptmp2->SetAttribute(XML_ATTR_RES,pcfg->stTourCfg.ucRes);

	//		//}
	//		//root->LinkEndChild(ptmp2);
	//		//for(int i=0;i<V_TOUR_COMBINE_NUM&&i<pcfg->iCombineNum;i++)
	//		//{
	//		//	RV_SPLIT_COMBINE stSplitCombine[V_TOUR_COMBINE_NUM];
	//		//	TiXmlElement* ptmp3= new TiXmlElement(XML_TAG_SPLITCOMBIN);
	//		//	ptmp3->SetAttribute(XML_ATTR_SPLITMODE,pcfg->stSplitCombine[i].ucSplitMode);
	//		//	ptmp3->SetAttribute(XML_ATTRSPLITTYPE, pcfg->stSplitCombine[i].ucSplitType);
	//		//	ptmp3->SetAttribute(XML_ATTR_COMBINNUM, pcfg->stSplitCombine[i].ucCombinNums);
	//		//	ptmp3->SetAttribute(XML_ATTR_RES, pcfg->stSplitCombine[i].ucRes);
	//		//	for(int j=0;j<pcfg->stSplitCombine[i].ucCombinNums&&j<MAX_SPLIT_COMINE_NUMS;j++)
	//		//	{
	//		//		TiXmlElement* ptmp4= new TiXmlElement(XML_TAG_SPLITCOMBINECH);
	//		//		ptmp4->SetAttribute(XML_ATTR_CHMASK,(unsigned long)pcfg->stSplitCombine[i].stCombineCh[j].iChMask);
	//		//		ptmp4->SetAttribute(XML_ATTR_SPECIALCH,pcfg->stSplitCombine[i].stCombineCh[j].ucSpecialCh);
	//		//		ptmp3->LinkEndChild(ptmp4);
	//		//	}		

	//		//	root->LinkEndChild(ptmp3);
	//		//}
	//		//	doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_ENCODE_MAIN_CFG:
	//	{	
	//		//RV_NET_ENCODE* pcfg = (RV_NET_ENCODE*)pBufIn;
	//		//TiXmlElement* root = new TiXmlElement(XML_TAG_NETENCODE);
	//		//root->SetAttribute(XML_ATTR_STREAMINDEX,pcfg->iSteamIndex);
	//		//TiXmlElement* ptmp = new TiXmlElement(XML_TAG_MEDIAFMT);
	//		//{
	//		//	TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_VIDEOFMT);
	//		//	{
	//		//		ptmp2->SetAttribute(XML_ATTR_COMRESSION,pcfg->dstFmt.vfFormat.iCompression);
	//		//		ptmp2->SetAttribute(XML_ATTR_RESOLUTION,pcfg->dstFmt.vfFormat.iResolution);
	//		//		ptmp2->SetAttribute(XML_ATTR_BITRATECONTROL,pcfg->dstFmt.vfFormat.iBitRateControl);
	//		//		ptmp2->SetAttribute(XML_ATTR_QUALITY,pcfg->dstFmt.vfFormat.iQuality);
	//		//		ptmp2->SetAttribute(XML_ATTR_FPS,pcfg->dstFmt.vfFormat.nFPS);
	//		//		ptmp2->SetAttribute(XML_ATTR_BITRATE,pcfg->dstFmt.vfFormat.nBitRate);
	//		//		ptmp2->SetAttribute(XML_ATTR_GOP,pcfg->dstFmt.vfFormat.iGOP);				
	//		//	}
	//		//	TiXmlElement* ptmp3 = new TiXmlElement(XML_TAG_AUDIOFMT);
	//		//	{
	//		//		ptmp3->SetAttribute(XML_ATTR_BITRATE,pcfg->dstFmt.afFormat.nBitRate);
	//		//		ptmp3->SetAttribute(XML_ATTR_FREQUENCE,pcfg->dstFmt.afFormat.nFrequency);
	//		//		ptmp3->SetAttribute(XML_ATTR_LAUDIOVOLUMN,pcfg->dstFmt.afFormat.ucLAudioVolumn);
	//		//		ptmp3->SetAttribute(XML_ATTR_RAUDIOVOLUMN,pcfg->dstFmt.afFormat.ucRAudioVolumn);						
	//		//	}		
	//		//	ptmp->SetAttribute(XML_ATTR_BAUDIOENABLE,pcfg->dstFmt.bAudioEnable);
	//		//	ptmp->SetAttribute(XML_ATTR_BVIDEOENABLE,pcfg->dstFmt.bVideoEnable);
	//		//	ptmp->LinkEndChild(ptmp2);
	//		//	ptmp->LinkEndChild(ptmp3);

	//		//}
	//		//root->LinkEndChild(ptmp);
	//		//	doc.LinkEndChild(root);
	//	}
	//	break;
	//case  CFG_CODE_SVAC_CFG:
	//	{
	//		//RV_NET_SVAC_PARAM* pcfg = (RV_NET_SVAC_PARAM*)pBufIn;
	//		//TiXmlElement* root = new TiXmlElement(XML_TAG_SVACPARAM);
	//		//root->SetAttribute(XML_ATTR_CHANNNELNO,pcfg->ucChannel);
	//		//root->SetAttribute(XML_ATTR_ENTRYTYPE,pcfg->ucEncryptType);
	//		//root->SetAttribute(XML_ATTR_ENTRYKEY,(char *)&pcfg->ucEncryptKey[0]);
	//		//root->SetAttribute(XML_ATTR_PICQUAL,pcfg->ucQuality);

	//		//TiXmlElement* ptmp = new TiXmlElement(XML_TAG_SVACROIENC);
	//		//{
	//		//	ptmp->SetAttribute(XML_ATTR_BENABLE,pcfg->stROIENC.ucEnable);
	//		//	ptmp->SetAttribute(XML_ATTR_ROINK,pcfg->stROIENC.ucROI_NK);
	//		//	ptmp->SetAttribute(XML_ATTR_QPLEVEL,pcfg->stROIENC.ucROI_QP_LEVEL);
	//		//	for(int i=0;i<4;i++)
	//		//	{
	//		//		TiXmlElement* ptmpsub = new TiXmlElement(XML_TAG_ROIAREA);
	//		//		{
	//		//			ptmpsub->SetAttribute(XML_ATTR_BENABLE,pcfg->stROIENC.stROIArea[i].ucEnable);
	//		//			ptmpsub->SetAttribute(XML_ATTR_BMOTION,pcfg->stROIENC.stROIArea[i].ucMotionDetectEnable);
	//		//			ptmpsub->SetAttribute(XML_ATTR_LEVEL,pcfg->stROIENC.stROIArea[i].ucLevel);
	//		//			ptmpsub->SetAttribute(XML_ATTR_LEFT,pcfg->stROIENC.stROIArea[i].stArea.left);
	//		//			ptmpsub->SetAttribute(XML_ATTR_RIGHT,pcfg->stROIENC.stROIArea[i].stArea.right);
	//		//			ptmpsub->SetAttribute(XML_ATTR_TOP,pcfg->stROIENC.stROIArea[i].stArea.top);
	//		//			ptmpsub->SetAttribute(XML_ATTR_BOTTOM,pcfg->stROIENC.stROIArea[i].stArea.bottom);
	//		//		}
	//		//		ptmp->LinkEndChild(ptmpsub);
	//		//	}		
	//		//}
	//		//TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_SVACSVCENC);
	//		//{
	//		//	ptmp2->SetAttribute(XML_ATTR_BENABLE,pcfg->stSVCENC.ucEnable);
	//		//	ptmp2->SetAttribute(XML_ATTR_RCMODE,pcfg->stSVCENC.ucSVC_RC_MODE);
	//		//	ptmp2->SetAttribute(XML_ATTR_ROINK,pcfg->stSVCENC.ucSVC_ROI_NK);
	//		//	ptmp2->SetAttribute(XML_ATTR_STMMODE,pcfg->stSVCENC.ucSVC_STM_MODE);
	//		//	ptmp2->SetAttribute(XML_ATTR_BLQUALITY,pcfg->stSVCENC.ucSVC_BL_Quality);
	//		//}
	//		//TiXmlElement* ptmp3 = new TiXmlElement(XML_TAG_SVACSEEXTENC);
	//		//{
	//		//	ptmp3->SetAttribute(XML_ATTR_BENABLE,pcfg->stEXTENC.ucEnable);
	//		//	ptmp3->SetAttribute(XML_ATTR_EXTTIME,pcfg->stEXTENC.ucSE_EXT_TIME);
	//		//	ptmp3->SetAttribute(XML_ATTR_EXTINFO,pcfg->stEXTENC.ucSE_EXT_INFO);			
	//		//}
	//		//root->LinkEndChild(ptmp);
	//		//root->LinkEndChild(ptmp2);
	//		//root->LinkEndChild(ptmp3);		
	//		//doc.LinkEndChild(root);
	//	}
	//	break;
	//case  CFG_DEV_TALKFDECODE_INFO:
	//	{
	//		//add xwy
	//		VG_TALKDECODE_INFO* pcfg = (VG_TALKDECODE_INFO*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_TALKENCORDINFO);
	//		root->SetAttribute(XML_ATTR_ENCODETYPE,pcfg->encodeType);	
	//		root->SetAttribute(XML_ATTR_BITRATE,pcfg->nBitRate);
	//		root->SetAttribute(XML_ATTR_SAMPLERATE,(int)pcfg->nSampleRate);	
	//		root->SetAttribute(XML_ATTR_SAMPLEBIT,(int)pcfg->nSampleBit);
	//		doc.LinkEndChild(root);
	//		//end


	//		//RVDEV_TALKDECODE_INFO* pcfg = (RVDEV_TALKDECODE_INFO*)pBufIn;
	//		//TiXmlElement* root = new TiXmlElement(XML_TAG_TALKENCORDINFO);
	//		//int nType =(int)pcfg->encodeType;
	//		//root->SetAttribute(XML_ATTR_ENCODETYPE,nType);				
	//		//root->SetAttribute(XML_ATTR_BITRATE,pcfg->nAudioBit);
	//		//root->SetAttribute(XML_ATTR_SAMPLERATE,(int)pcfg->dwSampleRate);	
	//		//int nsamplebit = pcfg->reserved[0];
	//		//root->SetAttribute(XML_ATTR_SAMPLEBIT,nsamplebit);
	//		//doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_QUERY_RECODR:
	//	{
	//		Vix_QUERY_RECORD* pcfg = (Vix_QUERY_RECORD*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_TALKENCORDINFO);
	//		
	//		root->SetAttribute(XML_ATTR_BPIC,pcfg->bPic);
	//		root->SetAttribute(XML_ATTR_BNEWSEARD,pcfg->bNewSeard);
	//		root->SetAttribute(XML_ATTR_QUERYID,(int)pcfg->nQueryID);
	//		root->SetAttribute(XML_ATTR_LOGINID,pcfg->lLoginID);
	//		root->SetAttribute(XML_ATTR_DEVID,pcfg->lDevID);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pcfg->nChannelNo);
	//		root->SetAttribute(XML_ATTR_BEGTIME,pcfg->lBegTime);
	//		root->SetAttribute(XML_ATTR_ENDTIME,pcfg->lEndTime);
	//		root->SetAttribute(XML_ATTR_RECORDTYPE,pcfg->nRecordType);
	//		root->SetAttribute(XML_ATTR_MAXSIZE,pcfg->nMaxSize);
	//		root->SetAttribute(XML_ATTR_SOURCE,pcfg->nSource);
	//		root->SetAttribute(XML_ATTR_DEVIP,pcfg->szDevIP);
	//		root->SetAttribute(XML_ATTR_PROTOCOL,pcfg->nProtocolType);
	//		root->SetAttribute(XML_ATTR_STREAM,pcfg->nStreamType);

	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_QUERY_RECODR_RESULT:
	//	{
	//		Vix_RECORD_INFO* pcfg = (Vix_RECORD_INFO*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_QUERYRECORD_RESULT);			
	//		root->SetAttribute(XML_ATTR_NUM,nNum);
	//		int i = 0;
	//		
	//		for(int i=0;i< nNum;i++)
	//		{				
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_RECORDINFO);
	//			ptmp->SetAttribute(XML_ATTR_DEVID,pcfg->szID);
	//			ptmp->SetAttribute(XML_ATTR_SOURCE,pcfg->source);
	//			ptmp->SetAttribute(XML_ATTR_BPIC,pcfg->bPic);
	//			ptmp->SetAttribute(XML_ATTR_RECORDTYPE,pcfg->recordType);
	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,pcfg->chn);
	//			ptmp->SetAttribute(XML_ATTR_BEGTIME,pcfg->lstartTime);
	//			ptmp->SetAttribute(XML_ATTR_ENDTIME,pcfg->lendTime);			
	//			ptmp->SetAttribute(XML_ATTR_LENGTH,pcfg->length);
	//			ptmp->SetAttribute(XML_ATTR_DRIVENUM,(int)pcfg->dskInfo.a.ndriveno);
	//			ptmp->SetAttribute(XML_ATTR_STARTCRUSTER,(int)pcfg->dskInfo.a.nstartcluster);
	//			ptmp->SetAttribute(XML_ATTR_PARTNO,(int)pcfg->dskInfo.a.npartno);
	//			ptmp->SetAttribute(XML_ATTR_HINT,(int)pcfg->dskInfo.a.nhint);
	//			ptmp->SetAttribute(XML_ATTR_NAME,pcfg->name);
	//			ptmp->SetAttribute(XML_ATTR_DEVIP,pcfg->szIp);
	//			root->LinkEndChild(ptmp);
	//			pcfg = pcfg ++;
	//		}
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_RECORD_INFO:
	//	{
	//		Vix_RECORD_INFO* pcfg = (Vix_RECORD_INFO*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_RECORDINFO);
	//		root->SetAttribute(XML_ATTR_DEVID,pcfg->szID);
	//		root->SetAttribute(XML_ATTR_SOURCE,pcfg->source);
	//		root->SetAttribute(XML_ATTR_BPIC,pcfg->bPic);
	//		root->SetAttribute(XML_ATTR_RECORDTYPE,pcfg->recordType);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pcfg->chn);
	//		root->SetAttribute(XML_ATTR_BEGTIME,pcfg->lstartTime);
	//		//modify xwy
	//		root->SetAttribute(XML_ATTR_ENDTIME,pcfg->lendTime);
	//		//root->SetAttribute(XML_ATTR_ENDTIME,pcfg->lstartTime);
	//		//end
	//		root->SetAttribute(XML_ATTR_LENGTH,pcfg->length);
	//		root->SetAttribute(XML_ATTR_DRIVENUM,(int)pcfg->dskInfo.a.ndriveno);
	//		root->SetAttribute(XML_ATTR_STARTCRUSTER,(int)pcfg->dskInfo.a.nstartcluster);
	//		root->SetAttribute(XML_ATTR_PARTNO,(int)pcfg->dskInfo.a.npartno);
	//		root->SetAttribute(XML_ATTR_HINT,(int)pcfg->dskInfo.a.nhint);
	//		root->SetAttribute(XML_ATTR_NAME,pcfg->name);
	//		root->SetAttribute(XML_ATTR_DEVIP,pcfg->szIp);
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_DEVSEARCH_RESULT:
	//	{
	//		DevSearchInfo* pcfg = (DevSearchInfo*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_DEVSEARCHRESULT);
	//		root->SetAttribute(XML_ATTR_NUM,nNum);			
	//		for(int i=0;i < nNum; i++)
	//		{
	//			TiXmlElement* ptmp =new TiXmlElement(XML_TAG_SEARCHDEVICE);
	//			ptmp->SetAttribute(XML_ATTR_DEVPORT,pcfg->nPort);
	//			ptmp->SetAttribute(XML_ATTR_DEVCTYPE,pcfg->nDevType);
	//			ptmp->SetAttribute(XML_ATTR_FAC,pcfg->nDevFac);
	//			ptmp->SetAttribute(XML_ATTR_NAME,pcfg->szDevName);
	//			ptmp->SetAttribute(XML_ATTR_DEVIP,pcfg->szIP);
	//			ptmp->SetAttribute(XML_ATTR_MAC,pcfg->szMac);
	//			root->LinkEndChild(ptmp);
	//			pcfg = pcfg ++;
	//		}
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	////版本信息---
	//case CFG_VERSION_INFO:
	//	{
	//		VG_VERSION_INFO* pinfo = (VG_VERSION_INFO*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_VERSIONINFO);			
	//		root->SetAttribute(XML_ATTR_VERSION,pinfo->szVersion);
	//		root->SetAttribute(XML_ATTR_SERIO,pinfo->szSerio);	
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	////网络配置信息
	//case CFG_NETWORK_INFO:
	//	{
	//		VG_NET_CONFIGURE* pinfo = (VG_NET_CONFIGURE*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_NETWORK);
	//		root->SetAttribute(XML_ATTR_DEVIP,pinfo->szIp);
	//		root->SetAttribute(XML_ATTR_SUBMASK,pinfo->szSubMask);
	//		root->SetAttribute(XML_ATTR_GATEWAY,pinfo->szGatWay);
	//		root->SetAttribute(XML_ATTR_MAC,pinfo->szMacAddr);
	//		root->SetAttribute(XML_ATTR_TCPPORT,pinfo->TCPPort);
	//		root->SetAttribute(XML_ATTR_UDPPORT,pinfo->UDPPort);
	//		root->SetAttribute(XML_ATTR_UDPPORT,pinfo->UDPPort);
	//		root->SetAttribute(XML_ATTR_DHCP,pinfo->nValid);
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_CODE_CFG:
	//	{
	//		VG_CODE_CFG* pinfo = (	VG_CODE_CFG*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_CODECFG);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->nChannel);			
	//		if(nChannel!=-1)
	//		{
	//			TiXmlElement* pcodechn = new TiXmlElement(XML_TAG_CODEONCHANNEL);
	//			pcodechn->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->nChannel);
	//			{
	//				int i = nChannel;
	//				TiXmlElement* psubmain = new TiXmlElement(XML_TAG_MAINCODECFG);
	//				psubmain->SetAttribute(XML_ATTR_BAUDIOENABLE,pinfo->mainEncode[i].iAudioEnable );
	//				psubmain->SetAttribute(XML_ATTR_BVIDEOENABLE,pinfo->mainEncode[i].iVideoEnable );
	//				psubmain->SetAttribute(XML_ATTR_COMRESSION,pinfo->mainEncode[i].iCompressionType );
	//				psubmain->SetAttribute(XML_ATTR_RESOLUTION,pinfo->mainEncode[i].iResolution );
	//				psubmain->SetAttribute(XML_ATTR_FPS,pinfo->mainEncode[i].nFPS );
	//				psubmain->SetAttribute(XML_ATTR_BITRATE,pinfo->mainEncode[i].nBitRate );
	//				psubmain->SetAttribute(XML_ATTR_GOP,pinfo->mainEncode[i].iGOP );

	//				TiXmlElement* psubmain1 = new TiXmlElement(XML_TAG_SUBCODECFG1);
	//				psubmain1->SetAttribute(XML_ATTR_BAUDIOENABLE,pinfo->SubEncode[i].iAudioEnable );
	//				psubmain1->SetAttribute(XML_ATTR_BVIDEOENABLE,pinfo->SubEncode[i].iVideoEnable );
	//				psubmain1->SetAttribute(XML_ATTR_COMRESSION,pinfo->SubEncode[i].iCompressionType );
	//				psubmain1->SetAttribute(XML_ATTR_RESOLUTION,pinfo->SubEncode[i].iResolution );
	//				psubmain1->SetAttribute(XML_ATTR_FPS,pinfo->SubEncode[i].nFPS );
	//				psubmain1->SetAttribute(XML_ATTR_BITRATE,pinfo->SubEncode[i].nBitRate );
	//				psubmain1->SetAttribute(XML_ATTR_GOP,pinfo->SubEncode[i].iGOP );

	//				pcodechn->LinkEndChild(psubmain);
	//				pcodechn->LinkEndChild(psubmain1);
	//			}
	//			root->LinkEndChild(pcodechn);				
	//		}
	//		else
	//		{
	//			for(int i=0;i<VG_MAX_CHANNELNUM;i++)
	//			{
	//				TiXmlElement* pcodechn = new TiXmlElement(XML_TAG_CODEONCHANNEL);
	//				pcodechn->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//				{
	//					TiXmlElement* psubmain = new TiXmlElement(XML_TAG_MAINCODECFG);
	//					psubmain->SetAttribute(XML_ATTR_BAUDIOENABLE,pinfo->mainEncode[i].iAudioEnable );
	//					psubmain->SetAttribute(XML_ATTR_BVIDEOENABLE,pinfo->mainEncode[i].iVideoEnable );
	//					psubmain->SetAttribute(XML_ATTR_COMRESSION,pinfo->mainEncode[i].iCompressionType );
	//					psubmain->SetAttribute(XML_ATTR_RESOLUTION,pinfo->mainEncode[i].iResolution );
	//					psubmain->SetAttribute(XML_ATTR_FPS,pinfo->mainEncode[i].nFPS );
	//					psubmain->SetAttribute(XML_ATTR_BITRATE,pinfo->mainEncode[i].nBitRate );
	//					psubmain->SetAttribute(XML_ATTR_GOP,pinfo->mainEncode[i].iGOP );

	//					TiXmlElement* psubmain1 = new TiXmlElement(XML_TAG_SUBCODECFG1);
	//					psubmain1->SetAttribute(XML_ATTR_BAUDIOENABLE,pinfo->SubEncode[i].iAudioEnable );
	//					psubmain1->SetAttribute(XML_ATTR_BVIDEOENABLE,pinfo->SubEncode[i].iVideoEnable );
	//					psubmain1->SetAttribute(XML_ATTR_COMRESSION,pinfo->SubEncode[i].iCompressionType );
	//					psubmain1->SetAttribute(XML_ATTR_RESOLUTION,pinfo->SubEncode[i].iResolution );
	//					psubmain1->SetAttribute(XML_ATTR_FPS,pinfo->SubEncode[i].nFPS );
	//					psubmain1->SetAttribute(XML_ATTR_BITRATE,pinfo->SubEncode[i].nBitRate );
	//					psubmain1->SetAttribute(XML_ATTR_GOP,pinfo->SubEncode[i].iGOP );

	//					pcodechn->LinkEndChild(psubmain);
	//					pcodechn->LinkEndChild(psubmain1);
	//				}
	//				root->LinkEndChild(pcodechn);			
	//			}
	//		}
	//		doc.LinkEndChild(root);	
	//	}
	//	break;
	//case CFG_OSD_INFO:
	//	{		
	//		VG_OSD_PLASEINFO* pinfo = (VG_OSD_PLASEINFO*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_OSDINFO);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->nCurchannel);
	//		root->SetAttribute(XML_ATTR_SIZE,pinfo->nsize);
	//		if(pinfo->nCurchannel==-1)
	//		{
	//			for(int i=0;i<pinfo->nsize&&i < VG_MAX_CHANNELNUM;i++)
	//			{
	//				TiXmlElement* ptmp = new TiXmlElement(XML_TAG_OSDINFO);

	//				ptmp->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->info[i].cfg.iChannel);
	//				ptmp->SetAttribute(XML_ATTR_NAME,pinfo->info[i].cfg.strChannelName);
	//				ptmp->SetAttribute(XML_ATTR_BTIMEOSD,pinfo->info[i].btimeEnable);
	//				ptmp->SetAttribute(XML_ATTR_BNAMEOSD,pinfo->info[i].bNameEnable);
	//				ptmp->SetAttribute(XML_ATTR_NAMELEFT,pinfo->info[i].namePose.nleft);
	//				ptmp->SetAttribute(XML_ATTR_NAMERIGHT,pinfo->info[i].namePose.nright);
	//				ptmp->SetAttribute(XML_ATTR_NAMETOP,pinfo->info[i].namePose.ntop);
	//				ptmp->SetAttribute(XML_ATTR_NAMEBOTTOM,pinfo->info[i].namePose.nbottom);

	//				ptmp->SetAttribute(XML_ATTR_TIMELEFT,pinfo->info[i].timepose.nleft);
	//				ptmp->SetAttribute(XML_ATTR_TIMERIGHT,pinfo->info[i].timepose.nright);
	//				ptmp->SetAttribute(XML_ATTR_TIMETOP,pinfo->info[i].timepose.ntop);
	//				ptmp->SetAttribute(XML_ATTR_TIMEBOTTOM,pinfo->info[i].timepose.nbottom);
	//				root->LinkEndChild(ptmp);
	//			}				
	//		}
	//		else
	//		{
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_OSDINFO);
	//			int i = pinfo->nCurchannel;

	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->info[i].cfg.iChannel);
	//			ptmp->SetAttribute(XML_ATTR_NAME,pinfo->info[i].cfg.strChannelName);
	//			ptmp->SetAttribute(XML_ATTR_BTIMEOSD,pinfo->info[i].btimeEnable);
	//			ptmp->SetAttribute(XML_ATTR_BNAMEOSD,pinfo->info[i].bNameEnable);
	//			ptmp->SetAttribute(XML_ATTR_NAMELEFT,pinfo->info[i].namePose.nleft);
	//			ptmp->SetAttribute(XML_ATTR_NAMERIGHT,pinfo->info[i].namePose.nright);
	//			ptmp->SetAttribute(XML_ATTR_NAMETOP,pinfo->info[i].namePose.ntop);
	//			ptmp->SetAttribute(XML_ATTR_NAMEBOTTOM,pinfo->info[i].namePose.nbottom);

	//			ptmp->SetAttribute(XML_ATTR_TIMELEFT,pinfo->info[i].timepose.nleft);
	//			ptmp->SetAttribute(XML_ATTR_TIMERIGHT,pinfo->info[i].timepose.nright);
	//			ptmp->SetAttribute(XML_ATTR_TIMETOP,pinfo->info[i].timepose.ntop);
	//			ptmp->SetAttribute(XML_ATTR_TIMEBOTTOM,pinfo->info[i].timepose.nbottom);
	//			root->LinkEndChild(ptmp);
	//		}
	//		doc.LinkEndChild(root);			
	//	}
	//	break;
	//case CFG_PTZ_PROTOCOL:
	//	{
	//		VG_PTZ_PROCFG* pinfo = (VG_PTZ_PROCFG*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_PTZINFO);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->nChannel);
	//		root->SetAttribute(XML_ATTR_TOTALCHANNEL,pinfo->nTotalChanel);
	//		root->SetAttribute(XML_ATTR_SIZE,pinfo->dwDecProListNum);
	//		string strdec;
	//		for (int index = 0; index < pinfo->dwDecProListNum; ++ index)
	//		{
	//			strdec += pinfo->DecProName[index];
	//			if (index != pinfo->dwDecProListNum-1)
	//			{
	//				strdec +="$";
	//			}
	//			
	//		}
	//		root->SetAttribute(XML_ATTR_NAME,strdec.c_str());
	//		if(pinfo->nChannel==-1)
	//		{
	//			for(int i=0;i < VG_MAX_CHANNELNUM&&i<pinfo->nTotalChanel;i++)
	//			{
	//				TiXmlElement* ptmp = new TiXmlElement(XML_TAG_PTZINFO);

	//				ptmp->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//				ptmp->SetAttribute(XML_ATTR_PTZPROTOCOL,pinfo->cfg[i].szProtocol);
	//				ptmp->SetAttribute(XML_ATTR_DATABIT,pinfo->cfg[i].nDataBit);
	//				ptmp->SetAttribute(XML_ATTR_STOPBIT,pinfo->cfg[i].nStopBit);
	//				ptmp->SetAttribute(XML_ATTR_PARITY,pinfo->cfg[i].nParity);
	//				ptmp->SetAttribute(XML_ATTR_BAURATE,pinfo->cfg[i].nBaudRate);
	//				ptmp->SetAttribute(XML_ATTR_ADDRESS,pinfo->cfg[i].nAddress);					
	//				root->LinkEndChild(ptmp);
	//			}				
	//		}
	//		else
	//		{
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_PTZINFO);
	//			int i = pinfo->nChannel;

	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//			ptmp->SetAttribute(XML_ATTR_PTZPROTOCOL,pinfo->cfg[i].szProtocol);
	//			ptmp->SetAttribute(XML_ATTR_DATABIT,pinfo->cfg[i].nDataBit);
	//			ptmp->SetAttribute(XML_ATTR_STOPBIT,pinfo->cfg[i].nStopBit);
	//			ptmp->SetAttribute(XML_ATTR_PARITY,pinfo->cfg[i].nParity);
	//			ptmp->SetAttribute(XML_ATTR_BAURATE,pinfo->cfg[i].nBaudRate);
	//			ptmp->SetAttribute(XML_ATTR_ADDRESS,pinfo->cfg[i].nAddress);			
	//			root->LinkEndChild(ptmp);

	//		}
	//		doc.LinkEndChild(root);
	//	}
	//	break;
	//case CFG_ALARM_ALARMIN:
	//	{
	//		VG_ALARMIN_CFG_SCHEDULE* pinfo = (VG_ALARMIN_CFG_SCHEDULE*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_ALARMIN);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->nCurChannel);
	//		root->SetAttribute(XML_ATTR_TOTALCHANNEL,pinfo->nTotalChannel);
	//		if(pinfo->nCurChannel==-1)
	//		{
	//			for(int i=0;i < VG_MAX_CHANNELNUM&&i<pinfo->nTotalChannel;i++)
	//			{
	//				TiXmlElement* ptmp = new TiXmlElement(XML_TAG_ALARMIN);
	//				ptmp->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//				ptmp->SetAttribute(XML_ATTR_ALARMTYPE,pinfo->alarmInCfg[i].byAlarmType);
	//				ptmp->SetAttribute(XML_ATTR_ALARMENABLE,pinfo->alarmInCfg[i].byAlarmEn);
	//				for(int m=0;m<7;m++)
	//				{
	//					for(int n=0;n<6;n++)
	//					{
	//						TiXmlElement* ptmp1 = new TiXmlElement(XML_TAG_TIMESECT);
	//						ptmp1->SetAttribute(XML_ATTR_BENABLE,pinfo->alarmInCfg[i].stSect[m][n].bEnable);
	//						ptmp1->SetAttribute(XML_ATTR_BEGHOUR,pinfo->alarmInCfg[i].stSect[m][n].iBeginHour);
	//						ptmp1->SetAttribute(XML_ATTR_BEGMIN,pinfo->alarmInCfg[i].stSect[m][n].iBeginMin);
	//						ptmp1->SetAttribute(XML_ATTR_BEGSEC,pinfo->alarmInCfg[i].stSect[m][n].iBeginSec);
	//						ptmp1->SetAttribute(XML_ATTR_ENDHOUR,pinfo->alarmInCfg[i].stSect[m][n].iEndHour);
	//						ptmp1->SetAttribute(XML_ATTR_ENDMIN,pinfo->alarmInCfg[i].stSect[m][n].iEndMin);
	//						ptmp1->SetAttribute(XML_ATTR_ENDSEC,pinfo->alarmInCfg[i].stSect[m][n].iEndSec);
	//						ptmp->LinkEndChild(ptmp1);
	//					}
	//				}
	//				TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_MSGHAND);
	//				ptmp2->SetAttribute(XML_ATTR_BPROMPT,pinfo->alarmInCfg[i].struHandle.bPrompt);
	//				ptmp2->SetAttribute(XML_ATTR_BMAILE,pinfo->alarmInCfg[i].struHandle.bMail);
	//				ptmp2->SetAttribute(XML_ATTR_BALARMOUTPUT,pinfo->alarmInCfg[i].struHandle.bAlarmoutput);
	//				ptmp2->SetAttribute(XML_ATTR_RELALARMOUT,(char*)pinfo->alarmInCfg[i].struHandle.byRelAlarmOut);
	//				ptmp2->SetAttribute(XML_ATTR_DURATION,pinfo->alarmInCfg[i].struHandle.dwDuration);	
	//				ptmp2->SetAttribute(XML_ATTR_BRECORD,pinfo->alarmInCfg[i].struHandle.bRecord);	
	//				ptmp2->SetAttribute(XML_ATTR_RECORDCHANNEL,(char*)pinfo->alarmInCfg[i].struHandle.byRecordChannel);	
	//				ptmp2->SetAttribute(XML_ATTR_RECLATCH,pinfo->alarmInCfg[i].struHandle.dwRecLatch);	
	//				ptmp2->SetAttribute(XML_ATTR_BSNAP,pinfo->alarmInCfg[i].struHandle.bSnap);	
	//				ptmp2->SetAttribute(XML_ATTR_SNAPCHANNEL,(char*)pinfo->alarmInCfg[i].struHandle.bySnap);	

	//				ptmp2->SetAttribute(XML_ATTR_BTOUR,pinfo->alarmInCfg[i].struHandle.bTour);	

	//				ptmp2->SetAttribute(XML_ATTR_TOURCHANNEL,(char*)pinfo->alarmInCfg[i].struHandle.byTour);	
	//				ptmp2->SetAttribute(XML_ATTR_EVENTLATCH,pinfo->alarmInCfg[i].struHandle.dwEventLatch);	

	//				ptmp->LinkEndChild(ptmp2);
	//				root->LinkEndChild(ptmp);
	//			}				
	//		}
	//		else
	//		{
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_ALARMIN);
	//			int i = pinfo->nCurChannel;
	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//			ptmp->SetAttribute(XML_ATTR_ALARMTYPE,pinfo->alarmInCfg[i].byAlarmType);
	//			ptmp->SetAttribute(XML_ATTR_ALARMENABLE,pinfo->alarmInCfg[i].byAlarmEn);
	//			for(int m=0;m<7;m++)
	//			{
	//				for(int n=0;n<6;n++)
	//				{
	//					TiXmlElement* ptmp1 = new TiXmlElement(XML_TAG_TIMESECT);
	//					ptmp1->SetAttribute(XML_ATTR_BENABLE,pinfo->alarmInCfg[i].stSect[m][n].bEnable);
	//					ptmp1->SetAttribute(XML_ATTR_BEGHOUR,pinfo->alarmInCfg[i].stSect[m][n].iBeginHour);
	//					ptmp1->SetAttribute(XML_ATTR_BEGMIN,pinfo->alarmInCfg[i].stSect[m][n].iBeginMin);
	//					ptmp1->SetAttribute(XML_ATTR_BEGSEC,pinfo->alarmInCfg[i].stSect[m][n].iBeginSec);
	//					ptmp1->SetAttribute(XML_ATTR_ENDHOUR,pinfo->alarmInCfg[i].stSect[m][n].iEndHour);
	//					ptmp1->SetAttribute(XML_ATTR_ENDMIN,pinfo->alarmInCfg[i].stSect[m][n].iEndMin);
	//					ptmp1->SetAttribute(XML_ATTR_ENDSEC,pinfo->alarmInCfg[i].stSect[m][n].iEndSec);
	//					ptmp->LinkEndChild(ptmp1);
	//				}
	//			}
	//			TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_MSGHAND);
	//			ptmp2->SetAttribute(XML_ATTR_BPROMPT,pinfo->alarmInCfg[i].struHandle.bPrompt);
	//			ptmp2->SetAttribute(XML_ATTR_BMAILE,pinfo->alarmInCfg[i].struHandle.bMail);
	//			ptmp2->SetAttribute(XML_ATTR_BALARMOUTPUT,pinfo->alarmInCfg[i].struHandle.bAlarmoutput);
	//			ptmp2->SetAttribute(XML_ATTR_RELALARMOUT,(char*)pinfo->alarmInCfg[i].struHandle.byRelAlarmOut);
	//			ptmp2->SetAttribute(XML_ATTR_DURATION,pinfo->alarmInCfg[i].struHandle.dwDuration);	
	//			ptmp2->SetAttribute(XML_ATTR_BRECORD,pinfo->alarmInCfg[i].struHandle.bRecord);	
	//			ptmp2->SetAttribute(XML_ATTR_RECORDCHANNEL,(char*)pinfo->alarmInCfg[i].struHandle.byRecordChannel);	
	//			ptmp2->SetAttribute(XML_ATTR_RECLATCH,pinfo->alarmInCfg[i].struHandle.dwRecLatch);	
	//			ptmp2->SetAttribute(XML_ATTR_BSNAP,pinfo->alarmInCfg[i].struHandle.bSnap);	
	//			ptmp2->SetAttribute(XML_ATTR_SNAPCHANNEL,(char*)pinfo->alarmInCfg[i].struHandle.bySnap);	

	//			ptmp2->SetAttribute(XML_ATTR_BTOUR,pinfo->alarmInCfg[i].struHandle.bTour);	
	//			ptmp2->SetAttribute(XML_ATTR_TOURCHANNEL,(char*)pinfo->alarmInCfg[i].struHandle.byTour);	
	//			ptmp2->SetAttribute(XML_ATTR_EVENTLATCH,pinfo->alarmInCfg[i].struHandle.dwEventLatch);	
	//			ptmp->LinkEndChild(ptmp2);
	//			root->LinkEndChild(ptmp);
	//		}
	//		doc.LinkEndChild(root);			
	//	}
	//	break;
	//case CFG_ALARM_OTHER:
	//	{
	//		VG_ALARM_CFG_SCHEDULE* pinfo = (VG_ALARM_CFG_SCHEDULE*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_ALARM);
	//		root->SetAttribute(XML_ATTR_CHANNNELNO,pinfo->nCurChannel);
	//		root->SetAttribute(XML_ATTR_TOTALCHANNEL,pinfo->nTotalChannel);
	//		root->SetAttribute(XML_ATTR_ALARMTYPE,pinfo->nAlarmType);
	//		int nType = pinfo->nAlarmType;
	//		if(pinfo->nCurChannel==-1)
	//		{
	//			for(int i=0;i < VG_MAX_CHANNELNUM&&i<pinfo->nTotalChannel;i++)
	//			{
	//				TiXmlElement* ptmp = new TiXmlElement(XML_TAG_ALARM);
	//				ptmp->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//				ptmp->SetAttribute(XML_ATTR_ALARMENABLE,pinfo->alarmInCfg[nType][i].byAlarmEn);

	//				ptmp->SetAttribute(XML_ATTR_COL,(int)pinfo->alarmInCfg[nType][i].iCol);
	//				ptmp->SetAttribute(XML_ATTR_ROW,(int)pinfo->alarmInCfg[nType][i].iRow);
	//				for(int k=0;k<32&&k<pinfo->alarmInCfg[nType][i].iRow;k++)
	//				{
	//					TiXmlElement* ptmp1 = new TiXmlElement(XML_TAG_SELECT);
	//					char szTmp[32]={0};
	//					memcpy(szTmp,pinfo->alarmInCfg[nType][i].bySelect[i],32);
	//					ptmp->SetAttribute(XML_ATTR_SELECT,szTmp);
	//					ptmp->LinkEndChild(ptmp1);
	//				}
	//				for(int m=0;m<7;m++)
	//				{
	//					for(int n=0;n<6;n++)
	//					{
	//						TiXmlElement* ptmp1 = new TiXmlElement(XML_TAG_TIMESECT);
	//						ptmp1->SetAttribute(XML_ATTR_BENABLE,pinfo->alarmInCfg[nType][i].stSect[m][n].bEnable);
	//						ptmp1->SetAttribute(XML_ATTR_BEGHOUR,pinfo->alarmInCfg[nType][i].stSect[m][n].iBeginHour);
	//						ptmp1->SetAttribute(XML_ATTR_BEGMIN,pinfo->alarmInCfg[nType][i].stSect[m][n].iBeginMin);
	//						ptmp1->SetAttribute(XML_ATTR_BEGSEC,pinfo->alarmInCfg[nType][i].stSect[m][n].iBeginSec);
	//						ptmp1->SetAttribute(XML_ATTR_ENDHOUR,pinfo->alarmInCfg[nType][i].stSect[m][n].iEndHour);
	//						ptmp1->SetAttribute(XML_ATTR_ENDMIN,pinfo->alarmInCfg[nType][i].stSect[m][n].iEndMin);
	//						ptmp1->SetAttribute(XML_ATTR_ENDSEC,pinfo->alarmInCfg[nType][i].stSect[m][n].iEndSec);
	//						ptmp->LinkEndChild(ptmp1);
	//					}

	//				}
	//				TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_MSGHAND);
	//				ptmp2->SetAttribute(XML_ATTR_BPROMPT,pinfo->alarmInCfg[nType][i].struHandle.bPrompt);
	//				ptmp2->SetAttribute(XML_ATTR_BMAILE,pinfo->alarmInCfg[nType][i].struHandle.bMail);
	//				ptmp2->SetAttribute(XML_ATTR_BALARMOUTPUT,pinfo->alarmInCfg[nType][i].struHandle.bAlarmoutput);
	//				ptmp2->SetAttribute(XML_ATTR_RELALARMOUT,(char*)pinfo->alarmInCfg[nType][i].struHandle.byRelAlarmOut);
	//				ptmp2->SetAttribute(XML_ATTR_DURATION,pinfo->alarmInCfg[nType][i].struHandle.dwDuration);	
	//				ptmp2->SetAttribute(XML_ATTR_BRECORD,pinfo->alarmInCfg[nType][i].struHandle.bRecord);	
	//				ptmp2->SetAttribute(XML_ATTR_RECORDCHANNEL,(char*)pinfo->alarmInCfg[nType][i].struHandle.byRecordChannel);	
	//				ptmp2->SetAttribute(XML_ATTR_RECLATCH,pinfo->alarmInCfg[nType][i].struHandle.dwRecLatch);	
	//				ptmp2->SetAttribute(XML_ATTR_BSNAP,pinfo->alarmInCfg[nType][i].struHandle.bSnap);	
	//				ptmp2->SetAttribute(XML_ATTR_SNAPCHANNEL,(char*)pinfo->alarmInCfg[nType][i].struHandle.bySnap);	

	//				ptmp2->SetAttribute(XML_ATTR_BTOUR,pinfo->alarmInCfg[nType][i].struHandle.bTour);	
	//				ptmp2->SetAttribute(XML_ATTR_TOURCHANNEL,(char*)pinfo->alarmInCfg[nType][i].struHandle.byTour);	
	//				ptmp2->SetAttribute(XML_ATTR_EVENTLATCH,pinfo->alarmInCfg[nType][i].struHandle.dwEventLatch);	

	//				ptmp->LinkEndChild(ptmp2);
	//				root->LinkEndChild(ptmp);
	//			}				
	//		}
	//		else
	//		{
	//			TiXmlElement* ptmp = new TiXmlElement(XML_TAG_ALARM);
	//			int i = pinfo->nCurChannel;
	//			ptmp->SetAttribute(XML_ATTR_CHANNNELNO,i);
	//			ptmp->SetAttribute(XML_ATTR_ALARMENABLE,pinfo->alarmInCfg[nType][i].byAlarmEn);
	//			ptmp->SetAttribute(XML_ATTR_COL,(int)pinfo->alarmInCfg[nType][i].iCol);
	//			ptmp->SetAttribute(XML_ATTR_ROW,(int)pinfo->alarmInCfg[nType][i].iRow);
	//			for(int k=0;k<32&&k<pinfo->alarmInCfg[nType][i].iRow;k++)
	//			{
	//				TiXmlElement* ptmp1 = new TiXmlElement(XML_TAG_SELECT);
	//				char szTmp[32]={0};
	//				memcpy(szTmp,pinfo->alarmInCfg[nType][i].bySelect[i],32);
	//				ptmp->SetAttribute(XML_ATTR_SELECT,szTmp);
	//				ptmp->LinkEndChild(ptmp1);
	//			}

	//			for(int m=0;m<7;m++)
	//			{
	//				for(int n=0;n<6;n++)
	//				{
	//					TiXmlElement* ptmp1 = new TiXmlElement(XML_TAG_TIMESECT);
	//					ptmp1->SetAttribute(XML_ATTR_BENABLE,pinfo->alarmInCfg[nType][i].stSect[m][n].bEnable);
	//					ptmp1->SetAttribute(XML_ATTR_BEGHOUR,pinfo->alarmInCfg[nType][i].stSect[m][n].iBeginHour);
	//					ptmp1->SetAttribute(XML_ATTR_BEGMIN,pinfo->alarmInCfg[nType][i].stSect[m][n].iBeginMin);
	//					ptmp1->SetAttribute(XML_ATTR_BEGSEC,pinfo->alarmInCfg[nType][i].stSect[m][n].iBeginSec);
	//					ptmp1->SetAttribute(XML_ATTR_ENDHOUR,pinfo->alarmInCfg[nType][i].stSect[m][n].iEndHour);
	//					ptmp1->SetAttribute(XML_ATTR_ENDMIN,pinfo->alarmInCfg[nType][i].stSect[m][n].iEndMin);
	//					ptmp1->SetAttribute(XML_ATTR_ENDSEC,pinfo->alarmInCfg[nType][i].stSect[m][n].iEndSec);
	//					ptmp->LinkEndChild(ptmp1);
	//				}
	//			}
	//			TiXmlElement* ptmp2 = new TiXmlElement(XML_TAG_MSGHAND);
	//			ptmp2->SetAttribute(XML_ATTR_BPROMPT,pinfo->alarmInCfg[nType][i].struHandle.bPrompt);
	//			ptmp2->SetAttribute(XML_ATTR_BMAILE,pinfo->alarmInCfg[nType][i].struHandle.bMail);
	//			ptmp2->SetAttribute(XML_ATTR_BALARMOUTPUT,pinfo->alarmInCfg[nType][i].struHandle.bAlarmoutput);
	//			ptmp2->SetAttribute(XML_ATTR_RELALARMOUT,(char*)pinfo->alarmInCfg[nType][i].struHandle.byRelAlarmOut);
	//			ptmp2->SetAttribute(XML_ATTR_DURATION,pinfo->alarmInCfg[nType][i].struHandle.dwDuration);	
	//			ptmp2->SetAttribute(XML_ATTR_BRECORD,pinfo->alarmInCfg[nType][i].struHandle.bRecord);	
	//			ptmp2->SetAttribute(XML_ATTR_RECORDCHANNEL,(char*)pinfo->alarmInCfg[nType][i].struHandle.byRecordChannel);	
	//			ptmp2->SetAttribute(XML_ATTR_RECLATCH,pinfo->alarmInCfg[nType][i].struHandle.dwRecLatch);	
	//			ptmp2->SetAttribute(XML_ATTR_BSNAP,pinfo->alarmInCfg[nType][i].struHandle.bSnap);	
	//			ptmp2->SetAttribute(XML_ATTR_SNAPCHANNEL,(char*)pinfo->alarmInCfg[nType][i].struHandle.bySnap);	

	//			ptmp2->SetAttribute(XML_ATTR_BTOUR,pinfo->alarmInCfg[nType][i].struHandle.bTour);	
	//			ptmp2->SetAttribute(XML_ATTR_TOURCHANNEL,(char*)pinfo->alarmInCfg[nType][i].struHandle.byTour);	
	//			ptmp2->SetAttribute(XML_ATTR_EVENTLATCH,pinfo->alarmInCfg[nType][i].struHandle.dwEventLatch);	
	//			ptmp->LinkEndChild(ptmp2);
	//			root->LinkEndChild(ptmp);
	//		}
	//		doc.LinkEndChild(root);			
	//	}
	//	break;
	//	case CFG_DEV_COMMON:
	//	{
	//		VG_COMM_CFG* pinfo = (VG_COMM_CFG*)pBufIn;
	//		TiXmlElement* root = new TiXmlElement(XML_TAG_COMMON);
	//		TiXmlElement* ptmp = new TiXmlElement(XML_TAG_GENERAL);
	//		ptmp->SetAttribute(XML_ATTR_SUPPORTVIDEOFMT,pinfo->stGeneral.ucSupportVideoFmt);
	//		ptmp->SetAttribute(XML_ATTR_TOTALCHANNEL,pinfo->stGeneral.ucCurVideoFmt);
	//		ptmp->SetAttribute(XML_ATTR_ALARMTYPE,(int)pinfo->stGeneral.uiSupportLanguage);
	//		ptmp->SetAttribute(XML_ATTR_ALARMTYPE,(int)pinfo->stGeneral.uiCurLanguage);
	//		root->LinkEndChild(ptmp);
	//		doc.LinkEndChild(root);	
	//	}
	//	break;
	//	case CFG_VIDEO_CAPTURE_CFG:
	//		{
	//			//RV_CONFIG_CAMERA* pInfo = (RV_CONFIG_CAMERA*)pBufIn;
	//			//TiXmlElement* root = new TiXmlElement(XML_TAG_CAMERAVIDCAP);
	//	
	//			//root->SetAttribute(XML_ATTR_HORREVERSE,			pInfo->HorReverse);
	//			//root->SetAttribute(XML_ATTR_VERREVERSE,			pInfo->VerReverse);
	//			//root->SetAttribute(XML_ATTR_EXPOSURETYPE,		pInfo->ExposureType);
	//			//root->SetAttribute(XML_ATTR_AESENSITIVITY,		pInfo->AESensitivity);
	//			//root->SetAttribute(XML_ATTR_BACKLIGHT,			pInfo->Backlight);
	//			//root->SetAttribute(XML_ATTR_WHITEBALANCEMODE,	pInfo->WhiteBalanceMode);
	//			//root->SetAttribute(XML_ATTR_SHADECORR,			pInfo->ShadeCorr);
	//			//root->SetAttribute(XML_ATTR_BADCORR,			pInfo->BadCorr);
	//			//root->SetAttribute(XML_ATTR_SHUTTER,			(unsigned long)pInfo->shutter);
	//			//root->SetAttribute(XML_ATTR_ANTIFLICKER,		pInfo->AntiFlicker);
	//			//root->SetAttribute(XML_ATTR_COLORTEMP,			pInfo->ColorTemp);
	//			//root->SetAttribute(XML_ATTR_YUVCUT,				pInfo->YUVCut);
	//			//root->SetAttribute(XML_ATTR_IRCUT,				pInfo->IRCut);
	//			//root->SetAttribute(XML_ATTR_PAA,				pInfo->PAA);
	//			//root->SetAttribute(XML_ATTR_COLOR2WHITEBLACK,	pInfo->Color2WhiteBlack);
	//			//root->SetAttribute(XML_ATTR_SENSORTYPE,			pInfo->SensorType);
	//			//root->SetAttribute(XML_ATTR_WDRENABLE,			pInfo->WDRenbale);
	//			//root->SetAttribute(XML_ATTR_BACKLIGHTCOM,		pInfo->BackLightCompensate);
	//			//root->SetAttribute(XML_ATTR_D1LOOPBACKOUTPUT,	pInfo->D1_loopback_output);
	//			//root->SetAttribute(XML_ATTR_LIGHTINHIBITION,	pInfo->LightInhibition);
	//			//root->SetAttribute(XML_ATTR_AOTOSHUTTER,		pInfo->res1);
	//			//doc.LinkEndChild(root);	
	//		}
	//		break;
	//	case CFG_DEV_ABILITY:
	//	{
	//		TiXmlElement *root =  new TiXmlElement(XML_TAG_ABILITY);
	//		PacketAbility((Ability)nParam1,strinfo,pBufIn,root,0);
	//		doc.LinkEndChild(root);	
	//	}
		break;
	}

	int nOutStream = 0;
	memset(m_buffer,0,1024*1024);
	if(doc.DocToString(m_buffer,1024*1024,nOutStream))
	{
		strinfo = m_buffer;
	}
	return 0;
}

//打包ability
int CXMLConfigure::PacketAbility(Ability nType,string& strinfo, void* pBufIn,TiXmlElement* root,long lParam2)
{
	switch(nType)
	{		
	case VG_ABILITY_CAMERA:
		{
			VG_VIDEOIN_CAPS* pInfo = (VG_VIDEOIN_CAPS*)pBufIn;
			TiXmlElement* pTmp = new TiXmlElement(XML_TAG_CAMERABILITY);

			pTmp->SetAttribute(XML_ATTR_CAMABILITY, (unsigned long)pInfo->uiCamAbility);
			pTmp->SetAttribute(XML_ATTR_EXPOSURE, (unsigned long)pInfo->uiExposure);
			pTmp->SetAttribute(XML_ATTR_SENSPAN,  (unsigned long)pInfo->uiSenSpan);
			pTmp->SetAttribute(XML_ATTR_LIGHTSPAN,  (unsigned long)pInfo->uiBLightSpan);
			pTmp->SetAttribute(XML_ATTR_SHUTTERL,(unsigned long)pInfo->uiShutterL);
			pTmp->SetAttribute(XML_ATTR_SHUTTERH,(unsigned long)pInfo->uiShutterH);
			pTmp->SetAttribute(XML_ATTR_ANTIFLICKER,  (unsigned long)pInfo->uiAntiFlicker);
			pTmp->SetAttribute(XML_ATTR_WHITEBALANCE,(unsigned long)pInfo->uiWhiteBlance);
			pTmp->SetAttribute(XML_ATTR_CHIPTYPE,(unsigned long)pInfo->uiChipType);

			root->LinkEndChild(pTmp);
			
		}
		break;
	case VG_ABILITY_DEVICECFG:
		{
			VG_DevAbility* pInfo = (VG_DevAbility*)pBufIn;
			TiXmlElement* pTmp = new TiXmlElement(XML_TAG_DEVABILITYCFG);
			pTmp->SetAttribute(XML_ATTR_BVERSION, pInfo->bVersion);
			pTmp->SetAttribute(XML_ATTR_BNETWORK, pInfo->bNetWorkcfg);
			pTmp->SetAttribute(XML_ATTR_BENCODECFG,  pInfo->bEncodecfg);
			pTmp->SetAttribute(XML_ATTR_BOSDCFG, pInfo->bOsdcfg);
			pTmp->SetAttribute(XML_ATTR_BPTZCFG, pInfo->bPtzcfg);
			pTmp->SetAttribute(XML_ATTR_BSVACCFG,  pInfo->bSVACcfg);
			pTmp->SetAttribute(XML_ATTR_BVIDEOCAPTURECFG, pInfo->bVideocapturecfg);
			pTmp->SetAttribute(XML_ATTR_BALARMINCFG, pInfo->bAlarmIncfg);
			pTmp->SetAttribute(XML_ATTR_BMOTIONCFG,  pInfo->bMotioncfg);
			root->LinkEndChild(pTmp);
		}
		break;
	case VG_ABILITY_ENCODE:
		{
			VG_Encode_CAPS* pInfo = (VG_Encode_CAPS*)pBufIn;
			TiXmlElement* pTmp = new TiXmlElement(XML_TAG_ENCODEABILITY);
			pTmp->SetAttribute(XML_ATTR_ENCODEMASK, pInfo->ucVideoStandardMask);
			pTmp->SetAttribute(XML_ATTR_STREAMCAP, pInfo->usStreamCap);
			pTmp->SetAttribute(XML_ATTR_COMPRESSION,  pInfo->ucCompression);
			TiXmlElement* pMain = new TiXmlElement(XML_TAG_MAINIMAGESIZE);
			pMain->SetAttribute(XML_ATTR_IMAGESIZEMASK,(unsigned long)pInfo->uiImageSizeMask);
			pTmp->LinkEndChild(pMain);
			for(int i=0;i<32;i++)
			{
				TiXmlElement* pSub = new TiXmlElement(XML_TAG_SUBIMAGESIZE);
				pSub->SetAttribute(XML_ATTR_IMAGESIZEMASK,(unsigned long)pInfo->uiImageSizeMask_Assi[i]);
				pTmp->LinkEndChild(pSub);
			}
			root->LinkEndChild(pTmp);
		}
		break;
	}

	return 0;
}
int CXMLConfigure::ParaseAbility(Ability nType,void* pBuf,TiXmlElement* root,long lParam1)
{
	const char* tmp = NULL;
	int nRet = 0;
	switch(nType)
	{
	case VG_ABILITY_CAMERA:
		{
			//RV_VIDEOIN_CAPS* pInfo = (RV_VIDEOIN_CAPS*)pBuf;
			//TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_CAMERABILITY);
			//if(!ptmp)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CAMABILITY,pInfo->uiCamAbility)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_EXPOSURE,pInfo->uiExposure)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_SENSPAN,pInfo->uiSenSpan)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_LIGHTSPAN,pInfo->uiBLightSpan)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_SHUTTERL,pInfo->uiShutterL)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_SHUTTERH,pInfo->uiShutterH)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ANTIFLICKER,pInfo->uiAntiFlicker)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_WHITEBALANCE,pInfo->uiWhiteBlance)
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_CHIPTYPE,pInfo->uiRes2[0])
		}
		break;
	case VG_ABILITY_DEVICECFG:
		{
			VG_DevAbility* pInfo = (VG_DevAbility*)pBuf;
			TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_DEVABILITYCFG);
			if(!ptmp)
			{
				nRet = -1;
				break;
			}
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BVERSION, pInfo->bVersion);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BNETWORK, pInfo->bNetWorkcfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BENCODECFG,  pInfo->bEncodecfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BOSDCFG, pInfo->bOsdcfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BPTZCFG, pInfo->bPtzcfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BSVACCFG,  pInfo->bSVACcfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BVIDEOCAPTURECFG, pInfo->bVideocapturecfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BALARMINCFG, pInfo->bAlarmIncfg);
			READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_BMOTIONCFG,  pInfo->bMotioncfg);
		}
		break;		
	case VG_ABILITY_ENCODE:
		{
			//RV_ENCODE_CAPS_NET_EN* pInfo = (RV_ENCODE_CAPS_NET_EN*)pBuf;
			//TiXmlElement* ptmp = root->FirstChildElement(XML_TAG_ENCODEABILITY);
			//if(!ptmp)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_ENCODEMASK, pInfo->ucVideoStandardMask);
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_STREAMCAP, pInfo->usStreamCap);
			//READ_ATTRIBUTE_INT_NO_RETURN(ptmp,XML_ATTR_COMPRESSION,  pInfo->ucCompression);
			//TiXmlElement* pMain = ptmp->FirstChildElement(XML_TAG_MAINIMAGESIZE);
			//if(!pMain)
			//{
			//	nRet = -1;
			//	break;
			//}
			//READ_ATTRIBUTE_INT_NO_RETURN(pMain,XML_ATTR_IMAGESIZEMASK,pInfo->uiImageSizeMask);
			//TiXmlElement* pSub  = ptmp->FirstChildElement(XML_TAG_SUBIMAGESIZE);
			//int i=0;
			//while(pSub)
			//{
			//	READ_ATTRIBUTE_INT_NO_RETURN(pSub,XML_ATTR_IMAGESIZEMASK,pInfo->uiImageSizeMask_Assi[i]);
			//	pSub=pSub->NextSiblingElement(XML_TAG_SUBIMAGESIZE);
			//	i++;
			//}
		}
		break;
	}
	return nRet;
}
