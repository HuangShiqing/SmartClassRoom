#pragma  once

#define VG_MAX_CHANNELNUM	256
#define VG_MAX_DECPRO_LIST_SIZE		100
#define VG_MAX_NAME_LEN				16
#define MAX_PTZTOURNUM  8


typedef unsigned long       DWORD;
typedef int                 BOOL;

//能力级枚举
enum Ability
{
	VG_ABILITY_DEVICECFG,		//设备能力集，包含是否拥有
	VG_ABILITY_CAMERA,			//相机能力集
	VG_ABILITY_ENCODE,			//编码能力集
	VG_ABILITY_DECODER
};

//配置枚举
enum CONFIG_TYPE
{
	CFG_DEV_INFO =0,				//登录设备返回的设备信息
	CFG_CHANNEL_NAME,				//通道名称
	CFG_TALKFORMATLIST,				//对讲支持类型
	CFG_PTZPRESET_SCHEDULE,			//云台预支点
	CFG_TOUR_SCHEDULE,				//巡航
	CFG_DIGICHAN_TOUR,				//数字通道轮训
	CFG_DISPLAY_SPLITTOUR,			//窗口分割
	CFG_CODE_CFG,					//编码配置
	CFG_ENCODE_MAIN_CFG,			//编码主码流配置
	CFG_CODE_SVAC_CFG,				//SVAC配置
	CFG_VIDEO_CAPTURE_CFG= 10,		//视频采集
	CFG_ADDPRESET_CFG ,				//增加预置点
	CFG_DELETEPRESET_CFG,			//删除预置点
	CFG_ADDTOURPRESET_CFG,			//增加巡航预置点
	CFG_DEV_DELTOURPRESET_CFG,		//删除巡航预置点
	CFG_DEV_CLEARTOUR_CFG,			//删除巡航线路

	CFG_DEV_TALKFDECODE_INFO,		//启动对讲时需要传入的信息
	CFG_QUERY_RECODR,				//录像查询结构体
	CFG_QUERY_RECODR_RESULT,		//录像查询结果
	CFG_RECORD_INFO,				//录像信息--打开，下载录像
	CFG_DEVSEARCH_RESULT=20,		//设备查询结果

	CFG_VERSION_INFO,
	CFG_NETWORK_INFO,				//网络配置
	CFG_OSD_INFO,					//OSD信息叠加
	CFG_PTZ_PROTOCOL,				//云台协议

	CFG_ALARM_ALARMIN,				//报警输入
	CFG_ALARM_OTHER,				//其他报警
	//
	CFG_DEV_COMMON,					//设备的普通配置，视频制式之类的信息

	CFG_DEV_ABILITY,				//表示为获取能力集，需用子命令继续解析
	CFG_SNAP,						//动检区域设置需抓图

	CFG_RBOOT,						//重启设备
	SDK_DEV_CONFIG_TYPENAMEMAP=732
};

namespace XMLCONFIGURE
{
	//住配置
#define  XML_TAG_CONFIGURE			"CONFIGURE"
	//设备信息
#define  XML_TAG_DEVICEINFO			"DEVICEINFO"
	//通道名
#define  XML_TAG_CHANNELNAME		"CHANNELNAME"
#define  XML_TAG_CHANNEL			"CHANNEL"
	//对讲支持类型列表
#define	 XML_TAG_TALKFORMAT			"TALKFORMATLIST"
	//对讲信息
#define  XML_TAG_TALKENCORDINFO		"TALKENCORDINFO"

	//云台预置点
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

	//解码器轮训
#define  XML_TAG_DIGICHTOUR			"DIGICHTOUR"
#define  XML_TAG_LOCALCFG			"LOCALCFG"
#define  XML_TAG_DIGILOCALCH		"DIGICHLOCAL"
#define  XML_TAG_DIGIREMOTECH		"DIGICHREMOTE"

	//系统信息
#define  XML_TAG_VERSIONINFO		 "VERSIONINFO"
#define  XML_TAG_NETWORK			 "NETWORK"
#define  XML_TAG_CODECFG			 "CODECFG"
#define  XML_TAG_CODEONCHANNEL		 "CODECFGONECHN"
#define  XML_TAG_MAINCODECFG		 "MAINCODECFG"
#define  XML_TAG_SUBCODECFG1		 "SUBCODECFG1"

