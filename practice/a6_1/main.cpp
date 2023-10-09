#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image = cv::imread("/home/zy/pictures/circle.jpg", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Cannot read the input image." << std::endl;
        return -1;
    }

    cv::Mat gray_image;
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    // 霍夫圆检测
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray_image, circles, cv::HOUGH_GRADIENT, 1, gray_image.rows / 8, 200, 100, 0, 0);

    // 绘制检测到的圆
    for (size_t i = 0; i < circles.size(); i++) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(image, center, radius, cv::Scalar(255, 0, 255), 2);
    }

    cv::imshow("Detected Circles", image);
    cv::waitKey(0);

    return 0;
}
