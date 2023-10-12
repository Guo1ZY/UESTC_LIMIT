#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/ModelCoefficients.h>

int main()
{
    // 创建PCL可视化器对象
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("PointCloud Viewer"));

    // 设置可视化窗口的背景颜色为白色
    viewer->setBackgroundColor(1, 1, 1);

    // 创建一个红色平面
    pcl::ModelCoefficients::Ptr plane_coefficients(new pcl::ModelCoefficients);
    plane_coefficients->values.resize(4);
    plane_coefficients->values[0] = 0;
    plane_coefficients->values[1] = 0;
    plane_coefficients->values[2] = 1;  // 法向量的z分量为1，表示平面垂直于z轴
    plane_coefficients->values[3] = 0;  // 平面方程的截距

    // 添加平面到可视化窗口，设置颜色为红色
    viewer->addPlane(*plane_coefficients, "plane", 0);
    viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 0, "plane");

    // 启动交互模式
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
    }

    return 0;
}