	//OSD信息叠加----------------------------------
#define  XML_TAG_OSDINFO			  "OSDINFO"
	//云台协议配置
#define  XML_TAG_PTZINFO			  "PTZINFO"

	//报警相关配置协议
#define  XML_TAG_ALARMIN			   "ALARMIN"
#define  XML_TAG_TIMESECT			   "TIMESECT"
#define  XML_TAG_MSGHAND			   "HANDLE"
#define  XML_TAG_ALARM				   "ALARM"
#define  XML_TAG_SELECT				   "RECT"

	//获取普通配置协议--
#define  XML_TAG_COMMON					"DEVCOMMON"
#define  XML_TAG_GENERAL				"GENERAL"

	//能力集
#define  XML_TAG_ABILITY				"ABILITY"
#define  XML_TAG_DEVABILITYCFG			"DEVCFGABILITY"
#define  XML_TAG_ENCODEABILITY			"ENCODEABILITY"
#define  XML_TAG_MAINIMAGESIZE			"IMAGESIZEMASK"
#define  XML_TAG_SUBIMAGESIZE			"SUBIMAGESIZEMASK"
#define	 XML_TAG_CAMERABILITY			"CAMERABILITY"



	//相对公共的属性
#define  XML_ATTR_CHANNNELNO		"channelno"
#define  XML_ATTR_NAME				"name"
#define  XML_ATTR_NUM				"number"
#define  XML_ATTR_SIZE				"size"
#define  XML_ATTR_BENABLE			"benable"
#define  XML_ATTR_DEVIP				"devip"
#define  XML_ATTR_DEVPORT			"devport"
#define  XML_ATTR_USERNAME			"username"		//用户名密码
#define  XML_ATTR_PASSWORD			"password"
#define  XML_ATTR_RES				"res"
#define  XML_ATTR_LOGINID			"lLoginid"
#define  XML_ATTR_DEVID				"devid"
#define  XML_ATTR_LEFT				"left"
#define  XML_ATTR_RIGHT				"right"
#define  XML_ATTR_TOP				"top"
#define  XML_ATTR_BOTTOM			"botoom"

	//设备信息结构体
#define  XML_ATTR_TOTALCHANNEL		"totalchannel"
#define  XML_ATTR_ALARMCHANNEL		"alarmchannel"
#define  XML_ATTR_ALARMOUTCHANNEL	"alarmoutchannel"
#define  XML_ATTR_DIGICHANNEL		"digichannel"		
#define  XML_ATTR_NEWSEARCHPIC		"searchnewpic"
#define  XML_ATTR_SVAC				"svac"
#define  XML_ATTR_DEVCTYPE			"devtype"

	//编码---
#define  XML_ATTR_ENCODETYPE		"encodetype"
#define  XML_ATTR_SAMPLERATE		"samplerate"
#define	 XML_ATTR_SAMPLEBIT			"samplebit"
#define  XML_ATTR_AUDIOBIT			"audiobit"
#define  XML_ATTR_BMOTION			"motion"
#define  XML_ATTR_LEVEL				"level"

	//云台控制--
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

	//解码配置
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

	//图片/录像查询
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

	//网络配置
#define  XML_ATTR_VERSION			"version"
#define  XML_ATTR_SERIO				"serio"
#define  XML_ATTR_SUBMASK			"submask"
#define  XML_ATTR_GATEWAY			"gateway"
#define  XML_ATTR_TCPPORT			"tcpport"
#define  XML_ATTR_UDPPORT			"udpport"
#define  XML_ATTR_DHCP				"dhcp"

	//OSD配置
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

	//云台协议配置
#define  XML_ATTR_PTZPROTOCOL		"ptzprotocol"
#define  XML_ATTR_DATABIT			 "databit"
#define  XML_ATTR_STOPBIT			 "stopbit"
#define  XML_ATTR_PARITY			 "paritybit"
#define  XML_ATTR_BAURATE			 "baurate"
#define  XML_ATTR_ADDRESS			 "address"

	//报警配置
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

	//编码能力集
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

//设备名
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
	unsigned char 	ucChannel;					//channel [通道]
	unsigned char 	ucPresetID;					//preset No. [预置点号]
	unsigned char	iSpeed;						//preset speed speed 1~15 level [预置点速度 速度1~15等级]
	unsigned char	iDWellTime;					//preset delay time 1~255 [预置点停留时间 1~255s]
	char	szPresetName[32];		//preset name [预置点名称]
}VG_PRESET_INFO;

