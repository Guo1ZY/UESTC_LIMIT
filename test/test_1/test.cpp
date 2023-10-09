#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/cudev.hpp>
#include <opencv2/cudabgsegm.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudalegacy.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaoptflow.hpp>
#include <opencv2/cudastereo.hpp>
#include <opencv2/cudawarping.hpp>
 
 
 
int main() {
 
    cv::Mat img1 = cv::imread("/home/zy/pictures/Tom.png");
    cv::Mat img3;
    cv::cuda::GpuMat cuda_img1, cuda_img2, cuda_img3;
    cuda_img1.upload(img1);
 
 
    // cv::cuda::cvtColor(cuda_img1,cuda_img3,cv::COLOR_BGR2GRAY);
 
    cuda_img3.download(img3);
 
    cv::namedWindow("cuda_gpu", cv::WINDOW_NORMAL);
    cv::imshow("cuda_gpu", img3);
    cv::waitKey(0);
 
 
    return 0;
 
}