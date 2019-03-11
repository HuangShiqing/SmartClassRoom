#ifndef VIXHZ_DEF_H
#define VIXHZ_DEF_H

#if defined(WIN32)
// For FILETIME in FromFileTime, until it moves to a new converter class.
// See TODO(iyengar) below.
#include <windows.h>
#include <string>
#define CALLBACK __stdcall

#ifdef VIXHZ
# define VIXHZ_EXPORT __declspec(dllexport)
#else
# define VIXHZ_EXPORT __declspec(dllimport)
#endif

#else
#define CALLBACK
#define HWND void*

#ifdef VIXHZ
# define VIXHZ_EXPORT __attribute__((visibility("default")))
#else
# define VIXHZ_EXPORT
#endif

#endif

typedef enum _EUPDAGRADE_PROGRESS
{
	EUP_DOWNLOADING = 1,
	EUP_UPGRADING,
	EUP_FINISHED,
}EUPDAGRADE_PROGRESS;

typedef enum EERROR
{
	ERR_NO_ERROR = 0,
	ERR_ERROR_EX = -20000,//����Ϣ�ص���ʱ��param1�����ERR_ERROR_EX,��param2��ʾ�����ǰ�˷��ص���Ϣ�������
	ERR_ERROR = -10000,
	ERR_TIMEOUT,			// ��ʱ
	ERR_NOACTIVE_TIME_OUT,	// ��ʱ��û��ЧӦ
	ERR_NET_CONNECT,		// �������ӳ���
	ERR_NOT_LOGIN,			// û�е�¼
	ERR_RTSP_SETUP,			// RTSP���ӣ�Setup����
	ERR_RTSP_PLAY,			// RTSP���ӣ�Play����
	ERR_NO_SUPPORT,			// ��֧��
	ERR_CREATE_FILE_ERROR,	// �����ļ�ʧ��
	ERR_USER_LOGGED,		// �Ѿ���¼
	ERR_IN_TALKING = -9990,			// �豸�Ѿ��ڶԽ�
	ERR_NET_ERROR,			// �����쳣
	ERR_USER_ERROR,			// �û������벻ƥ��
	ERR_OPEN_FILE,			// ���ļ�ʧ��
	ERR_USER_CANCEL,		// �û�ȡ��
	ERR_REPEAT_OPT,			// �ظ��������Ƚ�����������û�н������ֿ�ʼ��һ��
	ERR_FILE_LEN_ZERO,	    // �ļ�Ϊ���ļ�
	ERR_NO_THIS_USER,       //���û�������
	ERR_BEYOND_CONNECT_NUM, //�������豸���õ�������
	ERR_BLACKLIST_BAN,      //���ڰ�������ֹ
	ERR_USER_MANUAL_BAN,        //ip���ֶ�����
	ERR_USER_LOAKED,        //�û�������
}EERROR;

enum DEVC_CLASS
{
	DEVC_NOTHING = 0X0,
	DEVC_DVR,              //һ��DVR
	DEVC_IPC,              //IPC
	DEVC_DECODE,           //������
	DEVC_MIX,              //���DVR
	DEVC_NVR				//NVR
};

enum CALLBACK_TYPE
{
	VIXHZ_CALLBACK_ALARM_INFO,        		//������Ϣ
	VIXHZ_CALLBACK_UPDATE_DEVC,           	//�����豸��Ϣ
	VIXHZ_CALLBACK_CENTER_CONTROL,        	//
	VIXHZ_CALLBACK_DEVC_DISCONNECT,        //�豸����
	VIXHZ_CALLBACK_MOBILE_DVR_INFO,        //�ƶ�DVR��Ϣ
	VIXHZ_CALLBACK_MEET_DATA,             	//����
	VIXHZ_CALLBACK_TALKING_DATA,           //�����Խ�
	VIXHZ_CALLBACK_MEDIA_DATA,
	VIXHZ_CALLBACK_MEDIA_PLAYBACK_DATA,
	VIXHZ_CALLBACK_PLAYBACK_POS,
	VIXHZ_CALLBACK_VFS_DEVSTATUS,
	VIXHZ_CALLBACK_DEV_EVENT_EX,
    VIXHZ_CALLBACK_DEV_PUT_FILE,           //���õ���
	VIXHZ_CALLBACK_DEV_GET_FILE,           //���õ���
};

