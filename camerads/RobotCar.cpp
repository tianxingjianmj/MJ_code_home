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
			stMotorValue.acceleration1 = 1000; //加速度
			stMotorValue.acceleration1k = 1000; // 加速度变化率
			stMotorValue.deceleration1 = 1000; // 减速度
			stMotorValue.drivespeed1 = 1000;  // 行驶速度
			stMotorValue.multiplerate1 = 100;  // 倍率
			stMotorValue.startspeed1 = 100;   // 初始速度
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
	LCX.AxisNum = USB1010_XAXIS;			// 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)
	LCX.LV_DV= USB1010_LV;					/* 驱动方式 USB1010_DV:定长驱动 USB1010_LV: 连续驱动 */
	LCX.Mode = USB1010_CPDIR;				// 模式0：CW/CCW方式，1：CP/DIR方式 
	LCX.Line_Curve = USB1010_CURVE;			// 直线曲线(0:直线加/减速; 1:S曲线加/减速)
	DLX.Multiple=stMotorValue.multiplerate1;							// 倍数 (1~500) 
	DLX.Acceleration = stMotorValue.acceleration1;				// 加速度(125~1000,000)(直线加减速驱动中加速度一直不变）
	DLX.AccelerationK = stMotorValue.acceleration1k;				// 加速度变化率(仅S曲线驱动时有效)
	DLX.StartSpeed = stMotorValue.startspeed1 ;					// 初始速度(1~8000)
	DLX.DriveSpeed = stMotorValue.drivespeed1;					// 驱动速度	(1~8000)	
	LCX.nPulseNum = 10000 ;				// 定量输出脉冲数(0~268435455)
	switch(action){
	case 0:  // back
		LCX.Direction = USB1010_PDIRECTION ;
		break;
	case 1: // forward
		LCX.Direction = USB1010_MDIRECTION;
		break;
	case 2: // left
		LCX.Direction = USB1010_PDIRECTION ;	// 转动方向 USB1010_PDirection: 正转  USB1010_MDirection:反转
		break;
	case 3:// right
		LCX.Direction = USB1010_MDIRECTION ;	// 转动方向 USB1010_PDirection: 正转  USB1010_MDirection:反转
		break;
	default:
		break;
	}

	LCY.AxisNum = USB1010_YAXIS;			// 轴号(USB1010_XAXIS:X轴; USB1010_YAXIS:Y轴)
	LCY.LV_DV= USB1010_LV;					// 驱动方式 USB1010_DV:定长驱动 USB1010_LV: 连续驱动
	LCY.Mode = USB1010_CPDIR;				// 模式USB1010_CWCCW：CW/CCW方式,USB1010_CPDIR：CP/DIR方式 
	LCY.Line_Curve = USB1010_CURVE;			// 直线曲线(0:直线加/减速; 1:S曲线加/减速)
	DLY.Multiple=stMotorValue.multiplerate2;							// 倍数 (1~500) 
	DLY.Acceleration = stMotorValue.acceleration2;				// 加速度(125~1000,000)(直线加减速驱动中加速度一直不变）
	DLY.AccelerationK = stMotorValue.acceleration2k;				// 加速度变化率(仅S曲线驱动时有效)
	DLY.StartSpeed = stMotorValue.startspeed2 ;					// 初始速度(1~8000)
	DLY.DriveSpeed = stMotorValue.drivespeed2 ;					// 驱动速度	(1~8000)	
	LCY.nPulseNum = 10000 ;				// 定量输出脉冲数(0~268435455)
	switch(action){
	case 0: // back
		LCY.Direction = USB1010_MDIRECTION ;	// 转动方向 USB1010_PDirection: 正转  USB1010_MDirection:反转
		break;
	case 1: // forward
		LCY.Direction = USB1010_PDIRECTION;
		break;
	case 2: // left
		LCY.Direction = USB1010_PDIRECTION ;	// 转动方向 USB1010_PDirection: 正转  USB1010_MDirection:反转
		break;
	case 3: // right
		LCY.Direction = USB1010_MDIRECTION ;	// 转动方向 USB1010_PDirection: 正转  USB1010_MDirection:反转	
		break;
	default:
		break;
	}
	USB1010_SetLP(hDevice, LCX.AxisNum, 0); // 设置逻辑位置计数器
	USB1010_SetLP(hDevice, LCY.AxisNum, 0); // 设置逻辑位置计数器 
	USB1010_SetEP(	hDevice, LCX.AxisNum, 0);	
	USB1010_SetEP(hDevice,LCY.AxisNum, 0);	// 设置实位计数器 
	USB1010_PulseInputMode(hDevice,USB1010_XAXIS,USB1010_A_B);
	USB1010_PulseInputMode(hDevice,USB1010_YAXIS,USB1010_A_B);
	if(!USB1010_InitLVDV(hDevice,&DLX, &LCX)){
		printf("初始化X轴直线运动失败...\n");
		return;
	}
	if(!USB1010_InitLVDV(hDevice,&DLY, &LCY)){
		printf("初始化Y轴直线运动失败...\n");
		return;
	}			
	if(!USB1010_Start2D( hDevice)){
		printf("初始化双轴失败...\n");
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