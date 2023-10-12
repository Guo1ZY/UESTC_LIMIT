#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    VideoCapture camera(0);//似乎用手机ip极为卡顿，最好用电脑自带的

    if (!camera.isOpened()) {
        cerr << "Error: Camera not found." << endl;
        return -1;
    }
    CascadeClassifier face_cascade;// 创建人脸识别器，必须要绝对路径啊啊啊啊啊啊！！！！！！！！！！，疯掉了！！！！！！！
    if (!face_cascade.load("/media/zy/果果的500G大硬盘/培训一/┼α╤╡╥╗/opencv-4.8.0.zip/opencv-4.8.0/data/haarcascades_cuda/haarcascade_frontalface_alt.xml")) {
        cerr << "Error: Haar Cascade Classifier not found." << endl;
        return -1;
    }
    while (true) {
        Mat frame;
        camera >> frame;

        vector<Rect> faces;
        face_cascade.detectMultiScale(frame, faces); // 在帧上进行人脸检测

        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(0, 0, 255), 2);  // 使用红色标记记住红色就是255，scalar三个参数（RGB）顺序为BLUE，GREEN，RED
        }

        imshow("Face Recognition", frame);

        if (waitKey(30) == 27) {  // 按ESC键退出，其实任意键也可以
            break;
        }
    }
    return 0;
}
