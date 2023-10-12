/*
4. 任务4——透视变换

学习掌握透视变换的原理

重点掌握getPerspectiveTransform和warpPerspective两个函数，拍摄一个物体（如A4纸），并利用透视变换校正视角为正视该物体

    要求：学会利用透视变换获取不同的视角

*/
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // 读取拍摄的A4纸图像
    Mat image = imread("/home/zy/pictures/A4_2.png");
    if (image.empty()) {
        cerr << "Error: Image not found." << endl;
        return -1;
    }

    cv::Size smallSize(640, 480); // 设置目标尺寸
    cv::resize(image, image, smallSize);

    // 定义A4纸的四个角点
    vector<Point2f> srcPoints;
    srcPoints.push_back(Point2f(250, 100));  // 左上角
    srcPoints.push_back(Point2f(550, 100));  // 右上角
    srcPoints.push_back(Point2f(200, 400));  // 左下角
    srcPoints.push_back(Point2f(600, 400));  // 右下角

    // 定义A4纸的目标四个角点（正视角）
    vector<Point2f> dstPoints;
    dstPoints.push_back(Point2f(0, 0));      // 左上角
    dstPoints.push_back(Point2f(210, 0));    // 右上角
    dstPoints.push_back(Point2f(0, 297));    // 左下角
    dstPoints.push_back(Point2f(210, 297));  // 右下角

    // 获取透视变换矩阵
    Mat perspectiveMatrix = getPerspectiveTransform(srcPoints, dstPoints);

    // 进行透视变换
    Mat result;
    warpPerspective(image, result, perspectiveMatrix, Size(210, 297));

    // 显示原始图像和校正后的图像
    imshow("Original Image", image);
    imshow("Perspective Corrected Image", result);

    waitKey(0);
    destroyAllWindows();

    return 0;
}

/*
透视变换是一种图像处理技术，用于将一个透视投影（例如照相机视角下的图像）转换为平面视图（例如正视图），或者反之。它的原理基于投影几何学，主要包括以下关键概念：

透视投影：当我们在三维世界中观察物体时，它们的图像在投影到二维平面上时会发生透视效应。这意味着远离观察者的物体部分会在投影中变小，而靠近观察者的部分会变大。
这种透视效应是造成视角变形的原因。

透视投影矩阵：透视投影可以使用一个矩阵来描述，称为透视投影矩阵。这个矩阵将三维坐标映射到二维图像坐标。
透视投影矩阵包括摄像机的内部参数（如焦距和图像中心点）和外部参数（如摄像机位置和方向）。

透视变换：透视变换是将图像从透视投影转换为平行投影（正交投影）或反之的过程。透视变换矩阵用于执行这种转换。
它可以应用于图像中的每个像素点，以将其从一种视角变换到另一种视角。

透视变换矩阵：透视变换矩阵是一个3x3矩阵，通常表示为H，它用于将一个平面上的点映射到另一个平面上。
在OpenCV中，可以使用getPerspectiveTransform函数来计算透视变换矩阵。

透视变换的步骤如下：

确定原始图像中的四个关键点，这些点定义了您想要变换的区域，通常是一个四边形，表示物体的透视投影。

确定目标图像中的四个关键点，这些点定义了变换后的正视图中的相应区域。

使用getPerspectiveTransform函数计算透视变换矩阵，该矩阵将原始图像中的四个关键点映射到目标图像中的四个关键点。

使用warpPerspective函数将原始图像应用透视变换矩阵，从而将其转换为正视图或其他所需的视角。

透视变换常用于计算机视觉、图像校正和机器视觉中，以便更好地理解和分析三维世界中的物体。
这个技术允许我们从不同视角捕捉的图像中获取准确的信息，以支持各种应用，如物体检测、位姿估计和虚拟现实等。


*/