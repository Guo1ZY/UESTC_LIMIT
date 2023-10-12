#include <opencv2/opencv.hpp>

int main() {
    cv::Mat input_image = cv::imread("/home/zy/pictures/Tom.png", cv::IMREAD_COLOR);
    if (input_image.empty()) {
        std::cerr << "Error: Cannot read the input image." << std::endl;
        return -1;
    }

    cv::Mat filtered_image;
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1); // 自定义卷积核
    cv::filter2D(input_image, filtered_image, -1, kernel);

    cv::imshow("Input Image", input_image);
    cv::imshow("Filtered Image", filtered_image);
    cv::waitKey(0);

    return 0;
}
