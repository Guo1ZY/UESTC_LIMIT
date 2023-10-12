#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>

int main()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    // Load the PCD file
    if (pcl::io::loadPCDFile<pcl::PointXYZ>("five_people.pcd", *cloud) == -1)
    {
        PCL_ERROR("Couldn't read file five_people.pcd\n");
        return (-1);
    }

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("PointCloud Viewer"));

    viewer->setBackgroundColor(0, 0, 0);
    viewer->addPointCloud<pcl::PointXYZ>(cloud, "cloud");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");

    while (!viewer->wasStopped())
    {
        viewer->spinOnce(100);
        
    }

    return 0;
}
