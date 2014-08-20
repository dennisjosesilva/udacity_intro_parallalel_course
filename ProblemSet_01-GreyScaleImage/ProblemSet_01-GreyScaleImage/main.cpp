#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>

using namespace std;
using namespace cv;

Mat convertToGreyScaleImage(Mat& colouredImage);

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
		Mat colouredImage;
		cvtColor(image, colouredImage, CV_BGR2RGBA);
		auto greyImage = convertToGreyScaleImage(colouredImage);
		
		namedWindow("Hello World Image", WINDOW_AUTOSIZE);
		imshow("Hello World Image", greyImage);
		
		waitKey(0);
	}
	
	return 0;
}

Mat convertToGreyScaleImage(Mat& colouredImage)
{
	auto greyImage = Mat(colouredImage.rows, colouredImage.cols, CV_8UC1);
	auto ptrGreyImage = greyImage.ptr<unsigned char>(0);
	auto ptrColouredImage = (uchar4 *)colouredImage.ptr<unsigned char>(0);
	auto numPixels = colouredImage.total();

	for(auto i = 0; i < numPixels; i++)
		ptrGreyImage[i] = (.299f * ptrColouredImage[i].x) + (.587f * ptrColouredImage[i].y) + (.114 * ptrColouredImage[i].z);

	return greyImage;
}