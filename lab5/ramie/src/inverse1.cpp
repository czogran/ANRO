#include "ros/ros.h"
#include "ramie/inverse.h"
#include "nav_msgs/Path.h"
#include "interpolation.hpp" //bodajze w niej jest funkcja pose do robienia PoseStamped
//#include <oint_interpolation.hpp>
#include <geometry_msgs/PoseStamped.h>

#include <math.h> 


float x,y,z;
float l1,l2;
float h_base,h_griper;
float a,b,c;
float alfa, beta,alfa1,alfa_result,grip;


float pi=3.1415;
//zmienne pomocnicze
float A,B,C,D,delta,help;

//publishery
ros::Publisher chatter_pub;
ros::Publisher chatter_pub1;
ros::Publisher path_pub;

//wiadomosci
nav_msgs::Path path_msg;
geometry_msgs::PoseStamped pose1;



void jointCallback(const geometry_msgs::PoseStamped & poses)
{
	path_msg.header.stamp=ros::Time::now();
	path_msg.header.frame_id="base_link";

	//okreslenie pozycji koncowki z wiadomosci poze, by mniej pisac nowe zmienne x,y,z
	x=poses.pose.position.x;
	y=poses.pose.position.y;
	z=poses.pose.position.z;
	
	//parametry robota
	/*l1=0.6;
	l2=0.6;
	h_base=0.6;
	h_griper=0.2;

	grip=-z+h_base-2*h_griper;*/
		if((pow(x,2)+pow(y,2))>0.16&&z>0.1&&z<0.7&&(pow(x,2)+pow(y,2))<1.4)
{
	grip=-z+h_base-2*h_griper;
	beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
	A=y-l2*sin(beta)*x/(l1+l2*cos(beta));
	B=l1+l2*cos(beta)+(sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
	alfa=asin(A/B);

	C=x+l2*sin(beta)*y/(l1+l2*cos(beta));
	D=l1+l2*cos(beta)+l2*l2*sin(beta)*sin(beta)/(l1+l2*cos(beta));
	alfa1=acos(C/D);

	//obszar 1	
	if (alfa>0 &&alfa<=pi/2 &&alfa1>=0&&alfa1<pi/2)
	{
			ROS_INFO("1alfa:%f   beta:%f",alfa,alfa1);
		alfa_result=alfa;
	}
	//obszar 2
	else if(alfa>0&&alfa<pi/2 && alfa1>pi/2 && alfa1<pi)
	{
		ROS_INFO("2alfa:%f   beta:%f",alfa,alfa1);
		alfa_result=alfa1;
	}
	//obszar 3
	else if(alfa<0 && alfa1>pi/2&& alfa1<pi)
	{
		ROS_INFO("3alfa:%f   beta:%f",alfa,alfa1);
		alfa_result=2*pi-alfa1;
	}
	//obszar 4
	else if(alfa<0 && alfa1>0&&alfa1<=pi/2)
	{
		ROS_INFO("4alfa:%f   beta:%f",alfa,alfa1);
		alfa_result=alfa;
	}

	sensor_msgs::JointState msg;
	msg.name.resize(3);
 	msg.position.resize(3);
 	msg.name[0]="base_to_joint1";
	msg.name[1]="box1_to_joint2";
 	msg.name[2]="box2_to_gripper_prismatic";


	msg.header.stamp=ros::Time::now();
	msg.position[0]=alfa_result;
	msg.position[1]=beta;
	msg.position[2]=grip;
	//path_msg=path(msg.position[0],msg.position[1],msg.position[2]);
	// path_msg.header.stamp=ros::Time::now();
	pose1=pose(msg.position[0],msg.position[1],msg.position[2]);
	//	path_msg.poses.push_back(pose1);
		
    	//publishery, PointStamped i Sensor
    	chatter_pub.publish(msg);
		chatter_pub1.publish(pose1);
    //	ros::spinOnce();
}
else
ROS_INFO("zle parametry");


}


int main(int argc,char **argv)
{
	
 ros::init(argc, argv, "ikin");
 ros::NodeHandle n;
 
n.param<float>("l1",l1,0.6);
 n.param<float>("l2",l2,0.6);
 n.param<float>("h_base",h_base,0.6);
 n.param<float>("h_griper",h_griper,0.2);
 chatter_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
 chatter_pub1 = n.advertise<geometry_msgs::PoseStamped>("to_rviz", 1000);
 
 ros::Subscriber sub = n.subscribe("pose", 1000, jointCallback);
 ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 400);
 ros::spin();
return 0;
}













	
/*
	if(x>0 && y>0)
	{
		ROS_INFO("1alfa:%f   beta:%f",alfa,alfa1);
		beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
		A=y-l2*sin(beta)*x/(l1+l2*cos(beta));
		B=l1+l2*cos(beta)+(sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
		alfa=asin(A/B);

		C=x+l2*sin(beta)*y/(l1+l2*cos(beta));
		D=l1+l2*cos(beta)+l2*l2*sin(beta)*sin(beta)/(l1+l2*cos(beta));
		alfa1=acos(C/D);
	
	}	
	if(x<=0 && y>0)
	{
		ROS_INFO("2alfa:%f   beta:%f",alfa,alfa1);
		beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));	
		A=y-(l2*sin(beta)*x)/(l1+l2*cos(beta));
		B=l1+l2*cos(beta)+(sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
		alfa=asin(A/B);

		C=x+l2*sin(beta)*y/(l1+l2*cos(beta));
		D=l1+l2*cos(beta)+l2*l2*sin(beta)*sin(beta)/(l1+l2*cos(beta));
		alfa1=acos(C/D);

	}
	if(x<=0 && y<=0)
	{
		ROS_INFO("3alfa:%f   beta:%f",alfa,alfa1);
		beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
		A=y-(l2*sin(beta)*x)/(l1+l2*cos(beta));
		B=l1+l2*cos(beta)+(sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
		alfa=asin(A/B);

		C=x+l2*sin(beta)*y/(l1+l2*cos(beta));
		D=l1+l2*cos(beta)+l2*l2*sin(beta)*sin(beta)/(l1+l2*cos(beta));
		alfa1=acos(C/D);	
	}
	if(x>0 && y<=0)
	{
		ROS_INFO("4alfa:%f   beta:%f",alfa,alfa1);
		beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
		A=y-l2*sin(beta)*x/(l1+l2*cos(beta));
		B=l1+l2*cos(beta)+(sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
		alfa=asin(A/B);
	
		C=x+l2*sin(beta)*y/(l1+l2*cos(beta));
		D=l1+l2*cos(beta)+l2*l2*sin(beta)*sin(beta)/(l1+l2*cos(beta));
		alfa1=acos(C/D);		
	}*/




	//policzony kąt beta, iedzy dwoma ramionami	
 	//if(y>0)
