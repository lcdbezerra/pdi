#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
	Mat image;
	int width, height;
	VideoCapture cap;
	vector<Mat> planes;
	int nbins = 64;
	float range[] = {0,256};
	const float *histrange = { range };
	bool uniform = true, acummulate = false;
	double compare;

	Mat histR, histR_old;

	cap.open(0);
	if(!cap.isOpened()){
    	cout << "Camera indisponivel" << endl;
    return -1;
  	}

  	width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  	height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  	cout << "Largura = " << width << endl;
  	cout << "Altura = " << height << endl;

  	while(1){
  		cap >> image;
   		split (image,planes);

  		calcHist(&planes[0], 1, 0, Mat(), histR, 1, &nbins, &histrange, uniform, acummulate);    	
    	normalize(histR, histR, 0, 1, NORM_MINMAX, -1, Mat());

    	if(!histR_old.data){ histR.copyTo(histR_old); continue;}

    	compare = compareHist(histR, histR_old, CV_COMP_CORREL);
    	cout << "COMPARE: " << compare << endl;

    	if (compare < 0.99){
    		cout << "\n\tALERT: MOTION DETECTED\n\n";
    		histR.copyTo(histR_old);
    	}
    	
    	imshow("image", image);

    	if(waitKey(30) >= 0) break;

	}
	return 0;
}