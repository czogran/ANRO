#pragma once
#include "ros/ros.h"



#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Path.h"
#include <geometry_msgs/PoseStamped.h>


#include <math.h>
#include <geometry_msgs/Quaternion.h>
#include <kdl/segment.hpp>
#include <kdl/frames.hpp>
#include <kdl/joint.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>

using namespace KDL;
float prev_x,prev_y,prev_z,prev_roll,prev_yaw,prev_pitch;
//ros::Publisher pose_pub;

void line(float x ,float y,float z,float roll, float yaw, float pitch,float time)
{
  geometry_msgs::Point point;
  geometry_msgs::Pose pose;
  geometry_msgs::PoseStamped position_to_rviz;
  geometry_msgs::Quaternion quat;
  
 nav_msgs::Path path;
 path.header.frame_id="base_link";
   
 ros::NodeHandle n;
 //ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("pose1", 400);
  ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 ros::Rate loop_rate(1000);

float vx=-(prev_x-x)/time;
float vy=-(prev_y-y)/time;
float vz=-(prev_z-z)/time;
float vroll=-(prev_roll-roll)/time;
float vyaw=-(prev_yaw-yaw)/time;
float vpitch=-(prev_pitch-pitch)/time;
Rotation r3;

for (float t=0; t<=time;t+=0.01)
{
	path.header.stamp=ros::Time::now();
 	position_to_rviz.header.stamp=ros::Time::now();
 
	
	r3 = Rotation::RPY(prev_roll+vroll*t,prev_yaw+vyaw*t,prev_pitch+vpitch*t);
//GetRPY(prev_roll+vroll*t,prev_yaw+vyaw*t,prev_pitch+vpitch*t);
	Frame F_result(r3);

	//position_to_rviz.header.frame_id="base_link";
	//position_to_rviz.header.stamp = ros::Time::now();

	position_to_rviz.pose.position.x=prev_x+vx*t;
	position_to_rviz.pose.position.y=prev_y+vy*t;
	position_to_rviz.pose.position.z=prev_z+vz*t;

	double x, y, z, w;
	F_result.M.GetQuaternion(x, y, z, w);

	position_to_rviz.pose.orientation.x=x;
	position_to_rviz.pose.orientation.y=y;
	position_to_rviz.pose.orientation.z=z;
	position_to_rviz.pose.orientation.w=w; 

//if(q(0)<0.5&&q(0)>-0.5&&q(1)<0.5&&q(1)>-0.5&&q(2)<0.099&&q(2)>-0.099){
 //pose_pub.publish(position_to_rviz);
 	path.poses.push_back(position_to_rviz);
 	path_pub.publish(path);
	ROS_INFO("time %f v:%f prev%f pose%f",t,vx,prev_x,position_to_rviz.pose.position.x);
	ros::spinOnce();

    	loop_rate.sleep();
}
prev_x=x;
prev_y=position_to_rviz.pose.position.y;
prev_z=position_to_rviz.pose.position.z;
prev_roll=roll;
prev_yaw=yaw;
prev_pitch=pitch;

}




