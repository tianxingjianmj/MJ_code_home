/**************************************************************************
// Ӳ�����ò���
**************************************************************************/
#include "windows.h"

// ���ò��� 
#ifndef _USB1010_PAPA_DataList
typedef struct _USB1010_PAPA_DataList
{	 
	LONG Multiple;				// ���� (1~500)
	LONG StartSpeed;			// ��ʼ�ٶ�(1~8000)   
	LONG DriveSpeed;			// �����ٶ�(1~8000)   
	LONG Acceleration;			// ���ٶ�(125~1000000)
	LONG Deceleration;			// ���ٶ�(125~1000000)
	LONG AccelerationK;			// ���ٶȱ仯��(954~62500000)

} USB1010_PARA_DataList, *PUSB1010_PARA_DataList;
#endif

// ֱ�ߺ�S���߲���
#ifndef _USB1010_PAPA_LCData
typedef struct _USB1010_PAPA_LCData
{
	LONG AxisNum;				// ��� (X�� | Y�� | X��Y��)
	LONG LV_DV;					// ������ʽ  (���� | ���� )
	LONG Mode;					// ���巽ʽ (CW/CCW��ʽ | CP/DIR��ʽ)
	LONG Line_Curve;			// �˶���ʽ	(ֱ�� | ����)
	LONG Direction;				// �˶����� (������ | ������)
	LONG nPulseNum;		    	// �������������(0~268435455)
} USB1010_PARA_LCData, *PUSB1010_PARA_LCData;
#endif

// ֱ�߲岹�͹̶����ٶ�ֱ�߲岹����
#ifndef _USB1010_PAPA_LineData
typedef struct _USB1010_PAPA_LineData	
{
	LONG Line_Curve;			// �˶���ʽ	(ֱ�� | ����)
	LONG ConstantSpeed;			// �̶����ٶ� (���̶����ٶ� | �̶����ٶ�)
	LONG nXAxisPulseNum;		// X��岹������ (-8388608~8388607)
	LONG nYAxisPulseNum;		// Y��岹������ (-8388608~8388607)
} USB1010_PARA_LineData, *PUSB1010_PARA_LineData;
#endif

// ��������Բ���岹����
#ifndef _USB1010_PAPA_CircleData
typedef struct _USB1010_PAPA_CircleData	
{
	LONG ConstantSpeed;			// �̶����ٶ� (���̶����ٶ� | �̶����ٶ�)
	LONG XCenter;				// X��Բ������ (������ -8388608~8388607)
    LONG YCenter;				// Y��Բ������ (������ -8388608~8388607)
	LONG XPulse;				// X���յ����� (������ -8388608~8388607)		
	LONG YPulse;				// Y���յ����� (������ -8388608~8388607)
} USB1010_PARA_CircleData, *PUSB1010_PARA_CircleData;
#endif

/***************************************************************/
// ���
#define		USB1010_XAXIS			0X1			// X��
#define		USB1010_YAXIS	 		0x2			// Y��
#define		USB1010_XYAXIS			0x3			// X��Y��

/***************************************************************/
// ������ʽ
#define		USB1010_DV				0x0			// ��������
#define		USB1010_LV				0x1         // ��������

/***************************************************************/
// ���������ʽ
#define 	USB1010_CWCCW			0X0			// CW/CCW��ʽ 
#define 	USB1010_CPDIR 			0X1			// CP/DIR��ʽ

/***************************************************************/
// �������뷽ʽ
#define 	USB1010_A_B			    0X0			// A/B�����뷽ʽ 
#define 	USB1010_U_D 			0X1			// ��/���������뷽ʽ

/***************************************************************/
// �˶���ʽ
#define		USB1010_LINE			0X0			// ֱ���˶�
#define		USB1010_CURVE			0X1			// S�����˶�

/***************************************************************/
// �˶�����
#define		USB1010_MDIRECTION		0x0			// ������
#define		USB1010_PDIRECTION		0x1			// ������

/***************************************************************/
//�̶����ٶ�
#define		USB1010_NOCONSTAND		0X0			// ���̶����ٶ�
#define		USB1010_CONSTAND		0X1			// �̶����ٶ�

/***************************************************************/
// �����λ���߼�ʵλ������ѡ��������ⲿԽ���źŵ�ֹͣ��ʽ�������ⲿֹͣ�źŵ�ֹͣ��ѡ��
/***************************************************************/
// ���������
#define		USB1010_LOGIC			0x0			// �߼�λ������
#define		USB1010_FACT			0x1			// ʵλ������

/***************************************************************/
//ֹͣ��ʽ
#define		USB1010_SUDDENSTOP		0x0			// ����ֹͣ
#define		USB1010_DECSTOP			0X1			// ����ֹͣ

/***************************************************************/
//�ⲿֹͣ�ź�
#define 	USB1010_STOP0			0X0			// ֹͣ�ź�0
#define 	USB1010_STOP1			0X1			// ֹͣ�ź�1

/********************************************************************/
#define		USB1010_ERROR			0XFF		// ����
/********************************************************************/

// ״̬�Ĵ���RR0
#ifndef _USB1010_PARA_RR0
typedef struct _USB1010_PARA_RR0      
{
	UINT XDRV;			// X�������״̬  1������������� 0��ֹͣ����
	UINT YDRV;			// Y�������״̬  1������������� 0��ֹͣ����
	UINT XERROR;		// X��ĳ���״̬  X���RR2�Ĵ������κ�һλΪ1����λ��Ϊ1
	UINT YERROR;		// Y��ĳ���״̬  X���RR2�Ĵ������κ�һλΪ1����λ��Ϊ1
	UINT IDRV;			// �岹����״̬   1����������岹��������
	UINT CNEXT;			// ��ʾ����д�������岹����һ������  1������д�� 0��������д��
	UINT ZONE0;			// ZONE2��ZONE1��ZONE0��ʾ��Բ���岹���������ڵ�����
	UINT ZONE1;			// 000 ����0����   001����1����  010����2����  011����3����
	UINT ZONE2;			// 100 ����4����   101����5����	 110����6����  111����7����
	UINT BPSC0;			// BPSC1��BPSC0��ʾ��λ�岹�����ж�ջ������(SC)����ֵ
	UINT BPSC1;			// 00�� 0   01��1   10�� 2   11��3
} USB1010_PARA_RR0,*PUSB1010_PARA_RR0;
#endif

// ״̬�Ĵ���RR1��ÿһ���ᶼ��RR1�Ĵ��������ĸ�Ҫָ�����
#ifndef _USB1010_PARA_RR1
typedef struct _USB1010_PARA_RR1    
{
	UINT CMPP;			// ��ʾ�߼�/ʵλ��������COMP+�Ĵ����Ĵ�С��ϵ 1���߼�/ʵλ��������COMP+ 0���߼�/ʵλ��������COMP+
	UINT CMPM;			// ��ʾ�߼�/ʵλ��������COMP-�Ĵ����Ĵ�С��ϵ 1���߼�/ʵλ��������COMP- 0���߼�/ʵλ��������COMP-
	UINT ASND;			// �ڼ�/���������м���ʱ��Ϊ1
	UINT CNST;			// �ڼ�/���������ж���ʱ��Ϊ1
	UINT DSND;			// �ڼ�/���������м���ʱ��Ϊ1
	UINT AASND;			// ��S���߼�/���������У����ٶ�/���ٶ�����ʱ��Ϊ1 
	UINT ACNST;			// ��S���߼�/���������У����ٶ�/���ٶȲ���ʱ��Ϊ1 
	UINT ADSND;			// ��S���߼�/���������У����ٶ�/���ٶȼ���ʱ��Ϊ1 
	UINT STOP0;			// �ⲿֹͣ�ź�STOP0��Чʹ����ֹͣʱ��Ϊ1
	UINT STOP1;			// �ⲿֹͣ�ź�STOP1��Чʹ����ֹͣʱ��Ϊ1
	UINT LMTP;			// �ⲿ�����������ź�(nLMTP)��Чʹ����ֹͣʱ��Ϊ1
	UINT LMTM;			// �ⲿ�����������ź�(nLMTM)��Чʹ����ֹͣʱ��Ϊ1
	UINT ALARM;			// �ⲿ�ŷ���ﱨ���ź�(nALARM)��Чʹ����ֹͣʱ��Ϊ1
	UINT EMG;			// �ⲿ����ֹͣ�ź�(EMGN)ʹ����ֹͣʱ��Ϊ1
} USB1010_PARA_RR1,*PUSB1010_PARA_RR1;
#endif