//��̨����
enum VIXHZ_VSEnumPtzCommand
{
	VIXHZ_PTZ_INVALIADE=-1,					//��Ч����
	//��̨��������
	VIXHZ_PTZ_UP,							//��
	VIXHZ_PTZ_DOWN,							//��
	VIXHZ_PTZ_LEFT,                         //��
	VIXHZ_PTZ_RIGHT,                        //��
	
	//�䱶�佹������
	VIXHZ_PTZ_ZOOMADD,						//�䱶+        //Camera operation ��ö��˳����ģ���ϵ��������
	VIXHZ_PTZ_ZOOMREDUCE,					//�䱶-
	VIXHZ_PTZ_FOCUSADD,						//�佹+
	VIXHZ_PTZ_FOCUSREDUCE,					//�佹-	
	VIXHZ_PTZ_APERTUREADD,					//��Ȧ+
	VIXHZ_PTZ_APERTUREREDUCE,				//��Ȧ-

	VIXHZ_PTZ_GoPrepoint,					//ת��Ԥ�õ�

	VIXHZ_PTZ_LEFTUP = 32,                  //����
	VIXHZ_PTZ_RIGHTUP,						//����
	VIXHZ_PTZ_LEFTDOWN,                     //����
	VIXHZ_PTZ_RIGHTDOWN,					//����


	VIXHZ_PTZ_StartCruise = 39,				//����Ѳ��
	VIXHZ_PTZ_StopCruise,					//ֹͣѲ��
	VIXHZ_PTZ_LINESCAN_SETLEFT,				//��ɨ������߽�
	VIXHZ_PTZ_LINESCAN_SETRIGHT,			//�����ұ߽�
	VIXHZ_PTZ_LINESCAN_STARTSCAN,			//��ʼ��ɨ
	VIXHZ_PTZ_LINESCAN_STOPSCAN,			//ֹͣ��ɨ
	VIXHZ_PTZ_TRACE_SETMODESTART,			//Ѳ������ģʽ��ʼ
	VIXHZ_PTZ_TRACE_SETMODESTOP,			//����ģʽ����
	VIXHZ_PTZ_TRACE_RUNMODE,				//��ʼ����ģʽ
	VIXHZ_PTZ_TRACE_STOPMODE				//ֹͣ����ģʽ
};

enum EnumAlarmtype
{
	Alarm_Alarm = 0,
	Alarm_Motion,
	Alarm_Shelter,
	Alarm_Lost,
	Alarm_DiskFul,
	Alarm_DiskError,
	Alarm_SoundDetect,
	Alarm_TimeDiskFull,
	Alarm_Disconnect,   //�豸����
	Alarm_Sys = 10
};

