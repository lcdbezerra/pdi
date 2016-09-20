#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main (int argc, char** argv){
	if (argc != 6){
		cout << "\tArgumentos invalidos" << endl << "\t./regions [imagem] x1 y1 x2 y2" << endl;
		return 0;
	}

	Mat image;
	unsigned char cor;
	int p1[2], p2[2];
	int x;

	p1[0] = atoi(argv[2]);
	p1[1] = atoi(argv[3]);

	p2[0] = atoi(argv[4]);
	p2[1] = atoi(argv[5]);

	if (p1[0] > p2[0]){
		x = p1[0];
		p1[0] = p2[0];
		p2[0] = x;
	}

	if (p1[1] > p2[1]){
		x = p1[1];
		p1[1] = p2[1];
		p2[1] = x;
	}

	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data){ cout << "Nao foi possivel carregar a imagem" << endl; return 0;}

	if (p1[0] > image.rows || p1[0] < 0 || p2[0] > image.rows || p2[0] < 0 || p1[1] > image.cols || p1[1] < 0 || p2[1] > image.cols || p2[1] < 0){
		cout << "\tArgumentos invalidos" << endl << "\tCertifique-se de que as coordenadas nao extrapolam a imagem" << endl << endl << "\tAltura:\t\t" << image.rows << endl << "\tLargura:\t" << image.cols << endl;
		return 0;
	}

	namedWindow("janela",WINDOW_AUTOSIZE);
	imshow("janela",image);
	waitKey();

	for (int i=p1[0];i<p2[0];i++){
		for (int j=p1[1];j<p2[1];j++){
			cor = image.at<uchar>(i,j);
			cor = 255 - cor;
			image.at<uchar>(i,j)=cor;
		}
	}

	imshow("janela",image);
	waitKey();
	return 0;
}