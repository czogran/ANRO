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



void poly(float x ,float y,float z,float roll, float yaw, float pitch,float time)
{
   
 float v1_a,v2_a,vg_a;
 float v1_b,v2_b,vg_b;
 
  geometry_msgs::PoseStamped position_to_rviz;
  geometry_msgs::Quaternion quat;
  
 nav_msgs::Path path;
 path.header.frame_id="base_link";
   
 ros::NodeHandle n;
 //ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("pose1", 400);
  ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 ros::Rate loop_rate(1000);

	v1_b=6*(x-prev_x)/time/time;
	v2_b=6*(y-prev_y)/time/time;	
	vg_b=6*(z-prev_z)/time/time;
	v1_a=-v1_b/time;
	v2_a=-v2_b/time;	
	vg_a=-vg_b/time;
float vroll_b=6*(-prev_roll+roll)/time/time;
float vyaw_b=6*(-prev_yaw+yaw)/time/time;
float vpitch_b=6*(-prev_pitch+pitch)/time/time;
float vroll_a=-vroll_b/time;
float vyaw_a=-vyaw_b/time;
float vpitch_a=-vpitch_b/time;
float vr,vy,vp;
Rotation r3;

for (float t=0; t<=time;t+=0.01)
{
	path.header.stamp=ros::Time::now();
 	position_to_rviz.header.stamp=ros::Time::now();
 
	

	vr=vroll_a*t*t*t/3+vroll_b*t*t/2+prev_roll;
	vy=vyaw_a*t*t*t/3+vyaw_b*t*t/2+prev_yaw;
	vp=vpitch_a*t*t*t/3+vpitch_b*t*t/2+prev_pitch;	
	r3 = Rotation::RPY(vr,vy,vp);
	Frame F_result(r3);

	position_to_rviz.pose.position.x=v1_a*t*t*t/3+v1_b*t*t/2+prev_x;
	position_to_rviz.pose.position.y=v2_a*t*t*t/3+v2_b*t*t/2+prev_y;
	position_to_rviz.pose.position.z=vg_a*t*t*t/3+vg_b*t*t/2+prev_z;

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
	//ROS_INFO("time %f v:%f prev%f pose%f",t,vx_b,prev_x,position_to_rviz.pose.position.x);
	ros::spinOnce();

    	loop_rate.sleep();
}
prev_x=position_to_rviz.pose.position.x;
prev_y=position_to_rviz.pose.position.y;
prev_z=position_to_rviz.pose.position.z;
prev_roll=roll;
prev_yaw=yaw;
prev_pitch=pitch;

}











