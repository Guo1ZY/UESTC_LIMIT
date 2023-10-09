#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat image;


// void onMouse_RGB(int event, int x, int y, int flags, void* param) {
//     if (event == EVENT_LBUTTONDOWN) {
//         Vec3b pixel = image.at<Vec3b>(y, x);  // 获取像素值
//         int blue = pixel[0];
//         int green = pixel[1];
//         int red = pixel[2];
        
//         cout << "RGB at (" << x << ", " << y << "): ";
//         cout << "R=" << red << ", G=" << green << ", B=" << blue << endl;
//     }
// }


void onMouse_HSV(int event, int x, int y, int flags, void* param) {
    if (event == EVENT_LBUTTONDOWN) {
        Vec3b pixel = image.at<Vec3b>(y, x);  // 获取像素值
        Mat3b hsvPixel;
        cvtColor(Mat(1, 1, CV_8UC3, pixel), hsvPixel, COLOR_BGR2HSV);

        int hue = hsvPixel(0, 0)[0];
        int saturation = hsvPixel(0, 0)[1];
        int value = hsvPixel(0, 0)[2];

        cout << "HSV at (" << x << ", " << y << "): ";
        cout << "H=" << hue << ", S=" << saturation << ", V=" << value << endl;
    }
}
/*
Vec3b pixel = image.at<Vec3b>(y, x);：

image是输入图像。
.at<Vec3b>(y, x)表示在图像中获取位于(x, y)位置的像素值。Vec3b表示这是一个包含3个8位无符号整数的向量，对应于图像中的蓝色、绿色和红色（BGR）通道值。
Mat3b hsvPixel;：

Mat3b是一个3通道的Mat（矩阵）类型，用于存储HSV颜色信息。
这里创建了一个名为hsvPixel的Mat对象，用于存储HSV颜色信息。
接下来，代码使用cvtColor函数将RGB颜色值转换为HSV颜色值，并将结果存储在hsvPixel Mat中，以便提取HSV通道的值。然后，它从hsvPixel Mat中提取了H（色调）、S（饱和度）和V（亮度/值）的值，以获取特定点的HSV颜色信息。

这样，您就可以通过pixel变量获取RGB颜色值，并通过hsvPixel变量获取HSV颜色值，以进一步分析和处理图像中特定点的颜色信息。
*/

int main() {
    image = imread("/home/zy/pictures/1.jpg");  // 读取图像

    cv::Size smallSize(640, 480); // 设置目标尺寸
    cv::resize(image, image, smallSize);

    if (image.empty()) {
        cerr << "Error: Image not found." << endl;
        return -1;
    }

    namedWindow("Image");
    imshow("Image", image);

    setMouseCallback("Image", onMouse_HSV, NULL);  // 设置鼠标回调函数,这里修改mouse_RGB还是mouse_HSV
  

    waitKey(0);
    destroyAllWindows();

    return 0;
}
