# simple_costmap_layer

This directory contains original costmap layers for the ROS (Robot Operating System) navigation stack. 

It is an add-on to the one created by following the ROS wiki's costmap tutorials:
http://wiki.ros.org/costmap_2d;
http://wiki.ros.org/costmap_2d/Tutorials;

It was also pulled from a setup created by Benjamin Narin, available at:
https://bitbucket.org/benjaminnarin/costmap_introduction/src/e499397e4184a9e54d7143c2c059361dbaf91d46/simple_layers/?at=master

In addition to the simple costmap layer and grid costmap layer laid out by the tutorials and Benjamin's code, I added a wagon rut costmap layer and a cost compression layer. The code for both of these can be found in the src folder.

The cost compression layer compresses the range of costs in the costmap from the range 0 to 100 to the range 20 to 100. This allows the wagon rut layer to work, since this layer will make the cost of any location where the robot has previously driven 0. When both layers are at work (in addition to the standard layers) the robot will prefer to retrace paths it has previously driven in the same session.

In order to run my code, clone the entire repository into a catkin workspace. Build it and launch it using the turtlebot_costmap_nav.launch launch file. The package name is simple_layers and it depends on having stage, rviz, and the turtlebot packages installed.

This directory also contains code and data for creating histograms of costs in various costmaps, as well as the histograms themselves, saved in the data_and_histograms folder.
