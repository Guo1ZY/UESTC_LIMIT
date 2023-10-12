#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
int main()
{
    // 创建一个 pcl::PointCloud 对象，使用 pcl::PointXYZ 数据类型
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 添加一些点到点云中
    for (float x = -1.0f; x <= 1.0f; x += 0.05f)
    {
        for (float y = -1.0f; y <= 1.0f; y += 0.1f)
        {
            float z = x * x + y * y; // 点的高度值
            pcl::PointXYZ point(x, y, z);
            cloud->push_back(point);
        }
    }
    /*
    外循环 for (float x = -1.0f; x <= 1.0f; x += 0.1f) 控制 x 坐标的范围从 -1.0 到 1.0，以0.1为步进。

内循环 for (float y = -1.0f; y <= 1.0f; y += 0.1f) 控制 y 坐标的范围从 -1.0 到 1.0，以0.1为步进。

在内循环中，通过 z = x * x + y * y 计算每个点的高度值，这个高度值将根据 x 和 y 坐标而变化。
    使用 pcl::PointXYZ 创建一个点对象，传入 x、y、z 坐标值。

使用 cloud->push_back(point) 将每个点添加到 pcl::PointCloud 对象中。


    */

    // 遍历并访问点云中的点
    // 创建可视化窗口
    pcl::visualization::PCLVisualizer viewer("PointCloud Viewer");

    // 设置背景颜色
    viewer.setBackgroundColor(0, 0, 0);//黑

    // 添加点云数据到可视化窗口
    viewer.addPointCloud(cloud, "cloud");

    // 设置点云渲染属性
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "cloud");

    // 主循环，直到可视化窗口被关闭
    while (!viewer.wasStopped())
    {
        viewer.spinOnce();
    }

    return 0;
}


