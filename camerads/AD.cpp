#include "AD.h"
#include "stdio.h"

AD:: AD(){
	ADPara.FirstChannel = 0;				           // 首通道
	ADPara.LastChannel  = 9;						   // 末通道
	ADPara.GroundingMode = 0 ;                         // 单端方式
	ADPara.InputRange = 3;                             // 量程 0~+10V  
	ADPara.Gains=0;                                    // 1倍增益          
	hDeviceAD = USB5935_CreateDevice(0);  
	if(hDeviceAD == INVALID_HANDLE_VALUE)
	{
		printf("警告!","创建数据采集设备失败！...");  
	}
	printf("Hello world!........");
}
AD:: ~AD(){
	if(hDeviceAD != INVALID_HANDLE_VALUE)  
	{
		USB5935_ReleaseDevice(hDeviceAD);
	}
	printf("bye!........");
}

int AD::getDistance(double array[], int len){
	for(int i=0;i<len;i++){
		array[i] = arrDistance[i];
	}
	return 0;
}
int AD::getVoltage(double array[], int len){
	for(int i=0;i<len;i++){
		array[i] = arrVoltage[i];
	}
	return 0;
}
int AD::readData(){

	BOOL ReadCount;
	long ReadIndex = 0;
	long ReadSizeWords = 0;
	long nRetWords = 0;
	int bDeviceRun = 0;
	int WaveOrDight = 0;
	int CurrentIndex = 0;
	long gl_ReadSizeWords = 0;
	int nChannelCount = 0;
	int nRemainder = 0;
//	long ReadSizeWords;
	long nChannelSize = 0;
	int PerHeight = 0;
	int Original = 0;
	double PerPixelLsb = 0;
	float PerLsbVolt = 0;
	double dtemp = 0;
	int TreatChannel = 0;
	int Index = 0;
	float bInputRange = 0;
	double Volt[16384];
	double distance[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	double Sdistance0[8] = {1608,1791,1867,1895,1972,1942,1948,1957};
	double Sdistance1[8] = {3597,3791,3861,3899,3910,3918,3924,3936}; 
	double Sdistance2[8] = {5557,5757,5841,5876,5907,5917,5929,5940}; 
	double Sdistance3[8] = {7556,7771,7850,7884,7909,7927,7940,7949}; 
	double Sdistance4[8] = {9565,9776,9855,9894,9918,9934,9946,9950}; 
	double Sdistance5[8] = {11559,11773,11860,11901,11918,11939,11952,11960}; 
	double Sdistance6[8] = {13589,13775,13857,13899,13923,13939,13948,13957}; 
	double Sdistance7[8] = {15557,15767,15841,15891,15913,15930,15942,15962}; 
	
	bInputRange = 20000.0;
	gl_ReadSizeWords = 8192;
	nChannelCount = ADPara.LastChannel - ADPara.FirstChannel + 1 ; 
	nRemainder = gl_ReadSizeWords % (nChannelCount * 256);
	ReadSizeWords = gl_ReadSizeWords - nRemainder;
	nChannelSize =  ReadSizeWords / nChannelCount;
	PerHeight=(long)(20000/ nChannelCount);	
	
	Original =(long) (PerHeight / 2);
	PerPixelLsb = 8192.0 / PerHeight; 
	PerLsbVolt = bInputRange/8192;
	for (int i=0;i<MAX_SEGMENT;i++)												  
	{
		bNewSegmentData[i]=FALSE; 
	}
	CurrentIndex = 0;
	if(hDeviceAD == INVALID_HANDLE_VALUE){
		hDeviceAD = USB5935_CreateDevice(0);
		if (hDeviceAD == INVALID_HANDLE_VALUE)
		{
			printf("数据采集失败：未能成功创建设备......");
			return -1;
		}
	}
	
	
	USB5935_InitDeviceAD(hDeviceAD, &ADPara);  // 用Para参数初始化设备
	ReadCount=USB5935_ReadDeviceAD(hDeviceAD, pADBuffer[ReadIndex], ReadSizeWords,&nRetWords); 

	if(ReadCount == 1){
		// to be defined
	}else{
		printf("警告！读数据未知错误！");
		return -1;
	}

	if (bNewSegmentData[ReadIndex]==TRUE)
	{
		bDeviceRun = 0;
		printf("警告！缓冲区溢出..........");
		return -2;
	}
	bNewSegmentData[ReadIndex] = TRUE;
	

	// process data
	if (bNewSegmentData[CurrentIndex]==TRUE)
	{
		if (WaveOrDight == 0)
		{
			Original = PerHeight / 2;

			for(TreatChannel=0;TreatChannel<nChannelCount;TreatChannel++)
			{
				for(Index=0; Index<nChannelSize; Index++)   // 转换每个通道长度的数据，将采集的AD数据转换成电压值(mV)
				{
					Volt[Index] = Original-(((((pADBuffer[CurrentIndex][Index*nChannelCount+TreatChannel]))& 0x1FFF)- 4096) /PerPixelLsb); 
				} 

				for(Index=0; Index<nChannelSize; Index++)
				{
					distance[TreatChannel] = distance[TreatChannel] + Volt[Index];	 
				}	 
				
				////////////////////////////////////////////
				distance[TreatChannel] = distance[TreatChannel] /nChannelSize;

				//////////////////////////////////////////////////////////////// 
				Original = Original + PerHeight;
			} 

			dtemp = distance[0];
			if (dtemp<Sdistance0[0])
				distance[0] = 0;
			else if ( (dtemp>=Sdistance0[0])&&(dtemp<Sdistance0[1]))
				distance[0] = 0.054*dtemp-77.86;
			else if ( (dtemp>=Sdistance0[1])&&(dtemp<Sdistance0[2]))
				distance[0] = 0.131*dtemp-215.6;  
			else if ( (dtemp>=Sdistance0[2])&&(dtemp<Sdistance0[3]))
				distance[0] = 0.357*dtemp-636.7; 				 
			else if ( (dtemp>=Sdistance0[3])&&(dtemp<Sdistance0[4]))
				distance[0] = 0.312*dtemp-552.1; 
			else if ( (dtemp>=Sdistance0[4])&&(dtemp<Sdistance0[5]))
				distance[0] = 0.666*dtemp-1234; 
			else if ( (dtemp>=Sdistance0[5])&&(dtemp<Sdistance0[6]))
				distance[0] = 1.666*dtemp-3176; 
			else if ( (dtemp>=Sdistance0[6])&&(dtemp<=Sdistance0[7]))
				distance[0] = 1.111*dtemp-2094; 
			else if (dtemp>Sdistance0[7])
				distance[0] = 81;
			dtemp = 0;
			/////////////////////////////////////////////////////////2
			dtemp = distance[1];
			if (dtemp<Sdistance1[0])
				distance[1] = 0;
			else if ( (dtemp>=Sdistance1[0])&&(dtemp<Sdistance1[1]))
				distance[1] = 0.051*dtemp-175.4;
			else if ( (dtemp>=Sdistance1[1])&&(dtemp<Sdistance1[2]))
				distance[1] = 0.142*dtemp-521.5;  
			else if ( (dtemp>=Sdistance1[2])&&(dtemp<Sdistance1[3]))
				distance[1] = 0.263*dtemp-986;  
			else if ( (dtemp>=Sdistance1[3])&&(dtemp<Sdistance1[4]))
				distance[1] = 0.909*dtemp-3504;  
			else if ( (dtemp>=Sdistance1[4])&&(dtemp<Sdistance1[5]))
				distance[1] = 1.25*dtemp-4837;  
			else if ( (dtemp>=Sdistance1[5])&&(dtemp<Sdistance1[6]))
				distance[1] = 1.666*dtemp-6470; 
			else if ( (dtemp>=Sdistance1[6])&&(dtemp<=Sdistance1[7]))
				distance[1] = 0.833*dtemp-3200;  

			else if (dtemp>Sdistance1[7])
				distance[1] = 81;
			dtemp = 0;  
			/////////////////////////////////////////////////////////3
			dtemp = distance[2];
			if (dtemp<Sdistance2[0])
				distance[2] = 0;
			else if ( (dtemp>=Sdistance2[0])&&(dtemp<Sdistance2[1]))
				distance[2] = 0.05*dtemp-267.8;
			else if ( (dtemp>=Sdistance2[1])&&(dtemp<Sdistance2[2]))
				distance[2] = 0.119*dtemp-665.3;  
			else if ( (dtemp>=Sdistance2[2])&&(dtemp<Sdistance2[3]))
				distance[2] = 0.285*dtemp-1638; 
			else if ( (dtemp>=Sdistance2[3])&&(dtemp<Sdistance2[4]))
				distance[2] = 0.322*dtemp-1855; 
			else if ( (dtemp>=Sdistance2[4])&&(dtemp<Sdistance2[5]))
				distance[2] = dtemp-5857;  
			else if ( (dtemp>=Sdistance2[5])&&(dtemp<Sdistance2[6]))
				distance[2] = 0.833*dtemp-4870; 
			else if ( (dtemp>=Sdistance2[6])&&(dtemp<=Sdistance2[7]))
				distance[2] = 0.909*dtemp-5320;  

			else if (dtemp>Sdistance2[7])
				distance[2] = 81;
			dtemp = 0;  
			////////////////////////////////////////////////////////4
			dtemp = distance[3];
			if (dtemp<Sdistance3[0])
				distance[3] = 0;
			else if ( (dtemp>=Sdistance3[0])&&(dtemp<Sdistance3[1]))
				distance[3] = 0.046*dtemp-341.4;
			else if ( (dtemp>=Sdistance3[1])&&(dtemp<Sdistance3[2]))
				distance[3] = 0.126*dtemp-963.6;  
			else if ( (dtemp>=Sdistance3[2])&&(dtemp<Sdistance3[3]))
				distance[3] = 0.294*dtemp-2278;
			else if ( (dtemp>=Sdistance3[3])&&(dtemp<Sdistance3[4]))
				distance[3] = 0.4*dtemp-3113;
			else if ( (dtemp>=Sdistance3[4])&&(dtemp<Sdistance3[5]))
				distance[3] = 0.555*dtemp-4343;
			else if ( (dtemp>=Sdistance3[5])&&(dtemp<Sdistance3[6]))
				distance[3] = 0.769*dtemp-6037;
			else if ( (dtemp>=Sdistance3[6])&&(dtemp<=Sdistance3[7]))
				distance[3] =1.111*dtemp-8752;


			else if (dtemp>Sdistance3[7])
				distance[3] = 81;
			dtemp = 0;  
			////////////////////////////////////////////////////////5
			dtemp = distance[4];
			if (dtemp<Sdistance4[0])
				distance[4] = 0;
			else if ( (dtemp>=Sdistance4[0])&&(dtemp<Sdistance4[1]))
				distance[4] = 0.047*dtemp-443.3;
			else if ( (dtemp>=Sdistance4[1])&&(dtemp<Sdistance4[2]))
				distance[4] = 0.126*dtemp-1217;  
			else if ( (dtemp>=Sdistance4[2])&&(dtemp<Sdistance4[3]))
				distance[4] = 0.256*dtemp-2496; 
			else if ( (dtemp>=Sdistance4[3])&&(dtemp<Sdistance4[4]))
				distance[4] = 0.416*dtemp-4082; 
			else if ( (dtemp>=Sdistance4[4])&&(dtemp<Sdistance4[5]))
				distance[4] = 0.625*dtemp-6148; 
			else if ( (dtemp>=Sdistance4[5])&&(dtemp<Sdistance4[6]))
				distance[4] = 0.833*dtemp-8218; 
			else if ( (dtemp>=Sdistance4[6])&&(dtemp<=Sdistance4[7]))
				distance[4] = 2.5*dtemp-24795; 


			else if (dtemp>Sdistance4[7])
				distance[4] = 81;
			dtemp = 0;  
			///////////////////////////////////////////////////////6
			dtemp = distance[5];
			if (dtemp<Sdistance5[0])
				distance[5] = 0;
			else if ( (dtemp>=Sdistance5[0])&&(dtemp<Sdistance5[1]))
				distance[5] = 0.046*dtemp-530.1;
			else if ( (dtemp>=Sdistance5[1])&&(dtemp<Sdistance5[2]))
				distance[5] = 0.114*dtemp-1333;  
			else if ( (dtemp>=Sdistance5[2])&&(dtemp<Sdistance5[3]))
				distance[5] = 0.243*dtemp-2862; 
			else if ( (dtemp>=Sdistance5[3])&&(dtemp<Sdistance5[4]))
				distance[5] = 0.588*dtemp-6960; 
			else if ( (dtemp>=Sdistance5[4])&&(dtemp<Sdistance5[5]))
				distance[5] = 0.476*dtemp-5625; 
			else if ( (dtemp>=Sdistance5[5])&&(dtemp<Sdistance5[6]))
				distance[5] = 0.769*dtemp-9123; 
			else if ( (dtemp>=Sdistance5[6])&&(dtemp<=Sdistance5[7]))
				distance[5] = 1.25*dtemp-14870; 


			else if (dtemp>Sdistance5[7])
				distance[5] = 81;
			dtemp = 0;  
			/////////////////////////////////////////////////////7
			dtemp = distance[6];
			if (dtemp<Sdistance6[0])
				distance[6] = 0;
			else if ( (dtemp>=Sdistance6[0])&&(dtemp<Sdistance6[1]))
				distance[6] = 0.053*dtemp-720.5;
			else if ( (dtemp>=Sdistance6[1])&&(dtemp<Sdistance6[2]))
				distance[6] = 0.1*dtemp-1357;  
			else if ( (dtemp>=Sdistance6[2])&&(dtemp<Sdistance6[4]))
				distance[6] = 0.416*dtemp-5751; 
			else if ( (dtemp>=Sdistance6[4])&&(dtemp<Sdistance6[5]))
				distance[6] = 0.625*dtemp-8651; 
			else if ( (dtemp>=Sdistance6[5])&&(dtemp<=Sdistance6[7]))
				distance[6] = 1.111*dtemp-15428;  


			else if (dtemp>Sdistance6[7])
				distance[6] = 81;
			dtemp = 0;  
			/////////////////////////////////////////////////////8
			dtemp = distance[7];
			if (dtemp<Sdistance7[0])
				distance[7] = 0;
			else if ( (dtemp>=Sdistance7[0])&&(dtemp<Sdistance7[1]))
				distance[7] = 0.047*dtemp-730.8;
			else if ( (dtemp>=Sdistance7[1])&&(dtemp<Sdistance7[2]))
				distance[7] = 0.135*dtemp-2110;  
			else if ( (dtemp>=Sdistance7[2])&&(dtemp<Sdistance7[3]))
				distance[7] = 0.2*dtemp-3138; 
			else if ( (dtemp>=Sdistance7[3])&&(dtemp<Sdistance7[4]))
				distance[7] = 0.454*dtemp-7183;
			else if ( (dtemp>=Sdistance7[4])&&(dtemp<Sdistance7[5]))
				distance[7] = 0.588*dtemp-9310; 
			else if ( (dtemp>=Sdistance7[5])&&(dtemp<Sdistance7[6]))
				distance[7] = 0.833*dtemp-13215; 
			else if ( (dtemp>=Sdistance7[6])&&(dtemp<=Sdistance7[7]))
				distance[7] = 0.5*dtemp-7901; 

			else if (dtemp>Sdistance7[7])
				distance[7] = 81;
			dtemp = 0;  

			for(int iLoop=0;iLoop<8;iLoop++){
				arrDistance[iLoop] = distance[iLoop];
			}
			arrVoltage[0] = distance[8]/908;
			arrVoltage[1] = distance[9]/1730;

			bNewSegmentData[CurrentIndex] = FALSE; 
			WaveOrDight = 0;
			CurrentIndex=(CurrentIndex+1) % MAX_SEGMENT;
			ReadIndex=(ReadIndex+1) % MAX_SEGMENT; 
	}
		}
	return 0;
}
// the following functions are no longer needed....
 int AD:: start(){
	return 0;
}
 int AD:: stop(){
	return 0;
}