typedef struct
{
	unsigned long   dwCount;
	VG_PRESET_INFO	struPreset[256];
}VG_PTZ_PRESET_SCHEDULE;

typedef struct
{
	unsigned short 	iChannel;		//channel, start with 0 [通道 从0开始]
	unsigned short	iIndex;			//preset or locus index , start with 1 [预置点或者轨迹下标号 从1开始]
}VG_PTZ_CHANNEL;

typedef struct  
{
	VG_PTZ_CHANNEL struChannel;
	VG_PRESET_INFO	struPreset;
}VG_PTZ_TOUR_PRESET;


typedef struct
{
	unsigned char 	ucPresetID;					//preset No. [预置点号]
	unsigned char	iSpeed;                         //preset speed speed 1~15 level [预置点速度 速度1~15等级]
	unsigned char	iDWellTime;					//preset delay time 1~255 [预置点停留时间 1~255s]
}VG_TOUR_PRESET;

typedef struct
{
	unsigned int 	ucChannel;					//channel [通道]
	unsigned char	ucTourIndex;				//tour No. [巡航号]
	unsigned char	ucPresetCnt;				//number of presets in one tour [一个巡航组中的预置点数 0~128]
	unsigned char	uRes[2];                    //reserved [保留]
	VG_TOUR_PRESET	preset[32];			//preset No. in tour [巡航组中的预置点号]
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

//对讲的相关结构体信息--------
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
	int                 bPic;               //是否为图片查询
	int                 bNewSeard;          //是否为新的搜索协议
	unsigned int        nQueryID;
	unsigned long       lLoginID;           //
	unsigned long		lDevID;             //
	int                 nChannelNo;         //?
	unsigned long       lBegTime;
	unsigned long       lEndTime;
	int                 nRecordType;        //当为9时表示图片，如果未老协议搜索时，需用9来表示图片
	int                 nMaxSize;
	int                 nSource;            //
	char                szDevIP[256];        //设备IP，本地搜索时需要使用
	int                 nProtocolType;       //使用老的信令还是cig
	int                 nStreamType;
}Vix_QUERY_RECORD;

typedef struct
{
	char			szID[32];       //设备ID
	unsigned char   source;			// 录像源 0:设备 1:本地
	bool            bPic;           // 是否为图片
	unsigned char   recordType;     // 0 普通录像 1 外部报警 2 动检 3 卡号 4 手动 5 子码流 11 丢失 12 遮挡
	unsigned char   res1;			// 保留字
	int				chn;            // 通道号
	unsigned char   reserve;
	unsigned char   res[3];			// 保留字
	unsigned long    	    lstartTime;		// 开始时间
	unsigned long            lendTime;       // 结束时间
	char			name[256];      // 录像名
	unsigned long			length;         // 长度
	char            szIp[256];      // 设备IP
	//针对威乾设备--------------------------------------------
	union {
		struct {
			unsigned int    ndriveno;         //disk index
			unsigned int    nstartcluster;    //start cluster index ]
			unsigned int    npartno;		  //partion index
			unsigned int	nhint;
		}a;
		struct{
			char			diskId[32];				//磁盘ID
			unsigned int	planId;					//录像计划ID
			unsigned int	ssId;					//存储服务ID
			unsigned int	fileHandle;				//文件句柄
		}b;
	}dskInfo;

}Vix_RECORD_INFO;

typedef struct 
{
	char				szDevName[32];
	char				szIP[32];		//IP [IP]
	int					nPort;							//port [端口]
	char				szMac[64];		//MAC address [MAC地址]
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
	int TCPPort;		//!TCP侦听端口		
	int UDPPort;		//	UDP端口
	int  nValid;	//
}VG_NET_CONFIGURE;


typedef struct 
{
	int        iCompressionType;            /*!< 压缩模式 */
	int        iEncodingInterval;            /*!< 压缩率*/
	int        iResolution;            /*!< 分辨率 参照枚举capture_size_t(DVRAPI.H) */    
	int        iBitRateControl;        /*!< 码流控制 参照枚举capture_brc_t(DVRAPI.H) */    
	int        iQuality;                /*!< 码流的画质 档次1-6    */    
	int        nFPS;                    /*!< 帧率值，NTSC/PAL不区分,负数表示多秒一帧*/        
	int        nBitRate;                /*!< 0-4096k,该列表主要由客户端保存，设备只接收实际的码流值而不是下标。*/
	int        iGOP;                    /*!< 描述两个I帧之间的间隔时间，1-100 */
	int        iVideoEnable;            /*!< 开启视频编码*/
	int        iAudioEnable;            /*!< 开启音频编码*/
	char       acName[128];
	int        iUseCount;  
	int        iH264Profile;
} VG_VIDEO_ENCODE;