//error type code, returned by SDK_GetLastError [�������ʹ��ţ�SDK_GetLastError�����ķ���]
//#define _EC(x)						(0x80000000|x)
#define _EC(x)						(-x)
#define VIXHZ_NOERROR 				0				//no error [û�д���]
#define VIXHZ_ERROR					-1				//unknown error [δ֪����]
#define VIXHZ_SYSTEM_ERROR			_EC(1)			//error in Windows system [Windowsϵͳ����]
#define VIXHZ_NETWORK_ERROR			_EC(2)			//net error, maybe because net timeout [������󣬿�������Ϊ���糬ʱ]
#define VIXHZ_DEV_VER_NOMATCH		_EC(3)			//device protocal not mathched [�豸Э�鲻ƥ��]
#define VIXHZ_INVALID_HANDLE		_EC(4)			//invalid handle [�����Ч]
#define VIXHZ_OPEN_CHANNEL_ERROR	_EC(5)			//fail to open channel [��ͨ��ʧ��]
#define VIXHZ_CLOSE_CHANNEL			_EC(6)			//fail to close channel [�ر�ͨ��ʧ��]
#define VIXHZ_ILLEGAL_PARAM			_EC(7)			//user params not valid [�û��������Ϸ�]
#define VIXHZ_SDK_INIT_ERROR		_EC(8)			//error occur while initializing SDK [SDK��ʼ������]
#define VIXHZ_SDK_UNINIT_ERROR		_EC(9)			//error occur while cleanuping SDK [SDK�������]
#define VIXHZ_RENDER_OPEN_ERROR		_EC(10)			//error occur while applying render resource [����render��Դ����]
#define VIXHZ_DEC_OPEN_ERROR		_EC(11)			//error occur while opening decode library [�򿪽�������]
#define VIXHZ_DEC_CLOSE_ERROR		_EC(12)			//error occur while closing decode library [�رս�������]
#define VIXHZ_MULTIPLAY_NOCHANNEL	_EC(13)			//detect that the channel number is 0 in multi-view previewing [�໭��Ԥ���м�⵽ͨ����Ϊ0]
#define VIXHZ_TALK_INIT_ERROR		_EC(14)			//fail to initialize audio record library [¼�����ʼ��ʧ��]
#define VIXHZ_TALK_NOT_INIT			_EC(15)			//audio record library not inialized [¼����δ����ʼ��]
#define	VIXHZ_TALK_SENDDATA_ERROR	_EC(16)			//error occur while sending audio data [������Ƶ���ݳ���]
#define VIXHZ_REAL_ALREADY_SAVING	_EC(17)			//real-time data is in saving status [ʵʱ�����Ѿ����ڱ���״̬]
#define VIXHZ_NOT_SAVING			_EC(18)			//not saved real-time data [δ����ʵʱ����]
#define VIXHZ_OPEN_FILE_ERROR		_EC(19)			//open file fail [���ļ�����]
#define VIXHZ_PTZ_SET_TIMER_ERROR	_EC(20)			//fail to lauch PTZ control timer [������̨���ƶ�ʱ��ʧ��]
#define VIXHZ_RETURN_DATA_ERROR		_EC(21)			//check returned value unvalid [�Է������ݵ�У�����]
#define VIXHZ_INSUFFICIENT_BUFFER	_EC(22)			//not enough buffer [û���㹻�Ļ���]
#define VIXHZ_NOT_SUPPORTED			_EC(23)			//not support the function in this SDK [��ǰSDKδ֧�ָù���]
#define VIXHZ_NO_RECORD_FOUND		_EC(24)			//can't find out the record [��ѯ����¼��]
#define VIXHZ_NOT_AUTHORIZED		_EC(25)			//don't have operation authority [�޲���Ȩ��]
#define VIXHZ_NOT_NOW				_EC(26)			//can't comit now [��ʱ�޷�ִ��]
#define VIXHZ_NO_TALK_CHANNEL		_EC(27)			//don't find out talk channel [δ���ֶԽ�ͨ��]
#define VIXHZ_NO_AUDIO				_EC(28)			//don't find out audio [δ������Ƶ]
#define VIXHZ_NO_INIT				_EC(29)			//CLientSDK not initialize [CLientSDKδ����ʼ��]
#define VIXHZ_DOWNLOAD_END			_EC(30)			//download over [�����ѽ���]
#define VIXHZ_EMPTY_LIST			_EC(31)			//the result list of query is empty [��ѯ���Ϊ��]
#define VIXHZ_GETCFG_SYSATTR		_EC(32)			//fail position while getting configure : system attributes [��ȡ����ʧ��λ�ã�ϵͳ����]
#define VIXHZ_GETCFG_SERIAL			_EC(33)			//fail position while getting configure : serial number [��ȡ����ʧ��λ�ã����к�]
#define VIXHZ_GETCFG_GENERAL		_EC(34)			//fail position while getting configure : common attributes [��ȡ����ʧ��λ�ã���������]
#define VIXHZ_GETCFG_DSPCAP			_EC(35)			//fail position while getting configure : ability description of DSP [��ȡ����ʧ��λ�ã�DSP��������]
#define VIXHZ_GETCFG_NETCFG			_EC(36)			//fail position while getting configure : network attributes [��ȡ����ʧ��λ�ã���������]
#define VIXHZ_GETCFG_CHANNAME		_EC(37)			//fail position while getting configure : channel name [��ȡ����ʧ��λ�ã�ͨ������]
#define VIXHZ_GETCFG_VIDEO			_EC(38)			//fail position while getting configure : video attributes [��ȡ����ʧ��λ�ã���Ƶ����]
#define VIXHZ_GETCFG_RECORD			_EC(39)			//fail position while getting configure : configure of timer record [��ȡ����ʧ��λ�ã�¼��ʱ����]
#define VIXHZ_GETCFG_PRONAME		_EC(40)			//fail position while getting configure : protocal name of decoder [��ȡ����ʧ��λ�ã�������Э������]
#define VIXHZ_GETCFG_FUNCNAME		_EC(41)			//fail position while getting configure : function name of 232 serial port [��ȡ����ʧ��λ�ã�232���ڹ�������]
#define VIXHZ_GETCFG_485DECODER		_EC(42)			//fail position while getting configure : attributes of decoder [��ȡ����ʧ��λ�ã�����������]
#define VIXHZ_GETCFG_232COM			_EC(43)			//fail position while getting configure : attributes of 232 serial port [��ȡ����ʧ��λ�ã�232��������]
#define VIXHZ_GETCFG_ALARMIN		_EC(44)			//fail position while getting configure : attributes of alarm-in [��ȡ����ʧ��λ�ã��ⲿ������������]
#define VIXHZ_GETCFG_ALARMDET		_EC(45)			//fail position while getting configure : attributes of picture detect [��ȡ����ʧ��λ�ã�ͼ���ⱨ������]
#define VIXHZ_GETCFG_SYSTIME		_EC(46)			//fail position while getting configure : device time [��ȡ����ʧ��λ�ã��豸ʱ��]
#define VIXHZ_GETCFG_PREVIEW		_EC(47)			//fail position while getting configure : params of preview [��ȡ����ʧ��λ�ã�Ԥ������]
#define VIXHZ_GETCFG_AUTOMT			_EC(48)			//fail position while getting configure : configure of auto-mantance [��ȡ����ʧ��λ�ã��Զ�ά������]
#define VIXHZ_GETCFG_VIDEOMTRX		_EC(49)			//fail position while getting configure : configure of video matrix [��ȡ����ʧ��λ�ã���Ƶ��������]
#define VIXHZ_GETCFG_COVER			_EC(50)			//fail position while getting configure : video area shelter [��ȡ����ʧ��λ�ã���Ƶ�����ڵ�]
#define VIXHZ_GETCFG_WATERMAKE		_EC(51)			//fail position while getting configure : configure of watermask [��ȡ����ʧ��λ�ã�ͼ��ˮӡ����]
#define VIXHZ_SETCFG_GENERAL		_EC(55)			//fail position while setting configure : common attributes [��������ʧ��λ�ã���������]
#define VIXHZ_SETCFG_NETCFG			_EC(56)			//fail position while setting configure : network attributes [��������ʧ��λ�ã���������]
#define VIXHZ_SETCFG_CHANNAME		_EC(57)			//fail position while setting configure : channel name [��������ʧ��λ�ã�ͨ������]
#define VIXHZ_SETCFG_VIDEO			_EC(58)			//fail position while setting configure : video attributes [��������ʧ��λ�ã���Ƶ����]
#define VIXHZ_SETCFG_RECORD			_EC(59)			//fail position while setting configure : configure of timer record [��������ʧ��λ�ã�¼��ʱ����]
#define VIXHZ_SETCFG_485DECODER		_EC(60)			//fail position while setting configure : attributes of decoder [��������ʧ��λ�ã�����������]
#define VIXHZ_SETCFG_232COM			_EC(61)			//fail position while setting configure : attributes of 232 serial port [��������ʧ��λ�ã�232��������]
#define VIXHZ_SETCFG_ALARMIN		_EC(62)			//fail position while setting configure : attributes of alarm-in [��������ʧ��λ�ã��ⲿ������������]
#define VIXHZ_SETCFG_ALARMDET		_EC(63)			//fail position while setting configure : attributes of picture detect [��������ʧ��λ�ã�ͼ���ⱨ������]
#define VIXHZ_SETCFG_SYSTIME		_EC(64)			//fail position while setting configure : device time [��������ʧ��λ�ã��豸ʱ��]
#define VIXHZ_SETCFG_PREVIEW		_EC(65)			//fail position while setting configure : preview params [��������ʧ��λ�ã�Ԥ������]
#define VIXHZ_SETCFG_AUTOMT			_EC(66)			//fail position while setting configure : configure of auto-mantance [��������ʧ��λ�ã��Զ�ά������]
#define VIXHZ_SETCFG_VIDEOMTRX		_EC(67)			//fail position while setting configure : configure of video matrix [��������ʧ��λ�ã���Ƶ��������]
#define VIXHZ_SETCFG_COVER			_EC(69)			//fail position while setting configure : video area shelter [��������ʧ��λ�ã���Ƶ�����ڵ�]
#define VIXHZ_SETCFG_WATERMAKE		_EC(60)			//fail position while setting configure : configure of picture watermark [��������ʧ��λ�ã�ͼ��ˮӡ����]
#define VIXHZ_SETCFG_WLAN			_EC(61)			//fail position while setting configure : wireless network information [��������ʧ��λ�ã�����������Ϣ]
#define VIXHZ_SETCFG_WLANDEV		_EC(62)			//fail position while setting configure : select wireless network device [��������ʧ��λ�ã�ѡ�����������豸]
#define VIXHZ_SETCFG_REGISTER		_EC(63)			//fail position while setting configure : configure of auto-register params [��������ʧ��λ�ã�����ע���������]
#define VIXHZ_SETCFG_CAMERA			_EC(64)			//fail position while setting configure : configure of cameral attributes [��������ʧ��λ�ã�����ͷ��������]
#define VIXHZ_SETCFG_INFRARED		_EC(65)			//fail position while setting configure : configure of infrared ray alarm [��������ʧ��λ�ã����ⱨ������]
#define VIXHZ_SETCFG_SOUNDALARM		_EC(66)			//fail position while setting configure : configure of audio alarm [��������ʧ��λ�ã���Ƶ��������]
#define VIXHZ_SETCFG_STORAGE		_EC(67)			//fail position while setting configure : configure of store position [��������ʧ��λ�ã��洢λ������]

