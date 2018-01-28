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
void draw_circle()
{
	CvMat* mat=cvCreateMat(1000, 1000, CV_8UC3);
	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < 1000; j++)
			cvSet2D(mat, i, j, cvScalarAll(0));
	cvCircle(mat, cvPoint(500, 250), 250, cvScalar(255, 255, 0));
	cvShowImage("circle", mat);
	cvWaitKey(0);
	cvReleaseMat(&mat);
}
void draw_rec()
{
	CvPoint point1= cvPoint(200, 50);
	CvPoint point2 = cvPoint(400, 200);
	int row = 1000, col= 1000;
	CvMat * mat = cvCreateMat(row, col, CV_8UC3);
	cvZero(mat);
	uchar* p;
	for (int i = 0; i < 1000; i++)
		for (int j = 0; j < 1000; j++)
			if (i > point1.x&&i<point2.x&&j>point1.y&&j < point2.y)
			{
				p= cvPtr2D(mat, i, j);
				p++;
				*p = 255;
			}
	cvShowImage("rectangle", mat);
	cvWaitKey(0);
	cvReleaseMat(&mat);
}
void ROI()//fail
{
	// 图像高宽  
#define IMG_SIZE   420  

	// 边界宽度  
#define BORDER_WIDTH 10  

	IplImage * image = cvCreateImage(cvSize(IMG_SIZE, IMG_SIZE), 8, 1);

	// 初始化置零  
	cvZero(image);

	// 灰度值  
	int value = 0;
	// ROI区域大小  
	int rect_size = IMG_SIZE;
	for (int length = IMG_SIZE; length >= 0 && value <= 200; length -= BORDER_WIDTH, value += 10)
	{
		cvSetImageROI(image, cvRect(IMG_SIZE - length, IMG_SIZE - length, rect_size, rect_size));

		rect_size -= 2 * BORDER_WIDTH;
		cvSet(image, cvScalarAll(value));
		cvResetImageROI(image);
	}

	cvNamedWindow("img", 1);
	cvShowImage("img", image);

	cvWaitKey(0);
	cvReleaseImage(&image);
	cvDestroyAllWindows();
}
int main()
{
	//showpic("D:\\1.jpg");
	//aviplayer("D:\\1.avi");
	//cal_example();
	//draw_circle();
	//draw_rec();
	ROI();
	return 0;
}
