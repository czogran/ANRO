#pragma once
#include "ros/ros.h"
#include "ramie/service.h"


#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Path.h"
#include <geometry_msgs/PoseStamped.h>
#include <interpolation.hpp>
//#include <cmath>
#include <math.h>

nav_msgs::Path path(float x, float y, float z);
float prev_j1,prev_j2,prev_grip;

void poly2(float j1 ,float j2,float grip,float time)
{
 //float speed;
 float v1_a,v2_a,vg_a;
 float v1_b,v2_b,vg_b;
 
 ros::NodeHandle n;

 ros::Publisher chatter_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
 ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 
 ros::Rate loop_rate(1000);

 nav_msgs::Path path_msg;
 path_msg.header.stamp=ros::Time::now();
 path_msg.header.frame_id="base_link";
 sensor_msgs::JointState msg;
 
 msg.name.resize(3);
 msg.position.resize(3);
 msg.name[0]="base_to_joint1";
 msg.name[1]="box1_to_joint2";
 msg.name[2]="box2_to_gripper_prismatic";
 
 msg.position[0]=prev_j1;
 msg.position[1]=prev_j2;
 msg.position[2]=prev_grip;
 
 	v1_b=6*(j1-msg.position[0])/time/time;
	v2_b=6*(j2-msg.position[1])/time/time;	
	vg_b=6*(grip-msg.position[2])/time/time;
	v1_a=-v1_b/time;
	v2_a=-v2_b/time;	
	vg_a=-vg_b/time;

	for(float t=0; t<=time;t +=0.01)
	{
	//ROS_INFO("%f   pose v1 %f\n ", time, msg.position[0]);
	msg.header.stamp=ros::Time::now();

	//path_msg.header.stamp=ros::Time::now();
	msg.position[0]=v1_a*t*t*t/3+v1_b*t*t/2+prev_j1;
	msg.position[1]=v2_a*t*t*t/3+v2_b*t*t/2+prev_j2;
	msg.position[2]=vg_a*t*t*t/3+vg_b*t*t/2+prev_grip;
	
	path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
    	//path_msg.header.stamp=ros::Time::now();
	//path_msg.poses[].stamp=ros::Time::now();
	chatter_pub.publish(msg);
    	path_pub.publish(path_msg);	
	
	ROS_INFO("%f     %f position v1 %f\n ",t, time,msg.position[0]);
    	ros::spinOnce();
	loop_rate.sleep();
	}
    	prev_j1=msg.position[0];
	prev_j2=msg.position[1];
	prev_grip=msg.position[2];
	
}


void line (float j1 ,float j2,float grip,float time)
{
 float v1,v2,vg;
 
 ros::NodeHandle n;

 ros::Publisher chatter_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
 ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 
 ros::Rate loop_rate(1000);

 nav_msgs::Path path_msg;
 path_msg.header.stamp=ros::Time::now();
 path_msg.header.frame_id="base_link";
 sensor_msgs::JointState msg;
 
 msg.name.resize(3);
 msg.position.resize(3);
 msg.name[0]="base_to_joint1";
 msg.name[1]="box1_to_joint2";
 msg.name[2]="box2_to_gripper_prismatic";
 
 msg.position[0]=prev_j1;
 msg.position[1]=prev_j2;
 msg.position[2]=prev_grip;


	v1=(j1-msg.position[0])/time;
	v2=(j2-msg.position[1])/time;
	vg=(grip-msg.position[2])/time;
	//loop_rate(time);
	for(float t=0; t<=time;t +=0.01)
	{

	msg.header.stamp=ros::Time::now();
	msg.position[0]=v1*t+prev_j1;
	msg.position[1]=v2*t+prev_j2;
	msg.position[2]=vg*t+prev_grip;
	path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
	// path_msg.header.stamp=ros::Time::now();
    	chatter_pub.publish(msg);
    	path_pub.publish(path_msg);	
	ROS_INFO("%f    %f   v1 %f position v1 %f\n ",t, time, v1,msg.position[0]);
    	ros::spinOnce();

    	loop_rate.sleep();
    
	}

	prev_j1=msg.position[0];
	prev_j2=msg.position[1];
	prev_grip=msg.position[2];


}



