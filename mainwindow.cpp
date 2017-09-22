#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    unsigned t0, t1;
    t0=clock();    
        
    Mat inputImage = cv::imread("/home/nakio/Escritorio/fox.jpg");
    Mat auxImage = cv::imread("/home/nakio/Escritorio/fox.jpg");

    float gamma = 0.5;
    unsigned char lut[256];
    for (int i = 0; i < 256; i++){
    lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
    }
    Mat dst = auxImage.clone();
    const int channels = dst.channels();
    switch (channels) {
    case 1:
    {
        MatIterator_<uchar> it,end;
        for (it=dst.begin<uchar>(),end = dst.end<uchar>(); it != end; it++){
            *it = lut[(*it)];
        }
        break;
    }
    case 3:
    {
        MatIterator_<Vec3b> it,end;
        for(it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++){

            (*it)[0] = lut[((*it)[0])];

            (*it)[1] = lut[((*it)[1])];

            (*it)[2] = lut[((*it)[2])];
        }
        break;
    }
    }
    imshow("Imagen Original",inputImage);
    imshow("Imagen Modificada",dst);
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;    
}

MainWindow::~MainWindow()
{
    delete ui;
}
