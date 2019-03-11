#ifndef VIXHZ_EXPORT_H
#define VIXHZ_EXPORT_H
#include <string>
#include "VixHZ_def.h"

//�����ӿڶ���-------------------------------------

//-------����Ļص�����
//lRealHandle--���ž�� dwDataType-�������ͣ�pBuffer����ָ�� ��dwBufSize ���ݴ�С ��dwUser �û�����
typedef bool (CALLBACK * CallbackFuncRealData)(unsigned long lRealHandle, unsigned long dwDataType, unsigned char *pBuffer, unsigned long dwBufSize, unsigned long dwUser);
typedef void (CALLBACK * DownLoadPosCallBack) (unsigned long lPlayHandle, unsigned long dwTotalSize, unsigned long dwDownLoadSize, unsigned long dwUser);

//�����Խ��ص�
typedef void (CALLBACK * CallbackFuncTalkData)(unsigned long lTalkHandle, char *pDataBuf, unsigned long dwBufSize, unsigned char byAudioFlag, unsigned long dwUser);

//͸�����ڻص�
typedef void (CALLBACK * CallbackTransData)(long lTransHandle, char *pDataBuf, unsigned long dwBufSize, unsigned long dwUser);

//�豸�Ͽ��ص�
typedef void (CALLBACK * fDevDisconnectCallback)(long lLoginID,char*pDevIp, unsigned long lParam1,unsigned long dwUser);

//¼���ѯ���ݻص�
typedef void (CALLBACK * RecordQueryCallback)(base::string pRecFileInfo, int nNum, unsigned long dwUser);

//֪ͨӦ�ò�( display )�豸������Ϣ
//Command:EnumAlarmtype
typedef void (CALLBACK * CallbackAlarmInfo )( long lDevcID , long lCommand , unsigned char* pBuf , unsigned long dwLen , unsigned long dwUser );

//�������Ȼص�
typedef void (CALLBACK * CallBackDevUpGrade)(long lLoginID, int iPercent, int UpdateState, unsigned long dwUser);

//���õ������״̬�ص�
typedef void (CALLBACK * CallBackDevPutFile)(long lLoginID, int iPercent, int UpdateState, unsigned long dwUser);

