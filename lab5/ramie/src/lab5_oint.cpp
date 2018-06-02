#include "ros/ros.h"
#include "ramie/inverse.h"


#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Path.h"

#include <geometry_msgs/PoseStamped.h>
#include <interpolation.hpp>
#include <oint_interpolation.hpp>

#include <string>
#include <iostream>
#include <stdlib.h>


 float param_a,param_b,param_c;
 float px,py,pz;
 float position_x=1;
 float position_y=1;
 float position_z=0.2;
 int steps;
 float alfa;
 float beta;
 float gama;
 float pi=3.141592;

 geometry_msgs::PoseStamped pose1;


 ros::Publisher path_pub;
 ros::Publisher geo_pub;
 nav_msgs::Path path_msg;

bool add(ramie::inverse::Request &req,
        ramie::inverse::Response &res)
{

	 path_msg.header.stamp=ros::Time::now();
 path_msg.header.frame_id="base_link";

	 ros::Rate loop_rate(10);
	param_a=req.a;
	param_b=req.b;
	param_c=req.c;

	
	
if(req.type=="elipse")
{
	param_a=req.a;
	param_b=req.b;
	param_c=req.c;

	steps=100;
	alfa=-pi/2;
	beta=-pi; 
		gama=-0.0;
	px=position_x;
	py=position_y;
	pz=position_z;
	position_x=param_a*cos(beta);//*cos(alfa);
			position_y=param_b*sin(beta);//*sin(alfa);
			position_z=0.2+param_c*sin(gama);
	poly_inverse(position_x,position_y,position_z,0,0,0,px,py,pz,100);
	for(int a=0;a<1;a++)
	{
		for (int i=0;i<steps;i++)
		 {
		 	
			position_x=param_a*cos(beta);//*cos(alfa);
			position_y=param_b*sin(beta);//*sin(alfa);
			position_z=0.2+param_c*sin(gama);
			//position_x=param_a*cos(gama);
			//position_y=param_b*sin(gama);
			//position_z=1;
		
			ROS_INFO("x:%f y:%f z:%f alfa:%f beta:%f gama:%f",position_x,position_y,position_z,alfa,beta,gama);
			alfa+=pi/steps;
			beta+=2*pi/steps;
			gama+=2*pi/steps;
			//poly2(position_x, position_y,position_z,1);
			pose1=pose_point(position_x,position_y,position_z);
			path_msg.poses.push_back(pose1);
			path_pub.publish(path_msg);
			geo_pub.publish(pose1);
		    	ros::spinOnce();	
			loop_rate.sleep();
		 }
	}
}
else if(req.type=="square")
{
	alfa=req.x;//-0.5;
	beta=req.y;//-0.5;
	gama=req.z;//0.1;
	poly_inverse(alfa,beta,gama,0,0,0,position_x,position_y,position_z,100);
		param_a=req.a*4;
		param_b=req.b*4;
		param_c=req.c*4;
	for(int a=0;a<1;a++)
	{
		for (int i=0;i<steps;i++)
		 {
		 	
			position_x=alfa;//*cos(alfa);
			position_y=beta;//*sin(alfa);
			position_z=0.2+gama;
		
			ROS_INFO("x:%f y:%f z:%f alfa:%f beta:%f gama:%f",position_x,position_y,position_z,alfa,beta,gama);
			if(i<steps/4)
			{	ROS_INFO("1");	
			alfa+=param_a/steps;
			gama+=-param_c/steps;
			}
			if(i>=steps/4 &&i<steps/2)
			{ROS_INFO("2");
			beta+=param_b/steps;
			gama+=param_c/steps;
			}
			if(i>=steps/2 &&i<steps*3/4)
			{ROS_INFO("3");
			alfa+=-param_a/steps;
			gama+=-param_c/steps;
			}
			if(i>=steps/4*3 &&i<steps)
			{ROS_INFO("4");
			beta+=-param_b/steps;
			gama+=+param_c/steps;
			}
			//poly2(position_x, position_y,position_z,1);
			pose1=pose_point(position_x,position_y,position_z);
			path_msg.poses.push_back(pose1);
			path_pub.publish(path_msg);
			geo_pub.publish(pose1);
		    	ros::spinOnce();	
			loop_rate.sleep();
		 }
	
		}
}
	//res.status="OK";
  return true;
}











