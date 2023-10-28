#!/usr/bin/env python3
# use the default python compiler

# import ROS python library
import rospy

#import the Twist message type
from geometry_msgs.msg import Twist

    
# initialize a node named 'twist_publisher'
rospy.init_node("twist_publisher")

# creates a publisher for the /turtle1/cmd_vel topic
pub=rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)

# adjust the publishing rate to be 1 Hz
rate=rospy.Rate(1)

# loop forever or until interrupted by CTRL+C
while not rospy.is_shutdown():
    # Create a message and set the values of the x component of the linear velocity
    # and the z component of the angular velocity. Other fields will remain zero.
    twist_msg = Twist()
    twist_msg.linear.x=1.0
    twist_msg.angular.z=0.8
    
    # Use the publisher handler (pub) to publish the message
    pub.publish(twist_msg)
    
    #wait until the rate is satisfied (1Hz)
    rate.sleep()
