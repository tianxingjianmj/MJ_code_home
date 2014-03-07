/**************************************************************************
// 硬件设置参数
**************************************************************************/
#include "windows.h"

// 公用参数 
#ifndef _USB1010_PAPA_DataList
typedef struct _USB1010_PAPA_DataList
{	 
	LONG Multiple;				// 倍率 (1~500)
	LONG StartSpeed;			// 初始速度(1~8000)   
	LONG DriveSpeed;			// 驱动速度(1~8000)   
	LONG Acceleration;			// 加速度(125~1000000)
	LONG Deceleration;			// 减速度(125~1000000)
	LONG AccelerationK;			// 加速度变化率(954~62500000)

} USB1010_PARA_DataList, *PUSB1010_PARA_DataList;
#endif

// 直线和S曲线参数
#ifndef _USB1010_PAPA_LCData
typedef struct _USB1010_PAPA_LCData
{
	LONG AxisNum;				// 轴号 (X轴 | Y轴 | X、Y轴)
	LONG LV_DV;					// 驱动方式  (连续 | 定长 )
	LONG Mode;					// 脉冲方式 (CW/CCW方式 | CP/DIR方式)
	LONG Line_Curve;			// 运动方式	(直线 | 曲线)
	LONG Direction;				// 运动方向 (正方向 | 反方向)
	LONG nPulseNum;		    	// 定量输出脉冲数(0~268435455)
} USB1010_PARA_LCData, *PUSB1010_PARA_LCData;
#endif

// 直线插补和固定线速度直线插补参数
#ifndef _USB1010_PAPA_LineData
typedef struct _USB1010_PAPA_LineData	
{
	LONG Line_Curve;			// 运动方式	(直线 | 曲线)
	LONG ConstantSpeed;			// 固定线速度 (不固定线速度 | 固定线速度)
	LONG nXAxisPulseNum;		// X轴插补脉冲数 (-8388608~8388607)
	LONG nYAxisPulseNum;		// Y轴插补脉冲数 (-8388608~8388607)
} USB1010_PARA_LineData, *PUSB1010_PARA_LineData;
#endif

// 正反方向圆弧插补参数
#ifndef _USB1010_PAPA_CircleData
typedef struct _USB1010_PAPA_CircleData	
{
	LONG ConstantSpeed;			// 固定线速度 (不固定线速度 | 固定线速度)
	LONG XCenter;				// X轴圆心坐标 (脉冲数 -8388608~8388607)
    LONG YCenter;				// Y轴圆心坐标 (脉冲数 -8388608~8388607)
	LONG XPulse;				// X轴终点坐标 (脉冲数 -8388608~8388607)		
	LONG YPulse;				// Y轴终点坐标 (脉冲数 -8388608~8388607)
} USB1010_PARA_CircleData, *PUSB1010_PARA_CircleData;
#endif

/***************************************************************/
// 轴号
#define		USB1010_XAXIS			0X1			// X轴
#define		USB1010_YAXIS	 		0x2			// Y轴
#define		USB1010_XYAXIS			0x3			// X、Y轴

/***************************************************************/
// 驱动方式
#define		USB1010_DV				0x0			// 定长驱动
#define		USB1010_LV				0x1         // 连续驱动

/***************************************************************/
// 脉冲输出方式
#define 	USB1010_CWCCW			0X0			// CW/CCW方式 
#define 	USB1010_CPDIR 			0X1			// CP/DIR方式

/***************************************************************/
// 脉冲输入方式
#define 	USB1010_A_B			    0X0			// A/B相输入方式 
#define 	USB1010_U_D 			0X1			// 上/下脉冲输入方式

/***************************************************************/
// 运动方式
#define		USB1010_LINE			0X0			// 直线运动
#define		USB1010_CURVE			0X1			// S曲线运动

/***************************************************************/
// 运动方向
#define		USB1010_MDIRECTION		0x0			// 反方向
#define		USB1010_PDIRECTION		0x1			// 正方向

/***************************************************************/
//固定线速度
#define		USB1010_NOCONSTAND		0X0			// 不固定线速度
#define		USB1010_CONSTAND		0X1			// 固定线速度

/***************************************************************/
// 软件限位的逻辑实位计数器选择和设置外部越限信号的停止方式和设置外部停止信号的停止号选择
/***************************************************************/
// 计数器类别
#define		USB1010_LOGIC			0x0			// 逻辑位计数器
#define		USB1010_FACT			0x1			// 实位计数器