void spline (float j1 ,float j2,float grip,float time)
{
ROS_INFO("spline");
 float v1,v2,vg,a1,a2,ag;
 
 ros::NodeHandle n;

 ros::Publisher chatter_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
 ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 
 ros::Rate loop_rate(100);

 nav_msgs::Path path_msg;
 path_msg.header.stamp=ros::Time::now();
 path_msg.header.frame_id="base_link";
 sensor_msgs::JointState msg;
 
 msg.name.resize(3);
 msg.position.resize(3);
 msg.name[0]="base_to_joint1";
 msg.name[1]="box1_to_joint2";
 msg.name[2]="box2_to_gripper_prismatic";
 
 msg.position[0]=prev_j1;
 msg.position[1]=prev_j2;
 msg.position[2]=prev_grip;

	float help;
	
	a1=(j1-msg.position[0])/2*9/time/time;
	a2=(j2-msg.position[1])/time/time/2*9;
	ag=(grip-msg.position[2])/time/time/2*9;
	//loop_rate(time);
	v1=a1*1/3*time;
	v2=a2*1/3*time;
	vg=ag*time/3;
help=(j1-msg.position[0]);
	ROS_INFO("dane a1%f dx %f",a1,help );

	for(float t=0; t<=time;t +=0.01)
	{

	msg.header.stamp=ros::Time::now();
	if(t<time/3)
	{
	msg.position[0]=a1*t*t/2+prev_j1;
	msg.position[1]=a2*t*t/2+prev_j2;
	msg.position[2]=ag*t*t/2+prev_grip;
help=time/3;
ROS_INFO("cccc t%f time%f",t,help );
	}
	if(t<time/3*2&&t>=time/3)
	{
	msg.position[0]+=v1*0.01;
	msg.position[1]+=v2*0.01;
	msg.position[2]+=vg*0.01;
help=time/3*2;
ROS_INFO("bbb t%f time%f",t,help );
	}
	if(t>=(time/3*2))
	{
	msg.position[0]+=v1*0.01-a1*0.0001/2;
	msg.position[1]+=v2*0.01-a2*0.0001/2;
	msg.position[2]+=vg*0.01-ag*0.0001/2;
	v1-=a1*0.01;
	help=time/3*2;
	ROS_INFO("aaa t%f time%f",t,help );
	}
	path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
	// path_msg.header.stamp=ros::Time::now();
    	chatter_pub.publish(msg);
    	path_pub.publish(path_msg);	
	ROS_INFO("%f    %f  v1 %f position v1 %f\n ",t, time, v1,msg.position[0]);
    	ros::spinOnce();

    	loop_rate.sleep();
    
	}

	prev_j1=msg.position[0];
	prev_j2=msg.position[1];
	prev_grip=msg.position[2];


}




 nav_msgs::Path msg;
nav_msgs::Path path(float x, float y, float z)
{
 //nav_msgs::Path msg;
 msg.header.stamp=ros::Time::now();
 msg.header.frame_id="base_link";



 msg.poses.resize(1);

  geometry_msgs::Point point;
  geometry_msgs::Pose pose;
  geometry_msgs::PoseStamped position_to_rviz;
 	 
 	double roll=3.14;//msg.position[0]+msg.position[1];
	double pitch=0;//+msg.position[1];;
	double yaw=x+y;//msg.position[2];

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
 

 point.x= x;
 point.y= y;
 point.z= z;
 
 position_to_rviz.header.frame_id="base_link";
 position_to_rviz.header.stamp = ros::Time::now(); 

 pose.position=point;

//double ogr1=ogr2=0.5;
//if(point.x<0.5&&point.x>-0.5&&point.y<0.5&&point.y>-0.5){


 //position_to_rviz.pose.position.x=msg.position[0];
 //position_to_rviz.pose.position.y=msg.position[1];
 position_to_rviz.pose.position.x=(0.6*cos(point.x)+0.6*cos(point.x+point.y));
 position_to_rviz.pose.position.y=(0.6*sin(point.x)+0.6*sin(point.x+point.y));
 position_to_rviz.pose.position.z=-z+0.6-2*0.2;
//position_to_rviz.pose.position.x=x;
 //position_to_rviz.pose.position.y=y;
 //position_to_rviz.pose.position.z=z;



 position_to_rviz.pose.orientation.x=cy * sr * cp - sy * cr * sp;
 position_to_rviz.pose.orientation.y=cy * cr * sp + sy * sr * cp;
 position_to_rviz.pose.orientation.z=sy * cr * cp - cy * sr * sp; 
 position_to_rviz.pose.orientation.w=cy * cr * cp + sy * sr * sp;//(l1+l2);


//ROS_INFO("Uwaga, przekroczono dopuszczalny zakres ruchu nonkdl!\n");
//msg.poses[0]=position_to_rviz;
msg.poses.push_back(position_to_rviz);
//}
return msg;
}





