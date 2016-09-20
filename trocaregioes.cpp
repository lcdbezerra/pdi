#include <iostream>
#include <random>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main (int argc, char** argv){
	if (argc != 3){
		cout << "\tArgumentos invalidos" << endl << "\t./regions [imagem] n_partes_lado" << endl;
		return 0;
	}

	Mat im, swap, new_im(256,256,CV_8UC1);
	vector<unsigned int> rand_x, rand_y;
	namedWindow(argv[1],WINDOW_AUTOSIZE);
	int n, quad[2];

	im = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	if(!im.data){ cout << "Nao foi possivel carregar a imagem" << endl; return 0;}
	//im.copyTo(new_im);
	imshow(argv[1],im);
	waitKey();

	n = atoi(argv[2]);
	quad[0] = im.rows/n;
	quad[1] = im.cols/n;

	for (int x = 0; x < n; x++){
		rand_x.push_back(x);
	}
	std::random_shuffle(rand_x.begin(),rand_x.end());

	for (int y = 0; y < n; y++){
		rand_y.push_back(y);
	}
	std::random_shuffle(rand_y.begin(),rand_y.end());

	for (int i = 0; i < new_im.rows; i++){
		for (int j = 0; j < new_im.cols; j++){
			new_im.at<uchar>(i,j) = im.at<uchar>(i%quad[0] + rand_x[i/quad[0]]*quad[0],j%quad[1] + rand_y[j/quad[1]]*quad[1]);
		}
	}

	cout << "new_im.at<uchar>(i,j) = im.at<uchar>(" << rand_y[25/quad[1]] << " * " << quad[1] << " + " << 25 << endl;
	cout << "new_im.at<uchar>(i,j) = im.at<uchar>(" << rand_y[125/quad[1]] << " * " << quad[1] << " + " << 125 << endl;
	cout << "new_im.at<uchar>(i,j) = im.at<uchar>(" << rand_y[225/quad[1]] << " * " << quad[1] << " + " << 225 << endl;

	imshow("embaralhado",new_im);
	waitKey();

	return 0;
}