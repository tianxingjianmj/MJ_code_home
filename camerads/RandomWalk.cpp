#include "RandomWalk.h"
#include "AD.h"
#include "RobotCar.h"

RandomWalk::RandomWalk(){
	action = 0; // stop
	iCarStatus = 0; // not moving
	hSysStatus = CreateEvent(NULL, TRUE, FALSE, NULL);
	hCollectData = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)collectData,
		NULL,0,NULL);
	hProccessData = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)processData,
		NULL,0,NULL);
}

RandomWalk::~RandomWalk(){
	TerminateThread(hCollectData, 0);
	TerminateThread(hProccessData, 0);
}
UINT RandomWalk::collectData(LPVOID lparam){
	AD obj;
	while(TRUE){
		obj.readData();
		obj.getDistance(arrayDistance, 8);
		for(int i=0; i< 8; i++){
			if(arrayDistance[i] <= 5.0){
				SetEvent(hSysStatus);
				continue;
			}
		}
		obj.getVoltage(arrayVoltage, 2);
	}
	return 0;
}

UINT RandomWalk::processData(LPVOID lparam){
	RobotCar obj;
	struct MotorValue stValue;
	stValue.acceleration1 = 1000;
	stValue.acceleration1k = 1000;
	stValue.deceleration1 = 2000;
	stValue.drivespeed1 = 8000;
	stValue.multiplerate1 = 20;
	stValue.startspeed1 = 10;

	stValue.acceleration2 = 1000;
	stValue.acceleration2k = 1000;
	stValue.deceleration2 = 2000;
	stValue.drivespeed2 = 8000;
	stValue.multiplerate2 = 20;
	stValue.startspeed2 = 10;
	while(TRUE){
		WaitForSingleObject(hSysStatus,INFINITE);
		// check distance and direction
		// stop, choose a new direction randomly
		if(action == 0 ){
			// choose action
			if(arrayDistance[0]>=81){
				obj.Forward_Go(stValue);
			}else if(arrayDistance[5]>=81){
				obj.Back_Go(stValue);
			}else{
				// need to turn a direction
			}
		}else if(action == 1 && arrayDistance[0] <= 5.0){
			// stop
			obj.Stop_Im();
			// choose action
			if(arrayDistance[5] >= 81){
				obj.Back_Go(stValue);
			}else{
				// need to turn a direction
			}
		}else if(action == 2 && arrayDistance[5] <= 5.0){
			// stop
			obj.Stop_Im();
			// choose action
			if(arrayDistance[0] >= 81){
				obj.Forward_Go(stValue);
			}else{
				// need to turn a direction
			}
		}else if(action == 3 ){
			// 
		}else if(action == 4){
			//
		}
	}
	return 0;
}

int RandomWalk::chooseAction(int curAction){
	return 0;
}