/***************************************************************/
//停止方式
#define		USB1010_SUDDENSTOP		0x0			// 立即停止
#define		USB1010_DECSTOP			0X1			// 减速停止

/***************************************************************/
//外部停止信号
#define 	USB1010_STOP0			0X0			// 停止信号0
#define 	USB1010_STOP1			0X1			// 停止信号1

/********************************************************************/
#define		USB1010_ERROR			0XFF		// 错误
/********************************************************************/

// 状态寄存器RR0
#ifndef _USB1010_PARA_RR0
typedef struct _USB1010_PARA_RR0      
{
	UINT XDRV;			// X轴的驱动状态  1：正在输出脉冲 0：停止驱动
	UINT YDRV;			// Y轴的驱动状态  1：正在输出脉冲 0：停止驱动
	UINT XERROR;		// X轴的出错状态  X轴的RR2寄存器的任何一位为1，此位就为1
	UINT YERROR;		// Y轴的出错状态  X轴的RR2寄存器的任何一位为1，此位就为1
	UINT IDRV;			// 插补驱动状态   1：正在输出插补驱动脉冲
	UINT CNEXT;			// 表示可以写入连续插补的下一个数据  1：可以写入 0：不可以写入
	UINT ZONE0;			// ZONE2、ZONE1、ZONE0表示在圆弧插补驱动中所在的象限
	UINT ZONE1;			// 000 ：第0象限   001：第1象限  010：第2象限  011：第3象限
	UINT ZONE2;			// 100 ：第4象限   101：第5象限	 110：第6象限  111：第7象限
	UINT BPSC0;			// BPSC1、BPSC0表示在位插补驱动中堆栈计数器(SC)的数值
	UINT BPSC1;			// 00： 0   01：1   10： 2   11：3
} USB1010_PARA_RR0,*PUSB1010_PARA_RR0;
#endif

// 状态寄存器RR1，每一个轴都有RR1寄存器，读哪个要指定轴号
#ifndef _USB1010_PARA_RR1
typedef struct _USB1010_PARA_RR1    
{
	UINT CMPP;			// 表示逻辑/实位计数器和COMP+寄存器的大小关系 1：逻辑/实位计数器≥COMP+ 0：逻辑/实位计数器＜COMP+
	UINT CMPM;			// 表示逻辑/实位计数器和COMP-寄存器的大小关系 1：逻辑/实位计数器＜COMP- 0：逻辑/实位计数器≥COMP-
	UINT ASND;			// 在加/减速驱动中加速时，为1
	UINT CNST;			// 在加/减速驱动中定速时，为1
	UINT DSND;			// 在加/减速驱动中减速时，为1
	UINT AASND;			// 在S曲线加/减速驱动中，加速度/减速度增加时，为1 
	UINT ACNST;			// 在S曲线加/减速驱动中，加速度/减速度不变时，为1 
	UINT ADSND;			// 在S曲线加/减速驱动中，加速度/减速度减少时，为1 
	UINT STOP0;			// 外部停止信号STOP0有效使驱动停止时，为1
	UINT STOP1;			// 外部停止信号STOP1有效使驱动停止时，为1
	UINT LMTP;			// 外部正方向限制信号(nLMTP)有效使驱动停止时，为1
	UINT LMTM;			// 外部反方向限制信号(nLMTM)有效使驱动停止时，为1
	UINT ALARM;			// 外部伺服马达报警信号(nALARM)有效使驱动停止时，为1
	UINT EMG;			// 外部紧急停止信号(EMGN)使驱动停止时，为1
} USB1010_PARA_RR1,*PUSB1010_PARA_RR1;
#endif

// 状态寄存器RR2，每一个轴都有RR2寄存器，读哪个要指定轴号
#ifndef _USB1010_PARA_RR2
typedef struct _USB1010_PARA_RR2     
{
	UINT SLMTP;			// 设置正方向软件限位后，在正方向驱动中，逻辑/实位计数器大于COMP+寄存器值时，为1
	UINT SLMTM;			// 设置反方向软件限位后，在反方向驱动中，逻辑/实位计数器小于COMP-寄存器值时，为1
	UINT HLMTP;			// 外部正方向限制信号(nLMTP)处于有效电平时，为1
	UINT HLMTM;			// 外部反方向限制信号(nLMTM)处于有效电平时，为1
	UINT ALARM;			// 外部伺服马达报警信号(nALARM)设置为有效并处于有效状态时，为1
	UINT EMG;			// 外部紧急停止信号处于低电平时，为1
} USB1010_PARA_RR2,*PUSB1010_PARA_RR2;
#endif