// ״̬�Ĵ���RR2��ÿһ���ᶼ��RR2�Ĵ��������ĸ�Ҫָ�����
#ifndef _USB1010_PARA_RR2
typedef struct _USB1010_PARA_RR2     
{
	UINT SLMTP;			// ���������������λ���������������У��߼�/ʵλ����������COMP+�Ĵ���ֵʱ��Ϊ1
	UINT SLMTM;			// ���÷����������λ���ڷ����������У��߼�/ʵλ������С��COMP-�Ĵ���ֵʱ��Ϊ1
	UINT HLMTP;			// �ⲿ�����������ź�(nLMTP)������Ч��ƽʱ��Ϊ1
	UINT HLMTM;			// �ⲿ�����������ź�(nLMTM)������Ч��ƽʱ��Ϊ1
	UINT ALARM;			// �ⲿ�ŷ���ﱨ���ź�(nALARM)����Ϊ��Ч��������Ч״̬ʱ��Ϊ1
	UINT EMG;			// �ⲿ����ֹͣ�źŴ��ڵ͵�ƽʱ��Ϊ1
} USB1010_PARA_RR2,*PUSB1010_PARA_RR2;
#endif

// ״̬�Ĵ���RR3
#ifndef _USB1010_PARA_RR3
typedef struct _USB1010_PARA_RR3      
{
	UINT XSTOP0;		// �ⲿֹͣ�ź�XSTOP0�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT XSTOP1;		// �ⲿֹͣ�ź�XSTOP0�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT EMG;			// �ⲿ����ֹͣ�ź�EMG�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT XEXPP;			// �ⲿ������㶯�����ź�XEXPP�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT XEXPM;			// �ⲿ������㶯�����ź�XEXPM�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT XINPOS;		// �ⲿ�ŷ������λ�ź�XINPOS�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT XALARM;		// �ⲿ�ŷ���ﱨ���ź�XALARM�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT XIN0;			// �ⲿ�����ź�XIN0�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT XIN1;			// �ⲿ�����ź�XIN1�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT XLMTP;			// �ⲿ�����������ź�XLMTP�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT XLMTM;			// �ⲿ�����������ź�XLMTM�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ

} USB1010_PARA_RR3,*PUSB1010_PARA_RR3;
#endif

// ״̬�Ĵ���RR4
#ifndef _USB1010_PARA_RR4
typedef struct _USB1010_PARA_RR4      
{
	UINT YSTOP0;		// �ⲿֹͣ�ź�YSTOP0�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT YSTOP1;		// �ⲿֹͣ�ź�YSTOP1�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT YEXPP;			// �ⲿ������㶯�����ź�YEXPP�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT YEXPM;			// �ⲿ������㶯�����ź�YEXPM�ĵ�ƽ״̬ 1���ߵ�ƽ 0���͵�ƽ
	UINT YINPOS;		// �ⲿ�ŷ������λ�ź�YINPOS�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT YALARM;		// �ⲿ�ŷ���ﱨ���ź�YALARM�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT YIN0;			// �ⲿ�����ź�YIN0�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT YIN1;			// �ⲿ�����ź�YIN1�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT YLMTP;			// �ⲿ�����������ź�YLMTP�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
	UINT YLMTM;			// �ⲿ�����������ź�YLMTM�ĵ�ƽ״̬  1���ߵ�ƽ 0���͵�ƽ
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

//######################## �豸��������� #################################
// �����ڱ��豸�����������	
HANDLE DEVAPI FAR PASCAL USB1010_CreateDevice(       // �������
							int DeviceID);           // �豸ID��

int DEVAPI FAR PASCAL USB1010_GetDeviceCount(		// ��ȡ�豸����
							HANDLE hDevice);

BOOL DEVAPI FAR PASCAL USB1010_GetDeviceCurrentID(
							HANDLE hDevice, 		 // �豸���
							PLONG DeviceLgcID,		 // �߼�ID 
							PLONG DevicePhysID);	 // ����ID

BOOL DEVAPI FAR PASCAL USB1010_GetDevVersion(		// ��ȡ�豸�̼�������汾
							HANDLE hDevice,			// �豸������,����CreateDevice��������
							PULONG pulFmwVersion,	// �̼��汾
							PULONG pulDriverVersion);// �����汾

BOOL DEVAPI FAR PASCAL USB1010_ReleaseDevice(		 // �ͷ��豸
							HANDLE hDevice);		 // �豸���
 
BOOL DEVAPI  FAR PASCAL  USB1010_ResetDevice(		 // ��λ�豸
							HANDLE hDevice);		 // �豸���
//*******************************************************************
// ���õ���Ļ�������ģʽ�����ʡ����ٶȡ����ٶȡ���/���ٶȱ仯�ʡ���ʼ�ٶȡ����������
// �岹�����������Բ�����ꡢ�߼���������ʵ��λ�ü����������ټ�����ƫ��

BOOL DEVAPI FAR PASCAL USB1010_PulseOutMode(         // �����������ģʽ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)  
							LONG Mode);				 // ģʽ

BOOL DEVAPI FAR PASCAL USB1010_PulseInputMode(       // ������������ģʽ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)  
							LONG Mode);				 // ģʽ

BOOL DEVAPI FAR PASCAL USB1010_SetR(				 // ���ñ���(1-500)	
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)  
							LONG Data);				 // ����ֵ(1-500)