typedef struct
{
	int			     nChannel;	//当前通道
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
	VG_CHANNEL_NAME cfg;	//通道名
	VG_RECT  namePose;
	VG_RECT  timepose;
	bool	 bNameEnable;
	bool     btimeEnable;
}OSD_PLASEINFO;

typedef struct  
{
	int nsize;		    //总通道数
	int nCurchannel;	//当前通道
	OSD_PLASEINFO info[VG_MAX_CHANNELNUM];
}VG_OSD_PLASEINFO;


//报警输入
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
	bool				bPrompt;	//蜂鸣器提示
	bool				bMail;		//发送电子邮件
	/*triggered output ports, alarm message triggered output, 1 means trigger this output [报警触发的输出通道,报警触发的输出,为1 表示触发该输出]  */ 
	bool				bAlarmoutput;
	unsigned char		byRelAlarmOut[32];//为防止0截断，此处以1表示取消 2表示选中
	unsigned long		dwDuration;		/* alarm duration [报警持续时间] */

	/*linage to record [联动录象]*/
	bool				bRecord;
	unsigned char		byRecordChannel[32];	//为防止0截断，此处以1表示取消 2表示选中
	unsigned long		dwRecLatch;		/*record duration [录象持续时间] */

	/*snapshot channels [抓图通道]*/
	bool				bSnap;
	unsigned char		bySnap[32];	////为防止0截断，此处以1表示取消 2表示选中
	/*tour channels [轮巡通道]*/
	bool				bTour;
	unsigned char		byTour[32];	////为防止0截断，此处以1表示取消 2表示选中

	unsigned long       dwEventLatch;

	unsigned char		bMessageToNet;	//message upload network enable [消息上传给网络使能]

} VG_MSG_HANDLE;
//报警输入结构体
typedef struct
{
	unsigned int		iChannel;
	unsigned char		byAlarmType;							/*alarm type, 0:always closed;1:always opened [报警器类型,0：常闭,1：常开]  */
	unsigned char		byAlarmEn;								/*alarm enable [报警使能]*/
	VG_TSECT			stSect[7][6];		//NSP
	VG_MSG_HANDLE	struHandle;							/*deal method [处理方式]  */
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

//通用报警结构体
typedef struct
{
	unsigned int		iChannel;
	unsigned char		byAlarmEn;								/*alarm enable [报警使能]*/
	unsigned int		iRow;									//总的行数
	unsigned int		iCol;									//总的列数
	unsigned char       bySelect[32][32];						//最多是32*32
	VG_TSECT			stSect[7][6];		//NSP
	VG_MSG_HANDLE	struHandle;							/*deal method [处理方式]  */
} VG_ALARMNORMAL_CFG;

typedef struct  
{
	int				nCurChannel;
	int				nTotalChannel;
	int				nAlarmType;			//0 为动检 ,1:遮挡 2：丢失
	VG_ALARMNORMAL_CFG  alarmInCfg[3][32];	//0 为动检 ,1:遮挡 2：丢失
	VG_MOTIONAREA  motionArea[4];//动检区域
}VG_ALARM_CFG_SCHEDULE;

typedef struct
{
	int	 nChannel;
	char szProtocol[256];
	int  nDataBit;		//data bit 5,6,7,8
	int  nStopBit;		//stop bit 1,2
	int  nParity;		//verify bit 0-no, 1-odd, 2-even [校验位 0-no, 1-odd, 2-even] 
	int  nBaudRate;	
	int  nAddress;
}PTZ_PROCFG;
typedef struct 
{
	int nChannel;	//当前设置的通道，-1：表示全通道
	int nTotalChanel;	//总的通道数
	int	 dwDecProListNum;				//协议个数
	char DecProName[VG_MAX_DECPRO_LIST_SIZE][VG_MAX_NAME_LEN];
	PTZ_PROCFG cfg[VG_MAX_CHANNELNUM];
}VG_PTZ_PROCFG;

//设备能力集，判断设备是否在线
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
	unsigned char	ucVideoStandardMask;			//视频制式掩码，按位表示设备能够支持的视频制式0 PAL 1 NTSC
	unsigned char	ucEncodeModeMask;				//编码模式掩码，按位表示设备能够支持的编码模式设置，VBR，CBR
	unsigned short	usStreamCap;					//按位表示设备支持的多媒体功能，
	//第一位表示支持主码流
	//第二位表示支持辅码流
	//第三位表示支持jpg抓图，捉图功能另外定义，在此不加入
	unsigned int	uiImageSizeMask;				//主码流编码掩码枚举按照capture_size_t 
	unsigned int	uiImageSizeMask_Assi[32];		//主码流取不同的编码时候，辅码流支持的编码格式，例如, 
	//uiImageSizeMask_Assi【】表示主码流是CAPTURE_SIZE_D1时，辅码流支持的编码格式，
	//uiImageSizeMask_Assi【】表示主码流是CAPTURE_SIZE_HD1时，辅码流支持的编码格式。。。
	unsigned char	ucSupportPolicy;				//是否支持特殊编码策略0 不支持1 支持
	unsigned char	ucCompression;					//按位表示，第位表示是否支持，第位表示是否支持svac
	unsigned char   ucRebootType;					//如果等于时，配置主码流HD1，辅码流CIF需要重启设备

}VG_Encode_CAPS;