// 状态寄存器RR3
#ifndef _USB1010_PARA_RR3
typedef struct _USB1010_PARA_RR3      
{
	UINT XSTOP0;		// 外部停止信号XSTOP0的电平状态 1：高电平 0：低电平
	UINT XSTOP1;		// 外部停止信号XSTOP0的电平状态 1：高电平 0：低电平
	UINT EMG;			// 外部紧急停止信号EMG的电平状态 1：高电平 0：低电平
	UINT XEXPP;			// 外部正方向点动输入信号XEXPP的电平状态 1：高电平 0：低电平
	UINT XEXPM;			// 外部反方向点动输入信号XEXPM的电平状态 1：高电平 0：低电平
	UINT XINPOS;		// 外部伺服电机到位信号XINPOS的电平状态  1：高电平 0：低电平
	UINT XALARM;		// 外部伺服马达报警信号XALARM的电平状态  1：高电平 0：低电平
	UINT XIN0;			// 外部输入信号XIN0的电平状态  1：高电平 0：低电平
	UINT XIN1;			// 外部输入信号XIN1的电平状态  1：高电平 0：低电平
	UINT XLMTP;			// 外部正方向限制信号XLMTP的电平状态  1：高电平 0：低电平
	UINT XLMTM;			// 外部反方向限制信号XLMTM的电平状态  1：高电平 0：低电平

} USB1010_PARA_RR3,*PUSB1010_PARA_RR3;
#endif

// 状态寄存器RR4
#ifndef _USB1010_PARA_RR4
typedef struct _USB1010_PARA_RR4      
{
	UINT YSTOP0;		// 外部停止信号YSTOP0的电平状态 1：高电平 0：低电平
	UINT YSTOP1;		// 外部停止信号YSTOP1的电平状态 1：高电平 0：低电平
	UINT YEXPP;			// 外部正方向点动输入信号YEXPP的电平状态 1：高电平 0：低电平
	UINT YEXPM;			// 外部反方向点动输入信号YEXPM的电平状态 1：高电平 0：低电平
	UINT YINPOS;		// 外部伺服电机到位信号YINPOS的电平状态  1：高电平 0：低电平
	UINT YALARM;		// 外部伺服马达报警信号YALARM的电平状态  1：高电平 0：低电平
	UINT YIN0;			// 外部输入信号YIN0的电平状态  1：高电平 0：低电平
	UINT YIN1;			// 外部输入信号YIN1的电平状态  1：高电平 0：低电平
	UINT YLMTP;			// 外部正方向限制信号YLMTP的电平状态  1：高电平 0：低电平
	UINT YLMTM;			// 外部反方向限制信号YLMTM的电平状态  1：高电平 0：低电平
} USB1010_PARA_RR4,*PUSB1010_PARA_RR4;
#endif

#ifndef DEFINING
#define DEVAPI __declspec(dllimport)
#else
#define DEVAPI __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//######################## 设备对象管理函数 #################################
// 适用于本设备的最基本操作	
HANDLE DEVAPI FAR PASCAL USB1010_CreateDevice(       // 创建句柄
							int DeviceID);           // 设备ID号

int DEVAPI FAR PASCAL USB1010_GetDeviceCount(		// 获取设备个数
							HANDLE hDevice);

BOOL DEVAPI FAR PASCAL USB1010_GetDeviceCurrentID(
							HANDLE hDevice, 		 // 设备句柄
							PLONG DeviceLgcID,		 // 逻辑ID 
							PLONG DevicePhysID);	 // 物理ID

BOOL DEVAPI FAR PASCAL USB1010_GetDevVersion(		// 获取设备固件及程序版本
							HANDLE hDevice,			// 设备对象句柄,它由CreateDevice函数创建
							PULONG pulFmwVersion,	// 固件版本
							PULONG pulDriverVersion);// 驱动版本

