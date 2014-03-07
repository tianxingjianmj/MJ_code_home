//////////////////////////////////////////////////////////////////////
// Video Capture using DirectShow
// Author: Shiqi Yu (shiqi.yu@gmail.com)
// Thanks to:
//		HardyAI@OpenCV China
//		flymanbox@OpenCV China (for his contribution to function CameraName)
// Last modification: July 24, 2008
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// 使用说明：
//   1. 将CameraDS.h CameraDS.cpp以及目录DirectShow复制到你的项目中
//   2. 菜单 Project->Settings->Settings for:(All configurations)->C/C++->Category(Preprocessor)->Additional include directories
//      设置为 DirectShow/Include
//   3. 菜单 Project->Settings->Settings for:(All configurations)->Link->Category(Input)->Additional library directories
//      设置为 DirectShow/Lib
//////////////////////////////////////////////////////////////////////

#include "camerads.h"
#include <highgui.h>
#include <stdio.h>

#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>


//小车控制
#include "AD.h"
#include "RobotCar.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
//

#ifdef _EiC
#define WIN32
#endif

static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;

void detect_and_draw( IplImage* image );

const char* cascade_name =
    "haarcascade_frontalface_alt.xml";
/*    "haarcascade_profileface.xml";*/

int main()
{
	int cam_count;

	int start = 0;
	int finish = 0;
	//start = clock();
	int level = 1; // valid value:1,2,3,4,5
	
	//	Sleep(20000);
	//	objRobotCar.Left_Go();
	//	objRobotCar.Right_Go();
	//    objRobotCar.Forward_Go(2);
	//objRobotCar.Back_Go(2);
	//while(true){
	//	printf("running\n");
	//	finish = clock();		
	//	if((finish - start) >= 10000)
	//		break;
	//}
	//printf("stop back.............................................................\n");
	//objRobotCar.Stop_Slow();
	//printf("done!\n");

	
	//start = clock();
	//objRobotCar.Forward_Go(2);
	//while(true){
	//	printf("running\n");
	//	finish = clock();		
	//	if((finish - start) >= 2000)
	//		break;
	//}
	//printf("stop.  forward............................................................\n");
	//objRobotCar.Stop_Slow();
	//printf("done!\n");



	//仅仅获取摄像头数目
	cam_count = CCameraDS::CameraCount();
	printf("There are %d cameras.\n", cam_count);


	//获取所有摄像头的名称
	for(int i=0; i < cam_count; i++)
	{
		char camera_name[1024];  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );

		if(retval >0)
			printf("Camera #%d's Name is '%s'.\n", i, camera_name);
		else
			printf("Can not get Camera #%d's name.\n", i);
	}


	if(cam_count==0)
		return -1;

	
    IplImage *frame_copy = 0;
    cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
	if( !cascade )
    {
        printf("ERROR: Could not load classifier cascade\n" );
        printf("Usage: facedetect --cascade=\"<cascade_path>\" [filename|camera_index]\n" );
        return -1;
    }
	else printf("ok\n");
    storage = cvCreateMemStorage(0);

	//打开第一个摄像头
	CCameraDS camera;
	
	if(! camera.OpenCamera(1,false))
	{
		fprintf(stderr, "Can not open camera.\n");
		return -1;
	}
	
	
	cvNamedWindow("camera");
	//cvNamedWindow( "result", 1 );
	start = clock();
	RobotCar objRobotCar = RobotCar::RobotCar(level);	
	objRobotCar.Back_Go(2);
	
	while(true)
	{
		printf("running\n");
		finish = clock();		
		if((finish - start) >= 10000)
			break;
		//获取一帧
		IplImage *pFrame = camera.QueryFrame();

		//显示
		cvShowImage("camera", pFrame);

        //if( !frame_copy )
        //        frame_copy = cvCreateImage( cvSize(pFrame->width,pFrame->height),
        //                                    IPL_DEPTH_8U, pFrame->nChannels );
        //    if( pFrame->origin == IPL_ORIGIN_TL )
        //        cvCopy( pFrame, frame_copy, 0 );
        //    else
        //        cvFlip( pFrame, frame_copy, 0 );
            
            //detect_and_draw( frame_copy );

            



		if (cvWaitKey(20) == 'q')
			break;
	}
    objRobotCar.Stop_Slow();
	printf("done!\n");

	camera.CloseCamera(); //可不调用此函数，CCameraDS析构时会自动关闭摄像头

	cvDestroyWindow("camera");
	return 0;
}


void detect_and_draw( IplImage* img )
{
    static CvScalar colors[] = 
    {
        {{0,0,255}},
        {{0,128,255}},
        {{0,255,255}},
        {{0,255,0}},
        {{255,128,0}},
        {{255,255,0}},
        {{255,0,0}},
        {{255,0,255}}
    };

    double scale = 1.3;
    IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
    IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
                         cvRound (img->height/scale)),
                     8, 1 );
    int i;

    cvCvtColor( img, gray, CV_BGR2GRAY );
    cvResize( gray, small_img, CV_INTER_LINEAR );
    cvEqualizeHist( small_img, small_img );
    cvClearMemStorage( storage );

    if( cascade )
    {
        double t = (double)cvGetTickCount();
        CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
                                            1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
                                            cvSize(30, 30) );
        //t = (double)cvGetTickCount() - t;
        //printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
            CvPoint center;
             int radius;
             center.x = cvRound((r->x + r->width*0.5)*scale);
             center.y = cvRound((r->y + r->height*0.5)*scale);
             radius = cvRound((r->width + r->height)*0.25*scale);
            //cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
			cvRectangle(img,cvPoint(center.x-radius-20,center.y-radius-20),cvPoint(center.x+radius+20,center.y+radius+20),colors[i%8],3);
        }
    }

    //cvShowImage( "result", img );
    cvReleaseImage( &gray );
    cvReleaseImage( &small_img );
}
