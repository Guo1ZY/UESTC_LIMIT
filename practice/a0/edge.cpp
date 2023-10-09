#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <iostream>
using namespace cv;
using namespace std;
 
int threshold_value = 50, threshold_max = 255;
int threshold_type = 0, threshold_type_max = 4;
string outwindow = "1 img";
Mat src, dst;
int main(){
    Mat src1;
    src1 = imread("/home/zy/pictures/1.jpg");
   // resize(src1, src, Size(src1.cols, src1.rows)); 
    resize(src1, src, Size(src1.cols/2, src1.rows/2)); //缩小一半 
    if (!src.data){
        printf("cannot load image ...");
        return -1;
    }
    namedWindow("src img", WINDOW_AUTOSIZE);
    imshow("src img", src);
    
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    //canny边缘检测算子
    Canny(src_gray, dst, 100, 200);
    imshow("canny", dst);
    imshow("canny~", ~dst); //dst按照像素值取反
    
    waitKey(0);
    return 0;
}
