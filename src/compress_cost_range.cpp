#include <pluginlib/class_list_macros.h>
#include <compress_cost_range.h>

PLUGINLIB_EXPORT_CLASS(simple_layer_namespace::CompressLayer, costmap_2d::Layer)

using costmap_2d::NO_INFORMATION;
using costmap_2d::LETHAL_OBSTACLE;

namespace simple_layer_namespace
{
  CompressLayer::CompressLayer() {}

  void CompressLayer::onInitialize()
  {
    ros::NodeHandle nh("~");
    current_ = true;
    default_value_ = NO_INFORMATION;
    matchSize();

    dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);
    dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(&CompressLayer::reconfigureCB, this, _1, _2);
    dsrv_->setCallback(cb);
  }

  void CompressLayer::matchSize()
  {
    Costmap2D* master = layered_costmap_->getCostmap();
    resizeMap(master->getSizeInCellsX(), master->getSizeInCellsY(), master->getResolution(),
              master->getOriginX(), master->getOriginY());
  }

    void CompressLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level)
    {
      enabled_ = config.enabled;
    }

    void CompressLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x, double* max_y)
    {
      if (!enabled_)
        return;

      *min_x = std::min(*min_x, 0.0);
      *min_y = std::min(*min_y, 0.0);
      *max_x = std::max(*max_x, 200.0);
      *max_y = std::max(*max_y, 200.0);
    }

    void CompressLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j)
    {
      if (!enabled_)
        return;

      for (int j = min_j; j < max_j; j++)
      {
        for (int i = min_i; i < max_i; i++)
        {
          int index = getIndex(i, j);
          int cost = ((205*master_grid.getCost(i, j))/255) + 50;
          //int cost = std::max(costmap_[index], master_grid.getCost(i, j));
          master_grid.setCost(i, j, cost);
        }
      }
    }
}
