#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

//float w = 250, h = 350;
//Mat matrix, imgWarp;
//int hmin = 0, smin = 110, vmin = 153;
//int hmax = 19, smax = 240, vmax = 255;

void getContours(Mat imgDil, Mat img)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	
	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boudRect(contours.size());
	string objectType;

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			drawContours(img, contours, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;
			boudRect[i] = boundingRect(conPoly[i]);
			rectangle(img, boudRect[i].tl(), boudRect[i].br(), Scalar(0, 255, 0), 5);
			int objCer = (int)conPoly[i].size();
			if (objCer == 3)
			{
				objectType = "Tri";
			}
			else if(objCer == 4)
			{
				objectType = "Rect";
			}
			else if (objCer > 4)
			{
				objectType = "Circle";
			}
			putText(img, objectType, { boudRect[i].x, boudRect[i].y - 5 },
				FONT_HERSHEY_DUPLEX, 0.75,
				Scalar(0, 0, 255));
		}
	}
}
int main()
{
	string path = "face_test.png";
	Mat img = imread(path);
	CascadeClassifier faceCascade;
	faceCascade.load("haarcascade_frontalface_default.xml");
	if (faceCascade.empty()) { cout << "no se pudo carnal" << endl; }

	vector<Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);
	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
	}
	imshow("Image", img);
	waitKey(0);

	/*string path = "Anim_Link_Oscuro_Spacecat.mp4";*/
	/*VideoCapture cap(0);
	Mat img;
	while (true)
	{
		cap.read(img);
		imshow("Image", img);
		waitKey(0);
	}
	return 0;*/


	/*string path = "Face.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode, imgResize, imgCrop;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 50, 150);

	Mat Kernel = getStructuringElement(MORPH_CROSS, Size(15, 15));
	dilate(imgCanny, imgDilate, Kernel);
	erode(imgDilate, imgErode, Kernel);

	cout << img.size() << endl;
	resize(img, imgResize, Size(), 0.5, 0.5);

	Rect roi(100, 100, 300, 250);
	imgCrop = img(roi);

	imshow("Image", imgCrop);
	cout << img.size() << endl;
	waitKey(0);*/

	/*Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
	circle(img, Point(256, 256), 155, Scalar(150, 160, 0), FILLED);
	rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
	line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 5);

	imshow("Image", img);
	waitKey(0);*/

	/*string path = "cards.jpg";
	Mat img = imread(path);

	Point2f src[4] = { {529,142},{771,190},{405,395},{674,457} };
	Point2f dest[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = getPerspectiveTransform(src, dest, 0);
	warpPerspective(img, imgWarp, matrix, Point(w, h));
	imshow("Image", imgWarp);
	waitKey(0);*/

	
	/*string path = "lambo.png";
	Mat imgHSV, mask;
	Mat img = imread(path);
	cvtColor(img, imgHSV, COLOR_BGR2HSV);
	namedWindow("Trackbars", (640, 200));
	createTrackbar("Hue(Matriz) min", "Trackbars", &hmin, 179);
	createTrackbar("Hue(Matriz) max", "Trackbars", &hmax, 179);
	createTrackbar("Hue(Saturación) min", "Trackbars", &smin, 255);
	createTrackbar("Hue(Saturación) min", "Trackbars", &smax, 255);
	createTrackbar("Hue(Brillo) min", "Trackbars", &vmin, 255);
	createTrackbar("Hue(Brillo) min", "Trackbars", &vmax, 255);

	while (true)
	{
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
		imshow("Image", mask);
		waitKey(1);
	}*/

	/*string path = "shapes.png";
	Mat imgHSV, mask, imgGray, imgBlur, imgCanny, imgDil, imgErode;
	Mat img = imread(path);

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	getContours(imgDil, img);

	imshow("Image", img);
	waitKey(0);*/
}