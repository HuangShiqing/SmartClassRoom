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
	ERR_ERROR_EX = -20000,//在消息回调的时候，param1如果是ERR_ERROR_EX,则param2表示具体的前端返回的消息错误代码
	ERR_ERROR = -10000,
	ERR_TIMEOUT,			// 超时
	ERR_NOACTIVE_TIME_OUT,	// 长时间没有效应
	ERR_NET_CONNECT,		// 网络连接出错
	ERR_NOT_LOGIN,			// 没有登录
	ERR_RTSP_SETUP,			// RTSP连接，Setup出错
	ERR_RTSP_PLAY,			// RTSP连接，Play出错
	ERR_NO_SUPPORT,			// 不支持
	ERR_CREATE_FILE_ERROR,	// 创建文件失败
	ERR_USER_LOGGED,		// 已经登录
	ERR_IN_TALKING = -9990,			// 设备已经在对讲
	ERR_NET_ERROR,			// 网络异常
	ERR_USER_ERROR,			// 用户名密码不匹配
	ERR_OPEN_FILE,			// 打开文件失败
	ERR_USER_CANCEL,		// 用户取消
	ERR_REPEAT_OPT,			// 重复操作，比较正在升级还没有结束，又开始了一次
	ERR_FILE_LEN_ZERO,	    // 文件为空文件
	ERR_NO_THIS_USER,       //该用户不存在
	ERR_BEYOND_CONNECT_NUM, //超出了设备设置的连接数
	ERR_BLACKLIST_BAN,      //被黑白名单禁止
	ERR_USER_MANUAL_BAN,        //ip被手动屏蔽
	ERR_USER_LOAKED,        //用户被锁定
}EERROR;

enum DEVC_CLASS
{
	DEVC_NOTHING = 0X0,
	DEVC_DVR,              //一般DVR
	DEVC_IPC,              //IPC
	DEVC_DECODE,           //解码器
	DEVC_MIX,              //混合DVR
	DEVC_NVR				//NVR
};

enum CALLBACK_TYPE
{
	VIXHZ_CALLBACK_ALARM_INFO,        		//报警信息
	VIXHZ_CALLBACK_UPDATE_DEVC,           	//更新设备信息
	VIXHZ_CALLBACK_CENTER_CONTROL,        	//
	VIXHZ_CALLBACK_DEVC_DISCONNECT,        //设备断线
	VIXHZ_CALLBACK_MOBILE_DVR_INFO,        //移动DVR信息
	VIXHZ_CALLBACK_MEET_DATA,             	//会议
	VIXHZ_CALLBACK_TALKING_DATA,           //语音对讲
	VIXHZ_CALLBACK_MEDIA_DATA,
	VIXHZ_CALLBACK_MEDIA_PLAYBACK_DATA,
	VIXHZ_CALLBACK_PLAYBACK_POS,
	VIXHZ_CALLBACK_VFS_DEVSTATUS,
	VIXHZ_CALLBACK_DEV_EVENT_EX,
    VIXHZ_CALLBACK_DEV_PUT_FILE,           //配置导入
	VIXHZ_CALLBACK_DEV_GET_FILE,           //配置导出
};

//云台命令
enum VIXHZ_VSEnumPtzCommand
{
	VIXHZ_PTZ_INVALIADE=-1,					//无效命令
	//云台方向命令
	VIXHZ_PTZ_UP,							//上
	VIXHZ_PTZ_DOWN,							//下
	VIXHZ_PTZ_LEFT,                         //左
	VIXHZ_PTZ_RIGHT,                        //右
	
	//变倍变焦等命令
	VIXHZ_PTZ_ZOOMADD,						//变倍+        //Camera operation 的枚举顺序勿改，关系其他代码
	VIXHZ_PTZ_ZOOMREDUCE,					//变倍-
	VIXHZ_PTZ_FOCUSADD,						//变焦+
	VIXHZ_PTZ_FOCUSREDUCE,					//变焦-	
	VIXHZ_PTZ_APERTUREADD,					//光圈+
	VIXHZ_PTZ_APERTUREREDUCE,				//光圈-

