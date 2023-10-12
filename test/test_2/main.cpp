#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
 
void main(){
    VideoCapture cap;
    cap.open("./turtle.mp4");
 
    if(!cap.isOpened())
        return;
 
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);  //帧宽度
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //帧高度
    int frameRate = cap.get(CV_CAP_PROP_FPS);  //帧率 x frames/s
    int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //总帧数
 
    cout<<"视频宽度="<<width<<endl;
    cout<<"视频高度="<<height<<endl;
    cout<<"视频总帧数="<<totalFrames<<endl;
    cout<<"帧率="<<frameRate<<endl;
 
    Mat frame;
    while(1)
    {
        cap>>frame;//等价于cap.read(frame);
        if(frame.empty())
            break;
        imshow("video", frame);
        if(waitKey(20)>0)
            break;
    }
    cap.release();
 
 
    ///方法2.
    std::string camera_input = ".....";  //视频地址
    cv::VideoCapture vc(camera_input);
    if (!vc.isOpened()) {
        // error in opening the video input
        std::cerr << "Failed to open camera.\n";
        return -1;
    }
    cv::Mat rawInput;
    while (true) {
        bool ret = vc.read(rawInput);
        if (!ret) {
            std::cerr << "ERROR: Cannot read frame from stream\n";
            continue;
        }
    }
}