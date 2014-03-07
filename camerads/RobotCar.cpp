#include "RobotCar.h"
#include "stdio.h"
#pragma comment(lib,"USB1010.lib")
// level indicates running speed of the motor
// 1~5, increase 

RobotCar::RobotCar(int level){
	configParam(level);
}
RobotCar:: RobotCar (){
	stMotorValue.multiplerate1  =  20;
	stMotorValue.startspeed1	   =  10;
	stMotorValue.drivespeed1	   =  8000;
	stMotorValue.acceleration1  =  2500;
	stMotorValue.acceleration1k =  1000;
	stMotorValue.deceleration1  =  1000;

	stMotorValue.multiplerate2  =  20;
	stMotorValue.startspeed2	   =  10;
	stMotorValue.drivespeed2	   =  8000;
	stMotorValue.acceleration2  =  2500;
	stMotorValue.acceleration2k =  1000;
	stMotorValue.deceleration2  =  1000;
	hDevice =  USB1010_CreateDevice(0);
	if(hDevice == NULL){
		printf("Can not create device...\n");
		exit(0);
	}
}

RobotCar:: RobotCar(struct MotorValue stMotorValue){
	this->stMotorValue.multiplerate1  =  stMotorValue.multiplerate1;
	this->stMotorValue.startspeed1	   =  stMotorValue.startspeed1;
	this->stMotorValue.drivespeed1	   =  stMotorValue.drivespeed1;
	this->stMotorValue.acceleration1  =  stMotorValue.acceleration1;
	this->stMotorValue.acceleration1k =  stMotorValue.acceleration1k;
	this->stMotorValue.deceleration1  =  stMotorValue.deceleration1;

	this->stMotorValue.multiplerate2  =  stMotorValue.multiplerate2;
	this->stMotorValue.startspeed2	   =  stMotorValue.startspeed2;
	this->stMotorValue.drivespeed2	   =  stMotorValue.drivespeed2;
	this->stMotorValue.acceleration2  =  stMotorValue.acceleration2;
	this->stMotorValue.acceleration2k =  stMotorValue.acceleration2k;
	this->stMotorValue.deceleration2  =  stMotorValue.deceleration2;
	hDevice =  USB1010_CreateDevice(0);
	if(hDevice == NULL){
		printf("Can not create device...\n");
		exit(0);
	}
}