	VIXHZ_PTZ_GoPrepoint,					//转到预置点

	VIXHZ_PTZ_LEFTUP = 32,                  //左上
	VIXHZ_PTZ_RIGHTUP,						//右上
	VIXHZ_PTZ_LEFTDOWN,                     //左下
	VIXHZ_PTZ_RIGHTDOWN,					//右下


	VIXHZ_PTZ_StartCruise = 39,				//启动巡航
	VIXHZ_PTZ_StopCruise,					//停止巡航
	VIXHZ_PTZ_LINESCAN_SETLEFT,				//线扫设置左边界
	VIXHZ_PTZ_LINESCAN_SETRIGHT,			//设置右边界
	VIXHZ_PTZ_LINESCAN_STARTSCAN,			//开始线扫
	VIXHZ_PTZ_LINESCAN_STOPSCAN,			//停止线扫
	VIXHZ_PTZ_TRACE_SETMODESTART,			//巡迹设置模式开始
	VIXHZ_PTZ_TRACE_SETMODESTOP,			//设置模式结束
	VIXHZ_PTZ_TRACE_RUNMODE,				//开始运行模式
	VIXHZ_PTZ_TRACE_STOPMODE				//停止运行模式
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
	Alarm_Disconnect,   //设备断线
	Alarm_Sys = 10
};