#define VIXHZ_AUDIOENCODE_NOTINIT		_EC(70)			//interface of audio code not initialized success [��Ƶ����ӿ�û�гɹ���ʼ��]
#define VIXHZ_DATA_TOOLONGH				_EC(71)			//data too long [���ݹ���]
#define VIXHZ_UNSUPPORTED				_EC(72)			//device don't support this operation [�豸��֧�ָò���]
#define VIXHZ_DEVICE_BUSY				_EC(73)			//resource of device not enough [�豸��Դ����]
#define VIXHZ_SERVER_STARTED			_EC(74)			//server had been lauched [�������Ѿ�����]
#define VIXHZ_SERVER_STOPPED			_EC(75)			//server had not been lauched [��������δ�ɹ�����]

#define VIXHZ_LISTER_INCORRECT_SERIAL	_EC(80)			//inputed serial number is incorrect [�������к�����]
#define VIXHZ_QUERY_DISKINFO_FAILED		_EC(81)			//fail to get disk infomation [��ȡӲ����Ϣʧ��]

#define VIXHZ_LOGIN_ERROR_PASSWORD		_EC(100)		//passwork not correct [���벻��ȷ]
#define VIXHZ_LOGIN_ERROR_USER			_EC(101)		//account not exist [�ʻ�������]
#define VIXHZ_LOGIN_ERROR_TIMEOUT		_EC(102)		//wait to login timeout [�ȴ���¼���س�ʱ]
#define VIXHZ_LOGIN_ERROR_RELOGGIN		_EC(103)		//account had logined [�ʺ��ѵ�¼]
#define VIXHZ_LOGIN_ERROR_LOCKED		_EC(104)		//account had been locked [�ʺ��ѱ�����]
#define VIXHZ_LOGIN_ERROR_BLACKLIST		_EC(105)		//account had been add to black ip list [�ʺ��ѱ���Ϊ������]
#define VIXHZ_LOGIN_ERROR_BUSY			_EC(106)		//resource is not enough, system is busy [��Դ���㣬ϵͳæ]
#define VIXHZ_LOGIN_ERROR_CONNECT		_EC(107)		//fail to connect to host [��������ʧ��"]
#define VIXHZ_LOGIN_ERROR_NETWORK		_EC(108)		//fail to connect to network [��������ʧ��"]

