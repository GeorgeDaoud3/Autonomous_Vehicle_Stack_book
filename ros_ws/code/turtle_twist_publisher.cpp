// Include the necessary ROS header file for C++ programming
#include <ros/ros.h>

// Include the header file for the Twist message type
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv){
	//initialize a node named 'twist_publisher'
	ros::init(argc,argv,"twist_publisher");
	
	//create a nodeHandle object to interface with the ROS network.
	ros::NodeHandle nh;

	// creates a publisher to send messages of type geometry_msgs::Twist 
	// on the "/turtle1/cmd_vel" topic with a queue size of 10
	ros::Publisher pub= nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);

	// publishes messages at rate of 1 times per second
	ros::Rate rate(1);
	
	// while the node is running
	while(ros::ok()) {
		
		// Create a Twist message with linear and angular velocities
		geometry_msgs::Twist twist_msg;
		twist_msg.linear.x=1.0;
		twist_msg.angular.z=0.8;
		
		// publish tje linear and angular velocities
		pub.publish(twist_msg);
		
		//delay to achieve the desired publishing rate
		rate.sleep();
	}
	
	return 0;
}