//error type code, returned by SDK_GetLastError [错误类型代号，SDK_GetLastError函数的返回]
//#define _EC(x)						(0x80000000|x)
#define _EC(x)						(-x)
#define VIXHZ_NOERROR 				0				//no error [没有错误]
#define VIXHZ_ERROR					-1				//unknown error [未知错误]
#define VIXHZ_SYSTEM_ERROR			_EC(1)			//error in Windows system [Windows系统出错]
#define VIXHZ_NETWORK_ERROR			_EC(2)			//net error, maybe because net timeout [网络错误，可能是因为网络超时]
#define VIXHZ_DEV_VER_NOMATCH		_EC(3)			//device protocal not mathched [设备协议不匹配]
#define VIXHZ_INVALID_HANDLE		_EC(4)			//invalid handle [句柄无效]
#define VIXHZ_OPEN_CHANNEL_ERROR	_EC(5)			//fail to open channel [打开通道失败]
#define VIXHZ_CLOSE_CHANNEL			_EC(6)			//fail to close channel [关闭通道失败]
#define VIXHZ_ILLEGAL_PARAM			_EC(7)			//user params not valid [用户参数不合法]
#define VIXHZ_SDK_INIT_ERROR		_EC(8)			//error occur while initializing SDK [SDK初始化出错]
#define VIXHZ_SDK_UNINIT_ERROR		_EC(9)			//error occur while cleanuping SDK [SDK清理出错]
#define VIXHZ_RENDER_OPEN_ERROR		_EC(10)			//error occur while applying render resource [申请render资源出错]
#define VIXHZ_DEC_OPEN_ERROR		_EC(11)			//error occur while opening decode library [打开解码库出错]
#define VIXHZ_DEC_CLOSE_ERROR		_EC(12)			//error occur while closing decode library [关闭解码库出错]
#define VIXHZ_MULTIPLAY_NOCHANNEL	_EC(13)			//detect that the channel number is 0 in multi-view previewing [多画面预览中检测到通道数为0]
#define VIXHZ_TALK_INIT_ERROR		_EC(14)			//fail to initialize audio record library [录音库初始化失败]
#define VIXHZ_TALK_NOT_INIT			_EC(15)			//audio record library not inialized [录音库未经初始化]
#define	VIXHZ_TALK_SENDDATA_ERROR	_EC(16)			//error occur while sending audio data [发送音频数据出错]
#define VIXHZ_REAL_ALREADY_SAVING	_EC(17)			//real-time data is in saving status [实时数据已经处于保存状态]
#define VIXHZ_NOT_SAVING			_EC(18)			//not saved real-time data [未保存实时数据]
#define VIXHZ_OPEN_FILE_ERROR		_EC(19)			//open file fail [打开文件出错]
#define VIXHZ_PTZ_SET_TIMER_ERROR	_EC(20)			//fail to lauch PTZ control timer [启动云台控制定时器失败]
#define VIXHZ_RETURN_DATA_ERROR		_EC(21)			//check returned value unvalid [对返回数据的校验出错]
#define VIXHZ_INSUFFICIENT_BUFFER	_EC(22)			//not enough buffer [没有足够的缓存]
#define VIXHZ_NOT_SUPPORTED			_EC(23)			//not support the function in this SDK [当前SDK未支持该功能]
#define VIXHZ_NO_RECORD_FOUND		_EC(24)			//can't find out the record [查询不到录象]
#define VIXHZ_NOT_AUTHORIZED		_EC(25)			//don't have operation authority [无操作权限]
#define VIXHZ_NOT_NOW				_EC(26)			//can't comit now [暂时无法执行]
#define VIXHZ_NO_TALK_CHANNEL		_EC(27)			//don't find out talk channel [未发现对讲通道]
#define VIXHZ_NO_AUDIO				_EC(28)			//don't find out audio [未发现音频]
#define VIXHZ_NO_INIT				_EC(29)			//CLientSDK not initialize [CLientSDK未经初始化]
#define VIXHZ_DOWNLOAD_END			_EC(30)			//download over [下载已结束]
#define VIXHZ_EMPTY_LIST			_EC(31)			//the result list of query is empty [查询结果为空]
#define VIXHZ_GETCFG_SYSATTR		_EC(32)			//fail position while getting configure : system attributes [获取配置失败位置：系统属性]
#define VIXHZ_GETCFG_SERIAL			_EC(33)			//fail position while getting configure : serial number [获取配置失败位置：序列号]
#define VIXHZ_GETCFG_GENERAL		_EC(34)			//fail position while getting configure : common attributes [获取配置失败位置：常规属性]
#define VIXHZ_GETCFG_DSPCAP			_EC(35)			//fail position while getting configure : ability description of DSP [获取配置失败位置：DSP能力描述]
#define VIXHZ_GETCFG_NETCFG			_EC(36)			//fail position while getting configure : network attributes [获取配置失败位置：网络属性]
#define VIXHZ_GETCFG_CHANNAME		_EC(37)			//fail position while getting configure : channel name [获取配置失败位置：通道名称]
#define VIXHZ_GETCFG_VIDEO			_EC(38)			//fail position while getting configure : video attributes [获取配置失败位置：视频属性]
#define VIXHZ_GETCFG_RECORD			_EC(39)			//fail position while getting configure : configure of timer record [获取配置失败位置：录象定时配置]
#define VIXHZ_GETCFG_PRONAME		_EC(40)			//fail position while getting configure : protocal name of decoder [获取配置失败位置：解码器协议名称]
#define VIXHZ_GETCFG_FUNCNAME		_EC(41)			//fail position while getting configure : function name of 232 serial port [获取配置失败位置：232串口功能名称]
#define VIXHZ_GETCFG_485DECODER		_EC(42)			//fail position while getting configure : attributes of decoder [获取配置失败位置：解码器属性]
#define VIXHZ_GETCFG_232COM			_EC(43)			//fail position while getting configure : attributes of 232 serial port [获取配置失败位置：232串口属性]
#define VIXHZ_GETCFG_ALARMIN		_EC(44)			//fail position while getting configure : attributes of alarm-in [获取配置失败位置：外部报警输入属性]
#define VIXHZ_GETCFG_ALARMDET		_EC(45)			//fail position while getting configure : attributes of picture detect [获取配置失败位置：图像检测报警属性]
#define VIXHZ_GETCFG_SYSTIME		_EC(46)			//fail position while getting configure : device time [获取配置失败位置：设备时间]
#define VIXHZ_GETCFG_PREVIEW		_EC(47)			//fail position while getting configure : params of preview [获取配置失败位置：预览参数]
#define VIXHZ_GETCFG_AUTOMT			_EC(48)			//fail position while getting configure : configure of auto-mantance [获取配置失败位置：自动维护配置]
#define VIXHZ_GETCFG_VIDEOMTRX		_EC(49)			//fail position while getting configure : configure of video matrix [获取配置失败位置：视频矩阵配置]
#define VIXHZ_GETCFG_COVER			_EC(50)			//fail position while getting configure : video area shelter [获取配置失败位置：视频区域遮挡]
#define VIXHZ_GETCFG_WATERMAKE		_EC(51)			//fail position while getting configure : configure of watermask [获取配置失败位置：图象水印配置]
#define VIXHZ_SETCFG_GENERAL		_EC(55)			//fail position while setting configure : common attributes [设置配置失败位置：常规属性]
#define VIXHZ_SETCFG_NETCFG			_EC(56)			//fail position while setting configure : network attributes [设置配置失败位置：网络属性]
#define VIXHZ_SETCFG_CHANNAME		_EC(57)			//fail position while setting configure : channel name [设置配置失败位置：通道名称]
#define VIXHZ_SETCFG_VIDEO			_EC(58)			//fail position while setting configure : video attributes [设置配置失败位置：视频属性]
#define VIXHZ_SETCFG_RECORD			_EC(59)			//fail position while setting configure : configure of timer record [设置配置失败位置：录象定时配置]
#define VIXHZ_SETCFG_485DECODER		_EC(60)			//fail position while setting configure : attributes of decoder [设置配置失败位置：解码器属性]
#define VIXHZ_SETCFG_232COM			_EC(61)			//fail position while setting configure : attributes of 232 serial port [设置配置失败位置：232串口属性]
#define VIXHZ_SETCFG_ALARMIN		_EC(62)			//fail position while setting configure : attributes of alarm-in [设置配置失败位置：外部报警输入属性]
#define VIXHZ_SETCFG_ALARMDET		_EC(63)			//fail position while setting configure : attributes of picture detect [设置配置失败位置：图像检测报警属性]
#define VIXHZ_SETCFG_SYSTIME		_EC(64)			//fail position while setting configure : device time [设置配置失败位置：设备时间]
#define VIXHZ_SETCFG_PREVIEW		_EC(65)			//fail position while setting configure : preview params [设置配置失败位置：预览参数]
#define VIXHZ_SETCFG_AUTOMT			_EC(66)			//fail position while setting configure : configure of auto-mantance [设置配置失败位置：自动维护配置]
#define VIXHZ_SETCFG_VIDEOMTRX		_EC(67)			//fail position while setting configure : configure of video matrix [设置配置失败位置：视频矩阵配置]
#define VIXHZ_SETCFG_COVER			_EC(69)			//fail position while setting configure : video area shelter [设置配置失败位置：视频区域遮挡]
#define VIXHZ_SETCFG_WATERMAKE		_EC(60)			//fail position while setting configure : configure of picture watermark [设置配置失败位置：图象水印配置]
#define VIXHZ_SETCFG_WLAN			_EC(61)			//fail position while setting configure : wireless network information [设置配置失败位置：无线网络信息]
#define VIXHZ_SETCFG_WLANDEV		_EC(62)			//fail position while setting configure : select wireless network device [设置配置失败位置：选择无线网络设备]
#define VIXHZ_SETCFG_REGISTER		_EC(63)			//fail position while setting configure : configure of auto-register params [设置配置失败位置：主动注册参数配置]
#define VIXHZ_SETCFG_CAMERA			_EC(64)			//fail position while setting configure : configure of cameral attributes [设置配置失败位置：摄像头属性配置]
#define VIXHZ_SETCFG_INFRARED		_EC(65)			//fail position while setting configure : configure of infrared ray alarm [设置配置失败位置：红外报警配置]
#define VIXHZ_SETCFG_SOUNDALARM		_EC(66)			//fail position while setting configure : configure of audio alarm [设置配置失败位置：音频报警配置]
#define VIXHZ_SETCFG_STORAGE		_EC(67)			//fail position while setting configure : configure of store position [设置配置失败位置：存储位置配置]

