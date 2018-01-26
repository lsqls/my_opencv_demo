#include "highgui.h"
void showpic(char * pic)
{
	IplImage * img = cvLoadImage(pic);
	/*cvNamedWindow("example");*/
	cvShowImage("mypic", img);
	cvWaitKey(0);
	cvReleaseImage(&img);
//	cvDestroyWindow("example");
}
int main()
{
	showpic("D:\\1.jpg");
	return 0;
}
