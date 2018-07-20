#!/usr/bin/env python

import cv2
import numpy as np
import roslib
roslib.load_manifest('simple_layers')
import rospy


class reverse_pgm:
    def __init__(self):
        #https://www.learnopencv.com/filling-holes-in-an-image-using-opencv-python-c/
        im_in = cv2.imread('/home/strider/catkin_ws/src/simple_costmap_layer/world_files/old_map.pgm')
        im_in = cv2.bitwise_not(im_in)
        cv2.imwrite('/home/strider/catkin_ws/src/simple_costmap_layer/world_files/old_map.pgm', im_in)




if __name__=='__main__':
    rospy.init_node('reverse_pgm')
    reverse_pgm = reverse_pgm()
    rospy.spin()

# def reverse_pgm(file_name):
#     string_lst = []
#     with open(file_name, "r") as filestream:
#         for line in filestream:
#             currentline = line.split(" ")
#             string_lst.append(currentline)
#
#     string_lst = string_lst[4:]
#     number_lst = []
#     for i in string_lst:
#         number_lst.append(i)
