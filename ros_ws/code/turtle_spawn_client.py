#!/usr/bin/env python3
# use the default python compiler

# import ROS python library
import rospy

#import the Spawn Service 
from  turtlesim.srv  import  Spawn

# initialize a node named 'spawn_client'
rospy.init_node ('spawn_client')

# wait until the the /spawn service become available 
rospy.wait_for_service('/spawn') 

try :
    # get the service handler
    new_turtle =  rospy.ServiceProxy('/spawn', Spawn) 
    
    # Call the spawn service to create a new turtle at (7.5,7.5) with a 
    # direction (pi/2) under the name "turtle2". The mode will be   
    # blocked waiting for a response from the server (return value)
    response = new_turtle(7.5, 7.5, 1.57, "turtle2") 
    
    #print the returned value
    print("The service responded by {}".format(response.name));
    
except  rospy.ServiceException as e :
    # report a failure
    print  ("failed to call service : %s" % e)
    
    
    