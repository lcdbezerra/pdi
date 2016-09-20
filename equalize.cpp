#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  Mat image;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes, eq_planes;
  Mat histR, histG, histB;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;
  Vec3b cor;

  cap.open(0);

  if(!cap.isOpened()){
    cout << "Camera indisponivel" << endl;
    return -1;
  }

  width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "Largura = " << width << endl;
  cout << "Altura = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));

  while(1){
    cap >> image;
    split (image, planes);
    split (image, eq_planes);

    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[1], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[2], 1, 0, Mat(), histB, 1,
             &nbins, &histrange,
             uniform, acummulate);

    Mat swap(height,width,CV_8UC3, Scalar(0,0,0));

    equalizeHist(planes[0],eq_planes[0]);
    equalizeHist(planes[1],eq_planes[1]);
    equalizeHist(planes[2],eq_planes[2]);

    for (int i = 0; i < image.rows; i++){
      for (int j = 0; j < image.cols; j++){
        cor[0] = eq_planes[0].at<uchar>(i,j);
        cor[1] = eq_planes[1].at<uchar>(i,j);
        cor[2] = eq_planes[2].at<uchar>(i,j);
        swap.at<Vec3b>(i,j) = cor;
      }
    }

    //cvtColor( image, swap, CV_BGR2GRAY );
    //equalizeHist(image,equalized);
    imshow("Capturada",image);
    imshow("Equalizada",swap);
    //imshow("Equalizada",equalized);

    if(waitKey(30) >= 0) return 0;
  }
}