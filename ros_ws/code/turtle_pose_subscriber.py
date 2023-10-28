#!/usr/bin/env python
#use the default python compiler

# import ROS python library
import rospy

#import the Pose message type
from turtlesim.msg import Pose

def pose_callback(msg):
    # print the x and y coordinates, theta angle and linear and angular velocities
    print("x = {}, y = {}, theta = {}".format(msg.x, msg.y, msg.theta))
    print("linear velocity = {}, angular velocity = {}".format(msg.linear_velocity, msg.angular_velocity))
    
# initialize a node named 'pose_subscriber'
rospy.init_node("pose_subscriber")

# creates a subscriber that listens for Pose messages from the topic '/turtle1/pose'
# when a Pose message is recieved, 'pose_callback' function is called
rospy.Subscriber('/turtle1/pose',Pose,pose_callback)

# keep the node executing infinitely
rospy.spin()  
