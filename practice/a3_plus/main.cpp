#include <opencv2/opencv.hpp>

int main() {
    cv::Mat input_image = cv::imread("/home/zy/pictures/Tom.png", cv::IMREAD_GRAYSCALE);
    if (input_image.empty()) {
        std::cerr << "Error: Cannot read the input image." << std::endl;
        return -1;
    }

    cv::Mat closed_image;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));  // 定义内核
    cv::morphologyEx(input_image, closed_image, cv::MORPH_CLOSE, kernel);

    cv::imshow("Input Image", input_image);
    cv::imshow("Closed Image", closed_image);
    cv::waitKey(0);

    return 0;
}