BOOL DEVAPI FAR PASCAL USB1010_SetA(				 // ���ü��ٶ�
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)     
							LONG Data);				 // ���ٶ� (125-1000000)

BOOL DEVAPI FAR PASCAL USB1010_SetDec(				 // ���ü��ٶ�
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // ���ٶ�ֵ(125-1000,000)

BOOL DEVAPI FAR PASCAL USB1010_SetAK(				 // ���ٶȱ仯��  
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)   
							LONG Data);				 // ���� (1-62500000) 

BOOL DEVAPI FAR PASCAL USB1010_SetSV(				 // ���ó�ʼ�ٶ�(1-8000)
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)   
							LONG Data);				 // �ٶ�ֵ(1-8000)

BOOL DEVAPI FAR PASCAL USB1010_SetV(				 // ���������ٶ�
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)     
							LONG Data);				 // �����ٶ�ֵ(1-8000)

BOOL DEVAPI FAR PASCAL USB1010_SetP(				 // ���ö���������
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);			     // ����������(0-268435455)

BOOL DEVAPI FAR PASCAL USB1010_SetIP(				 // ���ò岹�յ�������(-8388608-+8388607)
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // �岹�յ�������(-8388608-+8388607)

BOOL DEVAPI FAR PASCAL USB1010_SetC(                 // ����Բ������(������)  
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // Բ��������������Χ(-8388608-+8388607)

BOOL DEVAPI FAR PASCAL USB1010_SetLP(				 // �����߼�λ�ü�����
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // �߼�λ�ü�����ֵ(-2147483648-+2147483647)

BOOL DEVAPI FAR PASCAL USB1010_SetEP(				 // ����ʵλ������ 
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // ʵλ������ֵ(-2147483648-+2147483647)

BOOL DEVAPI FAR PASCAL USB1010_SetAccofst(			 // ���ü��ټ�����ƫ��
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // ƫ�Ʒ�Χ(0-65535)

//*******************************************************************
// ֱ��S���߳�ʼ������������

BOOL DEVAPI FAR PASCAL USB1010_InitLVDV(				// ��ʼ������,������������
							HANDLE hDevice,				// �豸���
							PUSB1010_PARA_DataList pDL, // ���������ṹ��ָ��
							PUSB1010_PARA_LCData pLC);	// ֱ��S���߲����ṹ��ָ��

BOOL DEVAPI FAR PASCAL USB1010_StartLVDV(				// ��������,������������
							HANDLE hDevice,				// �豸���
							LONG AxisNum);				// ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

BOOL DEVAPI FAR PASCAL	USB1010_Start2D(HANDLE hDevice);// 2��ͬʱ����						           
//*******************************************************************
// ֱ�߲岹��ʼ������������
BOOL DEVAPI FAR PASCAL USB1010_InitLineInterpolation(	// ��ʼ��ֱ�߲岹�˶� 
							HANDLE hDevice,				// �豸���
							PUSB1010_PARA_DataList pDL, // ���������ṹ��ָ��
							PUSB1010_PARA_LineData pLD);// ֱ�߲岹�ṹ��ָ��

BOOL DEVAPI FAR PASCAL USB1010_StartLineInterpolation(	// ����ֱ�߲岹�˶� 
							HANDLE hDevice);			// �豸���

//*******************************************************************
// ��������Բ���岹��ʼ������������
BOOL DEVAPI FAR PASCAL USB1010_InitCWInterpolation(		// ��ʼ����������Բ���岹�˶� 
							HANDLE hDevice,				// �豸���
							PUSB1010_PARA_DataList pDL, // ���������ṹ��ָ��
							PUSB1010_PARA_CircleData pCD);// Բ���岹�ṹ��ָ��
                         
BOOL DEVAPI FAR PASCAL USB1010_StartCWInterpolation(    // ����������Բ���岹�˶� 
							HANDLE hDevice);			// �豸���
	                                                  
BOOL DEVAPI FAR PASCAL USB1010_StartCCWInterpolation(   // ����������Բ���岹�˶� 
							HANDLE hDevice);			// �豸���

//*************************************************************************
// λ�岹��غ���
BOOL DEVAPI FAR PASCAL USB1010_InitBitInterpolation(	// ��ʼ��λ�岹����
							HANDLE hDevice,				// �豸���
							PUSB1010_PARA_DataList pDL);// ���������ṹ��ָ��

BOOL DEVAPI FAR PASCAL USB1010_AutoBitInterpolation(    // �Զ�ִ��λ�岹
							HANDLE hDevice,				// �豸���
							PSHORT pBuffer,				// λ�岹����ָ��	
							UINT nCount);				// ��������

BOOL DEVAPI FAR PASCAL USB1010_ReleaseBitInterpolation(	// �ͷ�λ�岹
							HANDLE hDevice);			// �豸���

BOOL DEVAPI FAR PASCAL USB1010_SetBP(                   // ����λ�岹����
							HANDLE hDevice,				// �豸��� 
							LONG BP1PData,				// X����������������
							LONG BP1MData,				// X�ᷴ������������
							LONG BP2PData,				// Y����������������
							LONG BP2MData);				// Y�ᷴ������������

BOOL DEVAPI FAR PASCAL USB1010_StartBitInterpolation(	// ����λ�岹
							HANDLE hDevice);			// �豸���

BOOL DEVAPI FAR PASCAL  USB1010_BPWait(					// �ȴ�λ�岹����һ�������趨
							HANDLE hDevice);			// �豸���

BOOL DEVAPI FAR PASCAL USB1010_ClearBPData(				// ���BP�Ĵ�������
							HANDLE hDevice);			// �豸���

//*******************************************************************
// �����岹��غ���
							
BOOL DEVAPI FAR PASCAL  USB1010_NextWait(				// �ȴ������岹��һ���ڵ������趨
							HANDLE hDevice);			// �豸���

//*******************************************************************
// �ⲿ�ź��������������������������

BOOL DEVAPI FAR PASCAL USB1010_SetOutEnableDV(		 // �ⲿ���ƶ�������(�½�����Ч)
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
		                    
BOOL DEVAPI FAR PASCAL USB1010_SetOutEnableLV(		 // �ⲿ������������(���ֵ͵�ƽ��Ч)
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

//*******************************************************************
// ���������λ��Ч����Ч

BOOL DEVAPI FAR PASCAL USB1010_SetPDirSoftwareLimit( // ���������������λ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG LogicFact,			 // �߼�/ʵλ������ѡ�� USB1010_LOGIC���߼�λ�ü����� USB1010_FACT��ʵλ������	
							LONG Data);				 // �����λ����

BOOL DEVAPI FAR PASCAL USB1010_SetMDirSoftwareLimit( // ���÷����������λ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG LogicFact,			 // �߼�/ʵλ������ѡ�� USB1010_LOGIC���߼�λ�ü����� USB1010_FACT��ʵλ������	
							LONG Data);				 

BOOL DEVAPI FAR PASCAL USB1010_ClearSoftwareLimit(	 // ��������λ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)

//******************************************************************* 
// �����ⲿ�����źŵ���Ч����Ч		
BOOL DEVAPI FAR PASCAL USB1010_SetLMTEnable(		 // �����ⲿԽ���źŵ���Ч��ֹͣ��ʽ	
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG StopMode);          // USB1010_DECSTOP������ֹͣ��USB1010_SUDDENSTOP������ֹͣ

BOOL DEVAPI FAR PASCAL USB1010_SetStopEnable(		 // �����ⲿֹͣ�ź���Ч
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG StopNum);			 // ֹͣ��

BOOL DEVAPI FAR PASCAL USB1010_SetStopDisable(		 // �����ⲿֹͣ�ź���Ч
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);   		 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
											
BOOL DEVAPI FAR PASCAL USB1010_SetALARMEnable(       // �����ŷ������ź���Ч 
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)  

BOOL DEVAPI FAR PASCAL USB1010_SetALARMDisable(      // �����ŷ������ź���Ч  
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)  

BOOL DEVAPI FAR PASCAL USB1010_SetINPOSEnable(		 // �����ŷ���ﶨλ��������ź���Ч 
							HANDLE hDevice,			 // �豸���	
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

BOOL DEVAPI FAR PASCAL USB1010_SetINPOSDisable(		 // �����ŷ���ﶨλ��������ź���Ч
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

//*******************************************************************
// ���ٺ�������

BOOL DEVAPI FAR PASCAL USB1010_DecValid(			 // ������Ч
							HANDLE hDevice);		 // �豸���

BOOL DEVAPI FAR PASCAL USB1010_DecInvalid(			 // ������Ч
							HANDLE hDevice);		 // �豸���

BOOL DEVAPI FAR PASCAL USB1010_DecStop(				 // ����ֹͣ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)  

BOOL DEVAPI FAR PASCAL USB1010_InstStop(			 // ����ֹͣ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

BOOL DEVAPI FAR PASCAL USB1010_AutoDec(				 // �Զ�����
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

BOOL DEVAPI FAR PASCAL USB1010_HanDec(				 // �ֶ����ٵ��趨
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Data);				 // �ֶ����ٵ����ݣ���Χ(0 - 268435455)

//*************************************************************************
// �����״̬���߼���������ʵ��λ�ü���������ǰ�ٶȡ���/���ٶ�
LONG DEVAPI FAR PASCAL USB1010_ReadLP(				 // ���߼�������
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

LONG DEVAPI FAR PASCAL USB1010_ReadEP(				 // ��ʵλ������
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

LONG DEVAPI FAR PASCAL USB1010_ReadCV(				 // ����ǰ�ٶ�
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

LONG DEVAPI FAR PASCAL USB1010_ReadCA(				 // ����ǰ���ٶ�
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 

//*******************************************************************
// ��״̬�Ĵ�����λ״̬

LONG DEVAPI FAR PASCAL USB1010_ReadRR(				 // ��RR�Ĵ���
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							LONG Num);				 // �Ĵ�����

BOOL DEVAPI FAR PASCAL USB1010_GetRR0Status(		 // �����״̬�Ĵ���RR0��λ״̬
							HANDLE hDevice,			 // �豸���
							PUSB1010_PARA_RR0 pPara);// RR0�Ĵ���״̬

BOOL DEVAPI FAR PASCAL USB1010_GetRR1Status(		 // ���״̬�Ĵ���RR1��λ״̬
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							PUSB1010_PARA_RR1 pPara);// RR1�Ĵ���״̬			

BOOL DEVAPI FAR PASCAL USB1010_GetRR2Status(		 // ���״̬�Ĵ���RR2��λ״̬
							HANDLE hDevice,			 // �豸���
							LONG AxisNum,			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��) 
							PUSB1010_PARA_RR2 pPara);// RR2�Ĵ���״̬			

BOOL DEVAPI FAR PASCAL USB1010_GetRR3Status(		 // ���״̬�Ĵ���RR3��λ״̬
							HANDLE hDevice,			 // �豸���
							PUSB1010_PARA_RR3 pPara);// RR3�Ĵ���״̬			

BOOL DEVAPI FAR PASCAL USB1010_GetRR4Status(		 // ���״̬�Ĵ���RR4��λ״̬
							HANDLE hDevice,			 // �豸���
							PUSB1010_PARA_RR4 pPara);// RR4�Ĵ���״̬
		
//*******************************************************************
// ����ͨ������Ͷ�ͨ������
BOOL DEVAPI FAR PASCAL USB1010_SetOutput(				 // ����ͨ�������ƽ
							HANDLE hDevice,			 // �豸���
						    LONG XOut1,				 // X��OUT1 1��XOUT1Ϊ�ߵ�ƽ  0��XOUT0Ϊ�͵�ƽ  
							LONG XOut0,				 // X��OUT0 1��XOUT1Ϊ�ߵ�ƽ  0��XOUT0Ϊ�͵�ƽ
							LONG YOut1,				 // Y��OUT1 1��YOUT1Ϊ�ߵ�ƽ  0��YOUT0Ϊ�͵�ƽ  
							LONG YOut0);			 // Y��OUT0 1��YOUT1Ϊ�ߵ�ƽ  0��YOUT0Ϊ�͵�ƽ

LONG DEVAPI FAR PASCAL USB1010_ReadTYPE(			 // ��ͨ�������źŵ�ƽ
							HANDLE hDevice,			 // �豸���
							LONG AxisNum);			 // ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)

//*******************************************************************
#ifdef __cplusplus
}
#endif
// �Զ������������������

