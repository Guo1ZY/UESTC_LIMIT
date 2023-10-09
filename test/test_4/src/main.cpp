/*
图片的读取和显示
*/
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv)
{
	// 读取图片, mat是matrix的缩写, 是一个矩阵, 跟python接口一样, python用numpy储存的
	cv::Mat image = cv::imread("./media/cat.jpg");
	// 判断是否读取成功
	if (image.empty())
	{
		printf("Cannot Read the images\n");
		return -1;
	}

	// print rows and cols
	printf("图片高度: %d \n图片宽度:  %d\n", image.rows, image.cols);

	// 以numpy 和 python两种方式打印图片
	#if 0
	// 以numpy的形式打印图片
	std::cout << cv::format(image, cv::Formatter::FMT_NUMPY) << std::endl;

	// 以python list的方式打印
	std::cout << cv::format(image, cv::Formatter::FMT_PYTHON) << std::endl;
	#endif
	
	// 创建一个灰度图, 数据类型是Mat
	cv::Mat gray;
	// 转换图像格式
	cv::cvtColor(image, gray, cv::COLOR_RGB2GRAY);

	// 保存
	cv::imwrite("./output1/gray.jpg", gray);

	return 0;
}

