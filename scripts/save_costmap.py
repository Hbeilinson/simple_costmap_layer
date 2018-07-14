#!/usr/bin/env python

#Simple script to read the costmap to a file (old_costmap.txt in main package folder)
import roslib
roslib.load_manifest('simple_layers')
import rospy
from nav_msgs.msg import OccupancyGrid

#https://stackoverflow.com/questions/17126037/how-to-delete-only-the-content-of-file-in-python/17126137
def deleteContent(pfile):
    pfile.seek(0)
    pfile.truncate()

class save_costmap:
    def __init__(self):
        print("I have been summoned. I am here.")
        self.costmap_sub = rospy.Subscriber('/move_base/global_costmap/costmap', OccupancyGrid, self.costmap_callback)

    def costmap_callback(self, costmap):
        cost_str = str(costmap.data)
        if (cost_str[0] == "("):
            cost_str = cost_str[1:]
        if (cost_str[-1] == ")"):
            cost_str = cost_str[:-1]
        cost_str = cost_str.replace(",", "\n")
        file = open("../old_costmap.txt", "w")
        deleteContent(file)
        file.write(cost_str)
        file.close()

if __name__=='__main__':
    rospy.init_node('save_costmap')
    save_costmap = save_costmap()
    rospy.spin()
