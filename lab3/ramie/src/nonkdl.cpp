#include<stdio.h>
#include <iostream>
#include<math.h>


#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"//msg
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Point.h"


 
float x,y,z;
 geometry_msgs::PoseStamped position_to_rviz;
ros::Publisher chatter_pub; 

void chatterCallback(const sensor_msgs::JointState msg)    //(const std_msgs::String::ConstPtr& msg)
{
  //ros::NodeHandle n;
 //ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("chatter", 1000);
 //ros::Rate loop_rate(10);
 //geometry_msgs::PoseStamped position_to_rviz;
 geometry_msgs::Point point;
 geometry_msgs::Pose pose;
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  ROS_INFO("I heard: [%f]", msg.position[0]);
  ROS_INFO("I heard: [%f]", msg.position[1]);
  ROS_INFO("I heard: [%f]", msg.position[2]);
  ROS_INFO("I heard: [%f]", msg.position[3]);
 point.x= msg.position[0];
 point.y= msg.position[1];
 point.z= msg.position[2];
 
/*
 point.orientation.x=0;
 point.orientation.y=0;
 point.orientation.z=0;
 point.orientation.w=0;*/
 
 pose.position=point;

 pose.orientation.x=0;
 pose.orientation.y=0;
 pose.orientation.z=0;
 pose.orientation.w=0;

 position_to_rviz.header.frame_id="test";
 position_to_rviz.header.stamp =ros::Time::now();
 position_to_rviz.pose=pose;
  chatter_pub.publish(position_to_rviz);
}


using namespace std;
int main(int argc, char **argv)
{
 float alfa=0;
 float gamma=0.6;
 float roll,pitch,yaw;

 ros::init(argc, argv, "NONKDL_DKIN");

    ros::NodeHandle n;
ROS_INFO("blad");
 //ros::Subscriber sub = n.subscribe("joint_states", 1000, chatterCallback);


 ros::Rate loop_rate(10); 
//ros::Subscriber sub = n.subscribe("joint_states", 1000, chatterCallback);
 //ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("publish", 1000);
	n.param<float>("d1",x,3);
    n.param<float>("d2",y,3);
	n.param<float>("d3",z,3); 


while (ros::ok()){ 
 chatter_pub = n.advertise<geometry_msgs::PoseStamped>("to_rviz", 1000);
 ros::Subscriber sub = n.subscribe("joint_states", 1000, chatterCallback);

 //geometry_msgs::PoseStamped pose;
// chatter_pub.publish(position_to_rviz);
   ros::spinOnce();

    loop_rate.sleep();
}
 //pose.pose=1.0;
 //pose.pose=0.2;
// pose.point.z=0.0;
 ros::spin();
 return 0;
}