#define VIXHZ_AUDIOENCODE_NOTINIT		_EC(70)			//interface of audio code not initialized success [音频编码接口没有成功初始化]
#define VIXHZ_DATA_TOOLONGH				_EC(71)			//data too long [数据过长]
#define VIXHZ_UNSUPPORTED				_EC(72)			//device don't support this operation [设备不支持该操作]
#define VIXHZ_DEVICE_BUSY				_EC(73)			//resource of device not enough [设备资源不足]
#define VIXHZ_SERVER_STARTED			_EC(74)			//server had been lauched [服务器已经启动]
#define VIXHZ_SERVER_STOPPED			_EC(75)			//server had not been lauched [服务器尚未成功启动]

#define VIXHZ_LISTER_INCORRECT_SERIAL	_EC(80)			//inputed serial number is incorrect [输入序列号有误]
#define VIXHZ_QUERY_DISKINFO_FAILED		_EC(81)			//fail to get disk infomation [获取硬盘信息失败]

#define VIXHZ_LOGIN_ERROR_PASSWORD		_EC(100)		//passwork not correct [密码不正确]
#define VIXHZ_LOGIN_ERROR_USER			_EC(101)		//account not exist [帐户不存在]
#define VIXHZ_LOGIN_ERROR_TIMEOUT		_EC(102)		//wait to login timeout [等待登录返回超时]
#define VIXHZ_LOGIN_ERROR_RELOGGIN		_EC(103)		//account had logined [帐号已登录]
#define VIXHZ_LOGIN_ERROR_LOCKED		_EC(104)		//account had been locked [帐号已被锁定]
#define VIXHZ_LOGIN_ERROR_BLACKLIST		_EC(105)		//account had been add to black ip list [帐号已被列为黑名单]
#define VIXHZ_LOGIN_ERROR_BUSY			_EC(106)		//resource is not enough, system is busy [资源不足，系统忙]
#define VIXHZ_LOGIN_ERROR_CONNECT		_EC(107)		//fail to connect to host [连接主机失败"]
#define VIXHZ_LOGIN_ERROR_NETWORK		_EC(108)		//fail to connect to network [网络连接失败"]

