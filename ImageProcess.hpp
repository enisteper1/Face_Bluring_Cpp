#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/objdetect.hpp>
#include <opencv4/opencv2/videoio.hpp>
#include <iostream>
#include <string>

class ImageProcesser
{
public:
	int blur_kernel_size;
	int resize_width;
	int resize_height;
	cv::Mat source_image;
	cv::Mat processed_image;
	cv::Mat cropped_image;
	cv::CascadeClassifier face_cascade;
	cv::Rect crop_region;
	cv::Point p1;
	cv::Point p2;
	ImageProcesser(std::string, int*, int*, int*);
	void process_image(cv::Mat* image);
	void blur_face();

};
#endif