BOOL DEVAPI FAR PASCAL USB1010_ReleaseDevice(		 // 释放设备
							HANDLE hDevice);		 // 设备句柄
 
BOOL DEVAPI  FAR PASCAL  USB1010_ResetDevice(		 // 复位设备
							HANDLE hDevice);		 // 设备句柄
//*******************************************************************
// 设置电机的基本参数模式、倍率、加速度、减速度、加/减速度变化率、初始速度、输出脉冲数
// 插补输出脉冲数、圆心坐标、逻辑计数器、实际位置计数器、加速计数器偏移

BOOL DEVAPI FAR PASCAL USB1010_PulseOutMode(         // 设置脉冲输出模式
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)  
							LONG Mode);				 // 模式

BOOL DEVAPI FAR PASCAL USB1010_PulseInputMode(       // 设置脉冲输入模式
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)  
							LONG Mode);				 // 模式

BOOL DEVAPI FAR PASCAL USB1010_SetR(				 // 设置倍率(1-500)	
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)  
							LONG Data);				 // 倍率值(1-500)

BOOL DEVAPI FAR PASCAL USB1010_SetA(				 // 设置加速度
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)     
							LONG Data);				 // 加速度 (125-1000000)

BOOL DEVAPI FAR PASCAL USB1010_SetDec(				 // 设置减速度
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 减速度值(125-1000,000)

BOOL DEVAPI FAR PASCAL USB1010_SetAK(				 // 加速度变化率  
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)   
							LONG Data);				 // 数据 (1-62500000) 

BOOL DEVAPI FAR PASCAL USB1010_SetSV(				 // 设置初始速度(1-8000)
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)   
							LONG Data);				 // 速度值(1-8000)

BOOL DEVAPI FAR PASCAL USB1010_SetV(				 // 设置驱动速度
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)     
							LONG Data);				 // 驱动速度值(1-8000)

BOOL DEVAPI FAR PASCAL USB1010_SetP(				 // 设置定长脉冲数
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);			     // 定长脉冲数(0-268435455)

