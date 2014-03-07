#include "AD.h"
#include "RobotCar.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>


int main(){
	int start = 0;
	int finish = 0;
	start = clock();
	int level = 1; // valid value:1,2,3,4,5
	RobotCar objRobotCar = RobotCar::RobotCar(level);	
	//	Sleep(20000);
	//	objRobotCar.Left_Go();
	//	objRobotCar.Right_Go();
	//    objRobotCar.Forward_Go(2);
	objRobotCar.Back_Go(2);
	while(true){
		printf("running\n");
		finish = clock();		
		if((finish - start) >= 10000)
			break;
	}
	printf("stop back.............................................................\n");
	objRobotCar.Stop_Slow();
	printf("done!\n");

	
	start = clock();
	objRobotCar.Forward_Go(2);
	while(true){
		printf("running\n");
		finish = clock();		
		if((finish - start) >= 2000)
			break;
	}
	printf("stop.  forward............................................................\n");
	objRobotCar.Stop_Slow();
	printf("done!\n");



	
	
	start = clock();
	objRobotCar.Left_Go(2);
	while(true){
		printf("running\n");
		finish = clock();		
		if((finish - start) >= 2000)
			break;
	}
	printf("stop. left............................................................\n");
	objRobotCar.Stop_Slow();
	printf("done!\n");

	

	start = clock();
	objRobotCar.Right_Go(2);
	while(true){
		printf("running\n");
		finish = clock();		
		if((finish - start) >= 2000)
			break;
	}
	printf("stop..right...........................................................\n");
	objRobotCar.Stop_Slow();
	printf("done!\n");
	getchar();
}
