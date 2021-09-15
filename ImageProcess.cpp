#include "ImageProcess.hpp"

using namespace std;
using namespace cv;

ImageProcesser::ImageProcesser(string face_cascade_dir, int* kernel_size, int* width, int* height)
{
	//load the face cascade classifier
	if(!face_cascade.load(face_cascade_dir))
		std::cout<<"Could not load the classifier";
	//assign the parameters
	blur_kernel_size = *kernel_size;
	resize_width = *width;
	resize_height = *height;
}


void ImageProcesser::process_image(Mat* image)
{
	//Keep original image for visualization
	source_image = *image;
	
	resize(source_image, source_image, Size(resize_width, resize_height), INTER_LINEAR);
	// Convert to gray to detect faces
	cvtColor(source_image, processed_image, COLOR_BGR2GRAY);
	
	equalizeHist(processed_image, processed_image);
	
	//Create vector to hold face coordinates
	vector<Rect> faces;

	//Detect faces and store coordinates at faces vector
	face_cascade.detectMultiScale(processed_image, faces);
 
	//Draw rectangles and blur faces
	for(size_t i=0; i<faces.size(); i++)
	{	
		//left up coordinates to draw rect
		p1.x = faces[i].x;
		p1.y = faces[i].y;
		//right below coordinates to draw rect
		p2.x = faces[i].x + faces[i].width;
		p2.y = faces[i].y + faces[i].height;
		//draw rectangle 
		rectangle(source_image, p1, p2, Scalar(0, 0, 255), 2, 8, 0);
		//blur each face
		blur_face();
		
	}


}

void ImageProcesser::blur_face()
{
	//get crop region to blur
	crop_region.x = p1.x;
	crop_region.y = p1.y;
	crop_region.width = p2.x - p1.x;
	crop_region.height = p2.y - p1.y;

	cropped_image = source_image(crop_region);
	GaussianBlur(cropped_image, cropped_image, Size(blur_kernel_size, blur_kernel_size), 0, 0);

}