#define VIXHZ_RENDER_SOUND_ON_ERROR		_EC(120)		//Render Library open audio error [Render�����Ƶ����]
#define VIXHZ_RENDER_SOUND_OFF_ERROR	_EC(121)		//Render Library close audio error [Render��ر���Ƶ����]
#define VIXHZ_RENDER_SET_VOLUME_ERROR	_EC(122)		//Render Library control volumn error [Render�������������]
#define VIXHZ_RENDER_ADJUST_ERROR		_EC(123)		//Render Library set picture param error [Render�����û����������]
#define VIXHZ_RENDER_PAUSE_ERROR		_EC(124)		//Render Library pause error [Render����ͣ���ų���]
#define VIXHZ_RENDER_SNAP_ERROR			_EC(125)		//Render Library snapshot error [Render��ץͼ����]
#define VIXHZ_RENDER_STEP_ERROR			_EC(126)		//Render Library step error [Render�ⲽ������]
#define VIXHZ_RENDER_FRAMERATE_ERROR	_EC(127)		//Render Library set frame rate error [Render������֡�ʳ���]

#define VIXHZ_GROUP_EXIST				_EC(140)		//group name is exist already [�����Ѵ���]
#define	VIXHZ_GROUP_NOEXIST				_EC(141)		//group name is not exist [����������]
#define VIXHZ_GROUP_RIGHTOVER			_EC(142)		//authorities of the group exceed range of the authority list [���Ȩ�޳���Ȩ���б�Χ]
#define VIXHZ_GROUP_HAVEUSER			_EC(143)		//can't delete the group because there are users belong to this group [�������û�������ɾ��]
#define VIXHZ_GROUP_RIGHTUSE			_EC(144)		//some authority of the group is using by some user [���ĳ��Ȩ�ޱ��û�ʹ�ã����ܳ���]
#define VIXHZ_GROUP_SAMENAME			_EC(145)		//new group name is duplicate to some exist group name [������ͬ���������ظ�]
#define	VIXHZ_USER_EXIST				_EC(146)		//user exist [�û��Ѵ���]
#define VIXHZ_USER_NOEXIST				_EC(147)		//user not exist [�û�������]
#define VIXHZ_USER_RIGHTOVER			_EC(148)		//the authorities of user excceed to the authorities of group [�û�Ȩ�޳�����Ȩ��]
#define VIXHZ_USER_PWD					_EC(149)		//reserved account, can't be modified [�����ʺţ��������޸�����]
#define VIXHZ_USER_FLASEPWD				_EC(150)		//incorrect password [���벻��ȷ]
#define VIXHZ_USER_NOMATCHING			_EC(151)		//password not matched [���벻ƥ��]

