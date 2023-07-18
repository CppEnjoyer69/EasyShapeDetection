
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
string path = "Resources/cards.jpg";
Mat img = imread(path);
Mat imgGray, imgBlur, imgCanny, imgDil;

void getContours(Mat imgDil, Mat img)
{
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
}
int main()
{
  //Image preprocess
  cvtColor(img, imgGray, COLOR_BGR2GRAY);
  GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
  Canny(imgBlur, imgCanny, 25, 75);
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  dilate(imgCanny, imgDil, kernel);
  
  getContours(imgDil, img);




  imshow("contours", img);
waitKey(0);
    return 0;
}
