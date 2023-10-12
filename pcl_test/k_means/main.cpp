#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/io/pcd_io.h> 

int main()
{
    // 创建点云对象 'cloud' 并用数据填充它
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    // 用您的点云数据填充 'cloud' 点云对象
if (pcl::io::loadPCDFile<pcl::PointXYZ>("/home/zy/pcl/test/five_people.pcd", *cloud) == -1)
    {
        PCL_ERROR("Couldn't read the PCD file.\n");
        return -1;
    }

    // 创建 KD 树
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud(cloud);

    // 创建一个向量来存储聚类结果
    std::vector<pcl::PointIndices> cluster_indices;

    // 创建K均值聚类对象
    pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
    ec.setClusterTolerance(0.02);  // 聚类容差（距离阈值）
    ec.setMinClusterSize(100);     // 最小聚类大小
    ec.setMaxClusterSize(25000);   // 最大聚类大小
    ec.setSearchMethod(tree);
    ec.setInputCloud(cloud);
    ec.extract(cluster_indices);

    // 输出聚类结果
    for (const pcl::PointIndices& indices : cluster_indices)
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cluster(new pcl::PointCloud<pcl::PointXYZ>);
        for (int index : indices.indices)
        {
            cluster->push_back(cloud->points[index]);
        }

        // 在这里，'cluster' 包含一个聚类
        std::cout << "Cluster size: " << cluster->size() << std::endl;
    }

    return 0;
}