#define VIXHZ_GETCFG_ETHERNET			_EC(300)		//fail position while getting configure : network card configure [��ȡ����ʧ��λ�ã���������]
#define VIXHZ_GETCFG_WLAN				_EC(301)		//fail position while getting configure : wireless card infomation [��ȡ����ʧ��λ�ã�����������Ϣ]
#define VIXHZ_GETCFG_WLANDEV			_EC(302)		//fail position while getting configure : search wireless network device [��ȡ����ʧ��λ�ã��������������豸]
#define VIXHZ_GETCFG_REGISTER			_EC(303)		//fail position while getting configure : configure of auto-register params [��ȡ����ʧ��λ�ã�����ע���������]
#define VIXHZ_GETCFG_CAMERA				_EC(304)		//fail position while getting configure : configure of cameral attributes [��ȡ����ʧ��λ�ã�����ͷ��������]
#define VIXHZ_GETCFG_INFRARED			_EC(305)		//fail position while getting configure : configure of infrared ray alarm [��ȡ����ʧ��λ�ã����ⱨ������]
#define VIXHZ_GETCFG_SOUNDALARM			_EC(306)		//fail position while getting configure : configure of audio alarm [��ȡ����ʧ��λ�ã���Ƶ��������]
#define VIXHZ_GETCFG_STORAGE			_EC(307)		//fail position while getting configure : configure of store position [��ȡ����ʧ��λ�ã��洢λ������]
#define VIXHZ_GETCFG_MAIL				_EC(308)		//fail to get email configure [��ȡ�ʼ�����ʧ��]

#define VIXHZ_CONFIG_DEVBUSY			_EC(999)		//can't set now [��ʱ�޷�����]
#define VIXHZ_CONFIG_DATAILLEGAL		_EC(1000)		//data for configure is invalid [�������ݲ��Ϸ�]

enum CONFIGTYPE
{
	CFG_PTZ_CTRL,				//��̨����
	CFG_GET_PTZ_PRESET,			//Ԥ�õ����
	CFG_MOD_PTZ_PRESET,			
	CFG_GET_PTZ_TOUR,			//��ȡѲ����
	CFG_MOD_PTZ_TOUR,			

	CFG_GET_ALARM,				//������������
	CFG_SET_ALARM,		
	CFG_GET_ALARM_OUT,			//�����������
	CFG_SET_ALARM_OUT,		
	CFG_GET_ALARM_OUT_STATE,	//�������״̬
	CFG_GET_IMAGE,				//ͼ���������
	CFG_SET_IMAGE ,			
	CFG_GET_GENERAL_NET,		//��������
	CFG_SET_GENERAL_NET,		
	CFG_GET_DECODE,				//�����������
	CFG_SET_DECODE,		

