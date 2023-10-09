#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <arpa/inet.h> // 包含 htonl 函数的头文件

using namespace cv;
using namespace std;

int main() {
    // 打开摄像头
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Camera not found." << endl;
        return -1;
    }

    // 初始化串口
    int serialPort = open("/dev/ttyUSB1", O_RDWR);
    if (serialPort == -1) {
        cerr << "Error opening serial port" << endl;
        return -1;
    }

    // 设置串口波特率为115200（根据实际需求修改）
    int baudRate = B115200;
    struct termios tty;
    if (tcgetattr(serialPort, &tty) != 0) {
        cerr << "Error getting serial port attributes" << endl;
        return -1;
    }
    cfsetospeed(&tty, baudRate);
    cfsetispeed(&tty, baudRate);
    if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
        cerr << "Error setting serial port attributes" << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error: Frame is empty." << endl;
            break;
        }

        // 转换色彩空间为HSV
        Mat hsv_frame;
        cvtColor(frame, hsv_frame, COLOR_BGR2HSV);

        // 定义红色范围
        Scalar lower_red(150, 100, 100);
        Scalar upper_red(180, 255, 255);

        // 提取红色区域
        Mat mask_red;
        inRange(hsv_frame, lower_red, upper_red, mask_red);

        // 查找红色区域的轮廓
        vector<vector<Point>> contours;
        findContours(mask_red, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // 查找最大的红色区域
        double max_area = 0;
        int max_index = -1;
        for (int i = 0; i < contours.size(); i++) {
            double area = contourArea(contours[i]);
            if (area > max_area) {
                max_area = area;
                max_index = i;
            }
        }

        if (max_index != -1) {
            // 计算最大红色区域的中心坐标
            Moments mu = moments(contours[max_index]);
            int centerX = mu.m10 / mu.m00;
            int centerY = mu.m01 / mu.m00;

            // 构造发送数据
            char sendBuffer[12];
            sendBuffer[0] = '?';
            sendBuffer[1] = '!';
            sendBuffer[2] = 'A';

            // 将X和Y坐标转换为网络字节顺序（大端）并填充到sendBuffer
            int32_t netX = htonl(centerX);
            int32_t netY = htonl(centerY);
            memcpy(&sendBuffer[3], &netX, sizeof(int32_t));
            memcpy(&sendBuffer[7], &netY, sizeof(int32_t));

            sendBuffer[11] = '!';

            // 发送数据到串口
            write(serialPort, sendBuffer, sizeof(sendBuffer));
            usleep(100000);
        }

        imshow("Camera", frame);

        // 按下ESC键退出循环
        if (waitKey(10) == 27) {
            break;
        }
    }

    // 关闭串口和摄像头
    close(serialPort);
    cap.release();
    destroyAllWindows();

    return 0;
}
