#include "ColorDetect.h"

ColorDetect::ColorDetect()
{
	writer2 = std::unique_ptr< cv::VideoWriter > (new cv::VideoWriter("output.avi", CV_FOURCC('D', 'I', 'V', 'X'), 5, cv::Size(640, 480), true));
	getVideo();
}

ColorDetect::~ColorDetect() { }

void ColorDetect::getVideo()
{
	vcap.open(0); //0 = connected webcam
	
	//std::cout << "Press the enter key to begin" << std::endl;
	//std::cin.get();
	
	if (!vcap.isOpened())
		std::cout << "Could not open video input stream" << std::endl;
	if (!writer2->isOpened())
		std::cout << "Could not open video output stream" << std::endl;
	
}

cv::Mat ColorDetect::getThresh(const cv::Mat &inImg)
{
	cv::Mat tmpImg = inImg;
	cv::Mat imgThresh(tmpImg.size(), tmpImg.type());
	//change first cv::Scalar for lower boundary and second for upper boundary 
	//cv::inRange(tmpImg, cv::Scalar(0, 127, 127), cv::Scalar(6, 255, 255), imgThresh);
	cv::inRange(tmpImg, cv::Scalar(0, 50, 50), cv::Scalar(3, 100, 100), imgThresh);
	// Donno why this doesn't work, I think it should detect green color.
	//cv::inRange(tmpImg, cv::Scalar(127, 0, 127), cv::Scalar(255, 6, 255), imgThresh);
	return imgThresh;
}

cv::Mat ColorDetect::detect(const cv::Mat &img)
{	
	cv::Mat in, cvtImg, thrImg, eImg, dImg;
	cv::Mat element(5, 5, CV_8U, cv::Scalar(1));
	std::vector<std::vector<cv::Point> > contours;
	in = img;
	cv::cvtColor(in, cvtImg, CV_BGR2HLS, 0);
	thrImg = getThresh(cvtImg);

	cv::dilate(thrImg, dImg, element);
	cv::dilate(dImg, eImg, element);
	for (int h = 0; h>4; h++)
	{
		cv::erode(eImg, eImg, element);
	}
	cv::dilate(eImg, dImg, element);
	cv::dilate(dImg, dImg, element);

	cv::findContours(dImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	std::vector<cv::Rect> boundRect(contours.size());

	for (unsigned int i = 0; i < contours.size(); i++)
	{
		cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 25, true);
		boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]));
	}

	for (unsigned int j = 0; j < contours.size(); j++)
	{
		cv::rectangle(in, boundRect[j], cv::Scalar(0, 0, 255), 2);
	}

	return in;

}

void ColorDetect::update()
{	
	cv::Mat src;
	cv::namedWindow("Color Detect");

	for (;;)
	{
		vcap >> src;
		cv::imshow("Color Detect", detect(src));
		if (cv::waitKey(45) >= 0) break;
	}
}