#define VIXHZ_RENDER_SOUND_ON_ERROR		_EC(120)		//Render Library open audio error [Render库打开音频出错]
#define VIXHZ_RENDER_SOUND_OFF_ERROR	_EC(121)		//Render Library close audio error [Render库关闭音频出错]
#define VIXHZ_RENDER_SET_VOLUME_ERROR	_EC(122)		//Render Library control volumn error [Render库控制音量出错]
#define VIXHZ_RENDER_ADJUST_ERROR		_EC(123)		//Render Library set picture param error [Render库设置画面参数出错]
#define VIXHZ_RENDER_PAUSE_ERROR		_EC(124)		//Render Library pause error [Render库暂停播放出错]
#define VIXHZ_RENDER_SNAP_ERROR			_EC(125)		//Render Library snapshot error [Render库抓图出错]
#define VIXHZ_RENDER_STEP_ERROR			_EC(126)		//Render Library step error [Render库步进出错]
#define VIXHZ_RENDER_FRAMERATE_ERROR	_EC(127)		//Render Library set frame rate error [Render库设置帧率出错]

#define VIXHZ_GROUP_EXIST				_EC(140)		//group name is exist already [组名已存在]
#define	VIXHZ_GROUP_NOEXIST				_EC(141)		//group name is not exist [组名不存在]
#define VIXHZ_GROUP_RIGHTOVER			_EC(142)		//authorities of the group exceed range of the authority list [组的权限超出权限列表范围]
#define VIXHZ_GROUP_HAVEUSER			_EC(143)		//can't delete the group because there are users belong to this group [组下有用户，不能删除]
#define VIXHZ_GROUP_RIGHTUSE			_EC(144)		//some authority of the group is using by some user [组的某个权限被用户使用，不能出除]
#define VIXHZ_GROUP_SAMENAME			_EC(145)		//new group name is duplicate to some exist group name [新组名同已有组名重复]
#define	VIXHZ_USER_EXIST				_EC(146)		//user exist [用户已存在]
#define VIXHZ_USER_NOEXIST				_EC(147)		//user not exist [用户不存在]
#define VIXHZ_USER_RIGHTOVER			_EC(148)		//the authorities of user excceed to the authorities of group [用户权限超出组权限]
#define VIXHZ_USER_PWD					_EC(149)		//reserved account, can't be modified [保留帐号，不容许修改密码]
#define VIXHZ_USER_FLASEPWD				_EC(150)		//incorrect password [密码不正确]
#define VIXHZ_USER_NOMATCHING			_EC(151)		//password not matched [密码不匹配]

