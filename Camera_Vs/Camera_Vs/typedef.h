#pragma  once

#define VG_MAX_CHANNELNUM	256
#define VG_MAX_DECPRO_LIST_SIZE		100
#define VG_MAX_NAME_LEN				16
#define MAX_PTZTOURNUM  8


typedef unsigned long       DWORD;
typedef int                 BOOL;

//������ö��
enum Ability
{
	VG_ABILITY_DEVICECFG,		//�豸�������������Ƿ�ӵ��
	VG_ABILITY_CAMERA,			//���������
	VG_ABILITY_ENCODE,			//����������
	VG_ABILITY_DECODER
};

//����ö��
enum CONFIG_TYPE
{
	CFG_DEV_INFO =0,				//��¼�豸���ص��豸��Ϣ
	CFG_CHANNEL_NAME,				//ͨ������
	CFG_TALKFORMATLIST,				//�Խ�֧������
	CFG_PTZPRESET_SCHEDULE,			//��̨Ԥ֧��
	CFG_TOUR_SCHEDULE,				//Ѳ��
	CFG_DIGICHAN_TOUR,				//����ͨ����ѵ
	CFG_DISPLAY_SPLITTOUR,			//���ڷָ�
	CFG_CODE_CFG,					//��������
	CFG_ENCODE_MAIN_CFG,			//��������������
	CFG_CODE_SVAC_CFG,				//SVAC����
	CFG_VIDEO_CAPTURE_CFG= 10,		//��Ƶ�ɼ�
	CFG_ADDPRESET_CFG ,				//����Ԥ�õ�
	CFG_DELETEPRESET_CFG,			//ɾ��Ԥ�õ�
	CFG_ADDTOURPRESET_CFG,			//����Ѳ��Ԥ�õ�
	CFG_DEV_DELTOURPRESET_CFG,		//ɾ��Ѳ��Ԥ�õ�
	CFG_DEV_CLEARTOUR_CFG,			//ɾ��Ѳ����·

	CFG_DEV_TALKFDECODE_INFO,		//�����Խ�ʱ��Ҫ�������Ϣ
	CFG_QUERY_RECODR,				//¼���ѯ�ṹ��
	CFG_QUERY_RECODR_RESULT,		//¼���ѯ���
	CFG_RECORD_INFO,				//¼����Ϣ--�򿪣�����¼��
	CFG_DEVSEARCH_RESULT=20,		//�豸��ѯ���

	CFG_VERSION_INFO,
	CFG_NETWORK_INFO,				//��������
	CFG_OSD_INFO,					//OSD��Ϣ����
	CFG_PTZ_PROTOCOL,				//��̨Э��

	CFG_ALARM_ALARMIN,				//��������
	CFG_ALARM_OTHER,				//��������
	//
	CFG_DEV_COMMON,					//�豸����ͨ���ã���Ƶ��ʽ֮�����Ϣ

	CFG_DEV_ABILITY,				//��ʾΪ��ȡ�������������������������
	CFG_SNAP,						//��������������ץͼ

	CFG_RBOOT,						//�����豸
	SDK_DEV_CONFIG_TYPENAMEMAP=732
};

namespace XMLCONFIGURE
{
	//ס����
#define  XML_TAG_CONFIGURE			"CONFIGURE"
	//�豸��Ϣ
#define  XML_TAG_DEVICEINFO			"DEVICEINFO"
	//ͨ����
#define  XML_TAG_CHANNELNAME		"CHANNELNAME"
#define  XML_TAG_CHANNEL			"CHANNEL"
	//�Խ�֧�������б�
#define	 XML_TAG_TALKFORMAT			"TALKFORMATLIST"
	//�Խ���Ϣ
#define  XML_TAG_TALKENCORDINFO		"TALKENCORDINFO"

	//��̨Ԥ�õ�
#define  XML_TAG_CLEARTOUR			"CLEARTOUR"
#define  XML_TAG_PTZCHANNEL			"PTZCHANNEL"
#define  XML_TAG_TOURPRESET			"TOURPRESET"
#define  XML_TAG_PRESETSCHEDULE     "PRESETSCHEDULE"
#define  XML_TAG_PRESETINFO			"PRESETINFO"
#define  XML_TAG_TOURSCHEDULE		"TOURSCHEDULE"
#define  XML_TAG_TOURINFO			"TOURINFO"

#define  XML_TAG_QUERYRECORD_RESULT	"RECORDRESULT"
#define  XML_TAG_RECORDINFO			"RECORDINFO"

#define  XML_TAG_DEVSEARCHRESULT	 "DEVSEARCHRESULT"
#define  XML_TAG_SEARCHDEVICE		 "SEARCHDEVICE"

	//��������ѵ
#define  XML_TAG_DIGICHTOUR			"DIGICHTOUR"
#define  XML_TAG_LOCALCFG			"LOCALCFG"
#define  XML_TAG_DIGILOCALCH		"DIGICHLOCAL"
#define  XML_TAG_DIGIREMOTECH		"DIGICHREMOTE"

