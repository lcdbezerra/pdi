#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	if (argc != 2){
		cout << "\tArgumento invalido" << endl << "\t./buracos [imagem]" << endl;
		return 0;
	}

	Mat image, mask;
	CvPoint p;
	int fill = 0, nobjects = 0, nburacos = 0;

	p.x = 0;
	p.y = 0;

	image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	if(!image.data){ cout << "Nao foi possivel carregar a imagem" << endl; return -1;}

	int width = image.size().width;
  	int height = image.size().height;


	//Percorrer o perimetro da imagem apagando qualquer objeto que toque a borda
	for (int i = 0; i < height; i++){
		// Borda esquerda
		if(image.at<uchar>(i,0) == 255){
			p.y = i;
			p.x = 0;
			floodFill(image,p,0);
		}
		// Borda direita
		if(image.at<uchar>(i,width-1) == 255){
			p.y = i;
			p.x = width-1;
			floodFill(image,p,0);
		}
	}
	for (int j = 0; j < width; j++){
		// Borda superior
		if(image.at<uchar>(0,j) == 255){
			p.y = 0;
			p.x = j;
			floodFill(image,p,0);
		}
		// Borda inferior
		if(image.at<uchar>(height-1,j) == 255){
			p.y = height-1;
			p.x = j;
			floodFill(image,p,0);
		}
	}

	//Encontrar e rotular cada um dos objetos
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if(image.at<uchar>(i,j) == 255){
				// Objeto encontrado
				nobjects++;
				p.x = j;
				p.y = i;
				floodFill(image,p,nobjects);
			}
		}
	}

	// Preenche o fundo da imagem com branco para não confundir com os buracos dos objetos
	p.x = 0;
	p.y = 0;
	floodFill(image,p,255);

	// Para cada objeto encontrado, verifica se ele possui um buraco
	for (int z = 1; z <= nobjects; z++){
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				if (image.at<uchar>(i,j) == z){
					if (image.at<uchar>(i+1,j) == 0){
						nburacos++;
						p.x = j;
						p.y = i+1;
						floodFill(image,p,255);
					} else if (image.at<uchar>(i,j+1) == 0){
						nburacos++;
						p.x = j+1;
						p.y = i;
						floodFill(image,p,255);
					} else if (image.at<uchar>(i,j-1) == 0){
						nburacos++;
						p.x = j-1;
						p.y = i;
						floodFill(image,p,255);
					} else if (image.at<uchar>(i-1,j) == 0){
						nburacos++;
						p.x = j;
						p.y = i-1;
						floodFill(image,p,255);
					}
				}
			}
		}
	}
	cout << nburacos << endl;


	imshow("janela",image);
	waitKey();
	return 0;
}