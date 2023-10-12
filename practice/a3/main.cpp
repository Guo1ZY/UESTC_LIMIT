/*
3. 任务3——形态学操作

学习一些形态学操作，如膨胀、腐蚀、开运算、闭运算等

学习边缘提取（如Canny）和findContours函数，在任务二的基础上，实时提取出红色、蓝色、白色的轮廓，且利用形态学操作消除一些噪点（或一些面积过小的色块）

    要求：学会基础的形态学操作，辅助消除图像噪声等

*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;//命名空间
using namespace std;

int main() {
    VideoCapture cap("http://192.168.50.88:8081");  // 打开摄像头，您也可以使用图像文件
    //VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Camera not found." << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error: Frame is empty." << endl;
            break;
        }


/*
在无限循环中，首先创建一个`Mat`对象`frame`，用于存储捕获到的视频帧。
- 使用`cap >> frame`读取一帧视频，并检查该帧是否为空。如果帧为空，说明摄像头可能遇到问题，将打印错误消息并退出循环。
*/
        Mat hsv_frame;
        cvtColor(frame, hsv_frame, COLOR_BGR2HSV);//使用cvtColor函数将捕获到的BGR颜色空间的视频帧转换为HSV颜色空间
        //HSV色彩空间更适合颜色分析，因为它分离了颜色的色调、饱和度和亮度属性。

        // 定义红色、蓝色和白色的颜色范围
        Scalar lower_red(150, 100, 100);
        Scalar upper_red(180, 255, 255);
        Scalar lower_blue(90, 100, 100);
        Scalar upper_blue(150, 255, 255);
        Scalar lower_white(30, 0, 200);
        Scalar upper_white(255, 30, 255);

        Mat mask_red, mask_blue, mask_white;
        inRange(hsv_frame, lower_red, upper_red, mask_red);
        inRange(hsv_frame, lower_blue, upper_blue, mask_blue);
        inRange(hsv_frame, lower_white, upper_white, mask_white);

        Mat result;
        bitwise_or(mask_red, mask_blue, result);
        bitwise_or(result, mask_blue, result);//三种颜色

        // 形态学操作
        Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(result, result, MORPH_OPEN, kernel);
        morphologyEx(result, result, MORPH_CLOSE, kernel);
        /*
        创建一个形态学操作的内核，以便对result图像进行开运算和闭运算。这些操作用于去除噪声并平滑对象的边界。
        */

        // 查找轮廓
        vector<vector<Point>> contours;
        findContours(result, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        /*
        使用findContours函数查找result图像中的轮廓，将轮廓信息存储在contours中。
        创建原始图像的克隆副本contour_frame，并使用drawContours函数将找到的轮廓绘制在副本上，以绿色线条表示。
        */

        // 绘制轮廓
        Mat contour_frame = frame.clone();
        drawContours(contour_frame, contours, -1, Scalar(0, 0, 255), 2);

        imshow("Original Frame", frame);
        imshow("Processed Frame", contour_frame);

        if (waitKey(10) == 27)  // 按ESC键退出
            break;
    }

    return 0;
}
