#include "ros/ros.h"
#include "ramie/service.h"


#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Path.h"
#include <geometry_msgs/PoseStamped.h>
#include <interpolation.hpp>

#include <string>
#include <iostream>
#include <stdlib.h>




ros::Publisher chatter_pub;
ros::Publisher path_pub;

bool add(ramie::service::Request &req,
        ramie::service::Response &res)
{
 res.status.clear();
 res.status="status: ";
// poly2(req.j1, req.j2,req.grip,req.time, chatter_pub, path_pub);
if (req.time<=0 ||req.j2>1.5||req.j2<-1.5||req.grip<-0.1||req.grip>0.1||(req.type!="line"&&req.type!="poly"&&req.type!="spline"))
{
    if(req.time<=0)
 		res.status+="za maly czas";
	if(req.type!="poly"&&req.type!="line"&&req.type!="spline")
		res.status+=" nieznana interpolacja";
	if(req.j2>1.5||req.j2<-1.5||req.grip<-0.1||req.grip>0.1)
		res.status+=" zle parametry";
}
else
{
	  ROS_INFO("interpol");
	if(req.type=="poly")
 		poly2(req.j1, req.j2,req.grip,req.time);
 	if(req.type=="line")
		line(req.j1, req.j2,req.grip,req.time);
	res.status = "OK";
	if(req.type=="spline")
		spline(req.j1, req.j2,req.grip,req.time);
	res.status = "OK";

}
 //res.status = "aaa";
  ROS_INFO("request: x=%f, y=%f ", req.j1, req.time);
 
  ROS_INFO("sending back response: [%s]", res.status.c_str());
  return true;
}



int main(int argc, char **argv)
{


 ros::init(argc, argv, "jint");
 ros::NodeHandle n;
 ros::Publisher chatter_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);

 ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 	
  ros::ServiceServer service = n.advertiseService("jint_control_srv", add);
 // ROS_INFO("Ready to add two ints.");
 //poly2(j1,j2,grip,time, chatter_pub, path_pub);
  ros::spin();

  return 0;
}