void spline(float x ,float y,float z,float roll, float yaw, float pitch,float time)
{
   
 float a1,a2,a3;
 float v1,v2,v3;
 
  geometry_msgs::PoseStamped position_to_rviz;
  geometry_msgs::Quaternion quat;
  
 nav_msgs::Path path;
 path.header.frame_id="base_link";
   
 ros::NodeHandle n;
 //ros::Publisher pose_pub = n.advertise<geometry_msgs::PoseStamped>("pose1", 400);
  ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 ros::Rate loop_rate(1000);

	a1=(x-prev_x)/2*9/time/time;;
	a2=(y-prev_y)/2*9/time/time;;	
	a3=(z-prev_z)/2*9/time/time;;
	v1=a1*1/3*time;
	v2=a2/1/3*time;	
	v3=a3*1/3*time;
float roll_a=(-prev_roll+roll)/2*9/time/time;
float yaw_a=(-prev_yaw+yaw)/2*9/time/time;
float pitch_a=(-prev_pitch+pitch)/2*9/time/time;
float roll_v=roll_a*1/3*time;
float yaw_v=yaw_a*1/3*time;
float pitch_v=pitch_a*1/3*time;
float vr,vy,vp;
Rotation r3;
float help;
Frame result();
for (float t=0; t<=time;t+=0.01)
{
	path.header.stamp=ros::Time::now();
 	position_to_rviz.header.stamp=ros::Time::now();
 
	


	if(t<time/3)
	{
	position_to_rviz.pose.position.x=a1*t*t/2+prev_x;
	position_to_rviz.pose.position.y=a1*t*t/2+prev_y;
	position_to_rviz.pose.position.z=a3*t*t/2+prev_z;
	
	vr=roll_a*t*t/2+prev_roll;
	vy=yaw_a*t*t/2+prev_yaw;
	vp=pitch_a*t*t/2+prev_pitch;	
	r3 = Rotation::RPY(vr,vy,vp);
	Frame F_result(r3);
	
double x, y, z, w;
	F_result.M.GetQuaternion(x, y, z, w);

	position_to_rviz.pose.orientation.x=x;
	position_to_rviz.pose.orientation.y=y;
	position_to_rviz.pose.orientation.z=z;
	position_to_rviz.pose.orientation.w=w; 

	help=time/3;
	ROS_INFO("cccc t%f time%f",t,help );
	}
	if(t<time/3*2&&t>=time/3)
	{
	position_to_rviz.pose.position.x+=v1*0.01;
	position_to_rviz.pose.position.y+=v2*0.01;
	position_to_rviz.pose.position.z+=v3*0.01;

	vr+=roll_v*0.01;
	vy+=yaw_v+0.01;
	vp+=pitch_v*0.01;	
	r3 = Rotation::RPY(vr,vy,vp);
	Frame F_result(r3);

double x, y, z, w;
	F_result.M.GetQuaternion(x, y, z, w);

	position_to_rviz.pose.orientation.x=x;
	position_to_rviz.pose.orientation.y=y;
	position_to_rviz.pose.orientation.z=z;
	position_to_rviz.pose.orientation.w=w; 

	help=time/3*2;
	ROS_INFO("bbb t%f time%f",t,help );
	}
	if(t>=(time/3*2))
	{
	position_to_rviz.pose.position.x+=v1*0.01-a1*0.0001/2;
	position_to_rviz.pose.position.y+=v2*0.01-a2*0.0001/2;
	position_to_rviz.pose.position.z+=v3*0.01-a3*0.0001/2;
	
	
	vr+=roll_v*0.01-roll_a*0.0001/2;
	vy+=yaw_v+0.01-yaw_a*0.0001/2;
	vp+=pitch_v*0.01-pitch_a*0.0001/2;
	
	r3 = Rotation::RPY(vr,vy,vp);
	Frame F_result(r3);
	
double x, y, z, w;
	F_result.M.GetQuaternion(x, y, z, w);

	position_to_rviz.pose.orientation.x=x;
	position_to_rviz.pose.orientation.y=y;
	position_to_rviz.pose.orientation.z=z;
	position_to_rviz.pose.orientation.w=w; 

	help=time/3*2;
	ROS_INFO("aaa t%f time%f",t,help );
	}
	
	path.poses.push_back(position_to_rviz);
	//path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
	// path_msg.header.stamp=ros::Time::now();
    	//chatter_pub.publish(msg);
    	path_pub.publish(path);	
	//ROS_INFO("%f    %f  v1 %f position v1 %f\n ",t, time, v1,msg.position[0]);
    	ros::spinOnce();

    	loop_rate.sleep();
    
	}
prev_x=position_to_rviz.pose.position.x;
prev_y=position_to_rviz.pose.position.y;
prev_z=position_to_rviz.pose.position.z;
prev_roll=roll;
prev_yaw=yaw;
prev_pitch=pitch;

}



geometry_msgs::PoseStamped pose_point(float x, float y, float z)
{
  
  geometry_msgs::Pose pose;
  geometry_msgs::PoseStamped position_to_rviz;
 	 
 	double roll=0;//msg.position[0]+msg.position[1];
	double pitch=0;//+msg.position[1];;
	double yaw=0;//msg.position[2];

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
 


 position_to_rviz.header.frame_id="base_link";
 position_to_rviz.header.stamp = ros::Time::now(); 

 position_to_rviz.pose.position.x=x;
 position_to_rviz.pose.position.y=y;
 position_to_rviz.pose.position.z=z;


 position_to_rviz.pose.orientation.x=cy * sr * cp - sy * cr * sp;
 position_to_rviz.pose.orientation.y=cy * cr * sp + sy * sr * cp;
 position_to_rviz.pose.orientation.z=sy * cr * cp - cy * sr * sp; 
 position_to_rviz.pose.orientation.w=cy * cr * cp + sy * sr * sp;//(l1+l2);

return position_to_rviz;
}