//���õ�������״̬�ص�
typedef void (CALLBACK * CallBackDevGetFile)(long lLoginID, int iPercent, int UpdateState, unsigned long dwUser);
extern "C"
{
	//��ʼ��SDK
	VIXHZ_EXPORT bool _VixHz_InitSDK();
	VIXHZ_EXPORT void _VixHz_UnInitSDK();

	//��¼�豸,���ص�½�������½�ǳ�--
	VIXHZ_EXPORT long _VixHz_LoginDevice(char *szIp, int nPort, char* szUserName, char* szPassword, base::string& strOutInfo);
	VIXHZ_EXPORT void _VixHz_Logout(long lLoginID);
	VIXHZ_EXPORT void _VixHz_DevUpGrade(long lLoginID, char* fileName);
	VIXHZ_EXPORT void _VixHz_UnUpGrade(long lLoginID);
	VIXHZ_EXPORT void _VixHz_DevPutFile(long lLoginID, char* fileName, int nType = 1);
	VIXHZ_EXPORT void _VixHz_DevGetFile(long lLoginID, char* fileName, int nType = 1);

	//ʵʱ���ӽӿ�
	VIXHZ_EXPORT long _VixHz_StartRealPlay(long lLoginID, long lChannelNO, int type, HWND hWnd, CallbackFuncRealData func, unsigned long dwUserParm);
	VIXHZ_EXPORT long _VixHz_StopRealPlay(long lLoginID, long lChannelNO);
	VIXHZ_EXPORT void _VixHz_SetMediaCallbackType(long nType = 0);
	VIXHZ_EXPORT void _VixHz_SetSubAlarmInfo(long lLoginID, bool bAlarm = true);

	//�Խ��ӿ� _VixHZ_SendTalkDataEx���ڷ����ѱ������Ƶ����
	VIXHZ_EXPORT long _VixHZ_StartTalk(long lLoginID, base::string talkformat, CallbackFuncTalkData fCallback, unsigned long dwUser);
	VIXHZ_EXPORT bool _VixHZ_StopTalk(long lTalkHandle);
	VIXHZ_EXPORT long _VixHZ_SendTalkData(long lTalkHandle, char* pdata, unsigned long lDataLen) ;
	VIXHZ_EXPORT long _VixHZ_SendTalkDataEx(long lTalkHandle, char* pEncodedData, unsigned long lEncodedDataLen) ;

	//���ýӿ�
	VIXHZ_EXPORT bool _VixHz_GetCommandString(CONFIGTYPE ConfigType,base::string& command);
	VIXHZ_EXPORT bool _VixHz_GetDevConfig(long lLonginID, const base::string& command,base::string&config_output, int nChStart,int nChNum = -1);
	VIXHZ_EXPORT bool _VixHz_SetDevConfig(long lLonginID,const base::string& command, const base::string& config, int nChStart,int nchNum);
	VIXHZ_EXPORT bool _VixHz_MakeKeyFrame(long lLoginID, int nChannelNo, int nStreamType);
	VIXHZ_EXPORT bool _VixHz_SendPtzCtrl(long lLoginID, int nChannelNo, long lConfigtype, Vix_PtzCfgParam nParam, base::string& strinfo, unsigned long lParam1=0);
	
	//�طŽӿ�
	VIXHZ_EXPORT long _VixHz_QueryRecrodFile(base::string queryInfo, void* pRecQueryCallback, unsigned long dwUser);
	VIXHZ_EXPORT long _VixHz_PlaybackByRecordFile(long lLoginID, int nChannelNo, base::string strinfo, void *pDownloadPosCallback,void *pNetDataCallback,unsigned long  dwDataUser );
	VIXHZ_EXPORT long _VixHz_DownLoadByRecordFile(long lLoginID, int nChannelNo, base::string strinfo, char *filename, void *pDownloadPosCallback, unsigned long dwDataUser);
	VIXHZ_EXPORT long _VixHz_PlaybackByTime(long lLoginID, int nChannelNo,long lStartTime, long lEndTime, void *pDownloadPosCallback, void* pNetDataCallback, unsigned long dwDataUser);

	VIXHZ_EXPORT long _VixHz_RecordSlow(long lPlayHandle, long lLoginID);
	VIXHZ_EXPORT long _VixHz_RecordFast(long lPlayHandle, long lLoginID);

	VIXHZ_EXPORT bool _VixHz_PausePlayback(long lPlayHandle, long lLoginID=0, bool bPause = true);
	VIXHZ_EXPORT bool _VixHz_StopPlayback(long lPlayHandle, long lLoginID=0);
	VIXHZ_EXPORT bool _VixHz_StopDownLoad(long lPlayHandle, long lLoginID=0,int nChannelno=0);
	VIXHZ_EXPORT bool _VixHz_SeekPlayBack(long lPlayHandle, unsigned int offsetTime, unsigned int offsetByte,long lLoginID=0, int nChannelNO=0 );

	//͸������
	VIXHZ_EXPORT long _VixHZ_OpenTransport(long lLoginID, CallbackTransData fCallback, unsigned long dwUser);
	VIXHZ_EXPORT bool _VixHZ_StopTransport(long lTransHandle);
	VIXHZ_EXPORT long _VixHZ_SendTransData(long lTransHandle, char* pData, unsigned long lDataLen) ;

	//�豸��ѯ�ӿ�
	VIXHZ_EXPORT bool _VixHz_SearchDevice(base::string& pBuf,int& nNum,unsigned long ulWaitTime) ;        //�豸��ѯ�ӿ�

	//������Ϣ�ص�����----
	VIXHZ_EXPORT void _VixHz_SetMessageCallback(CALLBACK_TYPE type, void* pParam, unsigned long dwDataUser);

	VIXHZ_EXPORT void _VixHz_SynDeviceTime(long lLoginID);

	VIXHZ_EXPORT void _VixHz_SetReconnect(bool bConnect = true);

};

#endif