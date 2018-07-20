#include <pluginlib/class_list_macros.h>
#include <load_old_map.h>


PLUGINLIB_EXPORT_CLASS(simple_layer_namespace::LoadOldLayer, costmap_2d::Layer)

using costmap_2d::NO_INFORMATION;
using costmap_2d::LETHAL_OBSTACLE;

int string_to_int(string str)
{
  if (str == "100") {
    return 100;
  }
  else if (str.length() == 2) {
    return 10*(str[0]-'0') + (str[1] - '0');
  } else {
    return 1*(str[0] - 0);
  }
}


vector<int> vector_of_costs()
{
  vector<int> costs;
  ifstream file ("../old_costmap.txt");
  int number;
  string line;
  while (!file.eof())
  {
    getline(file, line);
    number = string_to_int(line);
    costs.push_back(number);
  }
  file.close();
  return costs;
}


namespace simple_layer_namespace
{
  LoadOldLayer::LoadOldLayer() {}
  void LoadOldLayer::onInitialize()
  {
    ros::NodeHandle nh("~");
    current_ = true;
    default_value_ = NO_INFORMATION;
    matchSize();

    dsrv_ = new dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>(nh);
    dynamic_reconfigure::Server<costmap_2d::GenericPluginConfig>::CallbackType cb = boost::bind(&LoadOldLayer::reconfigureCB, this, _1, _2);
    dsrv_->setCallback(cb);
  }

  void LoadOldLayer::matchSize() //Necessary function for all costmap layers
  {
    Costmap2D* master = layered_costmap_->getCostmap();
    resizeMap(master->getSizeInCellsX(), master->getSizeInCellsY(), master->getResolution(),
              master->getOriginX(), master->getOriginY());
  }

  void LoadOldLayer::reconfigureCB(costmap_2d::GenericPluginConfig &config, uint32_t level)
  {
    enabled_ = config.enabled;
  }

  void LoadOldLayer::updateBounds(double robot_x, double robot_y, double robot_yaw, double* min_x, double* min_y, double* max_x, double* max_y)
  //Updates bounds of area to be changed to be the entire map
  {
    if (!enabled_)
      return;

    *min_x = std::min(*min_x, 0.0);
    *min_y = std::min(*min_y, 0.0);
    *max_x = std::max(*max_x, 200.0);
    *max_y = std::max(*max_y, 200.0);
  }

  void LoadOldLayer::updateCosts(costmap_2d::Costmap2D& master_grid, int min_i, int min_j, int max_i, int max_j)
  {
    if (!enabled_)
      return;

    vector<int> old_costs = vector_of_costs();

    for (int j = min_j; j < max_j; j++) //Iterates through the entire costmap
    {
      for (int i = min_i; i < max_i; i++)
      {
        if (old_costs.size() > 0) {
          int index = getIndex(i, j);
          int cost = old_costs.front();
          old_costs.erase(old_costs.begin());
          if (cost >= 0 & cost <= 255) {
            master_grid.setCost(i, j, cost); //Try to actually save costmap2d and load that back in somehow? :O
          }
        } else {
          setCost(i, j, 0);
        }
        // int cost = ((205*master_grid.getCost(i, j))/255) + 50; //gets the previous cost of this location in the costmap, and calculates the compressed cost
        //int cost = std::max(costmap_[index], master_grid.getCost(i, j));
        // master_grid.setCost(i, j, 0); //Sets the new cost in the current location in the costmap to be the compressed cost
      }
    }
  }
}