RobotCar:: ~RobotCar(){
	USB1010_ReleaseDevice(hDevice);
}
void RobotCar::configParam(int level){
	switch(level){
		case 1:  // slow....
			stMotorValue.acceleration1 = 1000; //���ٶ�
			stMotorValue.acceleration1k = 1000; // ���ٶȱ仯��
			stMotorValue.deceleration1 = 1000; // ���ٶ�
			stMotorValue.drivespeed1 = 1000;  // ��ʻ�ٶ�
			stMotorValue.multiplerate1 = 100;  // ����
			stMotorValue.startspeed1 = 100;   // ��ʼ�ٶ�
			stMotorValue.acceleration2 = 1000;
			stMotorValue.acceleration2k = 1000;
			stMotorValue.deceleration2 = 1000;
			stMotorValue.drivespeed2 = 1000;
			stMotorValue.multiplerate2 = 100;
			stMotorValue.startspeed2 = 100;
			break;
		case 2:
			stMotorValue.acceleration1 = 1400;
			stMotorValue.acceleration1k = 1000;
			stMotorValue.deceleration1 = 1400;
			stMotorValue.drivespeed1 = 1500;
			stMotorValue.multiplerate1 = 100;
			stMotorValue.startspeed1 = 100;
			stMotorValue.acceleration2 = 1400;
			stMotorValue.acceleration2k = 1000;
			stMotorValue.deceleration2 = 1400;
			stMotorValue.drivespeed2 = 1500;
			stMotorValue.multiplerate2 = 100;
			stMotorValue.startspeed2 = 100;
			break;
		case 3:
			stMotorValue.acceleration1 = 1400;
			stMotorValue.acceleration1k = 1000;
			stMotorValue.deceleration1 = 1400;
			stMotorValue.drivespeed1 = 2000;
			stMotorValue.multiplerate1 = 100;
			stMotorValue.startspeed1 = 100;
			stMotorValue.acceleration2 = 1400;
			stMotorValue.acceleration2k = 1000;
			stMotorValue.deceleration2 = 1400;
			stMotorValue.drivespeed2 = 2000;
			stMotorValue.multiplerate2 = 100;
			stMotorValue.startspeed2 = 100;
			break;
		case 4:
			stMotorValue.acceleration1 = 1500;
			stMotorValue.acceleration1k = 1000;
			stMotorValue.deceleration1 = 1500;
			stMotorValue.drivespeed1 = 2500;
			stMotorValue.multiplerate1 = 100;
			stMotorValue.startspeed1 = 100;
			stMotorValue.acceleration2 = 1500;
			stMotorValue.acceleration2k = 1000;
			stMotorValue.deceleration2 = 1500;
			stMotorValue.drivespeed2 = 2500;
			stMotorValue.multiplerate2 = 100;
			stMotorValue.startspeed2 = 100;
			break;
		case 5:
			stMotorValue.acceleration1 = 1500;
			stMotorValue.acceleration1k = 1000;
			stMotorValue.deceleration1 = 1500;
			stMotorValue.drivespeed1 = 3000;
			stMotorValue.multiplerate1 = 100;
			stMotorValue.startspeed1 = 100;
			stMotorValue.acceleration2 = 1500;
			stMotorValue.acceleration2k = 1000;
			stMotorValue.deceleration2 = 1500;
			stMotorValue.drivespeed2 = 3000;
			stMotorValue.multiplerate2 = 100;
			stMotorValue.startspeed2 = 100;
			break;
		default:
			printf("Invalid parameter settting, please check the level parameter...\n");
			break;
	}
	
	hDevice =  USB1010_CreateDevice(0);
	if(hDevice == NULL){
		printf("Can not create device...\n");
		exit(0);
	}
}
void RobotCar::setParam(int action){
	LCX.AxisNum = USB1010_XAXIS;			// ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)
	LCX.LV_DV= USB1010_LV;					/* ������ʽ USB1010_DV:�������� USB1010_LV: �������� */
	LCX.Mode = USB1010_CPDIR;				// ģʽ0��CW/CCW��ʽ��1��CP/DIR��ʽ 
	LCX.Line_Curve = USB1010_CURVE;			// ֱ������(0:ֱ�߼�/����; 1:S���߼�/����)
	DLX.Multiple=stMotorValue.multiplerate1;							// ���� (1~500) 
	DLX.Acceleration = stMotorValue.acceleration1;				// ���ٶ�(125~1000,000)(ֱ�߼Ӽ��������м��ٶ�һֱ���䣩
	DLX.AccelerationK = stMotorValue.acceleration1k;				// ���ٶȱ仯��(��S��������ʱ��Ч)
	DLX.StartSpeed = stMotorValue.startspeed1 ;					// ��ʼ�ٶ�(1~8000)
	DLX.DriveSpeed = stMotorValue.drivespeed1;					// �����ٶ�	(1~8000)	
	LCX.nPulseNum = 10000 ;				// �������������(0~268435455)
	switch(action){
	case 0:  // back
		LCX.Direction = USB1010_PDIRECTION ;
		break;
	case 1: // forward
		LCX.Direction = USB1010_MDIRECTION;
		break;
	case 2: // left
		LCX.Direction = USB1010_PDIRECTION ;	// ת������ USB1010_PDirection: ��ת  USB1010_MDirection:��ת
		break;
	case 3:// right
		LCX.Direction = USB1010_MDIRECTION ;	// ת������ USB1010_PDirection: ��ת  USB1010_MDirection:��ת
		break;
	default:
		break;
	}

	LCY.AxisNum = USB1010_YAXIS;			// ���(USB1010_XAXIS:X��; USB1010_YAXIS:Y��)
	LCY.LV_DV= USB1010_LV;					// ������ʽ USB1010_DV:�������� USB1010_LV: ��������
	LCY.Mode = USB1010_CPDIR;				// ģʽUSB1010_CWCCW��CW/CCW��ʽ,USB1010_CPDIR��CP/DIR��ʽ 
	LCY.Line_Curve = USB1010_CURVE;			// ֱ������(0:ֱ�߼�/����; 1:S���߼�/����)
	DLY.Multiple=stMotorValue.multiplerate2;							// ���� (1~500) 
	DLY.Acceleration = stMotorValue.acceleration2;				// ���ٶ�(125~1000,000)(ֱ�߼Ӽ��������м��ٶ�һֱ���䣩
	DLY.AccelerationK = stMotorValue.acceleration2k;				// ���ٶȱ仯��(��S��������ʱ��Ч)
	DLY.StartSpeed = stMotorValue.startspeed2 ;					// ��ʼ�ٶ�(1~8000)
	DLY.DriveSpeed = stMotorValue.drivespeed2 ;					// �����ٶ�	(1~8000)	
	LCY.nPulseNum = 10000 ;				// �������������(0~268435455)
	switch(action){
	case 0: // back
		LCY.Direction = USB1010_MDIRECTION ;	// ת������ USB1010_PDirection: ��ת  USB1010_MDirection:��ת
		break;
	case 1: // forward
		LCY.Direction = USB1010_PDIRECTION;
		break;
	case 2: // left
		LCY.Direction = USB1010_PDIRECTION ;	// ת������ USB1010_PDirection: ��ת  USB1010_MDirection:��ת
		break;
	case 3: // right
		LCY.Direction = USB1010_MDIRECTION ;	// ת������ USB1010_PDirection: ��ת  USB1010_MDirection:��ת	
		break;
	default:
		break;
	}
	USB1010_SetLP(hDevice, LCX.AxisNum, 0); // �����߼�λ�ü�����
	USB1010_SetLP(hDevice, LCY.AxisNum, 0); // �����߼�λ�ü����� 
	USB1010_SetEP(	hDevice, LCX.AxisNum, 0);	
	USB1010_SetEP(hDevice,LCY.AxisNum, 0);	// ����ʵλ������ 
	USB1010_PulseInputMode(hDevice,USB1010_XAXIS,USB1010_A_B);
	USB1010_PulseInputMode(hDevice,USB1010_YAXIS,USB1010_A_B);
	if(!USB1010_InitLVDV(hDevice,&DLX, &LCX)){
		printf("��ʼ��X��ֱ���˶�ʧ��...\n");
		return;
	}
	if(!USB1010_InitLVDV(hDevice,&DLY, &LCY)){
		printf("��ʼ��Y��ֱ���˶�ʧ��...\n");
		return;
	}			
	if(!USB1010_Start2D( hDevice)){
		printf("��ʼ��˫��ʧ��...\n");
		return;
	}	
	
}

int RobotCar::Back_Go(int level){
	configParam(level);
	int action = 0;
	setParam(action);
	return 0;
}
int RobotCar::Forward_Go(int level){
	configParam(level);
	int action = 1;
	setParam(action);
	return 0;
}

int RobotCar::LaseRador(){
	return 0;
}
int RobotCar::Left_Go(int level){
	configParam(level);
	int action = 2;
	setParam(action);	
	return 0;
}
int RobotCar::Right_Go(int level){
	configParam(level);
	int action = 3;
	setParam(action);	 
	return 0;
}
int RobotCar::Stop_Im(){	
	if(!USB1010_InstStop(hDevice, 3)){
		printf("Imidiately stop failed.............\n");
	}
	return 0;
}

int RobotCar::Stop_Slow(){
	if(!USB1010_DecStop(hDevice, USB1010_XYAXIS)){
		printf("Slow stop failed!\n");
	}
	return 0;
}