	//ϵͳ��Ϣ
#define  XML_TAG_VERSIONINFO		 "VERSIONINFO"
#define  XML_TAG_NETWORK			 "NETWORK"
#define  XML_TAG_CODECFG			 "CODECFG"
#define  XML_TAG_CODEONCHANNEL		 "CODECFGONECHN"
#define  XML_TAG_MAINCODECFG		 "MAINCODECFG"
#define  XML_TAG_SUBCODECFG1		 "SUBCODECFG1"

	//OSD��Ϣ����----------------------------------
#define  XML_TAG_OSDINFO			  "OSDINFO"
	//��̨Э������
#define  XML_TAG_PTZINFO			  "PTZINFO"

	//�����������Э��
#define  XML_TAG_ALARMIN			   "ALARMIN"
#define  XML_TAG_TIMESECT			   "TIMESECT"
#define  XML_TAG_MSGHAND			   "HANDLE"
#define  XML_TAG_ALARM				   "ALARM"
#define  XML_TAG_SELECT				   "RECT"

	//��ȡ��ͨ����Э��--
#define  XML_TAG_COMMON					"DEVCOMMON"
#define  XML_TAG_GENERAL				"GENERAL"

	//������
#define  XML_TAG_ABILITY				"ABILITY"
#define  XML_TAG_DEVABILITYCFG			"DEVCFGABILITY"
#define  XML_TAG_ENCODEABILITY			"ENCODEABILITY"
#define  XML_TAG_MAINIMAGESIZE			"IMAGESIZEMASK"
#define  XML_TAG_SUBIMAGESIZE			"SUBIMAGESIZEMASK"
#define	 XML_TAG_CAMERABILITY			"CAMERABILITY"



	//��Թ���������
#define  XML_ATTR_CHANNNELNO		"channelno"
#define  XML_ATTR_NAME				"name"
#define  XML_ATTR_NUM				"number"
#define  XML_ATTR_SIZE				"size"
#define  XML_ATTR_BENABLE			"benable"
#define  XML_ATTR_DEVIP				"devip"
#define  XML_ATTR_DEVPORT			"devport"
#define  XML_ATTR_USERNAME			"username"		//�û�������
#define  XML_ATTR_PASSWORD			"password"
#define  XML_ATTR_RES				"res"
#define  XML_ATTR_LOGINID			"lLoginid"
#define  XML_ATTR_DEVID				"devid"
#define  XML_ATTR_LEFT				"left"
#define  XML_ATTR_RIGHT				"right"
#define  XML_ATTR_TOP				"top"
#define  XML_ATTR_BOTTOM			"botoom"

	//�豸��Ϣ�ṹ��
#define  XML_ATTR_TOTALCHANNEL		"totalchannel"
#define  XML_ATTR_ALARMCHANNEL		"alarmchannel"
#define  XML_ATTR_ALARMOUTCHANNEL	"alarmoutchannel"
#define  XML_ATTR_DIGICHANNEL		"digichannel"		
#define  XML_ATTR_NEWSEARCHPIC		"searchnewpic"
#define  XML_ATTR_SVAC				"svac"
#define  XML_ATTR_DEVCTYPE			"devtype"

	//����---
#define  XML_ATTR_ENCODETYPE		"encodetype"
#define  XML_ATTR_SAMPLERATE		"samplerate"
#define	 XML_ATTR_SAMPLEBIT			"samplebit"
#define  XML_ATTR_AUDIOBIT			"audiobit"
#define  XML_ATTR_BMOTION			"motion"
#define  XML_ATTR_LEVEL				"level"

	//��̨����--
#define  XML_ATTR_PRESETID			"presetid"
#define  XML_ATTR_SPEED				"speed"
#define  XML_ATTR_DWELLTIME			"idwelltime"
#define	 XML_ATTR_PRESETNAME		"presetname"
#define  XML_ATTR_TOURINDEX			"tourindex"
#define  XML_ATTR_PRESETCOUNT		"presetcnt"

#define  XML_ATTR_REMOTECHCNT		"remotechcount"
#define  XML_ATTR_CHANNELTYPE		"channeltype"
#define  XML_ATTR_MODE				"mode"
#define  XML_ATTR_TOURTIME			"tourtime"
#define  XML_ATTR_NOTTOURINDEX      "notourindex"
#define  XML_ATTR_DECODEPOLICY		"decodepolicy"
#define  XML_ATTR_AVENABLE			"avenable"
#define  XML_ATTR_CFGNAME			"cfgname"

#define  XML_ATTR_STREAMTYPE		"streamtype"
#define  XML_ATTR_CONNECTYPE		"connecttype"
#define  XML_ATTR_PRESETENABLE		"presetenable"
#define  XML_ATTR_COMBINNUM			"combinnum"
#define  XML_ATTR_SPLITMODE			"splitmode"
#define  XML_ATTR_CHMASK			"chmask"
#define  XML_ATTR_SPECIALCH			"specialch"
#define  XML_ATTR_INTERVALTIME		"intervertime"

	//��������
#define  XML_ATTRSPLITTYPE			"splittype"
#define  XML_ATTR_STREAMINDEX		"streamindex"
#define  XML_ATTR_COMRESSION		"compression"
#define  XML_ATTR_H264PROFILE		"h264profile"
#define  XML_ATTR_RESOLUTION		"resolution"
#define  XML_ATTR_BITRATECONTROL	"bitratecontrol"
#define  XML_ATTR_QUALITY			"quality"
#define  XML_ATTR_FPS			    "fps"
#define  XML_ATTR_BITRATE			"bitrate"
#define  XML_ATTR_GOP			    "gop"
#define  XML_ATTR_FREQUENCE			"frequence"
#define	 XML_ATTR_LAUDIOVOLUMN		"laudiovolumn"
#define	 XML_ATTR_RAUDIOVOLUMN		"raudiovolumn"
#define  XML_ATTR_BAUDIOENABLE		"baudioenable"
#define  XML_ATTR_BVIDEOENABLE		"bvideoenable"
#define  XML_ATTR_ENTRYTYPE			"entrytype"
#define  XML_ATTR_ENTRYKEY			"entrykey"
#define  XML_ATTR_ROINK				"roink"
#define  XML_ATTR_QPLEVEL			"qplevel"
#define  XML_ATTR_STMMODE			"stmmode"
#define  XML_ATTR_BLQUALITY			"blquality"
#define  XML_ATTR_EXTTIME			"exttime"
#define  XML_ATTR_EXTINFO			"extinfo"
#define  XML_ATTR_RCMODE			"rcmode"
#define  XML_ATTR_PICQUAL			"picqual"

	//ͼƬ/¼���ѯ
#define  XML_ATTR_BPIC				"bpic"
#define  XML_ATTR_BNEWSEARD			"bnewsearched"
#define  XML_ATTR_QUERYID			"queryid"
#define  XML_ATTR_BEGTIME			"begtime"
#define  XML_ATTR_ENDTIME			"endtime"
#define  XML_ATTR_RECORDTYPE		"recordtype"
#define  XML_ATTR_MAXSIZE    		"maxsize"
#define  XML_ATTR_SOURCE			"source"
#define  XML_ATTR_PROTOCOL          "ProtocolType"
#define  XML_ATTR_STREAM            "StreamType"
#define  XML_ATTR_LENGTH			"length"
#define  XML_ATTR_DRIVENUM			"drivenum"
#define  XML_ATTR_STARTCRUSTER		"startcluster"
#define  XML_ATTR_PARTNO			"partno"
#define  XML_ATTR_HINT				"hint"
#define  XML_ATTR_MAC				"mac"
#define  XML_ATTR_FAC				"fac"

	//��������
#define  XML_ATTR_VERSION			"version"
#define  XML_ATTR_SERIO				"serio"
#define  XML_ATTR_SUBMASK			"submask"
#define  XML_ATTR_GATEWAY			"gateway"
#define  XML_ATTR_TCPPORT			"tcpport"
#define  XML_ATTR_UDPPORT			"udpport"
#define  XML_ATTR_DHCP				"dhcp"

	//OSD����
#define  XML_ATTR_BTIMEOSD			"btimeosd"
#define  XML_ATTR_BNAMEOSD			"bnameosd"
#define  XML_ATTR_NAMELEFT			"nameleft"
#define  XML_ATTR_NAMERIGHT			"nameright"
#define  XML_ATTR_NAMETOP		    "nametop"
#define  XML_ATTR_NAMEBOTTOM		"namebottom"
#define  XML_ATTR_TIMELEFT			"timeleft"
#define  XML_ATTR_TIMERIGHT			"timeright"
#define  XML_ATTR_TIMETOP			"timetop"
#define  XML_ATTR_TIMEBOTTOM		"timebottom"

	//��̨Э������
#define  XML_ATTR_PTZPROTOCOL		"ptzprotocol"
#define  XML_ATTR_DATABIT			 "databit"
#define  XML_ATTR_STOPBIT			 "stopbit"
#define  XML_ATTR_PARITY			 "paritybit"
#define  XML_ATTR_BAURATE			 "baurate"
#define  XML_ATTR_ADDRESS			 "address"

	//��������
#define  XML_ATTR_ALARMTYPE			 "alarmtype"
#define  XML_ATTR_ALARMENABLE		 "alarmenable"
#define  XML_ATTR_ID				  "id"
#define  XML_ATTR_BEGHOUR			  "beghour"
#define  XML_ATTR_BEGMIN			  "begmin"
#define  XML_ATTR_BEGSEC			  "begsec"
#define  XML_ATTR_ENDHOUR			  "endhour"
#define  XML_ATTR_ENDMIN			  "endmin"
#define  XML_ATTR_ENDSEC			  "endsec"
#define  XML_ATTR_BPROMPT			  "bprompt"
#define  XML_ATTR_BMAILE			  "bmail"
#define  XML_ATTR_BALARMOUTPUT		  "balarmoutput"
#define  XML_ATTR_BRECORD			  "brecord"
#define  XML_ATTR_BTOUR				  "btour"
#define  XML_ATTR_BSNAP				  "bsnap"
#define  XML_ATTR_SELECT			  "select"

#define  XML_ATTR_MOTION_NAME			"motionname"
#define  XML_ATTR_MOTION_X				"motionx"
#define  XML_ATTR_MOTION_Y				"motiony"
#define  XML_ATTR_MOTION_WIDTH			"motionwidth"
#define  XML_ATTR_MOTION_HEIGHT			"motionheight"
#define  XML_ATTR_MOTION_ENABLE			"motionenable"
#define  XML_ATTR_MOTION_SENSITY		"motionsensity"

#define  XML_ATTR_DURATION			   "duration"
#define  XML_ATTR_RECLATCH			   "relatch"
#define  XML_ATTR_EVENTLATCH		   "eventlatch"

#define  XML_ATTR_RELALARMOUT			"relalarmout"
#define  XML_ATTR_RECORDCHANNEL			"recordchannel"
#define  XML_ATTR_SNAPCHANNEL			"snapchannel"
#define  XML_ATTR_TOURCHANNEL			"tourchannel"
#define  XML_ATTR_ROW					"row"
#define  XML_ATTR_COL					"col"


#define  XML_ATTR_SUPPORTVIDEOFMT		"suppvideofmt"
#define  XML_ATTR_VIDEOFMT				"videofmt"
#define  XML_ATTR_SUPPORTLANGUAGE		"supplanguage"
#define  XML_ATTR_CURLANGUAGE			"curlanguage"


