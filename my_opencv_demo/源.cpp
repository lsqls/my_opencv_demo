#include "highgui.h"
void showpic(char * pic)
{
	IplImage * img = cvLoadImage(pic);
	/*cvNamedWindow("example");*/
	cvShowImage("mypic", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
//	cvDestroyWindow("example"); ²»ÐèÒª
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
int main()
{
	//showpic("D:\\1.jpg");
	aviplayer("D:\\1.avi");
	return 0;
}
