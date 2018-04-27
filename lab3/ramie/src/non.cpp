
#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>


/*
Quaterniond toQuaternion(double pitch, double roll, double yaw)
{
	Quaterniond q;
        // Abbreviations for the various angular functions
	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);

	q.w() = cy * cr * cp + sy * sr * sp;
	q.x() = cy * sr * cp - sy * cr * sp;
	q.y() = cy * cr * sp + sy * sr * cp;
	q.z() = sy * cr * cp - cy * sr * sp;
	return q;
}*/


ros::Publisher chatter_pub; 
//geometry_msgs::PoseStamped position_to_rviz;
double h_base,l1,l2,h_griper,h_box;

void jointCallback(const sensor_msgs::JointState & msg)
{
  geometry_msgs::Point point;
  geometry_msgs::Pose pose;
  geometry_msgs::PoseStamped position_to_rviz;
 	 
 	double roll=0;//msg.position[0]+msg.position[1];
	double pitch=0;//+msg.position[1];;
	double yaw=msg.position[0]+msg.position[1];;//msg.position[2];

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);

	//q.w() = cy * cr * cp + sy * sr * sp;
	//q.x() = cy * sr * cp - sy * cr * sp;
	//q.y() = cy * cr * sp + sy * sr * cp;
	//q.z() = sy * cr * cp - cy * sr * sp; 

 point.x= msg.position[0];
 point.y= msg.position[1];
 point.z= msg.position[2];
 
 position_to_rviz.header.frame_id="base_link";
 position_to_rviz.header.stamp = ros::Time::now(); 

 pose.position=point;

 //position_to_rviz.pose.position.x=msg.position[0];
 //position_to_rviz.pose.position.y=msg.position[1];
 position_to_rviz.pose.position.x=(l1*cos(point.x)+l2*cos(point.x+point.y));
 position_to_rviz.pose.position.y=(l1*sin(point.x)+l2*sin(point.x+point.y));
 position_to_rviz.pose.position.z=msg.position[2]+h_base-2*h_griper;



 position_to_rviz.pose.orientation.x=cy * sr * cp - sy * cr * sp;
 position_to_rviz.pose.orientation.y=cy * cr * sp + sy * sr * cp;
 position_to_rviz.pose.orientation.z=sy * cr * cp - cy * sr * sp; 
 position_to_rviz.pose.orientation.w=cy * cr * cp + sy * sr * sp;//(l1+l2);


 //position_to_rviz.header.frame_id="test";
 //position_to_rviz.header.stamp =ros::Time::now();
 //position_to_rviz.pose=pose;
 chatter_pub.publish(position_to_rviz);
}

using namespace std;
int main(int argc, char **argv)
{

 
	
 ros::init(argc, argv, "NONKDL_DKIN");
     ros::NodeHandle n;
 n.param<double>("l1",l1,0.6);
 n.param<double>("l2",l2,0.6);
 n.param<double>("h_base",h_base,0.6);
 n.param<double>("h_griper",h_griper,0.2);
 n.param<double>("h_box",h_box,0.2);

 chatter_pub = n.advertise<geometry_msgs::PoseStamped>("to_rviz", 1000);
 ros::Subscriber sub = n.subscribe("joint_states", 1000, jointCallback);


 //n.param<float>("l1",l1,0.6);
 //n.param<float>("l2",l2,0.6);
 //n.param<float>("h_base",h_base,0.6);
 //n.param<float>("h_gripper",h_gripper,0.2);

 ros::spin();
 return 0;
}






