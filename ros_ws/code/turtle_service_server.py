#!/usr/bin/env python3
# use the default python compiler

# import ROS python library
import rospy
#import the Twist message type
from geometry_msgs.msg import Twist

#thread library
import _thread as thread
#import the standard Service 
from  std_srvs.srv  import  Trigger, TriggerResponse

# initialize a node named 'turtle_reverse_direction'
rospy.init_node ('turtle_reverse_direction')

# the service callback function
def dir_toggle_Callback(req): 
    # toggle the direction between +1 and -1
    global  direction
    direction  =  direction*-1;
    
    #prepare and return a proper response.
    if( direction==-1):
        return  TriggerResponse(1, "Clockwise rotation") # Feedback data
    elif( direction==1):
        return  TriggerResponse(1, "counterclockwise rotation") # Feedback data
    else:
        return  TriggerResponse(0, "unexcepted error") # Feedback data

# thread main function
def service_thread():
    # set the service name and the associated callback function
    service =  rospy.Service('/direction_toggle', Trigger, dir_toggle_Callback)
    # wait for a service call
    rospy.spin() 
    
# start a thread to handle the service
thread.start_new_thread(service_thread,())

# control the direction of rotation (-1 for clockwise and +1 for counter clockwise)
direction=1; 

# creates a publisher for the /turtle1/cmd_vel topic
pub=rospy.Publisher('/turtle1/cmd_vel',Twist,queue_size=10)

# adjust the publishing rate to be 1 Hz
rate=rospy.Rate(1)

# loop forever or until interrupted by CTRL+C
while not rospy.is_shutdown():
    # Create a message and set the values of the x component of the linear velocity
    # and the z component of the angular velocity. Other fields will remain zero.
    twist_msg = Twist()
    twist_msg.linear.x=1.0*direction
    twist_msg.angular.z=0.8*direction
    
    # Use the publisher handler (pub) to publish the message
    pub.publish(twist_msg)
    
    #wait until the rate is satisfied (1Hz)
    rate.sleep()
