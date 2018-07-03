import rospy, yaml, rospkg, tf, actionlib

from geometry_msgs.msg import Pose, PoseStamped, PoseWithCovarianceStamped
from gazebo_msgs.msg import ModelState
from gazebo_msgs.srv import GetModelState
from etu_simulation.srv import *

class path_publisher:
    def __init__(self):
        rospy.init_node('path_publisher')
        self.pose_sub = rospy.Subscriber()
        self.publisher = rospy.Publisher('/current_pose', Pose, queue_size = 10);

    # Stopped because this is redundant
