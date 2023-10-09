#include <opencv2/opencv.hpp>

int main() {
    // 创建一个3x3的灰度图像
    cv::Mat grayImage(3, 3, CV_8UC1); // CV_8UC1表示8位无符号单通道图像

    // 设置像素值
    grayImage.at<uchar>(0, 0) = 100;
    grayImage.at<uchar>(1, 1) = 200;
    grayImage.at<uchar>(2, 2) = 50;

    // 访问像素值
    uchar pixelValue = grayImage.at<uchar>(1, 1);
    std::cout << "Pixel Value at (1,1): " << static_cast<int>(pixelValue) << std::endl;

    return 0;
}
