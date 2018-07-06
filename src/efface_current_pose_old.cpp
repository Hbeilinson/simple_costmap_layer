#include<efface_current_pose/efface_current_pose.h>
#include <pluginlib/class_list_macros.h>
#include <cmath>
#include <math.h>

PLUGINLIB_EXPORT_CLASS(simple_layer_namespace::EffaceLayer, costmap_2d::Layer)

using costmap_2d::NO_INFORMATION;
using costmap_2d::LETHAL_OBSTACLE;



namespace simple_layer_namespace
{

EffaceLayer::EffaceLayer() {}

void EffaceLayer::onInitialize()
{
  ros::NodeHandle nh("~");
  current_ = true;
  default_value_ = NO_INFORMATION;
  matchSize();

  dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);
  dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(&EffaceLayer::reconfigureCB, this, _1, _2);
  dsrv_->setCallback(cb);


}

void EffaceLayer::matchSize()
{
  Costmap2D* master = layered_costmap_->getCostmap();
  resizeMap(master->getSizeInCellsX(), master->getSizeInCellsY(), master->getResolution(),
            master->getOriginX(), master->getOriginY());
}


void EffaceLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level)
{
  enabled_ = config.enabled;
}

void EffaceLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x,
                                           double* min_y, double* max_x, double* max_y)
{
  if (!enabled_)
    return;

  costmap_2d::Costmap2D* layered_costmap = layered_costmap_->getCostmap();
  unsigned char* master_array = layered_costmap->getCharMap();
  //ROS_INFO_STREAM(master_array);

  double mark_x = robot_x, mark_y = robot_y;
  // int minimum_x = 0;
  // int minimmum_y = 0;
  // double maximum_x = 0;
  // double maximum_y = 0;

  //need to go through all possible coordinates, check if they're legit, and then update the cost if so
  // for (double i = 0; i <= 1000; i++) {
  //   for (double j = 0; j <= 1000; j++) {
  //     unsigned int mx;
  //     unsigned int my;
  //     if (worldToMap(i, j, mx, my)) {
  //       // if ((layered_costmap->getCost(mx, my) + 10) >= LETHAL_OBSTACLE) {
  //       //   continue;
  //       // }  else {
  //         // maximum_x = i;
  //         // maximum_y = j;
  //         setCost(mx, my, (9));
  //       // }
  //       // if (layered_costmap->getCost(mx, my) == 0) {
  //       //   setCost(mx, my, 100);
  //       //}
  //     }
  //   }
  // }
  unsigned int mx;
  unsigned int my;
  if(worldToMap(mark_x, mark_y, mx, my)){
    //int cost = getCost(mx, my);
    //ROS_INFO_STREAM(cost);
    setCost(mx, my, 0);
    for (int i = 2; i < 15; i++) {
      for (int t = 0; t < 360; t++) {
        double rad = t * 0.0174533;
        int x = mx + i * cos(rad);
        int y = my + i * sin (rad);
        if (t > 175 & t < 185) {
          setCost(x, y, 0);
        } else {
          setCost(x, y, pow(i, 2));
        }
      }
    }
    // for (int i = 0; i < 50; i++) {
    //   for (int j = 0; j < 50; j++) {
    //     //square root of (i-mx)^2 + (j -my)^2
    //     double distance = pow(pow (i-mx, 2) + pow (j - my, 2), 0.5); //figure out how to do gaussian correctly
    //     unsigned int gaussian = pow((2*distance),3);
    //     setCost((mx+i), (my+j), gaussian);
    //     if (((mx - i) > 0) & ((my - j) > 0)) {
    //       setCost((mx-i), (my-j), gaussian);
    //     }
    //   }
    // }
  }

  *min_x = std::min(*min_x, 0.0);
  *min_y = std::min(*min_y, 0.0);
  *max_x = std::max(*max_x, 200.0);
  *max_y = std::max(*max_y, 200.0);

}

void EffaceLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i,
                                          int max_j)
{
  if (!enabled_)
    return;

  for (int j = min_j; j < max_j; j++)
  {
    for (int i = min_i; i < max_i; i++)
    {
      int index = getIndex(i, j);
      if (costmap_[index] == NO_INFORMATION) {
        continue;
      }
      master_grid.setCost(i, j, costmap_[index]);
    }
  }
}
}
