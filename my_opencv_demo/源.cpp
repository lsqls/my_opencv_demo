#include "highgui.h"
#include "cv.h"
#include <iostream>
using namespace std;
void showpic(char * pic)
{
	IplImage * img = cvLoadImage(pic);
	/*cvNamedWindow("example");*/
	cvShowImage("mypic", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
//	cvDestroyWindow("example"); 不需要
}
void aviplayer(char * video)
{
	CvCapture *capture = cvCreateFileCapture(video);
	IplImage* frame;
	while (1)
	{
		frame = cvQueryFrame(capture);
		if (!frame) break;
		cvShowImage("video", frame);
		char c = cvWaitKey(33);
		if (c == 27) break;
	}
		cvReleaseCapture(&capture);
}
void cal_example()//第三章练习题1
{
	double d = -2.501;
	cout <<"value："<<d << " abs:" << CV_IABS(d) << "\tround:" << cvRound(d) << endl;//cvround四舍五入
	CvRNG rng = cvRNG(cvGetTickCount());//时间戳作为seed
	for (int i = 0; i < 10; i++)
	{
		cout << "random number["<<i<<"]:"<<cvRandInt(&rng) % 256;
		cout << '\t' << cvRandReal(&rng) << endl;//随机数0-1
	}
	CvPoint2D32f point = cvPoint2D32f(1.22, 29.2);
	CvPoint point1 = cvPointFrom32f(point);
	CvPoint2D32f  point2 = cvPointTo32f(point1);
	cout <<"Three point\t" <<'('<<point.x << ',' << point.y <<')'<< ' ' << '(' << point1.x << ',' << point1.y<< ')' <<
		' ' << '(' << point2.x <<  ',' << point2.y<<')';
}
int main()
{
	//showpic("D:\\1.jpg");
	//aviplayer("D:\\1.avi");
	cal_example();
	return 0;
}