	//---------------------------------------------------------
#define XML_ATTR_CAMABILITY				"camability"
#define XML_ATTR_EXPOSURE				"exposure"
#define XML_ATTR_SENSPAN				"senspan"
#define XML_ATTR_LIGHTSPAN				"lightspan"
#define XML_ATTR_SHUTTERL				"shutterL"
#define XML_ATTR_SHUTTERH				"shutterH"
#define XML_ATTR_ANTIFLICKER			"antiflicker"
#define XML_ATTR_WHITEBALANCE			"whiteblance"
#define XML_ATTR_CHIPTYPE				"chipType"

#define XML_ATTR_BVERSION				"bversion"				
#define XML_ATTR_BNETWORK				"bNetWork"
#define XML_ATTR_BENCODECFG				"bencodecfg"
#define XML_ATTR_BOSDCFG				"bosdcfg"
#define XML_ATTR_BPTZCFG				"bptzcfg"
#define XML_ATTR_BSVACCFG				"bsvaccfg"
#define XML_ATTR_BVIDEOCAPTURECFG		"bvideocapturecfg"
#define XML_ATTR_BALARMINCFG			"balarmincfg"
#define XML_ATTR_BMOTIONCFG				"bmotioncfg"

	//����������
#define XML_ATTR_ENCODEMASK				 "encodemask"
#define XML_ATTR_STREAMCAP				 "streamcap"
#define XML_ATTR_IMAGESIZEMASK			 "imagesizemask"
#define XML_ATTR_COMPRESSION			 "compression"	

}

typedef struct _Out_DevInfo
{
	int		nTotalchannel;
	int		nAlarmchannel;
	int     nAlarmOutchannel;
	int		nDigichannel;
	int     nDevType;
	bool	bsearchnewpic;
	bool    bsvac;

	_Out_DevInfo()
	{
		nTotalchannel = 0;
		nAlarmchannel = 0;
		nAlarmOutchannel = 0;
		nDigichannel = 0;
		nDevType = 0;
		bsearchnewpic = 0;
		bsvac = 0;
	}
}VG_DevInfo;

//�豸��
typedef struct
{
	int iChannel;
	char strChannelName[32];
}VG_CHANNEL_NAME;
typedef struct
{
	VG_CHANNEL_NAME channel[VG_MAX_CHANNELNUM];
}VG_CHANNELNAME_CFG;

typedef struct 
{
	unsigned char 	ucChannel;					//channel [ͨ��]
	unsigned char 	ucPresetID;					//preset No. [Ԥ�õ��]
	unsigned char	iSpeed;						//preset speed speed 1~15 level [Ԥ�õ��ٶ� �ٶ�1~15�ȼ�]
	unsigned char	iDWellTime;					//preset delay time 1~255 [Ԥ�õ�ͣ��ʱ�� 1~255s]
	char	szPresetName[32];		//preset name [Ԥ�õ�����]
}VG_PRESET_INFO;

typedef struct
{
	unsigned long   dwCount;
	VG_PRESET_INFO	struPreset[256];
}VG_PTZ_PRESET_SCHEDULE;

typedef struct
{
	unsigned short 	iChannel;		//channel, start with 0 [ͨ�� ��0��ʼ]
	unsigned short	iIndex;			//preset or locus index , start with 1 [Ԥ�õ���߹켣�±�� ��1��ʼ]
}VG_PTZ_CHANNEL;

typedef struct  
{
	VG_PTZ_CHANNEL struChannel;
	VG_PRESET_INFO	struPreset;
}VG_PTZ_TOUR_PRESET;


typedef struct
{
	unsigned char 	ucPresetID;					//preset No. [Ԥ�õ��]
	unsigned char	iSpeed;                         //preset speed speed 1~15 level [Ԥ�õ��ٶ� �ٶ�1~15�ȼ�]
	unsigned char	iDWellTime;					//preset delay time 1~255 [Ԥ�õ�ͣ��ʱ�� 1~255s]
}VG_TOUR_PRESET;

typedef struct
{
	unsigned int 	ucChannel;					//channel [ͨ��]
	unsigned char	ucTourIndex;				//tour No. [Ѳ����]
	unsigned char	ucPresetCnt;				//number of presets in one tour [һ��Ѳ�����е�Ԥ�õ��� 0~128]
	unsigned char	uRes[2];                    //reserved [����]
	VG_TOUR_PRESET	preset[32];			//preset No. in tour [Ѳ�����е�Ԥ�õ��]
}VG_TOUR_INFO;

