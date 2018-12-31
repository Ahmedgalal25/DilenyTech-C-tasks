#include "mainwindow.h"
#include "ui_mainwindow.h"
Mat g_src;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageViewer->setScaledContents(true);
    ui->lowpassImage->setScaledContents(true);
    ui->highpassImage->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Browsebtn_clicked()
{
    Mat lowImg=g_src;
    Mat highImg=g_src;
    Mat gray;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    //browsing dialog and read image by opencv Mat format
    QString filename = QFileDialog::getOpenFileName(this,tr("Open image"),"/home/galal/Pictures",tr("Images Files(*.png *.jpg)"));
    QString path =  filename;
    cv::Mat img=cv::imread(path.toStdString(),CV_LOAD_IMAGE_ANYCOLOR);
    g_src=img;

    // burring the image for lowpass filter
    blur(g_src,lowImg,Size(15,15));

    //high pass filter by apply sobelx,sobely and take the magnitude
    cvtColor(g_src, gray, CV_BGR2GRAY);
    Sobel( gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    Sobel( gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );
    convertScaleAbs( grad_y, abs_grad_y );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0,highImg );

    // converting from Mat image in opencv form into Qimage in qt form
    QImage qlowImg=  QImage( lowImg.data,lowImg.cols, lowImg.rows,static_cast<int>(lowImg.step),QImage::Format_RGB888 );
    QImage qhighImg=  QImage( highImg.data,highImg.cols, highImg.rows,static_cast<int>(highImg.step),QImage::Format_Grayscale8 );
    QImage image=  QImage( img.data,img.cols, img.rows,static_cast<int>(img.step),QImage::Format_RGB888 );

    //for viewing the 3 image and the directory at QLabels
    ui->imageViewer->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
    ui->lowpassImage->setPixmap(QPixmap::fromImage(qlowImg.rgbSwapped()));
    ui->highpassImage->setPixmap(QPixmap::fromImage(qhighImg.rgbSwapped()));
    ui->pathLabel->setText(path);
    ui->lowpassImage->show();
    ui->highpassImage->show();
    ui->imageViewer->show();
}
