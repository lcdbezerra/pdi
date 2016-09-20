#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Scalar nobjects;

Scalar returnObject();

int main(int argc, char** argv){
  Mat image;
  int width, height;
  
  CvPoint p;

  image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
  if(!image.data){ cout << "Nao foi possivel carregar a imagem" << endl; return -1;}

  width=image.cols;
  height=image.rows;

  p.x=0;
  p.y=0;

  // busca objetos com buracos presentes
  nobjects[0]=128;
  nobjects[1]=128;
  nobjects[2]=0;

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<Vec3b>(i,j) == (255,255,255)){
		// achou um objeto
		p.x=j;
		p.y=i;
		floodFill(image,p,nobjects);
	  }
	}
  }
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}

Scalar returnObject(){
  if (nobjects[0]<255){
    nobjects[0]++;
  } else if (nobjects[1]<255){
    nobjects[1]++;
    nobjects[0]=0;
  } else {
    nobjects[2]++;
    nobjects[1]=0;
    nobjects[0]=0;
  }

  return nobjects;
}