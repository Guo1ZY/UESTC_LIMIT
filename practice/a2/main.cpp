#include <opencv2/opencv.hpp>

int main() {
    // 打开摄像头
    cv::VideoCapture cap("http://192.168.50.88:8081");//手机ip

    // 检查摄像头是否成功打开
    if (!cap.isOpened()) {//1
        std::cerr << "无法打开摄像头" << std::endl;
        return -1;//error
    }

    cv::Mat frame;
    while (true) {//一直循环
        // 读取一帧图像
        cap >> frame;

        cv::Mat result1;
        cv::Mat result2;
        cv::Mat result3;
        // 调整图像尺寸为更小的尺寸
        cv::Size smallSize(640, 480); // 设置目标尺寸
        cv::resize(frame, frame, smallSize);

        // 转换色彩空间为HSV
        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 定义红色范围
        cv::Scalar lower_red(150, 100, 100);
        cv::Scalar upper_red(180, 255, 255);

        // 定义蓝色范围
        cv::Scalar lower_blue(90, 100, 100);
        cv::Scalar upper_blue(150, 255, 255);

        // 定义白色范围
        cv::Scalar lower_white(0, 0, 200);
        cv::Scalar upper_white(255, 30, 255);

        // 提取红色、蓝色和白色
        cv::Mat mask_red, mask_blue, mask_white;
        cv::inRange(hsv, lower_red, upper_red, mask_red);
        cv::inRange(hsv, lower_blue, upper_blue, mask_blue);
        cv::inRange(hsv, lower_white, upper_white, mask_white);


        // 调整颜色提取结果的尺寸
        cv::resize(mask_red, mask_red, smallSize);
        cv::resize(mask_blue, mask_blue, smallSize);
        cv::resize(mask_white, mask_white, smallSize);

        cv::bitwise_and(frame, frame, result1, mask_red);
        cv::bitwise_and(frame, frame, result2, mask_blue);
        cv::bitwise_and(frame, frame, result3, mask_white);


        // 显示原始图像和颜色提取结果
        cv::imshow("Camera", frame);
        cv::imshow("Red", result1);
        cv::imshow("Blue", result2);
        cv::imshow("White", result3);


        // 等待用户按下ESC键后退出循环
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    // 关闭摄像头
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
/*
HSV（Hue, Saturation, Value）是一种描述颜色的色彩空间，与常见的RGB（红绿蓝）色彩空间不同，它更符合人类感知颜色的方式。HSV将颜色的属性分成三个主要的组成部分：

色调（Hue）：色调表示颜色的基本属性，通常以角度度量（0°到360°），对应于在色轮上的颜色位置。例如，0°表示红色，60°表示黄色，120°表示绿色，以此类推。色调决定了颜色的种类，而不考虑其亮度或饱和度。

饱和度（Saturation）：饱和度表示颜色的纯度或鲜艳程度。饱和度较高的颜色看起来更鲜艳，而饱和度较低的颜色则更接近灰度。饱和度的取值范围通常是0%到100%，其中0%表示灰度（无色彩），100%表示完全鲜艳的颜色。

亮度（Value）：亮度表示颜色的明暗程度。较高的亮度值表示颜色较亮，而较低的亮度值表示颜色较暗。亮度的取值范围通常也是0%到100%，其中0%表示完全黑色，100%表示最亮的颜色。

HSV色彩空间的优点之一是，它允许我们更容易地控制和分析颜色属性，特别是在计算机视觉和图像处理领域中。例如，您可以轻松地调整颜色的饱和度来增强或减弱颜色的强度，而无需考虑RGB色彩空间中复杂的颜色混合。

在OpenCV等图像处理库中，HSV色彩空间通常用于颜色分割、对象检测和颜色调整等任务，因为它更直观和方便于处理各种颜色操作。
*/