typedef struct
{
	unsigned long   dwCount;
	VG_TOUR_INFO	struTour[MAX_PTZTOURNUM];
}VG_PTZ_TOUR_SCHEDULE;


typedef struct
{
	int     encodeType;//VG_TALK_CODING_TYPE
	int     nBitRate;
	int     nSampleRate;
	int     nSampleBit;
}VG_TALKDECODE_INFO;

//�Խ�����ؽṹ����Ϣ--------
typedef enum
{
	TALK_DEFAULT = 0,
	TALK_PCM = 1,					//PCM
	TALK_G711a,						//G711a
	TALK_AMR,						//AMR
	TALK_G711u,						//G711u
	TALK_G726						//G726
}VG_TALK_CODING_TYPE;

typedef struct  
{
	int                 bPic;               //�Ƿ�ΪͼƬ��ѯ
	int                 bNewSeard;          //�Ƿ�Ϊ�µ�����Э��
	unsigned int        nQueryID;
	unsigned long       lLoginID;           //
	unsigned long		lDevID;             //
	int                 nChannelNo;         //?
	unsigned long       lBegTime;
	unsigned long       lEndTime;
	int                 nRecordType;        //��Ϊ9ʱ��ʾͼƬ�����δ��Э������ʱ������9����ʾͼƬ
	int                 nMaxSize;
	int                 nSource;            //
	char                szDevIP[256];        //�豸IP����������ʱ��Ҫʹ��
	int                 nProtocolType;       //ʹ���ϵ������cig
	int                 nStreamType;
}Vix_QUERY_RECORD;

typedef struct
{
	char			szID[32];       //�豸ID
	unsigned char   source;			// ¼��Դ 0:�豸 1:����
	bool            bPic;           // �Ƿ�ΪͼƬ
	unsigned char   recordType;     // 0 ��ͨ¼�� 1 �ⲿ���� 2 ���� 3 ���� 4 �ֶ� 5 ������ 11 ��ʧ 12 �ڵ�
	unsigned char   res1;			// ������
	int				chn;            // ͨ����
	unsigned char   reserve;
	unsigned char   res[3];			// ������
	unsigned long    	    lstartTime;		// ��ʼʱ��
	unsigned long            lendTime;       // ����ʱ��
	char			name[256];      // ¼����
	unsigned long			length;         // ����
	char            szIp[256];      // �豸IP
	//�����Ǭ�豸--------------------------------------------
	union {
		struct {
			unsigned int    ndriveno;         //disk index
			unsigned int    nstartcluster;    //start cluster index ]
			unsigned int    npartno;		  //partion index
			unsigned int	nhint;
		}a;
		struct{
			char			diskId[32];				//����ID
			unsigned int	planId;					//¼��ƻ�ID
			unsigned int	ssId;					//�洢����ID
			unsigned int	fileHandle;				//�ļ����
		}b;
	}dskInfo;

}Vix_RECORD_INFO;

typedef struct 
{
	char				szDevName[32];
	char				szIP[32];		//IP [IP]
	int					nPort;							//port [�˿�]
	char				szMac[64];		//MAC address [MAC��ַ]
	char				ProdutId[64];
	char				nDevType[24];
	int					nDevFac;
}DevSearchInfo;

typedef struct
{
	char szIp[20];
	char szSubMask[20];
	char szGatWay[20];
	char szMacAddr[32];
	int TCPPort;		//!TCP�����˿�		
	int UDPPort;		//	UDP�˿�
	int  nValid;	//
}VG_NET_CONFIGURE;


typedef struct 
{
	int        iCompressionType;            /*!< ѹ��ģʽ */
	int        iEncodingInterval;            /*!< ѹ����*/
	int        iResolution;            /*!< �ֱ��� ����ö��capture_size_t(DVRAPI.H) */    
	int        iBitRateControl;        /*!< �������� ����ö��capture_brc_t(DVRAPI.H) */    
	int        iQuality;                /*!< �����Ļ��� ����1-6    */    
	int        nFPS;                    /*!< ֡��ֵ��NTSC/PAL������,������ʾ����һ֡*/        
	int        nBitRate;                /*!< 0-4096k,���б���Ҫ�ɿͻ��˱��棬�豸ֻ����ʵ�ʵ�����ֵ�������±ꡣ*/
	int        iGOP;                    /*!< ��������I֮֡��ļ��ʱ�䣬1-100 */
	int        iVideoEnable;            /*!< ������Ƶ����*/
	int        iAudioEnable;            /*!< ������Ƶ����*/
	char       acName[128];
	int        iUseCount;  
	int        iH264Profile;
} VG_VIDEO_ENCODE;

typedef struct
{
	int			     nChannel;	//��ǰͨ��
	VG_VIDEO_ENCODE  mainEncode[VG_MAX_CHANNELNUM];
	VG_VIDEO_ENCODE  SubEncode[VG_MAX_CHANNELNUM];
}VG_CODE_CFG;

typedef struct  
{
	int  nleft;	
	int  ntop;
	int  nright;
	int  nbottom;

}VG_RECT;