//	beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
	//else
	//beta=2*3.1415-acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
	
	//else
	//beta=	
	
	//obliczenia pomocnicze
	//A=y-l2*sin(beta)*x/(l1+l2*cos(beta));
	//B=(l1+l2*cos(beta)+sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
	/*if(A/B>1)
		{
		A=1;
		B=1;
		}
	if(A/B<-1)
		{
		A=-1;
		B=1;
		}*/
	//if(x>0)	
//	alfa=asin(A/B);
	//else
	//alfa=3.1415-asin(A/B);	
	/*if(start==0&&alfa_prev==0)
{

		beta=acos((x*x+y*y-l1*l1-l2*l2)/(2*l1*l2));
		A=y-l2*sin(beta)*x/(l1+l2*cos(beta));
	B=l1+l2*cos(beta)+(sin(beta)*sin(beta)*l2*l2)/(l1+l2*cos(beta));
	alfa_prev=	asin(A/B);
start=1;
}
*/




	/*a=poses.pose.position.x;
	b=poses.pose.position.y;
	c=poses.pose.position.z;
	
	r=0.6;
	R=0.6;
	d=(pow(a,2)+pow(b,2)+pow(R,2)-pow(r,2));
	A=4*pow(a,2)+4*pow(b,2);
	B=-4*a*d;
	C=pow(d,2)-4*pow(b,2)*pow(R,2);
	delta=pow(B,2)-4*A*C;
	x=(-B+sqrt(delta))/2/A;
	help=x/R;
	ROS_INFO("moj x %f R:%f help:%f ",x,R,delta);
	alfa=acos(a/R);
	if(b<a*cos(alfa))
		beta=acos((a-x)/r)+alfa;
	else
		beta=acos((a-x)/r)-alfa;
	sensor_msgs::JointState msg;
 beta=0;
 msg.name.resize(3);
 msg.position.resize(3);
 msg.name[0]="base_to_joint1";
 msg.name[1]="box1_to_joint2";
 msg.name[2]="box2_to_gripper_prismatic";
 	*/
