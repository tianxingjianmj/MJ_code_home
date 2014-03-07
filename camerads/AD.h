#include "USB5935.h"
#pragma comment(lib, "USB5935.lib")

#define MAX_SEGMENT 64
class AD{
public:
	HANDLE hDeviceAD;
	USB5935_PARA_AD ADPara;
	unsigned short pADBuffer[MAX_SEGMENT][16384]; 
	BOOL bNewSegmentData[MAX_SEGMENT]; 
	double arrDistance[8];
	double arrVoltage[2];
public:
	int start();
	int readData();
	int stop();
	int getDistance(double array[], int len);
	int getVoltage(double array[], int len);
	AD();
	~AD();
};