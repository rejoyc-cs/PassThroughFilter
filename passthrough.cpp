#include <iostream>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

#include <pcl/visualization/pcl_visualizer.h>

int
 main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

/* Creating a random point cloud */

  // Fill in the cloud data
  cloud->width  = 10000;
  cloud->height = 1;
  cloud->points.resize (cloud->width * cloud->height);

  for (auto& point: *cloud)
  {
    point.x = 1024 * rand () / (RAND_MAX + 1.0f);
    point.y = 1024 * rand () / (RAND_MAX + 1.0f);
    point.z = 1024 * rand () / (RAND_MAX + 1.0f);
  }

  /* If You Want to Print The Point Locations
  std::cerr << "Cloud before filtering: " << std::endl;
  for (const auto& point: *cloud)
    std::cerr << "    " << point.x << " "
                        << point.y << " "
                        << point.z << std::endl;
 */
  // Create the filtering object
  pcl::PassThrough<pcl::PointXYZ> pass;
  pass.setInputCloud (cloud);
  pass.setFilterFieldName ("z"); //Provide the name of the field to be used for filtering data.
  pass.setFilterLimits (0.0, 1.0); //All points having field values outside this interval will be discarded.
  pass.setFilterLimitsNegative (true); //Just complement the range of setFilterLimits()
  pass.filter (*cloud_filtered);

  /*If You Want to Print The Point Locations
  std::cerr << "Cloud after filtering: " << std::endl;
  for (const auto& point: *cloud_filtered)
    std::cerr << "    " << point.x << " "
                        << point.y << " "
                        << point.z << std::endl;

  
  */
  pcl::visualization::PCLVisualizer viewer ("Pass Though Filter");

  // We add the point cloud to the viewer and pass the color handler
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> original_cloud(cloud, 255, 255, 255);
  viewer.addPointCloud (cloud, original_cloud, "original_cloud");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> filtered_cloud (cloud_filtered, 230, 20, 20); // Red
  viewer.addPointCloud (cloud_filtered, filtered_cloud, "transformed_cloud");

  viewer.addCoordinateSystem (1.0, "cloud", 0);
  viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "original_cloud");
  viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");
  //viewer.setPosition(800, 400); // Setting visualiser window position

  while (!viewer.wasStopped ()) { // Display the visualiser until 'q' key is pressed
    viewer.spinOnce ();
  }                    

  return (0);
}


/* Code Documentation:
http://pointclouds.org/documentation/tutorials/passthrough.html#passthrough

<pcl/filters/passthrough.h> Documentation:
https://pointclouds.org/documentation/classpcl_1_1_pass_through_3_01pcl_1_1_p_c_l_point_cloud2_01_4.html#a6a8fc75a0f2e78f008d102cdd07709d3
*/