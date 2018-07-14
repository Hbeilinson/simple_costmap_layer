# include "ros/ros.h"
# include "std_msgs/String.h"
# include "std_msgs/Header.h"
# include "nav_msgs/OccupancyGrid.h"
// #include <opencv2/core/core.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
# include "GRIDMAP2D_GRIDMAP2D_H_"

using namespace nav_msgs;
// using namespace gridmap_2d;

class Convert_To_Image
{
public:
  ros::Subscriber costmap_sub;
  ros::Publisher image_pub;

  Convert_To_Image();
  void costmap_callback(const OccupancyGrid& grid);

};

Convert_To_Image::Convert_To_Image()
{
  ros::NodeHandle nh;
  costmap_sub = nh.subscribe("/move_base/global_costmap/costmap", 1, &Convert_To_Image::costmap_callback, this);
  image_pub = nh.advertise<GridMap2D>("my_costmap_image", 1000);
}

Convert_To_Image::costmap_callback(const OccupancyGrid& grid)
{
  image_pub.publish(GridMap2D(grid));
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "convert_to_image");
//  ROS_INFO_STREAM("here");
  // ros::NodeHandle n;
  ros::spin();
  return 0;
}
