#include "USB1010.h"

struct MotorValue{
	int multiplerate1;
	int startspeed1;
	int drivespeed1;
	int acceleration1;
	int acceleration1k;
	int deceleration1;
	int multiplerate2;
	int startspeed2;
	int drivespeed2;
	int acceleration2;
	int acceleration2k;
	int deceleration2;
};
class RobotCar
{
	// 
private:
	struct MotorValue stMotorValue;
	USB1010_PARA_DataList DLX;
	USB1010_PARA_LCData LCX;
	USB1010_PARA_DataList DLY;
	USB1010_PARA_LCData LCY;
	// function definition
private:
//	void RSetMotorValue();
	HANDLE hDevice;
	void setParam(int action);
	void configParam(int level);
public:
	int Back_Go(int level);
	int Forward_Go(int level);
	int LaseRador();
	int Left_Go(int level);
	int Right_Go(int level);
//	public int Start();
//	public int Stop();
	int Stop_Im();
	int Stop_Slow();
	RobotCar();
	RobotCar(int level);
	RobotCar(struct MotorValue stMotorValue);
	~RobotCar();
};