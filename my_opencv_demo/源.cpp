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
void CVNOT()
{
	#define NEW_IMG_WIDTH  20
	#define NEW_IMG_HEIGHT 300
	IplImage *lena = cvLoadImage("D:\\lena.png");
	IplImage *image1 = cvCreateImage(cvSize(NEW_IMG_WIDTH, NEW_IMG_HEIGHT), lena->depth, lena->nChannels);
	IplImage *image2 = cvCreateImage(cvSize(NEW_IMG_WIDTH, NEW_IMG_HEIGHT), lena->depth, lena->nChannels);
	image1->imageData = (char*)cvPtr2D(lena, 5,10 );
	image2->imageData = (char*)cvPtr2D(lena, 50,60 );
	cvNot(image1, image1);
	cvNot(image2, image2);
	cvShowImage("lena",lena);
	cvWaitKey();
	cvReleaseImage(&lena);
}
void split()
{
	IplImage *lena = cvLoadImage("D:\\lena.png");
	IplImage *image1 = cvCreateImage(cvGetSize(lena), lena->depth, 1);
	IplImage *image2= cvCreateImage(cvGetSize(lena),lena->depth, 1);
	IplImage *image3 = cvCreateImage(cvGetSize(lena), lena->depth, 1);
	cvSplit(lena, image1, image2, image3,NULL);//blue,green,red
	cvShowImage("raw", lena);
	cvShowImage("blue", image1);
	cvShowImage("green",image2);
	cvShowImage("red", image3);
	IplImage *clone1 = cvCloneImage(image2);
	IplImage *clone2 = cvCloneImage(image2);
	double min, max;
	cvMinMaxLoc(image2, &min, &max);
	char thresh = (unsigned char)(max - min)/2;
	cvSet(clone1, cvScalarAll(thresh));
	cvShowImage("clone1", clone1);
	cvSet(clone2, cvScalarAll(0), 0);
	cvShowImage("clone2", clone2);
	cvCmp(image2, clone1, clone2, CV_CMP_GE);
	cvShowImage("clone2", clone2);
	cvSubS(image2, thresh / 2, image2, clone2);
	cvShowImage("clone2", clone2);
	cvWaitKey();
}
void cap()
{
	char * file_path = "D:\\opencv_demo_file\\1.avi";
	CvCapture * capture = 0;
	capture = cvCreateFileCapture(file_path);

	// 载入视频文件失败  
	if (capture == NULL)
		cout<<"Can't load the video file, quit...\n";
		


	// 每一帧  
	IplImage * frame = cvQueryFrame(capture);;
	// 灰度后的每一帧  
	IplImage * gray_frame = cvCreateImage(cvGetSize(frame), frame->depth, 1);
	IplImage * gray_frame_3 = cvCreateImage(cvGetSize(frame), frame->depth, 3);
	// 边缘检测后的每一帧  
	IplImage * canny_frame = cvCreateImage(cvGetSize(frame), frame->depth, 1);
	IplImage * canny_frame_3 = cvCreateImage(cvGetSize(frame), frame->depth, 3);
	// 聚合来的每一帧  
	IplImage * total_frame = cvCreateImage(cvSize(frame->width * 3, frame->height),
		frame->depth, frame->nChannels);

	while (1)
	{
		// 从视频文件读入数据  
		frame = cvQueryFrame(capture);
		if (!frame)
			break;

		// 将读入数据转换为灰度图  
		cvCvtColor(frame, gray_frame, CV_RGB2GRAY);
		cvCvtColor(gray_frame, gray_frame_3, CV_GRAY2BGR);

		// 对图像做Canny边缘检测  
		cvCanny(gray_frame, canny_frame, 30, 100, 3);
		cvCvtColor(canny_frame, canny_frame_3, CV_GRAY2BGR);

		// 将三幅图像分别复制到新的图像中  
		cvSetImageROI(total_frame, cvRect(0, 0, frame->width, frame->height));
		cvCopy(frame, total_frame, 0);
		cvResetImageROI(total_frame);

		cvSetImageROI(total_frame, cvRect(frame->width, 0, gray_frame->width, gray_frame->height));
		cvCopy(gray_frame_3, total_frame, 0);
		cvResetImageROI(total_frame);

		cvSetImageROI(total_frame, cvRect(frame->width * 2, 0, canny_frame->width, canny_frame->height));
		cvCopy(canny_frame_3, total_frame, 0);
		cvResetImageROI(total_frame);

		// 在图像的三个不同的部分写上合适的文字标签  
		CvFont textFont = cvFont(10, 1);
		cvInitFont(&textFont, CV_FONT_HERSHEY_SIMPLEX, 0.5f, 0.5f, 0, 1);

		cvPutText(total_frame, "Frame", cvPoint(10, 20), &textFont, cvScalar(0, 0, 255));
		cvPutText(total_frame, "Frame_Gray", cvPoint(frame->width + 10, 20), &textFont, cvScalar(0, 0, 255));
		cvPutText(total_frame, "Frame_Canny", cvPoint(frame->width * 2 + 10, 20), &textFont, cvScalar(0, 0, 255));



		// 显示图像  
		cvShowImage("total", total_frame);

		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}
	cvReleaseImage(&gray_frame);
	cvReleaseCapture(&capture);
	cvDestroyAllWindows();

}
int main()
{
	//showpic("D:\\1.jpg");
	//aviplayer("D:\\1.avi");
	//cal_example();
	//draw_circle();
	//draw_rec();
	//ROI();
	//CVNOT();
	//split();
	cap();
	return 0;
}