typedef struct
{
	bool			BEnable;                //enable [使能开关]
	char			cChName[32];            //name of this configure, for identify [本配置名称,便于识别]
	char			cDeviceIP[64];          //ip of device for connection [待连接设备的ip地址]
	long			iDevicePort;			//port of device for connection [待连接设备的端口号]
	char			cDeviceUserName[32];	//user name [用户名]
	char			cDevicePassword[32];	//password [密码]
	long			iDevType;               //device type, by enum, protocal type,
	//0:tcp connection, 3:rtsp+udp, 4:vs300 5 sony rtsp,6 sony 协议接入,7 中星贝尔接入[设备类型，按枚举表示，即协议类型,0表示tcp直连，3 rtsp+udp 4 vs300. 5 sony rtsp,6 sony 协议接入,7 中星贝尔接入]
	long			iRemoteChannelNo;       //remote channel index, start with 0 [远程通道号,从0开始算起]
	long			iStreamType;            //which bit-stream, 0:main, 1:assist [要连接的码流类行?0:主码流， 1:辅码流]
	long			iRemotePtzPreset;		//remote preset [远程预置点]
	long			iRemotePtzPresetEnable;	//if set preset on connected [是否一连接上就设置远程预置点]
	long			iConType;               //用掉一个保留?? 0 tcp 1 udp
	long			reserverd[4];           //reserved [保留字节]
}VG_REMOTE_CH_CFG;

typedef struct
{
	bool			BEnable;			//enable [使能开关]
	long			iDeviceChannelType; //channel type, 0:digital channel, 1:analog channel, default is digital channel, can't switch now [通道类型，0表示数字通道，1表示模拟通道，默认为数字通道,暂时不可以切换]
	long			iMode;				//0:single connection, 1:multi connection [0 单连接 1 多连接]
	unsigned long   uiTourTime;			//multi connection tour time [多连接轮巡时间]
	unsigned long   uiNotTourCfgIndex;	//channel configure on single connection, position in the tour list [单连接时的采用的通道配置,在轮巡列表中的位置]
	long			iDecodePolicy;		//decode plot (-2:most real-time, -1:real-time, 0:default, 1:fluency, 2:most fluency) mayby extend to self definition [解码策略     (-2, 最实时 -1 实时 0 默认情况 1 流畅 2,    最流畅 ) 以后可能扩展到自定义具体的延时时间]
	long			iAVEnable;			//0:only decode video, 1:only decode audio, 2:decode audio and video [0,只解视频 1，只解音频 ，2 解音视频 ]
	long			iReserverd[5];      //reserved [保留字节]
}VG_LOCAL_CH_CFG;
typedef struct
{
	VG_LOCAL_CH_CFG		stLocalChCfg;			//channel configure [通道配置]
	DWORD				dwRemoteChanCount;		//remote channel number [远程通道数目]
	VG_REMOTE_CH_CFG	stRemoteChanCfg[32];	//remote channel config [远程通道配置]
}VG_LOCAL_CH;
typedef struct
{
	DWORD dwSize;
	VG_LOCAL_CH stLocalChan[32];
}VG_DIGI_CH_TOUR_CFG;

//视频采集相关的结构体