	CFG_GET_RECORD_CTRL,		//¼�����
	CFG_SET_RECORD_CTRL,			
	CFG_GET_CHANNEL_TITLE,		//ͨ������
	CFG_SET_CHANNEL_TITLE,			
	CFG_REBOOT,					//Զ������

	CFG_GET_AUTO_MAINTAIN,		//�Զ�ά��
	CFG_SET_AUTO_MAINTAIN,		
	CFG_GET_DEVICE_INFO,		//�豸��Ϣ
	CFG_GET_PTZ_PROTOCOL,		//��̨Э��

	CFG_GET_PTZ,				//��̨����
	CFG_SET_PTZ,			

	CFG_GET_TIME,				//ʱ������
	CFG_SET_TIME,

	CFG_GET_RECORD_ABILITY,					
	CFG_GET_RECORD,				//¼������
	CFG_SET_RECORD,
	CFG_GET_DISKINFO,			//������Ϣ
	CFG_SET_DISK,				//���̹���
	CFG_QUERY_RECORD,			//¼���ѯ
	CFG_GET_RECORD_URL,			//���¼��URL
	CFG_GET_DISK_ARRAY,			//��������
	CFG_SET_DISK_ARRAY,
	CFG_NET_GET_RTSP,			//RTSP����
	CFG_NET_SET_RTSP,
	CFG_GET_ENCODE_ABILITY,		//����������
	CFG_GET_ENCODE,
	CFG_SET_ENCODE,

	CFG_NET_GET_SMTP,			//�ʼ�����
	CFG_NET_SET_SMTP,
	CFG_NET_GET_DDNS,			//DDNS����
	CFG_NET_SET_DDNS,
	CFG_NET_GET_UPNP,			//UPNP����
	CFG_NET_SET_UPNP,
	CFG_NET_GET_PPPOE,			//PPPOE����
	CFG_NET_SET_PPPOE,
	CFG_NET_GET_NTP,			//NTP����
	CFG_NET_SET_NTP,
	CFG_NET_GET_IP_FILTER,		//IP���˲���
	CFG_NET_SET_IP_FILTER,
	CFG_NET_GET_FTP_SERVER,		//FTP Server����
	CFG_NET_SET_FTP_SERVER,
	CFG_NET_GET_FTP_APP,		//FTP App����
	CFG_NET_SET_FTP_APP,

	CFG_GET_OSD_ABILITY,
	CFG_GET_OSD,				//OSD����
	CFG_SET_OSD,
	CFG_GET_LOG,				//��־��ѯ
	CFG_CLEAR_LOG,				//�����־
	CFG_GET_LOG_SET,			//��־����
	CFG_SET_LOG_SET,
	CFG_DEFAULT,				//�ָ�Ĭ��

	CFG_IMAGE_GET_EFFECT,		//effect����
	CFG_IMAGE_SET_ECCECT,
	CFG_IMAGE_GET_LENS,			//��ͷ����
	CFG_IMAGE_SET_LENS,
	CFG_IMAGE_GET_WB,			//��ƽ��
	CFG_IMAGE_SET_WB,
	CFG_IMAGE_GET_CLARITY,		//�����Ȳ�������
	CFG_IMAGE_SET_CLARITY,
	CFG_IMAGE_GET_ICR,			//��ת�ڲ�������
	CFG_IMAGE_SET_ICR,
	CFG_IMAGE_GET_FOCUS,		//�۽�����
	CFG_IMAGE_SET_FOCUS,
	CFG_IMAGE_GET_EXP,			//�ع����
	CFG_IMAGE_SET_EXP,
	CFG_IMAGE_GET_DR,			//��̬��������
	CFG_IMAGE_SET_DR,

	CFG_NET_GET_AUTOREG,		//����ע��
	CFG_NET_SET_AUTOREG,
	CFG_GET_SPLIT,				//����ָ�
	CFG_SET_SPLIT,
	CFG_GET_TOUR,				//��ѯ����
	CFG_SET_TOUR,
	CFG_GET_DEV_TYPENAME_MAP,	//��ȡ����ͨ��֧������
	CFG_GET_VIDEO_URL,			//��ȡ��Ƶurl
	CFG_GET_INTET_VIDEO,		//ƽ̨��������
	CFG_SET_INTET_VIDEO,
	CFG_NET_GET_ONVIF,			//ONVIF����
	CFG_NET_SET_ONVIF,

