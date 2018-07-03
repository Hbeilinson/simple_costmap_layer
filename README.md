## ROS Costmap_2d Tutorial Example

### Introduction
The simple_layer's package contains a demo of the ROS [costmap_2d] package.(http://wiki.ros.org/costmap_2d). The demo package contains the [costmap_2d tutorials](http://wiki.ros.org/costmap_2d/Tutorials) integrated into the turtlebot_navigation package. When launched the package runs both stage and rviz with the demo layers (simple_layer and grid_layer) enabled.

### Create package
```
catkin_create_pkg simple_layers roscpp costmap_2d dynamic_reconfigure
```

### System Setup
Layers are defined in src folder while their include files are put in their own folder in the include folder.

Plugins must be defined in yaml file before being loaded into a move_base node

__Locations Where Layers Must Be Defined:__  
simple_layers/include/layer_name/layer_name.h  
simple_layers/params/local_costmap_params.yaml  
simple_layers/src/"layer_name.cpp"  
simple_layers/costmap_plugins.xml
simple_layers/CMakeLists.txt

### Disabling Current Layers
The costmap_2d plugin's are currently declared in the local costmap (params/local_costmap_params.yaml) by commenting out the layers not wanted.

```yaml
#simple_layers/params/local_costmap_params.yaml
#simple_layer and grid_layer's disabled in local costmap
local_costmap:
   global_frame: odom
   robot_base_frame: /base_footprint
   update_frequency: 5.0
   publish_frequency: 2.0
   static_map: false
   rolling_window: true
   width: 4.0
   height: 4.0
   resolution: 0.05
   transform_tolerance: 0.5
   plugins:
    - {name: obstacle_layer,      type: "costmap_2d::VoxelLayer"}
    - {name: inflation_layer,     type: "costmap_2d::InflationLayer"}
#    - {name: simple_layer,        type: "simple_layer_namespace::SimpleLayer"}
#    - {name: grid_layer,         type: "simple_layer_namespace::GridLayer"}
```

### Adding Layers
To add a layer

__Locations Where Layers Must Be Defined:__  
simple_layers/include/layer_name/"layer_name.h"  
simple_layers/params/local_costmap_params.yaml  
simple_layers/src/"layer_name.cpp"  
simple_layers/costmap_plugins.xml
simple_layers/CMakeLists.txt
