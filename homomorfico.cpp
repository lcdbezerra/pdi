/////////////////////////////////////////////
//                                         //
//           FILTRO HOMOMORFICO            //
//                                         //
/////////////////////////////////////////////

// Declaracao de variaveis
Mat complexImage, padded, filter, tmp;
Mat_<float> realInput, zeros;
vector<Mat> planes;

if(!image.data)
    printf("\n\tNao foi possivel carregar a imagem\n\n");
    return;

// Padding
int dft_M = getOptimalDFTSize(image.rows), dft_N = getOptimalDFTSize(image.cols);
copyMakeBorder(image, padded, 0,
            dft_M - image.rows, 0,
            dft_N - image.cols,
            BORDER_CONSTANT, Scalar::all(0));


zeros = Mat_<float>::zeros(padded.size());
complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));

filter = complexImage.clone();

tmp = Mat(dft_M, dft_N, CV_32F);

float highFreq = (float)ui->highFreqSlider->value()/10, lowFreq = (float)ui->lowFreqSlider->value()/10, cParam  = (float)ui->cSlider->value()/10, d0 = ui->d0Slider->value();

int M = dft_M, N = dft_N;

for(int x=0; i<dft_M; i++){
    for(int y=0; j<dft_N; j++){
        tmp.at<float> (x,y) = (highFreq-lowFreq)*(1.0-exp(-1.0*(float)cParam*((((float)x-M/2.0)*((float)x-M/2.0) + ((float)y-N/2.0)*((float)y-N/2.0))/(d0*d0))))+ lowFreq;
    }
}

Mat comps[]= {tmp, tmp};
merge(comps, 2, filter);

realInput = Mat_<float>(padded);

planes.clear();
planes.push_back(realInput);
planes.push_back(zeros);
merge(planes, complexImage);

// DFT
dft(complexImage, complexImage);
shiftDFT(complexImage);

// Filtro em frequencia
mulSpectrums(complexImage,filter,complexImage,0);

planes.clear();
split(complexImage, planes);
merge(planes, complexImage);

shiftDFT(complexImage);

// DFT inversa
idft(complexImage, complexImage);

planes.clear();
split(complexImage, planes);
normalize(planes[0], planes[0], 0, 1, CV_MINMAX);

imshow("Original", image);
imshow("Filtrada", planes[0]);