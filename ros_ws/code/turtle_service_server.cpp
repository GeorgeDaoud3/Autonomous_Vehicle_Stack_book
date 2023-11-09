// Include the necessary ROS header file for C++ programming
#include <ros/ros.h>
// Include the header file for the Twist message type
#include <geometry_msgs/Twist.h>

//include thread header file
#include <pthread.h>
//include the header file of the standard Service 
#include <std_srvs/Trigger.h>

int direction =1; // control the direction of rotation (-1 for clockwise and +1 for counter clockwise)
ros::MultiThreadedSpinner spinner(1); // only one thread would call the spin function
	
// the service callback function
bool  toggle_dir_Callback(std_srvs::Trigger::Request   & req,
                    std_srvs::Trigger::Response  & res)
{
	// toggle the direction between +1 and -1
    direction  =  -direction; 

    // prepare a proper response
	if( direction ==-1){
		res.success  =  true;
		res.message  =  "Clockwise rotation";
	}
	else if( direction ==1){
		res.success  =  true;
		res.message  =  "counterclockwise rotation";
	}
	else{
		res.success  =  false;
		res.message  =  "unexcepted error";
	}
	
	// the callback function ends successfully
    return  true;
}

// thread main function
void * service_thread( void *ptr ){
	// retrive the nodehandle from the main
	ros::NodeHandle * nh_ptr= (ros::NodeHandle *) ptr;
    // set the service name and the associated callback function
	ros::ServiceServer  service  =  nh_ptr->advertiseService("/reverse_direction", toggle_dir_Callback);
    // wait for a service call
    spinner.spin();
	
	return NULL;
}

int main(int argc, char** argv){
	// initialize a node named 'turtle_reverse_direction'
	ros::init(argc,argv,"reverse_direction");
	
	// create a nodeHandle object to interface with the ROS network.
	ros::NodeHandle nh;
	
	// create and start a thread to handle the service
	// a pointer to the node handle will be sent as an argument
	pthread_t thread;
	pthread_create( &thread, NULL, service_thread, (void*) &nh);
	
	// creates a publisher to send messages of type geometry_msgs::Twist 
	// on the "/turtle1/cmd_vel" topic with a queue size of 10
	ros::Publisher pub= nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);

	// publishes messages at rate of 1 times per second
	ros::Rate rate(1);
	
	// while the node is running
	while(ros::ok()) {
		
		// Create a Twist message with linear and angular velocities
		geometry_msgs::Twist twist_msg;
		twist_msg.linear.x=1.0*direction;
		twist_msg.angular.z=0.8*direction;
		
		// publish the linear and angular velocities
		pub.publish(twist_msg);
		
		//delay to achieve the desired publishing rate
		rate.sleep();
	}
	// Terminate the thread
	pthread_cancel(thread);
	
	return 0;
}

