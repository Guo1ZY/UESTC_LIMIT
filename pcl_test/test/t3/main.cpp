#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>

int main()
{
    // 创建点云对象来存储PCD文件中的数据
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // 加载PCD文件
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("/home/zy/pcl/test/five_people.pcd", *cloud) == -1)
    {
        PCL_ERROR("Couldn't read file five_people.pcd\n");
        return (-1);
    }

    // 创建PCL可视化器对象
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("PointCloud Viewer"));

    // 设置可视化窗口的背景颜色为黑色
    viewer->setBackgroundColor(0, 0, 0);

    // 将点云添加到可视化窗口中
    viewer->addPointCloud<pcl::PointXYZ>(cloud, "cloud");

    // 设置点云的渲染属性，例如点的大小
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");

    // 主循环，直到可视化窗口被关闭
    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
       
    }

    return 0;
}
