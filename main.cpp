#include "ImageProcess.cpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout<<"Usage for webcam: ./blur_faces cam"<<endl;
		cout<<"Usage for video: ./blur_faces video path/to/video"<<endl;
		cout<<"Usage for webcam: ./blur_faces image path/to/image"<<endl;

	}
	
	Mat inp_image;
	
	string cascade_dir = "/home/enis/Opencv_Tutorials/Face_Bluring/Resources/haarcascade_frontalface_alt.xml";
	int kernel_size = 65;
	int resized_height = 240;
	int resized_width = 320; 
	ImageProcesser image_processer(cascade_dir, &kernel_size, &resized_width, &resized_height);
	char c;
	if(strcmp(argv[1],"cam") == 0)
	{
		VideoCapture cap(0);
		if(!cap.isOpened())
		{
			cout<<"Could not open video stream"<<endl;
			return -1;
		}
		while(true)
		{
			cap>>inp_image;
			image_processer.process_image(&inp_image);

			imshow("Webcam", image_processer.source_image);
			c = (char)waitKey(1);
			if (c==27)
				break;
		}
		cap.release();
		destroyAllWindows();
	}
	else if(strcmp(argv[1], "video") == 0)
	{
		VideoCapture cap(argv[2]);
		if(!cap.isOpened())
		{
			cout<<"Could not open video stream"<<endl;
			return -1;
		}
		while(true)
		{
			cap>>inp_image;
			image_processer.process_image(&inp_image);

			imshow("Video", image_processer.source_image);
			c = (char)waitKey(1);
			if (c==27)
				break;
		}
		cap.release();
		destroyAllWindows();
	}
	else if (strcmp(argv[1], "image") == 0)
	{
		inp_image = imread((string)argv[2]);
		image_processer.process_image(&inp_image);
		imshow("Image", image_processer.source_image);
		waitKey(0);
	}	
	else
	{
		cout<<"Invalid Arguments"<<endl;
		cout<<"Usage for webcam: ./program_name cam"<<endl;
		cout<<"Usage for video: ./program_name video path/to/video"<<endl;
		cout<<"Usage for webcam: ./program_name image path/to/image"<<endl;
	}
	return 0;
}
