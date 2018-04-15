#include<stdio.h>
#include <iostream>
#include<math.h>
//#include <kdl_parser/kdl_parser.hpp>


using namespace std;
int main()
{
 float alfa=3.14;
 float gamma=3.14;
 float roll,pitch,yaw;

 float r[3][3];
 r[0][0]=cos(gamma);
 r[0][1]=-sin(alfa)*cos(alfa);
 r[0][2]=sin(gamma)*sin(alfa);
 r[1][0]=sin(gamma);
 r[1][1]=cos(gamma)*cos(alfa);
 r[1][2]=-cos(gamma)*sin(alfa); 
 r[2][0]=0;
 r[2][1]=sin(alfa);
 r[2][2]=cos(alfa);

 roll=atan2(r[2][1],r[2][2]);
 pitch=atan2(-r[2][0],sqrt(r[2][1]*r[2][1]+r[2][2]*r[2][2]));
 yaw=atan2(r[1][0],r[0][0]);	
 cout<<"RPY"<<"\n"<<"roll: "<<roll<<"   "<<"pitch: "<<pitch<<" yaw:  "<<yaw<<"\n";
 return 0;
}



/*
//#include <urdf/model.h>
//#include "ros/ros.h"

int main(int argc, char** argv){
 /* ros::init(argc, argv, "my_parser");
  if (argc != 2){
    ROS_ERROR("Need a urdf file as argument");
    return -1;
  }
  std::string urdf_file = argv[1];

  urdf::Model model;
  if (!model.initFile(urdf_file)){
    ROS_ERROR("Failed to parse urdf file");
    return -1;
  }
  ROS_INFO("Successfully parsed urdf file");/
  return 0;
}
*/
