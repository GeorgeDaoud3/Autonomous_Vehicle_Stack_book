// Include the necessary ROS header file for C++ programming
#include <ros/ros.h>

// Include the header file for the Pose message type
#include <turtlesim/Pose.h>

void pose_callback(const turtlesim::Pose::ConstPtr & msg){
    // print the x and y coordinates, theta angle and linear and angular velocities
    std::cout << "x = " << msg->x << ", y = " << msg->y 
	          << "theta = " << msg->theta << std::endl;
    std::cout << "linear velocity = " << msg->linear_velocity 
	          << ", angular velocity = " << msg->angular_velocity << std::endl;
}

int main(int argc, char** argv){
	//initialize a node named 'pose_subscriber'
	ros::init(argc,argv,"pose_subscriber");
	
	//create a nodeHandle object to interface with the ROS network.
	ros::NodeHandle nh;

	// creates a subscriber that listens for Pose messages from the topic 
	// '/turtle1/pose' with a queue size of 10 
	// when a Pose message is recieved, 'pose_callback' function is called
	ros::Subscriber sub= nh.subscribe("/turtle1/pose",10,pose_callback);

	// keep the node executing infinitely
	ros::spin();
	
	return 0;
}

