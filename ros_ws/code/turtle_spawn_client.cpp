// Include the necessary ROS header file for C++ programming
#include <ros/ros.h>

// Include the header file for the Spawn Service
#include <turtlesim/Spawn.h>


int main(int argc, char** argv){
	// initialize a node named 'spawn_client'
	ros::init(argc,argv,"turtle_spawn_client");
	
	// create a nodeHandle object to interface with the ROS network.
	ros::NodeHandle nh;
	
	// wait until the the /spawn service become available 
	ros::service::waitForService("/spawn");
	
	// get the service handler
	ros::ServiceClient  new_turtle  =  nh.serviceClient < turtlesim::Spawn >("/spawn");

    // Initialize request data for the services to create a new turtle
    //  at (7.5,7.5) with a direction (pi/2) under the name "turtle2".
    turtlesim::Spawn  new_turtle_srv;
    new_turtle_srv.request.x  =  7.5;
    new_turtle_srv.request.y  =  7.5;
	new_turtle_srv.request.theta  =  1.57;
    new_turtle_srv.request.name  =  "turtle2";
	
	// Call the spawn service to  The mode will be blocked
    // waiting for a response from the server (return value)
    new_turtle.call(new_turtle_srv);

	// print the returned value
    std::cout << "Spwan turtle successfully [name:" << 
	          new_turtle_srv.response.name.c_str() << "]" << std::endl;

	return 0;
}