BOOL DEVAPI FAR PASCAL USB1010_SetIP(				 // 设置插补终点脉冲数(-8388608-+8388607)
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 插补终点脉冲数(-8388608-+8388607)

BOOL DEVAPI FAR PASCAL USB1010_SetC(                 // 设置圆心坐标(脉冲数)  
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 圆心坐标脉冲数范围(-8388608-+8388607)

BOOL DEVAPI FAR PASCAL USB1010_SetLP(				 // 设置逻辑位置计数器
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 逻辑位置计数器值(-2147483648-+2147483647)

BOOL DEVAPI FAR PASCAL USB1010_SetEP(				 // 设置实位计数器 
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 实位计数器值(-2147483648-+2147483647)

BOOL DEVAPI FAR PASCAL USB1010_SetAccofst(			 // 设置加速计数器偏移
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 偏移范围(0-65535)

//*******************************************************************
// 直线S曲线初始化、启动函数

BOOL DEVAPI FAR PASCAL USB1010_InitLVDV(				// 初始化连续,定长脉冲驱动
							HANDLE hDevice,				// 设备句柄
							PUSB1010_PARA_DataList pDL, // 公共参数结构体指针
							PUSB1010_PARA_LCData pLC);	// 直线S曲线参数结构体指针

BOOL DEVAPI FAR PASCAL USB1010_StartLVDV(				// 启动连续,定长脉冲驱动
							HANDLE hDevice,				// 设备句柄
							LONG AxisNum);				// 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

BOOL DEVAPI FAR PASCAL	USB1010_Start2D(HANDLE hDevice);// 2轴同时启动						           
//*******************************************************************
// 直线插补初始化、启动函数
BOOL DEVAPI FAR PASCAL USB1010_InitLineInterpolation(	// 初始化直线插补运动 
							HANDLE hDevice,				// 设备句柄
							PUSB1010_PARA_DataList pDL, // 公共参数结构体指针
							PUSB1010_PARA_LineData pLD);// 直线插补结构体指针

BOOL DEVAPI FAR PASCAL USB1010_StartLineInterpolation(	// 启动直线插补运动 
							HANDLE hDevice);			// 设备句柄

//*******************************************************************
// 正反方向圆弧插补初始化、启动函数
BOOL DEVAPI FAR PASCAL USB1010_InitCWInterpolation(		// 初始化正反方向圆弧插补运动 
							HANDLE hDevice,				// 设备句柄
							PUSB1010_PARA_DataList pDL, // 公共参数结构体指针
							PUSB1010_PARA_CircleData pCD);// 圆弧插补结构体指针
                         
BOOL DEVAPI FAR PASCAL USB1010_StartCWInterpolation(    // 启动正方向圆弧插补运动 
							HANDLE hDevice);			// 设备句柄
	                                                  
BOOL DEVAPI FAR PASCAL USB1010_StartCCWInterpolation(   // 启动反方向圆弧插补运动 
							HANDLE hDevice);			// 设备句柄

//*************************************************************************
// 位插补相关函数
BOOL DEVAPI FAR PASCAL USB1010_InitBitInterpolation(	// 初始化位插补参数
							HANDLE hDevice,				// 设备句柄
							PUSB1010_PARA_DataList pDL);// 公共参数结构体指针

BOOL DEVAPI FAR PASCAL USB1010_AutoBitInterpolation(    // 自动执行位插补
							HANDLE hDevice,				// 设备句柄
							PSHORT pBuffer,				// 位插补数据指针	
							UINT nCount);				// 数据组数

BOOL DEVAPI FAR PASCAL USB1010_ReleaseBitInterpolation(	// 释放位插补
							HANDLE hDevice);			// 设备句柄

BOOL DEVAPI FAR PASCAL USB1010_SetBP(                   // 设置位插补数据
							HANDLE hDevice,				// 设备句柄 
							LONG BP1PData,				// X轴正方向驱动数据
							LONG BP1MData,				// X轴反方向驱动数据
							LONG BP2PData,				// Y轴正方向驱动数据
							LONG BP2MData);				// Y轴反方向驱动数据

BOOL DEVAPI FAR PASCAL USB1010_StartBitInterpolation(	// 启动位插补
							HANDLE hDevice);			// 设备句柄

BOOL DEVAPI FAR PASCAL  USB1010_BPWait(					// 等待位插补的下一个数据设定
							HANDLE hDevice);			// 设备句柄

BOOL DEVAPI FAR PASCAL USB1010_ClearBPData(				// 清除BP寄存器数据
							HANDLE hDevice);			// 设备句柄

//*******************************************************************
// 连续插补相关函数
							
BOOL DEVAPI FAR PASCAL  USB1010_NextWait(				// 等待连续插补下一个节点命令设定
							HANDLE hDevice);			// 设备句柄

//*******************************************************************
// 外部信号启动电机定长驱动、连续驱动

BOOL DEVAPI FAR PASCAL USB1010_SetOutEnableDV(		 // 外部控制定量驱动(下降沿有效)
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
		                    
BOOL DEVAPI FAR PASCAL USB1010_SetOutEnableLV(		 // 外部控制连续驱动(保持低电平有效)
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

//*******************************************************************
// 设置软件限位有效和无效

BOOL DEVAPI FAR PASCAL USB1010_SetPDirSoftwareLimit( // 设置正方向软件限位
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG LogicFact,			 // 逻辑/实位计数器选择 USB1010_LOGIC：逻辑位置计数器 USB1010_FACT：实位计数器	
							LONG Data);				 // 软件限位数据

BOOL DEVAPI FAR PASCAL USB1010_SetMDirSoftwareLimit( // 设置反方向软件限位
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG LogicFact,			 // 逻辑/实位计数器选择 USB1010_LOGIC：逻辑位置计数器 USB1010_FACT：实位计数器	
							LONG Data);				 

BOOL DEVAPI FAR PASCAL USB1010_ClearSoftwareLimit(	 // 清除软件限位
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)

//******************************************************************* 
// 设置外部输入信号的有效和无效		
BOOL DEVAPI FAR PASCAL USB1010_SetLMTEnable(		 // 设置外部越限信号的有效及停止方式	
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG StopMode);          // USB1010_DECSTOP：减速停止，USB1010_SUDDENSTOP：立即停止

BOOL DEVAPI FAR PASCAL USB1010_SetStopEnable(		 // 设置外部停止信号有效
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG StopNum);			 // 停止号

BOOL DEVAPI FAR PASCAL USB1010_SetStopDisable(		 // 设置外部停止信号无效
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);   		 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
											
BOOL DEVAPI FAR PASCAL USB1010_SetALARMEnable(       // 设置伺服报警信号有效 
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)  

BOOL DEVAPI FAR PASCAL USB1010_SetALARMDisable(      // 设置伺服报警信号无效  
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)  

BOOL DEVAPI FAR PASCAL USB1010_SetINPOSEnable(		 // 设置伺服马达定位完毕输入信号有效 
							HANDLE hDevice,			 // 设备句柄	
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

BOOL DEVAPI FAR PASCAL USB1010_SetINPOSDisable(		 // 设置伺服马达定位完毕输入信号无效
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

//*******************************************************************
// 减速函数设置

BOOL DEVAPI FAR PASCAL USB1010_DecValid(			 // 减速有效
							HANDLE hDevice);		 // 设备句柄

BOOL DEVAPI FAR PASCAL USB1010_DecInvalid(			 // 减速无效
							HANDLE hDevice);		 // 设备句柄

BOOL DEVAPI FAR PASCAL USB1010_DecStop(				 // 减速停止
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)  

BOOL DEVAPI FAR PASCAL USB1010_InstStop(			 // 立即停止
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

BOOL DEVAPI FAR PASCAL USB1010_AutoDec(				 // 自动减速
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

BOOL DEVAPI FAR PASCAL USB1010_HanDec(				 // 手动减速点设定
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Data);				 // 手动减速点数据，范围(0 - 268435455)

//*************************************************************************
// 读电机状态：逻辑计数器、实际位置计数器、当前速度、加/减速度
LONG DEVAPI FAR PASCAL USB1010_ReadLP(				 // 读逻辑计数器
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

LONG DEVAPI FAR PASCAL USB1010_ReadEP(				 // 读实位计数器
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

LONG DEVAPI FAR PASCAL USB1010_ReadCV(				 // 读当前速度
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

LONG DEVAPI FAR PASCAL USB1010_ReadCA(				 // 读当前加速度
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 

//*******************************************************************
// 读状态寄存器的位状态

LONG DEVAPI FAR PASCAL USB1010_ReadRR(				 // 读RR寄存器
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							LONG Num);				 // 寄存器号

BOOL DEVAPI FAR PASCAL USB1010_GetRR0Status(		 // 获得主状态寄存器RR0的位状态
							HANDLE hDevice,			 // 设备句柄
							PUSB1010_PARA_RR0 pPara);// RR0寄存器状态

BOOL DEVAPI FAR PASCAL USB1010_GetRR1Status(		 // 获得状态寄存器RR1的位状态
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							PUSB1010_PARA_RR1 pPara);// RR1寄存器状态			

BOOL DEVAPI FAR PASCAL USB1010_GetRR2Status(		 // 获得状态寄存器RR2的位状态
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum,			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴) 
							PUSB1010_PARA_RR2 pPara);// RR2寄存器状态			

BOOL DEVAPI FAR PASCAL USB1010_GetRR3Status(		 // 获得状态寄存器RR3的位状态
							HANDLE hDevice,			 // 设备句柄
							PUSB1010_PARA_RR3 pPara);// RR3寄存器状态			

BOOL DEVAPI FAR PASCAL USB1010_GetRR4Status(		 // 获得状态寄存器RR4的位状态
							HANDLE hDevice,			 // 设备句柄
							PUSB1010_PARA_RR4 pPara);// RR4寄存器状态
		
//*******************************************************************
// 设置通用输出和读通用输入
BOOL DEVAPI FAR PASCAL USB1010_SetOutput(				 // 设置通用输出电平
							HANDLE hDevice,			 // 设备句柄
						    LONG XOut1,				 // X轴OUT1 1：XOUT1为高电平  0：XOUT0为低电平  
							LONG XOut0,				 // X轴OUT0 1：XOUT1为高电平  0：XOUT0为低电平
							LONG YOut1,				 // Y轴OUT1 1：YOUT1为高电平  0：YOUT0为低电平  
							LONG YOut0);			 // Y轴OUT0 1：YOUT1为高电平  0：YOUT0为低电平

LONG DEVAPI FAR PASCAL USB1010_ReadTYPE(			 // 读通用输入信号电平
							HANDLE hDevice,			 // 设备句柄
							LONG AxisNum);			 // 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)

//*******************************************************************
#ifdef __cplusplus
}
#endif
// 自动包含驱动函数导入库