typedef struct  
{
	VG_CHANNEL_NAME cfg;	//ͨ����
	VG_RECT  namePose;
	VG_RECT  timepose;
	bool	 bNameEnable;
	bool     btimeEnable;
}OSD_PLASEINFO;

typedef struct  
{
	int nsize;		    //��ͨ����
	int nCurchannel;	//��ǰͨ��
	OSD_PLASEINFO info[VG_MAX_CHANNELNUM];
}VG_OSD_PLASEINFO;


//��������
typedef struct  
{
	bool	bEnable;
	int		iBeginHour;
	int		iBeginMin;
	int		iBeginSec;
	int		iEndHour;
	int		iEndMin;
	int		iEndSec;
}VG_TSECT;

typedef struct 
{
	bool				bPrompt;	//��������ʾ
	bool				bMail;		//���͵����ʼ�
	/*triggered output ports, alarm message triggered output, 1 means trigger this output [�������������ͨ��,�������������,Ϊ1 ��ʾ���������]  */ 
	bool				bAlarmoutput;
	unsigned char		byRelAlarmOut[32];//Ϊ��ֹ0�ضϣ��˴���1��ʾȡ�� 2��ʾѡ��
	unsigned long		dwDuration;		/* alarm duration [��������ʱ��] */

	/*linage to record [����¼��]*/
	bool				bRecord;
	unsigned char		byRecordChannel[32];	//Ϊ��ֹ0�ضϣ��˴���1��ʾȡ�� 2��ʾѡ��
	unsigned long		dwRecLatch;		/*record duration [¼�����ʱ��] */

	/*snapshot channels [ץͼͨ��]*/
	bool				bSnap;
	unsigned char		bySnap[32];	////Ϊ��ֹ0�ضϣ��˴���1��ʾȡ�� 2��ʾѡ��
	/*tour channels [��Ѳͨ��]*/
	bool				bTour;
	unsigned char		byTour[32];	////Ϊ��ֹ0�ضϣ��˴���1��ʾȡ�� 2��ʾѡ��

	unsigned long       dwEventLatch;

	unsigned char		bMessageToNet;	//message upload network enable [��Ϣ�ϴ�������ʹ��]

} VG_MSG_HANDLE;
//��������ṹ��
typedef struct
{
	unsigned int		iChannel;
	unsigned char		byAlarmType;							/*alarm type, 0:always closed;1:always opened [����������,0������,1������]  */
	unsigned char		byAlarmEn;								/*alarm enable [����ʹ��]*/
	VG_TSECT			stSect[7][6];		//NSP
	VG_MSG_HANDLE	struHandle;							/*deal method [����ʽ]  */
} VG_ALARMIN_CFG;

typedef struct  
{
	int				nCurChannel;
	int				nTotalChannel;
	VG_ALARMIN_CFG  alarmInCfg[32];
}VG_ALARMIN_CFG_SCHEDULE;


typedef struct 
{
	int enable;
	char name[32];
	int x;
	int y;
	int width;
	int height;
	int sensity;
}VG_MOTIONAREA;

//ͨ�ñ����ṹ��
typedef struct
{
	unsigned int		iChannel;
	unsigned char		byAlarmEn;								/*alarm enable [����ʹ��]*/
	unsigned int		iRow;									//�ܵ�����
	unsigned int		iCol;									//�ܵ�����
	unsigned char       bySelect[32][32];						//�����32*32
	VG_TSECT			stSect[7][6];		//NSP
	VG_MSG_HANDLE	struHandle;							/*deal method [����ʽ]  */
} VG_ALARMNORMAL_CFG;

typedef struct  
{
	int				nCurChannel;
	int				nTotalChannel;
	int				nAlarmType;			//0 Ϊ���� ,1:�ڵ� 2����ʧ
	VG_ALARMNORMAL_CFG  alarmInCfg[3][32];	//0 Ϊ���� ,1:�ڵ� 2����ʧ
	VG_MOTIONAREA  motionArea[4];//��������
}VG_ALARM_CFG_SCHEDULE;

typedef struct
{
	int	 nChannel;
	char szProtocol[256];
	int  nDataBit;		//data bit 5,6,7,8
	int  nStopBit;		//stop bit 1,2
	int  nParity;		//verify bit 0-no, 1-odd, 2-even [У��λ 0-no, 1-odd, 2-even] 
	int  nBaudRate;	
	int  nAddress;
}PTZ_PROCFG;
typedef struct 
{
	int nChannel;	//��ǰ���õ�ͨ����-1����ʾȫͨ��
	int nTotalChanel;	//�ܵ�ͨ����
	int	 dwDecProListNum;				//Э�����
	char DecProName[VG_MAX_DECPRO_LIST_SIZE][VG_MAX_NAME_LEN];
	PTZ_PROCFG cfg[VG_MAX_CHANNELNUM];
}VG_PTZ_PROCFG;

//�豸���������ж��豸�Ƿ�����
typedef struct
{
	bool  bVersion;
	bool  bNetWorkcfg;
	bool  bEncodecfg;
	bool  bOsdcfg;
	bool  bPtzcfg;
	bool  bSVACcfg;
	bool  bVideocapturecfg;
	bool  bAlarmIncfg;
	bool  bMotioncfg;
}VG_DevAbility;

