#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "nav_msgs/Path.h"
#include <geometry_msgs/PoseStamped.h>

#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>


char getch() {

        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");        
     std::system("clear");
        return (buf);
}


nav_msgs::Path path(float x, float y, float z)
{
nav_msgs::Path msg;
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



 position_to_rviz.pose.orientation.x=cy * sr * cp - sy * cr * sp;
 position_to_rviz.pose.orientation.y=cy * cr * sp + sy * sr * cp;
 position_to_rviz.pose.orientation.z=sy * cr * cp - cy * sr * sp; 
 position_to_rviz.pose.orientation.w=cy * cr * cp + sy * sr * sp;//(l1+l2);


ROS_INFO("Uwaga, przekroczono dopuszczalny zakres ruchu nonkdl!\n");

msg.poses[0]=position_to_rviz;
//}
return msg;
}



int main(int argc, char **argv)
{
 char pozycja;
 std::string kierunek;
 std::string joint1_left="q";
 std::string joint1_right="e";
 std::string joint2_left="a";
 std::string joint2_right="d";
 std::string griper_up="w";
 std::string griper_down="s";
 std::string time_up="u";
 std::string time_down="j";
float j1,j2,grip,time;
j1=j2=grip=0;
time=1;
float speed;
float v1,v2,vg;
float poly;
  
  ros::init(argc, argv, "jint");
  ros::NodeHandle n;

  //ros::param::get("~prosto",alfa);
  //ros::param::get("~wlewo", beta);
  //ros::param::get("~wprawo",beta1);
  //ros::param::get("~tyl",alfa1);
	//n.getParam("wlewo", beta); //nie wiem czemu nie działa
	//n.getParam("wprawo",beta1);
	//n.getParam("tyl",alfa1);
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

msg.header.frame_id="sensor_frame";
  int count = 0;
msg.position[0]=0.0;
    msg.position[1]=0.0;
    msg.position[2]=0.0;

  while (ros::ok())
  {
ROS_INFO("joint1 joint 2 griper time\n");
ROS_INFO("%f   %f   %f     %f \n",j1,j2,grip,time);
   

    pozycja=getch();
//msg.velocity[0]=0.1;
    kierunek=pozycja;
    if (kierunek ==joint1_right)
	{
		j1+=0.01;
		//msg.position[0]+=0.01;
	}
    else if(kierunek ==joint1_left){
	j1+=-0.01;
	//msg.position[0]+=-0.01;
	}
    else if(kierunek ==joint2_right){
	j2+=0.01;
	//msg.position[1]+=0.01;
	}
   else if(kierunek ==joint2_left){
	j2+=-0.01;
	//msg.position[1]+=-0.01;
	}
  else if(kierunek ==griper_up){
	grip+=-0.01;
	//msg.position[2]+=-0.01;
	}
 else if(kierunek ==griper_down){
	grip+=0.01;
	//msg.position[2]+=0.01;
	}
else if(kierunek ==time_down){
	time-=0.1;
	//msg.position[2]+=0.01;
	}
else if(kierunek ==time_up){
	time+=0.1;
	//msg.position[2]+=0.01;
	}
 else{
	v1=(j1-msg.position[0])/time/10;
	v2=(j2-msg.position[1])/time/10;
	vg=(grip-msg.position[2])/time/10;
	//loop_rate(time);
	/*for(float t=0; t<=time;t +=0.1)
	{
	msg.header.stamp=ros::Time::now();
	msg.position[0]+=v1;
	msg.position[1]+=v2;
	msg.position[2]+=vg;
	path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
    	chatter_pub.publish(msg);
    	path_pub.publish(path_msg);	
	ROS_INFO("%f    %f   v1 %f position v1 %f\n ",t, time, v1,msg.position[0]);
    	ros::spinOnce();

    	loop_rate.sleep();
    	++count;
	}*/
	v1=6*(j1-msg.position[0])/time/time;
	v2=6*(j2-msg.position[1])/time/time;	
	grip=-6*(grip-msg.position[2])/time/time;
	poly=-v1/time;
	j1=msg.position[0];
	j2=msg.position[1];
	grip=msg.position[2];
	for(float t=0; t<=time;t +=0.01){
	msg.header.stamp=ros::Time::now();
	msg.position[0]=poly*t*t*t/3+v1*t*t/2+j1;
	msg.position[1]=v2*t*t-v2/time*t+j2;
	msg.position[2]=vg*t*t-vg/time*t+grip;
	path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
    	chatter_pub.publish(msg);
    	path_pub.publish(path_msg);	
	ROS_INFO("%f    %f   v1 %f position v1 %f\n ",t, time, v1,msg.position[0]);
    	ros::spinOnce();

    	loop_rate.sleep();
    	++count;
	}
	j1=msg.position[0];
	j2=msg.position[1];
	grip=msg.position[2];
 	}
  }


  return 0;
}



