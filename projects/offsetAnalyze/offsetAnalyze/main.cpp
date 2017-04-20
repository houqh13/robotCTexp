//#include <cv.h>
#include <opencv.hpp>
//#include <highgui.h>
using namespace cv;

int main()
{
	Mat frame;
	VideoCapture capture(0);
	
	while (true)
	{
		capture >> frame;
		imshow("camera", frame);
		if (waitKey(50) == 27)
		{
			break;
		}
	}

	return 0;
}