#define VIXHZ_GETCFG_ETHERNET			_EC(300)		//fail position while getting configure : network card configure [获取配置失败位置：网卡配置]
#define VIXHZ_GETCFG_WLAN				_EC(301)		//fail position while getting configure : wireless card infomation [获取配置失败位置：无线网络信息]
#define VIXHZ_GETCFG_WLANDEV			_EC(302)		//fail position while getting configure : search wireless network device [获取配置失败位置：搜索无线网络设备]
#define VIXHZ_GETCFG_REGISTER			_EC(303)		//fail position while getting configure : configure of auto-register params [获取配置失败位置：主动注册参数配置]
#define VIXHZ_GETCFG_CAMERA				_EC(304)		//fail position while getting configure : configure of cameral attributes [获取配置失败位置：摄像头属性配置]
#define VIXHZ_GETCFG_INFRARED			_EC(305)		//fail position while getting configure : configure of infrared ray alarm [获取配置失败位置：红外报警配置]
#define VIXHZ_GETCFG_SOUNDALARM			_EC(306)		//fail position while getting configure : configure of audio alarm [获取配置失败位置：音频报警配置]
#define VIXHZ_GETCFG_STORAGE			_EC(307)		//fail position while getting configure : configure of store position [获取配置失败位置：存储位置配置]
#define VIXHZ_GETCFG_MAIL				_EC(308)		//fail to get email configure [获取邮件配置失败]

#define VIXHZ_CONFIG_DEVBUSY			_EC(999)		//can't set now [暂时无法设置]
#define VIXHZ_CONFIG_DATAILLEGAL		_EC(1000)		//data for configure is invalid [配置数据不合法]

enum CONFIGTYPE
{
	CFG_PTZ_CTRL,				//云台控制
	CFG_GET_PTZ_PRESET,			//预置点操作
	CFG_MOD_PTZ_PRESET,			
	CFG_GET_PTZ_TOUR,			//获取巡航组
	CFG_MOD_PTZ_TOUR,			

	CFG_GET_ALARM,				//报警参数配置
	CFG_SET_ALARM,		
	CFG_GET_ALARM_OUT,			//报警输出配置
	CFG_SET_ALARM_OUT,		
	CFG_GET_ALARM_OUT_STATE,	//报警输出状态
	CFG_GET_IMAGE,				//图像参数配置
	CFG_SET_IMAGE ,			
	CFG_GET_GENERAL_NET,		//网络配置
	CFG_SET_GENERAL_NET,		
	CFG_GET_DECODE,				//解码参数配置
	CFG_SET_DECODE,		