typedef struct
{
	char szSerio[256];
	char szVersion[256];
}VG_VERSION_INFO;

typedef struct  
{
	unsigned char	ucVideoStandardMask;			//��Ƶ��ʽ���룬��λ��ʾ�豸�ܹ�֧�ֵ���Ƶ��ʽ0 PAL 1 NTSC
	unsigned char	ucEncodeModeMask;				//����ģʽ���룬��λ��ʾ�豸�ܹ�֧�ֵı���ģʽ���ã�VBR��CBR
	unsigned short	usStreamCap;					//��λ��ʾ�豸֧�ֵĶ�ý�幦�ܣ�
	//��һλ��ʾ֧��������
	//�ڶ�λ��ʾ֧�ָ�����
	//����λ��ʾ֧��jpgץͼ��׽ͼ�������ⶨ�壬�ڴ˲�����
	unsigned int	uiImageSizeMask;				//��������������ö�ٰ���capture_size_t 
	unsigned int	uiImageSizeMask_Assi[32];		//������ȡ��ͬ�ı���ʱ�򣬸�����֧�ֵı����ʽ������, 
	//uiImageSizeMask_Assi������ʾ��������CAPTURE_SIZE_D1ʱ��������֧�ֵı����ʽ��
	//uiImageSizeMask_Assi������ʾ��������CAPTURE_SIZE_HD1ʱ��������֧�ֵı����ʽ������
	unsigned char	ucSupportPolicy;				//�Ƿ�֧������������0 ��֧��1 ֧��
	unsigned char	ucCompression;					//��λ��ʾ����λ��ʾ�Ƿ�֧�֣���λ��ʾ�Ƿ�֧��svac
	unsigned char   ucRebootType;					//�������ʱ������������HD1��������CIF��Ҫ�����豸

}VG_Encode_CAPS;

typedef struct
{
	bool			BEnable;                //enable [ʹ�ܿ���]
	char			cChName[32];            //name of this configure, for identify [����������,����ʶ��]
	char			cDeviceIP[64];          //ip of device for connection [�������豸��ip��ַ]
	long			iDevicePort;			//port of device for connection [�������豸�Ķ˿ں�]
	char			cDeviceUserName[32];	//user name [�û���]
	char			cDevicePassword[32];	//password [����]
	long			iDevType;               //device type, by enum, protocal type,
	//0:tcp connection, 3:rtsp+udp, 4:vs300 5 sony rtsp,6 sony Э�����,7 ���Ǳ�������[�豸���ͣ���ö�ٱ�ʾ����Э������,0��ʾtcpֱ����3 rtsp+udp 4 vs300. 5 sony rtsp,6 sony Э�����,7 ���Ǳ�������]
	long			iRemoteChannelNo;       //remote channel index, start with 0 [Զ��ͨ����,��0��ʼ����]
	long			iStreamType;            //which bit-stream, 0:main, 1:assist [Ҫ���ӵ���������?0:�������� 1:������]
	long			iRemotePtzPreset;		//remote preset [Զ��Ԥ�õ�]
	long			iRemotePtzPresetEnable;	//if set preset on connected [�Ƿ�һ�����Ͼ�����Զ��Ԥ�õ�]
	long			iConType;               //�õ�һ������?? 0 tcp 1 udp
	long			reserverd[4];           //reserved [�����ֽ�]
}VG_REMOTE_CH_CFG;

typedef struct
{
	bool			BEnable;			//enable [ʹ�ܿ���]
	long			iDeviceChannelType; //channel type, 0:digital channel, 1:analog channel, default is digital channel, can't switch now [ͨ�����ͣ�0��ʾ����ͨ����1��ʾģ��ͨ����Ĭ��Ϊ����ͨ��,��ʱ�������л�]
	long			iMode;				//0:single connection, 1:multi connection [0 ������ 1 ������]
	unsigned long   uiTourTime;			//multi connection tour time [��������Ѳʱ��]
	unsigned long   uiNotTourCfgIndex;	//channel configure on single connection, position in the tour list [������ʱ�Ĳ��õ�ͨ������,����Ѳ�б��е�λ��]
	long			iDecodePolicy;		//decode plot (-2:most real-time, -1:real-time, 0:default, 1:fluency, 2:most fluency) mayby extend to self definition [�������     (-2, ��ʵʱ -1 ʵʱ 0 Ĭ����� 1 ���� 2,    ������ ) �Ժ������չ���Զ���������ʱʱ��]
	long			iAVEnable;			//0:only decode video, 1:only decode audio, 2:decode audio and video [0,ֻ����Ƶ 1��ֻ����Ƶ ��2 ������Ƶ ]
	long			iReserverd[5];      //reserved [�����ֽ�]
}VG_LOCAL_CH_CFG;
typedef struct
{
	VG_LOCAL_CH_CFG		stLocalChCfg;			//channel configure [ͨ������]
	DWORD				dwRemoteChanCount;		//remote channel number [Զ��ͨ����Ŀ]
	VG_REMOTE_CH_CFG	stRemoteChanCfg[32];	//remote channel config [Զ��ͨ������]
}VG_LOCAL_CH;
typedef struct
{
	DWORD dwSize;
	VG_LOCAL_CH stLocalChan[32];
}VG_DIGI_CH_TOUR_CFG;

