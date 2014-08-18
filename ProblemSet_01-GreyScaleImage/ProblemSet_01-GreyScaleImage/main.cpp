#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	string filename;

	switch(argc)
	{
	case 1:
		filename = "cinque_terre_small.jpg";
		break;
	case 2:
		filename = string(argv[1]);
		break;
	}

	auto image = imread(filename, CV_LOAD_IMAGE_COLOR);

	if(image.empty())
	{
		cerr << "image " << filename << " was not found!" << endl;
		exit(1);
	}
	else
	{
		namedWindow("Hello World Image", WINDOW_AUTOSIZE);
		imshow("Hello World Image", image);

		waitKey(0);
		
	}
	
	return 0;
}