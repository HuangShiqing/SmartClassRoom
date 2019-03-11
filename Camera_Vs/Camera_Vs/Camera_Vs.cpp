// focus_camera_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include "VixHZ_def.h"
#include "VixHZ_export.h"
#include <time.h>

//#include "XMLConfigure.h"
//#include "typedef.h"

#pragma comment(lib, "iNetSDK.lib")

using namespace std;




bool CALLBACK RealDataCBFunc(unsigned long lRealHandle, unsigned long dwDataType, unsigned char *pBuffer, unsigned long dwBufSize, unsigned long dwUser)
{
	printf("rev video data len = %d\n", dwBufSize);
	if (dwBufSize < 0)
	{
		return false;
	}

	if (dwDataType == VixFT_JEPG)
	{
		printf("jpg\n");
		char fileName[100];
		sprintf(fileName, "%d.jpg", time(0));//D:\DeepLearning\vs\focus_camera_test\focus_camera_test\//
		FILE* file = fopen(fileName, "wb");
		fwrite(pBuffer, 1, dwBufSize, file);
		fclose(file);
		return false;
	}
}



int _tmain(int argc, _TCHAR* argv[])
{

	if (!_VixHz_InitSDK())
	{		
		printf("InitSDK ERROR!\n");
		system("pause");
		return 0;
	}
	printf("InitSDK OK!\n");
	//登录
	long m_login_id = -1;
	base::string devInfo;
	m_login_id = _VixHz_LoginDevice("192.168.1.108", 80, "admin", "123456", devInfo);

	//云台控制
	//long mChannelNum = 0;
	//long lConfigType = VIXHZ_PTZ_LEFT;
	//Vix_PtzCfgParam para = { 0 };
	//para.lParam1 = 4;
	//para.lParam2 = 4;
	//base::string strInfoPtz;
	//long lParam1 = 0;//区分是控制命令还是配置，1-配置
	//_VixHz_SendPtzCtrl(m_login_id, mChannelNum, lConfigType, para, strInfoPtz);
	//Sleep(1000);		
	//para.bStop = true;
	//_VixHz_SendPtzCtrl(m_login_id, mChannelNum, lConfigType, para, strInfoPtz);
	

	//抓图
	//long lHandle = _VixHz_StartRealPlay(m_login_id, 0, 5, NULL, RealDataCBFunc, NULL);

	//添加预置点
	//string strinfo = "";
	//unsigned char nPointNum = 0;
	//VG_PRESET_INFO poinfinfo = { 0 };
	//poinfinfo.ucPresetID = nPointNum;
	//itoa(nPointNum, poinfinfo.szPresetName, 10);//必须设置名称
	//CXMLConfigure::Instance()->PacketXMLInside(CFG_ADDPRESET_CFG, strinfo, &poinfinfo, -1);
	//Vix_PtzCfgParam para = { 0 };
	//base::string info;
	//info = strinfo.c_str();
	//_VixHz_SendPtzCtrl(m_login_id, 0, CFG_ADDPRESET_CFG, para, info,1);

	//云台转到预置点
	unsigned char nPointNum = 2;
	long mChannelNum = 0;
	long lConfigType = VIXHZ_PTZ_GoPrepoint;
	Vix_PtzCfgParam para = { 0 };
	para.lParam1 = 4;
	para.lParam2 = nPointNum;
	base::string strInfoPtz;
	long lParam1 = 0;//区分是控制命令还是配置，1-配置
	_VixHz_SendPtzCtrl(m_login_id, mChannelNum, lConfigType, para, strInfoPtz);

	getchar();
	return 0;
}

