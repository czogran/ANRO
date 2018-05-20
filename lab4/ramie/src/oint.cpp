#include "ros/ros.h"
#include "ramie/ointservice.h"


#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Path.h"
#include <geometry_msgs/PoseStamped.h>
#include <oint_interpolation.hpp>


ros::Publisher pose_pub;
//float prev_j1,prev_j2,prev_grip;
bool add(ramie::ointservice::Request &req,
        ramie::ointservice::Response &res)
{
res.status = "OK";
 if(req.type=="line")
	line(req.x,req.y,req.z,req.roll,req.yaw,req.pitch,req.time);
 else if(req.type=="poly")
	poly(req.x,req.y,req.z,req.roll,req.yaw,req.pitch,req.time); 
else if(req.type=="spline")
	spline(req.x,req.y,req.z,req.roll,req.yaw,req.pitch,req.time); 
else
res.status = "zla interpoacja";


  ROS_INFO("request: x=%f, y=%f", req.x, req.time);
 
  ROS_INFO("sending back response: [%s]", res.status);
  return true;
}



int main(int argc, char **argv)
{


  ros::init(argc, argv, "oint");
 ros::NodeHandle n;

// pose_pub = n.advertise<geometry_msgs::PoseStamped>("pose1", 400);
 ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
  ros::ServiceServer service = n.advertiseService("oint_control_srv", add);
 // ROS_INFO("Ready to add two ints.");
 //poly2(j1,j2,grip,time, chatter_pub, path_pub);
  ros::spin();

  return 0;
}