	CFG_IPD_GET_INFR_WIPER,		//����������ˢ������
	CFG_IPD_SET_INFR_WIPER,
	CFG_IPD_CTR_INFR_WIPE,		//����������ˢ����
	//CFG_IPD_CTR_INFR_WIPE,

	CFG_GET_INTDETECT,			//���߰���
	CFG_SET_INTDETECT,
	CFG_GET_SYSTEM_ABILITY,		//��ȡ�豸������
	CFG_GET_SNAP_ABILITY,		//��ȡץͼ������
	CFG_GET_SNAP,				//ץͼ����
	CFG_SET_SNAP,
	CFG_GET_GENERAL,			//ͨ�ò���
	CFG_SET_GENERAL,
	CFG_GET_PURE_DECODE,		//����������������
	CFG_SET_PURE_DECODE,
	CFG_GET_ADVANCE,			//IPC�߼�����
	CFG_SET_ADVANCE,
	CFG_BADPIXEL_DETECT,		//������
	CFG_GET_DISPLAY,			//���ģʽ
	CFG_SET_DISPLAY, 
	CFG_GET_COMM,				//��������
	CFG_SET_COMM,
	CFG_GET_INTER_VIDEO_LOG,	//��ѯ������־
	CFG_CLEAR_INTER_VIDEO_LOG,	//���������־
	CFG_MANUAL_SHOT,			//�ֶ�ץͼ
	CFG_GET_ROI_ABILITY,		//��ȡROI������
	CFG_GET_ROI,				//ROI����
	CFG_SET_ROI,
	CFG_BOOK_TRANS_DATA,		//����͸������
	CFG_GET_ABTSET,				//�쳣��������
	CFG_SET_ABTSET,
	CFG_GET_WIFI_LIST,			//��ȡWIFI�б�
	CFG_GET_WIFI,
	CFG_SET_WIFI,

	CFG_BOOK_ALARM,				//���ı���
	CFG_CU_ALARM,				//�����ϱ�
	CFG_USER_QUERY_USER_AUTH,	//��ѯ�û�Ȩ��
	CFG_USER_QUERY_USER_GROUP,	//��ѯ�û���
	CFG_USER_ADD_USER_GROUP,	//�����û���
	CFG_USER_MOD_USER_GROUP,	//�޸��û���
	CFG_USER_DEL_USER_GROUP,	//ɾ���û���
	CFG_USER_QUERY_USER,		//��ѯ�û�
	CFG_USER_ADD_USER,			//�����û�
	CFG_USER_MOD_USER,			//�޸��û�
	CFG_USER_DEL_USER,			//ɾ���û�
	CFG_USER_MOD_PWD,			//�޸�����

	CFG_UPGRADE,				//����
	CFG_PUT_FILE,				//�ϴ��ļ�
	CFG_GET_FILE,				//�����ļ�

	CFG_IPD_GET_CAMERA,			//�������������
	CFG_IPD_SET_CAMERA,
	CFG_IPD_GET_ADV,			//�߼���������
	CFG_IPD_SET_ADV,
	CFG_IPD_GET_AUTO_HOME,		//�Զ���λ��������
	CFG_IPD_SET_AUTO_HOME,
	CFG_IPD_GET_BLIND,			//�ڵ���������
	CFG_IPD_SET_BLIND,
	CFG_IPD_SET_POSTION,		//3D��λ����
	CFG_IPD_GET_VIDEO_CAPTURE,	//ͼ�����Ƶ�ɼ���������
	CFG_IPD_SET_VIDEO_CAPTURE,
	CFG_IPD_OPERATION,			//��������������
	CFG_IPD_GET_ABLITY,			//�������Э��������
};

enum Vix_FrameType
{
	VixFT_Unknown,
	VixFT_I,
	VixFT_P,
	VixFT_B,
	VixFT_Audio,
	VixFT_JEPG,
};

typedef struct
{
	long lParam1;
	long lParam2;
	long lParam3;
	bool bStop;
	bool bGet;
}Vix_PtzCfgParam;

namespace base
{
	class VIXHZ_EXPORT string 
	{
	public:
		string();
		~string();
		int   size();
		int   lenth();
		const char* c_str() const;

		string& operator=(const std::string& str);
	private:
		char* _data;
		int _lenth;
	};
}

#endif
