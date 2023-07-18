
#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
string path = "Resources/shapes2.jpg";
Mat img = imread(path);
Mat imgGray, imgBlur, imgCanny, imgDil;
void getContours(Mat imgDil, Mat img)
{
  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  vector<vector<Point>> cornPoly(contours.size());
  vector<Rect> boundRect(contours.size());
  string objectType;
  for(int i = 0; i < contours.size(); ++i)
  {
    int area = contourArea(contours[i]);
    if(area >= 3000)
    {
      float peri = arcLength(contours[i], true);
      approxPolyDP(contours[i], cornPoly[i], 0.02*peri, true);
      drawContours(img, cornPoly, i, Scalar(255, 0, 255), 2);
      int objCor = static_cast<int>(cornPoly[i].size());
      boundRect[i] = boundingRect(cornPoly[i]);
        switch(objCor)
        {
          case 3 : objectType = "Triangle";
            break;
          case 4 : objectType = "Rectangle";
            break;
          default : objectType = "Circle";
        }
      putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 0 ,0), 2);
    }
}
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