	CFG_GET_RECORD_CTRL,		//录像控制
	CFG_SET_RECORD_CTRL,			
	CFG_GET_CHANNEL_TITLE,		//通道名称
	CFG_SET_CHANNEL_TITLE,			
	CFG_REBOOT,					//远程重启

	CFG_GET_AUTO_MAINTAIN,		//自动维护
	CFG_SET_AUTO_MAINTAIN,		
	CFG_GET_DEVICE_INFO,		//设备信息
	CFG_GET_PTZ_PROTOCOL,		//云台协议

	CFG_GET_PTZ,				//云台参数
	CFG_SET_PTZ,			

	CFG_GET_TIME,				//时间配置
	CFG_SET_TIME,

	CFG_GET_RECORD_ABILITY,					
	CFG_GET_RECORD,				//录像配置
	CFG_SET_RECORD,
	CFG_GET_DISKINFO,			//磁盘信息
	CFG_SET_DISK,				//磁盘管理
	CFG_QUERY_RECORD,			//录像查询
	CFG_GET_RECORD_URL,			//获得录像URL
	CFG_GET_DISK_ARRAY,			//盘组配置
	CFG_SET_DISK_ARRAY,
	CFG_NET_GET_RTSP,			//RTSP参数
	CFG_NET_SET_RTSP,
	CFG_GET_ENCODE_ABILITY,		//编码能力集
	CFG_GET_ENCODE,
	CFG_SET_ENCODE,

	CFG_NET_GET_SMTP,			//邮件参数
	CFG_NET_SET_SMTP,
	CFG_NET_GET_DDNS,			//DDNS参数
	CFG_NET_SET_DDNS,
	CFG_NET_GET_UPNP,			//UPNP参数
	CFG_NET_SET_UPNP,
	CFG_NET_GET_PPPOE,			//PPPOE参数
	CFG_NET_SET_PPPOE,
	CFG_NET_GET_NTP,			//NTP参数
	CFG_NET_SET_NTP,
	CFG_NET_GET_IP_FILTER,		//IP过滤参数
	CFG_NET_SET_IP_FILTER,
	CFG_NET_GET_FTP_SERVER,		//FTP Server配置
	CFG_NET_SET_FTP_SERVER,
	CFG_NET_GET_FTP_APP,		//FTP App配置
	CFG_NET_SET_FTP_APP,

	CFG_GET_OSD_ABILITY,
	CFG_GET_OSD,				//OSD叠加
	CFG_SET_OSD,
	CFG_GET_LOG,				//日志查询
	CFG_CLEAR_LOG,				//清除日志
	CFG_GET_LOG_SET,			//日志配置
	CFG_SET_LOG_SET,
	CFG_DEFAULT,				//恢复默认

	CFG_IMAGE_GET_EFFECT,		//effect参数
	CFG_IMAGE_SET_ECCECT,
	CFG_IMAGE_GET_LENS,			//镜头参数
	CFG_IMAGE_SET_LENS,
	CFG_IMAGE_GET_WB,			//白平衡
	CFG_IMAGE_SET_WB,
	CFG_IMAGE_GET_CLARITY,		//清晰度参数配置
	CFG_IMAGE_SET_CLARITY,
	CFG_IMAGE_GET_ICR,			//彩转黑参数配置
	CFG_IMAGE_SET_ICR,
	CFG_IMAGE_GET_FOCUS,		//聚焦参数
	CFG_IMAGE_SET_FOCUS,
	CFG_IMAGE_GET_EXP,			//曝光参数
	CFG_IMAGE_SET_EXP,
	CFG_IMAGE_GET_DR,			//宽动态参数配置
	CFG_IMAGE_SET_DR,

	CFG_NET_GET_AUTOREG,		//主动注册
	CFG_NET_SET_AUTOREG,
	CFG_GET_SPLIT,				//画面分割
	CFG_SET_SPLIT,
	CFG_GET_TOUR,				//轮询配置
	CFG_SET_TOUR,
	CFG_GET_DEV_TYPENAME_MAP,	//获取数字通道支持类型
	CFG_GET_VIDEO_URL,			//获取视频url
	CFG_GET_INTET_VIDEO,		//平台接入配置
	CFG_SET_INTET_VIDEO,
	CFG_NET_GET_ONVIF,			//ONVIF配置
	CFG_NET_SET_ONVIF,

