#include <Windows.h>
//#include "AD.h"
//#include "RobotCar.h"

enum ACTION{
	FORWARD = 1,
	BACKWORD,
	TURN_LEFT,
	TURN_RIGHT,
	STOP
};
class RandomWalk{
private:
	HANDLE hSysStatus;
	HANDLE hCollectData;
	HANDLE hProccessData;
	HANDLE hWatchVoltage;
	double arrayDistance[8];
	double arrayVoltage[2];
	int iCarStatus; // running or stop
	int action; // go forward, go backward, 
public:
	RandomWalk();
	~RandomWalk();	
	int chooseAction(int curAction);
};
UINT collectData(LPVOID lparam);
UINT processData(LPVOID lparam);