int main(int argc, char **argv)
{


 ros::init(argc, argv, "oint");
 ros::NodeHandle n;



  path_pub = n.advertise<nav_msgs::Path>("path1", 400);
  geo_pub = n.advertise<geometry_msgs::PoseStamped>("pose", 400);
   ros::ServiceServer service = n.advertiseService("oint_srv", add);
 ros::Rate loop_rate(10);



 


	//param_a=0.5;
	//param_b=1.1;
	//param_c=0.1;
	steps=100;
	alfa=-pi/2;
	beta=-pi; 
	gama=-0.0;
for(int a=0;a<0;a++){
	for (int i=0;i<steps;i++)
	 {
	 	
		position_x=param_a*cos(beta);//*cos(alfa);
		position_y=param_b*sin(beta);//*sin(alfa);
		position_z=0.2+param_c*sin(gama);
		//position_x=param_a*cos(gama);
		//position_y=param_b*sin(gama);
		//position_z=1;
		
		ROS_INFO("x:%f y:%f z:%f alfa:%f beta:%f gama:%f",position_x,position_y,position_z,alfa,beta,gama);
		alfa+=pi/steps;
		beta+=2*pi/steps;
		gama+=2*pi/steps;
		//poly2(position_x, position_y,position_z,1);
		pose1=pose_point(position_x,position_y,position_z);
		path_msg.poses.push_back(pose1);
		path_pub.publish(path_msg);
		geo_pub.publish(pose1);
	    	ros::spinOnce();	
loop_rate.sleep();
	 }
}
alfa=-0.5;
beta=-0.5;
gama=0.1;

	param_a=3;
	param_b=3;
	param_c=0.4;
for(int a=0;a<0;a++){
	for (int i=0;i<steps;i++)
	 {
	 	
		position_x=alfa;//*cos(alfa);
		position_y=beta;//*sin(alfa);
		position_z=0.2+gama;
		//position_x=param_a*cos(gama);
		//position_y=param_b*sin(gama);
		//position_z=1;
		
		ROS_INFO("x:%f y:%f z:%f alfa:%f beta:%f gama:%f",position_x,position_y,position_z,alfa,beta,gama);
		if(i<steps/4)
		{	ROS_INFO("1");	
		alfa+=param_a/steps;
	//	beta+=2.0/steps;
		gama+=-param_c/steps;
		}
		if(i>=steps/4 &&i<steps/2)
		{ROS_INFO("2");
	//	alfa+=-2.0/steps;
		beta+=param_b/steps;
		gama+=param_c/steps;
		}
		if(i>=steps/2 &&i<steps*3/4)
		{ROS_INFO("3");
		alfa+=-param_a/steps;
	//	beta+=-2.0/steps;
		gama+=-param_c/steps;
		}
		if(i>=steps/4*3 &&i<steps)
		{ROS_INFO("4");
	//	alfa+=-2.0/steps;
		beta+=-param_b/steps;
		gama+=+param_c/steps;
		}
		//poly2(position_x, position_y,position_z,1);
		pose1=pose_point(position_x,position_y,position_z);
		path_msg.poses.push_back(pose1);
		path_pub.publish(path_msg);
		geo_pub.publish(pose1);
	    	ros::spinOnce();	
loop_rate.sleep();
	 }
	
}

 //ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 	
  //ros::ServiceServer service = n.advertiseService("jint_control_srv", add);
 // ROS_INFO("Ready to add two ints.");
 //poly2(j1,j2,grip,time, chatter_pub, path_pub);
  ros::spin();

  return 0;
}