	CFG_IPD_GET_INFR_WIPER,		//球机红外灯雨刷控配置
	CFG_IPD_SET_INFR_WIPER,
	CFG_IPD_CTR_INFR_WIPE,		//球机红外灯雨刷控制
	//CFG_IPD_CTR_INFR_WIPE,

	CFG_GET_INTDETECT,			//拌线拌网
	CFG_SET_INTDETECT,
	CFG_GET_SYSTEM_ABILITY,		//获取设备能力集
	CFG_GET_SNAP_ABILITY,		//获取抓图能力集
	CFG_GET_SNAP,				//抓图配置
	CFG_SET_SNAP,
	CFG_GET_GENERAL,			//通用参数
	CFG_SET_GENERAL,
	CFG_GET_PURE_DECODE,		//纯解码器参数配置
	CFG_SET_PURE_DECODE,
	CFG_GET_ADVANCE,			//IPC高级参数
	CFG_SET_ADVANCE,
	CFG_BADPIXEL_DETECT,		//坏点检测
	CFG_GET_DISPLAY,			//输出模式
	CFG_SET_DISPLAY, 
	CFG_GET_COMM,				//串口配置
	CFG_SET_COMM,
	CFG_GET_INTER_VIDEO_LOG,	//查询接入日志
	CFG_CLEAR_INTER_VIDEO_LOG,	//清除借入日志
	CFG_MANUAL_SHOT,			//手动抓图
	CFG_GET_ROI_ABILITY,		//获取ROI能力集
	CFG_GET_ROI,				//ROI配置
	CFG_SET_ROI,
	CFG_BOOK_TRANS_DATA,		//订阅透传传输
	CFG_GET_ABTSET,				//异常参数配置
	CFG_SET_ABTSET,
	CFG_GET_WIFI_LIST,			//获取WIFI列表
	CFG_GET_WIFI,
	CFG_SET_WIFI,

	CFG_BOOK_ALARM,				//订阅报警
	CFG_CU_ALARM,				//报警上报
	CFG_USER_QUERY_USER_AUTH,	//查询用户权限
	CFG_USER_QUERY_USER_GROUP,	//查询用户组
	CFG_USER_ADD_USER_GROUP,	//增加用户组
	CFG_USER_MOD_USER_GROUP,	//修改用户组
	CFG_USER_DEL_USER_GROUP,	//删除用户组
	CFG_USER_QUERY_USER,		//查询用户
	CFG_USER_ADD_USER,			//增加用户
	CFG_USER_MOD_USER,			//修改用户
	CFG_USER_DEL_USER,			//删除用户
	CFG_USER_MOD_PWD,			//修改密码

	CFG_UPGRADE,				//升级
	CFG_PUT_FILE,				//上传文件
	CFG_GET_FILE,				//下载文件

	CFG_IPD_GET_CAMERA,			//摄像机参数设置
	CFG_IPD_SET_CAMERA,
	CFG_IPD_GET_ADV,			//高级参数设置
	CFG_IPD_SET_ADV,
	CFG_IPD_GET_AUTO_HOME,		//自动归位参数设置
	CFG_IPD_SET_AUTO_HOME,
	CFG_IPD_GET_BLIND,			//遮挡参数配置
	CFG_IPD_SET_BLIND,
	CFG_IPD_SET_POSTION,		//3D定位设置
	CFG_IPD_GET_VIDEO_CAPTURE,	//图像的视频采集的消隐区
	CFG_IPD_SET_VIDEO_CAPTURE,
	CFG_IPD_OPERATION,			//球机特殊操作命令
	CFG_IPD_GET_ABLITY,			//球机特殊协议能力集
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
