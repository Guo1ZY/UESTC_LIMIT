#include <opencv2/opencv.hpp>//包含库

int main() {
    // 读取图片
    cv::Mat image = cv::imread("/home/zy/pictures/12.jpg");

    // 检查是否成功读取图片
    if (image.empty()) {//empty返回值为1，执行以下程序
        std::cerr << "无法读取图片" << std::endl;
        return -1;//error
    }

    // 创建一个窗口并显示图片
    cv::imshow("Image", image);

    // 等待用户按下任意键后关闭窗口
    cv::waitKey(0);

    return 0;
}