//��Ƶ�ɼ���صĽṹ��

typedef struct  
{
	unsigned char ucSupportVideoFmt;	//device supported video standard, bit0:PAL, bit1:NTSC, bit2:SECAM [�豸����֧�ֵ���ʽ �� ��0λ PAL ����1λ NTSC�� ��2λ SECAM]
	unsigned char ucCurVideoFmt;		//device used video standard, 0:PAL, 1:NTSC, 2:SECAM [�豸ʹ�õ���ʽ ��0 PAL ��1 NTSC�� 2 SECAM]
	unsigned int uiSupportLanguage;		//device supported languages [�豸����֧�ֵ����� �� ]
	//bit0:English, bit1:SimpChinese, bit2:TradChinese [��0λ English����1λ SimpChinese�� ��2λ TradChinese��]
	//bit3:Italian, bit4:Spanish, bit5:Japanese, bit6:Russian, bit7:French, bit8:German [��3λ ��Italian��,4 ��Spanish��, 5��Japanese��, 6��Russian��, 7��French��, 8��German�� ]
	unsigned int uiCurLanguage;			//device used languages [�豸ʹ�õ����� ��]
	//0:English, 1:SimpChinese, 2:TradChinese, 3:Italian, 4:Spanish [0 English��1 SimpChinese��2 TradChinese��3��Italian��,4 ��Spanish��,] 
	//5:Japanese, 6:Russian, 7:French, 8:German [5��Japanese��, 6��Russian��, 7��French��, 8��German��] 	

}VG_NET_GENERAL;
typedef  struct
{
	unsigned long dwSize;
	VG_NET_GENERAL stGeneral;
	//RV_SYSTEM_TIME stCurTime;
	//RV_DST_TIME stDst;
}VG_COMM_CFG;


typedef struct{
	unsigned int uiCamAbility;  //��λ������32��Ŀ�� 
	//��0λ ֧��HorReverseˮƽ��ת��1Ϊ֧�ָ���ܣ�0Ϊ��֧�ָ����
	//��1λ ֧����ֱ��תVerReverse��1Ϊ֧�ָ���ܣ�0Ϊ��֧�ָ����
	//��2λ ֧���ع�ģʽ����Exposure��1Ϊ֧�ָ���ܣ�0Ϊ��֧�ָ����
	//��3λ ֧�ָй������AESensitivity��1Ϊ֧�ָ���ܣ�0Ϊ��֧�ָ����
	//��4λ ֧�ֱ��ⲹ��Backlight��1Ϊ֧�ָ���ܣ�0Ϊ��֧�ָ����
	//��5λ ֧�ְ�ƽ��ģʽWhiteBalance��1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָ���ܡ�
	//��6λ ֧����Ӱ����ShadeCorr��1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָ���ܡ�
	//��7λ ֧�ֻ�������BadCorr��1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָ���ܡ�
	//��8λ ֧�ַ���˸Anti-Flicker��1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָ����
	//��9λ ֧��ɫ�����ڣ�1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָù���
	//��10λ֧��YUV�����Χ���ƣ�1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָù���
	//��11λ֧��IR-CUR���ƣ�1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָù���
	//��12λ֧��ȥ����ƣ�1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָù���
	//��13λ֧�ֺڰ�/��ɫ/�Զ�ת����1Ϊ֧�ָù��ܣ�0Ϊ��֧�ָù���
	//��14λ֧�ֹ���������
	//��15λ DRC ��̬ 
	//��16λ��֡�ɼ�

	unsigned int uiExposure;//�ع�ģʽ
	unsigned int uiSenSpan; //�й�ȷ�Χ���ֵ ��ֵ255�����ʶ��ΧΪ0~255
	unsigned int uiBLightSpan;//���ⲹ��֧������Backlight,��ֵ15����Χ0~15
	unsigned int uiShutterL;//�ֶ��ع� ��ֵΪ6000��֧����С�ع�ʱ��Ϊ1/6000��
	unsigned int uiShutterH; //�ֶ��ع⣬��ֵΪ50��֧����С�ع�ʱ��Ϊ1/50��
	unsigned int uiAntiFlicker;	//���֧�ַ���˸֧��ģʽ��������Ч����λ����
	//��0λ �Ƿ�֧��50Hz indoorģʽ
	//��1λ �Ƿ�֧��50Hz outdoorģʽ
	//��2λ �Ƿ�֧��50Hz autoģʽ
	//��3λ �Ƿ�֧��60Hz indoorģʽ
	//��4λ �Ƿ�֧��60Hz outdoorģʽ
	//��5λ �Ƿ�֧��60Hz autoģʽ
	unsigned int uiWhiteBlance; //���֧�ְ�ƽ��ģʽ��������Ч����λ��ʾ��ƽ��֧�ֵ�ģʽ
	//ÿһλ��ӦWHITE_BALANCE_MODEö���е���Ӧλ������0xc0��ʾ֧��ɫ��4650k��ɫ��6500k����ģʽ

	unsigned int uiChipType;	//��ͬ
	unsigned int uiRes2;//����

}VG_VIDEOIN_CAPS;