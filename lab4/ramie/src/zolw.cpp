#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

#include <sstream>
#include <unistd.h>
#include <termios.h>

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
        return (buf);
}





int main(int argc, char **argv)
{
 char pozycja;
 std::string kierunek;
 std::string alfa;
 std::string beta;
 std::string alfa1;
 std::string beta1;
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;

  ros::param::get("~prosto",alfa);
  ros::param::get("~wlewo", beta);
  ros::param::get("~wprawo",beta1);
  ros::param::get("~tyl",alfa1);
	//n.getParam("wlewo", beta); //nie wiem czemu nie działa
	//n.getParam("wprawo",beta1);
	//n.getParam("tyl",alfa1);
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

  ros::Rate loop_rate(10);
  geometry_msgs::Twist msg;
 
 
  int count = 0;
  while (ros::ok())
  {
    msg.linear.x=0.0;
    msg.linear.y=0.0;
    msg.linear.z=0.0;
 
    msg.angular.x=0.0;
    msg.angular.y=0.0;
    msg.angular.z=0.0;

    pozycja=getch();
    kierunek=pozycja;
    if (kierunek ==alfa)
	{
		msg.linear.x=1.0;
	}
    else if(kierunek ==alfa1){
	msg.linear.x=-1.0;
	}
    else if(kierunek ==beta){
	msg.angular.z=1.0;
	}
   else if(kierunek ==beta1){
	msg.angular.z=-1.0;
	}
	

    
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