typedef struct  
{
	unsigned char ucSupportVideoFmt;	//device supported video standard, bit0:PAL, bit1:NTSC, bit2:SECAM [设备可以支持的制式 ， 第0位 PAL ，第1位 NTSC， 第2位 SECAM]
	unsigned char ucCurVideoFmt;		//device used video standard, 0:PAL, 1:NTSC, 2:SECAM [设备使用的制式 ，0 PAL ，1 NTSC， 2 SECAM]
	unsigned int uiSupportLanguage;		//device supported languages [设备可以支持的语言 ， ]
	//bit0:English, bit1:SimpChinese, bit2:TradChinese [第0位 English，第1位 SimpChinese， 第2位 TradChinese，]
	//bit3:Italian, bit4:Spanish, bit5:Japanese, bit6:Russian, bit7:French, bit8:German [第3位 “Italian”,4 “Spanish”, 5“Japanese”, 6“Russian”, 7“French”, 8“German” ]
	unsigned int uiCurLanguage;			//device used languages [设备使用的语言 ，]
	//0:English, 1:SimpChinese, 2:TradChinese, 3:Italian, 4:Spanish [0 English，1 SimpChinese，2 TradChinese，3“Italian”,4 “Spanish”,] 
	//5:Japanese, 6:Russian, 7:French, 8:German [5“Japanese”, 6“Russian”, 7“French”, 8“German”] 	

}VG_NET_GENERAL;
typedef  struct
{
	unsigned long dwSize;
	VG_NET_GENERAL stGeneral;
	//RV_SYSTEM_TIME stCurTime;
	//RV_DST_TIME stDst;
}VG_COMM_CFG;


typedef struct{
	unsigned int uiCamAbility;  //按位处理（总32项目） 
	//第0位 支持HorReverse水平翻转，1为支持该项功能，0为不支持该项功能
	//第1位 支持竖直翻转VerReverse，1为支持该项功能，0为不支持该项功能
	//第2位 支持曝光模式设置Exposure，1为支持该项功能，0为不支持该项功能
	//第3位 支持感光度设置AESensitivity，1为支持该项功能，0为不支持该项功能
	//第4位 支持背光补偿Backlight，1为支持该项功能，0为不支持该项功能
	//第5位 支持白平衡模式WhiteBalance，1为支持该功能，0为不支持该项功能。
	//第6位 支持阴影修正ShadeCorr，1为支持该功能，0为不支持该项功能。
	//第7位 支持坏点修正BadCorr，1为支持该功能，0为不支持该项功能。
	//第8位 支持防闪烁Anti-Flicker，1为支持该功能，0为不支持该项功能
	//第9位 支持色调调节，1为支持该功能，0为不支持该功能
	//第10位支持YUV输出范围控制，1为支持该功能，0为不支持该功能
	//第11位支持IR-CUR控制，1为支持该功能，0为不支持该功能
	//第12位支持去噪控制，1为支持该功能，0为不支持该功能
	//第13位支持黑白/彩色/自动转换，1为支持该功能，0为不支持该功能
	//第14位支持光敏电阻检查
	//第15位 DRC 宽动态 
	//第16位多帧采集

	unsigned int uiExposure;//曝光模式
	unsigned int uiSenSpan; //感光度范围最大值 如值255，则标识范围为0~255
	unsigned int uiBLightSpan;//背光补偿支持上限Backlight,如值15，则范围0~15
	unsigned int uiShutterL;//手动曝光 若值为6000则支持最小曝光时间为1/6000秒
	unsigned int uiShutterH; //手动曝光，若值为50则支持最小曝光时间为1/50秒
	unsigned int uiAntiFlicker;	//如果支持防闪烁支持模式，此项有效，按位处理
	//第0位 是否支持50Hz indoor模式
	//第1位 是否支持50Hz outdoor模式
	//第2位 是否支持50Hz auto模式
	//第3位 是否支持60Hz indoor模式
	//第4位 是否支持60Hz outdoor模式
	//第5位 是否支持60Hz auto模式
	unsigned int uiWhiteBlance; //如果支持白平衡模式，此项有效，按位表示白平衡支持的模式
	//每一位对应WHITE_BALANCE_MODE枚举中的相应位，比如0xc0表示支持色温4650k和色温6500k两种模式

	unsigned int uiChipType;	//不同
	unsigned int uiRes2;//保留

}VG_VIDEOIN_CAPS;